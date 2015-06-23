#include "shaderprogram.h"
#include <QFile>

ShaderProgram::ShaderProgram()
{
	vertexShaderPath = ":/shaders/shaders/default.vert";
	fragmentShaderPath = ":/shaders/shaders/default.frag";
}

ShaderProgram::~ShaderProgram()
{

}

void ShaderProgram::initializeShaders()
{
	initializeOpenGLFunctions();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(0.5, 0.5, 1.0, 1.0);
	//glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(0xffffffff);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(vPosition);
	glEnableVertexAttribArray(vUV);
	glEnableVertexAttribArray(vNormal);
	glBindVertexArray(0);

	loadShader();
	glUseProgram(program);
	uModelMatrix		 = glGetUniformLocation(program, "modelMatrix");
	uViewMatrix			 = glGetUniformLocation(program, "viewMatrix");
	uProjectionMatrix	 = glGetUniformLocation(program, "projectionMatrix");
	uLightDirection		 = glGetUniformLocation(program, "lightDirection");
	uEyePosition		 = glGetUniformLocation(program, "eyePosition");
	uKa					 = glGetUniformLocation(program, "Ka");
	uKd					 = glGetUniformLocation(program, "Kd");
	uKs					 = glGetUniformLocation(program, "Ks");
	uNs					 = glGetUniformLocation(program, "Ns");
	ud					 = glGetUniformLocation(program, "d");
	uUseTexture			 = glGetUniformLocation(program, "useTexture");
}

void ShaderProgram::resize(int w, int h)
{
	width = w;
	height = h;
}

void ShaderProgram::render(Scene *scene)
{

	glViewport(0,0,width,height);

	glUseProgram(program);
	glUniformMatrix4fv(uViewMatrix, 1, GL_FALSE, scene->mainCamera->viewMat().ptr());
	glUniformMatrix4fv(uProjectionMatrix, 1, GL_FALSE, scene->mainCamera->projectionMat().ptr());
	glUniform3fv(uLightDirection, 1 , scene->mainLight->forward().ptr());
	glUniform3fv(uEyePosition, 1 , scene->mainCamera->position.ptr());
	time = scene->time;
	renderObject(&scene->root);
}

