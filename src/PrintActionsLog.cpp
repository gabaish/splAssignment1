#include "../include/Action.h"
#include <iostream>

PrintActionsLog::PrintActionsLog(){}

void PrintActionsLog:: act(WareHouse &wareHouse){
    for(BaseAction* action: wareHouse.getActions()){
        cout << action->toString() << endl;
    }

    this->complete();
    wareHouse.addAction(this);

}

PrintActionsLog* PrintActionsLog:: clone() const{
    return new PrintActionsLog(*this);
}

std::string PrintActionsLog:: toString() const{
    string returnString = "log ";
    returnString.append(this->getStatusString());
    if(this->getStatus() ==  ActionStatus::ERROR){
        returnString.append(" ");
        returnString.append(this->getErrorMsg());
    }

    return returnString;

}

PrintActionsLog:: ~PrintActionsLog() = default;