#include <Maths/Mat4.h>
#include <iostream>

using namespace Maths;

Mat4::Mat4()
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			this->m_matrix[i][j] = 0;
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
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			this->m_matrix[i][j] = other.m_matrix[i][j];
}


// TRANFORMATION MATRICES
Mat4 Mat4::CreateTranslationMatrix(const Vector3<float>& translation)
{
	return  { 1,0,0,translation.m_x,
		0,1,0,translation.m_y,
		0,0,1,translation.m_z,
		0,0,0,1 };
}

Mat4 Mat4::CreateScaleMatrix(const Vector3<float>& scale)
{
	return  { scale.m_x,0,0,0,
		0,scale.m_y,0,0,
		0,0,scale.m_z,0,
		0,0,0,1 };
}

Mat4 Mat4::CreateXRotationMatrix(const float p_angle)
{
	return  { 1,		0,				0,				0,
		0,		cos(p_angle),	-sin(p_angle),	0,
		0,		sin(p_angle),	cos(p_angle),	0,
		0,		0,				0,				1 };
}

Mat4 Mat4::CreateYRotationMatrix(const float p_angle)
{
	return  { cos(p_angle),	0,	sin(p_angle),	0,
		0,				1,	0,				0,
		-sin(p_angle),	0,	cos(p_angle),	0,
		0,				0,	0,				1 };
}

Mat4 Mat4::CreateZRotationMatrix(const float angle)
{
	return  { cos(angle),	-sin(angle),	0,	0,
		sin(angle),	cos(angle),	0,	0,
		0,				0,				1,	0,
		0,				0,				0,	1 };
}

Mat4 Mat4::CreateRotationMatrix(const Vec3& rotation)
{
	return  CreateXRotationMatrix(Vec3::ToRad(rotation.m_x)) *
		CreateYRotationMatrix(Vec3::ToRad(rotation.m_y)) *
		CreateZRotationMatrix(Vec3::ToRad(rotation.m_z));
}

