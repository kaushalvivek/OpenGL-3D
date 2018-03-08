#include "timer.h"
#include <GLFW/glfw3.h>

const float zero = 0.0f;
Timer::Timer(float interval) {
    prev = zero;
    this->interval = interval;
}

bool Timer::processTick() {
    float cur = glfwGetTime();
    if (cur - prev >= interval) {
        prev = cur;
        return true;
    } else
        return false;
}
