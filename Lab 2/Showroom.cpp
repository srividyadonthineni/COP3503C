#include "Showroom.h"
#include <iostream>
#include <string>
#include <vector>
#include "Vehicle.h"
using namespace std;

// Defining default constructor
Showroom::Showroom(){
  name = "Unnamed Showroom";
  capacity = 0;
}

// Defining parameterized constructor
Showroom::Showroom(string name, unsigned int capacity){
  this->name = name;
  this->capacity = capacity;
}

// Accessor 
vector<Vehicle> Showroom::GetVehicleList(){
  return vehicles;
}

// Function which adds a vehicle object to the showroom when there is space
void Showroom::AddVehicle(Vehicle car){
  if(vehicles.size() == this->capacity){
    cout << "Showroom is full! Cannot add " << car.GetYearMakeModel() << endl;
  }
  else{
    vehicles.push_back(car);
  }
}

// Function which prints out all of the vehicle objects in a showroom
void Showroom::ShowInventory(){
  if(vehicles.size() > 0){
    cout << "Vehicles in " << this->name << endl;
    for(int i = 0; i < vehicles.size(); i++){
      vehicles[i].Display();
    }
  }
  else{
    cout << this->name << " is empty!" << endl;
  }
  
}

// Function that collects the total price of all vehicles in the showroom
float Showroom::GetInventoryValue(){
  float value = 0.0;
  for(int i = 0; i < vehicles.size(); i++){
    value += vehicles[i].GetPrice();
  }
  return value;
}
