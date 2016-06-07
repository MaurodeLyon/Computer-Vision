#include <Windows.h>
#include <gl/glut.h>
#include <gl/GL.h>
#include <gl/glu.h>
#include <math.h>
#include "ObjModel.h"
#include "Node.h"


float rotation = 0;
//vector<pair<int, ObjModel*> > models;
vector<Node*> nodes;
int currentModel = 0;

void display(void)
{
	glClearColor(0.6f, 0.6f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 500, 0, 0, 0, 0, 1, 0);
	glRotatef(rotation, 0, 1, 0);
	nodes[currentModel]->draw();
	//models[currentModel].second->draw();

	glutSwapBuffers();
}

void reshape(GLint width, GLint height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, width / (float)height, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

void InitGraphics(void)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	nodes.push_back(new Node(new ObjModel("models/car/honda_jazz.obj"), 0, 0, 0, 0, 0, 0, 1, 1, 1));
	nodes[0]->addNode(new Node(new ObjModel("models/bloemetje/PrimRoseP.obj"), 0, 0, 0, 100, -100, 0, 100, 100, 100));
	nodes[0]->addNode(new Node(new ObjModel("models/cube/cube-textures.obj"), 0, 0, 0, -100, -100, 0, 100, 100, 100));
	nodes[0]->addNode(new Node(new ObjModel("models/ship/shipA_OBJ.obj"), 0, 0, 0, 150, -200, 0, 1, 1, 1));
	nodes[0]->addNode(new Node(new ObjModel("models/knight/low.obj"), 0, 0, 0, -150, -200, 0, 10, 10, 10));
	//models.push_back(pair<int, ObjModel*>(75, new ObjModel("models/car/honda_jazz.obj")));
	//models.push_back(pair<int, ObjModel*>(1, new ObjModel("models/bloemetje/PrimRoseP.obj")));
	//models.push_back(pair<int, ObjModel*>(1, new ObjModel("models/cube/cube-textures.obj")));
	//models.push_back(pair<int, ObjModel*>(35, new ObjModel("models/ship/shipA_OBJ.obj")));
	//models.push_back(pair<int, ObjModel*>(5, new ObjModel("models/knight/low.obj")));
}

void MouseButton(int button, int state, int x, int y)
{

}

void MouseMotion(int x, int y)
{

}

void IdleFunc(void)
{
	rotation += 0.25f;
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:             // ESCAPE key
		exit(0);
		break;
	case '[':
		//currentModel = (currentModel + models.size() - 1) % models.size();
		currentModel = (currentModel + nodes.size() - 1) % nodes.size();
		break;
	case ']':
		//currentModel = (currentModel + 1) % models.size();
		currentModel = (currentModel + 1) % nodes.size();
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(1024, 768);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("GLUT example");
	// Initialize OpenGL graphics state
	InitGraphics();
	// Register callbacks:
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	glutIdleFunc(IdleFunc);
	// Turn the flow of control over to GLUT
	glutMainLoop();
	return 0;
}