//  Circle.h



#ifndef CIRCLE_H
#define CIRCLE_H

#include "color.h"

class Circle{
public:
    Circle();
    Circle(double xPosInput, double yPosInput, double radiusInput, Color circleColorInput);
    double getXPos() const;
    double getYPos() const;
    Color getColor() const;
    double getRadius() const;
    void setXPos(double xPosInput);
    void setYPos(double yPosInput);
    void setColor(Color circleColorInput);
    void setRadius(double radiusInput);
    void translate(double dx, double dy);
    void revolve(double deg, double xCenter, double yCenter);
    void disappear();
private:
    double xPos;
    double yPos;
    double radius;
    Color circleColor;
};
#endif //Circle.h
