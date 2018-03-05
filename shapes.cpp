//
// Created by kunal on 4/3/18.
//

#include <GL/glut.h>
#include "shapes.h"
#include <bits/stdc++.h>
#include "functionalities.h"


void FlatSurface::draw() {
    glPushAttrib(GL_CURRENT_BIT);
    glColor3fv(color);
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; ++i) {
        glVertex3d(corners[i].x, corners[i].y, corners[i].z);
    }
    glEnd();
    glPopAttrib();
}

FlatSurface ground;

void PoleSurface::draw() {
    glPushAttrib(GL_CURRENT_BIT);
    GLUquadric *quadric = gluNewQuadric();


    if (Type == U_POLE) {
//        glColor3f(0.0, 0.0, 0.0);
//        glBegin(GL_LINES);
//        glVertex3d(height, 0, 0);
//        glVertex3d(-height, 0, 0);
//        glEnd();
        glTranslated(radius, 0.0, radius);
        glRotatef(180, 1, 0, 0);
        {


            glPushMatrix();
            glPushAttrib(GL_CURRENT_BIT);
            glColor4fv(color);
            glTranslated(-radius, 0, radius);
            glRotatef(-90, 0, 1, 0);
            gluCylinder(quadric, radius, radius, height - radius, 20, 10);
            glPopMatrix();

            glTranslated(-height - 2 * radius, 0, 0);
            glPushMatrix();
            glRotatef(90, 1, 0, 0);
            myShear();
            glRotatef(-90, 1, 0, 0);
            glRotatef(90, 0, 1, 0);
            glTranslated(-radius, 0.0, 0.0);
            glColor4fv(color);
            gluCylinder(quadric, radius, radius, 2 * radius, 20, 10);
            glPopMatrix();


            glTranslated(height, 0, 0);
            glScalef(-1.0, 1.0, 1.0);
            glPushMatrix();
            glPushAttrib(GL_CURRENT_BIT);
            glColor4fv(color);
            glTranslated(-radius, 0, radius);
            glRotatef(-90, 0, 1, 0);
            gluCylinder(quadric, radius, radius, height - radius, 20, 10);
            glPopMatrix();

            glTranslated(-height - 2 * radius, 0, 0);
            glPushMatrix();
            glRotatef(90, 1, 0, 0);
            myShear();
            glRotatef(-90, 1, 0, 0);
            glRotatef(90, 0, 1, 0);
            glTranslated(-radius, 0.0, 0.0);
            glColor4fv(color);
            gluCylinder(quadric, radius, radius, 2 * radius, 20, 10);
            glPopMatrix();
        }
    } else if (Type == R_POLE || Type == L_POLE) {
        if (Type == L_POLE) {
            glScalef(-1.0, 1.0, 1.0);
        }
        glRotatef(90, 0, 1, 0);
        glTranslated(0, 0, 2 * radius);
        glRotatef(180, 1, 0, 0);
//        glColor3f(0.0, 0.0, 0.0);
//        glBegin(GL_LINES);
//        glVertex3d(0, 0, 0);
//        glVertex3d(-height, 0, 0);
        glEnd();
        {

            glPushMatrix();
            glPushAttrib(GL_CURRENT_BIT);
            glColor4fv(color);
            glTranslated(0, 0, radius);
            glRotatef(-90, 0, 1, 0);
            gluCylinder(quadric, radius, radius, height, 20, 10);
            glPopMatrix();

            glTranslated(-height - 2 * radius, 0, 0);
            glPushMatrix();
            glRotatef(90, 1, 0, 0);
            myShear();
            glRotatef(-90, 1, 0, 0);
            glRotatef(90, 0, 1, 0);
            glTranslated(-radius, 0.0, 0.0);
            glColor4fv(color);
            gluCylinder(quadric, radius, radius, 2 * radius, 20, 10);
            glPopMatrix();

        }

    }
    glPopMatrix();
    glPopAttrib();
}

PoleSurface::PoleSurface() {
    radius = POLE_RADIUS;
    color[0] = color[1] = color[2] = 1.0;
    color[3] = 1.0;
}


void FlatArrow::drawWithPoints() {
    axes vector;
    for (int i = 0; i < 3; ++i) {
        vector[i] = finish[i] - start[i];
    }
    double rot;
    rot = GRAD2DEG(acos((vector.y * vector.y) /
                        (sqrt(vector.y * vector.y) *
                         sqrt(vector.x * vector.x + vector.y * vector.y))));
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();

    glRotatef(-rot, 0, 0, 1);

    rot = GRAD2DEG(acos((vector.x * vector.x + vector.y * vector.y) /
                        (sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z) *
                         sqrt(vector.x * vector.x + vector.y * vector.y))));

    glRotatef(-rot, -vector.y, vector.x, 0);

    glTranslated(start.x, 0, start.z);
    glColor4fv(color);
    glBegin(GL_QUADS);
    glVertex3f(-width / 2, start.y, 0);
    glVertex3f(width / 2, start.y, 0);
    glVertex3f(width / 2, finish.y - 2 * width / vector.y, 0);
    glVertex3f(-width / 2, finish.y - 2 * width / vector.y, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(-width, finish.y - 2 * width / vector.y, 0);
    glVertex3f(width, finish.y - 2 * width / vector.y, 0);
    glVertex3f(0, finish.y, 0);
    glEnd();

    glPopMatrix();
    glPopAttrib();

}

void FlatArrow::drawWithAngles() {

    axes vector;
    for (int i = 0; i < 3; ++i) {
        vector[i] = finish[i] - start[i];
    }
    double rot;
    rot = yAngle;
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();

    glRotatef(-rot, 0, 0, 1);

    rot = zAngle;

    glRotatef(rot, cos(DEG2GRAD(rot)), 0, 0);

    glTranslated(start.x, 0, start.z);
    glColor4fv(color);
    glBegin(GL_QUADS);
    glVertex3f(-width / 2, start.y, 0);
    glVertex3f(width / 2, start.y, 0);
    glVertex3f(width / 2, length - 2 * width / vector.y, 0);
    glVertex3f(-width / 2, length - 2 * width / vector.y, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(-width, length - 2 * width / vector.y, 0);
    glVertex3f(width, length - 2 * width / vector.y, 0);
    glVertex3f(0, length, 0);
    glEnd();

    glPopMatrix();
    glPopAttrib();
}

FlatArrow aimArrow;

PoleSurface poles[3];


RealObject allObjects[] = {poles[0], poles[1], poles[2]};