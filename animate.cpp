//  animate.cpp is the file name.
//  currently the command line arguments include the following
//  currently moving to working with the config_data.txt file format
//  Author: Shivam Parikh, Period 4, Due 1/8/15
//  Purpose of animation: Draw a moving solar system with stars in the background and a death star like
//      object in the top right, where a base from the moon fires shots every time it reaches the peak of
//      its revolutions. This moon also has its own moon revolving around it. There exists a second planet as
//      well which has rings of variable count. Eventually, the death star begins to pulse colors and begins to
//      weaken. The death star fires a laser beam at a planet in the top left, which is destroyed.
//      End Animation.

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include "Circle.h"
#include "Color.h"
#include "Rect.h"
#include "TShip.h"
using namespace std;

//Global Constants
const double RADCON = M_PI/180;

//function definitions
void drawCircle(unsigned char ** buffer, Circle cir, int px, int pz);
void drawStars(unsigned char ** buffer, Circle cir, int px, int pz);
void drawRect(unsigned char ** buffer, Rect rec, int px, int pz);
void drawCirclewRings(unsigned char ** buffer, Circle cir, int px, int pz, int rings);
void drawTShip(unsigned char ** buffer, TShip tie, int px, int pz);
void write_bmp_header_file(ofstream& output_file, int px, int pz);
int string_to_int(string s);
string makeName(int num);
//end function definitions

