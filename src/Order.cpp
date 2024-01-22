#include "../include/Order.h"

Order::Order(int id, int customerId, int distance):
id(id),customerId(customerId),distance(distance),status(OrderStatus::PENDING),collectorId(NO_VOLUNTEER),driverId(NO_VOLUNTEER)
{}

int Order::getId() const{
    return this->id;
}

int Order::getCustomerId() const{
    return this->customerId;
} 

void Order:: setStatus(OrderStatus status){
    this->status=status;
    //hopeully this syntax is a valid one 
}

void Order:: setCollectorId(int collectorId){
    this->collectorId= collectorId;
    //hopeully this syntax is a valid one 

}

void Order:: setDriverId(int driverId){
    this->driverId= driverId;
    //hopeully this syntax is a valid one 

}

int Order::getCollectorId() const{
    return this->collectorId;
} 

int Order::getDriverId() const{
    return this->driverId;
} 

OrderStatus Order::getStatus() const{
    return this->status;
}

// used for action Close()
const string Order:: toString() const{
    string returnString = "OrderID: ";
    returnString.append(std::to_string(this->id));
    returnString.append(" , CustomerID: ");
    returnString.append(std::to_string(this->customerId));
    returnString.append(" , OrderStatus: ");
    returnString.append(this->getStatusString());

    return returnString;
}

int Order::getDistance() const{
    return this->distance;
}

string Order:: getStatusString() const {
    string returnString = "";
    switch(this->status){
        case(OrderStatus::PENDING):
            return "PENDING";    
        case(OrderStatus::COLLECTING):
            return "COLLECTING"; 
        case(OrderStatus::DELIVERING):
            return "DELIVERING";    
        case(OrderStatus::COMPLETED):
            return "COMPLETED"; 
    }
    

}

Order* Order:: clone() const {
    return new Order(*this);

// shoud this be implemented with new? who deletes it? 
// also - I do not have a copy constructor, is the default enoug
// should I have override keyword in the signature? 
} 