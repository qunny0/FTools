#include "glew.h"
#include "glut.h"
#include "ogldev_math_3d.h"
#include "ogldev_util.h"
#include "ogldev_pipeline.h"

#include <stdio.h>

/************************************************************************/
/*	We have finally reached the item that represents 3D graphics best - the projection from the 3D world on a 2D plane while maintaining 
	the appearance of depth.

	The perspective projection transformation will require us to supply 4 parameters:
	1.The aspect ratio - the ratio between the width and the height of the rectangular area which will be the target of projection.
	2.The vertical field of view: the vertical angle of the camera through which we are looking at the world.
	3.The location of the near Z plane. This allows us to clip objects that are too close to the camera.
	4.The location of the far Z plane. This allows us to clip objects that are too distance from the camera.



*/
/************************************************************************/

GLuint VBO;
GLuint IBO;

const char* pVSShader = "shader.vs";
const char* pFSShader = "shader.fs";

GLuint gWorldLocation;

PersProjInfo gPersProjInfo;

static void RenderSceneCB()
{
	glClear(GL_COLOR_BUFFER_BIT);

	static GLfloat scale = 0.0f;
	scale += 0.1f;

	Pipeline p;
	p.Rotate(0.0f, scale, 0.0f);
	p.WorldPos(0.0f, 0.0f, 5.0f);
	p.SetPerspectiveProj(gPersProjInfo);

	glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, (const GLfloat*)p.GetWPTrans());

	glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}

static void createVertexBuffer()
{
	Vector3f vertices[4] = {};
	vertices[0] = Vector3f(-0.75f, -0.75f, 0.75f);
	vertices[1] = Vector3f(-0.75f, -0.75f, -0.75f);
	vertices[2] = Vector3f(0.75f, -0.75f, 0.0f);
	vertices[3] = Vector3f(0.0f, 0.75f, 0.0f);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

static void createIndexBuffer()
{
	GLuint indices[] = {
		0, 1, 2,
		0, 1, 3,
		0, 2, 3,
		1, 2, 3,
	};

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

static void addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType)
{
	GLuint shaderObj = glCreateShader(shaderType);
	if (shaderObj == 0)
	{
		fprintf(stderr, "Error: creating shader type : %d\n", shaderType);
		exit(1);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint lengthes[1];
	lengthes[0] = strlen(pShaderText);

	glShaderSource(shaderObj, 1, p, lengthes);
	glCompileShader(shaderObj);

	GLint res;
	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &res);
	if (res == 0)
	{
		GLchar errorInfo[1024] = {};
		glGetShaderInfoLog(shaderObj, sizeof(errorInfo), nullptr, errorInfo);
		fprintf(stderr, "Error: Compiling shader type: %d, error: %s\n", shaderType, errorInfo);
		exit(1);
	}

	glAttachShader(shaderProgram, shaderObj);
}

static void compileShader()
{
	GLuint shaderProgram = glCreateProgram();
	if (shaderProgram == 0)
	{
		fprintf(stderr, "Error: creating program\n");
		exit(1);
	}

	string vs, fs;
	if (!ReadFile(pVSShader, vs))
	{
		exit(1);
	}
	if (!ReadFile(pFSShader, fs))
	{
		exit(1);
	}

	addShader(shaderProgram, vs.c_str(), GL_VERTEX_SHADER);
	addShader(shaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint res = 0;
	GLchar errorInfo[1024] = {};

	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &res);
	if (res == 0)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(errorInfo), nullptr, errorInfo);
		fprintf(stderr, "Error: Linking program: '%s'\n", errorInfo);
		exit(1);
	}

	glValidateProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &res);
	if (res == 0)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(errorInfo), nullptr, errorInfo);
		fprintf(stderr, "Error: Validating program: '%s'\n", errorInfo);
		exit(1);
	}

	glUseProgram(shaderProgram);

	gWorldLocation = glGetUniformLocation(shaderProgram, "gWorld");
	if (gWorldLocation == 0xFFFFFFFF)
	{
		exit(1);
	}
}

static void changeSize(int w, int h)
{
	gPersProjInfo.FOV = 30.0f;

	gPersProjInfo.Height = w;
	gPersProjInfo.Width = h;

	gPersProjInfo.zNear = 1.0f;
	gPersProjInfo.zFar = 100.0f;
}

static void InitializeCallback()
{
	glutDisplayFunc(RenderSceneCB);
	glutIdleFunc(RenderSceneCB);
	glutReshapeFunc(changeSize);
}

int main(int argc, char* argv)
{
	glutInit(&argc, &argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Perspective Projection");

	GLint res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: glewInit\n");
		exit(1);
	}


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	InitializeCallback();

	createVertexBuffer();
	createIndexBuffer();

	compileShader();

	glutMainLoop();

	return 0;
}