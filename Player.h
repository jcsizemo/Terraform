/* 
 * File:   Player.h
 * Author: John
 *
 * Object representing the player or, in this case, the camera.
 * Acts as a wrapper for the objects in which the player can use (firebomb
 * or water balloon)
 * 
 * Created on May 1, 2013, 4:43 PM
 */

#ifndef PLAYER_H
#define	PLAYER_H
#include <iostream>
#include <vector>
#include "Weapon.h"
#include "Firebomb.h"
#include "WaterBalloon.h"
#include "Structure.h"
#include "Light.h"

using namespace std;

class Weapon;
class Light;

class Player {
public:
    Player(double x, double y, double z, double xRot, double yRot);
    Player(const Player& orig);
    virtual ~Player();
    // position of player
    double xpos;
    double ypos;
    double zpos;
    // rotation of player
    double xrot;
    double yrot;
    // camera direction
    double xcam;
    double ycam;
    double zcam;
    // rotation of player in radians
    double xrotrad;
    double yrotrad;
    // these two variables are used for mouse movement
    int lastx;
    int lasty;
    // init first touch so camera doesn't go nuts at first
    bool firstTouch;
    // list of throwable weapons (firebomb, water balloon)
    vector<Weapon*> weapons;
    // keyboard function controlling movement per time
    void keyboard(bool *keys, double dt);
    // mouse movement function
    void mouseMovement(int x, int y);
    // camera function to update player's rotation and position. acts
    // as a wrapper for throwable object interactions with other structures
    // in the scene
    void camera(double dt, vector<Structure*> *structures, vector<Light*> *lights);
private:

};

#endif	/* PLAYER_H */

