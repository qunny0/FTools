#pragma once

#include "technique.h"
#include "ogldev_math_3d.h"

struct DirectionalLight
{
	Vector3f	Color;
	float		AmbientIntensity;
	Vector3f	Direction;
	float		DiffuseIntensity;
};

class LightingTechnique : public Technique
{
public:
	LightingTechnique();
	virtual ~LightingTechnique();

	virtual bool Init();

	void SetWVP(const Matrix4f& WVP);
	void SetWorldMatrix(const Matrix4f& WorldInverse);
	void SetTextureUnit(unsigned int TextureUnit);
	void SetDirectionalLight(const DirectionalLight& Light);

private:
	GLuint	m_WVPLocation;
	GLuint	m_WorldMatrixLocation;
	GLuint	m_SamplerLocation;

	struct {
		GLuint	Color;
		GLuint	AmbientIntensity;
		GLuint	Direction;
		GLuint	DiffuseIntensity;
	} m_dirLightLocation;
};

