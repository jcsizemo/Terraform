/* 
 * File:   main.cpp
 * Author: John
 *
 * Created on May 1, 2013, 4:26 PM
 */

#include <cstdlib>
#include <GL/glew.h>
#if defined(_WIN32)
#include <GL/wglew.h>
#endif

#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <ctime>
#include <vector>

#include "Player.h"
#include "Mesh.h"
#include "MeshTriangle.h"
#include "Structure.h"
#include "GLScreenCapturer.h"
#include "Light.h"

using namespace std;

// Init screen cap
static GLScreenCapturer screenshot("screenshot-%d.ppm");
bool record = false;

Player *player;
vector<Structure*> structures;
vector<Light*> lights;

Structure *ground;
GLuint grassTexture;
GLuint moonTexture;
GLuint starsTexture;

GLUquadric *moon;
GLUquadric *sky;

bool keys[255];

double dt = -1;
clock_t t;

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h); //set the viewport to the current window specifications
    glMatrixMode(GL_PROJECTION); //set the matrix to projection

    glLoadIdentity();
    gluPerspective(60, (GLfloat) w / (GLfloat) h, 1.0, 1000.0
            ); //set the perspective (angle of sight, width, height, , depth)
    glMatrixMode(GL_MODELVIEW); //set the matrix back to model
    glLoadIdentity();

}

void display(void) {

    dt = (((double) clock() - t) / CLOCKS_PER_SEC);
    t = clock();

    if (record) {
        screenshot.capture(); // record screen cap if enabled
    }

    glClearColor(0.0, 0.0, 0.0, 1.0); //clear the screen to black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST); //enable the depth testing
    glEnable(GL_COLOR_MATERIAL); // enable coloring

    player->camera(dt, &structures, &lights);
    player->keyboard(&keys[0], dt);

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, moonTexture);
    glTranslated(-5,300,0);
    gluSphere(moon,20,36,72);
    glPopMatrix();
    
    glBindTexture(GL_TEXTURE_2D, starsTexture);
    gluSphere(sky,500,36,72);
    
    glBindTexture(GL_TEXTURE_2D, grassTexture);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex3f(-500,0,-500);
    glTexCoord2d(100, 0);
    glVertex3f(500,0,-500);
    glTexCoord2d(100, 100);
    glVertex3f(500,0,500);
    glTexCoord2d(0, 100);
    glVertex3f(-500,0,500);
    glEnd();
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
            GL_MODULATE);
    glDisable(GL_TEXTURE_2D);

    for (int i = 0; i < structures.size(); i++) {
        structures.at(i)->draw(dt, &lights);
    }

    glutSwapBuffers(); //swap the buffers
}

void directional(int key, int x, int y) {


}

// Function controlling keyboard inputs.

void keyDown(unsigned char key, int x, int y) {
    if (!keys[key]) {
        keys[key] = true;
    }

    // toggle program exit with 'escape'
    if (key == 27) {
        exit(0);
    }

    if (key == 'q') { // toggle screen cap
        if (record) {
            record = false;
        } else {
            record = true;
        }
    }

}

void keyUp(unsigned char key, int x, int y) {

    if (keys[key]) {
        keys[key] = false;
    }

}

// Function controlling mouse movement.

void mouseMovement(int x, int y) {
    player->mouseMovement(x, y);
}

// Mouse click function. Sets up joint selection.

void mouseClick(int button, int state, int x, int y) {
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {

    }
    if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {

    }
}

GLuint loadEnvironmentTexture(const char *filename, int w, int h) {
    GLuint texture;
    unsigned char * data;
    FILE * file;
    file = fopen(filename, "rb");
    data = (unsigned char *) malloc(w * h * 3);
    fread(data, w * h * 3, 1, file);
    fclose(file);
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
            GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
            GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h,
            GL_RGB, GL_UNSIGNED_BYTE, data);
    free(data);
    glDisable(GL_TEXTURE_2D);
    return texture;
}

int main(int argc, char** argv) {

    player = new Player(0, 2, 15, 0, 0);

    double color[3] = {0.5, 0.5, 0.5};
    structures.push_back(new Structure("tree.msh", 5, 0, 0, &color[0]));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH); // double and depth buffering
    glutInitWindowSize(1000, 700); // window size
    glutInitWindowPosition(100, 100); // window position on screen
    glutCreateWindow("Terraform"); // window title
    glutDisplayFunc(display); // set display function
    glutIdleFunc(display); // set idle function
    glutReshapeFunc(reshape); // set reshape function
    glutSpecialFunc(directional);

    glutPassiveMotionFunc(mouseMovement); //check for mouse movement
    glutMouseFunc(mouseClick);

    glutKeyboardFunc(keyDown); // set keyboard function
    glutKeyboardUpFunc(keyUp);

    t = clock();
    
    moon = gluNewQuadric();
    sky = gluNewQuadric();
    gluQuadricTexture(moon, GL_TRUE);
    gluQuadricTexture(sky, GL_TRUE);
    lights.push_back(new Light(-5, 300, 0, 1, 1, 1));
    
    grassTexture = loadEnvironmentTexture("grass.raw",256,256);
    moonTexture = loadEnvironmentTexture("moon.raw",2000,1000);
    starsTexture = loadEnvironmentTexture("stars2.raw",1600,900);
    
    glutMainLoop();
    return 0;
}

