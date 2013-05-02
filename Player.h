/* 
 * File:   Player.h
 * Author: John
 *
 * Created on May 1, 2013, 4:43 PM
 */

#ifndef PLAYER_H
#define	PLAYER_H
#include "drawable.h"
#include <iostream>

using namespace std;

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
    void keyboard(unsigned char key, int x, int y);
    void mouseMovement(int x, int y);
    void camera();
private:

};

#endif	/* PLAYER_H */

