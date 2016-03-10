// Hello dot

/************************************************************************/
/* 
	http://ogldev.atspace.co.uk/www/tutorial02/tutorial02.html

	void glGenBuffers(GLsizei n, GLuint* buffers);
	void glBindBuffer(GLenum target, GLuint buffer);
	glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
	-----
	We allocate a GLuint in the global part of the program to store the handle of the vertex buffer object.
	You will see later that most (if not all) OpenGL objects are accessed via a variable of GLuint type.
	我们在程序的全局作用域分配一个无符号整型存储这个顶点数组的handle
	我会稍后会看到，几乎所有的OpenGL对象都是由一个无符号类型的数据保存其可操作性

	glEnableVertexAtribArray(0);
	-----
	In the shader tutorial you will see that vertex attributes used in the shader (position, normal, etc) have an index 
	mapped to them that enable you to create the binding between the data in the c/c++ program and the attribute name inside the shader.
	In addition you must also enable vertex attribute index.
	In this tutorial we are not yet using any shader but the vertex position we have loaded into the buffer is treated as vertex attribute
	index 0 in the fixed function pipeline (which becomes active when there is no shader bound). You must enable each vertex attribute or 
	else the data will not be accessible by the pipeline.

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	-----
	Here we bind our buffer again as we prepare for making the draw call. In this small program we only have one vertex buffer so making this
	call every frame is redundant but in more complex programs there are multiple buffers to store your various models and you must update
	the pipeline state with the buffer you intend to use.

	glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	-----
	This call tells the pipeline how to interpret the data inside the buffer. The first parameter specifies the index of the attribute.
	In our case we know that it is zero by default but when we start using shaders we will either need to explicitly set the index in the shader
	or query it. The second parameter is the number of components in the attribute(3 for X, Y and X). The third parameter is the data type of each
	component. The next parameter indicates whether we want our attribute to be normalized before it is used in the pipeline. It our case we want the 
	data to pass un-changed. The fifth parameter (called the 'stride') is the number of bytes between two instance of that attribute in the buffer. 
	When there is only one attribute (e.g. the buffer contains only vertex positions) and the data is tightly packed we pass the value zero.
	If we have an array of structures that contain a position and normal (each one is a vector of 3 floats) we will pass the size of the structure
	in bytes (6*4=24). The last parameter is useful in the case of the previous example. We need to specify the offset inside the structure where the 
	pipeline will find our attribute. In the case of the structure with the position and normal the offset of the position is zero while the offset
	of the normal is 12.
*/
/************************************************************************/
/************************************************************************/
/*	1. How to set the size of point.
	GLfloat sizes[2];
	GLfloat step;
	glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
	glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);
	glPointSize(float size);

	2. How to set the color of point.
	void glColor3f(0.0f, 1.0f, 0.0f);
*/
/************************************************************************/

#include "glew.h"
#include "math_3d.h"
#include "glut.h"
#include <stdio.h>

GLuint VBO;  // store the handle of the vertex buffer object

void RenderSceneCB(void)
{
	//clear the window use the current color
	glClear(GL_COLOR_BUFFER_BIT);
	
	glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_POINTS, 0, 1);
	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}

static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderSceneCB);
}

static void CreateVertexBuffer()
{
	Vector3f Vertices[1];
	Vertices[0] = Vector3f(0.0f, 0.0f, 0.0f);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);	
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Hello dot!");

	InitializeGlutCallbacks();

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error : '%s'\n", glewGetErrorString(res));
		return 1;
	}

	// set clear color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	CreateVertexBuffer();

	glutMainLoop();

	return 0;
}