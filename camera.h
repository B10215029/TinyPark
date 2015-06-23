#ifndef CAMERA_H
#define CAMERA_H

#include "gameobject.h"
#include "vec.h"
#include "mat.h"

class Camera : public GameObject
{
public:
	Camera(const vec3& p = vec3(0, 0, 0), const vec3& r = vec3(0, 0, 0), const vec3& s = vec3(1, 1, 1));
	Camera(const QString n, const vec3& p = vec3(0, 0, 0), const vec3& r = vec3(0, 0, 0), const vec3& s = vec3(1, 1, 1));
	~Camera();

	mat4 perspectiveMat();
	mat4 frustumMat();
	mat4 frustumPerspectiveMat();
	mat4 projectionMat();

	mat4 lookAt(vec3 center, vec3 up);
	mat4 viewMat();
	mat4 rotateViewMat();

	void setFrustum(float left, float right, float bottom, float top, float zNear, float zFar);
	void setPerspective(float fov, float aspect, float zNear, float zFar);

	int projectionType;
	float fov;
	float aspect;
	float left;
	float right;
	float bottom;
	float top;
	float zNear;
	float zFar;

};

#endif // CAMERA_H
