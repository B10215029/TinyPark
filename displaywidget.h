#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Core>
#include <QTime>
#include "shaderprogram.h"
#include "scene.h"

class DisplayWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_3_Core
{
	Q_OBJECT

public:
	DisplayWidget(QWidget *parent);
	~DisplayWidget();

signals:
	void showFPS(QString);
	void showMessage(QString);

protected:
	//Event
	void mousePressEvent(QMouseEvent *event);
//	void mouseReleaseEvent(QMouseEvent *event);
//	void mouseMoveEvent(QMouseEvent *event);
//	void mouseDoubleClickEvent(QMouseEvent *event);
//	void wheelEvent(QWheelEvent *event);
//	void keyPressEvent(QKeyEvent *event);
//	void keyReleaseEvent(QKeyEvent *event);

	//OpenGL
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

//variable
public:
	unsigned int frameNumber;
	float runTime;
	QTime elapsedTime;
	ShaderProgram* useingProgram;
	Scene* currentScene;

protected:

};

#endif // DISPLAYWIDGET_H
