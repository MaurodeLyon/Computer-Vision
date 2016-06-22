#include "stdafx.h"
#include "ShipComponent.h"

extern int x;
extern int y;
extern int z;
extern std::vector<pair<string, ObjModel*>> objectLibrary;
extern std::vector<Entity*> entities;
extern std::vector<Entity*> entitiesToAdd;

void ShipComponent::update(Entity& entity)
{
	entity.x = x;
	entity.y = y;
	entity.z = z;
	if (health < 0)
	{
		entity.alive = false;
		for each (Entity *other_entity in entities)
			if (&entity != other_entity)
				for each(Component * userinterface in other_entity->getComponents())
					if (dynamic_cast<const UserInterfaceComponent*>(userinterface) != nullptr)
					{
						UserInterfaceComponent * user_interface = (UserInterfaceComponent*)userinterface;
						user_interface->DeathCount++;
					}
	}
}

void ShipComponent::render(Entity& entity)
{
	for (int i = 0; i < health; i++)
	{
		auto * model = objectLibrary[10].second;

		float orbx = (cos((360 - (360 / health * i)) * PI / 180.0) * 200);
		float orby = 0;
		float orbz = (sin((360 - (360 / health * i)) * PI / 180.0) * 200);

		glPushMatrix();
		glTranslatef(entity.x, entity.y, entity.z);
		glRotatef(rotation, 0, 1, 0);
		model->draw(orbx, orby, orbz, 0.20, 0);
		glPopMatrix();
		if (rotation > 360)
		{
			rotation = 0;
		}
		rotation++;
	}

}
