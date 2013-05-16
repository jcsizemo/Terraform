/* 
 * File:   Structure.cpp
 * Author: John
 * 
 * Created on May 5, 2013, 7:03 PM
 * 
 * Structure class detailing interactive structures in the game world.
 */

#include "Structure.h"

// ambient light
double aR = 0.1;
double aG = 0.1;
double aB = 0.1;

// lifespan of a burning triangle
double burnLimit = 5;

Structure::Structure(const char* filename, double xpos, double ypos,
        double zpos) : Mesh(filename, xpos, ypos, zpos) {
}

Structure::~Structure() {
}

void Structure::draw(double dt, vector<Light*> *lights) {
    glPushMatrix();
    // for each triangle in the mesh...
    for (int i = 0; i < this->tris.size(); i++) {
        MeshTriangle *tri = tris.at(i);
        int mtlIndex = 0;
        // get material
        for (int j = 0; j < this->mtlIndices.size(); j++) {
            if (i < this->mtlIndices.at(j)) {
                mtlIndex = j;
                break;
            }
        }
        // Phong shading area. Only ambient/diffuse are taken into account.
        // Init rgb values with ambient light
        double r = this->mtls.at(3 * mtlIndex);
        double g = this->mtls.at(3 * mtlIndex + 1);
        double b = this->mtls.at(3 * mtlIndex + 2);
        double color0[3] = {aR, aG, aB};
        double color1[3] = {aR, aG, aB};
        double color2[3] = {aR, aG, aB};
        // triangle normal
        double N[] = {tri->nX, tri->nY, tri->nZ};
        for (int j = 0; j < lights->size(); j++) {
            // for each light in the scene....
            Light *l = lights->at(j);
            // vectors from the triangle vertex to the light
            double Lm0[] = {l->xpos - tri->x0, l->ypos - tri->y0, l->zpos - tri->z0};
            double Lm1[] = {l->xpos - tri->x1, l->ypos - tri->y1, l->zpos - tri->z1};
            double Lm2[] = {l->xpos - tri->x2, l->ypos - tri->y2, l->zpos - tri->z2};
            double mag0 = sqrt(Lm0[0] * Lm0[0] + Lm0[1] * Lm0[1] + Lm0[2] * Lm0[2]);
            double mag1 = sqrt(Lm1[0] * Lm1[0] + Lm1[1] * Lm1[1] + Lm1[2] * Lm1[2]);
            double mag2 = sqrt(Lm2[0] * Lm2[0] + Lm2[1] * Lm2[1] + Lm2[2] * Lm2[2]);
            // normal these directions
            Lm0[0] /= mag0;
            Lm0[1] /= mag0;
            Lm0[2] /= mag0;
            Lm1[0] /= mag1;
            Lm1[1] /= mag1;
            Lm1[2] /= mag1;
            Lm2[0] /= mag2;
            Lm2[1] /= mag2;
            Lm2[2] /= mag2;
            // light intensities; dot product of light direction towards point
            // with the normal
            double LdN0 = Lm0[0] * N[0] + Lm0[1] * N[1] + Lm0[2] * N[2];
            double LdN1 = Lm1[0] * N[0] + Lm1[1] * N[1] + Lm1[2] * N[2];
            double LdN2 = Lm2[0] * N[0] + Lm2[1] * N[1] + Lm2[2] * N[2];
            // clamp to zero
            if (LdN0 < 0) LdN0 = 0;
            if (LdN1 < 0) LdN1 = 0;
            if (LdN2 < 0) LdN2 = 0;
            // add diffuse components
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
        // blend phong colors
        glEnable(GL_BLEND);
        if (tri->collided) {
            // if the triangle has hit something, update burn timer
            tri->burnTimer += dt;
            if (tri->burnTimer > burnLimit) {
                // if the burn timer is over limit, remove triangle
                int particleSize = this->particles.size();
                int lightSize = lights->size();
                tri->burnt = true;
                // erase flame and light
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
                // if the triangle isn't burnt out then
                // update particles (flames)
                ParticleMachine *pm = particles.at(i);
                pm->updateParticles(dt);
                pm->drawParticles(dt);
            }
        }
        // if the triangle isn't burnt, draw it
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

void Structure::revive(void) {
    // to revive a tree each triangle is simply not burnt anymore.
    // so.....update all triangles to initial values
    for (int m = 0; m < this->tris.size(); m++) {
        this->tris.at(m)->burnt = false;
        this->tris.at(m)->collided = false;
        this->tris.at(m)->burnTimer = 0;
    }
    // erase all flames from the tree
    for (int m = this->particles.size() - 1; m >= 0; m--) {
        ParticleMachine *pm = this->particles.at(m);
        this->particles.erase(this->particles.begin() + m);
        delete pm;
    }
}
