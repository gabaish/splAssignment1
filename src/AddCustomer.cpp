#include "../include/BaseAction.h"


//do we need to verify the input is correct? 
AddCustomer::AddCustomer(string customerName, string customerType, int distance, int maxOrders):
customerName(customerName),distance(distance),maxOrders(maxOrders),
    customerType(){
        if (customerType == "soldier") 
            CustomerType::Soldier;
        else if (customerType == "civilian")
            CustomerType::Civilian;
    }



void AddCustomer::act(WareHouse &wareHouse){
    Customer* new_customer=nullptr;
    if (customerType == CustomerType::Civilian){
        new_customer=new CivilianCustomer(wareHouse.getCustomerCounter(),customerName,distance,maxOrders);
    }
    else if (customerType == CustomerType::Soldier){
        new_customer=new SoldierCustomer(wareHouse.getCustomerCounter(),customerName,distance,maxOrders);
    }

    wareHouse.addCustomer(new_customer);
    wareHouse.addAction(this);

}

AddCustomer *AddCustomer::clone() const{
    return new AddCustomer(*this);
}

string AddCustomer::toString() const{
    string type;
    if(this->customerType == CustomerType::Civilian)
        type="civilian";
    else if(this->customerType == CustomerType::Soldier)
        type="soldier";
    string returnString = "customer ";
    returnString.append(this->customerName);
    returnString.append(" ");
    returnString.append(type);
    returnString.append(" ");
    returnString.append(std::to_string(this->distance));
    returnString.append(" ");
    returnString.append(std::to_string(this->maxOrders));
    returnString.append(" ");
    returnString.append(this->getStatusString());
    if(this->getStatus() ==  ActionStatus::ERROR){
        returnString.append(" ");
        returnString.append(this->getErrorMsg());
    }

    return returnString;

    // override?
}

    


