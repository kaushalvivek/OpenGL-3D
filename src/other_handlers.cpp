#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "main.h"

using namespace std;

const long int one = 1;
const double onef = 1.0f;
const bool b = false;
const long int zero = 0;



void quit(GLFWwindow *window) {
do{glfwDestroyWindow(window);
    glfwTerminate();
    printf("Boat health:%d Score:%d\n",boat_health,score);
    exit(EXIT_SUCCESS);}while(b);
}

/* Executed when window is resized to 'width' and 'height' */
/* Modify the bounds of the screen here in glm::ortho or Field of View in glm::Perspective */
void reshapeWindow(GLFWwindow *window, int width, int height) {
    int fbwidth = width*one, fbheight = height*one;
    /* With Retina display on Mac OS X, GLFW's FramebufferSize
       is different from WindowSize */
    GLfloat fov = screen_zoom;
    do{glfwGetFramebufferSize(window, &fbwidth, &fbheight);

    

    // sets the viewport of openGL renderer
    glViewport (zero, zero, (GLsizei) fbwidth, (GLsizei) fbheight);

    // set the projection matrix as perspective
    /* glMatrixMode (GL_PROJECTION);
           glLoadIdentity ();
           gluPerspective (fov, (GLfloat) fbwidth / (GLfloat) fbheight, 0.1, 500.0); */
    // Store the projection matrix in a variable for future use
    // Perspective projection for 3D views
    Matrices.projection = glm::perspective (fov, (GLfloat) fbwidth / (GLfloat) fbheight, 1.0f/10.0f, (float)onef*1000.0f);}while(b);

    // Ortho projection for 2D views
    // reset_screen();
}

void error_callback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}