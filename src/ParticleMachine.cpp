/* 
 * File:   ParticleMachine.cpp
 * Author: John
 * 
 * Created on May 13, 2013, 3:35 AM
 * 
 * General purpose particle machine class. Loads a particle texture and
 * contains methods meant to be overriden to define behaviors of different
 * machines.
 */

#include "ParticleMachine.h"

// build half int value and two pi value used frequently in ensuing
// calculations
ParticleMachine::ParticleMachine(double oX, double oY, double oZ) {
    this->half = INT_MAX / 2;
    this->twoPI = 2 * 3.14159f;
}

ParticleMachine::ParticleMachine(const ParticleMachine& orig) {
}

ParticleMachine::~ParticleMachine() {
}

// the following three methods are all overriden by the flame class and
// are general purpose for any other types of possible particle machines
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

    // raw texture data
    data = (unsigned char *) malloc(width * height * 3);

    fread(data, width * height * 3, 1, file);
    fclose(file);

    glEnable(GL_TEXTURE_2D);
    // generate and bind texture to id
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    // tile texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
            GL_REPEAT);
    // modulate
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
            GL_MODULATE);
    // build mipmaps
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_LINEAR_MIPMAP_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
            GL_LINEAR);

    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height,
            GL_RGB, GL_UNSIGNED_BYTE, data);

    free(data);

    glDisable(GL_TEXTURE_2D);
    // return tex id
    return texture;
}

// delete particle texture to avoid memory leaks
void ParticleMachine::freeTexture(GLuint texture) {
    glDeleteTextures(1, &texture);
}

