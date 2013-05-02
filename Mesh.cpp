/* 
 * File:   Mesh.cpp
 * Author: John
 * 
 * Created on May 1, 2013, 5:43 PM
 */

#include "Mesh.h"

Mesh::Mesh(const char* filename, double xpos, double ypos, double zpos) {
    this->xpos = xpos;
    this->ypos = ypos;
    this->zpos = zpos;
    readModel(filename);
}

Mesh::Mesh(const Mesh& orig) {
}

Mesh::~Mesh() {
}

void Mesh::setMeshData(double *vertices, int *tris, int numVerts, int numTris) {
        
    for (int i = 0; i < numVerts; i++) {
        this->verts.push_back(vertices[3*i] + this->xpos);
        this->verts.push_back(vertices[3*i+1] + this->ypos);
        this->verts.push_back(vertices[3*i+2] + this->zpos);
    }
    
    for (int i = 0; i < numTris; i++) {
        this->tris.push_back(new MeshTriangle(this, tris[3*i], tris[3*i+1], tris[3*i+2]));
    }
}

void Mesh::readModel(const char* filename) {  // function reading in Blender model
    ifstream in_stream;
    string line;
    in_stream.open(filename);  // open file

    in_stream >> line;
    int nPoints = atoi(line.c_str());
    in_stream >> line;
    int nPolys = atoi(line.c_str());
    
    double vertices[nPoints*3];
    int triangles[nPolys*3];
    
    in_stream >> line;
    if (!line.compare("vertices")) {
        for (int i = 0; i < nPoints*3; i++) {
            in_stream >> line;
            vertices[i] = atof(line.c_str());
        }
    }
    
    in_stream >> line;
    if (!line.compare("triangles")) {
        for (int i = 0; i < nPolys*3; i++) {
            in_stream >> line;
            triangles[i] = atoi(line.c_str());
        }
    }
    
    in_stream.close();
    setMeshData(vertices,triangles,nPoints,nPolys);
}

void Mesh::draw() {
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < this->tris.size(); i++) {
        MeshTriangle *tri = tris.at(i);
        glVertex3f(verts.at(3*tri->v0),verts.at(3*tri->v0+1),verts.at(3*tri->v0+2));
        glVertex3f(verts.at(3*tri->v1),verts.at(3*tri->v1+1),verts.at(3*tri->v1+2));
        glVertex3f(verts.at(3*tri->v2),verts.at(3*tri->v2+1),verts.at(3*tri->v2+2));
    }
    glEnd();
    glPopMatrix();
}

bool Mesh::intersect(double xpos, double ypos, double zpos, double xcam, double ycam, double zcam) {
    for (int i = 0; i < this->tris.size(); i++) {
        if (tris.at(i)->intersect(xpos,ypos,zpos,xcam,ycam,zcam)) {
            return true;
        }
    }
    return false;
}


