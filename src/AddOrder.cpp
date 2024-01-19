#include "../include/BaseAction.h"

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
    //implement once it's more clear what we want to print 

    // override?
}
