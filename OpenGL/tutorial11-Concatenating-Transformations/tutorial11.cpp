#include "glew.h"
#include "glut.h"
#include "math_3d.h"
#include "opengl_util.h"
#include "ogldev_pipeline.h"
#include <stdio.h>
#include <iostream>
using std::string;

/************************************************************************/
/*	Mn*Mn-1* ... *Mo*V = (Mn * Mn-1 * ... *Mo)*V
	N = Mn * Mn-1 * ... *Mo
	This means that we can calculate N once and then send it to the shader as a uniform variable where it will be multiplied in each vertex.

	In 3D graphics you usually want to scale the object first, then rotate it, then translate it, then apply camear transformation
	and finally project it to 2D.

	const Matrix4f* Pipeline::GetTrans()
	{
		Matrix4f ScaleTrans, RotateTrans, TranslationTrans;
		InitScaleTransform(ScaleTrans);
		InitRotateTransform(RotateTrans);
		InitTranslationTransform(TranslationTrans);
		m_transformation = Translations * RotateTrans * ScaleTrans;
		return &m_transformation;
	}
*/
/************************************************************************/

const char* pVSShader = "shader.vs";
const char* pFSShader = "shader.fs";

GLuint VBO;
GLuint IBO;

GLint gWorldLocation;

static void RenderSceneCB()
{
	glClear(GL_COLOR_BUFFER_BIT);

	static GLfloat scale = 0.0f;
	scale += 0.01f;

	Pipeline p;
	p.Scale(sinf(scale*0.1f), sinf(scale*0.1f), sinf(scale*0.1f));
	p.WorldPos(sinf(scale), 0.0f, 0.0f);
	p.Rotate(sinf(scale)*90.0f, sinf(scale)*90.0f, sinf(90.0f));
	glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, (const GLfloat*)&(p.GetWorldTrans().m[0]));

	glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}

static void addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType)
{
	GLuint shaderObj = glCreateShader(shaderType);
	if (shaderObj == 0)
	{
		fprintf(stderr, "Error creating shader type: %d\n", shaderType);
		exit(1);
	}

	const GLchar* p[1] = {};
	p[0] = pShaderText;
	GLint lengthes[1] = {};
	lengthes[0] = strlen(pShaderText);

	glShaderSource(shaderObj, 1, p, lengthes);
	glCompileShader(shaderObj);

	GLint res;
	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &res);
	if (res == 0)
	{
		GLchar errorInfo[1024] = {};
		glGetShaderInfoLog(shaderObj, 1024, nullptr, errorInfo);
		fprintf(stderr, "Error compiling shader type: %d , error : '%s'\n", shaderType, errorInfo);
		exit(1);
	}
	glAttachShader(shaderProgram, shaderObj);
}

static void compileShader()
{
	GLuint shaderProgram = glCreateProgram();
	if (shaderProgram == 0)
	{
		fprintf(stderr, "Error creating program\n");
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
		fprintf(stderr, "Error linking shader program: %s\n", errorInfo);
		exit(1);
	}

	glValidateProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &res);
	if (res == 0)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(errorInfo), nullptr, errorInfo);
		fprintf(stderr, "Error validating shader program: %s\n", errorInfo);
		exit(1);
	}

	glUseProgram(shaderProgram);

	gWorldLocation = glGetUniformLocation(shaderProgram, "gWorld");
	if (gWorldLocation == 0xFFFFFFFF)
	{
		exit(1);
	}
}

static void createVertexBuffer()
{
	Vector3f vertices[4] = {};
	vertices[0] = Vector3f(-0.5f, -0.5f, 0.5f);
	vertices[1] = Vector3f(-0.5f, -0.5f, -0.5f);
	vertices[2] = Vector3f(0.5f, -0.5f, 0.0f);
	vertices[3] = Vector3f(0.0f, 0.5f, 0.0f);

	glGenBuffers(1, &VBO);
// 	glBindBuffer(GL_VERTEX_ARRAY, VBO);
// 	glBufferData(GL_VERTEX_ARRAY, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

static void createIndexBuffer()
{
	GLuint indices[] = {
		0, 1, 2,
		0, 1, 3,
		1, 2, 3,
		2, 0, 3,
	};

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

static void initState(int* argc, char** argv, const char* title)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(200, 200);
	glutCreateWindow(title);

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: %s \n", glewGetErrorString(res));
		exit(1);
	}
	printf("GL Version: %s\n", glGetString(GL_VERSION));

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

static void InitializeGlutCallback()
{
	glutDisplayFunc(RenderSceneCB);
	glutIdleFunc(RenderSceneCB);
}

int main(int argc, char* argv)
{
	initState(&argc, &argv, "Concatenating Transformation");

	InitializeGlutCallback();

	createVertexBuffer();
	createIndexBuffer();

	compileShader();

	glutMainLoop();

	return 0;
}