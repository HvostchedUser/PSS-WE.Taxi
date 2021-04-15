#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "utils.cpp"
using namespace std;
class Passenger{
public:
    string name;
    double rating;
    vector<Route> orderHistory;
    vector<Card> paymentMethods;
    vector<string> pinnedAddresses;
};
class Driver{
public:
    string name;
    double rating;
    vector<Route> orderHistory;
    vector<Route> available;
    Car car;
    string status;
};
class PassengerGateway{
public:
    vector<Card> paymentMethods;
    int psid;
};
class DriverGateway{
public:
    vector<Route> toAccept;
    int drid=-1;
};
