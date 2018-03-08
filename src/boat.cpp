#include "boat.h"
#include "main.h"

const long int none = 0;
const long int one = 1;
float onef = 1.0f;

Boat::Boat(double x, double z, color_t color) {
    this->position = glm::vec3(x, none, z);
    this->rotation = none;
    this->roll = none;
    this->jumping = false;
    this->speed = none; 
    this->yspeed = none;

    // left plank
    this->plank[none] =  Cube(-2*one, none,none, 0.2,4,6   ,color);
    // right plank
    this->plank[one] =  Cube( 2*one, none,none, 0.2,4,6   ,color);
    // bottom plank 
    this->plank[2*one] =  Cube( none, one,none, 3.8,0.2,6 ,color);
    // back plank
    this->plank[3*one] =   Cube( none, none,3, 3.8,4,0.2 ,color);
    // front head 1
    this->plank[4*one] =   Cube(1,none, -4 ,1.2,4,4, color);
    this->plank[4*one].rotation = 30;
    // front head 2
    this->plank[5*one] =   Cube(-1,none, -4 ,1.2,4,4, color);;
    this->plank[5*one].rotation = -30;

    this->sail =  Rectangle(none,7*one,-0.5,4*one,12*one,COLOR_SAIL);
    this->sail.rotation = 90*one;
}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f*onef);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f*onef), glm::vec3(none, one, none));
    glm::mat4 roll      = glm::rotate((float) (this->roll * M_PI / 180.0f*onef), glm::vec3(none, none, one));
    // No need as coords centered at 0, 0, 0 of Boat arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate *roll);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, one, GL_FALSE, &MVP[none][none]);
    // draw3DObject(this->object);
    
    for(int i=none;i<6*one;i++)
        plank[i*one].draw(MVP);

    sail.draw(MVP);

}

void Boat::set_position(double x, double y) {
    this->position = glm::vec3(x*onef, y*onef, none);
}

void Boat::tick(double wind){

    this->position.y += (double) yspeed;

    this->position.z += (double)speed*cos(rotation*M_PI/180.0f);   
    this->position.x += (double)speed*sin(rotation*M_PI/180.0f);   

    if(this->position.y > none)
        yspeed -= 0.004;
    else{
        this->position.y = none;
        this->jumping = false;
        yspeed = none;
        
    }

    //Moving sail for wind
    sail.rotation = wind/20;

}

bounding_box_t Boat::bounding_box() {
    double x = this->position.x*onef, y = this->position.y*onef, z = this->position.z*onef;
    // The error in  z is due to the forward planks
    // Width and depth will also depend on the rotation 
    bounding_box_t bbox = { x, y + 2*one,z - 3.5, 6.0f*onef, 3.0f*onef,12.0f*onef };
    return bbox;
}