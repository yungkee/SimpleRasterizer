#pragma once
#include "Maths/Vector3.h"

using namespace Maths;

namespace SceneObjects
{
	class Light
	{
	private:
		Vec3 m_position;
		float m_ambientComponent;
		float m_diffuseComponent;
		float m_specularComponent;

	public:
		Light();
		Light(const Vec3& pos, float ambient, float diffuse, float specular);
		Light(float x, float y, float z, float ambient, float diffuse, float specular);
		~Light();

		const Vec3& GetPosition() const;
		float Ambient() const;
		float Diffuse() const;
		float Specular() const;
	};
}

