#include "../include/Action.h"


Close::Close(){}

void Close:: act(WareHouse &wareHouse){
    wareHouse.close();
    
    this->complete();
    wareHouse.addAction(this);

    //free memory - Implemented when going out of the loop of start

}

string Close:: toString() const{
    string returnString = "close ";
    returnString.append(this->getStatusString());

    return returnString;

}

Close* Close:: clone() const{
    return new Close(*this);
}

Close:: ~Close() = default;
