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
//Draw the Tie Fighter Ships
void TShip::draw(unsigned char ** buffer, int px, int pz){
    Color col = shipColor;
    int minX = 3*(xPos-wWidth-radius-1);
    int maxX = 3*(xPos+wWidth+radius+1);
    int maxY = yPos+radius+1;
    for(int i=0;i<maxY;i++){
        for(int j=minX;j<maxX;j=j+3){
            //body
            double distance = sqrt(pow((i-yPos), 2) + (pow((j/3-xPos), 2)));
            if(distance <= radius){
                buffer[i][j]=col.getB();
                buffer[i][j+1]=col.getG();
                buffer[i][j+2]=col.getR();
            }
            //left Wing
            Rect rec = lWing;
            if(i >= rec.getYPos() && i <= rec.getYPos() + rec.getWidth() && j/3 >= rec.getXPos() && j/3 <= rec.getXPos() + rec.getLength()){
                buffer[i][j]=col.getB();
                buffer[i][j+1]=col.getG();
                buffer[i][j+2]=col.getR();
            }
            //right Wing
            Rect rec1 = rWing;
            if(i >= rec1.getYPos() && i <= rec1.getYPos() + rec1.getWidth() && j/3 >= rec1.getXPos() && j/3 <= rec1.getXPos() + rec1.getLength()){
                buffer[i][j]=col.getB();
                buffer[i][j+1]=col.getG();
                buffer[i][j+2]=col.getR();
            }
        }
    }
    
}
