#pragma once

#include <Maths/Vector3.h>
#include <Maths/Vector4.h>
#include "Mat3.h"

namespace Maths
{
	class Mat4
	{
	public:
		float m_matrix[4][4];
	public:
		Mat4();
		~Mat4() {}
	};
}