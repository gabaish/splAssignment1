#include "../include/Action.h"

BaseAction::BaseAction():
errorMsg(""),status(ActionStatus::COMPLETED){
}

ActionStatus BaseAction:: getStatus() const{
    return this->status;
}

void BaseAction::complete(){
    this->status=ActionStatus::COMPLETED;
}

void BaseAction::error(string errorMsg){
    this->status=ActionStatus::ERROR;
    this->errorMsg=errorMsg;
}

string BaseAction:: getErrorMsg() const{
    return this->errorMsg;
}

string BaseAction::getStatusString() const {
    switch (this->status) {
        case ActionStatus::COMPLETED: return "COMPLETED";
        case ActionStatus::ERROR: return "ERROR";
    }
    return "Unknown";
}