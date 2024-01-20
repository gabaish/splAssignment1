#include "../include/WareHouse.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <functional>
#include <iterator>

WareHouse::WareHouse(const string &configFilePath){
    
    isOpen = false;
    actionsLog = vector<BaseAction*>();
    volunteers = vector<Volunteer*>();
    pendingOrders = vector<Order*>();
    inProcessOrders = vector<Order*>();
    completedOrders = vector<Order*>();
    customers = vector<Customer*>();
    int customerCounter=0; //For assigning unique customer IDs
    int volunteerCounter=0; //For assigning unique volunteer IDs
    int orderCounter=0;
    
    
    
    //do we need to add each action to the action log?
    ifstream configFile(configFilePath);

    if(configFile.is_open())
    {
        string line;
        while(getline(configFile,line))
        {
            istringstream iss(line);

            string type;
            iss >> type;

            if(type == "customer")
            {
                string customer_name, customer_type;
                int customer_distance, max_orders;
                iss >> customer_name >> customer_type >> customer_distance >> max_orders;
                AddCustomer AddCustomer(customer_name,customer_type,customer_distance,max_orders);
                AddCustomer.act(*this);
            }       


            //do this. add new addvolunteer function.
            else if(type == "volunteer")
            {
                
                string volunteer_name, volunteer_role;
                iss >> volunteer_name >> volunteer_role;
                Volunteer* new_volunteer=nullptr;
                if(volunteer_role=="collector"){
                    int volunteer_coolDown;
                    iss >> volunteer_coolDown;
                    new_volunteer=new CollectorVolunteer(volunteerCounter,volunteer_name,volunteer_coolDown);

                }
                else if(volunteer_role=="limited_collector"){
                    int volunteer_coolDown, volunteer_maxOrders;
                    iss >> volunteer_coolDown >> volunteer_maxOrders;
                    new_volunteer=new LimitedCollectorVolunteer(volunteerCounter,volunteer_name,volunteer_coolDown,volunteer_maxOrders);
                }
                else if(volunteer_role=="driver"){
                    int volunteer_maxDistance, distance_per_step;
                    iss >> volunteer_maxDistance >> distance_per_step;
                    new_volunteer=new DriverVolunteer(volunteerCounter,volunteer_name,volunteer_maxDistance,distance_per_step);
                }
                else if(volunteer_role=="limited_driver"){
                    int volunteer_maxDistance, distance_per_step, volunteer_maxOrders;
                    iss >> volunteer_maxDistance >> distance_per_step >> volunteer_maxOrders;
                    new_volunteer=new LimitedDriverVolunteer(volunteerCounter,volunteer_name,volunteer_maxDistance,distance_per_step,volunteer_maxOrders);
                }

                volunteers.push_back(new_volunteer);
                volunteerCounter++;
            
            }


        }
    }
}

void WareHouse::start() 
{
    open();
    cout<<"Warehouse is open!"<<endl;

    //verify if we need to verify the user input (entered number, entered enough arguments..)
    //check if we can changw to switch 
    while(isOpen){

        std::string user_input;
        std::getline(std::cin, user_input);
        std::istringstream iss(user_input);
        std::vector<std::string> tokens{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};

        if(!tokens.empty()){
            std:: string action=tokens[0];

            //looking for the action:
            if(action=="step"){
                //do we need to verify if the input is correct?
                int numOfSteps=std::stoi(tokens[1]);
                SimulateStep simulateStep(numOfSteps);
                simulateStep.act(*this);
            }
            else if(action=="order"){
                int customer_id=std::stoi(tokens[1]);
                AddOrder addOrder(customer_id);
                addOrder.act(*this);
            }
            else if(action=="customer"){
                string customer_name=tokens[1];
                string customer_type=tokens[2];
                int customer_distance=std::stoi(tokens[3]);
                int max_orders=std::stoi(tokens[4]);
                AddCustomer addCustomer(customer_name,customer_type,customer_distance,max_orders);
                addCustomer.act(*this);
            }
            else if(action=="orderStatus"){
                int order_id=std::stoi(tokens[1]);
                PrintOrderStatus printOrderStatus(order_id);
                printOrderStatus.act(*this);

            }
            else if(action=="customerStatus"){
                int customer_id=std::stoi(tokens[1]);
                PrintCustomerStatus printCustomerStatus(customer_id);
                printCustomerStatus.act(*this);
            }
            else if(action=="volunteerStatus"){
                int volunteer_id=std::stoi(tokens[1]);
                PrintVolunteerStatus printVolunteerStatus(volunteer_id);
                printVolunteerStatus.act(*this);
            }
            else if(action=="log"){
                PrintActionsLog printActionsLogs();
                printActionsLogs.act(*this);
            }
            else if(action=="close"){
                Close close();
                close.act(*this);
            }
            else if(action=="backup"){
                BackupWareHouse BackupWareHouse();
                BackupWareHouse.act(*this);
            }
            else if(action=="restore"){
                RestoreWareHouse RestoreWareHouse();
                RestoreWareHouse.act(*this);
            }

        }
    }

}

