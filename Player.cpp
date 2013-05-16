/* 
 * File:   Player.cpp
 * Author: John
 * 
 * Created on May 1, 2013, 4:43 PM
 */

#include <cstdlib>
#include "Player.h"
#include <GL/glew.h>
#if defined(_WIN32)
#include <GL/wglew.h>
#endif

#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>

double movePerSec = 19;

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

void Player::camera(double dt, vector<Structure*> *structures, vector<Light*> *lights) {
    yrotrad = (yrot / 180 * 3.141592654f); // update polar and azimuth angles
    xrotrad = (xrot / 180 * 3.141592654f);
    this->ycam = -float(sin(xrotrad))*1; // update camera vector
    this->xcam = float(sin(yrotrad))*1 * cos(xrotrad);
    this->zcam = -float(cos(yrotrad))*1 * cos(xrotrad);
    glRotatef(this->xrot, 1.0, 0.0, 0.0); //rotate our camera on the x-axis (left and right)
    glRotatef(this->yrot, 0.0, 1.0, 0.0); //rotate our camera on the y-axis (up and down)
    glTranslated(-this->xpos, -this->ypos, -this->zpos); //translate the screen to the position of our camera
    for (int i = 0; i < this->weapons.size(); i++) {
        glPushMatrix();
        Weapon *w = this->weapons.at(i);
        if (w->t > 2) {
            weapons.erase(weapons.begin() + i);
            delete w;
        } else {
            w->draw(dt);
            bool isFire = w->isFirebomb();
            for (int j = 0; j < w->tris.size(); j++) {
                MeshTriangle *mt = w->tris.at(j);
                for (int k = 0; k < structures->size(); k++) {
                    if (structures->at(k)->intersect(mt->x0, mt->y0, mt->z0,
                            w->xcam, w->ycam, w->zcam, lights, isFire)) {
                        w->collided = true;
                        mt->collided = true;
                        if (w->initCollision && w->collided) {
                            w->setCollisionTrajectories();
                            w->initCollision = false;
                        }
                        if (!isFire) {
                            structures->at(k)->revive();
                            for (int m = lights->size() - 1; m >= 1; m--) {
                                Light *l = lights->at(m);
                                lights->erase(lights->begin() + m);
                                delete l;
                            }
                        }
                    }
                    if (structures->at(k)->intersect(mt->x1, mt->y1, mt->z1,
                            w->xcam, w->ycam, w->zcam, lights, isFire)) {
                        w->collided = true;
                        mt->collided = true;
                        if (w->initCollision && w->collided) {
                            w->setCollisionTrajectories();
                            w->initCollision = false;
                        }
                        if (!isFire) {
                            structures->at(k)->revive();
                            for (int m = lights->size() - 1; m >= 1; m--) {
                                Light *l = lights->at(m);
                                lights->erase(lights->begin() + m);
                                delete l;
                            }
                        }
                    }
                    if (structures->at(k)->intersect(mt->x2, mt->y2, mt->z2,
                            w->xcam, w->ycam, w->zcam, lights, isFire)) {
                        w->collided = true;
                        mt->collided = true;
                        if (w->initCollision && w->collided) {
                            w->setCollisionTrajectories();
                            w->initCollision = false;
                        }
                        if (!isFire) {
                            structures->at(k)->revive();
                            for (int m = lights->size() - 1; m >= 1; m--) {
                                Light *l = lights->at(m);
                                lights->erase(lights->begin() + m);
                                delete l;
                            }
                        }
                    }
                }
                if (w->ypos <= 0) {
                    w->collided = true;
                    w->ypos = 1;
                        mt->collided = true;
                        if (w->initCollision && w->collided) {
                            w->setCollisionTrajectories();
                            w->initCollision = false;
                        }
                }
            }
        }
        glPopMatrix();
    }
}

void Player::mouseMovement(int x, int y) {
    int diffx = x - lastx; //check the difference between the current x and the last x position
    int diffy = y - lasty; //check the difference between the current y and the last y position
    lastx = x; //set lastx to the current x position
    lasty = y; //set lasty to the current y position
    if (!firstTouch) {
        xrot += (float) diffy; //set the xrot to xrot with the addition of the difference in the y position
        yrot += (float) diffx; //set the xrot to yrot with the addition of the difference in the x position
    } else {
        firstTouch = false;
    }
    if (xrot > 90) xrot = 90; // Fix azimuth range to 180 degrees
    if (xrot < -90) xrot = -90;

    if (yrot > 360) yrot -= 360; // Keep polar angle between -360 and 360
    if (yrot < -360) yrot += 360;
}

void Player::keyboard(bool *keys, double dt) {
    float sineStep = (movePerSec * dt) * float(sin(yrotrad)); // depending on the polar angle,
    float cosStep = (movePerSec * dt) * float(cos(yrotrad)); // the step increments change

    if (keys['w']) { // forward
        xpos += sineStep;
        zpos -= cosStep;
    }

    if (keys['s']) { // backward
        xpos -= sineStep;
        zpos += cosStep;
    }

    if (keys['d']) { // right
        xpos += cosStep;
        zpos += sineStep;
    }

    if (keys['a']) { // left
        xpos -= cosStep;
        zpos -= sineStep;
    }

    //    if (keys['t']) {
    //        if (this->weapons.size() < 1) {
    //            this->weapons.push_back(new Firebomb("firebomb.msh", this->xpos, this->ypos, this->zpos,
    //                this->xcam, this->ycam, this->zcam));
    //        }
    //    }
}

