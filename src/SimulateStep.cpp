#include "../include/Action.h"

SimulateStep::SimulateStep(int numOfSteps):
numOfSteps(numOfSteps){}

void SimulateStep::act(WareHouse& warehouse) {
    for (int i = 0; i < this->numOfSteps; ++i) {
        // schema steps happen in the warehouse in order not 
        // to have getters for entire vectors

        warehouse.firstSchemastep();
        warehouse.secondAndThirdSchemaStep();
        warehouse.fourthSchemaStep();
  
    }
    this->complete();
    warehouse.addAction(this);

}

std::string SimulateStep:: toString() const{
    string returnString = "simulateStep ";
    returnString.append(std::to_string(this->numOfSteps));
    returnString.append(" ");
    returnString.append(this->getStatusString());

    return returnString;

}

SimulateStep* SimulateStep:: clone() const{
    return new SimulateStep(*this);

}

SimulateStep:: ~SimulateStep() = default;