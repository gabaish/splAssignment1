#include "../include/Volunteer.h"

DriverVolunteer::DriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep):
Volunteer(id,name),maxDistance(maxDistance),distancePerStep(distancePerStep),distanceLeft(0){
    volunteerType=VolunteerType::Driver;
    // I initialized distanceLeft (time left for the volunteer to finish its current order) to 0,
    // not sure it's important(i will override it) but just to make sure its ok
}

DriverVolunteer* DriverVolunteer:: clone() const {
    return new DriverVolunteer(*this);
} 

int DriverVolunteer:: getDistanceLeft() const{
    return this->distanceLeft;
}

int DriverVolunteer:: getMaxDistance() const{
    return this->maxDistance;
}

int DriverVolunteer:: getDistancePerStep() const{
    return this->distancePerStep;
}

bool DriverVolunteer:: decreaseDistanceLeft(){
    if(this->distanceLeft<=this->distancePerStep){
        this->distanceLeft=0;
        return true;
    }
    else{
        this->distanceLeft-=this->distancePerStep;
        return false;
    }
}

bool DriverVolunteer:: hasOrdersLeft() const{
    return true;

    //no limit because its not a limited  
}

bool DriverVolunteer:: canTakeOrder(const Order& order) const {
    return(!isBusy() && order.getDistance()<=this->maxDistance);

}

void DriverVolunteer:: acceptOrder(const Order& order){
    this->activeOrderId=order.getId();
    this->distanceLeft=order.getDistance();
 
}


void DriverVolunteer:: step(){
    bool finishedCurrentOrder = decreaseDistanceLeft();
    if(finishedCurrentOrder){
        this->completedOrderId=this->activeOrderId;
        this->activeOrderId=NO_ORDER;
    }
    // I changed the activeOrderId back to NO_ORDER, should have I?  
}


string DriverVolunteer:: toString() const{
    string driverVolunteerStatus= "TimeLeft: " +std::to_string(this->getDistanceLeft())+ "\n"
                                    "OrdersLeft: No Limit \n";
    return driverVolunteerStatus;
}

DriverVolunteer:: ~DriverVolunteer() = default;
