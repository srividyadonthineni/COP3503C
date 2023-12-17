#pragma once
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Header{
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};

struct Pixel{
    unsigned char blue; // unsigned char is 8bit integer 8-255
    unsigned char green; // 0(dark) - 255 length
    unsigned char red;
};

class Image {
public:
    Header header;
    vector<Pixel> pixelVec;
    Image();
    void read(const string& inName);
    void write(const string& outName);
    void Multiply(const Image& picture1, const Image& picture2);
    void Subtract(const Image& picture1, const Image& picture2);
    void Overlay(const Image& picture1, const Image& picture2);
    void Screen(const Image& picture1, const Image& picture2);
    void AddRed(Image& picture1, int addition);
    void AddGreen(Image& picture1, int addition);
    void AddBlue(Image& picture1, int addition);
    void Scale(const Image& picture1, float RedPix, float GreenPix, float BluePix);
    void SeperateChannel(const Image& picture1);
    void Combine(const Image& picture1, const Image& green, const Image& blue);
    Image& operator=(const Image& other);

private:
    string name;
};
