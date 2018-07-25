#include <SceneObjects/Light.h>
using namespace SceneObjects;


Light::Light() : m_position(0.0f, 0.0f, 0.0f),
m_ambientComponent(0.0f),
m_diffuseComponent(0.0f),
m_specularComponent(0.0f)
{
}

Light::Light(const Vec3& pos,
	const float ambient,
	const float diffuse,
	const float specular) :
	m_position(pos),
	m_ambientComponent(ambient),
	m_diffuseComponent(diffuse),
	m_specularComponent(specular)
{
}

Light::Light(const float x, const float y, const float z,
	const float ambient,
	const float diffuse,
	const float specular) :
	m_position(x, y, z),
	m_ambientComponent(ambient),
	m_diffuseComponent(diffuse),
	m_specularComponent(specular)
{
}


Light::~Light()
{
}

const Vec3& Light::GetPosition() const
{
	return this->m_position;
}

float Light::Ambient() const
{
	return this->m_ambientComponent;
}

float Light::Diffuse() const
{
	return this->m_diffuseComponent;
}

float Light::Specular() const
{
	return this->m_specularComponent;
}
