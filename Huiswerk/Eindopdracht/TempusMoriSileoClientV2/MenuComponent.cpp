#include "stdafx.h"
#include "MenuComponent.h"

GLuint undeadTexture;
GLuint mageTexture;
GLuint humanTexture;
extern int mousePosX;
extern int mousePosY;
extern int keyPressed;
extern bool inMenu;
extern std::vector<Entity*> entities;
extern float leapRightHand[4];
extern Client c;

MenuComponent::MenuComponent(Engine *engine1)
{
	this->engine1 = engine1;
	mouseX = 0;
	mouseY = 0;
	menu1color = 0;
	menu2color = 0;
	menu3color = 0;
	inMenu = true;
	loadTexture = true;
	factionSelected = false;
}

void MenuComponent::update(Entity& entity)
{
	if (inMenu)
	{
		updateMouse(mousePosX, mousePosY);
		if (keyPressed == 32 || leapRightHand[3] > 0.75)
		{
			enterOption();
			inMenu = false;
		}
	}
	if (factionSelected)
	{
		for each (auto entity in entities)
		{
			for each(auto component in entity->getComponents())
			{
				if (dynamic_cast<const PlayerComponent*>(component) != nullptr)
				{
					PlayerComponent* interface = (PlayerComponent*)component;
					if (interface->getPlayer())
					{
						if (faction == 0) { interface->setUndead(); }
						else if (faction == 1) { interface->setHuman(); }
						else if (faction == 2) { interface->setMage(); }
					}
				}
			}
		}
	}
}

void MenuComponent::render(Entity& entity)
{
	if (inMenu)
	{
		cout << leapRightHand[0] << "	" << leapRightHand[3] << endl;
		//cout << mousePosX << "	" << mousePosY << endl;
		draw();
	}
}

void MenuComponent::drawBitmapText(const std::string s, float x, float y)
{
	glRasterPos2f(x, y);

	for (auto &c : s) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
	}
}

void MenuComponent::updateMouse(int x, int y)
{
	mouseX = x;
	mouseY = y;
	if (leapRightHand[0] < 150)//(mouseX <= (glutGet(GLUT_WINDOW_WIDTH) / 3)) || leapRightHand[0] < 150)
	{
		menu1color = 0.5f;
		menu2color = 1;
		menu3color = 0;
	}
	else if (leapRightHand[0] > 150 && leapRightHand[0] < 300)//(mouseX <= ((glutGet(GLUT_WINDOW_WIDTH) / 3) * 2) && mouseX >= ((glutGet(GLUT_WINDOW_WIDTH) / 3))) || (leapRightHand[0] > 150 && leapRightHand[0] < 300))
	{
		menu1color = 0;
		menu2color = 0.5f;
		menu3color = 0;
	}
	else if (leapRightHand[0] > 300)//(mouseX >= ((glutGet(GLUT_WINDOW_WIDTH) / 3) * 2)) || (leapRightHand[0] > 300))
	{
		menu1color = 0;
		menu2color = 1;
		menu3color = 0.5f;
	}
}

void MenuComponent::enterOption()
{
	if (leapRightHand[0] < 150)//(mouseX <= (glutGet(GLUT_WINDOW_WIDTH) / 3)) || leapRightHand[0] < 150)
	{
		cout << "Selected Undead // FactionSelectionMenu.cpp" << endl;
		menu1color = 0.7f;
		faction = Undead;
		factionSelected = true;
		engine1->init_world(0);
		engine1->init_Interface();
		LoginPacket packet = LoginPacket("undead");
		packet.writeData(c);
		//DisplayInterface display = DisplayTest();				//UNDEAD WORLD
	}
	else if (leapRightHand[0] > 150 && leapRightHand[0] < 300)//(mouseX <= ((glutGet(GLUT_WINDOW_WIDTH) / 3) * 2) && mouseX >= ((glutGet(GLUT_WINDOW_WIDTH) / 3))) || (leapRightHand[0] > 150 && leapRightHand[0] < 300))
	{
		cout << "Selected Human // FactionSelectionMenu.cpp" << endl;
		menu2color = 0.7f;
		faction = Human;
		factionSelected = true;
		engine1->init_world(1);
		engine1->init_Interface();
		LoginPacket packet = LoginPacket("human");
		packet.writeData(c);
		//DisplayInterface display = DisplayTest();				//Human WORLD
	}
	else if (leapRightHand[0] > 300)//(mouseX >= ((glutGet(GLUT_WINDOW_WIDTH) / 3) * 2)) || (leapRightHand[0] > 300))
	{
		cout << "Selected Mage // FactionSelectionMenu.cpp" << endl;
		menu3color = 0.8f;
		faction = Mage;
		factionSelected = true;
		engine1->init_world(2);
		engine1->init_Interface();
		LoginPacket packet = LoginPacket("mage");
		packet.writeData(c);
		//DisplayInterface display = DisplayTest();				//Mage WORLD
	}
}

