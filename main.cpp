//
// Created by kunal on 3/3/18.
//
#include <GL/glut.h>
#include <bits/stdc++.h>
#include "constants.h"
#include "functionalities.h"
#include "shapes.h"

using namespace std;


void drawBox(float boxSize) {
    float drawSize = boxSize / 2;
    glBegin(GL_QUADS);
    glVertex3f(-drawSize, -drawSize, drawSize);
    glVertex3f(drawSize, -drawSize, drawSize);
    glVertex3f(drawSize, drawSize, drawSize);
    glVertex3f(-drawSize, drawSize, drawSize);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(drawSize, -drawSize, drawSize);
    glVertex3f(drawSize, -drawSize, -drawSize);
    glVertex3f(drawSize, drawSize, -drawSize);
    glVertex3f(drawSize, drawSize, drawSize);
    glEnd();


    glBegin(GL_QUADS);
    glVertex3f(-drawSize, drawSize, -drawSize);
    glVertex3f(drawSize, drawSize, -drawSize);
    glVertex3f(drawSize, -drawSize, -drawSize);
    glVertex3f(-drawSize, -drawSize, -drawSize);
    glEnd();
}


PhysicalState sphere;

void getCurrentAcceleration(PhysicalState &p) {
    double k = 10;
    for (int i = 0; i < 3; ++i) {
        p.accelerationCurrent[i] = -k * p.positionCurrent[i];
    }
}

void updatePos(PhysicalState &p, double t) {
    p.timePassed += t;
    getCurrentAcceleration(p);
    for (int i = 0; i < 3; ++i) {
        p.positionCurrent[i] = p.velocityCurrent[i] * t + 0.5 * p.accelerationCurrent[i] * t * t + p.positionCurrent[i];
        p.velocityCurrent[i] = p.velocityCurrent[i] + p.accelerationCurrent[i] * t;
    }
}

void updatePosCallBack(int _) {
    float fps = 60;

    updatePos(sphere, 1.0 / fps);
    glutTimerFunc(100 / fps, updatePosCallBack, 0);
}

double cameraAngle[3];

double translations[3];

void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
    glLoadIdentity(); //Reset the drawing perspective
    glTranslatef(translations[0], translations[1], translations[2]);
    glTranslatef(0.0f, 0.0f, -5.0f); //Move forward 5 units
    glRotatef(90, 1.0, 0, 0);
    glRotatef(cameraAngle[0], 1.0, 0.0, 0.0);
    glRotatef(cameraAngle[1], 0.0, 1.0, 0.0);
    glRotatef(cameraAngle[2], 0.0, 0.0, 1.0);

    glPushMatrix();
    glTranslatef(sphere.positionCurrent.x, sphere.positionCurrent.y, sphere.positionCurrent.z);
    glutWireSphere(0.2, 20, 20);
    glPopAttrib();
//    drawBox(0.3);

    glPopMatrix();

    glutSwapBuffers();
    glutPostRedisplay();
}

void update(int _) {
    float increment = 0.0;
    glutPostRedisplay();
}

void update_callback(int _) {
    update(_);
    glutTimerFunc(25, update_callback, 0);
}

void rotateAbout(int axes, int direction) {
    cameraAngle[axes - 1] += direction * 1;
}


void handleKeypress(unsigned char key, //The key that was pressed
                    int x, int y) {    //The current mouse coordinates
    switch (key) {
        case '+':
            translations[2] += 0.05f;
            break;
        case '-':
            translations[2] += -0.05f;
            break;
        case ' ':
            updatePosCallBack(0);
            break;
        case 27: //Escape key
            exit(0); //Exit the program
    }
}

void handleSpecialKeypress(int key, int x, int y){

    switch (key) {
        case GLUT_KEY_UP:
            rotateAbout(1, 1);
            break;
        case GLUT_KEY_DOWN:
            rotateAbout(1, -1);
            break;
        case GLUT_KEY_LEFT:
            rotateAbout(3, -1);
            break;
        case GLUT_KEY_RIGHT:
            rotateAbout(3, 1);
            break;
    }
}

void myInit(void) {
    glClearColor(137/255.0, 206/255.0, 255/255.0, 0);
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
}

int main(int argc, char *argv[]) {
    sphere.positionInitial.x = sphere.positionCurrent.x = -1.0;


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow(WINDOW_NAME);
    glutFullScreen();
    glutReshapeFunc(handleResize);

    glutKeyboardFunc(handleKeypress);
    glutSpecialFunc(handleSpecialKeypress);

    glutDisplayFunc(draw);
    myInit();

//    glutTimerFunc(25, update_callback, 0);
    glutMainLoop();

    return 0;
}