#pragma once
class vec3 {
public:
	vec3();
	vec3(float, float, float);
	bool operator==(vec3 rhs);
	vec3 operator+(vec3 rhs);
	vec3 operator-(vec3 rhs);
	vec3 operator*(vec3 rhs);
	vec3 operator/(vec3 rhs);
	vec3 operator+(float scalar);
	vec3 operator-(float scalar);
	vec3 operator*(float scalar);
	vec3 operator/(float scalar);
	vec3 cross(vec3 rhs);
	float dot(vec3 rhs);
	float length();
	vec3 unit();

	float x;
	float y;
	float z;
};