/* 
 * File:   Player.h
 * Author: John
 *
 * Created on May 1, 2013, 4:43 PM
 */

#ifndef PLAYER_H
#define	PLAYER_H
#include <iostream>
#include <vector>
#include "Weapon.h"
#include "Firebomb.h"
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
    double xpos;
    double ypos;
    double zpos;
    double xrot;
    double yrot;
    double xcam;
    double ycam;
    double zcam;
    double xrotrad;
    double yrotrad;
    int lastx;
    int lasty;
    bool firstTouch;
    vector<Weapon*> weapons;
    void keyboard(bool *keys, double dt);
    void mouseMovement(int x, int y);
    void camera(double dt, vector<Structure*> *structures, vector<Light*> *lights);
private:

};

#endif	/* PLAYER_H */

