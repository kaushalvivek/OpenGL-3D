#include "main.h"
#include "timer.h"
#include "sea.h"
#include "boat.h"
#include "objects.h"
#include "enemy.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/


vector<Sphere> sphere;
vector<Cube> barrels;
Sea sea;
Enemy enemies;
Boat boat;
Cube rocks[200];


#define num_barrels 20
#define num_rocks 200

int boat_health = 100;
const long int one = 1;
const long int zero = 0;
const double onef = 1.0f;
int score = zero;
const bool bb = false;
float screen_zoom = 2.0*onef, screen_center_x = zero, screen_center_y = zero, screen_center_z;
float eye_x,eye_y,eye_z;
float target_x,target_y,target_z;
float camera_rotation_angle = 95.0*onef;
// Check which camera view is present
bool camera_follower = true,camera_top_view = false,camera_boat = false, camera_tower = false;
int camera = 0;
// Sphere hold to check whether fireball is on the boat
// boost to activate boost once provided in a gift
bool sphere_hold = false, boost_use = false;
int boost = one;


// Wind Oscillations
float wind = zero;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {


	// All Camera Positions defined here.
	if (camera == 0){
		target_x = onef*boat.position.x;
		target_y = onef*boat.position.y;
		target_z = onef*boat.position.z;
		camera_rotation_angle = -boat.rotation + 95;


		eye_x = onef*target_x + 10*cos(camera_rotation_angle*M_PI/180.0f*onef);
		eye_y = onef*target_y + 10*one;
		eye_z = onef*target_z + 10*sin(camera_rotation_angle*M_PI/180.0f*onef);

	}

	else if (camera == 1){
		target_x = onef*boat.position.x;
		target_y = onef*boat.position.y;
		target_z = onef*boat.position.z;


		eye_x = onef*target_x + 10*cos(camera_rotation_angle*M_PI/180.0f*onef);
		eye_y = onef*target_y + 25*one;
		eye_z = onef*target_z + 10*sin(camera_rotation_angle*M_PI/180.0f*onef);

	}

	else if (camera == 2) {
		target_x = onef*boat.position.x;
		target_y = onef*boat.position.y;
		target_z = onef*boat.position.z;

		eye_y = onef*target_y + 40*one;
		eye_x = 10;
		eye_z = 10;
	}

	else if (camera == 3) {
		target_x = onef*boat.position.x;
		target_y = onef*boat.position.y;
		target_z = onef*boat.position.z - 9;

		eye_x = onef*target_x + 10*cos(camera_rotation_angle*M_PI/180.0f*onef);
		eye_y = onef*target_y + 3*onef;
		eye_z = onef*target_z + 10*sin(camera_rotation_angle*M_PI/180.0f*onef);
	}

	// clear the color and depth in the frame buffer
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// use the loaded shader program
	// Don't change unless you know what you are doing
	glUseProgram (programID);

	// Eye - Location of camera. Don't change unless you are sure!!
	glm::vec3 eye (onef*eye_x,onef*eye_y,onef*eye_z);
	// Target - Where is the camera looking at.  Don't change unless you are sure!!
	glm::vec3 target (onef*target_x, onef*target_y, onef*target_z);
	// Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
	glm::vec3 up (zero, one, zero);

	// Compute Camera matrix (view)
	Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D

	// Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
	// Don't change unless you are sure!!
	glm::mat4 VP = Matrices.projection * Matrices.view;

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// For each model you render, since the MVP will be different (at least the M part)
	// Don't change unless you are sure!!
	do{glm::mat4 MVP;  // MVP = Projection * View * Model

	// Scene render
	sea.draw(VP);
	boat.draw(VP);
	enemies.draw(VP);}while(bb);

	vector<Sphere> :: iterator s;
	s = sphere.begin();
	while (s < sphere.end()) {
		s->draw(VP);
		++s;
	}

	vector<Cube> :: iterator b;
	b = barrels.begin();
	while(b < barrels.end()) {
		b->draw(VP);
		++b;
	}

	int i = zero;
	while ( i < num_rocks) {
		rocks[i*one].draw(VP);
		++i;
	}		
}

