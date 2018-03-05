//
// Created by kunal on 4/3/18.
//

#include "functionalities.h"
#include "shapes.h"


mode currentMode = ADJUSTING;
bool currentlyWaiting;
bool downKeys[127];

void handleResize(int w, int h) {
    //Tell OpenGL how to convert from coordinates to pixel values
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective

    //Set the camera perspective
    glLoadIdentity(); //Reset the camera
    glFrustum(-1.0 * w / h, 1.0 * w / h, -1, 1, 1.0, 400);
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

double distanceBW(axes axes1, axes axes2){
    double sum=0.0;
    double sqr;
    for (int i = 0; i < 3; ++i) {
        sqr = axes1[i] - axes2[i];
        sqr*=sqr;
        sum+=sqr;
    }
    return sqrt(sum);
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
    temp = {-20, -20, -BALL_RADIUS};
    ground.corners[0] = temp;
    temp = {-20, 20, -BALL_RADIUS};
    ground.corners[1] = temp;
    temp = {20, 20, -BALL_RADIUS};
    ground.corners[2] = temp;
    temp = {20, -20, -BALL_RADIUS};
    ground.corners[3] = temp;
    ground.color[0] = 1 / 255.0;
    ground.color[1] = 142 / 255.0;
    ground.color[2] = 14 / 255.0;


    poles[0].Type = L_POLE;
    poles[0].height = POLE_HEIGHT;
    poles[1].Type = U_POLE;
    poles[1].height = POLE_LENGTH / 2;
    poles[2].Type = R_POLE;
    poles[2].height = POLE_HEIGHT;

    temp = {0, 0, 0};
    aimArrow.start = temp;
    temp = {0, 2, 0};
    aimArrow.finish = temp;

    aimArrow.width = 0.2;


    aimArrow.zAngle = 0.0;
    aimArrow.yAngle = 0.0;
    aimArrow.length = 2.0;

    aimArrow.color[0] = 0 / 255.0;
    aimArrow.color[1] = 0 / 255.0;
    aimArrow.color[2] = 127 / 255.0;
    aimArrow.color[3] = 0.5;

}

void drawGoalPost() {

    {
        glPushMatrix();
        glTranslated(GOAL_POST_X - POLE_LENGTH / 2 + POLE_RADIUS, GOAL_POST_Y + 0, 0 - BALL_RADIUS);
        poles[0].draw();
        glPopMatrix();

        glPushMatrix();
        glTranslated(GOAL_POST_X + 0, GOAL_POST_Y + 0, POLE_HEIGHT + POLE_RADIUS - BALL_RADIUS);
        poles[1].draw();
        glPopMatrix();


        glPushMatrix();
        glTranslated(GOAL_POST_X + POLE_LENGTH / 2 - POLE_RADIUS, GOAL_POST_Y + 0, 0 - BALL_RADIUS);
        poles[2].draw();
        glPopMatrix();
    }

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


void rainBox(double alpha = 0.7) {

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

void myShear() {
//    glRotatef(-45, 0.0, 0.0, 1.0);
    float m[] = {
            1.0, 0.0, 0.0, 0.0,
            1.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
    };
    glMultMatrixf(m);
}

double powerMeter = 0.0;

void drawPowerMeter() {


    glPushMatrix();
    glPushAttrib(GL_CURRENT_BIT);

    glTranslatef(-10.0, -20.0 + powerMeter * 40, 0.0);

    glColor4f(0.1, 0.1, 0.1, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(-10.0, -0.2);
    glVertex2f(5.0, -0.2);
    glVertex2f(5.0, 0.2);
    glVertex2f(-10.0, 0.2);
    glEnd();
    glBegin(GL_TRIANGLES);

    glVertex2f(5.0, -0.4);
    glVertex2f(8.0, 0.0);
    glVertex2f(5.0, 0.4);


    glEnd();
//
//    glTranslatef(36.0, 0, 0);
//    glScalef(-1.0, 1.0, 1.0);
//    glColor4f(0.1, 0.1, 0.1, 1.0);
//    glBegin(GL_QUADS);
//    glVertex2f(-10.0, -0.2);
//    glVertex2f(5.0, -0.2);
//    glVertex2f(5.0, 0.2);
//    glVertex2f(-10.0, 0.2);
//    glEnd();
//    glBegin(GL_TRIANGLES);
//
//    glVertex2f(5.0, -0.4);
//    glVertex2f(8.0, 0.0);
//    glVertex2f(5.0, 0.4);
//    glEnd();
//
//    glColor3f(0.3, 0.3, 1.0);
//    glTranslatef(18, 0, 0);
//    glBegin(GL_LINES);
//    glVertex2f(-10, 0);
//    glVertex2f(10.0, 0);
//    glEnd();


    glPopAttrib();
    glPopMatrix();
}


void drawHUD() {
    {   //HUD Render
        glMatrixMode(GL_PROJECTION);
        glPushAttrib(GL_CURRENT_BIT);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(-100.0, 100.0, -100.0, 100.0);       //glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT)
        glMatrixMode(GL_MODELVIEW);
//glPushMatrix();        ----Not sure if I need this
        glLoadIdentity();
        glDisable(GL_CULL_FACE);

        glClear(GL_DEPTH_BUFFER_BIT);

        if (currentMode == POWERING) {   //Power Bar
            glPushMatrix();

            glTranslatef(90, 0, 0);


            glScalef(0.3, 4.0, 1.0);

            drawPowerMeter();


            rainBox();
            glScalef(1.0, -1.0, 0.0);
            rainBox();

            glPopMatrix();
        }
// Making sure we can render 3d again
        glMatrixMode(GL_PROJECTION);
        glPopAttrib();
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    }
}
