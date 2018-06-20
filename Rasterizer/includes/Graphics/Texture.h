#pragma once
#include <Graphics/Color.h>

namespace Graphics
{
	class Texture
	{
	private:
		Color * m_pixels;
		unsigned int m_width;
		unsigned int m_height;
	public:
		Texture(const unsigned int& width, const unsigned int& height);
		~Texture();

		void SetPixelColor(unsigned int x, unsigned int y, const Color& c);
		void Clear(const Color& c = Color(0, 0, 0)) const;

		Color* GetPixels();
		unsigned int Width() const;
		unsigned int Height() const;

	};
}
