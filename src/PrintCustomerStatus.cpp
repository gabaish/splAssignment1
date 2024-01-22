#include "../include/Action.h"
#include <iostream>

PrintCustomerStatus::PrintCustomerStatus(int customerId) : customerId(customerId){}

void PrintCustomerStatus::act(WareHouse &wareHouse) {
    if(customerId>=0 && customerId<= wareHouse.getCustomerCounter()){
        cout << "CustomerID: " << customerId << endl;

        Customer& current_cutomer=wareHouse.getCustomer(customerId);

        //printing all inProcessOrders, if exist:
        const vector<int> &orders=current_cutomer.getOrdersIds();
        for(int order_id : orders){
            Order& current_order=wareHouse.getOrder(order_id);
            cout << "OrderID: " << order_id << endl;
            cout << "OrderStatus: " << current_order.getStatusString() << endl;
        }
        //printing the customer sum of orders left:
        cout << "numOrdersLeft: " << current_cutomer.getMaxOrders()-current_cutomer.getNumOrders() << endl;

        this->complete();
    }

    //error if the customerId doesn't exists:
    else{
        this->error("Customer doesn't exist");
        cout << "Customer doesn't exist" << endl;
    }
    wareHouse.addAction(this);

}

PrintCustomerStatus *PrintCustomerStatus::clone() const{
    return new PrintCustomerStatus(*this);
}

string PrintCustomerStatus::toString() const{
    string returnString = "volunteerStatus ";
    returnString.append(std::to_string(this->customerId));
    returnString.append(" ");
    returnString.append(this->getStatusString());
    if(this->getStatus() ==  ActionStatus::ERROR){
        returnString.append(" ");
        returnString.append(this->getErrorMsg());
    }

    return returnString;

    // override?
}