int main(int argc, char * argv[]){
    //Open Config_File
    ifstream in_config;
    string strInput = argv[1];
    in_config.open(strInput.c_str());
    string blank;
    string dO;
    vector<double> data;
    time_t sTime = time(0);
    while(!in_config.fail()){
        in_config >> blank >> dO;
        data.push_back(string_to_int(dO));
    }
    //end config file input to the vector
    
    
    //Create Needed Variables to Store Data
    int i,j;
    int px = data [0];
    int pz = data[1];
    int pxPos, pyPos, pTxPos, pTyPos, mxPos, myPos, sxPos, syPos, m1xPos, m1yPos;
    int deg = 0;
    int mdeg = 0;
    int m1deg = 180;
    int pdeg = 180;
    int sdeg = 180;
    int cirSize = 20;
    int frames = data[2];
    int pCycle = abs(360/data[15]);
    int oCycle = abs(360/data[18]);
    int dFrames = data[25];
    int starIntensityMin = data[26];
    int starIntensityMax = data[27];
    double radius = data[5];
    bool dStarExists = true;
    bool alderanHit = false;
    
    
    //Calculations for Animations
    int dRate = data[13];
    int dxPos = px-data[9]-7;
    int dyPos = data[9]+7;
    int dRad = data[9];
    int moonShotSpeed;
    int eX = (dxPos - (data[3]-data[7]))/2;
    int eY = (data[4] - dyPos);
    int exStart = dxPos - eX;
    int eyStart = data[4];
    double moonScale;
    
    //DECLARE objects for the Animation
    Color background(20, 20, 20);
    Color moonCol(255, 255, 255);
    Color yellow(255, 255, 0);
    Color gray(220, 220, 210);
    Color blue(0, 255, 255);
    Color flashRed(255, 210, 210);
    Color alderanCol(5, 178, 255);
    Color red(255, 0, 0);
    Color gShot(95, 255, 35);
    Color plOther(199, 21, 133);
    Color spaceShips(249, 100, 16);
    Color mOMoon(127, 255, 212);
    Circle moon(0, 0, data[23], moonCol);
    Circle sun(data[3], data[4], data[8], yellow);
    Circle deathStar(dxPos, dyPos, dRad, gray);
    Circle planet(0, 0, data[12], blue);
    Circle alderan(data[16]+5, dyPos, data[16], alderanCol);
    Circle otherPlanet(0, 0, data[11], plOther);
    Circle rebelShot(0, 0, data[31], red);
    TShip starShip(0, 0, data[22], data[32], spaceShips);
    TShip starShip1(0, 0, data[22], data[32], spaceShips);
    TShip starShip2(0, 0, data[22], data[32], spaceShips);
    Circle moonOfMoon(0, 0, data[28], mOMoon);
    Rect deathShotR((dxPos-dRad), (dyPos-20), 40, data[24], gShot);
    
    //Create the background Stars for the Project
    int starCount = data[20];
    //set the seed for the random
    srand(data[19]);
    cout << "Seed is " << data[19] << " and the Number of Stars is " << data[20] << "\n";
    cout << "Frames count = " << frames << " and the size of the images is " << px << "x" << pz << "\n";
    unsigned char * * backBuf = new unsigned char * [pz];
    for(i = 0; i < pz; i++){
        backBuf[i] = new unsigned char [px*3];
    }
    //background
    for(i=0;i<pz;i++){
        for(j=0;j<3*px;j=j+3){
            backBuf[i][j]=1;
            backBuf[i][j+1]=1;
            backBuf[i][j+2]=1;
        }
    }
    //Draw all the stars in the whole background
    Circle xyz;
    Color randCol;
    for(int m = 0; m < starCount; m++){
        double random1 = (rand()%(starIntensityMax-starIntensityMin+1)) + starIntensityMin;
        randCol.setVal(random1, random1, random1);
        xyz.setColor(randCol);
        xyz.setRadius((rand()%(3))+2);
        xyz.setXPos((rand()%(px-1)));
        xyz.setYPos((rand()%(pz-1)));
        drawStars(backBuf, xyz, px, pz);
    }
    //draw the sun in the background as it is stationary
    drawCircle(backBuf, sun, px, pz);
    
    double fTime = difftime(time(0), sTime);
    cout << fTime << " seconds have passed in making the sun and all of the stars for the program.\n";
    cout << (starCount/fTime) << " stars drawn per second in this program.\n";
    
    //FOR LOOP for the creation of files
    for(int sw = 0; sw <= frames; sw++){
        //make name of files
        string nom = makeName(sw) + ".bmp";
        ofstream ostrm_1;
        if(sw%dFrames == 0){
            ostrm_1.open(nom.c_str(), ios::out | ios::binary);
            if(ostrm_1.fail()){
                cout << "Error.  Can't open output file " << nom << "." << endl;
                return 0;
            }
            cout << "Opening output file " << nom <<"." << endl;
        }
        //end make names of files
    
        string arg;
        if(px<=0){
            ostrm_1.close();
            return -1;
        }
        if(pz<=0){
            ostrm_1.close();
            return -1;
        }
        
        int rem;
        rem=3*px%4;
        int padding;
        if(rem==0)padding=0;
        else (padding=4-rem);
        write_bmp_header_file(ostrm_1, px, pz);
        unsigned char * * buffer = new unsigned char * [pz];
        for (i=0; i< pz; i++){
            buffer[i]= new unsigned char [px*3];
        }
        //initialize the buffer into the old one from the background
        for(i=0;i<pz;i++){
            for(j=0;j<3*px;j=j+3){
                buffer[i][j]=backBuf[i][j];
                buffer[i][j+1]=backBuf[i][j+1];
                buffer[i][j+2]=backBuf[i][j+2];
            }
        }

        //generate the planet that will later be destroyed by the death star.
        if(deathShotR.getXPos() >= (alderan.getXPos())){
            drawCircle(buffer, alderan, px, pz);
        }
        else alderanHit = true;
        
        //The Laser from the Death Star which is a rectangle.
        if(sw > (frames/12) && !alderanHit){
            drawRect(buffer, deathShotR, px, pz);
            int temp = deathShotR.getLength();
            temp += (data[17]);
            deathShotR.setLength(temp);
            temp = deathShotR.getWidth();
            //Shrink the laser as the time goes by while it is traveling.
            if(sw%20 == 0){
                deathShotR.setWidth(temp-1);
            }
            //Move the laser while expanding it so that it can become larger every time.
            deathShotR.translate(-1*data[17], 0);
        }

        //the first planet and its movement in circular motion
        pxPos = sun.getXPos() + data[5]*(cos(deg*RADCON));
        pyPos = sun.getYPos() + data[5]*(sin(deg*RADCON));
        deg += data[15];
        planet.setXPos(pxPos);
        planet.setYPos(pyPos);
        drawCircle(buffer, planet, px, pz);
        
        //SpaceShip Squadron follows elliptical orbit between the beginning of the second planet and the death star
        if(sdeg >= 0){
            sxPos = (exStart) + eX*(cos(sdeg*RADCON));
            syPos = (eyStart) + eY*(sin(sdeg*RADCON));
            starShip.setXPos(sxPos);
            starShip.setYPos(syPos);
            starShip1.setXPos(sxPos+data[22]+10);
            starShip1.setYPos(syPos+data[22]+10);
            starShip2.setXPos(sxPos-data[22]-10);
            starShip2.setYPos(syPos+data[22]+10);
            drawTShip(buffer, starShip, px, pz);
            drawTShip(buffer, starShip1, px, pz);
            drawTShip(buffer, starShip2, px, pz);
            sdeg -= data[21];
        }
        //The three SpaceShips end their elliptical orbit and enter the death star after moving for 180 degrees
        else if(starShip.getYPos() > dyPos && dStarExists == true){
            starShip.translate(0, -4*(data[21]));
            starShip1.translate(0, -4*(data[21]));
            starShip2.translate(0, -4*(data[21]));
            drawTShip(buffer, starShip, px, pz);
            drawTShip(buffer, starShip1, px, pz);
            drawTShip(buffer, starShip2, px, pz);
        }
        //2 SpaceShips Escape from the Death Star, the Third One remains trying to solve the issue at hand.
        else if(starShip2.getXPos() > 0){
            starShip1.translate(-10, 5);
            starShip2.translate(-10, 5);
            drawTShip(buffer, starShip1, px, pz);
            drawTShip(buffer, starShip2, px, pz);
        }
        
        //planet2 and its circular movement
        pTxPos = sun.getXPos() + data[7]*(cos(pdeg*RADCON));
        pTyPos = sun.getYPos() + data[7]*(sin(pdeg*RADCON));
        pdeg += data[18];
        otherPlanet.setXPos(pTxPos);
        otherPlanet.setYPos(pTyPos);
        drawCirclewRings(buffer, otherPlanet, px, pz, data[10]);
        
        //the moon and its circular movement around the first planet
        mxPos = planet.getXPos() + data[6]*(cos(mdeg*RADCON));
        myPos = planet.getYPos() + data[6]*(sin(mdeg*RADCON));
        moon.setXPos(mxPos);
        moon.setYPos(myPos);
        drawCircle(buffer, moon, px, pz);
        mdeg += data[14];
        
        //the moon of the moon and its circular motion around the moon.
        m1xPos = moon.getXPos() + data[30]*(cos(m1deg*RADCON));
        m1yPos = moon.getYPos() + data[30]*(sin(m1deg*RADCON));
        moonOfMoon.setXPos(m1xPos);
        moonOfMoon.setYPos(m1yPos);
        drawCircle(buffer, moonOfMoon, px, pz);
        m1deg += data[29];
        
        //Shots from the moon that fly every time its at the peak.
        //They travel a measured distance from the death star to the moon
        //This improves the accuracy of the shots.
        if(sw >= (pCycle/4) && dStarExists == true){
            if((sw-(pCycle/4))%(pCycle) == 0){
                moonScale = (dxPos-moon.getXPos())/(moon.getYPos()-dyPos);
                moonShotSpeed = (dxPos-moon.getXPos())/pCycle;
                rebelShot.setXPos(mxPos);
                rebelShot.setYPos(myPos);
            }
            drawCircle(buffer, rebelShot, px, pz);
            rebelShot.translate(moonScale*moonShotSpeed, -1*moonShotSpeed);
            if(rebelShot.getXPos() >= dxPos){
                rebelShot.disappear();
            }
        }
        
        //The Death Star is a massive circle in the top right of the screen.
        //The circle has a shield until it is destroyed by the first laser from the moon.
        if(sw < pCycle) drawCirclewRings(buffer, deathStar, px, pz, 1);
        else drawCircle(buffer, deathStar, px, pz);
        int dRad = deathStar.getRadius();
        if(sw > (3*frames)/4 && dRad >= 0){
            if(sw%2 == 0){
                deathStar.setColor(flashRed);
                dRad -= dRate;
                deathStar.setRadius(dRad);
            }
            else deathStar.setColor(gray);
            deathStar.setRadius(dRad);
            dStarExists = false;
            //Once the death star begins to shrink, the third spaceship can leave.
            starShip.translate(-20, 5);
            drawTShip(buffer, starShip, px, pz);
        }
        //Refresh the degree values in the case that the number of degrees and frames exceeds the max size of
        //  an integer variable.
        deg %= 360;
        mdeg %= 360;
        pdeg %= 360;

        if(sw%dFrames != 0){
            ostrm_1.close();
            continue;
        }
        
        unsigned char p_buffer[4];
        p_buffer[0]=0;
        p_buffer[1]=0;
        p_buffer[2]=0;
        p_buffer[3]=0;

        for(i=pz-1;i>=0;i--){
            ostrm_1.write ((char*)buffer[i], px*3*sizeof (unsigned char));
            ostrm_1.write ((char*)p_buffer, padding*sizeof (unsigned char));
        }
        //Erase the memory of the buffer after printing it, so that we can start over.
        for(int i = 0; i<pz;i++){
            delete[] buffer[i];
            buffer[i] = NULL;
        }
        delete[] buffer;
        ostrm_1.close();
    }
    //This outputs calculations related to time so I could measure improved efficiency.
    double oldT = fTime;
    cout << oldT << " seconds taken to make the sun and all of the stars for the program.\n";
    fTime = difftime(time(0), sTime);
    cout << (fTime - oldT) << " seconds to draw the frames.\n";
    cout << fTime << " seconds taken to complete the whole program.\n";
    cout << (frames/(fTime - oldT)) << " frames drawn per second after stars drawn.\n";
    cout << ((fTime - oldT)/frames) << " seconds to draw each frame.\n";
    return 0;
}

