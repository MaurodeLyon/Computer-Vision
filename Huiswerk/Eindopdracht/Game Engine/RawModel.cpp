#include "stdafx.h"
#include "RawModel.h"


int RawModel::getVaoID()
{
	return vaoID;
}

int RawModel::getVertexCount()
{
	return vertexCount;
}

RawModel::RawModel(int vaoID,int vertexCount)
{
	this->vaoID = vaoID;
	this->vertexCount = vertexCount;
}


RawModel::~RawModel()
{
}
