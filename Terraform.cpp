/* 
 * File:   main.cpp
 * Author: John
 *
 * Created on May 1, 2013, 4:26 PM
 */

#include <cstdlib>
#include <GL/glew.h>
#include <GLUT/glut.h>

using namespace std;

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

    glClearColor(0.0, 0.0, 0.0, 1.0); //clear the screen to black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
    glLoadIdentity();
    glutSwapBuffers(); //swap the buffers
}

void directional(int key, int x, int y) {

    
}

// Function controlling keyboard inputs.

void keyboard(unsigned char key, int x, int y) {

    // toggle program exit with 'escape'
    if (key == 27) {
        exit(0);
    }

}

// Function controlling mouse movement.

void mouseMovement(int x, int y) {


}

// Mouse click function. Sets up joint selection.

void mouseClick(int button, int state, int x, int y) {
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {

    }
    if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {

    }
}

int main(int argc, char** argv) {
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

