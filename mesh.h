#ifndef MESH_H
#define MESH_H


#include <QVector>
#include <QMap>
#include <QImage>
#include "vec.h"
#include "texture.h"

typedef struct{
	vec3 Kd;
	vec3 Ka;
	vec3 Ks;
	float Ns;
	float d;
	Texture* texture;
}Material;

typedef struct{
	Material material;
	unsigned int bufferOffset;
}Part;

class Mesh
{
public:
	static QVector<Mesh*> ptr;

	static Mesh* genMesh(QString path);

	Mesh();
	Mesh(const QString filePath);
	~Mesh();

	void loadOBJ(const QString filePath);
	void loadMTL(const QString filePath);
	void clear();

	QVector<vec3> vertices;
	QVector<vec3> uvs;
	QVector<vec3> normals;
	QMap<QString, int> materialName;
	QVector<Part> parts;
	QVector<unsigned int> faces;

	bool id;
	QString name;
	unsigned int elementBuffId;
	unsigned int fvGlBuffId;	//face vertix OpenGL buffer id
	unsigned int ftGlBuffId;
	unsigned int fnGlBuffId;
	bool isLoad;

};

#endif // MESH_H