void drawCircle(unsigned char ** buffer, Circle cir, int px, int pz){
    Color col = cir.getColor();
    //Calculate minima and maxima for Predictive Pixel Method
    int minX = 3*((int)cir.getXPos()-cir.getRadius()-1);
    int maxX = 3*((int)cir.getXPos()+cir.getRadius()+1);
    int maxY = cir.getYPos()+cir.getRadius()+1;
    for(int i=0;i<maxY;i++){
        for(int j=minX;j<maxX;j=j+3){
            //distance formula implementation of the circle.
            double distance = sqrt(pow((i-cir.getYPos()), 2) + (pow((j/3-cir.getXPos()), 2)));
            if(distance <= cir.getRadius()){
                buffer[i][j]=col.getB();
                buffer[i][j+1]=col.getG();
                buffer[i][j+2]=col.getR();
            }
        }
    }
}
void drawStars(unsigned char ** buffer, Circle cir, int px, int pz){
    //For massive drawings at the same time like in the case of the stars, only limit the x, not y
    //Though it is slower, it makes it bypass the segmentation errors.
    int minX = 3*((int)cir.getXPos()-cir.getRadius()-1);
    int maxX = 3*((int)cir.getXPos()+cir.getRadius()+1);
    Color col = cir.getColor();
    for(int i=0;i<pz;i++){
        for(int j=minX;j<maxX;j=j+3){
            //distance formula implementation of the circle.
            double distance = sqrt(pow((i-cir.getYPos()), 2) + (pow((j/3-cir.getXPos()), 2)));
            if(distance <= cir.getRadius()){
                buffer[i][j]=col.getB();
                buffer[i][j+1]=col.getG();
                buffer[i][j+2]=col.getR();
            }
        }
    }
}
void drawRect(unsigned char ** buffer, Rect rec, int px, int pz){
    Color col = rec.getColor();
    int minX = 3*(rec.getXPos()-1);
    int maxX = 3*(rec.getXPos() + rec.getLength() +1);
    int maxY = rec.getYPos()+rec.getWidth()+1;
    for(int i=0;i<maxY;i++){
        for(int j=minX;j<maxX;j=j+3){
            //Due to the Predictive Pixel Method, I only had to have one limit in the if statement.
            if(i >= rec.getYPos()){
                buffer[i][j]=col.getB();
                buffer[i][j+1]=col.getG();
                buffer[i][j+2]=col.getR();
            }
        }
    }
}
void drawTShip(unsigned char ** buffer, TShip tie, int px, int pz){
    Color col = tie.getColor();
    int minX = 3*(tie.getXPos()-tie.getWidth()-tie.getRadius()-1);
    int maxX = 3*(tie.getXPos()+tie.getWidth()+tie.getRadius()+1);
    int maxY = tie.getYPos()+tie.getRadius()+1;
    for(int i=0;i<maxY;i++){
        for(int j=minX;j<maxX;j=j+3){
            //body
            double distance = sqrt(pow((i-tie.getYPos()), 2) + (pow((j/3-tie.getXPos()), 2)));
            if(distance <= tie.getRadius()){
                buffer[i][j]=col.getB();
                buffer[i][j+1]=col.getG();
                buffer[i][j+2]=col.getR();
            }
            //left Wing
            Rect rec = tie.getLWing();
            if(i >= rec.getYPos() && i <= rec.getYPos() + rec.getWidth() && j/3 >= rec.getXPos() && j/3 <= rec.getXPos() + rec.getLength()){
                buffer[i][j]=col.getB();
                buffer[i][j+1]=col.getG();
                buffer[i][j+2]=col.getR();
            }
            //right Wing
            Rect rec1 = tie.getRWing();
            if(i >= rec1.getYPos() && i <= rec1.getYPos() + rec1.getWidth() && j/3 >= rec1.getXPos() && j/3 <= rec1.getXPos() + rec1.getLength()){
                buffer[i][j]=col.getB();
                buffer[i][j+1]=col.getG();
                buffer[i][j+2]=col.getR();
            }
        }
    }
    
}
//Make the circle with rings
void drawCirclewRings(unsigned char ** buffer, Circle cir, int px, int pz, int rings){
    Color col = cir.getColor();
    int minX = 3*(cir.getXPos()-cir.getRadius()-1-(5*rings));
    int maxX = 3*(cir.getXPos()+cir.getRadius()+1+(5*rings));
    int maxY = cir.getYPos()+cir.getRadius()+1+(5*rings);
    for(int i=0;i<maxY;i++){
        for(int j=minX;j<maxX;j=j+3){
            double distance = sqrt(pow((i-cir.getYPos()), 2) + (pow((j/3-cir.getXPos()), 2)));
            if(distance <= cir.getRadius()){
                buffer[i][j]=col.getB();
                buffer[i][j+1]=col.getG();
                buffer[i][j+2]=col.getR();
            }
            //Define distance between planet and first ring, then continue through and add radius
            //  Without adding pixels unless its in a certain area.
            int extra = 5;
            for(int k = 0; k < rings; k++){
                if((cir.getRadius()+extra < distance) && (distance < cir.getRadius()+(extra+2))){
                    buffer[i][j]=(col.getB());
                    buffer[i][j+1]=(col.getG());
                    buffer[i][j+2]=(col.getR());
                }
                extra += 4;
            }
        }
    }
}
void write_bmp_header_file(ofstream& output_file, int px, int pz){
    unsigned short int bfType;
    bfType = 0x4D42;
    output_file.write ((char*)&bfType, sizeof (short int));
    unsigned int bfSize;
    int rem;
    rem=3*px%4;
    int padding;
    if(rem==0){
        padding=0;
    }
    else{
        padding=4-rem;
    }
    
    bfSize = 14 + 40 + (3 * px+padding) * pz;
    //	bfSize = 14 + 40 + (3 * px+padding) * pz + 2;
    output_file.write ((char*)&bfSize, sizeof (int));
    
    unsigned short int bfReserved1;
    bfReserved1 = 0;
    output_file.write ((char*)&bfReserved1, sizeof (short int));
    
    unsigned short int bfReserved2;
    bfReserved2 = 0;
    output_file .write ((char*)&bfReserved2, sizeof (short int));
    
    unsigned int bfOffsetBits;
    bfOffsetBits = 14 + 40;
    output_file.write ((char*)&bfOffsetBits, sizeof (int));
    
    unsigned int biSize;
    biSize=40;
    output_file.write ((char*)&biSize, sizeof (int));
    
    int biWidth;
    biWidth=px;
    output_file.write ((char*)&biWidth, sizeof (int));
    
    int biHeight;
    biHeight=pz;
    output_file.write ((char*)&biHeight, sizeof (int));
    
    unsigned short int biPlanes;
    biPlanes=1;
    output_file.write ((char*)&biPlanes, sizeof (short int));
    
    unsigned short int biBitCount;
    biBitCount=24;
    output_file.write ((char*)&biBitCount, sizeof (short int));
    
    unsigned int biCompression;
    // #define BI_RGB 0
    unsigned int bi_rgb = 0;
    //	biCompression=BI_RGB;
    biCompression=bi_rgb;
    output_file.write ((char*)&biCompression, sizeof (int));
    
    unsigned int biSizeImage;
    biSizeImage=0;
    output_file.write ((char*)&biSizeImage, sizeof (int));
    
    unsigned int biXPelsPerMeter;
    biXPelsPerMeter=0;
    output_file.write ((char*)&biXPelsPerMeter, sizeof (int));
    
    unsigned int biYPelsPerMeter;
    biYPelsPerMeter=0;
    output_file.write ((char*)&biYPelsPerMeter, sizeof (int));
    
    unsigned int biClrUsed;
    biClrUsed = 0;
    output_file.write ((char*)&biClrUsed, sizeof (int));   
    
    unsigned int biClrImportant;
    biClrImportant = 0;
    output_file.write ((char*)&biClrImportant, sizeof (int));   
}
int string_to_int(string s){
    istringstream strm;
    strm.str(s);
    int n=0;
    strm >> n;
    return n;
}
string makeName(int num){
    ostringstream strm;
    strm << setfill('0') << setw(4) << num;
    return strm.str();
}