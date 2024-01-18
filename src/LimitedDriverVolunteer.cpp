#include "../include/Volunteer.h"

LimitedDriverVolunteer::LimitedDriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep,int maxOrders):
DriverVolunteer(id,name,maxDistance,distancePerStep),maxOrders(maxOrders),ordersLeft(maxOrders){
    //orders left is initialsized to maxorders and I am planning to 
    //decrease it by one for any order made
}

LimitedDriverVolunteer* LimitedDriverVolunteer:: clone() const {
    return new LimitedDriverVolunteer(*this);

    // shoud this be implemented with new? who deletes it? 
    // also - I do not have a copy constructor, is the default enoug
    // should I have override keyword in the signature? 
} 

int LimitedDriverVolunteer:: getMaxOrders() const{
    return this->maxOrders;
}

int LimitedDriverVolunteer:: getNumOrdersLeft() const{
    return this->ordersLeft;
}

bool LimitedDriverVolunteer:: hasOrdersLeft() const{
    return (this->ordersLeft>0);

    //override?
}

bool LimitedDriverVolunteer:: canTakeOrder(const Order& order) const{
    return(!isBusy&&hasOrdersLeft()&&(order.getDistance()<this->getMaxDistance()));

    //override?
}

void LimitedDriverVolunteer:: acceptOrder(const Order& order){
    this->DriverVolunteer::acceptOrder(order);
    // is it ok to use this method here? just to prevent double coding
    this->ordersLeft-=1;
    // I'm counting on the fact that we only get here after using hasOrdersLeft()

    //override?
}

string LimitedDriverVolunteer:: toString() const{

    //implement once I know what to print
    //override? 
}