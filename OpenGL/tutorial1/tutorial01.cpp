// Open a window

/************************************************************************/
/*	���ʹ��DOUBLE_BUFFER������glutSwapBuffersʱ��ˢ����Ⱦ����
	���ʹ��SINGLE_BUFFER����Ҫ����glFlush()�ֶ�ˢ����Ⱦ����
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