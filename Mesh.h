/* 
 * File:   Mesh.h
 * Author: John
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
    void readModel(const char* filename);
    void setMeshData(double *vertices, int *tris, int *mtlIndices, 
        double *mtls, int numVerts, int numTris, int numObjs);
    vector<double> verts;
    vector<MeshTriangle*> tris;
    vector<ParticleMachine*> particles;
    map<int,int> mtlIndices;
    vector<double> mtls;
    virtual void draw(double dt);
    bool intersect(double xpos, double ypos, double zpos, 
        double xcam, double ycam, double zcam, vector<Light*> *lights);
    double xpos;
    double ypos;
    double zpos;
private:

};

#endif	/* MESH_H */

