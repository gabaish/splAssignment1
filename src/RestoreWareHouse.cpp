#include "../include/Action.h"
#include <iostream>

extern WareHouse* backup;

RestoreWareHouse:: RestoreWareHouse(){};

void RestoreWareHouse:: act(WareHouse &wareHouse){
    //verifying warehouse backup exists:
    if(backup != nullptr){
        wareHouse= *backup;

        this->complete();
    }

    else{
        cout << "No backup available" << endl;
        this->error("No backup available");
    }

    wareHouse.addAction(this);
}

RestoreWareHouse* RestoreWareHouse:: clone() const{
    return new RestoreWareHouse(*this);
}

string RestoreWareHouse:: toString() const{
    string returnString = "backup";
    returnString.append(" ");
    returnString.append(this->getStatusString());
    if(this->getStatus() ==  ActionStatus::ERROR){
        returnString.append(" ");
        returnString.append(this->getErrorMsg());
    }
    return returnString;
}
