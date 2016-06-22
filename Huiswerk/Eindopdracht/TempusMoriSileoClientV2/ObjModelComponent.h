#pragma once
#include "objModel.h"
class ObjModelComponent : public Component
{
public:
	ObjModelComponent(ObjModel* objModel) : objModel(objModel), scale(1), rotation(0) {}
	ObjModelComponent(ObjModel* objModel, float rotation, float scale) : objModel(objModel), scale(scale), rotation(rotation) {}
	~ObjModelComponent() {};

	virtual void render(Entity& entity);
	void setRotation(float rotation) { this->rotation = rotation; }
	void setScale(float scale) { this->scale = scale; }
private:
	ObjModel* objModel;
	float scale;
	float rotation;
};

