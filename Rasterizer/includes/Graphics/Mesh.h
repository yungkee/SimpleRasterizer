#pragma once
#include <vector>
#include <memory>
#include <Graphics/Vertex.h>

namespace Graphics
{
	class Mesh
	{
	private:
		std::vector<Vertex> m_vertices;
		std::vector<int> m_indices;

	public:
		unsigned GetTriangleCount() const;
		const Vertex* GetTriangleVertices(unsigned triangleIndex) const;


		Mesh();
		~Mesh();

	};
}
