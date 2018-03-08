#include "main.h"
#include "objects.h"

#ifndef ENEMY_H
#define ENEMY_H

#define num_enemies 60

class Enemy {
public:
    Enemy() {}
    void draw(glm::mat4 VP);
    Enemy(color_t color);
    void tick(double x, double z);
    std::vector<Prism> prism;
    void kill(std::vector <Prism> :: iterator ind);
    
};

#endif