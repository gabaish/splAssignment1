#include "../include/Volunteer.h"

Volunteer::Volunteer(int id, const string &name):
id(id),name(name),completedOrderId(NO_ORDER),activeOrderId(NO_ORDER){}
// In constructors I couldn't use this-> (vsCode didnt like it) so it's in this type
// of syntax for now

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

bool Volunteer::isBusy() const{
    return(!this->activeOrderId==NO_ORDER);
    // if the activeOrderId is NO_ORDER - the volunteer is not busy
}
