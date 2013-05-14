/* 
 * File:   Flame.cpp
 * Author: John
 * 
 * Created on May 13, 2013, 3:38 AM
 */

#include "Flame.h"

const int ParticleCount = 5;

Flame::Flame(double oX, double oY, double oZ) : ParticleMachine(oX,oY,oZ) {
    this->texture[0] = loadTexture("flame_mask.raw", 256, 256);
    this->texture[1] = loadTexture("flame.raw", 256, 256);
    this->oX = oX;
    this->oY = oY;
    this->oZ = oZ;
    this->createParticles(oX,oY,oZ);
}

Flame::~Flame() {
    freeTexture(this->texture[0]);
    freeTexture(this->texture[1]);
//    free(this->Particle);
}

void Flame::createParticles(double oX, double oY, double oZ) {
    for (int i = 0; i < ParticleCount; i++) {
        double seed = (double) rand() / INT_MAX;
        Particle[i].life = seed; // seconds
        Particle[i].yDir = seed;
        Particle[i].r = seed;      // particle rgb color
        seed *= twoPI;
        Particle[i].fade = 0.5;  // fade per second
        Particle[i].x = oX;       // start x,y,z position
        Particle[i].y = oY;
        Particle[i].z = oZ;
        Particle[i].g = 0;
        Particle[i].b = 0;
        Particle[i].xDir = cos(seed);   // dir variables per sec
        Particle[i].zDir = sin(seed);
        Particle[i].t = seed;
    }
}

void Flame::updateParticles(double dt) {
    for (int i = 0; i < ParticleCount; i++) {
        glPushMatrix();
        glColor4f(Particle[i].r, Particle[i].g,
                Particle[i].b, Particle[i].life);
        glEnable(GL_BLEND);
        glColor4f(Particle[i].r,Particle[i].g,Particle[i].b,Particle[i].life);

        Particle[i].life -= Particle[i].fade*dt;
        Particle[i].t += dt;
        if (Particle[i].t > twoPI) {
            Particle[i].t -= twoPI;
        }
        
        double ti = Particle[i].t;

        Particle[i].y += Particle[i].yDir*dt;
        Particle[i].x = this->oX + cos(ti)*(1 - Particle[i].life)*0.2;
        Particle[i].z = this->oZ + sin(ti)*(1 - Particle[i].life)*0.2;

//        Particle[i].xDir += Particle[i].xGrav*dt; // Take Pull On X Axis Into Account
//        Particle[i].yDir += Particle[i].yGrav*dt; // Take Pull On Y Axis Into Account
//        Particle[i].zDir += Particle[i].zGrav*dt; // Take Pull On Z Axis Into Account

        if (Particle[i].life <= 0.0f) // If Particle Is Burned Out
        {
            double seed = (double) rand() / INT_MAX;
            Particle[i].life = seed; // Give It New Life
//            Particle[i].yDir = seed;
//            Particle[i].fade = float(rand() % 100) / 1000.0f + 0.003f; // Random Fade Value
            Particle[i].x = this->oX; // Center On X Axis
            Particle[i].y = this->oY; // Center On Y Axis
            Particle[i].z = this->oZ; // Center On Z Axis
//            Particle[i].xDir = cos(seed);
//            Particle[i].yDir = 1*dt;
//            Particle[i].zDir = 5*sin(seed);
//            Particle[i].r = seed; // Select Red From Color Table
//            Particle[i].g = 0; // Select Green From Color Table
//            Particle[i].b = 0; // Select Blue From Color Table
        }
        
        glDisable(GL_BLEND);
        glPopMatrix();
    }
}

void Flame::drawParticles(double dt) {
    int i;
    for (i = 1; i < ParticleCount; i++) {
        glPushMatrix();
        glEnable(GL_TEXTURE_2D);
//        glTranslatef(Particle[i].x, Particle[i].y, Particle[i].z);

        glEnable(GL_BLEND);

//        glBlendFunc(GL_DST_COLOR, GL_ZERO);
//        glBindTexture(GL_TEXTURE_2D, texture[0]);
//
//        glBegin(GL_QUADS);
//        glTexCoord2d(0, 0);
//        glVertex3f(Particle[i].x, Particle[i].y, Particle[i].z);
//        glTexCoord2d(1, 0);
//        glVertex3f(Particle[i].x + 0.5f, Particle[i].y, Particle[i].z);
//        glTexCoord2d(1, 1);
//        glVertex3f(Particle[i].x + 0.5f, Particle[i].y + 0.5f, Particle[i].z);
//        glTexCoord2d(0, 1);
//        glVertex3f(Particle[i].x, Particle[i].y + 0.5f, Particle[i].z);
//        glEnd();

        glBlendFunc(GL_ONE, GL_ONE);
        glBindTexture(GL_TEXTURE_2D, texture[1]);

//        glDisable(GL_DEPTH_TEST);
        glBegin(GL_QUADS);
        glTexCoord2d(0, 0);
        glVertex3f(Particle[i].x, Particle[i].y, Particle[i].z);
        glTexCoord2d(1, 0);
        glVertex3f(Particle[i].x + 0.5f, Particle[i].y, Particle[i].z);
        glTexCoord2d(1, 1);
        glVertex3f(Particle[i].x + 0.5f, Particle[i].y + 0.5f, Particle[i].z);
        glTexCoord2d(0, 1);
        glVertex3f(Particle[i].x, Particle[i].y + 0.5f, Particle[i].z);
        glEnd();
//        glEnable(GL_DEPTH_TEST);
        glDisable(GL_TEXTURE_2D);

        
        glDisable(GL_BLEND);
        glPopMatrix();

    }
}

