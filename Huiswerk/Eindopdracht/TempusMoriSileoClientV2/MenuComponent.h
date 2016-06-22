#pragma once
#include "Engine.h"

class MenuComponent : public Component
{
public:
	MenuComponent(Engine *engine1);
	~MenuComponent() {};
	virtual void update(Entity& entity);
	virtual void render(Entity& entity);
	void drawBitmapText(std::string str, float x, float y);
	void draw();
	void loadTextures();
	void updateMouse(int, int);
	void enterOption();
private:
	int mouseX, mouseY;
	Engine *engine1;
	double menu1color, menu2color, menu3color;
	bool loadTexture, inMenu, factionSelected;
	enum Faction { Undead, Human, Mage } faction;
};



