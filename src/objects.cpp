#include "objects.h"
#include "main.h"

const double twof = 2.0f;
const bool b = false;
const double onef = 1.0f;
const double zerof = 0.0f;
const long int one = 1;
const long int zero = 0;

Cube::Cube(double x, double y,double z, double width , double height , double depth,  color_t color) {
    this->position = glm::vec3(x*onef, y, z*onef);
    this->rotation = zero;
    this->speed = glm::vec3(zero, zero, zero);
    this->dimensions  = glm::vec3(width,height,depth);
    // depth = 6;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        -width/twof ,-height/twof ,-depth/twof, // triangle 1 : begin
        -width/twof ,-height/twof , depth/twof,
        -width/twof , height/twof , depth/twof, // triangle 1 : end

        width/twof , height/twof ,-depth/twof, // triangle 2 : begin
        -width/twof ,-height/twof ,-depth/twof,
        -width/twof , height/twof ,-depth/twof, // triangle 2 : end

        width/twof ,-height/twof , depth/twof,
        -width/twof ,-height/twof ,-depth/twof,
        width/twof ,-height/twof ,-depth/twof,

        width/twof , height/twof ,-depth/twof,
        width/twof ,-height/twof ,-depth/twof,
        -width/twof ,-height/twof ,-depth/twof,

        -width/twof ,-height/twof ,-depth/twof,
        -width/twof , height/twof , depth/twof,
        -width/twof , height/twof ,-depth/twof,

        width/twof ,-height/twof , depth/twof,
        -width/twof ,-height/twof , depth/twof,
        -width/twof ,-height/twof ,-depth/twof,

        -width/twof , height/twof , depth/twof,
        -width/twof ,-height/twof , depth/twof,
        width/twof ,-height/twof , depth/twof,

        width/twof , height/twof , depth/twof,
        width/twof ,-height/twof ,-depth/twof,
        width/twof , height/twof ,-depth/twof,

        width/twof ,-height/twof ,-depth/twof,
        width/twof , height/twof , depth/twof,
        width/twof ,-height/twof , depth/twof,

        width/twof , height/twof , depth/twof,
        width/twof , height/twof ,-depth/twof,
        -width/twof , height/twof ,-depth/twof,

        width/twof , height/twof , depth/twof,
        -width/twof , height/twof ,-depth/twof,
        -width/twof , height/twof , depth/twof,

        width/twof , height/twof , depth/twof,
        -width/twof , height/twof , depth/twof,
        width/twof ,-height/twof , depth/twof
    };


    this->object = create3DObject(GL_TRIANGLES, 12*3*one, vertex_buffer_data, color, GL_FILL);
}

void Cube::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(onef);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f*onef), glm::vec3(zero, one, zero));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    do{
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, one, GL_FALSE, &MVP[zero][zero]);
    draw3DObject(this->object);} while (b);
}

void Cube::set_position(double x, double y) {
    this->position = glm::vec3(x, y, zero);
}

void Cube::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Cube::bounding_box() {
    double x = this->position.x*one, y = this->position.y*one, z = this->position.z*one;
    double width = this->dimensions.x*one, height = this->dimensions.y*one, depth = this->dimensions.z*one;
    bounding_box_t bbox = { x, y,z, width, height, depth };
    return bbox;
}


Prism::Prism(double x,double z,  color_t color) {
    this->position = glm::vec3(x, zero, z);
    this->rotation = zero;
    this->speed = 0.03*onef;
    // depth = 6;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A Prism has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
       zerof, 6.0f,zerof,
       -twof,zerof,twof,
       -twof,zerof,-twof,

       zerof, 6.0f,zerof,
       -twof,zerof,twof,
        twof,zerof,twof,

        zerof, 6.0f,zerof,
        twof,zerof,-twof,
       -twof,zerof,-twof,

       zerof, 6.0f,zerof,
       twof,zerof,-twof,
       twof,zerof,twof,
    };

    this->object = create3DObject(GL_TRIANGLES, 4*3*one, vertex_buffer_data, color, GL_FILL);
}


// Define Prism

void Prism::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(onef);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f*onef), glm::vec3(zero, one, zero));
    // No need as coords centered at 0, 0, 0 of Prism arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, one, GL_FALSE, &MVP[zero][zero]);
    draw3DObject(this->object);
}

void Prism::set_position(double x, double y) {
    this->position = glm::vec3(x, y, zero);
}

