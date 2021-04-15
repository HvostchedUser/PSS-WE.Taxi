#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Card{
public:
    double money;
};
class Route{
public:
    string passenger;
    string origin;
    string destination;
    double distance=0;
    double position=0;
};
class Car{
public:
    string model;
    Route coordinates;
    string type;//There are 4 car types: Economy, Comfort, ComfortPlus, Business.
    
};
