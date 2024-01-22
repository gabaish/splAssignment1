#include "../include/Volunteer.h"

LimitedCollectorVolunteer:: LimitedCollectorVolunteer(int id, const string &name, int coolDown ,int maxOrders):
CollectorVolunteer(id,name,coolDown),maxOrders(maxOrders),ordersLeft(maxOrders){
    volunteerType=VolunteerType::LimitedCollector;
    //orders left is initialsized to maxorders and I am planning to 
    //decrease it by one for any order made
}

LimitedCollectorVolunteer* LimitedCollectorVolunteer:: clone() const {
    return new LimitedCollectorVolunteer(*this);
} 

bool LimitedCollectorVolunteer:: hasOrdersLeft() const{
    return (this->ordersLeft>0);
}

bool LimitedCollectorVolunteer:: canTakeOrder(const Order& order) const{
    return(hasOrdersLeft() && !isBusy());
}

void LimitedCollectorVolunteer:: acceptOrder(const Order& order){
    this->CollectorVolunteer::acceptOrder(order);
    // is it ok to use this method here? just to prevent double coding
    this->ordersLeft-=1;
    // I'm counting on the fact that we only get here after using hasOrdersLeft()

}

int LimitedCollectorVolunteer:: getMaxOrders() const{
    return this->maxOrders;
}

int LimitedCollectorVolunteer:: getNumOrdersLeft() const{
    return this->ordersLeft;
}

string CollectorVolunteer:: toString() const{

    //implement once I know what to print
}