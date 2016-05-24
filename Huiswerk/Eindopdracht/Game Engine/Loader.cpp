#include "stdafx.h"
#include "Loader.h"


Loader::Loader()
{

}

Loader::~Loader()
{
}

RawModel Loader::loadToVao(float positions[])
{
	int vaoID = createVAO();
	vaos.push_back(&vaoID);
	storeDataInAttributeList(0, positions);
	return RawModel(vaoID, (sizeof(positions) / sizeof(*positions)) / 3);
}

int Loader::createVAO()
{
	int index = vaos.size();
	return index;
}

void Loader::storeDataInAttributeList(int attributeNumber, float data[])
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(attributeNumber, GL_FLOAT, 0, data);
	glDisableClientState(GL_VERTEX_ARRAY);
	/*GLuint vboId = glGenLists(1);
	glNewList(vboId, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	for (int vertex = 0; vertex < (sizeof(data) / sizeof(*data)); vertex += 3)
	{
		glVertex3f(data[vertex],data[vertex+1],data[vertex+2]);
	}
	glEnd();
	glEndList();*/
}