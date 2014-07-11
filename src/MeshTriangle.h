/* 
 * File:   MeshTriangle.h
 * Author: John
 * 
 * MeshTriangle class used for the triangles covering a mesh. The triangles
 * are very important and used for collision detection.
 *
 * Created on May 1, 2013, 8:28 PM
 */

#ifndef MESHTRIANGLE_H
#define	MESHTRIANGLE_H
#include "Mesh.h"
#include "Light.h"
#include <vector>

using namespace std;

class Mesh;
class Light;

class MeshTriangle {
public:
    MeshTriangle(Mesh *parent, int inV0, int inV1, int inV2); // parent mesh and verts
    MeshTriangle(const MeshTriangle& orig);
    virtual ~MeshTriangle();
    Mesh *parent;
    int v0; // triangle vertices
    int v1;
    int v2;
    double x0; // x,y, and z coords of the 3 verts
    double x1;
    double x2;
    double y0;
    double y1;
    double y2;
    double z0;
    double z1;
    double z2;
    double ctX; // explosion vector directions
    double ctY;
    double ctZ;
    double nX; // normal values
    double nY;
    double nZ;
    double A;  // A-F various values used for collision detection
    double B;
    double C;
    double D;
    double E;
    double F;
    double ctSpd; // explosion speed 
    bool collided; // checks if the triangle intersected another triangle
    bool burnt;   // checks if a mesh is "burnt" by fire
    double burnTimer; // timer counting how long a burning triangle has to live
    // intersection function taking an incoming point/direction. The lights are
    // used to add lights due to the fires and the isFire variable checks
    // if the incoming point is on a firebomb or water balloon
    bool intersect(double xpos, double ypos, double zpos, double xcam, 
        double ycam, double zcam, vector<Light*> *lights, bool isFire);
private:

};

#endif	/* MESHTRIANGLE_H */

