/* 
 * File:   Light.cpp
 * Author: John
 * 
 * Created on May 14, 2013, 7:36 PM
 * 
 * Light class holding values used for phong shading
 */

#include "Light.h"

// init light based on position and rgb values. used in phong shading for the
// interactive structure meshes
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

