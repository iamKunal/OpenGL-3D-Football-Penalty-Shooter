//
// Created by kunal on 3/3/18.
//

#ifndef FOOTBALL_PENALTY_SHOOTER_FUNCTIONALITIES_H
#define FOOTBALL_PENALTY_SHOOTER_FUNCTIONALITIES_H


#include <bits/stdc++.h>
#include <GL/glut.h>
#include "constants.h"
#include "SOIL.h"

#define DEG2GRAD(x) ((x) * PI/180.0)


using namespace std;

void handleResize(int w, int h);



struct axes{
    double x,y,z;
    double &operator[] (int);
};

struct PhysicalState {
    axes positionInitial;
    axes velocityInitial;

    axes positionCurrent;
    axes velocityCurrent;
    axes accelerationCurrent;

    double elasticity;
    double timePassed;

    PhysicalState();
};


int LoadGLTexture(char * filename);


void initialiseEverything();

void cameraPosition(axes point, double distance, double xAngle, double zAngle);

struct camera{
    double xAngle, yAngle;
    double distance;
    camera();
};
extern camera sphereCamera;

void drawHUD();


enum mode {ADJUSTING, AIMING, SHOOTING, REPLAY};

extern mode currentMode;

#endif //FOOTBALL_PENALTY_SHOOTER_FUNCTIONALITIES_H
