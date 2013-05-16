/* 
 * File:   Flame.cpp
 * Author: John
 * 
 * Created on May 13, 2013, 3:38 AM
 * 
 * Flame class. Inits the particles, updates positions based on time,
 * and binds textures to each particle.
 */

#include "Flame.h"

// number of particles per flame
const int ParticleCount = 10;

// load flame texture, set position, and init the particles
Flame::Flame(double oX, double oY, double oZ) : ParticleMachine(oX,oY,oZ) {
    this->texture[0] = loadTexture("flame.raw", 256, 256);
    this->oX = oX;
    this->oY = oY;
    this->oZ = oZ;
    this->createParticles(oX,oY,oZ);
}

// free texture when flame dissipated otherwise huge memory leaks occur
Flame::~Flame() {
    freeTexture(this->texture[0]);
}

void Flame::createParticles(double oX, double oY, double oZ) {
    for (int i = 0; i < ParticleCount; i++) {
        // give each flame random life
        double seed = (double) rand() / INT_MAX;
        Particle[i].life = seed; // seconds
        Particle[i].yDir = 0.1;  // move per second in y direction
        Particle[i].r = 1;      // particle rgb color
        seed *= twoPI;
        Particle[i].fade = 0.1;  // fade per second
        Particle[i].x = oX;       // start x,y,z position
        Particle[i].y = oY;
        Particle[i].z = oZ;
        Particle[i].g = 0;      // no green or blue
        Particle[i].b = 0;
        Particle[i].xDir = cos(seed);   // random x direction for flame "wave"
        seed = (double) rand() / INT_MAX;
        seed *= twoPI;
        Particle[i].zDir = sin(seed+twoPI*0.25);  // random z dir
        Particle[i].t = seed; // time used to update x and z values
    }
}

void Flame::updateParticles(double dt) {
    for (int i = 0; i < ParticleCount; i++) {
        // color the particle; used to blend with texture
        glColor3f(Particle[i].r, Particle[i].g,
                Particle[i].b);
        // update life based on time
        Particle[i].life -= Particle[i].fade*dt;
        // update the t value used for the sine/cosine calculations for x and z
        Particle[i].t += dt;
        if (Particle[i].t > twoPI) {
            Particle[i].t -= twoPI;
        }
        
        double ti = Particle[i].t;

        // update x,y,z position
        Particle[i].y += Particle[i].yDir*dt;
        double seed = (double) rand() / INT_MAX;
        seed *= twoPI;
        Particle[i].x = this->oX + cos(seed)*(Particle[i].y - this->oY)*0.1;
        Particle[i].z = this->oZ + sin(seed)*(Particle[i].y - this->oY)*0.2;

        if (Particle[i].life <= 0.0f) // if particle burned out
        {
            // keep all init values except for those below
            double seed = (double) rand() / INT_MAX;
            Particle[i].life = seed; // new random life
            seed *= twoPI;
            Particle[i].x = this->oX; // recenter on initial x,y,z
            Particle[i].y = this->oY;
            Particle[i].z = this->oZ;
        }
//        glPopMatrix();
    }
}

void Flame::drawParticles(double dt) {
    int i;
    for (i = 1; i < ParticleCount; i++) {
        // for each particle....
        glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ZERO);
        // bind texture to particle, blend with color set in previous function
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        // build quad and attach texture to it
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

