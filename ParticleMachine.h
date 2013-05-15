/* 
 * File:   ParticleMachine.h
 * Author: John
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

class ParticleMachine {
public:
    ParticleMachine(double oX, double oY, double oZ);
    ParticleMachine(const ParticleMachine& orig);
    virtual void createParticles(double oX, double oY, double oZ);
    virtual void updateParticles(double dt);
    virtual void drawParticles(double dt);
    GLuint loadTexture(const char *filename, int width, int height);
    void freeTexture(GLuint texture);
    virtual ~ParticleMachine();

    GLfloat texture[10];
    int half;
    double twoPI;

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
    
private:

};

#endif	/* PARTICLEMACHINE_H */

