/* 
 * File:   Firebomb.cpp
 * Author: John
 * 
 * Created on May 5, 2013, 5:37 PM
 */

#include "Firebomb.h"
#include <cmath>

double vel = 80;

Firebomb::Firebomb(const char *filename, double xpos, double ypos, double zpos,
        double xcam, double ycam, double zcam) : Weapon(filename, xpos,
ypos, zpos, xcam, ycam, zcam) {
    this->color[0] = 1;
    this->color[1] = 0;
    this->color[2] = 0;
}

Firebomb::~Firebomb() {
}

bool Firebomb::isFirebomb() {
    return true;
}

void Firebomb::draw(double dt) {
    Weapon::draw(dt);
    if (!this->collided) {
        double dx = vel * dt*xcam;
        double dy = vel * dt*ycam;
        double dz = vel * dt*zcam;
        this->xpos += dx;
        this->ypos += dy;
        this->zpos += dz;
        for (int i = 0; i < this->tris.size(); i++) {
            this->tris.at(i)->x0 += dx;
            this->tris.at(i)->x1 += dx;
            this->tris.at(i)->x2 += dx;
            this->tris.at(i)->y0 += dy;
            this->tris.at(i)->y1 += dy;
            this->tris.at(i)->y2 += dy;
            this->tris.at(i)->z0 += dz;
            this->tris.at(i)->z1 += dz;
            this->tris.at(i)->z2 += dz;
        }
    } else {
        for (int i = 0; i < this->tris.size(); i++) {
            MeshTriangle *mt = this->tris.at(i);
            if (!mt->collided) {
                double dx = mt->ctSpd * dt * mt->ctX;
                double dy = mt->ctSpd * dt * mt->ctY;
                double dz = mt->ctSpd * dt * mt->ctZ;
                mt->x0 += dx;
                mt->y0 += dy;
                mt->z0 += dz;
                mt->x1 += dx;
                mt->y1 += dy;
                mt->z1 += dz;
                mt->x2 += dx;
                mt->y2 += dy;
                mt->z2 += dz;
            }

        }
    }

    this->t = this->t + dt;
}

void Firebomb::setCollisionTrajectories() {
    for (int i = 0; i < this->tris.size(); i++) {
        MeshTriangle *mt = this->tris.at(i);
        int half = INT_MAX / 2;
        double x = (double) (rand() - half) / INT_MAX;
        double y = (double) (rand() - half) / INT_MAX;
        double z = (double) (rand() - half) / INT_MAX;
        double mag = sqrt(x * x + y * y + z * z);
        mt->ctX = x / mag;
        mt->ctY = y / mag;
        mt->ctZ = z / mag;
        mt->ctSpd = rand() % 40;
    }
}

