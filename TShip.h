//  TShip.h



#ifndef TSHIP_H
#define TSHIP_H

#include "color.h"
#include "rect.h"
#include "circle.h"

class TShip{
public:
    TShip();
    TShip(double xPosInput, double yPosInput, double radiusInput, double wWidthIn, Color shipColorInput);
    double getXPos() const;
    double getYPos() const;
    Color getColor() const;
    Rect getLWing() const;
    Rect getRWing() const;
    double getRadius() const;
    double getWidth() const;
    void setXPos(double xPosInput);
    void setYPos(double yPosInput);
    void setColor(Color shipColorInput);
    void setRadius(double radiusInput);
    void translate(double dx, double dy);
    void draw(unsigned char ** buffer, int px, int pz);
private:
    double xPos;
    double yPos;
    double radius;
    double wWidth;
    Color shipColor;
    Circle body;
    Rect lWing;
    Rect rWing;
};
#endif //TShip.h
