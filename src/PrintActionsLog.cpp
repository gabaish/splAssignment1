#include "../include/BaseAction.h"
#include <iostream>

PrintActionsLog::PrintActionsLog(){}

void PrintActionsLog:: act(WareHouse &wareHouse){
    for(BaseAction* action: wareHouse.getActionsLog()){
        cout << action->toString() << endl;
    }

    this->complete();
    wareHouse.addAction(this);

}

PrintActionsLog* PrintActionsLog:: clone() const{
    return new PrintActionsLog(*this);

    // is this the way? 
    // override? 
}

std::string PrintActionsLog:: toString() const{
    string returnString = "log ";
    returnString.append(this->getStatusString());
    if(this->getStatus() ==  ActionStatus::ERROR){
        returnString.append(" ");
        returnString.append(this->getErrorMsg());
    }

    return returnString;

    // override?
}