void Prism::tick(double x,double z) {


    if(this->position.z > z*onef)
        this->position.z  -= speed*one;
    else
        this->position.z  += speed*one;


    if(this->position.x > x*onef)
        this->position.x  -= speed*one;
    else
        this->position.x  += speed*one;  

}

bounding_box_t Prism::bounding_box() {
    double x = this->position.x*onef, y = this->position.y*onef, z = this->position.z*onef;
    bounding_box_t bbox = { x, y + 3.0*onef,z, 2, 3*one, 2*one };
    return bbox;
}

// Define Sphere


Sphere::Sphere(double x, double y, double z, color_t color) {
    this->position = glm::vec3(x*onef, y*onef, z*onef);
    this->rotation = zero;
    this->speed = zerof;
    this->yspeed = zerof;
    this->radius = onef;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A Sphere has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[90000*one];
    int sides = 100*one;
    double angle = (2*M_PI)/double(sides);
    int j=zero;
    while(j<sides) {
        int i = zero;
        while (i < sides) {
            int k = sides*i + j*one;
            vertex_buffer_data[9*k*one] = zerof;
            vertex_buffer_data[9*k + one] = zerof;  
            vertex_buffer_data[9*k + 2*one] = radius*sin(j*angle);
            vertex_buffer_data[9*k + 3*one] = radius*cos(i*angle)*cos(j*angle); 
            vertex_buffer_data[9*k + 4*one] = radius*sin(i*angle)*cos(j*angle);
            vertex_buffer_data[9*k + 5*one] = radius*sin(j*angle); 
            vertex_buffer_data[9*k + 6*one] = radius*cos((i+1)*angle)*cos(j*angle); 
            vertex_buffer_data[9*k + 7*one] = radius*sin((i+1)*angle)*cos(j*angle); 
            vertex_buffer_data[9*k + 8*one] = radius*sin(j*angle); 
            i++;
        }
        this->object = create3DObject(GL_TRIANGLES, sides*sides*3, vertex_buffer_data, color, GL_FILL);
        j++;
    }   
}

void Sphere::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(onef);
    // Rotate about y axis and not center of object
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f*onef), glm::vec3(one, zero, zero));
    // No need as coords centered at 0, 0, 0 of Sphere arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, one, GL_FALSE, &MVP[zero][zero]);
    draw3DObject(this->object);
}

void Sphere::set_position(double x, double y,double z) {
    this->position = glm::vec3(x*onef, y*onef, z*onef);
}

bool Sphere::tick() {


    this->position.y += yspeed*onef;
    this->yspeed -= onef/1000.0;

    this->position.z -= speed*cos(rotation*M_PI/180.0f*onef);   
    this->position.x += speed*sin(rotation*M_PI/180.0f*onef); 

    return this->position.y < -5.0f*onef;

}

bounding_box_t Sphere::bounding_box() {
    double x = this->position.x*onef, y = this->position.y*onef, z = this->position.z*onef;
    bounding_box_t bbox = { x*onef, y*onef,z*onef, this->radius, this->radius, this->radius };
    return bbox;
}


// Rectangle for sail


Rectangle::Rectangle(double x, double y, double z,double length, double height, color_t color) {
    this->position = glm::vec3(x*onef, y*onef, z*onef);
    this->rotation = zero;
    this->dimensions = glm::vec2(length,height);    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A Rectangle has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
         zerof,height/twof, length/twof,
         zerof,height/twof, -length/twof,
         zerof,-height/twof,-length/twof,

        zerof ,height/twof,  length/twof,
        zerof,-height/twof, length/twof,
         zerof,-height/twof,-length/twof,


    };
 
    this->object = create3DObject(GL_TRIANGLES, 2*3*one, vertex_buffer_data, color, GL_FILL);
}

void Rectangle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(onef);
    glm::vec3 translate_vec = this->position;
    translate_vec.z -= this->dimensions.x/twof;
    glm::mat4 translate = glm::translate (translate_vec);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f*onef), glm::vec3(zero, one, zero));
    glm::mat4 neg_translate = glm::translate (-translate_vec);    // glTranslatef
    Matrices.model *= (translate * rotate)*neg_translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, one, GL_FALSE, &MVP[zero][zero]);
    draw3DObject(this->object);
}

void Rectangle::set_position(double x, double y,double z) {
    this->position = glm::vec3(x*onef, y*onef, z*onef);
}

bounding_box_t Rectangle::bounding_box() {
    double x = this->position.x*onef, y = this->position.y*onef, z = this->position.z*onef;
    bounding_box_t bbox = { x, y,z, this->dimensions.x*onef, this->dimensions.y*onef, zero};
    return bbox;
}
