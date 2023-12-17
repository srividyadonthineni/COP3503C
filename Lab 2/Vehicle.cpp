#include "Vehicle.h"
#include <iostream>
#include <string>
using namespace std;

// Defining default constructor
Vehicle::Vehicle(){
  make = "COP3503";
  model = "Rust Bucket";
  year = 1900;
  price = 0;
  mileage = 0;
}

// Defining parameterized constructor
Vehicle::Vehicle(string make, string model, int year, float price, int mileage){
  this->make = make;
  this->model = model;
  this->year = year;
  this->price = price;
  this->mileage = mileage;
}

// Defining getter function GetYearMakeModel
string Vehicle::GetYearMakeModel(){
  string syear = to_string(year);
  return syear + " " + make + " " + model;
}

// Defining getter function GetPrice
float Vehicle::GetPrice(){
  return this->price;
}

// A void function to display
void Vehicle::Display(){
  cout << this->year << " " << this->make << " " << this->model << " $" << this->price << " " << this->mileage << endl;
}
