#include "../include/Volunteer.h"

Volunteer::Volunteer(int id, const string &name):
completedOrderId(NO_ORDER),activeOrderId(NO_ORDER),volunteerType(VolunteerType::Volunteer),id(id),name(name){}

int Volunteer::getId() const{
    return this->id;
}

const string& Volunteer:: getName() const{
    return this->name;
}

int Volunteer::getActiveOrderId() const {
    return this->activeOrderId;
}

int Volunteer::getCompletedOrderId() const{
    return this->completedOrderId;
}

void Volunteer::setCompletedOrderId(int completedOrderId){
    this->completedOrderId = completedOrderId;
}

bool Volunteer::isBusy() const{
    return!(this->activeOrderId==NO_ORDER);
    // if the activeOrderId is NO_ORDER - the volunteer is not busy
}

VolunteerType Volunteer::getVolunteerType() const{
    return this->volunteerType;
}

Volunteer:: ~Volunteer() = default;