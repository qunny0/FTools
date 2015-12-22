// Open a window

#include "glut.h"
#include <stdio.h>
#include <iostream>

void RenderScene(void)
{
 	//clear the window use the current color
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();

// glFlush();

	printf("RenderScene\n");
}

void openglCheck()
{
	const GLubyte* uglName = glGetString(GL_VENDOR);
	if (uglName)
		std::cout << "openglʵ�ֳ��̵�����: " << uglName << std::endl;
	else
		std::cout << "uglName empty pointer" << std::endl;

	const GLubyte* uglRenderer = glGetString(GL_RENDERER);
	if (uglName)
		std::cout << "��Ⱦ����ʶ����ͨ���Ǹ�Ӳ��ƽ̨ : " << uglRenderer << std::endl;
	else
		std::cout << "uglRender empty pointer" << std::endl;

	const GLubyte* uglVersion = glGetString(GL_VERSION);
	if (uglVersion)
		std::cout << "OpenGLʵ�ֵİ汾��" << uglVersion << std::endl;
	else
		std::cout << "version empty pointer" << std::endl;

	const GLubyte* uglGluVersion = gluGetString(GLU_VERSION);
	if (uglGluVersion)
		std::cout << "��ǰGLU���߿�汾 : " << uglGluVersion << std::endl;
	else
		std::cout << "uglGluVersion empty pointer" << std::endl;
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Open a window");

// 	openglCheck();

	glutDisplayFunc(RenderScene);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
 	glutMainLoop();

	return 0;
}