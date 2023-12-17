#include "Image.h"
#include <vector>
#include <iostream>
using namespace std;


Image::Image() {}

void Image::read(const string& inName) {
    ifstream stream = ifstream (inName, ios_base::binary);
    if(!stream.is_open()){
        throw runtime_error("Could not open file.");
    }

    stream.read(&header.idLength , sizeof(header.idLength));
    stream.read(&header.colorMapType , sizeof(header.colorMapType));
    stream.read(&header.dataTypeCode , sizeof(header.dataTypeCode));
    stream.read((char*)&header.colorMapOrigin , sizeof(header.colorMapOrigin));
    stream.read((char*)&header.colorMapLength , sizeof(header.colorMapLength));
    stream.read(&header.colorMapDepth , sizeof(header.colorMapDepth));
    stream.read((char*)&header.xOrigin , sizeof(header.xOrigin));
    stream.read((char*)&header.yOrigin , sizeof(header.yOrigin));
    stream.read((char*)&header.width , sizeof(header.width));
    stream.read((char*)&header.height , sizeof(header.height));
    stream.read(&header.bitsPerPixel , sizeof(header.bitsPerPixel));
    stream.read(&header.imageDescriptor , sizeof(header.imageDescriptor));

    int imageSize = int(header.width * header.height);

    for(unsigned int i = 0; i < imageSize; i++){
        Pixel pixel;

        stream.read((char*)&pixel.blue, sizeof(pixel.blue));
        stream.read((char*)&pixel.green, sizeof(pixel.green));
        stream.read((char*)&pixel.red, sizeof(pixel.red));

        pixelVec.push_back(pixel);

    }
}

void Image::write(const string& outName) {
    ofstream stream(outName, ios_base::binary);

    stream.write(&header.idLength , sizeof(header.idLength));
    stream.write(&header.colorMapType , sizeof(header.colorMapType));
    stream.write(&header.dataTypeCode , sizeof(header.dataTypeCode));
    stream.write((char*)&header.colorMapOrigin , sizeof(header.colorMapOrigin));
    stream.write((char*)&header.colorMapLength , sizeof(header.colorMapLength));
    stream.write(&header.colorMapDepth , sizeof(header.colorMapDepth));
    stream.write((char*)&header.xOrigin , sizeof(header.xOrigin));
    stream.write((char*)&header.yOrigin , sizeof(header.yOrigin));
    stream.write((char*)&header.width , sizeof(header.width));
    stream.write((char*)&header.height , sizeof(header.height));
    stream.write(&header.bitsPerPixel , sizeof(header.bitsPerPixel));
    stream.write(&header.imageDescriptor , sizeof(header.imageDescriptor));

    for(unsigned int i = 0; i < pixelVec.size(); i++){
        Pixel pixel = pixelVec[i];
        stream.write((char*)&pixel.blue, sizeof(pixel.blue));
        stream.write((char*)&pixel.green, sizeof(pixel.green));
        stream.write((char*)&pixel.red, sizeof(pixel.red));
    }
}

void Image::Multiply(const Image& picture1, const Image& picture2){

    header = picture1.header;

    for(unsigned int i = 0; i < picture1.pixelVec.size(); i++){
        Pixel tempPixel;
        const Pixel& tempPixel2 = picture1.pixelVec[i];
        const Pixel& tempPixel3 = picture2.pixelVec[i];

        float bluePixel = float(tempPixel2.blue) * float(tempPixel3.blue) / 255.0f + 0.5f;
        float greenPixel = float(tempPixel2.green) * float(tempPixel3.green) / 255.0f + 0.5f;
        float redPixel = float(tempPixel2.red) * float(tempPixel3.red) / 255.0f + 0.5f;

        tempPixel.blue = char(bluePixel);
        tempPixel.green = char(greenPixel);
        tempPixel.red = char(redPixel);

        pixelVec.push_back(tempPixel);

    }
}

void Image::Subtract(const Image &picture1, const Image &picture2) {
    header = picture1.header;
    for(unsigned int i = 0; i < picture1.pixelVec.size(); i++){
        Pixel shortPixel;
        const Pixel& shortPixel2 = picture1.pixelVec[i];
        const Pixel& shortPixel3 = picture2.pixelVec[i];

        int subtractBluePixel = int(shortPixel2.blue) - int(shortPixel3.blue);
        int subtractGreenPixel = int(shortPixel2.green) - int(shortPixel3.green);
        int subtractRedPixel = int(shortPixel2.red) - int(shortPixel3.red);

        if(subtractBluePixel < 0){
            subtractBluePixel = 0;
        }
        if(subtractGreenPixel < 0){
            subtractGreenPixel = 0;
        }
        if(subtractRedPixel < 0){
            subtractRedPixel = 0;
        }

        shortPixel.blue = char(subtractBluePixel);
        shortPixel.green = char(subtractGreenPixel);
        shortPixel.red = char(subtractRedPixel);

        pixelVec.push_back(shortPixel);
    }

}


