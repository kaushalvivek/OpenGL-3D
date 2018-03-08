#include "main.h"

#ifndef SEA_H
#define SEA_H


class Sea {
public:
    Sea() {}
    Sea(double x, double y, color_t color);
    glm::vec3 position;
    double rotation;
    double yspeed;
    void draw(glm::mat4 VP);
    void set_position(double x, double z);
    void tick();
private:
    VAO *object;
};

#endif // SEA_H
