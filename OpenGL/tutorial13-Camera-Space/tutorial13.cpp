#include "glew.h"
#include "glut.h"
#include <stdio.h>
#include <string>
using namespace std;

static void renderSceneCB()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glutSwapBuffers();
}

static void changeSize(int w, int h)
{

}

static void initializeCallbck()
{
	glutDisplayFunc(renderSceneCB);
	glutReshapeFunc(changeSize);
}

int main(int argc, char* argv)
{
	glutInit(&argc, &argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Camera Space");

	initializeCallbck();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glutMainLoop();

	return 1;
}