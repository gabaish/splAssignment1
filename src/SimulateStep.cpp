#include "../include/BaseAction.h"

SimulateStep::SimulateStep(int numOfSteps):
numOfSteps(numOfSteps){}

void SimulateStep::act(WareHouse& warehouse) {
    for (int i = 0; i < this->numOfSteps; ++i) {
        //first step in the schema - move orders from pendingOrders to relevant volunteer
        for(const Order* order : warehouse.getPendingOrders()){
            if(order->getStatus()==OrderStatus::PENDING){
                // looking for an available collector
                for(Volunteer* volunteer : warehouse.getVolunteers()) {
                    if(volunteer->getType()== VolunteerType::Collector && volunteer->canTakeOrder(*order)){
                        volunteer->acceptOrder(*order);
                        warehouse.removePendingOrder(*order);
                        warehouse.addInProcessOrder(*order);
                        break;
                    }
                }       
            } else if (order->getStatus()==OrderStatus::COLLECTING){
                // looking for an available driver
                for(Volunteer* volunteer : warehouse.getVolunteers()){
                    if(volunteer->getType()== VolunteerType::Driver && volunteer->canTakeOrder(*order)){
                        volunteer->acceptOrder(*order);
                        warehouse.removePendingOrder(*order);
                        warehouse.addInProcessOrder(*order);
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
                    if(volunteer->getType()==VolunteerType::Collector){
                        Order orderToAdd = warehouse.getOrder(volunteer->getCompletedOrderId());
                        warehouse.removeInProcessOrder(orderToAdd);
                        warehouse.addPendingOrder(orderToAdd);
                    }
                    // drivers should push their order to completedOrders
                    if(volunteer->getType()==VolunteerType::Driver){
                        Order orderToAdd = warehouse.getOrder(volunteer->getCompletedOrderId());
                        warehouse.removeInProcessOrder(orderToAdd);
                        warehouse.addCompletedOrder(orderToAdd);
                    }
                }
            }
        }

        // fourth step in the schema - delete volunteers that had maxed out and finished their last order
        for(Volunteer* volunteer : warehouse.getVolunteers()){
            if(!(volunteer->hasOrdersLeft()) && volunteer->getActiveOrderId()==NO_ORDER){
                Volunteer* currentVolunteer = volunteer;
                warehouse.removeVolunteer(*volunteer);

                delete currentVolunteer;

                //should have I made this copy currentVolunteer ?
                //it this how we delete memory in c++ ? 

            }

        }
  
    }

    //override? 
}

std::string SimulateStep:: toString() const{
    //implement once it's more clear what we want to print 

    // override?
}

SimulateStep* SimulateStep:: clone() const{
    return new SimulateStep(*this);

    // is this the way? 
    // override? 
}