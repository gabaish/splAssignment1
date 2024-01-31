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
        this->error("No backup available");
        cout << "Error: " << this->getErrorMsg() << endl;

    }

    wareHouse.addAction(this);
}

RestoreWareHouse* RestoreWareHouse:: clone() const{
    return new RestoreWareHouse(*this);
}

string RestoreWareHouse:: toString() const{
    string returnString = "restore";
    returnString.append(" ");
    returnString.append(this->getStatusString());
    
    return returnString;
}

RestoreWareHouse:: ~RestoreWareHouse() = default;
