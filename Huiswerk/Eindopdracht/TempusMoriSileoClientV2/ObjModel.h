#pragma once
#include "stdafx.h"
#include "ObjTexture.h"
#include "S_Vertex.h"

class Vec3f
{
public:
	union
	{
		struct
		{
			float x, y, z;
		};
		float v[3];
	};
	Vec3f();
	Vec3f(Vec3f &other);
	Vec3f(float x, float y, float z);
	float& operator [](int);
};

class Vec2f
{
public:
	union
	{
		struct
		{
			float x, y;
		};
		float v[2];
	};
	Vec2f();
	Vec2f(float x, float y);
	Vec2f(Vec2f &other);
	float& operator [](int);
};

class ObjModel
{
public:
	ObjModel(string filename);
	~ObjModel(void);

	void draw(Entity &entity, float scale, float rotation);
private:
	class Vertex
	{
	public:
		int position;
		int normal;
		int texcoord;
	};

	class Face
	{
	public:
		list<Vertex> vertices;
	};
	
	class MaterialInfo
	{
	public:
		MaterialInfo();
		std::string name;
		bool hasTexture;
		ObjTexture *texture;
	};

	class ObjGroup
	{
	public:
		std::string name;
		int materialIndex;
		list<Face> faces;
		std::vector<S_Vertex> optimisedArray;
	};
	
	vector<Vec3f>	vertices;
	vector<Vec3f>	normals;
	vector<Vec2f>	texcoords;
	vector<ObjGroup*> groups;
	vector<MaterialInfo*> materials;

	void loadMaterialFile(std::string fileName, std::string dirName);
	void optimise(ObjGroup*);
};

