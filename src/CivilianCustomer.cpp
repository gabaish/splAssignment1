#include "../include/Customer.h"


CivilianCustomer::CivilianCustomer(int id, const string &name, int locationDistance, int maxOrders)
: Customer(id, name, locationDistance, maxOrders){}

CivilianCustomer* CivilianCustomer:: clone() const{
    return new CivilianCustomer(*this);

    // shoud this be implemented with new? who deletes it? 
    // also - I do not have a copy constructor, is the default enough? 
    // I had errors while using override keywords, so i removed it.. not sure if I was supposed to
}