/* 
 * File:   Flame.h
 * Author: John
 * 
 * Class for the flames which appear when a tree is hit with a firebomb.
 *
 * Created on May 13, 2013, 3:38 AM
 */

#ifndef FLAME_H
#define	FLAME_H

#include "ParticleMachine.h"

class ParticleMachine; // extends ParticleMachine class

class Flame : public ParticleMachine {
public:
    Flame(double oX, double oY, double oZ);     //init Flame with position
    void updateParticles(double dt);    // update the particle positions, vectors
    void drawParticles(double dt);      // draw particles with updated information
    void createParticles(double oX, double oY, double oZ);      // init particles
    virtual ~Flame();
private:

};

#endif	/* FLAME_H */

