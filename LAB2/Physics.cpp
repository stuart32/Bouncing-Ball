#include <iostream>
#include <vector>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <chrono>

#include "Physics.h"
#include "Vector.h"

vec3 g = vec3(0.0f, -9.8f, 0.0f);


float mass;
vec3 i_velocity;
vec3 f_velocity;
vec3 position;
vec3 acceleration;
vec3 weight;
vec3 netForce;
float diameter;
int lifetime;
float radius;

Physics::Physics(float m) {
	g = vec3(0.0f, -9.8f, 0.0f);
	mass = m;
	weight = g*(m);
	i_velocity = vec3(0.0f, 0.0f, 0.0f);
	f_velocity = vec3(0.0f, 0.0f, 0.0f);
	position = vec3(0.0f, 0.0f, 0.0f);
	acceleration = vec3(0.0f, 0.0f, 0.0f);
	lifetime = 100;
	diameter = 1.0f;
	radius = 0.5f;
	bool hit = false;

}


void Physics::applyForce(vec3 f) {
	netForce = netForce.operator+(f);
};

void Physics::initState() {
	applyForce(weight);
}

float Physics::getDistance(vec3 v) {
	return sqrt(pow((position.x - v.x), 2) + pow((position.y - v.y), 2) + pow((position.z - v.z), 2));
}



void Physics::setSize(float s) {
	diameter = s;
	radius = s / 2;

};

float Physics::getSize() {
	return diameter;
}




void Physics::collision(Physics body) {
	
};



void Physics::setPosition(vec3 p) {
	position = p;
};


void Physics::calcPosition(float time) {
	vec3 t_velocity = i_velocity.operator+(f_velocity);
	vec3 displacement = t_velocity.operator*((float)time).operator/(2);
	position = position.operator+(displacement);
};



void Physics::calcForce() {

	


};


void Physics::calcAcceleration() {
	acceleration = netForce.operator/(mass);
};


void Physics::calcVelocity(float time) {
	f_velocity = i_velocity + acceleration.operator*(time);
};

void Physics::updateState(float time) {
	calcForce();
	calcAcceleration();
	calcVelocity(time);
	calcPosition(time);
	acceleration = acceleration * 0;
	i_velocity = f_velocity;
	lifetime = lifetime - 1;
};

bool Physics::isDead() {
	if (lifetime == 0) {
		return true;
	}
	else {
		return false;
	}
}


void Physics::setForce(vec3 f) {
	netForce = f;
}


vec3 Physics::impact(float d) {
	vec3 vSqr = f_velocity*f_velocity;
	vec3 e = (vSqr.operator*(mass)).operator/(2.0f);
	return e / d;
}



float Physics::getMass() {
	return mass;
};

vec3 Physics::getPosition() {
	return position;
};

vec3 Physics::getVelocity() {
	return i_velocity;
}

vec3 Physics::getAcceleration() {
	return acceleration;
};

vec3 Physics::getForce() {
	return netForce;
};







