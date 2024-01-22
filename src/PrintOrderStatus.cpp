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
        cout << "Collector: " << order.getCollectorId() << endl;
        cout << "Driver: " << order.getDriverId() << endl;

        this->complete();
    }
    // if this orderId does not exist in the warehouse - return an error
    else{
        this->error("Order doesn't exist");
    }

    wareHouse.addAction(this);

    // override?
}

PrintOrderStatus* PrintOrderStatus:: clone() const{
    return new PrintOrderStatus(*this);

    // is this the way? 
    // override? 
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

    // override?
}