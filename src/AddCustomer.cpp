#include "../include/BaseAction.h"

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
}


    


