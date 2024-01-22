#include "../include/Action.h"

extern WareHouse* backup;

BackupWareHouse:: BackupWareHouse(){};

void BackupWareHouse:: act(WareHouse &wareHouse){
    //Delete the previous backup, if exists:
    if(backup != nullptr){
        delete backup;
        backup=nullptr;
    }

    //copying the current warehouse:
    backup=new WareHouse(wareHouse);   

    this->complete();
    wareHouse.addAction(this);
}

BackupWareHouse* BackupWareHouse:: clone() const{
    return new BackupWareHouse(*this);
}

string BackupWareHouse:: toString() const{
    string returnString = "backup";
    returnString.append(" ");
    returnString.append(this->getStatusString());

    return returnString;
}