Mat4 Mat4::CreateTransformMatrix(const Vec3& rotation, const Vec3& p_position, const Vec3& p_scale)
{
	return  CreateTranslationMatrix(p_position) *
		CreateRotationMatrix(rotation) *
		CreateScaleMatrix(p_scale);
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

void Mat4::Multiply(const Mat4& other)
{
	for (unsigned int i = 0; i < 4; ++i)
		for (unsigned int j = 0; j < 4; ++j)
			this->m_matrix[i][j] = VectorsMul(this->GetRow(i), other.GetColumn(j));
}

Vector4<float> Mat4::Multiply(const Vector4<float>& other) const
{
	Vector4<float> multiply;
	for (unsigned int i = 0; i < 4; ++i)
		multiply[i] = VectorsMul(this->GetRow(i), other);
	return multiply;
}

void Mat4::Multiply(const Vector4<float>& other)
{
	for (unsigned int i = 0; i < 4; ++i)
		for (unsigned int j = 0; j < 4; ++j)
			this->m_matrix[i][j] = VectorsMul(this->GetRow(i), other);
}

float Mat4::VectorsMul(const Vector4<float>& p_v1, const Vector4<float>& p_v2)
{
	float VectorsMul = 0;
	int i = 0;
	for (int j = 0; i < 4; ++j)
	{
		VectorsMul += p_v1[i] * p_v2[j];
		++i;
	}
	return VectorsMul;
}

// MATRICES TRANSFORMATIONS
Mat4 Mat4::Transpose() const
{
	Mat4 transpose;
	for (unsigned int i = 0; i < 4; ++i)
		for (unsigned int j = 0; j < 4; ++j)
			transpose.m_matrix[i][j] = m_matrix[j][i];
	return transpose;
}

float** Mat4::GetData()
{
	return reinterpret_cast<float**>(this->m_matrix);
}

Vector4<float> Mat4::GetRow(unsigned int p_row) const
{
	if (p_row < 4)
	{
		return Vector4<float>(this->m_matrix[p_row][0],
			this->m_matrix[p_row][1],
			this->m_matrix[p_row][2],
			this->m_matrix[p_row][3]);
	}
	std::cout << "Out of Matrix" << std::endl;
	return Vector4<float>();

}

Vector4<float> Mat4::GetColumn(unsigned int p_col) const
{
	if (p_col < 4)
	{
		return Vector4<float>(this->m_matrix[0][p_col],
			this->m_matrix[1][p_col],
			this->m_matrix[2][p_col],
			this->m_matrix[3][p_col]);
	}
	std::cout << "Out of Matrix" << std::endl;
	return Vector4<float>();

}

const float& Mat4::GetValue(unsigned int p_row, unsigned int p_col) const
{
	if (p_row < 4 && p_col < 4)
	{
		return this->m_matrix[p_row][p_col];
	}
	std::cout << "Out of Matrix" << std::endl;
	return this->m_matrix[0][0];
}

float& Mat4::GetValue(unsigned int p_row, unsigned int p_col)
{
	if (p_row < 4 && p_col < 4)
	{
		return this->m_matrix[p_row][p_col];
	}
	std::cout << "Out of Matrix" << std::endl;
	return this->m_matrix[0][0];
}

const float& Mat4::operator()(unsigned int p_row, unsigned int p_col) const
{
	if (p_row <= 4 && p_col <= 4)
		return this->m_matrix[p_row][p_col];
	std::cout << "Out of Matrix" << std::endl;
	return this->m_matrix[0][0];
}

float& Mat4::operator()(unsigned int p_row, unsigned int p_col)
{
	if (p_row < 4 && p_col < 4)
		return this->m_matrix[p_row][p_col];
	return m_matrix[0][0];
}


// TESTS
bool Mat4::IsEqual(const Mat4& other)
{
	for (unsigned int i = 0; i < 4; ++i)
		for (unsigned int j = 0; j < 4; ++j)
			if (m_matrix[i][j] != other.m_matrix[i][j])
				return false;
	return true;
}

bool Mat4::IsOrthogonal() const
{
	return Multiply(Transpose()).IsIdentity();
}

bool Mat4::IsIdentity() const
{
	for (unsigned int i = 0; i < 4; ++i)
		for (unsigned int j = 0; j < 4; ++j)
		{
			if (i == j && m_matrix[i][j] != 1)
				return false;
			if (i != j && m_matrix[i][j] != 0)
				return false;

		}
	return true;
}

Mat4 Mat4::operator+(const Mat4& other) const { return Add(other); }
void Mat4::operator+=(const Mat4& other) { Add(other); }

Mat4 Mat4::operator-(const Mat4& other) const { return Sub(other); }
void Mat4::operator-=(const Mat4& other) { Sub(other); }

Mat4 Mat4::operator*(const Mat4& other) const { return Multiply(other); }
void Mat4::operator*=(const Mat4& other) { Multiply(other); }


Vector4<float> Mat4::operator*(const Vector4<float>& other) const { return Multiply(other); }
void Mat4::operator*=(const Vector4<float>& other) { Multiply(other); }


Mat4 Mat4::operator+(const float& scalar) const { return Add(scalar); }
void Mat4::operator+=(const float& scalar) { Add(scalar); }

Mat4 Mat4::operator-(const float& scalar) const { return Sub(scalar); }
void Mat4::operator-=(const float& scalar) { Sub(scalar); }

Mat4 Mat4::operator*(const float& scalar) const { return Scale(scalar); }
void Mat4::operator*=(const float& scalar) { Scale(scalar); }

Mat4 Mat4::operator/(const float& scalar) const { return Div(scalar); }
void Mat4::operator/=(const float& scalar) { Div(scalar); }


bool Mat4::operator==(const Mat4& other) { return IsEqual(other); }
bool Mat4::operator!=(const Mat4& other) { return !IsEqual(other); }


std::ostream& Maths::operator<<(std::ostream& p_os, const Mat4& other)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			p_os << other(i, j) << " ";
		p_os << std::endl;
	}
	return p_os;
}
