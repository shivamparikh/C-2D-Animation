//  Rect.h



#ifndef RECT_H
#define RECT_H

#include "color.h"

class Rect{
public:
    Rect();
    Rect(double xPosInput, double yPosInput, double length, double width, Color rectColorInput);
    double getXPos() const;
    double getYPos() const;
    double getLength() const;
    double getWidth() const;
    Color getColor() const;
    void setXPos(double xPosInput);
    void setYPos(double yPosInput);
    void setLength(double length);
    void setWidth(double width);
    void setColor(Color rectColorInput);
    void translate(double dx, double dy);
    void disappear();
private:
    double xPos;
    double yPos;
    double length;
    double width;
    Color rectColor;
};
#endif //rect.h
