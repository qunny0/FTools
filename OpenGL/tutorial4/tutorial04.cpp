#include "glew.h"
#include "glut.h"
#include "math_3d.h"
#include "opengl_util.h"
#include <stdio.h>
#include <string>

/************************************************************************/
/*	Simple Shader Instance
	GL_VERTEX_SHADER: 修改了坐标
	GL_FRAGMENT_SHADER：修改了每个坐标的颜色

顶点着色器：
	替代顶点变换
	替代光照
	替代纹理坐标处理
-- 顶点着色器和片断着色器之间，仍然保留了一些固定功能阶段，它们将作为粘帖两种着色器的胶水。
片断着色器：
	替代纹理
	替代颜色求和
	替代雾

内置变量：
顶点着色器：
输入：gl_Color, gl_SecondaryColor, gl_Normal, gl_Vertex, gl_MultiTexCoordn, gl_FogCoord
输出：gl_Position, gl_ClipVertex, gl_PointSize, gl_FrontColor, gl_BackColor, gl_FrontSecondaryColor, gl_BackSecondaryColor, gl_TexCoord[], gl_FogFragCoord
片断着色器：
输入：gl_Color, gl_SecondaryColor, gl_TexCoord[], gl_FogFragCoord, gl_FragCoord, gl_FrontFacing, gl_PointCoord
输出：gl_FragColor, gl_FragData[], gl_FragDepth

Vertex Processor ---> Geometry Processor ---> Clipper ---> Rasterizer(Fragment Processor)

	#version 330
	This tells the compiler that we are targeting version 3.3 of GLSL.
	If the compiler does not support it, it will emit an error

	layout (location = 0) in vec3 Position;
	This statement appears in the vertex shader. 
	It declares that a vertex specify attribute which is a vector of 3 floats will be known as 'Position' in the shader.
	'Vertex specific' means that for every invocation of the shader in the GPU the value of a new vertex from the buffer will
	be supplied. The first section of the statement, layout (location = 0), creates the binding between the attribute name and 
	attribute in the buffer. This is required for cases where our vertex contains several attributes (position, normal, 
	texture coordinates, etc). We have to let the compiler know which attribute in the vertex in the buffer must be mapped to the 
	declared attribute in the shader. There are two ways to do this. We can either set it explicitly as we do here (to zero).
	In that case we can use a hard coded value in our application (which we did with the first parameter to the call to 
	glVertexAttributePointer). Or we can leave it out (and simply declare 'in vec3 Position' in the shader) and then query the location
	from the application at runtime using glGetAttribuLocation. In that case we will need to supply the returned value to 
	glVertexAttributePointer instead of using the hard coded value. We choose the simply way here but for more complex application
	it better to let the compiler determine the attribute indices and query them during runtime. This is makes it easier 
	intergrating shaders from multiple sources without adaping them to your buffer layout.

*/
/************************************************************************/

/************************************************************************/
/*	1. layout (location = 0) in vec3 Position; 这句话是怎么和程序对应起来的
	layout (location = 0).
	2. out vec4 FragColor;这句话是怎么和程序对应起来的
*/
/************************************************************************/

GLuint VBO;
const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";

static void RenderSceneCB()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);

	glutSwapBuffers();
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
		exit(1);
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
		exit(1);

	if (!ReadFile(pFSFileName, fs))
		exit(1);

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
}

static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderSceneCB);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("04 - Shader");

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

	// compile shader
 	CompileShaders();

	glutMainLoop();
}