void Image::Overlay(const Image &picture1, const Image &picture2) {
    this->header = picture1.header;
    for(unsigned int i = 0; i < picture1.pixelVec.size(); i++){
        Pixel overlayPixel;
        const Pixel& overlayPixel2 = picture1.pixelVec[i];
        const Pixel& overlayPixel3 = picture2.pixelVec[i];

        float blueOverlay1 = overlayPixel2.blue / 255.f;
        float blueOverlay2 = overlayPixel3.blue / 255.f;
        float greenOverlay1 = overlayPixel2.green / 255.f;
        float greenOverlay2 = overlayPixel3.green / 255.f;
        float redOverlay1 = overlayPixel2.red / 255.f;
        float redOverlay2 = overlayPixel3.red / 255.f;

        if(blueOverlay2 <= 0.5f){
            overlayPixel.blue = char(2.0f * (float(blueOverlay1) * float(blueOverlay2)) * 255.0f + 0.5f);
        }
        else if(blueOverlay2 > 0.5){
            overlayPixel.blue = char((1.0f - (2.0f * (1.0f - float(blueOverlay1)) * (1.0f - float(blueOverlay2)))) * 255.0f + 0.5f);
        }

        if(greenOverlay2 <= 0.5){
            overlayPixel.green = char(2.0f * (float(greenOverlay1) * float(greenOverlay2)) * 255.0f + 0.5f);
        }
        else if(greenOverlay2 > 0.5){
            overlayPixel.green = ((1.0f - (2.0f * (1.0f - float(greenOverlay1)) * (1.0f - float(greenOverlay2)))) * 255.0f + 0.5f);
        }

        if(redOverlay2 <= 0.5){
            overlayPixel.red = char(2.0f * (float(redOverlay1) * float(redOverlay2)) * 255.0f + 0.5f);
        }
        else if(redOverlay2 > 0.5){
            overlayPixel.red = ((1.0f - (2.0f * (1.0f - float(redOverlay1)) * (1.0f - float(redOverlay2)))) * 255.0f + 0.5f);
        }

        if(overlayPixel.blue > 255){
            overlayPixel.blue = 255;
        }
        if(overlayPixel.green > 255){
            overlayPixel.green = 255;
        }
        if(overlayPixel.red > 255){
            overlayPixel.red = 255;
        }

        pixelVec.push_back(overlayPixel);
    }
}


void Image::Screen(const Image &picture1, const Image &picture2) {
    this->header = picture1.header;
    for(unsigned int i = 0; i < picture1.pixelVec.size(); i++){
        Pixel screenPixel;
        const Pixel& screenPixel2 = picture1.pixelVec[i];
        const Pixel& screenPixel3 = picture2.pixelVec[i];

        float blueScreen1 = float(screenPixel2.blue) / 255.0f;
        float blueScreen2 = float(screenPixel3.blue) / 255.0f;
        float greenScreen1 = float(screenPixel2.green) / 255.0f;
        float greenScreen2 = float(screenPixel3.green) / 255.0f;
        float redScreen1 = float(screenPixel2.red) / 255.0f;
        float redScreen2 = float(screenPixel3.red) / 255.0f;

        int blueScreen = (1.0f - ((1.0f - blueScreen1) * (1.0f - blueScreen2))) * 255.0f + 0.5f;
        int greenScreen = (1.0f - ((1.0f - greenScreen1) * (1.0f - greenScreen2))) * 255.0f + 0.5f;
        int redScreen = (1.0f - ((1.0f - redScreen1) * (1.0f - redScreen2))) * 255.0f + 0.5f;

        if(screenPixel.blue > 255){
            screenPixel.blue = 255;
        }
        if(screenPixel.green > 255){
            screenPixel.green = 255;
        }
        if(screenPixel.red > 255){
            screenPixel.red = 255;
        }

        screenPixel.blue = char(blueScreen);
        screenPixel.green = char(greenScreen);
        screenPixel.red = char(redScreen);

        pixelVec.push_back(screenPixel);
    }
}


