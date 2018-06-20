#include <Graphics/Color.h>

using namespace Graphics;

Color::Color() : m_r(0), m_g(0), m_b(0), m_a(255)
{
}

Color::Color(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a) : m_r(r), m_g(g), m_b(b), m_a(a)
{
}

Color::Color(const Color& c)
{
	this->m_r = c.m_r;
	this->m_g = c.m_g;
	this->m_b = c.m_b;
	this->m_a = c.m_a;
}

Color::~Color()
{

}
