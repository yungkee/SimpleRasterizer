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


Mesh* Mesh::CreateCube()
{
	Mesh* cube = new Mesh();
	cube->m_vertices.reserve(8);

	cube->m_vertices.emplace_back(0.5f, 0.5f, 0.5f);
	cube->m_vertices.emplace_back(0.5f, -0.5f, 0.5f);
	cube->m_vertices.emplace_back(-0.5f, 0.5f, 0.5f);
	cube->m_vertices.emplace_back(-0.5f, -0.5f, 0.5f);
	cube->m_vertices.emplace_back(0.5f, 0.5f, -0.5f);
	cube->m_vertices.emplace_back(0.5f, -0.5f, -0.5f);
	cube->m_vertices.emplace_back(-0.5f, 0.5f, -0.5f);
	cube->m_vertices.emplace_back(-0.5f, -0.5f, -0.5f);

	cube->m_indices.reserve(36);

	cube->AddTriangleIndices(0, 1, 2);
	cube->AddTriangleIndices(1, 2, 3);
	cube->AddTriangleIndices(0, 4, 1);
	cube->AddTriangleIndices(4, 5, 1);
	cube->AddTriangleIndices(0, 2, 6);
	cube->AddTriangleIndices(0, 6, 4);
	cube->AddTriangleIndices(6, 4, 5);
	cube->AddTriangleIndices(6, 5, 7);
	cube->AddTriangleIndices(6, 2, 3);
	cube->AddTriangleIndices(6, 3, 7);
	cube->AddTriangleIndices(7, 5, 3);
	cube->AddTriangleIndices(5, 3, 1);

	return cube;
}

Mesh* Mesh::CreateSphere(const int& p_latitudeCount, const int& p_longitudeCount)
{
	Mesh* sphere = new Mesh;

	//TODO implement Coord & Indices

	return sphere;
}

void Mesh::AddTriangleIndices(const int p_idx1, const int p_idx2, const int p_idx3)
{
	this->m_indices.push_back(p_idx1);
	this->m_indices.push_back(p_idx2);
	this->m_indices.push_back(p_idx3);
}