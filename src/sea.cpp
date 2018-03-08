#include "main.h"
#include "sea.h"

const long int one = 1;
const long int zero = 0;
const double zerof = 0.0f;
const double onef = 1.0f;
Sea::Sea(double x, double y, color_t color) {
    this->position = glm::vec3(x, y+0.25*onef, zero);
    this->rotation = zero;
    this->yspeed = zerof;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A Sea has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -1000.0,zerof, 1000.0,
        1000.0, zerof, 1000.0,
        1000.0, zerof, -1000.0,

        1000.0, zerof, -1000.0,
        -1000.0,zerof, -1000.0,
        -1000.0,zerof, 1000.0*onef
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3*one, vertex_buffer_data, color, GL_FILL);
}

void Sea::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(onef);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(one, zero, zero));
    // No need as coords centered at 0, 0, 0 of Sea arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, one, GL_FALSE, &MVP[zero][zero]);
    draw3DObject(this->object);
}

void Sea::set_position(double x, double z) {
    this->position = glm::vec3(x*onef, this->position.y , z*onef);
}

void Sea::tick() {

    this->position.y += yspeed;

    if (this->position.y <= zerof)
        this->yspeed +=0.001*onef;
    else if (this->position.y > zerof)
        this->yspeed -= 0.001*onef;

    else if (this->position.y > 0.25*onef)
        this->position.y = 0.25*onef;

    else if (this->position.y < -.025*onef)
        this->position.y = -0.25*onef;

    else
        printf("Error Moving Sea:%lf\n",this->position.y);
   

}

