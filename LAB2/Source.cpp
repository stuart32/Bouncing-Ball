// Simplified Renderer application for GP course
// Code is similar to the one in lab 1 but all the graphics sections were refactored into the Graphics Class.
// Extra improvements:
// Reduced OpenGL version from 4.5 to 3.3 to allow it to render in older laptops.
// Added Shapes library for rendering cubes, spheres and vectors.
// Added examples of matrix multiplication on Update.
// Added resize screen and keyboard callbacks.
// 
// Update 2018/01 updated libraries and created project for VS2015.

// Suggestions or extra help please do email me S.Padilla@hw.ac.uk
//
// Note: Do not forget to link the libraries correctly and add the GLEW DLL in your debug/release folder.

#include <iostream>
#include <vector>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <chrono>


#include "Graphics.h"
#include "Shapes.h"
#include "Physics.h"


// FUNCTIONS
void render(double currentTime);
void update(double currentTime);
void startup();
void onResizeCallback(GLFWwindow* window, int w, int h);
void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

// VARIABLES
bool		running = true;

Graphics	myGraphics;		// Runing all the graphics in this object

Cube		myCube;
Sphere		mySphere;
Arrow		arrowX;
Arrow		arrowY;
Arrow		arrowZ;

Physics body(1.0f), ground(0.0f);


float angleY = 0.0f;

float t = 0.001f;			// Global variable for animation

std::chrono::duration<int> s;
std::chrono::duration<float, std::milli> ms;
std::chrono::duration<int, std::ratio<60 * 60>> h;

float deltaTime;
float height = 10;


int main()
{

	double lastTime;
	double currentTime = glfwGetTime();

	int errorGraphics = myGraphics.Init();		// Launch window and graphics context
	if (errorGraphics) return 0;				//Close if something went wrong...

	startup();									// Setup all necessary information for startup (aka. load texture, shaders, models, etc).

												// Mixed graphics and update functions - declared in main for simplicity.
	glfwSetWindowSizeCallback(myGraphics.window, onResizeCallback);			// Set callback for resize
	glfwSetKeyCallback(myGraphics.window, onKeyCallback);					// Set Callback for keys

																			// MAIN LOOP run until the window is closed
	do {
		lastTime = currentTime;
		currentTime = glfwGetTime();		// retrieve timelapse
		deltaTime = (float)(currentTime - lastTime);
		glfwPollEvents();						// poll callbacks
		update(currentTime);					// update (physics, animation, structures, etc)
		render(currentTime);					// call render function.

		glfwSwapBuffers(myGraphics.window);		// swap buffers (avoid flickering and tearing)

		running &= (glfwGetKey(myGraphics.window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);	// exit if escape key pressed
		running &= (glfwWindowShouldClose(myGraphics.window) != GL_TRUE);
	} while (running);

	myGraphics.endProgram();			// Close and clean everything up...

	cout << "\nPress any key to continue...\n";
	cin.ignore(); cin.get(); // delay closing console to read debugging errors.

	return 0;
}

void startup() {

	// Calculate proj_matrix for the first time.
	myGraphics.aspect = (float)myGraphics.windowWidth / (float)myGraphics.windowHeight;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);

	// Load Geometry
	myCube.Load();

	mySphere.Load();
	mySphere.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);	// You can change the shape fill colour, line colour or linewidth 

	arrowX.Load(); arrowY.Load(); arrowZ.Load();
	arrowX.fillColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); arrowX.lineColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	arrowY.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f); arrowY.lineColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	arrowZ.fillColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f); arrowZ.lineColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	body.initState();
	body.setSize(1.0f);
	body.setPosition(vec3(0.0f, 10.0f, -25.0f));
	ground.initState();
	ground.setSize(6.0f);
	ground.setPosition(vec3(0.0f, -5.0f, -25.0f));

	myGraphics.SetOptimisations();		// Cull and depth testing
}

void update(double currentTime) {

	// Calculate Cube movement ( T * R * S ) http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
glm::mat4 mv_matrix_cube =
		glm::translate(glm::vec3(ground.getPosition().x, ground.getPosition().y, ground.getPosition().z)) *
		glm::mat4(1.0f);
 mv_matrix_cube = glm::scale(mv_matrix_cube, glm::vec3(ground.getSize(), ground.getSize(), ground.getSize()));

	
	myCube.mv_matrix = mv_matrix_cube;
	myCube.proj_matrix = myGraphics.proj_matrix;





	// calculate Sphere movement
	glm::mat4 mv_matrix_sphere =
		glm::translate(glm::vec3(body.getPosition().x, body.getPosition().y, body.getPosition().z)) *
		glm::rotate(t, glm::vec3(0.0f, 0.1f, 0.0f)) *
		glm::rotate(t, glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::mat4(1.0f);
	mv_matrix_sphere = glm::scale(mv_matrix_sphere, glm::vec3(body.getSize(), body.getSize(), body.getSize()));


	mySphere.mv_matrix = mv_matrix_sphere;
	mySphere.proj_matrix = myGraphics.proj_matrix;
	



		float d = body.getDistance(ground.position);
		if (d < (body.radius + ground.radius) && body.hit == false) {
		body.applyForce(body.impact(height)*(15));
		body.i_velocity = body.i_velocity.operator*(0);
		height = d;
		body.hit = true;
	}
	else {
		body.setForce(body.weight);
		body.hit = false;
	}


body.updateState(0.05);

	
	
	//ground.updateState(deltaTime);
	
	

	t += 0.01f; // increment movement variable


}

void render(double currentTime) {
	// Clear viewport - start a new frame.
	myGraphics.ClearViewport();

	// Draw
	/*
	for (int i = 0; i < 1; i++) {
		glm::mat4 mv_matrix_cube =
			glm::translate(glm::vec3(body.getPosition().x, body.getPosition().y, body.getPosition().z)) *
			glm::rotate(t, glm::vec3(0.0f, 0.1f, 0.0f)) *
			glm::rotate(t, glm::vec3(1.0f, 0.0f, 0.0f)) *
			glm::mat4(1.0f);

		
		myCube.mv_matrix = mv_matrix_cube;
		myCube.proj_matrix = myGraphics.proj_matrix;
		myCube.Draw();
	}

	*/	
	myCube.Draw();
	mySphere.Draw();


}

void onResizeCallback(GLFWwindow* window, int w, int h) {	// call everytime the window is resized
	myGraphics.windowWidth = w;
	myGraphics.windowHeight = h;

	myGraphics.aspect = (float)w / (float)h;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);
}

void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) { // called everytime a key is pressed
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (key == GLFW_KEY_LEFT) angleY += 0.05f;
}