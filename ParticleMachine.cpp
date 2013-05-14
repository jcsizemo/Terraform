/* 
 * File:   ParticleMachine.cpp
 * Author: John
 * 
 * Created on May 13, 2013, 3:35 AM
 */

#include "ParticleMachine.h"

ParticleMachine::ParticleMachine(double oX, double oY, double oZ) {
    this->half = INT_MAX / 2;
    this->twoPI = 2 * 3.14159f;
}

ParticleMachine::ParticleMachine(const ParticleMachine& orig) {
}

ParticleMachine::~ParticleMachine() {
}

void ParticleMachine::createParticles(double oX, double oY, double oZ) {
    
}

void ParticleMachine::updateParticles(double dt) {
    
}

void ParticleMachine::drawParticles(double dt) {
    
}

//function to load the RAW file

GLuint ParticleMachine::loadTexture(const char * filename, int width,
        int height) {
    GLuint texture;
    unsigned char * data;
    FILE * file;

    file = fopen(filename, "rb");
    if (file == NULL) return 0;

    data = (unsigned char *) malloc(width * height * 3);

    fread(data, width * height * 3, 1, file);
    fclose(file);

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
            GL_REPEAT);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
            GL_MODULATE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_LINEAR_MIPMAP_NEAREST);
//
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
            GL_LINEAR);

    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height,
            GL_RGB, GL_UNSIGNED_BYTE, data);

    free(data);

    glDisable(GL_TEXTURE_2D);
    return texture;
}

void ParticleMachine::freeTexture(GLuint texture) {
    glDeleteTextures(1, &texture);
}

