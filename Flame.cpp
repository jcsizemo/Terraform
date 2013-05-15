/* 
 * File:   Flame.cpp
 * Author: John
 * 
 * Created on May 13, 2013, 3:38 AM
 */

#include "Flame.h"

const int ParticleCount = 10;

Flame::Flame(double oX, double oY, double oZ) : ParticleMachine(oX,oY,oZ) {
    this->texture[0] = loadTexture("brightFlame.raw", 256, 256);
    this->oX = oX;
    this->oY = oY;
    this->oZ = oZ;
    this->createParticles(oX,oY,oZ);
}

Flame::~Flame() {
    freeTexture(this->texture[0]);
}

void Flame::createParticles(double oX, double oY, double oZ) {
    for (int i = 0; i < ParticleCount; i++) {
        double seed = (double) rand() / INT_MAX;
        Particle[i].life = seed; // seconds
//        Particle[i].maxLife = seed;
        Particle[i].yDir = 0.1;
        Particle[i].r = 1;      // particle rgb color
        seed *= twoPI;
        Particle[i].fade = 0.1;  // fade per second
        Particle[i].x = oX;       // start x,y,z position
        Particle[i].y = oY;
        Particle[i].z = oZ;
        Particle[i].g = 0;
        Particle[i].b = 0;
        Particle[i].xDir = cos(seed);   // dir variables per sec
        seed = (double) rand() / INT_MAX;
        seed *= twoPI;
        Particle[i].zDir = sin(seed+twoPI*0.25);
        Particle[i].t = seed;
    }
}

void Flame::updateParticles(double dt) {
    for (int i = 0; i < ParticleCount; i++) {
//        glPushMatrix();
        glColor3f(Particle[i].r, Particle[i].g,
                Particle[i].b);
        Particle[i].life -= Particle[i].fade*dt;
        Particle[i].t += dt;
        if (Particle[i].t > twoPI) {
            Particle[i].t -= twoPI;
        }
        
        double ti = Particle[i].t;

        Particle[i].y += Particle[i].yDir*dt;
        double seed = (double) rand() / INT_MAX;
        seed *= twoPI;
        Particle[i].x = this->oX + cos(seed)*(Particle[i].y - this->oY)*0.1;
        Particle[i].z = this->oZ + sin(seed)*(Particle[i].y - this->oY)*0.2;

//        Particle[i].xDir += Particle[i].xGrav*dt; // Take Pull On X Axis Into Account
//        Particle[i].yDir += Particle[i].yGrav*dt; // Take Pull On Y Axis Into Account
//        Particle[i].zDir += Particle[i].zGrav*dt; // Take Pull On Z Axis Into Account

        if (Particle[i].life <= 0.0f) // If Particle Is Burned Out
        {
            double seed = (double) rand() / INT_MAX;
            Particle[i].life = seed; // Give It New Life
//            Particle[i].maxLife = seed;
//            Particle[i].yDir = seed;
//            Particle[i].fade = seed*0.5;
            seed *= twoPI;
//            Particle[i].fade = float(rand() % 100) / 1000.0f + 0.003f; // Random Fade Value
            Particle[i].x = this->oX; // Center On X Axis
            Particle[i].y = this->oY; // Center On Y Axis
            Particle[i].z = this->oZ; // Center On Z Axis
//            Particle[i].xDir = cos(seed)*dt;
//            Particle[i].yDir = 1*dt;
//            Particle[i].zDir = sin(seed)*dt;
//            Particle[i].r = seed; // Select Red From Color Table
//            Particle[i].g = 0; // Select Green From Color Table
//            Particle[i].b = 0; // Select Blue From Color Table
        }
//        glPopMatrix();
    }
}

void Flame::drawParticles(double dt) {
    int i;
    for (i = 1; i < ParticleCount; i++) {
        glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ZERO);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glBegin(GL_QUADS);
        glTexCoord2d(0, 0);
        glVertex3f(Particle[i].x, Particle[i].y, Particle[i].z);
        glTexCoord2d(1, 0);
        glVertex3f(Particle[i].x + 0.2f, Particle[i].y, Particle[i].z);
        glTexCoord2d(1, 1);
        glVertex3f(Particle[i].x + 0.2f, Particle[i].y + 0.2f, Particle[i].z);
        glTexCoord2d(0, 1);
        glVertex3f(Particle[i].x, Particle[i].y + 0.2f, Particle[i].z);
        glEnd();
        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }
}

