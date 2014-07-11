/* 
 * File:   Structure.h
 * Author: John
 * 
 * Class representing a drawable
 * object in the scene which can be interacted with.
 *
 * Created on May 5, 2013, 7:03 PM
 */

#ifndef STRUCTURE_H
#define	STRUCTURE_H

#include "Mesh.h"
#include "Light.h"

class Mesh;
class ParticleMachine;
class Light;

// subclass of Mesh
class Structure : public Mesh {
public:
    // mesh file and mesh position
    Structure(const char* filename, double xpos, double ypos, 
            double zpos);
    virtual ~Structure();
    // draw function used to draw the mesh and do Phong shading
    void draw(double dt, vector<Light*> *lights);
    // revive function used to display burnt mesh triangles
    void revive(void);
private:

};

#endif	/* STRUCTURE_H */

