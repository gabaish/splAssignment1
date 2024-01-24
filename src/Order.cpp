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
}

void Order:: setCollectorId(int collectorId){
    this->collectorId= collectorId;
}

void Order:: setDriverId(int driverId){
    this->driverId= driverId; 
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
        {
            returnString.append("PENDING");
            break;  
        } 
        case(OrderStatus::COLLECTING):
        {
            returnString.append("COLLECTING"); 
            break;
        }   
        case(OrderStatus::DELIVERING):
        {
             returnString.append("DELIVERING");  
             break;
        }
        case(OrderStatus::COMPLETED):
        {
            returnString.append("COMPLETED"); 
            break;
        }
    
    }
    return returnString;
}

Order* Order:: clone() const {
    return new Order(*this);
} 