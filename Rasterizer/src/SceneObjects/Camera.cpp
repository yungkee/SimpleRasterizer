#include <SceneObjects\Camera.h>
#include "Rendering/Rasterizer.h"

using namespace SceneObjects;


Camera::Camera(const int& width, const int& height, const float& near, const float& far, const float& fov,
	const Mat4& modelView) : m_view(modelView), m_near(near), m_far(far)
{
	this->m_top = tanf(fov * static_cast<float>(M_PI) / 360.f) * this->m_near;
	this->m_right = this->m_top * (width / (float)height);
	this->m_projection = Rendering::Rasterizer::CreatePerspectiveProjectionMatrix(
		-this->m_right, this->m_right, -this->m_top,
		this->m_top, this->m_near, this->m_far);
}

Camera::~Camera()
{
}

const Mat4& Camera::GetPerspectiveProjectionMatrix() const
{
	return this->m_projection;
}

void Camera::UseOrthographic()
{
	this->m_projection = Rendering::Rasterizer::CreateOrthographicProjectionMatrix(
		-this->m_right, this->m_right, -this->m_top,
		this->m_top, this->m_near, this->m_far);
}

void Camera::UsePerspective()
{
	this->m_projection = Rendering::Rasterizer::CreatePerspectiveProjectionMatrix(
		-this->m_right, this->m_right, -this->m_top,
		this->m_top, this->m_near, this->m_far);
}

const float& Camera::Top() const
{
	return m_top;
}

const float& Camera::Right() const
{
	return m_right;
}

const float& Camera::Near() const
{
	return m_near;
}

const float& Camera::Far() const
{
	return m_far;
}