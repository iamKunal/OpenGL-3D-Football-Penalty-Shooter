//
// Created by kunal on 4/3/18.
//

#include <GL/glut.h>
#include "shapes.h"
#include <bits/stdc++.h>
#include "functionalities.h"




void FlatSurface :: draw(){
        glPushAttrib(GL_CURRENT_BIT);
        glColor3fv(color);
        glBegin(GL_QUADS);
        for (int i = 0; i < 4; ++i) {
            glVertex3f(corners[i].x, corners[i].y, corners[i].z);
        }
    glEnd();
    glPopAttrib();
}

FlatSurface ground;
