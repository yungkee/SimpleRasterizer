#include <Graphics/Vertex.h>

using namespace Graphics;

Vertex::Vertex(): m_position(0.0f, 0.0f, 0.0f),
				  m_normal(0.0f,0.0f,0.0f), 
				  m_color(255,255,255)
{}

Vertex::Vertex(const Vertex& vertex): m_position(vertex.m_position),
										m_normal(vertex.m_normal.Normalize()),
										m_color(vertex.m_color)
{
}


void Vertex::operator=(const Vertex& vertex)
{
	this->m_position = vertex.m_position;
	this->m_normal = vertex.m_normal.Normalize();
	this->m_color = vertex.m_color;
}

Vertex::Vertex(const Vec3& pos, const Vec3& norm, const Color& color) : 
				  m_position(pos), 
				  m_normal(norm.Normalize()),
				  m_color(color)
{
}

Vertex::Vertex(const float x, const float y, const float z, const Color& color) : 
				  m_position(x, y, z), 
				  m_normal(0, 0, 0), 
				  m_color(color)
{
	m_normal.Normalize();
}

Vertex::~Vertex()
{}

void Vertex::SetPosition(const Vec3& pos)
{
	this->m_position = pos;
}

const Vec3& Vertex::GetPosition() const
{
	return this->m_position;
}


void Vertex::SetColor(const Color & color)
{
	this->m_color = color;
}

const Color& Vertex::GetColor() const
{
	return this->m_color;
}

