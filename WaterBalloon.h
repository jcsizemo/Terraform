/* 
 * File:   Firebomb.h
 * Author: John
 *
 * Created on May 5, 2013, 5:37 PM
 */

#ifndef WATERBALLOON_H
#define	WATERBALLOON_H

#include "Weapon.h"

class Weapon;

class WaterBalloon : public Weapon {
public:
    WaterBalloon(const char *filename, double xpos, double ypos, double zpos,
            double xcam, double ycam, double zcam);
    virtual ~WaterBalloon();
    void draw(double dt);
    void setCollisionTrajectories();
    bool isFirebomb();
private:

};

#endif	/* FIREBOMB_H */

