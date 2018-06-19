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
		Mat4();
		Mat4(std::initializer_list<float> initList);
		Mat4(const Mat4& other);
		~Mat4() {}

		//translation matrices
		static Mat4 CreateTranslationMatrix(const Vector3<float>& translation);
		static Mat4 CreateScaleMatrix(const Vector3<float>& scale);

		static Mat4 CreateXRotationMatrix(const float angle);
		static Mat4 CreateYRotationMatrix(const float angle);
		static Mat4 CreateZRotationMatrix(const float angle);

		static Mat4 CreateRotationMatrix(const Vec3& rotation);
		static Mat4 CreateTransformMatrix(const Vec3& p_position, const Vec3& p_rotation, const Vec3& p_scale);

		// SCALAR OPERATIONS
		Mat4 Add(const float & scalar) const;
		void Add(const float & scalar);

		Mat4 Sub(const float & scalar) const;
		void Sub(const float & scalar);

		Mat4 Scale(const float &scalar) const;
		void Scale(const float &scalar);

		Mat4 Div(const float &scalar) const;
		void Div(const float &scalar);


		// MATRICES ARTIHMETICS OPERATIONS
		Mat4 Add(const Mat4 &other) const;
		void Add(const Mat4 &other);

		Mat4 Sub(const Mat4 &other) const;
		void Sub(const Mat4 &other);

		Mat4 Multiply(const Mat4 &other) const;

		static float VectorsMul(const Vector4<float> &v1, const Vector4<float> &v2);
	
		// GETTERS
		float** GetData();
		Vector4<float> GetRow(unsigned int row) const;
		Vector4<float> GetColumn(unsigned int col) const;

		const float& GetValue(unsigned int row, unsigned int col) const;
		float& GetValue(unsigned int row, unsigned int col);

		const float& operator()(unsigned int row, unsigned int col) const;
		float& operator()(unsigned int row, unsigned int col);

		// OPERATORS
		Mat4 operator+(const Mat4 &other) const;
		Mat4 operator-(const Mat4 &other) const;
		Mat4 operator*(const Mat4 &other) const;
		Mat4 operator/(const float &scalar) const;
	};

	std::ostream &operator<<(std::ostream &os, const Mat4 &other);



}