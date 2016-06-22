#pragma once
#include <string>
#include <gl/glut.h>
using namespace std;
class ObjTexture
{
private:
	GLuint texture;

public:
	ObjTexture(const string &fileName);
	~ObjTexture(){};
	void bind();
	int width,height;

};

