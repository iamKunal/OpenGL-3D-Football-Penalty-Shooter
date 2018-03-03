//
// Created by kunal on 3/3/18.
//

#ifndef FOOTBALL_PENALTY_SHOOTER_FUNCTIONALITIES_H
#define FOOTBALL_PENALTY_SHOOTER_FUNCTIONALITIES_H


#include <bits/stdc++.h>
#include "constants.h"
#include "SOIL.h"
using namespace std;

void handleResize(int w, int h) {
    //Tell OpenGL how to convert from coordinates to pixel values
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective

    //Set the camera perspective
    glLoadIdentity(); //Reset the camera
    gluPerspective(45.0,                  //The camera angle
                   (double) w / (double) h, //The width-to-height ratio
                   1.0,                   //The near z clipping coordinate
                   200.0);                //The far z clipping coordinate
}



struct axes {
    double x, y, z;
    double &operator[] (int index){
        switch(index){
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            default:
                cout<<"Out of Bound Axis!"<<endl;
                exit(1);
        }
    }
};

struct PhysicalState {
    axes positionInitial;
    axes velocityInitial;

    axes positionCurrent;
    axes velocityCurrent;
    axes accelerationCurrent;

    double timePassed;

    PhysicalState() {
        positionInitial = positionCurrent = velocityInitial = velocityCurrent = accelerationCurrent = {0.0, 0.0, 0.0};
        timePassed = 0;
    }
};


int LoadGLTexture(char * filename)
{
    GLuint texture = SOIL_load_OGL_texture
            (
                    filename,
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_INVERT_Y
            );


    if(texture == 0)
        return false;


    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    return texture;
}


#endif //FOOTBALL_PENALTY_SHOOTER_FUNCTIONALITIES_H
