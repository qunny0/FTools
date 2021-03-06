/*
	To get texture mapping working you need to do three things;
	1. Load a texture into OpenGL
	2. Supply texture coordinates with the vertices (to map the texture to them)
	3. Perform a sampling operation from the texture using the texture coordinates in order to get the pixel color.
	Since a triangle is scaled, rotated, translated and finally projected it can land on the screen in numerous ways and look very different depending on its
	orientation to the camera. What the GPU needs to do is make the texture follow the movement of the vertices of the triangle so that it will look real
	(if the texture appear to "swim" across the triangle it will not). To do this the developer supplies a set of coordinates knows as 'texture coordinates' to
	each vertex. As the GPU rasterizes the triangle it interpolates the texture coordinates across the triangle face and in the fragment shader the developer maps
	these coordinates to the texture. This action is know as 'sampling' and the result of sampling is a texel (a pixel in a texture). the texel often contains a color
	which is used to paint the corresponding pixel to the screen. In the coming tutorials we will see that the texel can contain different types of data that can be 
	used for multiple effects.

	OpenGl supports several types of textures such as 1D, 2D, 3D, cube, etc that can be used for different techniques. Let`s stick with 2D texture for now. A 2D texture
	has a width and height that can be any number within the limitations of the spec. Multiplying the width by height tells you the number of texels in the texture.
	How do you specify the texture coordinates of a vertex? - No, it is not the coordinate of a texel inside the texture. That would be too limiting because replacing the 
	a texture with one that has different width/height means that will need to update the texture coordinates of all the vertices to match the new texture. The ideal 
	scenario is to be enable to change textures without changing texture coordinates. Therefore, texture coordinates are specified in 'texture space' which is simply 
	the normalized range [0,1]. This means that the texture coordinates is usually a fraction and by multiplying that fraction with the corresponding width/height of a 
	texture we get the coordinate of the texel in the texture. For example, If the texture coordinate is [0.5, 0.1] and the texture has a width of 320 and a height of 200
	the texel location will be (160,20) (0.5*320=160 and 0.1*200=20).


	glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	The general function glTexParameterf control many aspects of the texture sampling operation. 
	These aspects are part of the texture sampling state. 
	Here we specify the filter to be used for magnification and minification. 
	Every texture has a given width and height dimensions but rarely it is applied to a triangle of the same proportion. 
	In most case the triangle is either smaller or larger than the texture. 
	In this case the filter type determines how to handle the case of magnifying or minifying the texture to match the proportion of the triangle. 
	When the rasterized triangle is larger than the texture (e.g. it is very close to the camera) we may have several pixels covered by the same texel (magnification). 
	When it is smaller (e.g. very far from the camera) several texels are covered by the same pixel (minification). 
	Here we select the linear interpolation filter type for both cases. 
	As we've seen earlier, linear interpolation provides good looking results by mixing the colors of a 2x2 texel quad based on the proximity of the actual texel location (calculated by scaling the texture coordinates by the texture dimensions).
*/

#include <stdio.h>

#include "glew.h"
#include "glut.h"

#include "ogldev_pipeline.h"
#include "ogldev_camera.h"
#include "ogldev_texture.h"
#include "ogldev_glut_backend.h"

#define WINDOW_WIDTH	1280
#define WINDOW_HEIGHT	1024

struct Vertex
{
	Vector3f	m_pos;
	Vector2f	m_tex;

	Vertex() {};

	Vertex(Vector3f pos, Vector2f tex)
	{
		m_pos = pos;
		m_tex = tex;
	}
};

GLuint		VBO;
GLuint		IBO;
GLuint		gWVPLocation;
GLuint		gSampler;
Texture*	pTexture = nullptr;
Camera*		pGameCamera = nullptr;

PersProjInfo gPersProjInfo;

const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";

static void RenderSceneCB()
{
	pGameCamera->OnRender();

	glClear(GL_COLOR_BUFFER_BIT);

	static float scale = 0.0f;
// 	scale += 0.1f;

	Pipeline p;
	p.Rotate(0.0f, scale, 0.0f);
	p.WorldPos(0.0f, 0.0f, 3.0f);
	p.SetCamera(*pGameCamera);
	p.SetPerspectiveProj(gPersProjInfo);

	glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, (const GLfloat*)p.GetWVPTrans());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	pTexture->Bind(GL_TEXTURE0);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glutSwapBuffers();
}

static void SpecialKeyboardCB(int key, int x, int y)
{
	OGLDEV_KEY ogldevKey = GLUTKeyToOGLDEVKey(key);
	pGameCamera->OnKeyboard(ogldevKey);
}

static void KeyboardCB(unsigned char Key, int x, int y)
{
// 	switch (Key) {
// 		case 'q':
// 			glutLeaveMainLoop();
// 	}
}

