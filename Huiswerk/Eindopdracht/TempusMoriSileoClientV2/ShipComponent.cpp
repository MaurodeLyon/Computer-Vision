#include "stdafx.h"
#include "ShipComponent.h"

extern int x;
extern int y;
extern std::vector<pair<string, ObjModel*>> objectLibrary;

void ShipComponent::update(Entity& entity)
{
	entity.x = x;
	entity.y = y;
	if (health < 0) entity.alive = false;
}

void ShipComponent::render(Entity& entity)
{
	for (int i = 0; i < health; i++)
	{
		auto * model = objectLibrary[4].second;

		float orbx = (cos((360 - (360 / health * i)) * PI / 180.0) * 25);
		float orby = 0;
		float orbz = (sin((360 - (360 / health * i)) * PI / 180.0) * 25);

		glPushMatrix();
		glTranslatef(entity.x, entity.y, entity.z);
		glRotatef(rotation, 0, 1, 0);
		model->draw(orbx, orby, orbz, 0.5, 0);
		glPopMatrix();
		if (rotation > 360)
		{
			rotation = 0;
		}
		rotation++;
	}

}
