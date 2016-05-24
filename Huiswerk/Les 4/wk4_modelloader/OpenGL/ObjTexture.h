#pragma once
#include <string>
#include <GL/freeglut.h>

class ObjTexture
{
private:
	GLuint tex;

public:
	ObjTexture(const std::string &fileName);
	~ObjTexture();
	void bind();
	int width, height;

};
