// Hello dot

#include "glew.h"
#include "math_3d.h"
#include "glut.h"
#include <stdio.h>

Vector3f Vertices[1];
GLuint VBO;

void RenderScene(void)
{
	//clear the window use the current color
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_POINTS, 0, 1);
	glDisableVertexAttribArray(0);

	
	// glFlush();
	printf("RenderScene\n"); 
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Hello dot");

	glutDisplayFunc(RenderScene);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glutMainLoop();

	// glew
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error : '%s'\n", glewGetErrorString(res));
	}

	return 0;
}