//need to change the method name to getActions()
const vector<BaseAction*> &WareHouse::getActionsLog() const
{
    return actionsLog;
}

//make sure we only need to add to the pendingOrders vector - i think yes
//Do we need to add checks before adding? if the info is correct?
void WareHouse:: addOrder(Order* order)
{
    pendingOrders.push_back(order);
    orderCounter++;
}

//TO DO (what to do in here?)
void WareHouse:: addAction(BaseAction* action)
{
    actionsLog.push_back(action);
}

//TO DO (what to do in here?)
//No Need - the deleted the method
void WareHouse:: printActionsLogs()
{
    for(const auto& action : actionsLog)
    {
        cout << action << endl;
    }
}


//deal with the issue if customer doesnt exists 
//inside the print customers status
Customer &WareHouse::getCustomer(int customerId) const
{
    for(const auto& customer : customers){
        if(customer ->getId()==customerId){
            return *customer;
        }
    }
    
}
 //inside the print volunteer status
Volunteer &WareHouse::getVolunteer(int volunteerId) const{
    for(const auto& volunteer : volunteers){
        if(volunteer ->getId()==volunteerId){
            return *volunteer;
        }
    }
}
//inside the print order status
Order &WareHouse::getOrder(int orderId) const{
    //see what shay is expecting in case null
}


void WareHouse::close() 
{
    for(const auto& pending_order : pendingOrders)
        cout<< pending_order << endl;
    for(const auto& inProcess_order : inProcessOrders)
        cout<< inProcess_order << endl;
    for(const auto& completed_order : completedOrders)
        cout<< completed_order << endl;
    
    isOpen=false;

    //add rule of 5
    //free memory
    //should i print something in the end?
}

//shoud i add something ekse?
void WareHouse::open(){
    isOpen=true;
} 

//should i add log?
void WareHouse::addCustomer(Customer* customer){
    customers.push_back(customer);
    customerCounter++;

}


void WareHouse::addVolunteer(string volunteer_name, string volunteerRole, istringstream iss){
    Volunteer* new_volunteer=nullptr;

    if(volunteerRole=="collector"){
        int volunteer_coolDown;
        iss >> volunteer_coolDown;
        new_volunteer=new CollectorVolunteer(volunteerCounter,volunteer_name,volunteer_coolDown);

    }
    else if(volunteerRole=="limited_collector"){
        int volunteer_coolDown, volunteer_maxOrders;
        iss >> volunteer_coolDown >> volunteer_maxOrders;
        new_volunteer=new LimitedCollectorVolunteer(volunteerCounter,volunteer_name,volunteer_coolDown,volunteer_maxOrders);
    }
    else if(volunteerRole=="driver"){
        int volunteer_maxDistance, distance_per_step;
        iss >> volunteer_maxDistance >> distance_per_step;
        new_volunteer=new DriverVolunteer(volunteerCounter,volunteer_name,volunteer_maxDistance,distance_per_step);
    }
     else if(volunteerRole=="limited_driver"){
        int volunteer_maxDistance, distance_per_step, volunteer_maxOrders;
        iss >> volunteer_maxDistance >> distance_per_step >> volunteer_maxOrders;
        new_volunteer=new LimitedDriverVolunteer(volunteerCounter,volunteer_name,volunteer_maxDistance,distance_per_step,volunteer_maxOrders);
    }

    volunteers.push_back(new_volunteer);
    volunteerCounter++;


}

int WareHouse::getCustomerCounter() const{
    return this->customerCounter;
}

int WareHouse::getVolunteerCounter() const{
    return this->volunteerCounter;
}
//check if need to delete something else
WareHouse:: ~WareHouse() {
    for(BaseAction* action: actionsLog){
        delete action;
    }
    for (Volunteer* volunteer : volunteers) {
        delete volunteer;
    }
    for (Order* order : pendingOrders) {
        delete order;
    }
    for (Order* order : inProcessOrders) {
        delete order;
    }
    for (Order* order : completedOrders) {
        delete order;
    }
    for (Customer* customer : customers) {
        delete customer;
    }
}

