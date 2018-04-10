//
// Created by kunal on 3/3/18.
//

#ifndef FOOTBALL_PENALTY_SHOOTER_FUNCTIONALITIES_H
#define FOOTBALL_PENALTY_SHOOTER_FUNCTIONALITIES_H


#include <bits/stdc++.h>
#include <GL/glut.h>
#include "constants.h"
#include "SOIL.h"
using namespace std;
#define DEG2GRAD(x) ((x) * PI/180.0)

#define GRAD2DEG(x) ((x) * 180.0/PI)
using namespace std;

extern unsigned int Tries, Goals;

void handleResize(int w, int h);


struct axes {
    double x, y, z;

    double &operator[](int);
};

double distanceBW(axes axes1, axes axes2);

struct PhysicalState {
    axes positionInitial;
    axes velocityInitial;

    axes positionCurrent;
    axes velocityCurrent;
    axes accelerationCurrent;

    double elasticity;
    double timePassed;

    PhysicalState();
    friend ostream &operator << (ostream &out, PhysicalState &p);
};

bool isItGoal(PhysicalState ball);

int LoadGLTexture(char *filename);

void updateDefenderPosition(int);

void initialiseEverything();

void initialiseEverythingCallback(int _);


void drawGoalPost();

void cameraPosition(axes point, double distance, double xAngle, double zAngle);

struct camera {
    double zAngle, xAngle;
    double distance;

    camera();
};

extern camera sphereCamera;

void myShear();

void drawHUD();


enum mode {
    ADJUSTING, AIMING, POWERING, SHOOTING, HELP, NONE
};

void goalAnimateCallBack(int _=0);
void backgroundMusicPlayer(int);


extern double powerMeter;

void drawPowerMeter();

int convertToTexture(const char * filename);
GLuint loadTextureFile(const char * filename);
GLuint convertAndLoadTexture(const char* filename);

void start2DTexture(GLuint texture, bool lightingDisabled = true);
void end2DTexture(bool lightingDisabled = true);


extern mode currentMode;

extern bool currentlyWaiting;
extern bool stopEverything;

extern bool downKeys[127];

extern PhysicalState sphere, *determineSphere;


extern bool scoredGoal;

extern int goalCount, totalTries;

void drawBitmapText(const char *string,float x,float y);

extern int mouseX, mouseY;

extern bool firstTime;
enum alignment {
    LEFT, RIGHT, CENTER
};
extern GLuint groundTexture, defenderTexture, leftArm, rightArm, font, ads;
extern vector<float> currentTextColor;
float writeText(string text, int texture, alignment align = LEFT);
float writeMultiLineText(string text, int texture, alignment align = LEFT);
void drawChalkLines();

void showMsg();
void rotateMsg(int _);

extern axes toLookAt;
#endif //FOOTBALL_PENALTY_SHOOTER_FUNCTIONALITIES_H
