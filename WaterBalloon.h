/* 
 * File:   Firebomb.h
 * Author: John
 * 
 * Water balloon class. The water balloon
 * is a throwable object which can revive burnt trees.
 *
 * Created on May 5, 2013, 5:37 PM
 */

#ifndef WATERBALLOON_H
#define	WATERBALLOON_H

#include "Weapon.h"

class Weapon;

class WaterBalloon : public Weapon {
public:
    // mesh file, water balloon position and direction
    WaterBalloon(const char *filename, double xpos, double ypos, double zpos,
            double xcam, double ycam, double zcam);
    virtual ~WaterBalloon();
    // draw water balloon
    void draw(double dt);
    // set explosion vectors
    void setCollisionTrajectories();
    // used to check if a tree should be revived
    bool isFirebomb();
private:

};

#endif	/* FIREBOMB_H */

