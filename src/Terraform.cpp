/* 
 * File:   main.cpp
 * Author: John
 *
 * Created on May 1, 2013, 4:26 PM
 * 
 * Terraform class acting as the driver for all other classes. Initializes
 * the OpenGL states, updates time variable used in time-based animations,
 * builds the game world, updates values used for keyboard/mouse interaction,
 * draws all structures, and updates the player's movement.
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

// player, structure, and light objects
Player *player;
vector<Structure*> structures;
vector<Light*> lights;

// grass, moon, and star textures
GLuint grassTexture;
GLuint moonTexture;
GLuint starsTexture;

// moon and sky objects
GLUquadric *moon;
GLUquadric *sky;

// arrays used for keyboard and mouse interactions. used in time based animation
bool keys[255];
bool mouse[255];

// time variable counting time elapsed per frame
double dt = -1;
clock_t t;

// reshape viewport
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
    //update dt for time based animation
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

    // update player movement, do collision detection, do phong shading
    player->camera(dt, &structures, &lights);
    player->keyboard(&keys[0], dt);

    // draw moon, stars, and grass
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, moonTexture);
    glTranslated(-100,300,0);
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

    // draw interactive structures
    for (int i = 0; i < structures.size(); i++) {
        structures.at(i)->draw(dt, &lights);
    }

    glutSwapBuffers(); //swap the buffers
}

// Function controlling keyboard inputs.

void keyDown(unsigned char key, int x, int y) {
    // set value to true if pressed down
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
    // set key to false if released
    if (keys[key]) {
        keys[key] = false;
    }

}

// Function controlling mouse movement.

void mouseMovement(int x, int y) {
    // update polar/azimuth angles of player
    player->mouseMovement(x, y);
}

void mouseClick(int button, int state, int x, int y) {
    // throw firebomb with left click
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP)) {
        if (player->weapons.size() < 1) {
            player->weapons.push_back(new Firebomb("res/firebomb.msh", player->xpos, player->ypos, player->zpos,
                player->xcam, player->ycam, player->zcam));
        }
    }
    // throw water balloon with right click
    if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_UP)) {
        if (player->weapons.size() < 1) {
            player->weapons.push_back(new WaterBalloon("res/waterballoon.msh", player->xpos, player->ypos, player->zpos,
                player->xcam, player->ycam, player->zcam));
        }
    }
    mouse[button] = state;
}

// load textures for grass, moon, stars
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
    // create player, init position
    player = new Player(0, 2, 15, 0, 0);

    // init trees
    for (int i = -200; i <= 200; i += 400) {
        for (int j = -200; j <= 200; j += 400) {
            structures.push_back(new Structure("res/tree.msh", i, 0, j));
        }
    }
    structures.push_back(new Structure("res/tree.msh", 0, 0, 0));

    // init glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH); // double and depth buffering
    glutEnterGameMode(); //full screen
    // remove comments in the below three lines and comment out the line
    // above for a game window
//    glutInitWindowSize(1000, 700); // window size
//    glutInitWindowPosition(100, 100); // window position on screen
//    glutCreateWindow("Terraform"); // window title
    glutDisplayFunc(display); // set display function
    glutIdleFunc(display); // set idle function
    glutReshapeFunc(reshape); // set reshape function

    glutPassiveMotionFunc(mouseMovement); //check for mouse movement
    glutMouseFunc(mouseClick);  // check for mouse click

    glutKeyboardFunc(keyDown); // set key down function
    glutKeyboardUpFunc(keyUp); // set key up function

    t = clock();        // init clock
    
    moon = gluNewQuadric();     // create moon/sky objects
    sky = gluNewQuadric();
    gluQuadricTexture(moon, GL_TRUE);
    gluQuadricTexture(sky, GL_TRUE);
    lights.push_back(new Light(-100, 300, 0, 1, 1, 1)); // moonlight
    
    // build grass,moon,and star textures
    grassTexture = loadEnvironmentTexture("res/grass.raw",256,256);
    moonTexture = loadEnvironmentTexture("res/moon.raw",2000,1000);
    starsTexture = loadEnvironmentTexture("res/stars.raw",1600,900);
    
    glutMainLoop();
    return 0;
}

