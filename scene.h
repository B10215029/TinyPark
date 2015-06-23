#ifndef SCENE_H
#define SCENE_H

#include <QVector>
#include <QString>
#include "gameobject.h"
#include "camera.h"
#include "light.h"

class Scene
{
public:
	Scene();
	Scene(QString filePath);
	~Scene();

	void loadFile(QString filePath);
	void saveFile(QString filePath);

	QString name;
	GameObject root;
	Camera* mainCamera;
	Light* mainLight;
	QVector<Camera*> cameras;
	QVector<Light*> lights;
	float time;
};

#endif // SCENE_H
