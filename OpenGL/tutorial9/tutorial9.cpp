#include "glew.h"
#include "glut.h"
#include "math_3d.h"
#include "opengl_util.h"
#include <stdio.h>
#include <string>
#include <assert.h>

/************************************************************************/
/*	
	Color = vec4(clamp(Position, 0.0, 1.0), 1.0);
	Color in the graphics pipeline is usually represented using a floating point value in the range[0.0, 1.0]. That value is later 
	mapped to the integer 0 to 255 for each color channel (totaling in 16M colors). We set the vertex color value as a function of the
	vertex position. First we using the built-in function clamp() to make sure the values do not go outside of the 0.0-1.0 range. The reason
	is that the lower left vertex of the triangle is located at -1,-1. If we take that value as is it will be interpolated by the rasterzer 
	and until both X and Y pass zero we will not see anything because every value which is less than or equal to zero will be rendered as black.
	This means that half of the edge on each direction will be black before the color pass zero and become something meaningful.
	By clamping we make only the far bottom left black but as we get further away the color quickly becomes more bright. Try playing with the
	clamp function remove it all together or change its parameters to see the effect.
	The result of the clamp function does not go directly to the output variable since it is a 4-vector while the position is a 3-vector
	(clamp does not change the number of components, only their values). From the point of view of GLSL there is no default conversion here and
	we have to make this explicit. We do this using the notation 'vec4(vec3, W)' which creates a 4-vector by concatenating a 3-vector with the 
	supplied W value. In our case we use 1.0 becault this goes into the alpha part of the color and we want the pixel to be completely opaque.
	
	getType clamp(getType x, getType minVal, getType maxVal);
	getTeyp clamp(getTeyp x, float minVal, float maxVal);
	Returns min(max(x, minVal), maxVal)

	in vec4 Color
	The opposite side of the output color in the VS is the input color in the FS. 
	This variable undergoes interpolation by the rasterizer so every FS is (probably) executed with a different color.
*/
/************************************************************************/

GLuint VBO;
GLuint gWorldLocation;

const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";

static void RenderSceneCB()
{
	glClear(GL_COLOR_BUFFER_BIT);

	static float Scale = 0.0f;
	Scale += 0.01f;
	Matrix4f World;

	World.m[0][0] = sinf(Scale); World.m[0][1] = 0; World.m[0][2] = 0; World.m[0][3] = 0.0f;
	World.m[1][0] = 0; World.m[1][1] = sinf(Scale); World.m[1][2] = 0; World.m[1][3] = 0.0f;
	World.m[2][0] = 0; World.m[2][1] = 0; World.m[2][2] = sinf(Scale); World.m[2][3] = 0.0f;
	World.m[3][0] = 0; World.m[3][1] = 0; World.m[3][2] = 0; World.m[3][3] = 1.0f;

	glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &World.m[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}

static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderSceneCB);
	glutIdleFunc(RenderSceneCB);
}

static void CreateVertexBuffer()
{
	Vector3f Vertices[3];
	Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
	Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
	Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0)
	{
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
		exit(0);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	glShaderSource(ShaderObj, 1, p, Lengths);
	glCompileShader(ShaderObj);
	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar InfoLog[1024] = {};
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s' \n", ShaderType, InfoLog);
		exit(1);
	}

	glAttachShader(ShaderProgram, ShaderObj);
}

static void CompileShaders()
{
	GLuint ShaderProgram = glCreateProgram();

	if (ShaderProgram == 0)
	{
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	std::string vs, fs;

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
	GLchar ErrorLog[1024] = { 0 };

	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
	if (Success == 0)
	{
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success)
	{
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s' \n", ErrorLog);
		exit(1);
	}

	glUseProgram(ShaderProgram);

	gWorldLocation = glGetUniformLocation(ShaderProgram, "gWorld");
	assert(gWorldLocation != 0xFFFFFFFF);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("09 - Interpolation");

	InitializeGlutCallbacks();

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s' \n", glewGetErrorString(res));
		return 1;
	}

	printf("GL version : %s\n", glGetString(GL_VERSION));

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	CreateVertexBuffer();

	CompileShaders();

	glutMainLoop();
}