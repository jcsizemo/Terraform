/* 
 * File:   Firebomb.h
 * Author: John
 * 
 * Firebomb class. Defines the model used for the firebomb and
 * other behaviors. The firebomb can set trees on fire.
 *
 * Created on May 5, 2013, 5:37 PM
 */

#ifndef FIREBOMB_H
#define	FIREBOMB_H

#include "Weapon.h"

class Weapon; // extends Weapon class

class Firebomb : public Weapon {
public:
    // init firebomb with model file, position, and direction
    Firebomb(const char *filename, double xpos, double ypos, double zpos,
            double xcam, double ycam, double zcam);     
    virtual ~Firebomb();
    void draw(double dt);       // draw the bomb
    void setCollisionTrajectories();    // set explosion vectors
    bool isFirebomb();  // used for environment manipulation
private:

};

#endif	/* FIREBOMB_H */

