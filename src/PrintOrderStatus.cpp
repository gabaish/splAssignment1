#include "../include/Action.h"
#include <iostream>

PrintOrderStatus::PrintOrderStatus(int id):
orderId(id){}

void PrintOrderStatus:: act(WareHouse &wareHouse){
    // checking if the orderId is in the correct range 
    if(orderId>=0 && orderId<=wareHouse.getOrderCounter()){
        Order& order = wareHouse.getOrder(orderId);
        cout << "OrderId: " << order.getId() << endl;
        cout << "OrderStatus: " << order.getStatusString() << endl;
        cout << "CustomerId: " << order.getCustomerId() << endl;
        cout << "Collector: " << ((order.getCollectorId()!=-1) ? to_string(order.getCollectorId()) : ("None")) << endl;
        cout << "Driver: " << ((order.getDriverId()!=-1) ? to_string(order.getDriverId()) : ("None")) << endl;

        this->complete();
    }
    // if this orderId does not exist in the warehouse - return an error
    else{
        this->error("Order doesn't exist");
        cout << this->getErrorMsg() << endl;
    }

    wareHouse.addAction(this);

}

PrintOrderStatus* PrintOrderStatus:: clone() const{
    return new PrintOrderStatus(*this);

}

std::string PrintOrderStatus:: toString() const{
    string returnString = "orderStatus ";
    returnString.append(std::to_string(this->orderId));
    returnString.append(" ");
    returnString.append(this->getStatusString());
    if(this->getStatus() ==  ActionStatus::ERROR){
        returnString.append(" ");
        returnString.append(this->getErrorMsg());
    }

    return returnString;

}

PrintOrderStatus:: ~PrintOrderStatus() = default;