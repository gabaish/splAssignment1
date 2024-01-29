#include "../include/WareHouse.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <functional>
#include <iterator>
#include <algorithm>


WareHouse::WareHouse(const string &configFilePath):
isOpen(false),actionsLog(vector<BaseAction*>()),volunteers(vector<Volunteer*>()),
pendingOrders(vector<Order*>()),inProcessOrders(vector<Order*>()),completedOrders(vector<Order*>()),
customers(vector<Customer*>()),customerCounter(0),volunteerCounter(0),orderCounter(0){
    
    //adding default volunteer with id=-1  to volunteers:
    Volunteer* default_volunteer = new CollectorVolunteer(-1, "default",0);
    volunteers.push_back(default_volunteer);
        
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
                addCustomerConfig(customer_name,customer_type,customer_distance,max_orders);
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

    while(isOpen){

        std::string user_input;
        std::getline(std::cin, user_input);
        std::istringstream iss(user_input);
        std::vector<std::string> tokens{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};

        if(!tokens.empty()){
            std:: string action=tokens[0];

            //looking for the action:
            if(action=="step"){
                int numOfSteps=std::stoi(tokens[1]);
                SimulateStep* simulateStep=new SimulateStep(numOfSteps);
                simulateStep->act(*this);
            }
            else if(action=="order"){
                int customer_id=std::stoi(tokens[1]);
                AddOrder* addOrder = new AddOrder(customer_id);
                addOrder->act(*this);
            }
            else if(action=="customer"){
                string customer_name=tokens[1];
                string customer_type=tokens[2];
                int customer_distance=std::stoi(tokens[3]);
                int max_orders=std::stoi(tokens[4]);
                AddCustomer* addCustomer=new AddCustomer(customer_name,customer_type,customer_distance,max_orders);
                addCustomer->act(*this);
            }
            else if(action=="orderStatus"){
                int order_id=std::stoi(tokens[1]);
                PrintOrderStatus* printOrderStatus=new PrintOrderStatus(order_id);
                printOrderStatus->act(*this);

            }
            else if(action=="customerStatus"){
                int customer_id=std::stoi(tokens[1]);
                PrintCustomerStatus* printCustomerStatus=new PrintCustomerStatus(customer_id);
                printCustomerStatus->act(*this);
            }
            else if(action=="volunteerStatus"){
                int volunteer_id=std::stoi(tokens[1]);
                PrintVolunteerStatus* printVolunteerStatus=new PrintVolunteerStatus(volunteer_id);
                printVolunteerStatus->act(*this);
            }
            else if(action=="log"){
                PrintActionsLog* printActionsLogs=new PrintActionsLog();
                printActionsLogs->act(*this);
            }
            else if(action=="close"){
                Close* close=new Close();
                close->act(*this);
            }
            else if(action=="backup"){
                BackupWareHouse* backupWareHouse=new BackupWareHouse();
                backupWareHouse->act(*this);
            }
            else if(action=="restore"){
                RestoreWareHouse* restoreWareHouse=new RestoreWareHouse();
                restoreWareHouse->act(*this);
            }

        }
    }

    //delete this;

}

