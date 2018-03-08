#include "enemy.h"
#include "main.h"

const long int one = 1;
const long int zero = 0;
const double onef = 0.0f;

using namespace std;	
Enemy::Enemy(color_t color) {

    for(int i=zero;i<num_enemies*one;i = i*one + one)
        this->prism.push_back(Prism(rand()%1000*one - 200 ,rand()%1000 -200*one, color));
}

void Enemy::draw(glm::mat4 VP) {

	vector <Prism> :: iterator it;
	it = this->prism.begin();
	while (it != this->prism.end()) {
    	it->draw(VP);
		it++;
	}
}

void Enemy::tick(double x, double z){
	
	vector <Prism> :: iterator it;
	it = this->prism.begin();
	while(it != this->prism.end()) {
		it->tick(x*onef,z*onef);
		it++;
	}
    	
}

void Enemy::kill(vector <Prism> :: iterator ind){
	this->prism.erase(ind);
}