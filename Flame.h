/* 
 * File:   Flame.h
 * Author: John
 *
 * Created on May 13, 2013, 3:38 AM
 */

#ifndef FLAME_H
#define	FLAME_H

#include "ParticleMachine.h"
#include <cmath>

class ParticleMachine;

class Flame : public ParticleMachine {
public:
    Flame(double oX, double oY, double oZ);
    void updateParticles(double dt);
    void drawParticles(double dt);
    void createParticles(double oX, double oY, double oZ);
    double oX;
    double oY;
    double oZ;
    virtual ~Flame();
private:

};

#endif	/* FLAME_H */