static void PassiveMouseCB(int x, int y)
{
	pGameCamera->OnMouse(x, y);
}

static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderSceneCB);
	glutIdleFunc(RenderSceneCB);
	glutSpecialFunc(SpecialKeyboardCB);
// 	glutPassiveMotionFunc(PassiveMouseCB);
	glutKeyboardFunc(KeyboardCB);
}

static void CreateVertexBuffer()
{
	Vertex vertices[4] = {
		Vertex(Vector3f(-1.0f, -1.0f, 0.5774f), Vector2f(0.0f, 0.0f)),		// top left (0, 1)
		Vertex(Vector3f(0.0f, -1.0f, -1.15475f), Vector2f(0.5f, 0.0f)),		// 
		Vertex(Vector3f(1.0f, -1.0f, 0.5773f), Vector2f(1.0f, 0.0f)),		// bottom right (1, 1)
		Vertex(Vector3f(0.0f, 1.0f, 0.0f), Vector2f(0.5f, 1.0f)),			// 
	};
	// Y���෴��

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
		0, 1, 2,
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
		GLchar infoLog[1024];
		glGetShaderInfoLog(shaderObj, 1024, nullptr, infoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", shaderType, infoLog);
		exit(1);
	}

	glAttachShader(shaderProgram, shaderObj);
}

static void CompileShaders()
{
	GLuint shaderProgram = glCreateProgram();

	if (shaderProgram == 0)
	{
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	string fs, vs;
	if (!ReadFile(pVSFileName, vs))
	{
		exit(1);
	}
	if (!ReadFile(pFSFileName, fs))
	{
		exit(1);
	}

	addShader(shaderProgram, vs.c_str(), GL_VERTEX_SHADER);
	addShader(shaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint success = 0;
	GLchar errorLog[1024] = {};

	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (success == 0)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", errorLog);
		exit(1);
	}

	glValidateProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
	if (success == 0)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), nullptr, errorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", errorLog);
		exit(1);
	}

	glUseProgram(shaderProgram);

	gWVPLocation = glGetUniformLocation(shaderProgram, "gWVP");
	assert(gWVPLocation != 0xFFFFFFFF);
	gSampler = glGetUniformLocation(shaderProgram, "gSampler");
	assert(gSampler != 0xFFFFFFFF);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tutorial 17 - Base Texture Mapping");

	InitializeGlutCallbacks();

	pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	CreateVertexBuffer();
	CreateIndexBuffer();

	CompileShaders();

	glUniform1i(gSampler, 0);

	pTexture = new Texture(GL_TEXTURE_2D, "../Content/test.png");
	if (!pTexture->Load())
	{
		return 1;
	}

	/*	When creating a Texture object you will need to specify a target (we use GL_TEXTURE_2D) and file name. 
		After that you call the Load() function. This can fail, for example, if the file does not exist or if
		ImageMagick encountered any other error. When you want to use a specific Texture instance you need to 
		bind it to one of the texture units.
	*/

	/*
		glTexImage2D(m_textureTarget, 0, GL_RGBA, m_pImage->columns(), m_pImage->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());
		This rather complex function is used to load the main part of the texture object, that is, the texture data itself.
		There are several glTexImage* function available and each one covers a few texture targets.
		
		The texture target is always the first parameter.
		The second parameter is the LOD, or Level - Of - Detail. 
			A texture object can contain the same texture in different resolutions, a concept known as mip - mapping.Each mip - map has a different LOD index, 
			starting from 0 for the highest resolution and growing as resolution decreases.
			For now, we have only a single mip - map so we pass zero.
		The next parameter is the internal format in which OpenGL stores the texture.
			For example, you can pass a texture with the full four color channel(red, green, blue and alpha) 
			but if you specify GL_RED you will get a texture with only the red channel, which looks kinda, well..., red(try it!).
			We use GL_RGBA to get the full texture color correctly.
		The next two parameters are the width and height of the texture in texels.
			ImageMagick conveniently stores this information for us when it loads the image and we get it using the Image::columns() / rows() functions.
		The fifth parameter is the border, which we leave as zero for now.
		The last three parameters specify the source of the incoming texture data.
			The parameters are format, type and memory address.
			The format tells us the number of channels and needs to match the BLOB that we have in memory.
			The type describes the core data type that we have per channel.
			OpenGL supports many data types but in the ImageMagick BLOB we have one byte per channel so we use GL_UNSIGNED_BYTE.
			Finally comes the memory address of the actual data which we extract from the BLOB using the Blob::data() function.
	*/
	
	
	gPersProjInfo.FOV = 60.0f;
	gPersProjInfo.Height = WINDOW_HEIGHT;
	gPersProjInfo.Width = WINDOW_WIDTH;
	gPersProjInfo.zNear = 1.0f;
	gPersProjInfo.zFar = 100.0f;

	glutMainLoop();

	return 0;
}