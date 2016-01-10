//  Created by Shivam Parikh on 12/27/15.
//  Shivam Parikh, Period 4
//  Copyright (c) 2015 Shivam Parikh. All rights reserved.
//  Color.cpp

#include "Color.h"

Color::Color(){
    r = 0;
    g = 0;
    b = 0;
}

Color::Color(double rInput, double gInput, double bInput){
    r = rInput;
    g = gInput;
    b = bInput;
}

double Color::getR() const{
    return r;
}

double Color::getG() const{
    return g;
}

double Color::getB() const{
    return b;
}

void Color::setR(double rInput){
    r = rInput;
}

void Color::setG(double gInput){
    g = gInput;
}

void Color::setB(double bInput){
    b = bInput;
}

void Color::setColor(Color colorInput){
    r = colorInput.getR();
    g = colorInput.getG();
    b = colorInput.getB();
}
void Color::setVal(double red, double green, double blue){
    r = red;
    g = green;
    b = blue;
}