WareHouse::WareHouse(const WareHouse& other){
    //copying the isOpen status:
    this ->isOpen=other.isOpen;
    //clone all actionsLog:
    for(const BaseAction* action : other.actionsLog){
        this ->actionsLog.push_back(action->clone());
    }
    //clone all volunteers:
    for(const Volunteer* volunteer : other.volunteers){
        this ->volunteers.push_back(volunteer->clone());
    }
    //clone all pending orders:
    for(const Order* pendingOrder : other.pendingOrders){
        this ->pendingOrders.push_back(pending_order->clone());
    }
    //clone all inProcess orders:
    for(const Order* inProcessOrder : other.inProcessOrders){
        this ->inProcessOrders.push_back(pending_order->clone());
    }
    //clone all completed orders:
    for(const Order* completedOrder : other.completedOrders){
        this -> completedOrders.push_back(completedOrder->clone());
    }
    //clone all the customers:
    for(const Customer* customer : other.customers){
        this->customers.push_back(customer->clone());
    }
    //copying the current customerCounter:
    this ->customerCounter=other.customerCounter;
    //copying the current volunteerCounter:
    this ->volunteerCounter=other.volunteerCounter;

}

//maybe we can do it more efficantly 
WareHouse &WareHouse::operator=(const WareHouse &other){
    if(this!=&other){
        this ->isOpen=other.isOpen;

        //delete old actionLogs:
        for(int i=0;i<=this->actionsLog.size();i++)
            delete this ->actionsLog.at(i);
        //clear old actions logs addresses:
        this ->actionsLog.clear();
        // add other actionLogs:
        for(int i=0;i<=other.actionsLog.size();i++)
            this ->actionsLog.push_back(other.actionsLog.at(i)->clone());

        //delete old volunteers:
        for(int i=0;i<=this->volunteers.size();i++)
            delete this ->volunteers.at(i);
        //clear old volunteers addresses:
        this ->volunteers.clear();
        // add other volunteers:
        for(int i=0;i<=other.volunteers.size();i++)
            this ->volunteers.push_back(other.volunteers.at(i)->clone());
        

        //delete old pendingOrders:
        for(int i=0;i<=this->pendingOrders.size();i++)
            delete this ->pendingOrders.at(i);
        //clear old pendingOrders addresses:
        this ->pendingOrders.clear();
        // add other pendingOrders:
        for(int i=0;i<=other.pendingOrders.size();i++)
            this ->pendingOrders.push_back(other.pendingOrders.at(i)->clone());
        

        //delete old inProcessOrders:
        for(int i=0;i<=this->inProcessOrders.size();i++)
            delete this ->inProcessOrders.at(i);
        //clear old inProcessOrders addresses:
        this ->inProcessOrders.clear();
        // add other inProcessOrders:
        for(int i=0;i<=other.inProcessOrders.size();i++)
            this ->inProcessOrders.push_back(other.inProcessOrders.at(i)->clone());
        

        //delete old completedOrders:
        for(int i=0;i<=this->completedOrders.size();i++)
            delete this ->completedOrders.at(i);
        //clear old completedOrders addresses:
        this ->completedOrders.clear();
        // add other completedOrders:
        for(int i=0;i<=other.completedOrders.size();i++)
            this ->completedOrders.push_back(other.completedOrders.at(i)->clone());
        

        //delete old customers:
        for(int i=0;i<=this->customers.size();i++)
            delete this ->customers.at(i);
        //clear old customers addresses:
        this ->customers.clear();
        // add other customers:
        for(int i=0;i<=other.customers.size();i++)
            this ->customers.push_back(other.completedOrders.at(i)->clone());        }

        this->customerCounter=other.customerCounter;
        this ->volunteerCounter=other.volunteerCounter;
}


//move constructor:
WareHouse::WareHouse(WareHouse &&other) noexcept : isOpen(other.isOpen), actionsLog(std::move(other.actionsLog)), volunteers(std::move(other.volunteers)), pendingOrders(std::move(other.pendingOrders)), inProcessOrders(std::move(other.inProcessOrders)), completedOrders(std::move(other.completedOrders)),customers(std::move(other.customers)), customerCounter(other.customerCounter), volunteerCounter(other.volunteerCounter), orderCounter(other.orderCounter){
    
    //do we need to nullptr this?
    other.isOpen=flase;
    other.customerCounter=0;
    other.volunteerCounter=0;
    other.orderCounter=0;

    //do we need to delete the vectors?
}



//TODO move constructor and move assignment constructor