void ShaderProgram::renderObject(GameObject *target, mat4 parentModelMatrix)
{
	target->animation(time);
	parentModelMatrix=target->modelMat()*parentModelMatrix;
	if(target->mesh){
		glUniformMatrix4fv(uModelMatrix, 1, GL_FALSE, parentModelMatrix.ptr());
		if(!target->mesh->isLoad){
			glGenBuffers(1, &target->mesh->elementBuffId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, target->mesh->elementBuffId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*target->mesh->faces.size(), &target->mesh->faces[0], GL_STATIC_DRAW);
			glGenBuffers(1, &target->mesh->fvGlBuffId);
			glBindBuffer(GL_ARRAY_BUFFER, target->mesh->fvGlBuffId);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*target->mesh->vertices.size()*3, &target->mesh->vertices[0], GL_STATIC_DRAW);
			glGenBuffers(1, &target->mesh->ftGlBuffId);
			glBindBuffer(GL_ARRAY_BUFFER, target->mesh->ftGlBuffId);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*target->mesh->uvs.size()*3, &target->mesh->uvs[0], GL_STATIC_DRAW);
			glGenBuffers(1, &target->mesh->fnGlBuffId);
			glBindBuffer(GL_ARRAY_BUFFER, target->mesh->fnGlBuffId);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*target->mesh->normals.size()*3, &target->mesh->normals[0], GL_STATIC_DRAW);
			target->mesh->isLoad = true;
		}
		glBindBuffer(GL_ARRAY_BUFFER, target->mesh->fvGlBuffId);
		glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, target->mesh->ftGlBuffId);
		glVertexAttribPointer(vUV, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, target->mesh->fnGlBuffId);
		glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, target->mesh->elementBuffId);
		for(int i=0;i<target->mesh->parts.size();++i){
			glUniform3fv(uKa, 1 , target->mesh->parts[i].material.Ka.ptr());
			glUniform3fv(uKd, 1 , target->mesh->parts[i].material.Kd.ptr());
			glUniform3fv(uKs, 1 , target->mesh->parts[i].material.Ks.ptr());
			glUniform1f(uNs, target->mesh->parts[i].material.Ns);
			glUniform1f(ud, target->mesh->parts[i].material.d);
			glUniform1i(uUseTexture, target->mesh->parts[i].material.texture?1:0);
			if(target->mesh->parts[i].material.texture){
				glActiveTexture(GL_TEXTURE0);
				if(!target->mesh->parts[i].material.texture->isLoad){
					glGenTextures(1, &target->mesh->parts[i].material.texture->glTexId);
					glBindTexture(GL_TEXTURE_2D, target->mesh->parts[i].material.texture->glTexId);
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, target->mesh->parts[i].material.texture->image.width(), target->mesh->parts[i].material.texture->image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, target->mesh->parts[i].material.texture->image.bits());
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					target->mesh->parts[i].material.texture->isLoad = true;
				}
				glBindTexture(GL_TEXTURE_2D, target->mesh->parts[i].material.texture->glTexId);
			}
			int bfs = target->mesh->parts[i].bufferOffset;
			int bfe = target->mesh->parts.size() == i+1?target->mesh->faces.size()-1:target->mesh->parts[i+1].bufferOffset-1;
			glDrawRangeElements(GL_TRIANGLE_FAN, bfs, bfe, bfe-bfs+1, GL_UNSIGNED_INT, NULL);
		}
	}
	for(int i=0;i<target->childCount();++i)
		renderObject(target->getChild(i), parentModelMatrix);
}

void ShaderProgram::loadShader()
{
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

	std::string VertexShaderCode;
	std::string FragmentShaderCode;
	const char* vs_source;
	const char* fs_source;

	// Read the Vertex Shader code from the file
	QFile VertexShaderFile(vertexShaderPath);
	if(VertexShaderFile.open(QIODevice::ReadOnly)){
		VertexShaderCode=QString(VertexShaderFile.readAll()).toStdString();
		VertexShaderFile.close();
		vs_source = VertexShaderCode.c_str();
	}

	// Read the Fragment Shader code from the file
	QFile FragmentShaderFile(fragmentShaderPath);
	if(FragmentShaderFile.open(QIODevice::ReadOnly)){
		FragmentShaderCode=QString(FragmentShaderFile.readAll()).toStdString();
		FragmentShaderFile.close();
		fs_source = FragmentShaderCode.c_str();
	}

	// Compile Vertex Shader
	glShaderSource(vs,1,&vs_source,NULL);
	glCompileShader(vs);

	// Compile Fragment Shader
	glShaderSource(fs, 1, &fs_source , NULL);
	glCompileShader(fs);

	GLint Result = GL_FALSE;
	int InfoLogLength;
	// Check Vertex Shader
	glGetShaderiv(vs, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		char* VertexShaderErrorMessage = new char[InfoLogLength+1];
		glGetShaderInfoLog(vs, InfoLogLength, NULL, VertexShaderErrorMessage);
		printf("in %s:\n%s\n", vertexShaderPath.toLatin1().data(), VertexShaderErrorMessage);
		delete[] VertexShaderErrorMessage;
	}

	// Check Fragment Shader
	glGetShaderiv(fs, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		char* FragmentShaderErrorMessage = new char[InfoLogLength+1];
		glGetShaderInfoLog(fs, InfoLogLength, NULL, FragmentShaderErrorMessage);
		printf("in %s:\n%s\n", fragmentShaderPath.toLatin1().data(), FragmentShaderErrorMessage);
		delete[] FragmentShaderErrorMessage;
	}

	// Link the program
	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);
}