const vector<BaseAction*> &WareHouse::getActions() const
{
    return this->actionsLog;
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


//deal with the issue if customer doesnt exists 
//inside the print customers status
Customer &WareHouse::getCustomer(int customerId) const
{
    Customer* returnCustomer = nullptr;
    for(const auto customer : customers){
        if(customer ->getId()==customerId){
            returnCustomer = customer;
        }
    }
    return *returnCustomer;
    
}
 //inside the print volunteer status
Volunteer &WareHouse::getVolunteer(int volunteerId) const{
    for(const auto& volunteer : volunteers){
        if(volunteer ->getId()==volunteerId){
            return *volunteer;
        }
    }
    //returning the default volunteer:
    return getVolunteer(-1);
}
//inside the print order status
Order& WareHouse::getOrder(int orderId) const{
    // we only get here after we cmade sure that this orderId exists in the warehouse
    Order* returnOrder = nullptr;
    for(Order* pending_order : pendingOrders)
    {
        if(pending_order->getId()==orderId)
            returnOrder= pending_order;
    }
    for(Order* inProcess_order : inProcessOrders)
    {
        if(inProcess_order->getId()==orderId)
            returnOrder= inProcess_order;
    }
    for(Order* completed_order : completedOrders)
    {
        if(completed_order->getId()==orderId)
            returnOrder= completed_order; 
    }
    return *returnOrder;

}


void WareHouse::close() 
{
    for(const auto& pending_order : pendingOrders)
        cout<< pending_order->toString() << endl;
    for(const auto& inProcess_order : inProcessOrders)
        cout<< inProcess_order->toString() << endl;
    for(const auto& completed_order : completedOrders)
        cout<< completed_order->toString() << endl;
    
    isOpen=false;

    //free memory - Implemented when going out of the loop of start
}

void WareHouse::open(){
    isOpen=true;
} 

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

void WareHouse::moveOrderFromPendingToInProcess(Order* order){
    // remove the order from pendingOrders
    auto it = std::remove(this->pendingOrders.begin(), this->pendingOrders.end(), order);
    this->pendingOrders.erase(it, pendingOrders.end());
    // I really really hope it works - its from chatGPT

    // add the order to inProcessOrders
    this->inProcessOrders.push_back(order);

}

void WareHouse::moveOrderFromInProcessToPending(Order* order){
    // maybe it should get const ref? and not pinter..? but its a vector of pointers
    // remove the order from inProcessOrders
    auto it = std::remove(this->inProcessOrders.begin(), this->inProcessOrders.end(), order);
    this->inProcessOrders.erase(it, inProcessOrders.end());
    // I really really hope it works - its from chatGPT


    // add the order to pendingOrders
    this->pendingOrders.push_back(order);

}
void WareHouse::moveOrderFromInProcessToCompleted(Order* order){
    // maybe it should get const ref? and not pinter..? but its a vector of pointers
    // remove the order from pendingOrders
    auto it = std::remove(this->inProcessOrders.begin(), this->inProcessOrders.end(), order);
    this->inProcessOrders.erase(it, inProcessOrders.end());
    // I really really hope it works - its from chatGPT

    // add the order to inProcessOrders
    this->completedOrders.push_back(order);

}

void WareHouse::removeVolunteer(Volunteer* volunteer){
    auto it = std::remove(this->volunteers.begin(), this->volunteers.end(), volunteer);
    this->volunteers.erase(it, volunteers.end());
}

int WareHouse::getCustomerCounter() const{
    return this->customerCounter;
}

int WareHouse::getVolunteerCounter() const{
    return this->volunteerCounter;
}

int WareHouse::getOrderCounter() const{
    return this->orderCounter;
}

void WareHouse:: firstSchemastep(){
    //first step in the schema - move orders from pendingOrders to relevant volunteers
    for(Order* order : this->pendingOrders){
        if(order->getStatus()==OrderStatus::PENDING){
            // looking for an available collector
            for(Volunteer* volunteer : this->volunteers) {
                if(((volunteer->getVolunteerType()== VolunteerType::Collector)||(volunteer->getVolunteerType()== VolunteerType::LimitedCollector)) 
                && volunteer->getId()!=-1 && volunteer->canTakeOrder(*order)){
                    volunteer->acceptOrder(*order);
                    order->setCollectorId(volunteer->getId());
                    order->setStatus(OrderStatus::COLLECTING);
                    this->moveOrderFromPendingToInProcess(order);
                    break;
                }
            }
        }
    }

    for(Order* order : this->pendingOrders){
        if (order->getStatus()==OrderStatus::COLLECTING){
            // looking for an available driver
            for(Volunteer* volunteer : this->volunteers){
                if(((volunteer->getVolunteerType()== VolunteerType::Driver)||(volunteer->getVolunteerType()== VolunteerType::LimitedDriver)) 
                && volunteer->canTakeOrder(*order)){
                    volunteer->acceptOrder(*order);
                    order->setDriverId(volunteer->getId());
                    order->setStatus(OrderStatus::DELIVERING);
                    this->moveOrderFromPendingToInProcess(order);
                    break;
                }
            }
        }
    }


    // for(Order* order : this->pendingOrders){
    //     if(order->getStatus()==OrderStatus::PENDING){
    //         // looking for an available collector
    //         for(Volunteer* volunteer : this->volunteers) {
    //             if(((volunteer->getVolunteerType()== VolunteerType::Collector)||(volunteer->getVolunteerType()== VolunteerType::LimitedCollector)) 
    //             && volunteer->getId()!=-1 && volunteer->canTakeOrder(*order)){
    //                 volunteer->acceptOrder(*order);
    //                 order->setCollectorId(volunteer->getId());
    //                 order->setStatus(OrderStatus::COLLECTING);
    //                 this->moveOrderFromPendingToInProcess(order);
    //                 break;
    //             }
    //         }       
    //     } else if (order->getStatus()==OrderStatus::COLLECTING){
    //         // looking for an available driver
    //         for(Volunteer* volunteer : this->volunteers){
    //             if(((volunteer->getVolunteerType()== VolunteerType::Driver)||(volunteer->getVolunteerType()== VolunteerType::LimitedDriver)) 
    //             && volunteer->canTakeOrder(*order)){
    //                 volunteer->acceptOrder(*order);
    //                 order->setDriverId(volunteer->getId());
    //                 order->setStatus(OrderStatus::DELIVERING);
    //                 this->moveOrderFromPendingToInProcess(order);
    //                 break;
    //             }
    //         }
    //     }

    // }
}

void WareHouse:: secondAndThirdSchemaStep(){
    // second step in the schema - perform a step in the simulation
    // third step in the schema - once performing a step - check if they are done processing
    for(Volunteer* volunteer : this->volunteers){
        // if the volunteer is curentlly working on something - we should simulate a step
        if(volunteer->isBusy())
        {
            volunteer->step();
            // if after the step the volunteer is done processing - the activeOrderId shold be NO_ORDER
            if(volunteer->getActiveOrderId()==NO_ORDER){
                
                // collectors should push their order to pendingOrders
                if((volunteer->getVolunteerType()== VolunteerType::Collector)||(volunteer->getVolunteerType()== VolunteerType::LimitedCollector)){
                    Order& orderToAdd = this->getOrder(volunteer->getCompletedOrderId());
                    this->moveOrderFromInProcessToPending(&orderToAdd);
                    volunteer->setCompletedOrderId(NO_ORDER);
                }
                // drivers should push their order to completedOrders
                if((volunteer->getVolunteerType()== VolunteerType::Driver)||(volunteer->getVolunteerType()== VolunteerType::LimitedDriver)){
                    Order& orderToAdd = this->getOrder(volunteer->getCompletedOrderId());
                    this->moveOrderFromInProcessToCompleted(&orderToAdd);
                    volunteer->setCompletedOrderId(NO_ORDER);
                    orderToAdd.setStatus(OrderStatus::COMPLETED);
                }
            }
        }
    }
}

void WareHouse:: fourthSchemaStep(){
    // fourth step in the schema - delete volunteers that had maxed out and finished their last order
    for(Volunteer* volunteer : this->volunteers){
        if(!(volunteer->hasOrdersLeft()) && !volunteer->isBusy()){
            this->removeVolunteer(volunteer);

            delete volunteer;
        }

    }
}

// destructor
//check if need to delete something else
WareHouse:: ~WareHouse() {
    for(BaseAction* action: this->actionsLog){
        delete action;
    }
    for (Volunteer* volunteer : this->volunteers) {
        delete volunteer;
    }
    for (Order* order : this->pendingOrders) {
        delete order;
    }
    for (Order* order : this->inProcessOrders) {
        delete order;
    }
    for (Order* order : this->completedOrders) {
        delete order;
    }
    for (Customer* customer : this->customers) {
        delete customer;
    }
}

WareHouse::WareHouse(const WareHouse& other):
isOpen(other.isOpen),actionsLog(vector<BaseAction*>()),volunteers(vector<Volunteer*>()),pendingOrders(vector<Order*>()),
inProcessOrders(vector<Order*>()),completedOrders(vector<Order*>()),customers(vector<Customer*>()),
customerCounter(other.customerCounter),volunteerCounter(other.volunteerCounter),orderCounter(other.orderCounter)
{
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
        this ->pendingOrders.push_back(pendingOrder->clone());
    }
    //clone all inProcess orders:
    for(const Order* inProcessOrder : other.inProcessOrders){
        this ->inProcessOrders.push_back(inProcessOrder->clone());
    }
    //clone all completed orders:
    for(const Order* completedOrder : other.completedOrders){
        this -> completedOrders.push_back(completedOrder->clone());
    }
    //clone all the customers:
    for(const Customer* customer : other.customers){
        this->customers.push_back(customer->clone());
    }

}

