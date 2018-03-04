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


double cameraAngle[3];

double translations[3];

PhysicalState sphere;


void getCurrentAcceleration(PhysicalState &p) {
//    double k = 10;
    p.accelerationCurrent[2] = -9.8;
}

void updatePos(PhysicalState &p, double t) {
    p.timePassed += t;
    getCurrentAcceleration(p);


    {   // Gravity and ground bouncing effects
        for (int i = 0; i < 3; ++i) {
            p.positionCurrent[i] =
                    p.velocityCurrent[i] * t + 0.5 * p.accelerationCurrent[i] * t * t + p.positionCurrent[i];
            p.velocityCurrent[i] = p.velocityCurrent[i] + p.accelerationCurrent[i] * t;
        }
        if (p.positionCurrent[2] <= 0) {
            p.positionCurrent[2] = 0;
            p.velocityCurrent[2] = -p.velocityCurrent[2];
            for (int i = 0; i < 3; ++i) {
                p.velocityCurrent[i] = p.elasticity * p.velocityCurrent[i];
            }
        }
        for (int i = 0; i < 3; ++i) {
            if (fabs(p.velocityCurrent[i]) <= THRESHOLD_ZERO) {
                p.velocityCurrent[i] = 0;
            }
        }
        if (fabs(p.positionCurrent[2]) <= THRESHOLD_ZERO) {
            p.positionCurrent[2] = 0;
        }
    }

}

void updatePosCallBack(int _) {
    float fps = 60;

    updatePos(sphere, 1.0 / fps);
    glutTimerFunc(100 / fps, updatePosCallBack, 0);
}

void draw() {
    glLoadIdentity(); //Reset the drawing perspective
//    glMatrixMode(GL_PROJECTION);
    cameraPosition(sphere.positionCurrent, sphereCamera.distance, sphereCamera.xAngle, sphereCamera.yAngle);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
//    glScalef(-1.0f, -1.0f, 1.0f);
//    glTranslatef(0, 0, 0);
//    glTranslatef(translations[0], translations[1], translations[2]);

//    glutSolidSphere(BALL_RADIUS, 20, 20);

//    glRotatef(cameraAngle[0], 1.0, 0.0, 0.0);
//    glRotatef(cameraAngle[1], 0.0, 1.0, 0.0);
//    glRotatef(cameraAngle[2], 0.0, 0.0, 1.0);

    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(5, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 5, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 5);
    glEnd();




////    glTranslatef(sphere.positionCurrent.x, sphere.positionCurrent.y, sphere.positionCurrent.z-20.0f);
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(sphere.positionCurrent.x, sphere.positionCurrent.y, sphere.positionCurrent.z);

//    glRotatef(90, 0,0,1);

    glutWireSphere(BALL_RADIUS, 20, 20);
//    drawBox(0.3);

    glPopMatrix();
    ground.draw();

//    drawField();

    drawHUD();


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
    if (currentMode == ADJUSTING || currentMode == REPLAY) {
        switch (key) {
            case '+':
                sphereCamera.distance -= 0.1f;
                break;
            case '-':
                sphereCamera.distance += 0.1f;
                break;
            case ' ':
                currentMode = AIMING;
                glutPostRedisplay();
                break;
            case 27: //Escape key
                exit(0); //Exit the program
        }
    }
    if (currentMode == AIMING) {
        switch (key) {
            case '+':
                sphereCamera.distance -= 0.1f;
                break;
            case '-':
                sphereCamera.distance += 0.1f;
                break;
            case ' ':
                currentMode = AIMING;
                glutPostRedisplay();
                break;
            case 27: //Escape key
                currentMode = ADJUSTING;
        }
    }
}

void handleSpecialKeypress(int key, int x, int y) {
    if (currentMode == ADJUSTING || currentMode == REPLAY) {
        switch (key) {
            case GLUT_KEY_UP:
                sphereCamera.xAngle += 1.0f;
                break;
            case GLUT_KEY_DOWN:
                sphereCamera.xAngle -= 1.0f;
                break;
            case GLUT_KEY_LEFT:
                sphereCamera.yAngle -= 1.0f;
                break;
            case GLUT_KEY_RIGHT:
                sphereCamera.yAngle += 1.0f;
                break;
        }
    }
    if (currentMode == AIMING) {
        switch (key) {
            case GLUT_KEY_UP:
                sphereCamera.xAngle += 1.0f;
                break;
            case GLUT_KEY_DOWN:
                sphereCamera.xAngle -= 1.0f;
                break;
            case GLUT_KEY_LEFT:
                sphereCamera.yAngle -= 1.0f;
                break;
            case GLUT_KEY_RIGHT:
                sphereCamera.yAngle += 1.0f;
                break;
        }
    }
}

void myInit(void) {
    glClearColor(137 / 255.0, 206 / 255.0, 255 / 255.0, 0);
//    glOrtho(0, WIDTH, 0, HEIGHT, 0, 500);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
//    glDisable(GL_LIGHTING);

}

int main(int argc, char *argv[]) {
    initialiseEverything();
    sphere.positionInitial.x = sphere.positionCurrent.x = 0.0;
    sphere.velocityCurrent[0] = sphere.velocityInitial[0] = sphere.velocityCurrent[1] = sphere.velocityInitial[1] = sphere.velocityCurrent[2] = sphere.velocityInitial[2] = 3;

    sphere.elasticity = 0.9;
    translations[2] = -10.0f;


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