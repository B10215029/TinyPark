#include "gameobject.h"

int GameObject::NumOfID = 0;

GameObject::GameObject(const vec3& p, const vec3& r, const vec3& s)
{
	id = ++NumOfID;
	position = p;
	rotation = r;
	scale = s;
	name = "GameObject";
	active = true;
	mesh = NULL;
	parent = NULL;
	children.clear();
	animationType = 0;
	isClone = false;
}

GameObject::GameObject(const QString n, const vec3& p, const vec3& r, const vec3& s)
{
	id = ++NumOfID;
	position = p;
	rotation = r;
	scale = s;
	name = n;
	active = true;
	mesh = NULL;
	parent = NULL;
	children.clear();
	animationType = 0;
	isClone = false;
}

GameObject::GameObject(const GameObject& other){
	id = ++NumOfID;
	position = other.position;
	rotation = other.rotation;
	scale = other.scale;
	name = other.name;
	active = other.active;
	mesh = other.mesh;
	setParent(other.parent);
	for(int i=0;i<other.children.size();++i) {
		GameObject* newChild = new GameObject(*other.children[i]);
		newChild->isClone = true;
		setChild(newChild);
	}
	animationType = other.animationType;
	isClone = false;
}

GameObject::~GameObject()
{
	for(int i=0;i<children.size();++i)
		if(children[i]->isClone)
			delete children[i];
}

GameObject& GameObject::operator=(const GameObject &other){
	id = ++NumOfID;
	position = other.position;
	rotation = other.rotation;
	scale = other.scale;
	name = other.name;
	active = other.active;
	mesh = other.mesh;
	setParent(other.parent);
	for(int i=0;i<other.children.size();++i) {
		GameObject* newChild = new GameObject(*other.children[i]);
		newChild->isClone = true;
		setChild(newChild);
	}
	animationType = other.animationType;
	return *this;
}

int GameObject::childCount()
{
	return children.size();
}

void GameObject::detachChildren()
{
	for(int i=0;i<children.size();++i)
		children[i]->setParent(parent);
}

void GameObject::detachParent()
{
	if(parent)
		setParent(parent->parent);
}

GameObject* GameObject::find(QString n)
{
	for(int i=0;i<children.size();++i)
		if(children[i]->name == n)
			return children[i];
	return NULL;
}

GameObject* GameObject::getChild(int index)
{
	if(index >= 0 && index < children.size())
		return children[index];
	else
		return NULL;
}

GameObject* GameObject::getParent()
{
	return parent;
}

bool GameObject::isChildOf(GameObject* p)
{
	for(int i=0;i<children.size();++i)
		if(children[i] == p)
			return true;
	return false;
}

void GameObject::setParent(GameObject* p)
{
	if(parent) {
		for(int i=0;i<parent->children.size();++i)
			if(parent->children[i] == this)
				parent->children.remove(i);
		parent = p;
		p->children.append(this);
	}
	else {
		parent = p;
		p->children.append(this);
	}
}

void GameObject::setChild(GameObject* p)
{
	p->setParent(this);
}

void GameObject::animation(float t)
{

}

