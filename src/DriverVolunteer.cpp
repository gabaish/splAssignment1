#include "../include/Volunteer.h"

DriverVolunteer::DriverVolunteer(int id, string name, int maxDistance, int distancePerStep):
Volunteer(id,name),maxDistance(maxDistance),distancePerStep(distancePerStep),distanceLeft(0){
    // I initialized distanceLeft (time left for the volunteer to finish its current order) to 0,
    // not sure it's important(i will override it) but just to make sure its ok
}

DriverVolunteer* DriverVolunteer:: clone() const {
    return new DriverVolunteer(*this);

// shoud this be implemented with new? who deletes it? 
// also - I do not have a copy constructor, is the default enoug
// should I have override keyword in the signature? 
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
        //is this syntax ok? 
    }
}

bool DriverVolunteer:: hasOrdersLeft() const{
    return true;

    //no limit because its not a limited 
    //override? 
}

bool DriverVolunteer:: canTakeOrder(const Order& order) const {
    return(!isBusy() && order.getDistance()<=this->maxDistance);

    //override? 
}

void DriverVolunteer:: acceptOrder(const Order& order){
    this->activeOrderId=order.getId();
    this->distanceLeft=order.getDistance();

    //override? 
}


void DriverVolunteer:: step(){
    bool finishedCurrentOrder = decreaseDistanceLeft();
    if(finishedCurrentOrder){
        this->completedOrderId=this->activeOrderId;
        this->activeOrderId=NO_ORDER;
    }
    // I changed the activeOrderId back to NO_ORDER, should have I?  
    //override?
}


string DriverVolunteer:: toString() const{

    //implement once I know what to print
    //override? 
}
