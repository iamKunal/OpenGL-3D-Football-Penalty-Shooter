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
enum objectType{WALL, POLE};

class RealObject{
public:
    double distance;
    objectType Type;
    axes position;
};


class FlatSurface: public RealObject{
public:
    GLfloat color[4];
    axes corners[4];
    void draw();
};

extern FlatSurface ground;


#endif //FOOTBALL_PENALTY_SHOOTER_SHAPES_H

