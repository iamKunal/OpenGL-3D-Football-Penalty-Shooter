//
// Created by kunal on 4/3/18.
//

#include "functionalities.h"
#include "shapes.h"


mode currentMode = ADJUSTING;


void handleResize(int w, int h) {
    //Tell OpenGL how to convert from coordinates to pixel values
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective

    //Set the camera perspective
    glLoadIdentity(); //Reset the camera
    glFrustum(-1.0 * w / h, 1.0 * w / h, -1, 1, 1, 200);
    glMatrixMode(GL_MODELVIEW);
//    gluPerspective(45.0,                  //The camera angle
//                   (double) w / (double) h, //The width-to-height ratio
//                   1.0,                   //The near z clipping coordinate
//                   200.0);                //The far z clipping coordinate
}

double &axes::operator[](int index) {
    switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            cout << "Out of Bound Axis!" << endl;
            exit(1);
    }
}


PhysicalState::PhysicalState() {
    positionInitial = positionCurrent = velocityInitial = velocityCurrent = accelerationCurrent = {0.0, 0.0, 0.0};
    timePassed = 0;
    elasticity = 1.0;
}

int LoadGLTexture(char *filename) {
    GLuint texture = SOIL_load_OGL_texture
            (
                    filename,
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_INVERT_Y
            );


    if (texture == 0)
        return false;


    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
}


void initialiseEverything() {
    ground.Type = WALL;
    axes temp;
    temp = {-10, -10, -BALL_RADIUS};
    ground.corners[0] = temp;
    temp = {-10, 10, -BALL_RADIUS};
    ground.corners[1] = temp;
    temp = {10, 10, -BALL_RADIUS};
    ground.corners[2] = temp;
    temp = {10, -10, -BALL_RADIUS};
    ground.corners[3] = temp;
    ground.color[0] = 1 / 255.0;
    ground.color[1] = 142 / 255.0;
    ground.color[2] = 14 / 255.0;
}


void cameraPosition(axes point, double distance, double zAngle, double xAngle) {
    gluLookAt(point.x + distance * (cos(DEG2GRAD(zAngle)) * cos(DEG2GRAD(xAngle))),
              point.y + distance * (cos(DEG2GRAD(zAngle)) * sin(DEG2GRAD(xAngle))),
              point.z + distance * sin(DEG2GRAD(zAngle)), point.x, point.y, point.z, 0, 0, 1);

}

camera::camera() {
    xAngle = yAngle = 0.0;
    distance = 5.0;
}

camera sphereCamera;


void rainBox(double alpha=0.7) {

    glBegin(GL_QUADS);
    glColor4f(1.0f, 0.0f, 0.0, alpha); //RED
    glVertex2f(-10.0, -20.0);
    glVertex2f(10.0, -20.0);

    glColor4f(1.0f, 1.0f, 0.0, alpha); //YELLOW
    glVertex2f(10.0, -10.0);
    glVertex2f(-10.0, -10.0);

    glVertex2f(-10.0, -10.0);
    glVertex2f(10.0, -10.0);


    glColor4f(0.0f, 1.0f, 0.0, alpha); //GREEN
    glVertex2f(10.0, 0.0);
    glVertex2f(-10.0, 0.0);
    glEnd();
}

void drawHUD() {
    {   //HUD Render
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(-100.0, 100.0, -100.0, 100.0);       //glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT)
        glMatrixMode(GL_MODELVIEW);
//glPushMatrix();        ----Not sure if I need this
        glLoadIdentity();
        glDisable(GL_CULL_FACE);

        glClear(GL_DEPTH_BUFFER_BIT);

        if (currentMode == AIMING){   //Power Bar
            glPushMatrix();

            glTranslatef(90, 0, 0);
            glScalef(0.3, 4.0, 1.0);


            rainBox();
            glScalef(1.0, -1.0, 0.0);
            rainBox();

            glPopMatrix();
        }
// Making sure we can render 3d again
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    }
}