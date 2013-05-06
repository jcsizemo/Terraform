/* 
 * File:   Weapon.cpp
 * Author: John
 * 
 * Created on May 4, 2013, 3:03 AM
 */

#include "Weapon.h"
#include <cmath>

Weapon::Weapon(const char *filename, double xpos, double ypos, double zpos,
        double xcam, double ycam, double zcam) : Mesh(filename, xpos, ypos, zpos) {
    this->xcam = xcam;
    this->ycam = ycam;
    this->zcam = zcam;
    this->collided = false;
    this->initCollision = true;
    this->t = 0;
}

Weapon::~Weapon() {
}

void Weapon::draw(double dt) {
    Mesh::draw(dt);
}

void Weapon::setCollisionTrajectories() {
    for (int i = 0; i < this->tris.size(); i++) {
        MeshTriangle *mt = this->tris.at(i);
        int half = INT_MAX / 2;
        double x = (double) (rand() - half) / INT_MAX;
        double y = (double) (rand() - half) / INT_MAX;
        double z = (double) (rand() - half) / INT_MAX;
        double mag = sqrt(x*x + y*y + z*z);
        mt->ctX = x/mag;
        mt->ctY = y/mag;
        mt->ctZ = z/mag;
        mt->ctSpd = rand() % 40;
    }
}