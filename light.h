#ifndef LIGHT_H
#define LIGHT_H

#include "camera.h"
#include "vec.h"

class Light : public Camera
{
public:
	Light();
	~Light();

	int lightType;
	vec3 lightColor;
	float intensity;
	float spotAngle;
	float areaSize;
};

#endif // LIGHT_H
