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
//To draw most all Circles
void Circle::draw(unsigned char ** buffer, int px, int pz){
    Color col = circleColor;
    //Calculate minima and maxima for Predictive Pixel Method
    int minX = 3*((int)xPos-radius-1);
    int maxX = 3*((int)xPos+radius+1);
    int maxY = yPos+radius+1;
    for(int i=0;i<maxY;i++){
        for(int j=minX;j<maxX;j=j+3){
            //distance formula implementation of the circle.
            double distance = sqrt(pow((i-yPos), 2) + (pow((j/3-xPos), 2)));
            if(distance <= radius){
                buffer[i][j]=col.getB();
                buffer[i][j+1]=col.getG();
                buffer[i][j+2]=col.getR();
            }
        }
    }
}
void Circle::drawS(unsigned char ** buffer, int px, int pz){
    //For massive drawings at the same time like in the case of the stars, only limit the x, not y
    //Though it is slower, it makes it bypass the segmentation errors.
    Color col = circleColor;
    int minX = 3*((int)xPos-radius-1);
    int maxX = 3*((int)xPos+radius+1);
    for(int i=0;i<pz;i++){
        for(int j=minX;j<maxX;j=j+3){
            //distance formula implementation of the circle.
            double distance = sqrt(pow((i-yPos), 2) + (pow((j/3-xPos), 2)));
            if(distance <= radius){
                buffer[i][j]=col.getB();
                buffer[i][j+1]=col.getG();
                buffer[i][j+2]=col.getR();
            }
        }
    }
}
//To Draw Circles With Rings
void Circle::drawR(unsigned char ** buffer, int px, int pz, int rings){
    Color col = circleColor;
    int minX = 3*(xPos-radius-1-(5*rings));
    int maxX = 3*(xPos+radius+1+(5*rings));
    int maxY = yPos+radius+1+(5*rings);
    for(int i=0;i<maxY;i++){
        for(int j=minX;j<maxX;j=j+3){
            double distance = sqrt(pow((i-yPos), 2) + (pow((j/3-xPos), 2)));
            if(distance <= radius){
                buffer[i][j]=col.getB();
                buffer[i][j+1]=col.getG();
                buffer[i][j+2]=col.getR();
            }
            //Define distance between planet and first ring, then continue through and add radius
            //  Without adding pixels unless its in a certain area.
            int extra = 5;
            for(int k = 0; k < rings; k++){
                if((radius+extra < distance) && (distance < radius+(extra+2))){
                    buffer[i][j]=(col.getB());
                    buffer[i][j+1]=(col.getG());
                    buffer[i][j+2]=(col.getR());
                }
                extra += 4;
            }
        }
    }
}
