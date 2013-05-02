/* 
 * File:   MeshTriangle.h
 * Author: John
 *
 * Created on May 1, 2013, 8:28 PM
 */

#ifndef MESHTRIANGLE_H
#define	MESHTRIANGLE_H
#include "Mesh.h"

using namespace std;

class Mesh;

class MeshTriangle {
public:
    MeshTriangle(Mesh *parent, int inV0, int inV1, int inV2);
    MeshTriangle(const MeshTriangle& orig);
    virtual ~MeshTriangle();
    Mesh *parent;
    int v0;
    int v1;
    int v2;
    bool intersect(double xpos, double ypos, double zpos, double xcam, double ycam, double zcam);
private:

};

#endif	/* MESHTRIANGLE_H */

