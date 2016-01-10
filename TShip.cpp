//  Created by Shivam Parikh on 1/7/16.
//  Shivam Parikh, Period 4
//  Copyright (c) 2015 Shivam Parikh. All rights reserved.
//  TShip.cpp

#include <cmath>
#include "Color.h"
#include "Circle.h"
#include "Rect.h"
#include "TShip.h"



TShip::TShip(){
    xPos = 0;
    yPos = 0;
    radius = 1;
}

TShip::TShip(double xPosInput, double yPosInput, double radiusInput, double wWidthIn, Color shipColorInput){
    xPos = xPosInput;
    yPos = yPosInput;
    radius = radiusInput;
    wWidth = wWidthIn;
    shipColor.setColor(shipColorInput);
    Circle temp(xPos, yPos, radius, shipColor);
    body = temp;
    Rect temp1(xPos+radius, yPos-radius, wWidth, 2*radius, shipColor);
    rWing = temp1;
    Rect temp2(xPos-radius-wWidth, yPos-radius, wWidth, 2*radius, shipColor);
    lWing = temp2;
}

double TShip::getXPos() const{
    return xPos;
}

double TShip::getYPos() const{
    return yPos;
}

Color TShip::getColor() const{
    return shipColor;
}

double TShip::getRadius() const{
    return radius;
}
double TShip::getWidth() const{
    return wWidth;
}
Rect TShip::getLWing() const{
    return lWing;
}
Rect TShip::getRWing() const{
    return rWing;
}

void TShip::setXPos(double xPosInput){
    xPos = xPosInput;
    rWing.setXPos(xPos+radius);
    lWing.setXPos(xPos-radius-wWidth);
}

void TShip::setYPos(double yPosInput){
    yPos = yPosInput;
    rWing.setYPos(yPos-radius);
    lWing.setYPos(yPos-radius);
}

void TShip::setColor(Color shipColorInput){
    shipColor = shipColorInput;
}

void TShip::setRadius(double radiusInput){
    radius = radiusInput;
}

void TShip::translate(double dx, double dy){
    xPos += dx;
    yPos += dy;
    rWing.setXPos(xPos+radius);
    rWing.setYPos(yPos-radius);
    lWing.setXPos(xPos-radius-wWidth);
    lWing.setYPos(yPos-radius);
}
