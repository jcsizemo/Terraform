/* 
 * File:   Light.cpp
 * Author: John
 * 
 * Created on May 14, 2013, 7:36 PM
 */

#include "Light.h"

Light::Light(double xpos, double ypos, double zpos, 
        double r, double g, double b) {
    this->xpos = xpos;
    this->ypos = ypos;
    this->zpos = zpos;
    this->r = r;
    this->g = g;
    this->b = b;
}

Light::~Light() {
}

