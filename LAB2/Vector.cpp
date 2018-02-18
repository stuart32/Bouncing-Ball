#include <iostream>
#include <vector>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Vector.h"

float x, y, z;

vec3::vec3() {

};


vec3::vec3(float a, float b, float c) {
	x = a;
	y = b;
	z = c;
};



bool vec3::operator==(vec3 rhs) {
	return(x == rhs.x && y == rhs.y && z == rhs.z);
}

vec3 vec3::operator+(vec3 rhs) {
	return vec3(x + rhs.x,
		y + rhs.y,
		z + rhs.z);
}


vec3 vec3::operator-(vec3 rhs) {
	return vec3(x - rhs.x,
		y - rhs.y,
		z - rhs.z);
}


vec3 vec3::operator*(vec3 rhs) {
	return vec3(x * rhs.x,
		y * rhs.y,
		z * rhs.z);
}


vec3 vec3::operator/(vec3 rhs) {
	return vec3(x / rhs.x,
		y / rhs.y,
		z / rhs.z);
}


vec3 vec3::operator+(float scalar) {
	return vec3(x + scalar,
		y + scalar,
		z + scalar);
}


vec3 vec3::operator-(float scalar) {
	return vec3(x - scalar,
		y - scalar,
		z - scalar);
}


vec3 vec3::operator*(float scalar) {
	return vec3(x * scalar,
		y * scalar,
		z * scalar);
}


vec3 vec3::operator/(float scalar) {
	return vec3(x / scalar,
		y / scalar,
		z / scalar);
}


float vec3::dot(vec3 rhs) {
	return (x * rhs.x +
		y * rhs.y +
		z * rhs.z);
}



vec3 vec3::cross(vec3 rhs) {
	return vec3(y * rhs.z - z * rhs.y,
		z * rhs.x - x * rhs.z,
		x * rhs.y - y * rhs.x);
}


float vec3::length() {
	return float(sqrt(x*x + y*y + z*z));
}



vec3 vec3::unit() {
	return vec3(x / this->length(),
		y / this->length(),
		z / this->length());
}