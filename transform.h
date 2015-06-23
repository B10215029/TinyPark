#ifndef TRANSFORM_H
#define TRANSFORM_H
#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif
#ifndef RADIAN
#define RADIAN(x) (x*(PI/180.0))
#endif
#ifndef DEGREE
#define DEGREE(x) (x*(180.0/PI))
#endif

#include <cmath>
#include "vec.h"
#include "mat.h"

class Transform
{
public:
	Transform(const vec3& p = vec3(0, 0, 0), const vec3& r = vec3(0, 0, 0), const vec3& s = vec3(1, 1, 1));
	~Transform();

	mat4 translateMat();
	mat4 rotateMat();
	mat4 scaleMat();
	mat4 modelMat();

	void lookAt(const vec3& target, const vec3& up = vec3(0.0, 1.0, 0.0));
	void translate(const vec3& p);
	void rotate(const vec3& r);
	void scaleSize(const vec3& s);

	vec3 left();
	vec3 up();
	vec3 forward();

	vec3 position;
	vec3 rotation;
	vec3 scale;
};

#endif // TRANSFORM_H
