//
// Created by kunal on 3/3/18.
//

#ifndef FOOTBALL_PENALTY_SHOOTER_SHAPES_H
#define FOOTBALL_PENALTY_SHOOTER_SHAPES_H
#include "functionalities.h"

//void drawField() {
//    glPushAttrib(GL_CURRENT_BIT);
////    glPushAttrib(GL_TEXTURE);
//    glBegin(GL_QUADS);
//    glColor3f(1/255.0, 142/255.0, 14/255.0);
////    GLuint texture;
////    texture = LoadGLTexture("./resources/grass.bmp");
////    glBindTexture(GL_TEXTURE_2D, texture);
////    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
////    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//    glVertex3f(-10, -10, 0);
//    glVertex3f(10, -10, 0);
//    glVertex3f(10, 10, 0);
//    glVertex3f(-10, 10, 0);
//    glEnd();
//    glPopAttrib();
//}
enum objectType{WALL, R_POLE, L_POLE, U_POLE};

class RealObject{
public:
    GLfloat color[4];
    objectType Type;
};


class FlatSurface: public RealObject{
public:
    axes corners[4];
    void draw();
};

class PoleSurface: public RealObject{
public:
    PoleSurface();
    axes base;
    double radius;
    double height;
    void draw();
};

class FlatArrow{
public:
    double width;
    axes start;
    axes finish;
    double yAngle;
    double zAngle;
    GLfloat color[4];
    double length;
    void drawWithPoints();
    void drawWithAngles();
};

class Defender{
public:
    double width;
    double height;
    double armRot;
    GLfloat color[4];

    PhysicalState state;
    void acceleration();
    void draw();
};

extern FlatArrow aimArrow;


extern FlatSurface ground;

extern PoleSurface poles[3];
extern RealObject allObjects[];
extern Defender defender;

#endif //FOOTBALL_PENALTY_SHOOTER_SHAPES_H

