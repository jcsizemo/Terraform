/* 
 * File:   Structure.h
 * Author: John
 *
 * Created on May 5, 2013, 7:03 PM
 */

#ifndef STRUCTURE_H
#define	STRUCTURE_H

#include "Mesh.h"

class Mesh;
class ParticleMachine;

class Structure : public Mesh {
public:
    Structure(const char* filename, double xpos, double ypos, 
            double zpos, double *color);
    virtual ~Structure();
    double color[3];
    void draw(double dt);
private:

};

#endif	/* STRUCTURE_H */

