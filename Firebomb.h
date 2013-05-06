/* 
 * File:   Firebomb.h
 * Author: John
 *
 * Created on May 5, 2013, 5:37 PM
 */

#ifndef FIREBOMB_H
#define	FIREBOMB_H

#include "Weapon.h"

class Weapon;

class Firebomb : public Weapon {
public:
    Firebomb(const char *filename, double xpos, double ypos, double zpos,
            double xcam, double ycam, double zcam);
    virtual ~Firebomb();
    void draw(double dt);
    void setCollisionTrajectories();
private:

};

#endif	/* FIREBOMB_H */

