/* 
 * File:   Structure.cpp
 * Author: John
 * 
 * Created on May 5, 2013, 7:03 PM
 */

#include "Structure.h"

double aR = 0.1;
double aG = 0.1;
double aB = 0.1;

Structure::Structure(const char* filename, double xpos, double ypos,
        double zpos, double *color) : Mesh(filename, xpos, ypos, zpos) {
    this->color[0] = color[0];
    this->color[1] = color[1];
    this->color[2] = color[2];
}

Structure::~Structure() {
}

void Structure::draw(double dt, vector<Light*> *lights) {
    glPushMatrix();
    
        glEnable(GL_BLEND);
        for (int i = 0; i < this->tris.size(); i++) {
            MeshTriangle *tri = tris.at(i);
            for (int j = 0; j < lights->size(); j++) {
                Light *l = lights->at(j);
                double N[] = {tri->nX, tri->nY, tri->nZ};
                double Lm0[] = {l->xpos - tri->x0, l->ypos - tri->y0, l->zpos - tri->z0};
                double Lm1[] = {l->xpos - tri->x1, l->ypos - tri->y1, l->zpos - tri->z1};
                double Lm2[] = {l->xpos - tri->x2, l->ypos - tri->y2, l->zpos - tri->z2};
                double mag0 = sqrt(Lm0[0]*Lm0[0]+Lm0[1]*Lm0[1]+Lm0[2]*Lm0[2]);
                double mag1 = sqrt(Lm1[0]*Lm1[0]+Lm1[1]*Lm1[1]+Lm1[2]*Lm1[2]);
                double mag2 = sqrt(Lm2[0]*Lm2[0]+Lm2[1]*Lm2[1]+Lm2[2]*Lm2[2]);
                Lm0[0] /= mag0;
                Lm0[1] /= mag0;
                Lm0[2] /= mag0;
                Lm1[0] /= mag1;
                Lm1[1] /= mag1;
                Lm1[2] /= mag1;
                Lm2[0] /= mag2;
                Lm2[1] /= mag2;
                Lm2[2] /= mag2;
                double LdN0 = Lm0[0] * N[0] + Lm0[1] * N[1] + Lm0[2] * N[2];
                double LdN1 = Lm1[0] * N[0] + Lm1[1] * N[1] + Lm1[2] * N[2];
                double LdN2 = Lm2[0] * N[0] + Lm2[1] * N[1] + Lm2[2] * N[2];
                if (LdN0 < 0) LdN0 = 0;
                if (LdN1 < 0) LdN1 = 0;
                if (LdN2 < 0) LdN2 = 0;
                glBegin(GL_TRIANGLES);
//                            glColor3dv(this->color);
                glColor3f(aR + l->r * LdN0 * this->color[0],
                        aG + l->g * LdN0 * this->color[1],
                        aB + l->b * LdN0 * this->color[2]);
                glVertex3f(tri->x0, tri->y0, tri->z0);
                glColor3f(aR + l->r * LdN1 * this->color[0],
                        aG + l->g * LdN1 * this->color[1],
                        aB + l->b * LdN1 * this->color[2]);
                glVertex3f(tri->x1, tri->y1, tri->z1);
                glColor3f(aR + l->r * LdN2 * this->color[0],
                        aG + l->g * LdN2 * this->color[1],
                        aB + l->b * LdN2 * this->color[2]);
                glVertex3f(tri->x2, tri->y2, tri->z2);
                glEnd();
                if (tri->collided) {
                    for (int i = 0; i < this->particles.size(); i++) {
                        ParticleMachine *pm = particles.at(i);
                        pm->updateParticles(dt);
                        pm->drawParticles(dt);
                    }
                }
            
        }
        glDisable(GL_BLEND);
    }

    glPopMatrix();
    glColor3d(0, 0, 0);
}

