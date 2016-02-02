// Open a window

/************************************************************************/
/*	如果使用DOUBLE_BUFFER。调用glutSwapBuffers时，刷新渲染命令
	如果使用SINGLE_BUFFER。需要调用glFlush()手动刷新渲染命令
*/
/************************************************************************/

#include "glut.h"
#include <stdio.h>
#include <iostream>

void RenderScene(void)
{
 	//clear the window use the current color
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderScene);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Open a window");
		
	InitializeGlutCallbacks();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

 	glutMainLoop();

	return 0;
}