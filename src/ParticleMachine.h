/* 
 * File:   ParticleMachine.h
 * Author: John
 *
 * Particle machine class used for general purpose particle duties.
 * 
 * Created on May 13, 2013, 3:35 AM
 */

#ifndef PARTICLEMACHINE_H
#define	PARTICLEMACHINE_H

#include <climits>
#include <GL/glew.h>
#if defined(_WIN32)
#include <GL/wglew.h>
#endif

#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <cstdlib>
#include <cmath>

class ParticleMachine {
public:
    // position of machine
    ParticleMachine(double oX, double oY, double oZ);
    ParticleMachine(const ParticleMachine& orig);
    // init particles in an x,y,z position
    virtual void createParticles(double oX, double oY, double oZ);
    // update particles based on time
    virtual void updateParticles(double dt);
    // draw particles
    virtual void drawParticles(double dt);
    // functions to load and free textures to/from memory
    GLuint loadTexture(const char *filename, int width, int height);
    void freeTexture(GLuint texture);
    virtual ~ParticleMachine();

    // texture array
    GLfloat texture[10];
    // this variable is equal to half that of the max integer value
    int half;
    double twoPI;

    // particle structure. has values for the life of the particle, max life,
    // fade rate, x, y, and z positions, rgb values, direction, and gravity.
    // This struct is used in subclasses to control the which in which
    // the particles behave.
    typedef struct {
        double life;
        double maxLife;
        double fade;
        double x;
        double y;
        double z;
        double r;
        double g;
        double b;
        double xDir;
        double yDir;
        double zDir;
        double xGrav;
        double yGrav;
        double zGrav;
        double t;
    } PARTICLES;
    
    PARTICLES Particle[10];
    
    // position of machine
    double oX;
    double oY;
    double oZ;
    
private:

};

#endif	/* PARTICLEMACHINE_H */

