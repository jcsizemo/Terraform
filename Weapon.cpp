/* 
 * File:   Weapon.cpp
 * Author: John
 * 
 * Created on May 4, 2013, 3:03 AM
 */

#include "Weapon.h"

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
    
}