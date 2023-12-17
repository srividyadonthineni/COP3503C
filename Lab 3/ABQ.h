#pragma once
#include <iostream>
using namespace std;

template <typename T>
class ABQ{
private:
    T* elements;
    unsigned int capacity;
    unsigned int size;
    float scale_factor;
    unsigned int front;
    unsigned int back;

public:
    ABQ(){
        capacity = 1;
        size = 0;
        scale_factor = 2.0;
        front = 0;
        back = 0;
        elements = new T[capacity];
    }

    ABQ(int capacity){
        this->capacity = capacity;
        size = 0;
        scale_factor = 2.0;
        front = 0;
        back = 0;
        elements = new T[capacity];
    }

    ABQ(const ABQ &d){
        capacity = d.capacity;
        size = d.size;
        scale_factor = d.scale_factor;
        front = 0;
        back = 0;
        elements = new T[capacity];
        for(unsigned int i = 0; i < d.size; i++){
            elements[i] = d.elements[i];
        }
    }

    ABQ &operator=(const ABQ &d){
        if (this == &d){
            return *this;
        }

        delete[] elements;

        size = d.size;
        capacity = d.capacity;
        scale_factor = d.scale_factor;

        elements = new T[capacity];
        for(unsigned int i = 0; i < size; i++){
            elements[i] = d.elements[i];
        }
        return *this;
    }

    ~ABQ(){
        delete[] elements;
    }

    void enqueue(T data){
        if (size >= capacity){
            int newCapacity = capacity * 2;
            T* newArray = new T[newCapacity];
            for(unsigned int i = 0; i < size; i++){
                newArray[i] = elements[(front + i)];
            }

            delete[] elements;
            elements = newArray;
            capacity = newCapacity;
        }

        elements[back] = data;
        back = back + 1;
        size++;  
    }

    T dequeue(){
        if (isEmpty()){
            throw runtime_error("Queue is empty");
        }
        T item = elements[front];
        front = front + 1;
        size--;

        if (isEmpty()){
            front = 0;
            back = 0;
        }

        back = front + size;
        if (size < capacity / scale_factor && capacity > 1){
            int newCapacity = capacity / scale_factor;

            T* newArray = new T[newCapacity];
            for(unsigned int i = 0; i < size; i++){
                newArray[i] = elements[front + i];
            }
            delete[] elements;
            elements = newArray;
            front = 0;
            back = size - 1;
            capacity = newCapacity;
        }
        return item;
    }

    T peek(){
        while (size == 0){
          throw runtime_error("Queue is empty");
          break;
        }
        return elements[front];
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
        return elements;
    }
};
