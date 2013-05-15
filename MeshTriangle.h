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
    double x0;
    double x1;
    double x2;
    double y0;
    double y1;
    double y2;
    double z0;
    double z1;
    double z2;
    double ctX;
    double ctY;
    double ctZ;
    double nX;
    double nY;
    double nZ;
    double A;
    double B;
    double C;
    double D;
    double E;
    double F;
    double ctSpd;
    bool collided;
    bool intersect(double xpos, double ypos, double zpos, double xcam, double ycam, double zcam);
private:

};

#endif	/* MESHTRIANGLE_H */

