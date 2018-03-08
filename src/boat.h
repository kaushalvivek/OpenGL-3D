#include "main.h"
#include "objects.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(double x, double z, color_t color);
    glm::vec3 position;
    double rotation;
    double roll;
    void draw(glm::mat4 VP);
    void set_position(double x, double y);
    void tick(double wind);
    long double speed;
    long double yspeed;
    bool jumping;
    bounding_box_t bounding_box();


    Cube plank[6];
    Rectangle sail;
};


#endif // BOAT_H
