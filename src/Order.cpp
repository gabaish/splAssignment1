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

const string Order:: toString() const{
    // will implement once I understand what we should print
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


// enum class OrderStatus {
//     PENDING,
//     COLLECTING,
//     DELIVERING,
//     COMPLETED,
// };
