#include "../include/Action.h"

AddOrder::AddOrder(int id):
customerId(id){}

void AddOrder:: act(WareHouse &wareHouse){
    // checking if the customerId is in the correct range 
    if(customerId>=0 && customerId<=wareHouse.getCustomerCounter()){
        Customer& customer = wareHouse.getCustomer(customerId);
        Order* order = new Order(wareHouse.getOrderCounter(),customerId,customer.getCustomerDistance());
        wareHouse.addOrder(order);
        customer.addOrder(order->getId());
        this->complete();
    } 
    // if this customer ID does not exist in the warehouse - return an error
    else {
        this->error("Cannot place this order");
    }
    wareHouse.addAction(this);

    // override?
}


AddOrder* AddOrder:: clone() const{
    return new AddOrder(*this);

    // is this the way? 
    // override? 
}

std::string AddOrder:: toString() const{
    string returnString = "order ";
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
