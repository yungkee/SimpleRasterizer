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

		static Mesh* CreateCube();
		static Mesh* CreateSphere(const int& p_latitudeCount, const int& p_longitudeCount);

	private:
		void AddTriangleIndices(const int p_idx1, const int p_idx2, const int p_idx3);

	};
}
