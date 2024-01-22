#include "../include/Customer.h"

Customer::Customer(int id, const string &name, int locationDistance, int maxOrders): 
id(id),name(name), locationDistance(locationDistance), maxOrders(maxOrders) {
    //vector should init itself I guess 
}

const string &Customer::getName() const {
    return this->name;
}

int Customer::getId() const{
    return this->id;
}

int Customer::getCustomerDistance() const{
    return this->locationDistance;
}

int Customer:: getMaxOrders() const{
    return this->maxOrders;
}

int Customer:: getNumOrders() const{
    return this->ordersId.size();
}

bool Customer:: canMakeOrder() const{
    return(this->ordersId.size()<this->maxOrders);
}

const vector<int>& Customer:: getOrdersIds() const{
    return this->ordersId;
}

int Customer:: addOrder(int orderId){
    ordersId.push_back(orderId);
    return orderId;
    // in the comments they said return orderId only if the adding worked, 
    // but in what situation should it not work..? 
}