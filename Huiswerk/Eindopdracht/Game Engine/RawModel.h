#pragma once
class RawModel
{
public:
	int getVaoID();
	int getVertexCount();
	RawModel(int, int);
	~RawModel();
private:
	int vaoID;
	int vertexCount;
};