void Image::AddRed(Image& picture1, int addition) {
    this->header = picture1.header;
    for(unsigned int i = 0; i < picture1.pixelVec.size(); i++) {
        Pixel& addRedPixel = picture1.pixelVec[i];
        int redPixel = int(addRedPixel.red) + addition;

        if (redPixel < 0) {
            redPixel = 0;
        } else if (redPixel > 255) {
            redPixel = 255;
        }

        addRedPixel.red = char(redPixel);
        pixelVec.push_back(addRedPixel);
    }
}


void Image::AddGreen(Image& picture1, int addition) {
    this->header = picture1.header;
    for(unsigned int i = 0; i < picture1.pixelVec.size(); i++){
        Pixel& addGreenPixel = picture1.pixelVec[i];
        int greenPixel = int(addGreenPixel.green) + addition;

        if (greenPixel < 0){
            greenPixel = 0;
        }
        else if (greenPixel > 255){
            greenPixel = 255;
        }

        addGreenPixel.green = char(greenPixel);
        pixelVec.push_back(addGreenPixel);
    }
}


void Image::AddBlue(Image& picture1, int addition) {
    this->header = picture1.header;
    for (unsigned int i = 0; i < picture1.pixelVec.size(); i++){
        Pixel& addBluePixel = picture1.pixelVec[i];
        int bluePixel = int(addBluePixel.blue) + addition;

        if (bluePixel < 0){
            bluePixel = 0;
        }
        else if (bluePixel > 255){
            bluePixel = 255;
        }

        addBluePixel.blue = char(bluePixel);
        pixelVec.push_back(addBluePixel);
    }
}

void Image::Scale(const Image& picture1, float RedPix, float GreenPix, float BluePix){
    this->header = picture1.header;
    for (unsigned int i = 0; i < picture1.pixelVec.size(); i++){
        Pixel scalePixel;
        const Pixel& scalePixel2 = picture1.pixelVec[i];

        int scaleRed = int(scalePixel2.red) * RedPix;
        if(scaleRed > 255){
            scaleRed = 255;
        }

        int scaleGreen = int(scalePixel2.green) * GreenPix;
        if(scaleGreen > 255){
            scaleGreen = 255;
        }

        int scaleBlue = int(scalePixel2.blue) * BluePix;
        if(scaleBlue > 255){
            scaleBlue = 255;
        }

        scalePixel.blue = char(scaleBlue);
        scalePixel.red = char(scaleRed);
        scalePixel.green = char(scaleGreen);

        pixelVec.push_back(scalePixel);
    }
}

void Image::SeperateChannel(const Image& picture1){
    Image imageRed;
    Image imageGreen;
    Image imageBlue;
    imageBlue.header = picture1.header;
    imageRed.header = picture1.header;
    imageGreen.header = picture1.header;
    Pixel red;
    Pixel blue;
    Pixel green;

    for(unsigned int i = 0; i < picture1.pixelVec.size(); i++){
        red.red = picture1.pixelVec[i].red;
        red.blue = picture1.pixelVec[i].red;
        red.green = picture1.pixelVec[i].red;
        blue.red = picture1.pixelVec[i].blue;
        blue.blue = picture1.pixelVec[i].blue;
        blue.green = picture1.pixelVec[i].blue;
        green.red = picture1.pixelVec[i].green;
        green.blue = picture1.pixelVec[i].green;
        green.green = picture1.pixelVec[i].green;

        imageRed.pixelVec.push_back(red);
        imageGreen.pixelVec.push_back(green);
        imageBlue.pixelVec.push_back(blue);

    }
    imageRed.write("output/part8_r.tga");
    imageGreen.write("output/part8_g.tga");
    imageBlue.write("output/part8_b.tga");
}


void Image::Combine(const Image& picture1, const Image& greenSource, const Image& blueSource){
    this->header = picture1.header;
    pixelVec.clear();
    for(unsigned int i = 0; i < picture1.pixelVec.size(); i++){
        Pixel combined;
        combined.red = picture1.pixelVec[i].red;
        combined.green = greenSource.pixelVec[i].green;
        combined.blue = blueSource.pixelVec[i].blue;
        pixelVec.push_back(combined);
    }
}

Image& Image::operator=(const Image& other) {
    if (this != &other) {
        this->header = other.header;
        this->pixelVec.assign(other.pixelVec.begin(), other.pixelVec.end());
    }
    return *this;
}

