#pragma once
#include <string>
#include <vector>
using namespace std;

#include "Order.h"
#include "Customer.h"
#include "Volunteer.h"
#include "Action.h"

class BaseAction;
class Volunteer;

// Warehouse responsible for Volunteers, Customers Actions, and Orders.


class WareHouse {

    public:
        WareHouse(const string &configFilePath);
        void start();
        const vector<BaseAction*> &getActions() const;
        void addOrder(Order* order);
        void addAction(BaseAction* action);
        Customer &getCustomer(int customerId) const;
        Volunteer &getVolunteer(int volunteerId) const;
        Order &getOrder(int orderId) const;
        void close();
        void open();
        void addCustomer(Customer* customer);
        void addVolunteer(string volunteer_name, string volunteerRole, istringstream iss);
        void moveOrderFromPendingToInProcess(Order* order);
        void moveOrderFromInProcessToPending(Order* order);
        void moveOrderFromInProcessToCompleted(Order* order);
        void removeVolunteer(Volunteer* volunteer);
        int getCustomerCounter() const;
        int getVolunteerCounter() const;
        int getOrderCounter() const;
        void firstSchemastep();
        void secondAndThirdSchemaStep();
        void fourthSchemaStep();
        ~WareHouse();
        WareHouse(const WareHouse &other);
        WareHouse &operator=(const WareHouse &other);
        WareHouse(WareHouse &&other) noexcept;
        WareHouse &operator=(WareHouse &&other) noexcept;
        void addCustomerConfig(string customerName, string customerType, int distance, int maxOrders);



    private:
        bool isOpen;
        vector<BaseAction*> actionsLog;
        vector<Volunteer*> volunteers;
        vector<Order*> pendingOrders;
        vector<Order*> inProcessOrders;
        vector<Order*> completedOrders;
        vector<Customer*> customers;
        int customerCounter; //For assigning unique customer IDs
        int volunteerCounter; //For assigning unique volunteer IDs
        int orderCounter;
};