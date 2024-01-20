#include "../include/BaseAction.h"
#include <iostream>

PrintVolunteerStatus::PrintVolunteerStatus(int id) : VolunteerId(id){}

void PrintVolunteerStatus::act(WareHouse &wareHouse){
    Volunteer& current_volunteer=wareHouse.getVolunteer(VolunteerId);

    cout << "VolunteerID: " << VolunteerId << endl;
    cout << "isBusy: " << current_volunteer.isBusy() << endl;
    //getActiveOrderID returns NO_ORDER, but they want none, TOCHECK
    cout << "OrderID: " << current_volunteer.getActiveOrderId() << endl;
    //if()
    //cout << "TimeLeft: " <<


}