#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
using namespace std;

class Vehicle {
  private:
    string make;
    string model;
    unsigned int year;
    float price;
    unsigned int mileage;
  public:
    Vehicle();
    Vehicle(string make, string model, int year, float price, int mileage);
    string GetYearMakeModel();
    float GetPrice();
    void Display();
};

#endif