//maybe we can do it more efficantly 
WareHouse &WareHouse::operator=(const WareHouse &other){
    if(this!=&other){
        this ->isOpen=other.isOpen;

        //delete old actionLogs:
        for(BaseAction* action: actionsLog){
            delete action;
        }
        //clear old actions logs addresses:
        this ->actionsLog.clear();
        // add other actionLogs:
        for(BaseAction* action: other.actionsLog){
            this->actionsLog.push_back(action->clone());
        }
        //delete old volunteers:
        for(Volunteer* volunteer: volunteers){
            delete volunteer;
        }
        //clear old volunteers addresses:
        this ->volunteers.clear();
        // add other volunteers:
        for(Volunteer* volunteer: other.volunteers){
            this->volunteers.push_back(volunteer->clone());
        }

        //delete old pendingOrders:
        for(Order* order: pendingOrders){
            delete order;
        }
        //clear old pendingOrders addresses:
        this ->pendingOrders.clear();
        // add other pendingOrders:
        for(Order* order: other.pendingOrders){
            this->pendingOrders.push_back(order->clone());
        }

        //delete old inProcessOrders:
        for(Order* order: inProcessOrders){
            delete order;
        }
        //clear old inProcessOrders addresses:
        this ->inProcessOrders.clear();
        // add other inProcessOrders:
        for(Order* order: other.inProcessOrders){
            this->inProcessOrders.push_back(order->clone());
        }

        //delete old completedOrders:
        for(Order* order: completedOrders){
            delete order;
        }
        //clear old completedOrders addresses:
        this ->completedOrders.clear();
        // add other completedOrders:
        for(Order* order: other.completedOrders){
            this->completedOrders.push_back(order->clone());
        }

        //delete old customers:
        for(Customer* customer : customers){
            delete customer;
        }
        //clear old customers addresses:
        this ->customers.clear();
        // add other customers:
        for(Customer* customer : other.customers){
            this->customers.push_back(customer->clone());
        }

        this->customerCounter=other.customerCounter;
        this ->volunteerCounter=other.volunteerCounter;
        this->orderCounter=other.orderCounter;
    }
    return *this;
}