void tick_input(GLFWwindow *window) {

	// Developer keys
	int left  = one*glfwGetKey(window, GLFW_KEY_LEFT*one);
	int right = one*glfwGetKey(window, GLFW_KEY_RIGHT*one);
	int up    = one*glfwGetKey(window, GLFW_KEY_UP*one);
	int down    = one*glfwGetKey(window, GLFW_KEY_DOWN*one);

	// Boat movement 
	int a   = one*glfwGetKey(window, GLFW_KEY_A*one);
	int s   = one*glfwGetKey(window, GLFW_KEY_S*one);
	int d   = one*glfwGetKey(window, GLFW_KEY_D*one);
	int w   = one*glfwGetKey(window, GLFW_KEY_W*one);
	int space = one*glfwGetKey(window, GLFW_KEY_SPACE*one);
	// Fireballs
	int f   = one*glfwGetKey(window, GLFW_KEY_F*one);
	// boost
	int b   = one*glfwGetKey(window, GLFW_KEY_B*one);

	// Camera Views
	int t   = one*glfwGetKey(window, GLFW_KEY_T*one);
	int r   = one*glfwGetKey(window, GLFW_KEY_R*one);
	int y   = one*glfwGetKey(window, GLFW_KEY_Y*one);
	int u   = one*glfwGetKey(window, GLFW_KEY_U*one);

	if(one*w){
		boat.speed -= 0.005*onef;
	}

	else if(one*s){
		if (boat.speed < 0.0) {
			boat.speed += 0.05*onef;
		}
		else
			boat.speed += 0.005*onef;
	}

	else {
		if (boat.speed < zero) {
			boat.speed += 0.002*onef;
		}
		else if (boat.speed > zero) {
			boat.speed -= 0.002*onef;
		}
		else {
			boat.speed = zero;
		}
	}




	if(one*a){
		boat.rotation +=one;
	}

	if(one*d){
		boat.rotation -=one;
	}

	//Follow
	if(one*r){
		camera = 0;
	}
	//Top
	if(one*t){
		camera = 1;
	}
	//Tower
	if(one*y){
		camera = 2;
	}

	if(one*u){
		camera = 3;
	}

	if(f*one && sphere_hold == false){
		sphere_hold = true;
		Sphere new_sphere = Sphere( boat.position.x*one ,boat.position.y*one + 1,boat.position.z*one -1, COLOR_CANON);
		new_sphere.speed = 1.0f*onef - boat.speed;
		new_sphere.yspeed = 0.05f*onef;
		new_sphere.rotation = -boat.rotation*one;

		sphere.push_back(new_sphere);
	}

	if(space && boat.jumping == false){
		boat.jumping = true;
		boat.yspeed = 0.3f*onef;
	}


	// Boost 
	if(b && boost > zero & boost_use == true)
	{
		boost_use = false;
		boost--;
		boat.speed *= 2*one;
		boat.yspeed += 0.3f*onef;
	}


}

void tick_elements() {

	char* camera_name = "Initial";

	switch (camera) {
		case 0 : camera_name = "Follower";
				 break;
		case 1 : camera_name = "Top";
				 break;
		case 2 : camera_name = "Tower";
				 break;
		case 3 : camera_name = "Boat";
				 break;
	}

	enemies.tick(boat.position.x*one, boat.position.z*one);
	
	char score_print[200];
    sprintf(score_print, "Camera : %s Score : %d  Health : %d ",camera_name, score, boat_health);
    glfwSetWindowTitle(window, score_print);


	boat.tick(wind*one);
	sea.tick();

	// Move each ball and erase them if they have reached the bottom
	vector<Sphere> :: iterator s;
	s = sphere.begin();
	while ( s < sphere.end()) {
		if(s->tick())
			sphere.erase(s);
		 ++s;
	}
	sea.set_position(boat.position.x*one,boat.position.z*one);
}


