#include "transform.h"

Transform::Transform(const vec3& p, const vec3& r, const vec3& s) : position(p), rotation(r), scale(s)
{

}

Transform::~Transform()
{

}

mat4 Transform::translateMat()
{
	return mat4(
		1.0, 0.0, 0.0, position.x,
		0.0, 1.0, 0.0, position.y,
		0.0, 0.0, 1.0, position.z,
		0.0, 0.0, 0.0, 1.0);
}

mat4 Transform::rotateMat()
{
	mat4 rx(1, 0, 0, 0,
			0, cos(RADIAN(rotation.x)), -sin(RADIAN(rotation.x)), 0,
			0, sin(RADIAN(rotation.x)), cos(RADIAN(rotation.x)), 0,
			0, 0, 0, 1);
	mat4 ry(cos(RADIAN(rotation.y)), 0, sin(RADIAN(rotation.y)), 0,
			0, 1, 0, 0,
			-sin(RADIAN(rotation.y)), 0, cos(RADIAN(rotation.y)), 0,
			0, 0, 0, 1);
	mat4 rz(cos(RADIAN(rotation.z)), -sin(RADIAN(rotation.z)), 0, 0,
			sin(RADIAN(rotation.z)), cos(RADIAN(rotation.z)), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
	return rz*ry*rx;
}

mat4 Transform::scaleMat()
{
	return mat4(
		scale.x, 0.0,     0.0,     0.0,
		0.0,     scale.y, 0.0,     0.0,
		0.0,     0.0,     scale.z, 0.0,
		0.0,     0.0,     0.0,     1.0);
}

mat4 Transform::modelMat()
{
	return rotateMat() * scaleMat() * translateMat();
}

void Transform::lookAt(const vec3& target, const vec3& up)
{
	rotation.x = DEGREE(atan2(target.z,target.y))-90;
	rotation.y = DEGREE(acos(target.z/(sqrt(target.x*target.x+target.y*target.y))));
	rotation.z = DEGREE(atan2(up.y, up.x))-90;
}

void Transform::translate(const vec3 &p)
{
	position+=p;
}

void Transform::rotate(const vec3& r)
{
	rotation+=r;
}

void Transform::scaleSize(const vec3 &s)
{
	scale*=s;
}

vec3 Transform::left()
{
	return rotateMat() * vec3(1,0,0);
}

vec3 Transform::up()
{
	return rotateMat() * vec3(0,1,0);
}

vec3 Transform::forward()
{
	return rotateMat() * vec3(0,0,1);
}
