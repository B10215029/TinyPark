#include "texture.h"

QVector<Texture*> Texture::ptr;

Texture::Texture(QString path)
{
	id = 0;
	name = "noname";
	isLoad = false;
	image = QImage(path).convertToFormat(QImage::Format_RGBA8888).mirrored();
}

Texture::~Texture()
{

}

Texture* Texture::genTexture(QString path)
{
	for(int i=0;i<ptr.size();++i)
		if(ptr[i]->name == path)
			return ptr[i];
	ptr.append(new Texture(path));
	ptr.last()->id = ptr.size()-1;
	return ptr.last();
}
