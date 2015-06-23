#include "camera.h"

Camera::Camera(const vec3 &p, const vec3 &r, const vec3 &s) : GameObject("Camera", p, r, s)
{
	projectionType = 0;
	fov = 45;
	aspect = 1;
	left = -10;
	right = 10;
	bottom = -10;
	top = 10;
	zNear = -100;
	zFar = 100;
}

Camera::Camera(const QString n, const vec3 &p, const vec3 &r, const vec3 &s) : GameObject(n, p, r, s)
{
	projectionType = 0;
	fov = 45;
	aspect = 1;
	left = -10;
	right = 10;
	bottom = -10;
	top = 10;
	zNear = -100;
	zFar = 100;
}

Camera::~Camera()
{

}

void Camera::setFrustum(float left, float right, float bottom, float top, float zNear, float zFar)
{
	this->left = left;
	this->right = right;
	this->bottom = bottom;
	this->top = top;
	this->zNear = zNear;
	this->zFar = zFar;
}

void Camera::setPerspective(float fov, float aspect, float zNear, float zFar)
{
	this->fov = fov;
	this->aspect = aspect;
	this->zNear = zNear;
	this->zFar = zFar;
}

mat4 Camera::perspectiveMat()
{

	return mat4(1);
}

mat4 Camera::frustumMat()
{

	return mat4(1);
}

mat4 Camera::frustumPerspectiveMat()
{

	return mat4(1);
}

mat4 Camera::projectionMat()
{

	return mat4(1);
}

mat4 Camera::lookAt(vec3 center, vec3 up)
{

	return mat4(1);
}

mat4 Camera::viewMat()
{

	return mat4(1);
}

mat4 Camera::rotateViewMat()
{

	return mat4(1);
}
