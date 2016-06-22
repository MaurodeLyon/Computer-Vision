#include "stdafx.h"

UserInterfaceComponent::UserInterfaceComponent()
{
	maxHealth = 1;
	maxEnemyHealth = 1;
	health = 1;
	enemyHealth = 1;
	energy = 1;
	maxEnergy = 1;
	unit = 0;
	spell = 0;
	//undead();
	//wizards();
	////units
	loadTextures("zombie.png", true);
	loadTextures("skeleton.png", true);
	loadTextures("abomenation.png", true);
	//spells
	loadTextures("boulder.png", false);
	loadTextures("Plague.png", false);
}

void UserInterfaceComponent::undeadTextures()
{
	unitPictures.clear();
	spellPictures.clear();
	//units
	loadTextures("zombie.png", true);
	loadTextures("skeleton.png", true);
	loadTextures("abomenation.png", true);
	//spells
	loadTextures("resurrection.png", false);
	loadTextures("attack-buf.png", false);
}

void UserInterfaceComponent::humanTextures()
{
	unitPictures.clear();
	spellPictures.clear();
	//units
	loadTextures("warrior.png", true);
	loadTextures("archer.png", true);
	loadTextures("mercenary.png", true);
	//spells
	loadTextures("cavalry.png", false);
	loadTextures("rain-of-arrows.png", false);
}

void UserInterfaceComponent::wizardsTextures()
{
	unitPictures.clear();
	spellPictures.clear();
	//units
	loadTextures("apprentice.png", true);
	loadTextures("arcane-warrior.png", true);
	loadTextures("archmage.png", true);
	//spells
	loadTextures("fireball.png", false);
	loadTextures("frost-nova.png", false);
}

void UserInterfaceComponent::render(Entity& entity)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 1000, 1000, 0, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);


	//Health bar
	glBegin(GL_QUADS);
	glColor4f(0, 0, 0, 1.0);
	glVertex2f(250, 980);
	glVertex2f(250, 965);
	glVertex2f(750, 965);
	glVertex2f(750, 980);
	glEnd();
	
	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0);
	glVertex2f(250, 980);
	glVertex2f(250, 965);
	if (health < 0)
	{
		glVertex2f(250 + (0 / (maxHealth / 500)), 965);
		glVertex2f(250 + (0 / (maxHealth / 500)), 980);
	}
	else
	{
		glVertex2f(250 + (health / (maxHealth / 500)), 965);
		glVertex2f(250 + (health / (maxHealth / 500)), 980);
	}
	
	glEnd();

	//Enemy Health bar
	glBegin(GL_QUADS);
	glColor4f(0, 0, 0, 1.0);
	glVertex2f(375, 250);
	glVertex2f(375, 235);
	glVertex2f(625, 235);
	glVertex2f(625, 250);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0);
	glVertex2f(375, 250);
	glVertex2f(375, 235);
	if (enemyHealth < 0)
	{
		glVertex2f(375 + (0 / 2) / (maxEnemyHealth / 500), 235);
		glVertex2f(375 + (0 / 2) / (maxEnemyHealth / 500), 250);
	}
	else
	{
		glVertex2f(375 + (enemyHealth / 2) / (maxEnemyHealth / 500), 235);
		glVertex2f(375 + (enemyHealth / 2) / (maxEnemyHealth / 500), 250);
	}
	
	glEnd();

	//Energy bar
	glBegin(GL_QUADS);
	glColor4f(0, 0, 0, 1.0);
	glVertex2f(250, 950);
	glVertex2f(250, 935);
	glVertex2f(750, 935);
	glVertex2f(750, 950);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(0, 0, 1.0f, 1.0);
	glVertex2f(250, 950);
	glVertex2f(250, 935);
	glVertex2f(250 + (energy / (maxEnergy / 500)), 935);
	glVertex2f(250 + (energy / (maxEnergy / 500)), 950);
	glEnd();

	glColor3f(1, 1, 1);
	glutBitmapString("Energy: " + std::to_string(energy), 455, 925);

	//UnitSelection
	glColor3f(0, 0, 0);
	int s = unitPictures[unit].first.length();
	glutBitmapString(unitPictures[unit].first.substr(0, s - 4), 50, 790);

	glColor3f(0, 0, 0);
	int k = spellPictures[spell].first.length();
	glutBitmapString(spellPictures[spell].first.substr(0, k - 4), 900, 790);

	//unitPictures[unit].first.size
	//unitPictures[unit].first.substr(0, unitPictures[unit].first.size);

	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, unitPictures[unit].second);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex2f(0, 800);
	glTexCoord2f(1, 1); glVertex2f(150, 800);
	glTexCoord2f(1, 0); glVertex2f(150, 1000);
	glTexCoord2f(0, 0); glVertex2f(0, 1000);
	glEnd();

	//Spels
	glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, spellPictures[spell].second);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex2f(850, 1000);
	glTexCoord2f(0, 1); glVertex2f(850, 800);
	glTexCoord2f(1, 1); glVertex2f(1000, 800);
	glTexCoord2f(1, 0); glVertex2f(1000, 1000);
	glEnd();

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void UserInterfaceComponent::glutBitmapString(std::string str, int x, int y)
{
	glRasterPos2f(x, y);
	for (int i = 0; i < str.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	}
}

void UserInterfaceComponent::nextUnit()
{
	if (unit < unitPictures.size() - 1)
	{
		unit++;
	}
	else { unit = 0; };
}

void UserInterfaceComponent::nextSpell()
{
	if (spell < 1)
	{
		spell++;
	}
	else { spell = 0; };
}

void UserInterfaceComponent::loadTextures(string pictureName, bool unitPicture)
{
	int width1, height1, bpp1;
	string pictureName1 = "res/images/" + pictureName;
	unsigned char* imgData2 = stbi_load(pictureName1.c_str(), &width1, &height1, &bpp1, 4);
	glGenTextures(1, &unitSelect);
	glBindTexture(GL_TEXTURE_2D, unitSelect);

	glTexImage2D(GL_TEXTURE_2D,
		0,					//level
		GL_RGBA,			//internal format
		width1,				//width
		height1,			//height
		0,					//border
		GL_RGBA,			//data format
		GL_UNSIGNED_BYTE,	//data type
		imgData2);			//data
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	stbi_image_free(imgData2);
	if (unitPicture) { unitPictures.push_back(pair<string, GLuint>(pictureName, unitSelect)); }
	else { spellPictures.push_back(pair<string, GLuint>(pictureName, unitSelect)); }

}
