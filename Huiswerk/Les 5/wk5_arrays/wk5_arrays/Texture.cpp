#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

Texture::Texture(const char *fileName)
{
	
	glGenTextures(1, &texture);
	stbi_set_flip_vertically_on_load(true);

	int textureWidth, textureHeight, textureBPP;
	char* textureData = (char*)stbi_load(fileName, &textureWidth, &textureHeight, &textureBPP, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)textureData);
	stbi_image_free(textureData);
	std::cout << texture << std::endl;
	width = textureWidth;
	height = textureHeight;
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
