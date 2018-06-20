#include <Graphics/Texture.h>

using namespace Graphics;


Texture::Texture(const unsigned& width, const unsigned& height) : m_width{ width }, m_height{ height }
{
	m_pixels = new Color[m_width * m_height];
}

Texture::~Texture()
{
	delete[] m_pixels;
}

void Texture::SetPixelColor(unsigned x, unsigned y, const Color& c)
{
	if (y >= this->m_height || x >= this->m_width) return;
	this->m_pixels[y * this->m_width + x] = c;
}

void Texture::Clear(const Color& c) const
{
	for (int i = 0; i < this->m_width * this->m_height; ++i)
	{
		m_pixels[i] = c;
	}
}

Color* Texture::GetPixels()
{
	return this->m_pixels;
}

unsigned Texture::Width() const
{
	return this->m_width;
}

unsigned Texture::Height() const
{
	return this->m_height;
}