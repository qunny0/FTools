#include "math_3d.h"
#include "glew.h"
#include "glut.h"

#include "ogldev_app.h"
#include "ogldev_util.h"
#include "ogldev_pipeline.h"
#include "ogldev_camera.h"
#include "ogldev_texture.h"
// #include "lighting_technique.h"
#include "ogldev_glut_backend.h"

#define WINDOW_WIDTH		1920
#define WINDOW_HEIGHT		1200

struct Vertex
{
	Vector3f	m_pos;
	Vector2f	m_tex;
	Vector3f	m_normal;

	Vertex() {}

	Vertex(Vector3f pos, Vector2f tex)
	{
		m_pos = pos;
		m_tex = tex;
		m_normal = Vector3f(0.0f, 0.0f, 0.0f);
	}
};

class Tutorial19 : public ICallbacks, public OgldevApp
{
public:
	Tutorial19()
	{
	
	}

	~Tutorial19()
	{

	}

	bool Init()
	{

	}

	void Run()
	{

	}

	virtual void RenderSceneCB()
	{

	}

	virtual void KeyboardCB(OGLDEV_KEY OgldevKey)
	{

	}

	virtual void PassiveMouseCB(int x, int y)
	{

	}

private:
	void CalcNormals(const unsigned int* pIndices, unsigned int IndexCount,
		Vertex* pVertices, unsigned int VertexCount)
	{

	}

	void CreateVertexBuffer(const unsigned int* pIndices, unsigned int IndexCount)
	{

	}

	void CreateIndexBuffer(const unsigned int* pIndices, unsigned int SizeInBytes)
	{

	}

private:
	GLuint		m_VBO;
	GLuint		m_IBO;
	LightingTechnique*	m_pEffect;
	Texture*			m_pTexture;
	Camera*				m_pGameCamera;
	float				m_scale;
	DirectionalLight	m_directionLight;
	PersProjInfo		m_persProjInfo;
};

int main(int argc, char** argv)
{
// 	Magick::InitializeMagick(*argv);

	if (!GLUTBackendCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false, "Tutorial 19 - specular lighting"))
	{
		return 1;
	}

	Tutorial19* pApp = new Tutorial19();

	if (!pApp->Init())
	{
		return 1;
	}

	pApp->Run();

	delete pApp;

	return 0;
}