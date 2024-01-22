#include "../include/Action.h"
#include <iostream>

PrintVolunteerStatus::PrintVolunteerStatus(int id) : volunteerId(id){}

void PrintVolunteerStatus::act(WareHouse &wareHouse){
    Volunteer& current_volunteer=wareHouse.getVolunteer(volunteerId);

    //if volunteer Id exsit:
    if(current_volunteer.getId()!=-1){
        cout << "VolunteerID: " << volunteerId << endl;
        cout << "isBusy: " << current_volunteer.isBusy() << endl;
        //getActiveOrderID returns NO_ORDER, but they want none, TOCHECK
        cout << "OrderID: " << current_volunteer.getActiveOrderId() << endl;
        VolunteerType type=current_volunteer.getVolunteerType();

        //also test this instead of the switch():
        //current_volunteer.toString();


        switch(type){
            case VolunteerType::Volunteer: {
                current_volunteer.toString();
                //when testing, check if we need this, or we can count on the polymorphism like above
                //CollectorVolunteer *collectorVolunteer = dynamic_cast<CollectorVolunteer*>(&current_volunteer);
                //collectorVolunteer->toString();
            }
            case VolunteerType::Collector: {
                current_volunteer.toString();
                //when testing, check if we need this, or we can count on the polymorphism like above
                //CollectorVolunteer *collectorVolunteer = dynamic_cast<CollectorVolunteer*>(&current_volunteer);
                //collectorVolunteer->toString();
            }
            case VolunteerType::LimitedCollector: {
                current_volunteer.toString();

                /*LimitedCollectorVolunteer *limitedCollectorVolunteer = dynamic_cast<LimitedCollectorVolunteer*>(&current_volunteer);
                cout << "TimeLeft: " << limitedCollectorVolunteer->getTimeLeft() << endl;
                cout << "OrdersLeft: " << limitedCollectorVolunteer->getNumOrdersLeft() << endl;*/
            }
            case VolunteerType::Driver: {
                current_volunteer.toString();
                /*DriverVolunteer *driverVolunteer = dynamic_cast<DriverVolunteer*>(&current_volunteer);
                cout << "TimeLeft: " << driverVolunteer->getDistanceLeft() << endl;
                cout << "OrdersLeft: No Limit" << endl;*/
            }
            case VolunteerType::LimitedDriver: {
                current_volunteer.toString();
                /*LimitedDriverVolunteer *limitedDriverVolunteer = dynamic_cast<LimitedDriverVolunteer*>(&current_volunteer);
                cout << "TimeLeft: " << limitedDriverVolunteer->getDistanceLeft() << endl;
                cout << "OrdersLeft: " << limitedDriverVolunteer->getNumOrdersLeft() <<endl;*/
            }
        }

        this->complete();
    }
    else{
        this->error("Volunteer doesn't exist");
        cout << this->getErrorMsg() << endl;
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
    if(this->getStatus() ==  ActionStatus::ERROR){
        returnString.append(" ");
        returnString.append(this->getErrorMsg());
    }

    return returnString;

}

PrintVolunteerStatus:: ~PrintVolunteerStatus() = default;