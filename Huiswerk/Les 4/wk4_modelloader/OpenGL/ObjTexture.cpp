#include "ObjTexture.h"

ObjTexture::ObjTexture(const std::string &fileName)
{
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	stbi_set_flip_vertically_on_load(true);

	int TEXTwidth, TEXTheight, TEXTbpp;
	char* TEXTData = (char*)stbi_load(fileName.c_str(), &TEXTwidth, &TEXTheight, &TEXTbpp, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEXTwidth, TEXTheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)TEXTData);
	stbi_image_free(TEXTData);

	width = TEXTwidth;
	height = TEXTheight;
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void ObjTexture::bind()
{
	glBindTexture(GL_TEXTURE_2D, tex);
}

ObjTexture::~ObjTexture()
{
}
