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
    glColor3dv(this->color);
    Mesh::draw(dt);
    glColor3d(0,0,0);
    glPopMatrix();
}

