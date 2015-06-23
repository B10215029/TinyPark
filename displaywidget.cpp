#include "displaywidget.h"

DisplayWidget::DisplayWidget(QWidget *parent) : QOpenGLWidget(parent)
{
	//initialize variable
	frameNumber = 0;
	elapsedTime.restart();
}

DisplayWidget::~DisplayWidget()
{

}

void DisplayWidget::initializeGL(){

	useingProgram->initializeShaders();
}

void DisplayWidget::resizeGL(int w, int h){
	useingProgram->resize(w, h);
}

void DisplayWidget::paintGL(){
	frameNumber++;
	runTime += elapsedTime.elapsed()/1000.;

	currentScene->time = runTime;
	useingProgram->render(currentScene);

	emit showFPS(QString("FPS:%1\nFN:%2").arg(int(1000./(elapsedTime.elapsed()))).arg(frameNumber));
	elapsedTime.restart();
	this->update();
}

void DisplayWidget::mousePressEvent(QMouseEvent *event){
	emit showMessage("Click!");
}
