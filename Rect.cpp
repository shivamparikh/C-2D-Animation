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