//move constructor:
WareHouse::WareHouse(WareHouse &&other) noexcept : isOpen(other.isOpen), actionsLog(std::move(other.actionsLog)), volunteers(std::move(other.volunteers)), pendingOrders(std::move(other.pendingOrders)), inProcessOrders(std::move(other.inProcessOrders)), completedOrders(std::move(other.completedOrders)),customers(std::move(other.customers)), customerCounter(other.customerCounter), volunteerCounter(other.volunteerCounter), orderCounter(other.orderCounter){
    
    //do we need to nullptr this?
    other.isOpen=false;
    other.customerCounter=0;
    other.volunteerCounter=0;
    other.orderCounter=0;

    //do we need to delete the vectors?
}


//move assignment constructor:
WareHouse& WareHouse::operator=(WareHouse &&other) noexcept{
    if(this != &other){
        //delete old actionLogs:
        for(BaseAction* action: actionsLog){
            delete action;
        }
        //clear old actions logs addresses:
        this ->actionsLog.clear();
        
        //delete old volunteers:
        for(Volunteer* volunteer : volunteers){
            delete volunteer;
        }
        //clear old volunteers addresses:
        this ->volunteers.clear();
        
        //delete old pendingOrders:
        for(Order* order:pendingOrders){
            delete order;
        }
        //clear old pendingOrders addresses:
        this ->pendingOrders.clear();
       
        //delete old inProcessOrders:
        for(Order* order : inProcessOrders){
            delete order;
        }
        //clear old inProcessOrders addresses:
        this ->inProcessOrders.clear();

        //delete old completedOrders:
        for(Order* order : completedOrders){
            delete order;
        }
        //clear old completedOrders addresses:
        this ->completedOrders.clear();

        //delete old customers:
        for(Customer* customer: customers){
            delete customer;
        }
        //clear old customers addresses:
        this ->customers.clear();
       
       //move the resources from  other to this:
       isOpen=other.isOpen;
       actionsLog = std::move(other.actionsLog);
       volunteers = std::move(other.volunteers);
       pendingOrders = std::move(other.pendingOrders);
       inProcessOrders = std::move(other.inProcessOrders);
       completedOrders = std::move(other.completedOrders);
       customers = std::move(other.customers);
       customerCounter = other.customerCounter;
       volunteerCounter = other.volunteerCounter;
       orderCounter = other.orderCounter;

       //setting the other's to valid state:
       other.isOpen=false;
       other.customerCounter=0;
        other.volunteerCounter=0;
        other.orderCounter=0;
       
    }
    return *this;
}

void WareHouse::addCustomerConfig(string customerName, string customerType, int distance, int maxOrders){
    Customer* new_customer=nullptr;
    if(customerType=="soldier"){
        new_customer=new SoldierCustomer(customerCounter,customerName,distance,maxOrders);
    }
    else if(customerType=="civilian"){
        new_customer=new CivilianCustomer(customerCounter,customerName,distance,maxOrders);
    }
    addCustomer(new_customer);
}

