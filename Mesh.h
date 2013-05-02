/* 
 * File:   Mesh.h
 * Author: John
 *
 * Created on May 1, 2013, 5:43 PM
 */

#ifndef MESH_H
#define	MESH_H

#include <GL/glew.h>
#include <GLUT/glut.h>
#include "MeshTriangle.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class MeshTriangle;

class Mesh {
public:
    Mesh(const char* filename);
    Mesh(const Mesh& orig);
    virtual ~Mesh();
    void readModel(const char* filename);
    void setMeshData(double *vertices, int *triangles, int numVerts, int numTris);
    vector<double> verts;
    vector<MeshTriangle*> tris;
    void draw();
    bool intersect(double xpos, double ypos, double zpos, double xcam, double ycam, double zcam);
private:

};

#endif	/* MESH_H */

