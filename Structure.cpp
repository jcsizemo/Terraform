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

    for (int i = 0; i < this->tris.size(); i++) {
        MeshTriangle *tri = tris.at(i);
        int mtlIndex = 0;
        for (int j = 0; j < this->mtlIndices.size(); j++) {
            if (i < this->mtlIndices.at(j)) {
                mtlIndex = j - 1;
                break;
            }
        }
        double r = this->mtls.at(3 * mtlIndex);
        double g = this->mtls.at(3 * mtlIndex + 1);
        double b = this->mtls.at(3 * mtlIndex + 2);
        double color0[3] = {aR, aG, aB};
        double color1[3] = {aR, aG, aB};
        double color2[3] = {aR, aG, aB};
        double N[] = {tri->nX, tri->nY, tri->nZ};
        for (int j = 0; j < lights->size(); j++) {
            Light *l = lights->at(j);
            double Lm0[] = {l->xpos - tri->x0, l->ypos - tri->y0, l->zpos - tri->z0};
            double Lm1[] = {l->xpos - tri->x1, l->ypos - tri->y1, l->zpos - tri->z1};
            double Lm2[] = {l->xpos - tri->x2, l->ypos - tri->y2, l->zpos - tri->z2};
            double mag0 = sqrt(Lm0[0] * Lm0[0] + Lm0[1] * Lm0[1] + Lm0[2] * Lm0[2]);
            double mag1 = sqrt(Lm1[0] * Lm1[0] + Lm1[1] * Lm1[1] + Lm1[2] * Lm1[2]);
            double mag2 = sqrt(Lm2[0] * Lm2[0] + Lm2[1] * Lm2[1] + Lm2[2] * Lm2[2]);
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
            color0[0] += l->r * LdN0 * this->mtls.at(3 * mtlIndex);
            color0[1] += l->g * LdN0 * this->mtls.at(3 * mtlIndex + 1);
            color0[2] += l->b * LdN0 * this->mtls.at(3 * mtlIndex + 2);
            color1[0] += l->r * LdN1 * this->mtls.at(3 * mtlIndex);
            color1[1] += l->g * LdN1 * this->mtls.at(3 * mtlIndex + 1);
            color1[2] += l->b * LdN1 * this->mtls.at(3 * mtlIndex + 2);
            color2[0] += l->r * LdN2 * this->mtls.at(3 * mtlIndex);
            color2[1] += l->g * LdN2 * this->mtls.at(3 * mtlIndex + 1);
            color2[2] += l->b * LdN2 * this->mtls.at(3 * mtlIndex + 2);
        }
        glEnable(GL_BLEND);
        if (tri->collided) {
            tri->burnTimer += dt;
            if (tri->burnTimer > 5) {
                int particleSize = this->particles.size();
                int lightSize = lights->size();
                tri->burnt = true;
                ParticleMachine *pm = this->particles.at(0);
                this->particles.erase(this->particles.begin());
                delete pm;
                Light *l = lights->at(1);
                lights->erase(lights->begin() + 1);
                delete l;
                tri->burnTimer = 0;
                tri->collided = false;
            }
            for (int i = 0; i < this->particles.size(); i++) {
                ParticleMachine *pm = particles.at(i);
                pm->updateParticles(dt);
                pm->drawParticles(dt);
            }
        }
        if (!tri->burnt) {
            glBegin(GL_TRIANGLES);
            glColor3dv(color0);
            glVertex3f(tri->x0, tri->y0, tri->z0);
            glColor3dv(color1);
            glVertex3f(tri->x1, tri->y1, tri->z1);
            glColor3dv(color2);
            glVertex3f(tri->x2, tri->y2, tri->z2);
            glEnd();
        }
        glDisable(GL_BLEND);
    }

    glPopMatrix();
    glColor3d(0, 0, 0);
}

