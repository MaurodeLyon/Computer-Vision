#pragma once
#include <vector>
#include "ObjModel.h"

class Node
{
public:
	Node(ObjModel* model, float rotationX, float rotationY, float rotationZ, float x, float y, float z, float sx, float sy, float sz)
		:model(model), rotationX(rotationX), rotationY(rotationY), rotationZ(rotationZ), x(x), y(y), z(z), sx(sx), sy(sy), sz(sz) {};
	~Node() {};

	void addNode(Node* node)
	{
		nodes_.push_back(node);
	};

	void draw()
	{
		glPushMatrix();
		glRotatef(rotationX, 1, 0, 0);
		glRotatef(rotationY, 0, 1, 0);
		glRotatef(rotationZ, 0, 0, 1);
		glTranslatef(x, y, z);
		glScalef(sx, sy, sz);
		model->draw();
		for each (Node * node in nodes_)
		{
			node->draw();
		}
		glPopMatrix();
	};

private:
	float rotationX, rotationY, rotationZ;
	float x, y, z;
	float sx, sy, sz;
	ObjModel* model;
	std::vector<Node*> nodes_;
};