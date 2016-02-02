#include "glew.h"
#include "glut.h"
#include "math_3d.h"
#include "opengl_util.h"
#include <string>
#include <assert.h>
using namespace std;

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

	Matrix4f world;
	world.m[0][0] = cosf(scale);	world.m[0][1] = 0.0f; world.m[0][2] = -sinf(scale); world.m[0][3] = 0.0f;
	world.m[1][0] = 0.0f;			world.m[1][1] = 1.0f; world.m[1][2] = 0.0f;			world.m[1][3] = 0.0f;
	world.m[2][0] = sinf(scale);	world.m[2][1] = 0.0f; world.m[2][2] = cosf(scale);	world.m[2][3] = 0.0f;
	world.m[3][0] = 0.0f;			world.m[3][1] = 0.0f; world.m[3][2] = 0.0f;		world.m[3][3] = 1.0f;
	glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &world.m[0][0]);

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
		fprintf(stderr, "Error creating shader type %d\n", shaderType);
		exit(1);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengthes[1];
	Lengthes[0] = strlen(pShaderText);

	glShaderSource(shaderObj, 1, p, Lengthes);
	glCompileShader(shaderObj);

	GLint success;
	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar InfoLog[1024] = {};
		glGetShaderInfoLog(shaderObj, sizeof(InfoLog), NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d : '%s' \n", shaderType, InfoLog);
		exit(1);
	}

	glAttachShader(shaderProgram, shaderObj);
}

static void CompileShaders()
{
	// create program
	GLuint shaderProgram = glCreateProgram();
	if (shaderProgram == 0)
	{
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	string vs, fs;
	if (ReadFile(pVSShader, vs) == 0) {
		exit(1);
	}
	if (ReadFile(pFSShader, fs) == 0) {
		exit(1);
	}

	addShader(shaderProgram, vs.c_str(), GL_VERTEX_SHADER);
	addShader(shaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint success = 0;
	GLchar ErrorInfo[1024] = {};

	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (success == 0)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(ErrorInfo), nullptr, ErrorInfo);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorInfo);
		exit(1);
	}

	glValidateProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
	if (success == 0)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(ErrorInfo), nullptr, ErrorInfo);
		fprintf(stderr, "Error validting shader program: '%s' \n", ErrorInfo);
		exit(1);
	}

	glUseProgram(shaderProgram);

	gWorldLocation = glGetUniformLocation(shaderProgram, "gWorld");
	assert(gWorldLocation != 0xFFFFFFFF);
}

static void CreateVertexBuffer()
{
	Vector3f Vectices[4] = {};
	Vectices[0] = Vector3f(0.0f, 0.0f, 0.5f);
	Vectices[1] = Vector3f(0.0f, 0.0f, -0.5f);
	Vectices[2] = Vector3f(0.5f, 0.0f, 0.0f);
	Vectices[3] = Vector3f(0.25f, 0.5f, 0.0f);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vectices), Vectices, GL_STATIC_DRAW);
}

static void CreateIndexBuffer()
{
	GLuint Indices[] = {
		0, 1, 2,
		0, 3, 2,
		0, 3, 1,
		3, 1, 2
	};

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

static void initState(int* argc, char** argv, const char* title)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(200, 200);
	glutCreateWindow(title);

	// Must be done after glut is initialized
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s' \n", glewGetErrorString(res));
		exit(1);
	}
	printf("GL version: %s\n", glGetString(GL_VERSION));
}

static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderSceneCB);
	glutIdleFunc(RenderSceneCB);
}

int main(int argc, char* argv[])
{
	initState(&argc, argv, "Indexed Draws");

	InitializeGlutCallbacks();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	CreateVertexBuffer();
	CreateIndexBuffer();

	CompileShaders();

	glutMainLoop();

	return 0;
}