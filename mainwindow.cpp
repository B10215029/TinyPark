#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->openGLWidget, SIGNAL(showFPS(QString)), ui->label, SLOT(setText(QString)));
	connect(ui->openGLWidget, SIGNAL(showMessage(QString)), ui->statusBar, SLOT(showMessage(QString)));
	ui->openGLWidget->useingProgram = new ShaderProgram();
	ui->openGLWidget->currentScene = new Scene();
	ui->openGLWidget->currentScene->cameras.append(new Camera());
	ui->openGLWidget->currentScene->mainCamera = ui->openGLWidget->currentScene->cameras[0];
	ui->openGLWidget->currentScene->lights.append(new Light());
	ui->openGLWidget->currentScene->mainLight = ui->openGLWidget->currentScene->lights[0];
}

MainWindow::~MainWindow()
{
	delete ui;
}
