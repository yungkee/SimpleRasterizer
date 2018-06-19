#pragma once

#include <string>

namespace Maths
{
	template<typename T>
	class Vector4
	{
	public:
		T x;
		T y;
		T z;
		T w;

	public:

		Vector4();

		~Vector4() = default;
	};
}
