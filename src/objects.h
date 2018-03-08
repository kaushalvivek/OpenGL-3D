#include "main.h"

#ifndef OBJECTS
#define OBJECTS


class Cube {
public:
    Cube() {}
    Cube(double x, double y,double z,double width , double height , double depth,  color_t color);
    glm::vec3 position;
    glm::vec3 speed;
    glm::vec3 dimensions;
    double rotation;
    void draw(glm::mat4 VP);
    void set_position(double x, double y);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};


class Prism {
public:
    Prism() {}
    Prism(double x, double z, color_t color);
    glm::vec3 position;
    double rotation;
    void draw(glm::mat4 VP);
    void set_position(double x, double z);
    void tick(double x,double z);
    double speed;
    bounding_box_t bounding_box();

private:
	VAO *object;
};



class Sphere {
public:
    Sphere() {}
    Sphere(double x, double y,double z, color_t color);
    glm::vec3 position;
    double rotation;
    void draw(glm::mat4 VP);
    void set_position(double x, double y ,double z);
    bool tick();
    double speed;
    double yspeed;
    double radius;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

class Rectangle {
public:
    Rectangle() {}
    Rectangle(double x, double y,double z,double length, double height, color_t color);
    glm::vec3 position;
    glm::vec2 dimensions;
    double rotation;
    void draw(glm::mat4 VP);
    void set_position(double x, double y ,double z);
    bool tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};


#endif // OBJECTS