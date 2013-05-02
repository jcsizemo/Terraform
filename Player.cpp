/* 
 * File:   Player.cpp
 * Author: John
 * 
 * Created on May 1, 2013, 4:43 PM
 */

#include <cstdlib>
#include "Player.h"
#include <GL/glew.h>
#include <GLUT/glut.h>
#include <cmath>

int movePerSec = 1000;

Player::Player(double x, double y, double z, double xrot, double yrot) {
    this->xpos = x;
    this->ypos = y;
    this->zpos = z;
    this->xrot = xrot;
    this->yrot = yrot;
    this->firstTouch = true;
}

Player::Player(const Player& orig) {
}

Player::~Player() {
}

void Player::camera() {
    yrotrad = (yrot / 180 * 3.141592654f); // update polar and azimuth angles
    xrotrad = (xrot / 180 * 3.141592654f);
    this->ycam = -float(sin(xrotrad))*1; // update camera vector
    this->xcam = float(sin(yrotrad))*1 * cos(xrotrad);
    this->zcam = -float(cos(yrotrad))*1 * cos(xrotrad);
    glRotatef(this->xrot, 1.0, 0.0, 0.0); //rotate our camera on the x-axis (left and right)
    glRotatef(this->yrot, 0.0, 1.0, 0.0); //rotate our camera on the y-axis (up and down)
    glTranslated(-this->xpos, -this->ypos, -this->zpos); //translate the screen to the position of our camera
}

void Player::mouseMovement(int x, int y) {
    int diffx = x - lastx; //check the difference between the current x and the last x position
    int diffy = y - lasty; //check the difference between the current y and the last y position
    lastx = x; //set lastx to the current x position
    lasty = y; //set lasty to the current y position
    if (!firstTouch) {
        xrot += (float) diffy; //set the xrot to xrot with the addition of the difference in the y position
        yrot += (float) diffx; //set the xrot to yrot with the addition of the difference in the x position
    }
    else {
        firstTouch = false;
    }
    if (xrot > 90) xrot = 90; // Fix azimuth range to 180 degrees
    if (xrot < -90) xrot = -90;

    if (yrot > 360) yrot -= 360; // Keep polar angle between -360 and 360
    if (yrot < -360) yrot += 360;
}

void Player::keyboard(unsigned char key, int x, int y, double dt) {
    float sineStep = movePerSec*dt*float(sin(yrotrad)); // depending on the polar angle,
    float cosStep = movePerSec*dt*float(cos(yrotrad)); // the step increments change

    if (key == 'w') { // forward
        xpos += sineStep;
        zpos -= cosStep;
    }

    if (key == 's') { // backward
        xpos -= sineStep;
        zpos += cosStep;
    }

    if (key == 'd') { // right
        xpos += cosStep;
        zpos += sineStep;
    }

    if (key == 'a') { // left
        xpos -= cosStep;
        zpos -= sineStep;
    }
}

