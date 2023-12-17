#include <iostream>
#include <ostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include "Image.h"
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

int main(int argv, char* args[]) {
    string firstInput;
    string secondInput;
    string additionArgument;
    if(argv < 2 || strcmp(args[1], "--help") == 0){
        cout << "Project 2: Image Processing, Fall 2023" << endl;
        cout << endl;
        cout << "Usage:" << endl;
        cout << "\t./project2.out [output] [firstImage] [method] [...] " << endl;

        return 0;
    }
    firstInput = args[1];
    if(firstInput.size() < 4){
        cout << "Invalid file name." << endl;
        return 1;
    }
    if(firstInput.substr(firstInput.size()-4) != ".tga"){
        cout << "Invalid file name." << endl;
        return 1;
    }
    secondInput = args[2];
    Image image1;
    image1.read(secondInput);
    if(secondInput.size() < 4){
        cout << "Invalid file name." << endl;
        return 1;
    }
    if(secondInput.substr(secondInput.size()-4) != ".tga"){
        cout << "Invalid file name." << endl;
        return 1;
    }
    ifstream File(secondInput, ios_base::binary);
    if(!File.is_open()){
        cout << "File does not exist." << endl;
        return 1;
    }
    File.close();
    if(secondInput.size() < 4){
        cout << "Invalid file name." << endl;
        return 1;
    }
    if(secondInput.substr(secondInput.size()-4) != ".tga"){
        cout << "Invalid file name." << endl;
        return 1;
    }

    int argIndex = 3;
    while(argIndex < argv){
        if (strcmp(args[argIndex], "multiply") == 0){
            if(argv < 5) {
                cout << "Missing argument." << endl;
                return 1;
            }
            additionArgument = args[4];
            if(additionArgument.substr(additionArgument.size()-4) != ".tga"){
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            ifstream additionalFile(additionArgument, ios_base::binary);
            if(!additionalFile.is_open()){
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            Image image1part2;
            image1part2.read(additionArgument);
            Image trackingImage1;
            trackingImage1.Multiply(image1, image1part2);
            image1 = trackingImage1;
        }
        else if (strcmp(args[argIndex], "subtract") == 0){
            if(argv < 5) {
                cout << "Missing argument." << endl;
                return 1;
            }
            additionArgument = args[4];
            if(additionArgument.substr(additionArgument.size()-4) != ".tga"){
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            ifstream additionalFile2(additionArgument, ios_base::binary);
            if(!additionalFile2.is_open()){
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            Image image2part2;
            image2part2.read(additionArgument);
            Image trackingImage2;
            trackingImage2.Subtract(image1, image2part2);
            image1 = trackingImage2;
            argIndex++;
        }
        else if (strcmp(args[argIndex], "flip") == 0){
            Image reverseImage;
            reverseImage = image1;
            reverse(reverseImage.pixelVec.begin(), reverseImage.pixelVec.end());
            //reverseImage.write(firstInput);
            image1 = reverseImage;
            argIndex++;
        }
        else if (strcmp(args[argIndex], "screen") == 0){
            if(argv < 5) {
                cout << "Missing argument." << endl;
                return 1;
            }
            additionArgument = args[4];
            if(additionArgument.substr(additionArgument.size()-4) != ".tga"){
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            ifstream additionalFile(additionArgument, ios_base::binary);
            if(!additionalFile.is_open()){
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            Image image3part2;
            image3part2.read(additionArgument);
            Image trackingImage3;
            trackingImage3.Screen(image1, image3part2);
            image1 = trackingImage3;
        }
        else if (strcmp(args[argIndex], "overlay") == 0){
            if(argv < 5) {
                cout << "Missing argument." << endl;
                return 1;
            }
            additionArgument = args[4];
            if(additionArgument.substr(additionArgument.size()-4) != ".tga"){
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            ifstream additionalFile(additionArgument, ios_base::binary);
            if(!additionalFile.is_open()){
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            Image image8part2;
            image8part2.read(additionArgument);
            Image trackingImage8;
            trackingImage8.Overlay(image1, image8part2);
            image1 = trackingImage8;
        }
        else if (strcmp(args[argIndex], "screen") == 0){
            if(argv < 5) {
                cout << "Missing argument." << endl;
                return 1;
            }
            additionArgument = args[4];
            if(additionArgument.substr(additionArgument.size()-4) != ".tga"){
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            ifstream additionalFile(additionArgument, ios_base::binary);
            if(!additionalFile.is_open()){
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            Image image9part2;
            image9part2.read(additionArgument);
            Image trackingImage9;
            trackingImage9.Screen(image1, image9part2);
            image1 = trackingImage9;
        }
        else if (strcmp(args[argIndex], "combine") == 0){
            if(argv < argIndex) {
                cout << "Missing argument." << endl;
                return 1;
            }
            additionArgument = args[argIndex + 1];
            if(additionArgument.substr(additionArgument.size()-4) != ".tga"){
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            ifstream additionalFile(additionArgument, ios_base::binary);
            if(!additionalFile.is_open()){
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            string additionArgument2 = args[5];
            if(additionArgument.substr(additionArgument2.size()-4) != ".tga"){
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            ifstream additionalFile2(additionArgument, ios_base::binary);
            if(!additionalFile2.is_open()){
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            Image image6;
            Image image6part2;
            image6.read(additionArgument);
            image6part2.read(additionArgument2);
            Image trackingImage6;
            trackingImage6.Combine(image1,image6, image6part2);
            image1 = trackingImage6;
        }
        else if (strcmp(args[argIndex], "onlyred") == 0){
            Image newImage;
            newImage.header = image1.header; // Copy the header from the original image
            for(unsigned int i = 0; i < image1.pixelVec.size(); i++) {
                newImage.pixelVec.push_back({image1.pixelVec[i].red, image1.pixelVec[i].red, image1.pixelVec[i].red});
            }
            image1.header = newImage.header;
            image1.pixelVec = newImage.pixelVec;
            image1 = newImage;
        }
        else if (strcmp(args[argIndex], "onlygreen") == 0){
            Image newImage;
            newImage.header = image1.header; // Copy the header from the original image
            for(unsigned int i = 0; i < image1.pixelVec.size(); i++) {
                newImage.pixelVec.push_back({image1.pixelVec[i].green,image1.pixelVec[i].green, image1.pixelVec[i].green});
            }
            image1.header = newImage.header;
            image1.pixelVec = newImage.pixelVec;
            image1 = newImage;
        }
        else if (strcmp(args[argIndex], "onlyblue") == 0){
            Image newImage;
            newImage.header = image1.header; // Copy the header from the original image
            for(unsigned int i = 0; i < image1.pixelVec.size(); i++) {
                newImage.pixelVec.push_back({image1.pixelVec[i].blue, image1.pixelVec[i].blue, image1.pixelVec[i].blue});
            }
            image1.header = newImage.header;
            image1.pixelVec = newImage.pixelVec;
            image1 = newImage;
        }
        else if (strcmp(args[argIndex], "scalegreen") == 0){
            float scaleNum = atof(args[argIndex + 1]);
            Image trackingImage5;
            trackingImage5.Scale(image1, 1, scaleNum , 1);
            image1 = trackingImage5;
        }
        else if (strcmp(args[argIndex], "scalered") == 0){
            float scaleNum = atof(args[argIndex + 1]);
            Image trackingImage5;
            trackingImage5.Scale(image1, scaleNum, 1 , 1);
            image1 = trackingImage5;
        }
        else if (strcmp(args[argIndex], "scaleblue") == 0){
            float scaleNum = atof(args[argIndex + 1]);
            Image trackingImage5;
            trackingImage5.Scale(image1, 1, 1 , scaleNum);
            image1 = trackingImage5;
        }
        else if(strcmp(args[argIndex], "addblue") == 0){
            int addNum = atoi(args[argIndex + 1]);
            Image trackingImage5;
            trackingImage5.AddBlue(image1, addNum);
            image1 = trackingImage5;
            argIndex++;
        }
        else if(strcmp(args[argIndex], "addred") == 0){
            int addNum = atoi(args[argIndex + 1]);
            Image trackingImage5;
            trackingImage5.AddRed(image1, addNum);
            image1 = trackingImage5;
            argIndex++;
        }
        else if(strcmp(args[argIndex], "addgreen") == 0){
            int addNum = atoi(args[argIndex + 1]);
            Image trackingImage5;
            trackingImage5.AddGreen(image1, addNum);
            image1 = trackingImage5;
            argIndex++;
        }
        else{
            cout << "Invalid method name." << endl;
        }
        argIndex++;
        image1.write(firstInput);
    }

    /*
    //Test case 1
    Image image1;
    Image image1part2;
    image1.read("input/layer1.tga");
    image1part2.read("input/pattern1.tga");
    Image part1;
    part1.Multiply(image1, image1part2);
    part1.write("output/part1.tga");

    //Test case 2
    Image image2;
    Image image2part2;
    image2.read("input/layer2.tga");
    image2part2.read("input/car.tga");
    Image part2;
    part2.Subtract(image2, image2part2);
    part2.write("output/part2.tga");

    //Test case 3
    Image image3;
    Image image3part2;
    image3.read("input/layer1.tga");
    image3part2.read("input/pattern2.tga");
    Image tempImage;
    tempImage.Multiply(image3, image3part2);
    Image image3part3;
    image3part3.read("input/text.tga");
    Image part3;
    part3.Screen(image3part3, tempImage);
    part3.write("output/part3.tga");

    //Test case 4
    Image image4;
    Image image4part2;
    image4.read("input/layer2.tga");
    image4part2.read("input/circles.tga");
    Image tempImage2;
    tempImage2.Multiply(image4, image4part2);
    Image image4part3;
    image4part3.read("input/pattern2.tga");
    Image part4;
    part4.Subtract(image4part3, tempImage2);
    part4.write("output/part4.tga");

    //Test case 5
    Image image5;
    image5.read("input/layer1.tga");
    Image image5part2;
    image5part2.read("input/pattern1.tga");
    Image part5;
    part5.Overlay(image5, image5part2);
    part5.write("output/part5.tga");



    // Test case 6
    Image image6;
    image6.read("input/car.tga");
    Image partSix;
    partSix.AddGreen(image6, 200);
    partSix.write("output/part6.tga");

    // Test case 7
    Image image7;
    image7.read("input/car.tga");
    Image partSeven;
    partSeven.Scale(image7, 4, 1 , 0);
    partSeven.write("output/part7.tga");


    //Test case 8
    Image image8;
    image8.read("input/car.tga");
    image8.SeperateChannel(image8);


    //Test case 9

    Image layerRed;
    Image layerGreen;
    Image layerBlue;
    layerRed.read("input/layer_red.tga");
    layerGreen.read("input/layer_green.tga");
    layerBlue.read("input/layer_blue.tga");

    Image result9;
    result9.Combine(layerRed, layerGreen, layerBlue);
    result9.write("output/part9.tga");


    //Test case 10
    Image reverseImage;
    reverseImage.read("input/text2.tga");
    reverse(reverseImage.pixelVec.begin(), reverseImage.pixelVec.end());
    reverseImage.write("output/part10.tga");
    */
    return 0;
}
