#include "../include/Customer.h"


SoldierCustomer::SoldierCustomer(int id, string name, int locationDistance, int maxOrders)
: Customer(id, name, locationDistance, maxOrders){}

SoldierCustomer* SoldierCustomer:: clone() const{
    return new SoldierCustomer(*this);

    // shoud this be implemented with new? who deletes it? 
    // also - I do not have a copy constructor, is the default enough? 
    // I had errors while using override keywords, so i removed it.. not sure if I was supposed to
}