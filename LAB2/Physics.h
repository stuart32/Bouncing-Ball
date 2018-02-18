#pragma once


#include <iostream>
#include <vector>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Vector.h"

class Physics {



public:

	vec3 g = vec3(0.0f, 9.8f, 0.0f);

	vec3 i_velocity;
	vec3 f_velocity;
	float mass;
	vec3 position;
	vec3 acceleration;
	vec3 weight;
	//vec3* force;
	vec3 netForce;
	int lifetime;
	float diameter;
	float radius;
	bool hit;


	Physics(float mass);
	void applyForce(vec3 f);
	void initState();
	void setSize(float size);
	float getSize();
	void collision(Physics body);
	void setPosition(vec3 position);
	void calcForce();
	void calcVelocity(float time);
	void calcAcceleration();
	void calcPosition(float time);
	void updateState(float time);
	float getMass();
	vec3 getPosition();
	vec3 getVelocity();
	vec3 getAcceleration();
	vec3 getForce();
	float getDistance(vec3 v);
	bool isDead();
	vec3 impact(float d);
	void setForce(vec3 f);
	
};