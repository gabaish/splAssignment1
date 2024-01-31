#include "../include/Action.h"
#include <iostream>

PrintVolunteerStatus::PrintVolunteerStatus(int id) : volunteerId(id){}

void PrintVolunteerStatus::act(WareHouse &wareHouse){
    Volunteer& current_volunteer=wareHouse.getVolunteer(volunteerId);

    //if volunteer Id exsit:
    if(current_volunteer.getId()!=-1){
        cout << "VolunteerID: " << volunteerId << endl;
        cout << "isBusy: " << (current_volunteer.isBusy() ? "True" : "False") << endl;
        //getActiveOrderID returns NO_ORDER, but they want none, TOCHECK
        string orderId=std::to_string(current_volunteer.getActiveOrderId());
        if(orderId=="-1"){
            orderId="None";
        }
        cout << "OrderID: " << orderId << endl;
        //VolunteerType type=current_volunteer.getVolunteerType();

        //also test this instead of the switch():
        string volunteerTypeToString=current_volunteer.toString();
        cout << volunteerTypeToString << endl;

        this->complete();
    }
    else{
        this->error("Volunteer doesn't exist");
        cout << "Error: " << this->getErrorMsg() << endl;
    }

    wareHouse.addAction(this);
}

PrintVolunteerStatus* PrintVolunteerStatus::clone() const{
    return new PrintVolunteerStatus(*this);
}

string PrintVolunteerStatus:: toString() const{
    string returnString = "volunteerStatus ";
    returnString.append(std::to_string(this->volunteerId));
    returnString.append(" ");
    returnString.append(this->getStatusString());

    return returnString;

}

PrintVolunteerStatus:: ~PrintVolunteerStatus() = default;