#pragma once
namespace Graphics
{
	class Color
	{	
	public:
		unsigned char m_r;
		unsigned char m_g;
		unsigned char m_b;
		unsigned char m_a;

		Color();
		Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
		Color(const Color& c);
		~Color();
	};
}
