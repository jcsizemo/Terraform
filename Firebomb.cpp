/* 
 * File:   Firebomb.cpp
 * Author: John
 * 
 * Created on May 5, 2013, 5:37 PM
 */

#include "Firebomb.h"

double vel = 50;

Firebomb::Firebomb(const char *filename, double xpos, double ypos, double zpos,
        double xcam, double ycam, double zcam) : Weapon(filename, xpos,
ypos, zpos, xcam, ycam, zcam) {
    this->color[0] = 1;
    this->color[1] = 0;
    this->color[2] = 0;
}

Firebomb::~Firebomb() {
}

void Firebomb::draw(double dt) {
    Weapon::draw(dt);
    if (!this->hitSomething) {
        double dx = vel * dt*xcam;
        double dy = vel * dt*ycam;
        double dz = vel * dt*zcam;
        this->xpos += dx;
        this->ypos += dy;
        this->zpos += dz;
        for (int i = 0; i < this->verts.size(); i += 3) {
            verts.at(i) += dx;
            verts.at(i + 1) += dy;
            verts.at(i + 2) += dz;
        }
    }

    this->t = this->t + dt;
}

