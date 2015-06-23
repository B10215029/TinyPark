#ifndef TEXTURE_H
#define TEXTURE_H

#include <QImage>
#include <QVector>
#include <QString>

class Texture
{
public:
	static QVector<Texture*> ptr;

	static Texture* genTexture(QString path);

	Texture(QString path);
	~Texture();

	unsigned int id;
	QString name;
	QImage image;
	unsigned int glTexId;
	bool isLoad;
};

#endif // TEXTURE_H
