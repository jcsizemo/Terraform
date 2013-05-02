/* 
 * File:   main.cpp
 * Author: John
 *
 * Created on May 1, 2013, 4:26 PM
 */

#include <cstdlib>
#include <GL/glew.h>
#include <GLUT/glut.h>
#include <ctime>

#include "Player.h"
#include "Mesh.h"
#include "MeshTriangle.h"

using namespace std;

Player *player;
Mesh *structure;

//time_t lastTime;
double dt = -1;
clock_t t;
bool initTime = true;

void enable(void) {
    GLfloat specular[] = {1, 1, 1, 1}; // specular light for the shiny reflections on the spheres/tower
    GLfloat ambient[] = {0.01, 0.01, 0.01, 1}; // low ambient light.
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    GLfloat diffuse[] = {1, 1, 1, 1}; // diffuse light for the lighting of the spheres/tower
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0}; // white specular material
    GLfloat mat_shininess[] = {50.0}; // shiny!
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    GLfloat light0_position[] = {0, 80, 0, 1}; // Last 1 means light is positional, if a zero then directional
    glShadeModel(GL_SMOOTH); // Put spotlight directly above center platform.
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0); // 45 degree spotlight
    GLfloat spot0_direction[] = {0.0, -1.0, 0.0}; // shine directly downward
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot0_direction);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient); // Set LIGHT1 to have the same parameters
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    GLfloat light1_position[] = {0, 100, -200, 1}; // Set it 100 units above the "playground"
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 60.0); // 60 degree spotlight
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot0_direction); // Straight down
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.5);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

    glEnable(GL_DEPTH_TEST); //enable the depth testing
    glEnable(GL_LIGHTING); //enable the lighting
    glEnable(GL_LIGHT0); //enable LIGHT0
    glEnable(GL_LIGHT1); // enable LIGHT1
    glEnable(GL_BLEND); // enable blending
    glEnable(GL_COLOR_MATERIAL); // enable coloring

}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h); //set the viewport to the current window specifications
    glMatrixMode(GL_PROJECTION); //set the matrix to projection

    glLoadIdentity();
    gluPerspective(60, (GLfloat) w / (GLfloat) h, 1.0, 100.0
            ); //set the perspective (angle of sight, width, height, , depth)
    glMatrixMode(GL_MODELVIEW); //set the matrix back to model
    glLoadIdentity();

}

void display(void) {

    t = clock();

    glClearColor(0.0, 0.0, 0.0, 1.0); //clear the screen to black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
    glLoadIdentity();

    enable();
    player->camera();
    structure->draw();
//    cout << structure->intersect(player->xpos, player->ypos, player->zpos, player->xcam, player->ycam, player->zcam) << endl;

    glPushMatrix();
    glColor3f(1, 0, 0);
    glutSolidCube(2);
    glTranslated(0, 0, -5);
    glColor3f(0, 1, 0);
    glutSolidCube(2);
    glPopMatrix();

    glutSwapBuffers(); //swap the buffers

    t = clock() - t;
    dt = (((double) t) / CLOCKS_PER_SEC);
    cout << dt << endl;
}

void directional(int key, int x, int y) {


}

// Function controlling keyboard inputs.

void keyboard(unsigned char key, int x, int y) {

    player->keyboard(key, x, y, dt);

    // toggle program exit with 'escape'
    if (key == 27) {
        exit(0);
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

int main(int argc, char** argv) {

    player = new Player(0, 2, 15, 0, 0);
    structure = new Mesh("structure.msh", 5, 0, 0);

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

    glutKeyboardFunc(keyboard); // set keyboard function
    glutMainLoop();
    return 0;
}

