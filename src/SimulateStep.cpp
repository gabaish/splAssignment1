#include "../include/Action.h"

SimulateStep::SimulateStep(int numOfSteps):
numOfSteps(numOfSteps){}

void SimulateStep::act(WareHouse& warehouse) {
    for (int i = 0; i < this->numOfSteps; ++i) {
        //first step in the schema - move orders from pendingOrders to relevant volunteers
        for(Order* order : warehouse.getPendingOrders()){
            if(order->getStatus()==OrderStatus::PENDING){
                // looking for an available collector
                for(Volunteer* volunteer : warehouse.getVolunteers()) {
                    if(volunteer->getVolunteerType()== VolunteerType::Collector && volunteer->canTakeOrder(*order)){
                        volunteer->acceptOrder(*order);
                        warehouse.moveOrderFromPendingToInProcess(order);
                        break;
                    }
                }       
            } else if (order->getStatus()==OrderStatus::COLLECTING){
                // looking for an available driver
                for(Volunteer* volunteer : warehouse.getVolunteers()){
                    if(volunteer->getVolunteerType()== VolunteerType::Driver && volunteer->canTakeOrder(*order)){
                        volunteer->acceptOrder(*order);
                        warehouse.moveOrderFromPendingToInProcess(order);
                        break;
                    }
                }
            }

        }

        // second step in the schema - perform a step in the simulation
        // third step in the schema - once performing a step - check if they are done processing
        for(Volunteer* volunteer : warehouse.getVolunteers()){
            // if the volunteer is curentlly working on something - we should simulate a step
            if(volunteer->getActiveOrderId()!=NO_ORDER)
            {
                volunteer->step();
                // if after the step the volunteer is done processing - the activeOrderId shold be NO_ORDER
                if(volunteer->getActiveOrderId()==NO_ORDER){
                    // collectors should push their order to pendingOrders
                    if(volunteer->getVolunteerType()==VolunteerType::Collector){
                        Order orderToAdd = warehouse.getOrder(volunteer->getCompletedOrderId());
                        // type &orderToAdd - not sure about it memory-wise
                        warehouse.moveOrderFromInProcessToPending(&orderToAdd);
                    }
                    // drivers should push their order to completedOrders
                    if(volunteer->getVolunteerType()==VolunteerType::Driver){
                        Order orderToAdd = warehouse.getOrder(volunteer->getCompletedOrderId());
                        // type &orderToAdd - not sure about it memory-wise
                        warehouse.moveOrderFromInProcessToCompleted(&orderToAdd);
                    }
                }
            }
        }

        // fourth step in the schema - delete volunteers that had maxed out and finished their last order
        for(Volunteer* volunteer : warehouse.getVolunteers()){
            if(!(volunteer->hasOrdersLeft()) && volunteer->getActiveOrderId()==NO_ORDER){
                warehouse.removeVolunteer(volunteer);

                delete volunteer;

                //it this how we delete memory in c++ ? 

            }

        }
  
    }
    this->complete();
    warehouse.addAction(this);

    //override? 
}

std::string SimulateStep:: toString() const{
    string returnString = "step ";
    returnString.append(std::to_string(this->numOfSteps));
    returnString.append(" ");
    returnString.append(this->getStatusString());
    if(this->getStatus() ==  ActionStatus::ERROR){
        returnString.append(" ");
        returnString.append(this->getErrorMsg());
    }

    return returnString;

    // override?
}

SimulateStep* SimulateStep:: clone() const{
    return new SimulateStep(*this);

    // is this the way? 
    // override? 
}