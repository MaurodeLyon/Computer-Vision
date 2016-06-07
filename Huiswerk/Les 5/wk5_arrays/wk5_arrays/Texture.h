#pragma once
#include "freeglut/include/GL/freeglut.h"
#include <string>

class Texture
{
public:
	Texture(const char * fileName);
	~Texture() {};
	void bind()
	{
		glBindTexture(GL_TEXTURE_2D, texture);
	};
private:
	GLuint texture;
	int width, height;
};

