#ifndef SHOWROOM_H
#define SHOWROOM_H

#include <vector>
#include "Vehicle.h"
#include <iostream>
using namespace std;

class Showroom {
  private:
    string name;
    unsigned int capacity;
    vector <Vehicle> vehicles;
  public:
    Showroom();
    Showroom(string name, unsigned int capacity);
    vector<Vehicle> GetVehicleList();
    void AddVehicle(Vehicle car);
    void ShowInventory();
    void Display();
    float GetInventoryValue();
};

#endif
