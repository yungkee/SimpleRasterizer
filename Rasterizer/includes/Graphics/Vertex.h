#pragma once
#include <Maths/Vector3.h>
#include "Color.h"

using namespace Maths;

namespace Graphics
{
	class Vertex
	{
	private:
		Vec3 m_position;
		Vec3 m_normal;
		Color m_color;
	public:
		Vertex();
		Vertex(const Vertex& vertex);
		void operator=(const Vertex& vertex);
		~Vertex();

		Vertex(const Vec3& pos, const Vec3& norm = Vec3(0.0f,0.0f,0.0f), const Color& color = Color(255,255,255));
		Vertex(float x, float y, float z, const Color& color = Color(255, 255, 255));

		const Vec3& GetPosition() const;
		const Color& GetColor() const;

		void SetColor(const Color& color);
		void SetPosition(const Vec3& pos);

	};
}
