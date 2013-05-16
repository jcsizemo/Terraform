/* 
 * File:   Structure.h
 * Author: John
 *
 * Created on May 5, 2013, 7:03 PM
 */

#ifndef STRUCTURE_H
#define	STRUCTURE_H

#include "Mesh.h"
#include "Light.h"
#include <cmath>

class Mesh;
class ParticleMachine;
class Light;

class Structure : public Mesh {
public:
    Structure(const char* filename, double xpos, double ypos, 
            double zpos);
    virtual ~Structure();
    void draw(double dt, vector<Light*> *lights);
    void revive(void);
private:

};

#endif	/* STRUCTURE_H */