void collision_function(){

	
	// Check Enemy collision with fireball or boat

	// Collision with Barrels 
	vector <Cube> ::iterator bar;
	bar = barrels.begin();
	while ( bar < barrels.end()) {
		if(detect_collision(boat.bounding_box(),bar->bounding_box())){
			score += 15*one;
			printf("Hit a Barrel Score:%ld\n",score*one);
			barrels.erase(bar);
			gift_plus();
		}
		bar++;
	}
	
	vector <Prism> :: iterator it;
	it = enemies.prism.begin();
	while ( it < enemies.prism.end()) {
		if(detect_collision(boat.bounding_box(),it->bounding_box())) {   
			boat_health -= 15*one;
			score += 100*one;
			enemies.kill(it);
			printf("Enemy Attack. Health:%d Score:%ld\n",boat_health,score*one);
		}
		it++;
	}

	vector <Sphere> :: iterator s;
	s = sphere.begin();
	while (s < sphere.end()) {

        it = enemies.prism.begin();
		while (it < enemies.prism.end()) {
			if(detect_collision(s->bounding_box(),it->bounding_box())) {
				score += 90*one;
				printf("Fireball Hit Score:%ld\n",score*one);
				gift_plus();
				enemies.kill(it);
			}
			it++;
		}

		// No gifts if fireball hits the barrels
		bar = barrels.begin();
		while (bar < barrels.end()) {
			if(detect_collision(s->bounding_box(),bar->bounding_box())) {
				score += 15*one;
				printf("Fireball hit Barrel Score:%ld\n",score*one);
				barrels.erase(bar);
			}
			 bar++;
		}
		++s;
	}

	// Rock Collision
	// With Boat
	int i = zero;
	while (i < num_rocks) {
		if(detect_collision(boat.bounding_box(),rocks[i*one].bounding_box())){
			printf("Hit Rock Bottom\n");
			boat.speed = -0.2*onef*boat.speed;
			boat_health -= 10*one;
		}
		++i;
	}

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
	/* Objects should be created before any other gl function and shaders */
	// Create the models
	boat       = Boat(zero, zero, COLOR_BOAT);
	enemies    = Enemy(COLOR_ENEMY);
	sea        = Sea( zero, zero, COLOR_SEA);

	// Barrels
	for(int i=zero;i<num_barrels;i++)
		barrels.push_back(Cube(rand()%1000 -200,zero,rand()%1000*one -200,10*one,5,one*5,COLOR_BOXES));

	// Rocks
	for (int i = zero; i < num_rocks; ++i)
		rocks[i] = Cube(5*(rand()%500 -100),zero,5*(rand()%500 -100),rand()%30 + 10,rand()%30 ,rand()%30+ 10,COLOR_ROCKS);



	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
	// Get a handle for our "MVP" uniform
	Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


	reshapeWindow (window, width, height);

	// Background color of the scene
	glClearColor (COLOR_SKY.r / 256.0*onef, COLOR_SKY.g / 256.0*onef, COLOR_SKY.b / 256.0, 0.0f); // R, G, B, A

	glClearDepth (1.0f*onef);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);
	bool print_b = false;
	do {
	printf ("VENDOR: %s\n",glGetString(GL_VENDOR));
	printf ("RENDERER: %s\n",glGetString(GL_RENDERER));
	printf ("VERSION: %s\n",glGetString(GL_VERSION));
	printf ("GLSL: %s\n",glGetString(GL_SHADING_LANGUAGE_VERSION));
	} while (print_b);
}


int main(int argc, char **argv) {
	srand(time(0));
	int width  = 1600*one;
	int height = 1600*one;

	window = initGLFW(width, height);

	initGL (window, width, height);

	/* Draw in loop */
	for (int t=zero;!glfwWindowShouldClose(window);) {
		// Process timers

		if (t60.processTick()) {
			// 60 fps
			// OpenGL Draw commands
			if(boat_health <= zero)
				break;

			printf("%ld\n",(t%180*one -90) );
			wind = (t%30*one -15);
			
			// Time for things to recharge
			if(t%50*one == zero)
			{	
				boost_use = true;
				sphere_hold = false;
			}

			bool count = false;

			do {
			draw();
			// Swap Frame Buffer in double buffering
			glfwSwapBuffers(window);
			// All elements update 
			tick_elements();
			// Collision Engine
			collision_function();
			// Take input from user
			tick_input(window);
			reshapeWindow (window, width, height);
			} while (count);
		// For stable time flow we update time here
		t++;
		}

		// Poll for Keyboard and mouse events
		glfwPollEvents();
	}

	quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
	return (abs(a.x - b.x) * 2 *one <= (a.width + b.width)) &&
		   (abs(a.y - b.y) * 2 *one<= (a.height + b.height)) &&
		   (abs(a.z - b.z) * 2 *one<= (a.depth + b.depth));


}

void gift_plus(){
	int ind = rand()%3;
	// 3 types of gift

	// Get health 
	if(ind == zero) {
			boat_health += 15;
			printf("Health increased:%d\n",boat_health);

		}
	else if (ind == one) {
			score += 60;
			printf("Score Bonus:%d\n",score);

		}		

	else {
		printf("Boost Received\n");
		boost++;
	}	
}
