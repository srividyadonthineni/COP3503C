#include <vector>
#include "Vehicle.h"
#include "Showroom.h"
#include <iostream>
using namespace std;

class Dealership {
  private:
    string name;
    unsigned int capacity;
    vector <Showroom> showrooms;
  public:
    Dealership();
    Dealership(string name, unsigned int capacity);
    void AddShowroom(Showroom s);
    float GetAveragePrice();
    void ShowInventory();
};
