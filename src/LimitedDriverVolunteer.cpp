#include "../include/Volunteer.h"

LimitedDriverVolunteer::LimitedDriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep,int maxOrders):
DriverVolunteer(id,name,maxDistance,distancePerStep),maxOrders(maxOrders),ordersLeft(maxOrders){
    volunteerType=VolunteerType::LimitedDriver;
    //orders left is initialsized to maxorders and I am planning to 
    //decrease it by one for any order made
}

LimitedDriverVolunteer* LimitedDriverVolunteer:: clone() const {
    return new LimitedDriverVolunteer(*this); 
} 

int LimitedDriverVolunteer:: getMaxOrders() const{
    return this->maxOrders;
}

int LimitedDriverVolunteer:: getNumOrdersLeft() const{
    return this->ordersLeft;
}

bool LimitedDriverVolunteer:: hasOrdersLeft() const{
    return (this->ordersLeft>0);
}

bool LimitedDriverVolunteer:: canTakeOrder(const Order& order) const{
    if(this->DriverVolunteer::canTakeOrder(order))
        return hasOrdersLeft();
    else
        return false;
}

void LimitedDriverVolunteer:: acceptOrder(const Order& order){
    this->DriverVolunteer::acceptOrder(order);
    // is it ok to use this method here? just to prevent double coding
    this->ordersLeft-=1;
    // I'm counting on the fact that we only get here after using hasOrdersLeft()
}

string LimitedDriverVolunteer:: toString() const{
    string timeLeft=std::to_string(this->getDistanceLeft());
    if(timeLeft=="0"){
        timeLeft="None";
    }
    string limitedDriverVolunteerStatus= "TimeLeft: " +timeLeft+ "\n" 
                                "OrdersLeft: "+std::to_string(this->getNumOrdersLeft());
    return limitedDriverVolunteerStatus;
}

LimitedDriverVolunteer:: ~LimitedDriverVolunteer() = default;