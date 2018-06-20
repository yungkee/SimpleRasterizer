#include <Graphics/Mesh.h>
#include <iostream>

using namespace Graphics;

Mesh::Mesh()
{
	std::cout << "Mesh created" << std::endl;
}


Mesh::~Mesh()
{
	std::cout << "Mesh destroyed" << std::endl;
}

unsigned Mesh::GetTriangleCount() const
{
	return (unsigned)m_indices.size() / 3;
}

const Vertex* Mesh::GetTriangleVertices(unsigned triangleIndex) const
{
	triangleIndex *= 3;
	Vertex* triangle = new Vertex[3];
	triangle[0] = this->m_vertices[this->m_indices[triangleIndex]];
	triangle[1] = this->m_vertices[this->m_indices[triangleIndex + 1]];
	triangle[2] = this->m_vertices[this->m_indices[triangleIndex + 2]];
	return triangle;
}