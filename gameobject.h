#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QVector>
#include <QString>
#include "transform.h"
#include "mesh.h"

class GameObject : public Transform
{
public:
	GameObject(const vec3& p = vec3(0, 0, 0), const vec3& r = vec3(0, 0, 0), const vec3& s = vec3(1, 1, 1));
	GameObject(const QString n, const vec3& p = vec3(0, 0, 0), const vec3& r = vec3(0, 0, 0), const vec3& s = vec3(1, 1, 1));
	GameObject(const GameObject &other);
	~GameObject();

	GameObject& operator=(const GameObject &other);
	int childCount();
	void detachChildren();
	void detachParent();
	GameObject* find(QString n);
	GameObject* getChild(int index);
	GameObject* getParent();
	bool isChildOf(GameObject* p);
	void setParent(GameObject* p);
	void setChild(GameObject* p);
	virtual void animation(float t);

public:
	static int NumOfID;
	unsigned int id;
	QString name;
	bool active;
	Mesh* mesh;
	int animationType;

protected:
	GameObject* parent;
	QVector<GameObject*> children;
	bool isClone;

};

#endif // GAMEOBJECT_H
