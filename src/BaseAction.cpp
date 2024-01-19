#include "../include/BaseAction.h"

BaseAction::BaseAction():
errorMsg(""),status(ActionStatus::COMPLETED){
 //what should i initialize it with???????/
 //
 //

 /// pay attention
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