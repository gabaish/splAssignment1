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
    if(this->CollectorVolunteer::canTakeOrder(order))
        return hasOrdersLeft();
    else
        return false;
}

void LimitedCollectorVolunteer:: acceptOrder(const Order& order){
    this->CollectorVolunteer::acceptOrder(order);
    this->ordersLeft-=1;
    // I'm counting on the fact that we only get here after using hasOrdersLeft()

}

int LimitedCollectorVolunteer:: getMaxOrders() const{
    return this->maxOrders;
}

int LimitedCollectorVolunteer:: getNumOrdersLeft() const{
    return this->ordersLeft;
}

string LimitedCollectorVolunteer:: toString() const{
    string timeLeft=std::to_string(this->getTimeLeft());
    if(timeLeft=="0"){
        timeLeft="None";
    }
    string limitedCollectorVolunteerStatus= "TimeLeft: " +timeLeft+ "\n"
                                    "OrdersLeft: "+std::to_string(this->getNumOrdersLeft());
    return limitedCollectorVolunteerStatus;
}

LimitedCollectorVolunteer:: ~LimitedCollectorVolunteer() = default;