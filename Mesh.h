/* 
 * File:   Mesh.h
 * Author: John
 * 
 * Mesh class. General purpose class used to define base operations for
 * all meshes such as reading mesh fils and drawing.
 *
 * Created on May 1, 2013, 5:43 PM
 */

#ifndef MESH_H
#define	MESH_H

#include <GL/glew.h>
#if defined(_WIN32)
#include <GL/wglew.h>
#endif

#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "MeshTriangle.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "ParticleMachine.h"
#include "Light.h"

using namespace std;

class MeshTriangle;
class Light;
class ParticleMachine;

class Mesh {
public:
    Mesh(const char* filename, double xpos, double ypos, double zpos);
    Mesh(const Mesh& orig);
    virtual ~Mesh();
    // read .msh file and parse data
    void readModel(const char* filename);
    // send parsed data to this function to build the mesh object.
    // adds vertices, triangles, and material colors
    void setMeshData(double *vertices, int *tris, int *mtlIndices, 
        double *mtls, int numVerts, int numTris, int numObjs);
    vector<double> verts;
    vector<MeshTriangle*> tris;
    vector<ParticleMachine*> particles;
    map<int,int> mtlIndices;
    vector<double> mtls;
    // draw function which draws the triangles of the mesh. inherited by
    // subclasses to perform additional duties
    virtual void draw(double dt);
    // intersect function which takes an incoming point's position and direction
    // as well as a list of lights in the scene. The incoming object is either
    // a firebomb or a water balloon so a boolean is declared checking which
    // is which.
    bool intersect(double xpos, double ypos, double zpos, 
        double xcam, double ycam, double zcam, vector<Light*> *lights, bool isFire);
    // x,y,z coords of mesh
    double xpos;
    double ypos;
    double zpos;
private:

};

#endif	/* MESH_H */

