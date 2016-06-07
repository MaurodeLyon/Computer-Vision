#pragma once

#include <string>
#include <vector>
#include <list>

#include <windows.h>
#include <gl/GL.h>

using namespace std;

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

	class Texture
	{
	public:
		Texture(string &fileName);
		~Texture() {};
		void bind()
		{
			glBindTexture(GL_TEXTURE_2D, texture);
		};
	private:
		GLuint texture;
		int width, height;
	};

	class MaterialInfo
	{
	public:
		MaterialInfo();
		std::string name;
		bool hasTexture;
		Texture * texture;
	};

	class S_Vertex
	{
	public:
		float x;				// Kan ook een Vec3 zijn 	
		float y;
		float z;
		float normalx;			// Kan ook een Vec3 zijn
		float normaly;
		float normalz;
		float texcoordx;		// kan ook een Vec2 zijn
		float texcoordy;
		S_Vertex(float xC, float yC, float zC, float normalxC, float normalyC, float normalzC, float texcoordxC, float texcoordyC)
		{
			x = xC;						// Kan ook een Vec3 zijn 	
			y = yC;
			z = zC;
			normalx = normalxC;			// Kan ook een Vec3 zijn
			normaly = normalyC;
			normalz = normalzC;
			texcoordx = texcoordxC;		// kan ook een Vec2 zijn
			texcoordy = texcoordyC;

		}
		~S_Vertex() {};
	};

	class ObjGroup
	{
	public:
		std::string name;
		int materialIndex;
		list<Face> faces;
		std::vector<S_Vertex> optimisedArray;
	};


	std::vector<Vec3f>	vertices;
	std::vector<Vec3f>	normals;
	std::vector<Vec2f>	texcoords;
	std::vector<ObjGroup*> groups;
	std::vector<MaterialInfo*> materials;

	void loadMaterialFile(std::string fileName, std::string dirName);
	void loadOpt();
public:
	ObjModel(std::string filename);
	~ObjModel(void);

	void draw();
};

