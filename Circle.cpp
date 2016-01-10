//  Created by Shivam Parikh on 12/27/15.
//  Shivam Parikh, Period 4
//  Copyright (c) 2015 Shivam Parikh. All rights reserved.
//  Circle.cpp

#include <cmath>
#include "Color.h"
#include "Circle.h"



Circle::Circle(){
    xPos = 0;
    yPos = 0;
    radius = 1;
}

Circle::Circle(double xPosInput, double yPosInput, double radiusInput, Color circleColorInput){
    xPos = xPosInput;
    yPos = yPosInput;
    radius = radiusInput;
    circleColor.setColor(circleColorInput);
}

double Circle::getXPos() const{
    return xPos;
}

double Circle::getYPos() const{
    return yPos;
}

Color Circle::getColor() const{
    return circleColor;
}

double Circle::getRadius() const{
    return radius;
}

void Circle::setXPos(double xPosInput){
    xPos = xPosInput;
}

void Circle::setYPos(double yPosInput){
    yPos = yPosInput;
}

void Circle::setColor(Color circleColorInput){
    circleColor = circleColorInput;
}

void Circle::setRadius(double radiusInput){
    radius = radiusInput;
}

void Circle::translate(double dx, double dy){
    xPos += dx;
    yPos += dy;
}

void Circle::revolve(double deg, double xCenter, double yCenter){
    double radCon = 3.141592653/180;
    xPos = xCenter + radius*(cos(deg*radCon));
    yPos = yCenter + radius*(sin(deg*radCon));
}
void Circle::disappear(){
    xPos = -1*radius;
    yPos = -1*radius;
}
