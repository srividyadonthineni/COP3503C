#include "Showroom.h"
#include "Vehicle.h"
#include "Dealership.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;


// Defining default constructor
Dealership::Dealership(){
  name = "Generic Dealership";
  capacity = 0;
}

// Defining parameterized constructor
Dealership::Dealership(string name, unsigned int capacity){
  this->name = name;
  this->capacity = capacity;
}

// Function which adds a showroom object to the dealership when it is not full
void Dealership::AddShowroom(Showroom s){
  if(showrooms.size() == this->capacity){
      cout << "Dealership is full, can't add another showroom!" << endl;
    }
  else{
    showrooms.push_back(s);
  }
}

// A function which returns the average price of all of the vehicles in all showrooms of a dealership
float Dealership::GetAveragePrice(){
  float sum = 0.0;
  int counter = 0;
  float average = 0.0;
  // For loop runs through the showroom vector to access each vehicle in each showroom and gets price
  for(int i = 0; i < showrooms.size(); i++){
    Showroom obj = showrooms[i];
    vector<Vehicle> cars = obj.GetVehicleList();
    for(int j = 0; j < cars.size(); j++){
        counter++;
        sum += cars[j].GetPrice();
    }
  }
  average = sum/counter;
  return average;
}

// A function which shows all showrooms in the dealership and then states the average price of each vehicle
void Dealership::ShowInventory(){
  if(showrooms.size() > 0){
    float sum = 0.0;
    int counter = 0;
    float average = 0.0;
    for(int i = 0; i < showrooms.size(); i++){
      showrooms[i].ShowInventory();
      cout << endl;
      sum += showrooms[i].GetInventoryValue();
      counter += showrooms[i].GetVehicleList().size();
    }
    average = sum/counter;
    cout << "Average car price: $" << average;
  }
  else{
    cout << this->name << " is empty!" << endl;
    cout << "Average car price: $0.00";
  }

  
}
