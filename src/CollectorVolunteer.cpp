#include "../include/Volunteer.h"

CollectorVolunteer::CollectorVolunteer(int id, const string &name, int coolDown):
Volunteer(id,name),coolDown(coolDown),timeLeft(0){
    volunteerType=VolunteerType::Collector;
    // I initialized timeLeft (time left for the volunteer to finish its current order) to 0,
    // not sure it's important(i will override it) but just to make sure its ok
}

CollectorVolunteer* CollectorVolunteer:: clone() const {
    return new CollectorVolunteer(*this);
} 

void CollectorVolunteer:: step() {
    bool finishedCurrentOrder = decreaseCoolDown();
    if(finishedCurrentOrder)
    {
        this->completedOrderId=this->activeOrderId;
        this->activeOrderId=NO_ORDER;
    }
}

int CollectorVolunteer::getCoolDown() const{
    return this-> coolDown;
}

int CollectorVolunteer::getTimeLeft() const{
    return this->timeLeft;
}

bool CollectorVolunteer:: decreaseCoolDown(){
    this->timeLeft--;
    if(this->timeLeft==0)
        return true;
    else
        return false;

}

bool CollectorVolunteer:: hasOrdersLeft() const{
    return true;
    // true because it is not limited, so it is never false
}

bool CollectorVolunteer:: canTakeOrder(const Order &order) const{
    return !isBusy();

}

void CollectorVolunteer:: acceptOrder(const Order &order){
    this->activeOrderId= order.getId();
    this->timeLeft= this->coolDown;

}

string CollectorVolunteer:: toString() const{

    //implement once I know what to print
}

bool CollectorVolunteer:: hasOrdersLeft() const{
    return true;
    //there is no limit
} 