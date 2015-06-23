#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <QOpenGLFunctions_4_3_Core>
#include <QString>
#include "scene.h"
#include "gameobject.h"
#include "vec.h"
#include "mat.h"

class ShaderProgram : protected QOpenGLFunctions_4_3_Core
{
public:
	ShaderProgram();
	~ShaderProgram();
	virtual void initializeShaders();
	virtual void resize(int w, int h);
	virtual void render(Scene* scene);
	virtual void renderObject(GameObject *target, mat4 parentModelMatrix = mat4(1));
	virtual void loadShader();

public:
	enum {vPosition, vUV, vNormal};

	QString vertexShaderPath;
	QString fragmentShaderPath;
	GLuint VAO;
	GLuint program;
	GLuint uModelMatrix;
	GLuint uViewMatrix;
	GLuint uProjectionMatrix;
	GLuint uLightDirection;
	GLuint uEyePosition;
	GLuint uKd;
	GLuint uKa;
	GLuint uKs;
	GLuint uNs;
	GLuint ud;
	GLuint uUseTexture;

protected:
	int width;
	int height;
	float time;

};

#endif // SHADERPROGRAM_H
