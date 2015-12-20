// Open a window

#include "glut.h"
#include <stdio.h>

void RenderScene(void)
{
 	//clear the window use the current color
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();

// glFlush();

	printf("RenderScene\n");
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Open a window");

	glutDisplayFunc(RenderScene);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
 	glutMainLoop();

	return 0;
}