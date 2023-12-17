#include "Shapes.h"
#include <iostream>
#include <cmath>
using namespace std;


void Shape2D::ShowArea() const {
    cout << "The area of the " << GetName2D() << " is : " << Area() << endl;
}

bool Shape2D::operator>(const Shape2D &rhs) const{
    return this->Area() > rhs.Area();
}
bool Shape2D::operator<(const Shape2D &rhs) const{
    return this->Area() < rhs.Area();
}
bool Shape2D::operator==(const Shape2D &rhs) const{
    return this->Area() == rhs.Area();
}

float Shape3D::Volume() const{
    cout << endl;
}

void Shape3D::ShowVolume() const {
    cout << "The volume of the " << GetName3D() << " is : " << Volume() << endl;
}

bool Shape3D::operator>(const Shape3D &rhs) const{
    return this->Volume() > rhs.Volume();
}
bool Shape3D::operator<(const Shape3D &rhs) const{
    return this->Volume() < rhs.Volume();
}
bool Shape3D::operator==(const Shape3D &rhs) const{
    return this->Volume() == rhs.Volume();
}

Square::Square(){
    float squareLength = 0.0;
}

Square::Square(float squareLength) {
    this->squareLength = squareLength;
}
void Square::Scale(float scaleFactor){
    squareLength *= scaleFactor;
}
void Square::Display() const{
    ShowArea();
    cout << "Length of a side: " << squareLength << endl;
}
float Square::Area() const{
    return squareLength * squareLength;
}
string Square::GetName2D() const {
    return "Square";
}

Triangle::Triangle() {
    float triangleBase = 0.0;
    float triangleHeight = 0.0;
}

Triangle::Triangle(float triangleBase, float triangleHeight) {
    this->triangleBase = triangleBase;
    this->triangleHeight = triangleHeight;
}

void Triangle::Scale(float scaleFactor){
    triangleHeight *= scaleFactor;
    triangleBase *= scaleFactor;
}

void Triangle::Display() const{
    ShowArea();
    cout << "Base: " << triangleBase << endl;
    cout << "Height: " << triangleHeight << endl;
}

float Triangle::Area() const{
    return 0.5f * triangleBase * triangleHeight;
}

string Triangle::GetName2D() const {
    return "Triangle";
}

Circle::Circle() {
    float circleRadius = 0.0;
}

Circle::Circle(float circleRadius) {
    this->circleRadius = circleRadius;
}

void Circle::Scale(float scaleFactor){
    circleRadius *= scaleFactor;
}

void Circle::Display() const{
    ShowArea();
    cout << "Radius: " << circleRadius << endl;
}

float Circle::Area() const{
    return M_PI * circleRadius * circleRadius;
}

string Circle::GetName2D() const {
    return "Circle";
}

TriangularPyramid::TriangularPyramid() : base(0, 0){
    float pyramidHeight = 0.0;
}

TriangularPyramid::TriangularPyramid(float pyramidHeight, float pyramidBaseLength, float pyramidBaseHeight) : base(pyramidBaseLength, pyramidBaseHeight) {
    this->pyramidHeight = pyramidHeight;
}

void TriangularPyramid::Scale(float scaleFactor){
    base.Scale(scaleFactor);
    pyramidHeight *= scaleFactor;
}

void TriangularPyramid::Display() const{
    ShowVolume();
    cout << "The height is: " << pyramidHeight << endl;
    base.Display();
}

float TriangularPyramid::Volume() const {
    return base.Area() * pyramidHeight * 1.0f / 3.0f;
}

string TriangularPyramid::GetName3D() const {
    return "TriangularPyramid";
}

Cylinder::Cylinder() : round(0){
    float cylinderHeight = 0.0;
}

Cylinder::Cylinder(float cylinderHeight, float cylinderRadius) : round(cylinderRadius) {
    this->cylinderHeight = cylinderHeight;
}

void Cylinder::Scale(float scaleFactor){
    cylinderHeight *= scaleFactor;
    round.Scale(scaleFactor);
}
void Cylinder::Display() const{
    ShowVolume();
    cout << "The height is: " << cylinderHeight << endl;
    round.Display();
}
float Cylinder::Volume() const {
    return round.Area() * cylinderHeight;
}

string Cylinder::GetName3D() const {
    return "Cylinder";
}

Sphere::Sphere() : round2(0){
    float sphereRadius = 0.0;
}

Sphere::Sphere(float sphereRadius) : round2(sphereRadius){
    this->sphereRadius = sphereRadius;
}

void Sphere::Scale(float scaleFactor){
    sphereRadius *= scaleFactor;
    round2.Scale(scaleFactor);
}
void Sphere::Display() const{
    ShowVolume();
    round2.Display();
}
float Sphere::Volume() const {
    return round2.Area() * sphereRadius * 4.0f / 3.0f;
}

string Sphere::GetName3D() const {
    return "Sphere";
}

