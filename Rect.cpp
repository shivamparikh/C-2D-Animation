//  Created by Shivam Parikh on 1/4/16.
//  Shivam Parikh, Period 4
//  Copyright (c) 2016 Shivam Parikh. All rights reserved.
//  Rect.cpp

#include <cmath>
#include "Color.h"
#include "Rect.h"



Rect::Rect(){
    xPos = 0;
    yPos = 0;
    length = 0;
    width = 0;
}

Rect::Rect(double xPosInput, double yPosInput, double lengthIn, double widthIn, Color rectColorInput){
    xPos = xPosInput;
    yPos = yPosInput;
    length = lengthIn;
    width = widthIn;
    rectColor.setColor(rectColorInput);

}

double Rect::getXPos() const{
    return xPos;
}

double Rect::getYPos() const{
    return yPos;
}

Color Rect::getColor() const{
    return rectColor;
}

double Rect::getLength() const{
    return length;
}

double Rect::getWidth() const{
    return width;
}

void Rect::setXPos(double xPosInput){
    xPos = xPosInput;
}

void Rect::setYPos(double yPosInput){
    yPos = yPosInput;
}

void Rect::setColor(Color rectColorInput){
    rectColor = rectColorInput;
}

void Rect::setLength(double lengthIn){
    length = lengthIn;
}

void Rect::setWidth(double widthIn){
    width = widthIn;
}

void Rect::translate(double dx, double dy){
    xPos += dx;
    yPos += dy;
}

void Rect::disappear(){
    xPos = -1*length;
    yPos = -1*width;
}
void Rect::draw(unsigned char ** buffer, int px, int pz){
    Color col = rectColor;
    int minX = 3*(xPos-1);
    int maxX = 3*(xPos + length +1);
    int maxY = yPos+width+1;
    for(int i=0;i<maxY;i++){
        for(int j=minX;j<maxX;j=j+3){
            //Due to the Predictive Pixel Method, I only had to have one limit in the if statement.
            if(i >= yPos){
                buffer[i][j]=col.getB();
                buffer[i][j+1]=col.getG();
                buffer[i][j+2]=col.getR();
            }
        }
    }
}