void MenuComponent::loadTextures()
{
	int width1, height1, bpp1;
	unsigned char* imgData1 = stbi_load("res/images/undead.jpg", &width1, &height1, &bpp1, 4);
	glGenTextures(1, &undeadTexture);
	glBindTexture(GL_TEXTURE_2D, undeadTexture);

	glTexImage2D(GL_TEXTURE_2D,
		0,				//level
		GL_RGBA,		//internal format
		width1,			//width
		height1,		//height
		0,				//border
		GL_RGBA,		//data format
		GL_UNSIGNED_BYTE,	//data type
		imgData1);		//data
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	stbi_image_free(imgData1);

	unsigned char* imgData2 = stbi_load("res/images/knight.jpg", &width1, &height1, &bpp1, 4);
	glGenTextures(1, &humanTexture);
	glBindTexture(GL_TEXTURE_2D, humanTexture);

	glTexImage2D(GL_TEXTURE_2D,
		0,				//level
		GL_RGBA,		//internal format
		width1,			//width
		height1,		//height
		0,				//border
		GL_RGBA,		//data format
		GL_UNSIGNED_BYTE,	//data type
		imgData2);		//data
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	stbi_image_free(imgData2);

	unsigned char* imgData3 = stbi_load("res/images/mage.jpg", &width1, &height1, &bpp1, 4);
	glGenTextures(1, &mageTexture);
	glBindTexture(GL_TEXTURE_2D, mageTexture);

	glTexImage2D(GL_TEXTURE_2D,
		0,				//level
		GL_RGBA,		//internal format
		width1,			//width
		height1,		//height
		0,				//border
		GL_RGBA,		//data format
		GL_UNSIGNED_BYTE,	//data type
		imgData3);		//data
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	stbi_image_free(imgData3);
}

void MenuComponent::draw()
{
	updateMouse(mousePosX, mousePosY);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1000, 1000, 0, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();



	//glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);

	if (loadTexture)
	{
		loadTextures();
		loadTexture = false;
	}
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, mageTexture);
	glBegin(GL_QUADS);
	glColor3f(1, menu3color, 1);

	glTexCoord2f(0, 0); glVertex2f((1000 / 3 * 2), 1000);//glVertex3f(7, 7, 0);
	glTexCoord2f(0, 1); glVertex2f((1000 / 3 * 2), 0);//glVertex3f(7 / 3.0f, 7, 0);
	glTexCoord2f(1, 1); glVertex2f(1000, 0);//glVertex3f(7 / 3.0f, -7, 0);
	glTexCoord2f(1, 0); glVertex2f(1000, 1000);//glVertex3f(7, -7, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glColor3f(1, 1, 1);
	drawBitmapText("Mage", 7 / 3 + 7 / 3 / 2, 0);

	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, undeadTexture);
	glBegin(GL_QUADS);
	glColor3f(0, 1, menu1color);

	glTexCoord2f(0, 0); glVertex2f((1000 / 3), 1000);
	glTexCoord2f(0, 1); glVertex2f((1000 / 3), 0);
	glTexCoord2f(1, 1); glVertex2f(0, 0);
	glTexCoord2f(1, 0); glVertex2f(0, 1000);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glColor3f(1, 1, 1);
	drawBitmapText("Undead", -7 / 3 - 7 / 3 / 2 - 1, 0);

	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, humanTexture);
	glBegin(GL_QUADS);
	glColor3f(1, 1, menu2color);
	glTexCoord2f(0, 1); glVertex2f((1000 / 3) * 2, 0);
	glTexCoord2f(1, 1); glVertex2f((1000 / 3), 0);
	glTexCoord2f(1, 0); glVertex2f((1000 / 3), 1000);
	glTexCoord2f(0, 0); glVertex2f((1000 / 3) * 2, 1000);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glColor3f(1, 1, 1);
	drawBitmapText("Human", -0.5f, 0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}