#include "mesh.h"
#include <QFile>
#include <QTextStream>

QVector<Mesh*> Mesh::ptr;

Mesh::Mesh()
{

}

Mesh::Mesh(const QString filePath)
{
	loadOBJ(filePath);
}

Mesh::~Mesh()
{

}

Mesh* Mesh::genMesh(QString path)
{
	for(int i=0;i<ptr.size();++i)
		if(ptr[i]->name == path)
			return ptr[i];
	ptr.append(new Mesh(path));
	ptr.last()->id = ptr.size()-1;
	return ptr.last();
}

void Mesh::loadOBJ(const QString filePath)
{
	QFile file(filePath);
	if(!file.open(QIODevice::ReadOnly))
		return;

	QVector<vec3> fileUvs;
	QVector<vec3> fileNormals;
	QVector<QVector<unsigned int> > fileFaces;
	QVector<int> vertexNext;
	int currentPart = 0;
	name = filePath;

	QTextStream data(&file);
	while(!data.atEnd()){
		QString line = data.readLine();
		if(line.size() == 0 || line[0] == '#')
			continue;
		QStringList arg = line.split(' ');
		if(arg.size() >= 4 && arg[0] == "v"){
			vertices.push_back(vec3(arg[1].toFloat(), arg[2].toFloat(), arg[3].toFloat()));
			uvs.push_back(vec3(0.0f, 0.0f, 1.0f));
			normals.push_back(vec3(0.0f, 0.0f, 0.0f));
			vertexNext.push_back(0);
		}
		else if(arg.size() >= 3 && arg[0] == "vt"){
			fileUvs.push_back(vec3(arg[1].toFloat(), arg[2].toFloat(), 0));
		}
		else if(arg.size() >= 4 && arg[0] == "vn"){
			fileNormals.push_back(vec3(arg[1].toFloat(), arg[2].toFloat(), arg[3].toFloat()));
		}
		else if(arg.size() >= 4 && arg[0] == "f"){
			for(int i = 1;i<arg.size();++i){
				unsigned int fv = ~0, fvt = ~0, fvn = ~0;
				QStringList info = arg[i].split('/');
				if(info.size() == 1){
					fv = info[0].toInt() - 1;
				}
				else if(info.size() == 2){
					fv = info[0].toInt() - 1;
					fvt = info[1].toInt() - 1;
				}
				else if(info.size() == 3){
					fv = info[0].toInt() - 1;
					fvt = info[1].toInt() - 1;
					fvn = info[2].toInt() - 1;
				}
				if((fvt==~0||uvs[fv]==fileUvs[fvt])&&(fvn==~0||normals[fv]==fileNormals[fvn])){
					fileFaces[currentPart].append(fv);
				}
				else if(uvs[fv].z==1&&normals[fv]==vec3::ZERO){
					uvs[fv] = fileUvs[fvt];
					normals[fv] = fileNormals[fvn];
					fileFaces[currentPart].append(fv);
				}
				else{
					vertices.push_back(vertices[fv]);
					uvs.push_back(fileUvs[fvt]);
					normals.push_back(fileNormals[fvn]);
					vertexNext.push_back(0);
					vertexNext[fv] = vertices.size()-1;
					fileFaces[currentPart].append(vertices.size()-1);
				}
			}
			fileFaces[currentPart].append(0xffffffff);
		}
		else if(arg.size() >= 2 && arg[0] == "mtllib"){
			QString path;
			QStringList pathSplit = QString(filePath).split('/');
			for(int i = 0;i < pathSplit.size()-1;++i)
				path += pathSplit[i] + '/';
			loadMTL(path + arg[1]);
			fileFaces.resize(parts.size());
		}
		else if(arg.size() >= 2 && arg[0] == "usemtl"){
			currentPart = materialName[arg[1]];
		}
	}
	file.close();
	for(int i=0;i<parts.size();++i){
		parts[i].bufferOffset = faces.size();
		faces += fileFaces[i];
	}
	isLoad = false;
}

void Mesh::loadMTL(const QString filePath)
{
	QFile file(filePath);
	if(!file.open(QIODevice::ReadOnly))
		return;
	QTextStream data(&file);
	while(!data.atEnd()){
		QString line = data.readLine();
		if(line.size() == 0 || line[0] == '#')
			continue;
		QStringList arg = line.split(' ');
		if(arg.size() >= 2 && arg[0] == "newmtl"){
			materialName.insert(arg[1], materialName.size());
			parts.push_back(Part());
			parts.last().material.texture = NULL;
		}
		else if(arg.size() >= 4 && arg[0] == "Ka"){
			parts.last().material.Ka = vec3(arg[1].toFloat(), arg[2].toFloat(), arg[3].toFloat());
		}
		else if(arg.size() >= 4 && arg[0] == "Kd"){
			parts.last().material.Kd = vec3(arg[1].toFloat(), arg[2].toFloat(), arg[3].toFloat());
		}
		else if(arg.size() >= 4 && arg[0] == "Ks"){
			parts.last().material.Ks = vec3(arg[1].toFloat(), arg[2].toFloat(), arg[3].toFloat());
		}
		else if(arg.size() >= 2 && arg[0] == "Ns"){
			parts.last().material.Ns = arg[1].toFloat();
		}
		else if(arg.size() >= 2 && (arg[0] == "d" || arg[0] == "Tr")){
			parts.last().material.d = arg[1].toFloat();
		}
		else if(arg.size() >= 2 && arg[0] == "map_Kd"){
			QString path;
			QStringList pathSplit = QString(filePath).split('/');
			for(int i = 0;i < pathSplit.size()-1;++i)
				path += pathSplit[i] + '/';
			parts.last().material.texture = Texture::genTexture(path + arg[1]);
		}
	}
	file.close();
}

void Mesh::clear()
{
	vertices.clear();
	uvs.clear();
	normals.clear();
	materialName.clear();
	parts.clear();
	name = "noname";
	isLoad = false;
}
