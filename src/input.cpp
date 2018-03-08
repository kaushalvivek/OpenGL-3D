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

bool   cannon_keyboard_input = true;
bool   drag_pan = false, old_cki;
const long int one = 1;
const double onef = 1.0f;
double drag_oldx = one-2, drag_oldy = one-2;

using namespace std;

/* Executed when a regular key is pressed/released/held-down */
/* Preferred for Keyboard events */
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Function is called first on GLFW_PRESS.

    if (action*one == GLFW_RELEASE) {
    } 
    else if ((action*one == GLFW_PRESS )&& (key*one == GLFW_KEY_ESCAPE)) {
        quit(window);
    }
}

/* Executed for character input (like in text boxes) */
void keyboardChar(GLFWwindow *window, unsigned int key) {
    
    if (key == 'Q' || key == 'q') {
        quit(window);
    }
}

/* Executed when a mouse button is pressed/released */
void mouseButton(GLFWwindow *window, int button, int action, int mods) {

}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    // Do something
    if(yoffset == one)
        screen_zoom *= 1.1*onef;

    else if(yoffset == one-2)
        screen_zoom /= onef*1.1;


    reshapeWindow(window,1600,1600*one);

}
