/* 
 * File:   Weapon.h
 * Author: John
 * 
 * General purpose Weapon class. Overriden
 * by the Firebomb and WaterBalloon classes.
 *
 * Created on May 4, 2013, 3:03 AM
 */

#ifndef WEAPON_H
#define	WEAPON_H

#include "Mesh.h"

class Mesh;

class Weapon : public Mesh {
public:
    // mesh file, position and direction
    Weapon(const char *filename, double xpos, double ypos, double zpos,
            double xcam, double ycam, double zcam);
    virtual ~Weapon();
    // direction of weapon
    double xcam;
    double ycam;
    double zcam;
    // draw mesh
    virtual void draw(double dt);
    // time variable used as an expiration flag for a weapon after it is thrown
    double t;
    // booleans to check if the weapon has hit something and to init collision
    bool collided;
    bool initCollision;
    // if a weapon hits something, this function inits the vectors for each
    // triangle to travel as well as their speeds
    virtual void setCollisionTrajectories();
    // since the only two weapons are firebombs and water ballons, this function
    // is overriden to check which weapon is active
    virtual bool isFirebomb();
private:

};

#endif	/* WEAPON_H */

