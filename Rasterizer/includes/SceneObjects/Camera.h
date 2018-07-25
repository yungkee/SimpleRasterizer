#pragma once
#include "Maths/Mat4.h"

using namespace Maths;

namespace SceneObjects
{
	class Camera
	{
	private:
		Mat4 m_view;
		Mat4 m_projection;
		float m_top;
		float m_right;
		float m_near;
		float m_far;
	public:
		Camera(const int& width, const int& height, const float& near,
			const float& far, const float& fov,
			const Mat4& p_modelView = Mat4::CreateTranslationMatrix(Vec3(0, 0, 0)));
		~Camera();

		const Mat4& GetPerspectiveProjectionMatrix() const;


		void UseOrthographic();
		void UsePerspective();

		const float& Top() const;
		const float& Right() const;
		const float& Near() const;
		const float& Far() const;
	};
}
