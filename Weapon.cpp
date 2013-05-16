/* 
 * File:   Weapon.cpp
 * Author: John
 * 
 * Created on May 4, 2013, 3:03 AM
 * 
 * General purpose Weapon class used for the Firebomb and Water balloon.
 */

#include "Weapon.h"

// mesh file, position, and direction
Weapon::Weapon(const char *filename, double xpos, double ypos, double zpos,
        double xcam, double ycam, double zcam) : Mesh(filename, xpos, ypos, zpos) {
    this->xcam = xcam;
    this->ycam = ycam;
    this->zcam = zcam;
    this->collided = false;
    this->initCollision = true;
    //lifespan of weapon
    this->t = 0;
}

Weapon::~Weapon() {
}

// draw mesh
void Weapon::draw(double dt) {
    Mesh::draw(dt);
}

// the following two functions are overriden by subclasses to define different
// behaviors
void Weapon::setCollisionTrajectories() {
    
}

bool Weapon::isFirebomb() {
    
}