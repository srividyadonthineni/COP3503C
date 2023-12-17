#pragma once
#include <string>
#include <iostream>
using namespace std;

template<typename T>
class ABS {
  private:
    int capacity;
    int size;
    T* item;
    float scale_factor;
  public:
    ABS(){
      capacity = 1;
      size = 0;
      scale_factor = 2.0;
      item = new T[capacity];
    }
    ABS(int capacity){
      this->capacity = capacity;
      size = 0;
      scale_factor = 2.0;
      item = new T[capacity];
    }
    ABS(const ABS &d){
      size = d.size;
      capacity = d.capacity;
      scale_factor = d.scale_factor;
      item = new T[capacity];
      for (unsigned int i = 0; i < size; i++){
        item[i] = d.item[i];
      }
    }
    ABS &operator=(const ABS &d){
      if (this == &d){
        return *this;
      }

      delete[] item;

      size = d.size;
      capacity = d.capacity;
      scale_factor = d.scale_factor;

      item = new T[capacity];
      for(unsigned int i = 0; i < size; i++){
        item[i] = d.item[i];
      }
      return *this;
    }
    ~ABS(){
      delete[] item;
    }
    void push(T data){
      if (size >= capacity){
        int newCapacity = capacity * 2;
        T* newArray = new T[newCapacity];
        for(unsigned int i = 0; i < size; i++){
          newArray[i] = item[i];
        }
        delete[] item;
        item = newArray;
        capacity = newCapacity;
      }
      item[size++] = data;
    }

    T pop(){
      if (isEmpty()){
        throw runtime_error("Stack is empty");
      }
      T data = item[size - 1];
      size--;
      if (size < capacity / scale_factor){
        int newCapacity = capacity / scale_factor;
        T* newArray = new T[newCapacity];
        for(unsigned int i = 0; i < size; i++){
          newArray[i] = item[i];
        }
        delete[] item;
        item = newArray;
        capacity = newCapacity;
      }
      return data;
    }

    T peek(){
      if (isEmpty()){
        throw runtime_error("Stack is empty");
      }
      return item[size - 1];
    }

    bool isEmpty(){
      return size == 0;
    }

    unsigned int getSize(){
      return size;
    }

    unsigned int getMaxCapacity(){
      return capacity;
    }

    T* getData(){
      return item;
    }
};

