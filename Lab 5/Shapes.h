#include <iostream>
#include <string>
using namespace std;

class Shape{
public:
    virtual void Scale(float scaleFactor) = 0;
    virtual void Display() const = 0;
};

class Shape2D: virtual public Shape{
protected:
    float squareLength;
    float triangleBase;
    float triangleHeight;
    float circleRadius;
public:
    virtual float Area() const = 0;
    void ShowArea() const;
    virtual string GetName2D() const = 0;
    bool operator>(const Shape2D &rhs) const;
    bool operator<(const Shape2D &rhs) const;
    bool operator==(const Shape2D &rhs) const;
};

class Shape3D: virtual public Shape{
protected:
    float pyramidHeight;
    float cylinderHeight;
    float cylinderRadius;
    float sphereRadius;
public:
    virtual float Volume() const = 0;
    void ShowVolume() const;
    virtual string GetName3D() const = 0;
    bool operator>(const Shape3D &rhs) const;
    bool operator<(const Shape3D &rhs) const;
    bool operator==(const Shape3D &rhs) const;
};

class Square: public Shape2D{
public:
    Square();
    Square(float squareLength);
    void Scale(float scaleFactor);
    void Display() const;
    float Area() const;
    string GetName2D() const;
};

class Triangle: public Shape2D{
public:
    Triangle();
    string GetName2D() const;
    Triangle(float triangleBase, float triangleHeight);
    void Scale(float scaleFactor);
    void Display() const;
    float Area() const;
};

class Circle: public Shape2D{
public:
    Circle();
    string GetName2D() const;
    Circle(float circleRadius);
    void Scale(float scaleFactor);
    void Display() const;
    float Area() const;
};

class TriangularPyramid: public Shape3D{
public:
    Triangle base;
    TriangularPyramid();
    TriangularPyramid(float pyramidHeight, float pyramidBaseLength, float pyramidBaseHeight);
    void Scale(float scaleFactor);
    void Display() const;
    float Volume() const;
    string GetName3D() const;
};

class Cylinder: public Shape3D{
public:
    Circle round;
    Cylinder();
    Cylinder(float cylinderHeight, float cylinderRadius);
    void Scale(float scaleFactor);
    void Display() const;
    float Volume() const;
    string GetName3D() const;
};

class Sphere: public Shape3D{
public:
    Circle round2;
    Sphere();
    Sphere(float sphereRadius);
    void Scale(float scaleFactor);
    void Display() const;
    float Volume() const;
    string GetName3D() const;
};
