#include <stdio.h>
#include "glew.h"
#include "glut.h"
#include "ogldev_pipeline.h"
#include "ogldev_camera.h"
#include "ogldev_util.h"
#include "ogldev_glut_backend.h"

#define WINDOW_WIDTH	1024
#define WINDOW_HEIGHT	768

GLuint VBO;
GLuint IBO;
GLuint gWVPLocation;

Camera* pGameCamera = NULL;
PersProjInfo gPersProjInfo;

const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";

static void RenderSceneCB()
{
	glClear(GL_COLOR_BUFFER_BIT);

	static float scale = 0.0f;
	scale += 0.1f;

	Pipeline p;
	p.Rotate(0.0f, scale, 0.0f);
	p.WorldPos(0.0f, 0.0f, 3.0f);
	p.SetCamera(*pGameCamera);
	p.SetPerspectiveProj(gPersProjInfo);

	glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, (const GLfloat*)p.GetWVPTrans());

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}

static void	CreateVertexBuffer()
{
	Vector3f vertices[4];
	vertices[0] = Vector3f(-1.0f, -1.0f, 0.5773f);
	vertices[1] = Vector3f(0.0f, -1.0f, -1.15475f);
	vertices[2] = Vector3f(1.0f, -1.0f, 0.5773f);
	vertices[3] = Vector3f(0.0f, 1.0f, 0.0f);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}
static void CreateIndexBuffer()
{
	GLuint indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

static void SpecailKeyboardCB(int key, int x, int y)
{
	OGLDEV_KEY ogldevKey = GLUTKeyToOGLDEVKey(key);
	pGameCamera->OnKeyboard(ogldevKey);
}

static void initializeGlutCallbacks()
{
	glutIdleFunc(RenderSceneCB);
	glutDisplayFunc(RenderSceneCB);

	glutSpecialFunc(SpecailKeyboardCB);
}

static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum shaderType)
{
	GLuint shaderObj = glCreateShader(shaderType);

	if (shaderObj == 0)
	{
		fprintf(stderr, "Error creating shader type %d\n", shaderType);
		exit(1);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint lengthes[1];
	lengthes[0] = strlen(pShaderText);

	glShaderSource(shaderObj, 1, p, lengthes);
	glCompileShader(shaderObj);

	GLint success;
	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar InfoLog[1024] = {};
		glGetShaderInfoLog(shaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", shaderType, InfoLog);
		exit(1);
	}

	glAttachShader(ShaderProgram, shaderObj);
}

static void CompileShader()
{
	GLuint ShaderProgram = glCreateProgram();
	if (ShaderProgram == 0)
	{
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	string vs, fs;
	if (!ReadFile(pVSFileName, vs))
	{
		exit(1);
	}
	if (!ReadFile(pFSFileName, fs))
	{
		exit(1);
	}

	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar errorInfo[1024] = {};

	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
	if (Success == 0)
	{
		glGetProgramInfoLog(ShaderProgram, sizeof(errorInfo), NULL, errorInfo);
		fprintf(stderr, "Error linking shader program: '%s'\n", errorInfo);
		exit(1);
	}

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (Success == 0)
	{
		glGetProgramInfoLog(ShaderProgram, sizeof(errorInfo), nullptr, errorInfo);
		fprintf(stderr, "Invalid shader program: '%s'\n", errorInfo);
		exit(1);
	}

	glUseProgram(ShaderProgram);

	gWVPLocation = glGetUniformLocation(ShaderProgram, "gWVP");
	assert(gWVPLocation != 0xFFFFFFFF);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Tutorial 14 -- Camera Control - Part 1");

	initializeGlutCallbacks();

	pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	CreateVertexBuffer();
	CreateIndexBuffer();

	CompileShader();

	gPersProjInfo.FOV = 60.0f;
	gPersProjInfo.Height = WINDOW_HEIGHT;
	gPersProjInfo.Width = WINDOW_WIDTH;
	gPersProjInfo.zNear = 1.0f;
	gPersProjInfo.zFar = 100.0f;

	glutMainLoop();

	return 1;
}