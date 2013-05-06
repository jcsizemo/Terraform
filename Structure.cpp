/* 
 * File:   Structure.cpp
 * Author: John
 * 
 * Created on May 5, 2013, 7:03 PM
 */

#include "Structure.h"

Structure::Structure(const char* filename, double xpos, double ypos, 
        double zpos, double *color) : Mesh(filename,xpos,ypos,zpos) {
    this->color[0] = color[0];
    this->color[1] = color[1];
    this->color[2] = color[2];
}

Structure::~Structure() {
}

void Structure::draw(double dt) {
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < this->tris.size(); i++) {
        MeshTriangle *tri = tris.at(i);
        if (tri->collided) {
            glColor3d(1,1,1);
        }
        else {
            glColor3dv(this->color);
        }
        glVertex3f(tri->x0,tri->y0,tri->z0);
        glVertex3f(tri->x1,tri->y1,tri->z1);
        glVertex3f(tri->x2,tri->y2,tri->z2);
    }
    glEnd();
    glPopMatrix();
    glColor3d(0,0,0);
}

