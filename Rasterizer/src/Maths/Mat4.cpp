#include <Maths/Mat4.h>
#include <iostream>

using namespace Maths;

Mat4::Mat4()
{
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			this->m_matrix[i][j]=0;
}

Mat4::Mat4(std::initializer_list<float> initList)
{
	if (initList.size() < 16)
		std::cout << "Insufficient elements" << std::endl;
	else
	{
		auto it = initList.begin();
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				this->m_matrix[i][j] = *it++;
	}
}

Mat4::Mat4(const Mat4& other)
{
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			this->m_matrix[i][j] = other.m_matrix[i][j];
}

Mat4 Mat4::CreateTranslationMatrix(const Vector3<float>& translation)
{
	return  {	1,0,0,translation.m_x,
				0,1,0,translation.m_y,
				0,0,1,translation.m_z,
				0,0,0,1 };
}


Mat4 Mat4::CreateScaleMatrix(const Vector3<float>& scale)
{
	return  {	scale.m_x,0,0,0,
				0,scale.m_y,0,0,
				0,0,scale.m_z,0,
				0,0,0,1 };
}

Mat4 Mat4::CreateXRotationMatrix(const float angle)
{
	return  {	1,		0,				0,				0,
				0,		cos(angle),		-sin(angle),	0,
				0,		sin(angle),		cos(angle),		0,
				0,		0,				0,				1 };
}

Mat4 Mat4::CreateYRotationMatrix(const float angle)
{
	return  {	cos(angle),		0,	sin(angle),		0,
				0,				1,	0,				0,
				-sin(angle),	0,	cos(angle),		0,
				0,				0,	0,				1 };
}

Mat4 Mat4::CreateZRotationMatrix(const float angle)
{
	return  {	cos(angle),	  -sin(angle),	    0,	0,
				sin(angle),		cos(angle),		0,	0,
				0,				0,				1,	0,
				0,				0,				0,	1 };
}

Mat4 Mat4::CreateRotationMatrix(const Vec3& rotation)
{
	return  CreateYRotationMatrix(Vec3::ToRad(rotation.m_y)) *
			CreateXRotationMatrix(Vec3::ToRad(rotation.m_x)) *
			CreateZRotationMatrix(Vec3::ToRad(rotation.m_z));
}

Mat4 Mat4::CreateTransformMatrix(const Vec3& position, const Vec3& rotation, const Vec3& scale)
{
	return  CreateTranslationMatrix(position) *
			CreateRotationMatrix(rotation) * 
			CreateScaleMatrix(scale);
}


// SCALAR OPERATIONS
Mat4 Mat4::Add(const float& scalar) const
{
	Mat4 add;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			add.m_matrix[i][j] = this->m_matrix[i][j] + scalar;
	return add;
}

void Mat4::Add(const float& scalar)
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			this->m_matrix[i][j] += scalar;
}

Mat4 Mat4::Sub(const float& scalar) const
{
	Mat4 sub;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			sub.m_matrix[i][j] = this->m_matrix[i][j] - scalar;
	return sub;
}

void Mat4::Sub(const float& scalar)
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			this->m_matrix[i][j] -= scalar;
}

Mat4 Mat4::Scale(const float& scalar) const
{
	Mat4 scale;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			scale.m_matrix[i][j] = this->m_matrix[i][j] * scalar;
	return scale;
}

void Mat4::Scale(const float& scalar)
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			this->m_matrix[i][j] *= scalar;
}

Mat4 Mat4::Div(const float& scalar) const
{
	Mat4 div;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			div.m_matrix[i][j] = this->m_matrix[i][j] / scalar;
	return div;
}

void Mat4::Div(const float& scalar)
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			this->m_matrix[i][j] /= scalar;
}


// MATRICES ARTIHMETICS OPERATIONS
Mat4 Mat4::Add(const Mat4& other) const
{
	Mat4 add;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			add.m_matrix[i][j] = this->m_matrix[i][j] + other.m_matrix[i][j];
	return add;
}

void Mat4::Add(const Mat4& other)
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			this->m_matrix[i][j] += other.m_matrix[i][j];
}

Mat4 Mat4::Sub(const Mat4& other) const
{
	Mat4 sub;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			sub.m_matrix[i][j] = this->m_matrix[i][j] - other.m_matrix[i][j];
	return sub;
}

void Mat4::Sub(const Mat4& other)
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			this->m_matrix[i][j] -= other.m_matrix[i][j];
}

Mat4 Mat4::Multiply(const Mat4& other) const
{
	Mat4 multiply;
	for (unsigned int i = 0; i < 4; ++i)
		for (unsigned int j = 0; j < 4; ++j)
			multiply.m_matrix[i][j] = VectorsMul(this->GetRow(i), other.GetColumn(j));
	return multiply;
}

float Mat4::VectorsMul(const Vector4<float>& v1, const Vector4<float>& v2)
{
	float VectorsMul = 0;
	int i = 0;
	for (int j = 0; i < 4; ++j)
	{
		VectorsMul += v1[i] * v2[j];
		++i;
	}
	return VectorsMul;
}


float** Mat4::GetData()
{
	return reinterpret_cast<float**>(this->m_matrix);
}

Vector4<float> Mat4::GetRow(const unsigned int row) const
{
	if (row < 4)
	{
		return Vector4<float>(this->m_matrix[row][0],
			this->m_matrix[row][1],
			this->m_matrix[row][2],
			this->m_matrix[row][3]);
	}
	std::cout << "Out of Matrix" << std::endl;
	return Vector4<float>();

}

Vector4<float> Mat4::GetColumn(const unsigned int col) const
{
	if (col < 4)
	{
		return Vector4<float>(this->m_matrix[0][col],
			this->m_matrix[1][col],
			this->m_matrix[2][col],
			this->m_matrix[3][col]);
	}
	std::cout << "Out of Matrix" << std::endl;
	return Vector4<float>();

}

const float& Mat4::GetValue(const unsigned int row, const unsigned int col) const
{
	if (row < 4 && col < 4)
	{
		return this->m_matrix[row][col];
	}
	std::cout << "Out of Matrix" << std::endl;
	return this->m_matrix[0][0];
}

float& Mat4::GetValue(const unsigned int row, const unsigned int col)
{
	if (row < 4 && col < 4)
	{
		return this->m_matrix[row][col];
	}
	std::cout << "Out of Matrix" << std::endl;
	return this->m_matrix[0][0];
}

const float& Mat4::operator()(const unsigned int row, const unsigned int col) const
{
	if (row < 4 && col < 4)
		return this->m_matrix[row][col];
	std::cout << "Out of Matrix" << std::endl;
	return this->m_matrix[0][0];
}

float& Mat4::operator()(const unsigned int row, const unsigned int col)
{
	if (row < 4 && col < 4)
		return this->m_matrix[row][col];
	return m_matrix[0][0];
}

Mat4 Mat4::operator+(const Mat4& other) const { return Add(other); }
Mat4 Mat4::operator-(const Mat4& other) const { return Sub(other); }
Mat4 Mat4::operator*(const Mat4& other) const { return Multiply(other); }
Mat4 Mat4::operator/(const float& scalar) const { return Div(scalar); }


std::ostream& Maths::operator<<(std::ostream& os, const Mat4& other)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			os << other(i, j) << " ";
		os << std::endl;
	}
	return os;
}
