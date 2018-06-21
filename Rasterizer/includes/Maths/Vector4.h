#pragma once

#include <string>

namespace Maths
{
	template<typename T>
	class Vector4
	{
	public:
		T m_x;
		T m_y;
		T m_z;
		T m_w;

	public:

		static float ToDegree(const double &angle)
		{
			return angle * 180.0 / M_PI;
		}
		static float ToRad(const double &angle)
		{
			return angle * M_PI / 180.0f;
		}

		Vector4(const T& out_x = 0.0f, const T& out_y = 0.0f, const T& out_z = 0.0f, const T& out_w = 1.0f) : m_x{ out_x }, m_y{ out_y }, m_z{ out_z }, m_w{ out_w } {}
		Vector4(const Vector3<T>& vec3, const T& out_w = 1.0f) : m_x{ vec3.m_x }, m_y{ vec3.m_y }, m_z{ vec3.m_z }, m_w{ out_w } {}
		Vector4(const Vector4 &other)
		{
			this->m_x = other.m_x;
			this->m_y = other.m_y;
			this->m_z = other.m_z;
			this->m_w = other.m_w;
		}

		Vector4 &operator=(const Vector4 &other)
		{
			this->m_x = other.m_x;
			this->m_y = other.m_y;
			this->m_z = other.m_z;
			this->m_w = other.m_w;
			return *this;
		}

		~Vector4() = default;
		Vector4 Homogenize() const
		{
			if (this->m_w != 0 && this->m_w != 1)
			{
				Vector4 homogenized = this->Division(this->m_w);
				homogenized.m_w = 1;
				return homogenized;
			}
			return *this;
		}

		void Homogenize()
		{
			if (this->m_w != 0 && this->m_w != 1)
			{
				this->Division(this->m_w);
				this->m_w /= this->m_w;
			}
		}

		Vector4 Normalize() const
		{
			float mag = this->GetMagnitude();
			if (mag != 0 && mag != 1)
			{
				return this->Division(mag);
			}
			return this;
		}

		void Normalize()
		{
			float mag = this->GetMagnitude();
			if (mag != 0 && mag != 1)
			{
				this->Division(mag);
			}
		}

		T MagSq() const { return (this->m_x * this->m_x) + (this->m_y * this->m_y) + (this->m_z * this->m_z); }

		T GetMagnitude() const
		{
			if (this->w != 1.0f)
			{
				this->Homogenize();
			}
			return sqrt(MagSq());

		}
		T DotProduct(const Vector4 &other) const { return (this->m_x * other.m_x) + (this->m_y * other.m_y) + (this->m_z * other.m_z); }
		Vector4 CrossProduct(const Vector4 &other) const
		{
			float crossX = (this->m_y * other.m_z) - (other.m_y * this->m_z);
			float crossY = (this->m_z * other.m_x) - (other.m_z * this->m_x);
			float crossZ = (this->m_x * other.m_y) - (other.m_x * this->m_y);

			return Vector4(crossX, crossY, crossZ);
		}

		float AngleBetween(const Vector4 &other) const
		{
			if (this->m_x == 0 && this->m_y == 0 && this->m_z == 0) return 0.0f;
			if (other.m_x == 0 && other.m_y == 0 && other.m_z == 0) return 0.0f;


			const double amt = this->DotProduct(other) / (this->GetMagnitude() * other.GetMagnitude());

			if (amt <= -1) {
				return M_PI;
			}
			else if (amt >= 1) {
				return 0;
			}
			return static_cast<float>(acos(amt));
		}

		T operator,(const Vector4 &other) const { return this->DotProduct(other); }


		// SCALAR OPERATIONS

		Vector4 operator+(const Vector4 &other) const { return Vector4(this->m_x + other.m_x, this->m_y + other.m_y, this->m_z + other.m_z); }
		Vector4 &operator+=(const Vector4 &other)
		{
			this->m_x += other.m_x;
			this->m_y += other.m_y;
			this->m_z += other.m_z;
			return *this;
		}

		Vector4 Add(const Vector4 &other) const { return Vector4(this->m_x + other.m_x, this->m_y + other.m_y, this->m_z + other.m_z); }
		Vector4 &Add(const Vector4 &other)
		{
			this->m_x += other.m_x;
			this->m_y += other.m_y;
			this->m_z += other.m_z;
			return *this;
		}

		Vector4 operator-(const Vector4 &other) const { return Vector4(this->m_x - other.m_x, this->m_y - other.m_y, this->m_z - other.m_z); }
		Vector4 &operator-=(const Vector4 &other)
		{
			this->m_x -= other.m_x;
			this->m_y -= other.m_y;
			this->m_z -= other.m_z;
			return *this;
		}
		Vector4 Sub(const Vector4 &other) const { return Vector4(this->m_x - other.m_x, this->m_y - other.m_y, this->m_z - other.m_z); }
		Vector4 &Sub(const Vector4 &other)
		{
			this->m_x -= other.m_x;
			this->m_y -= other.m_y;
			this->m_z -= other.m_z;
			return *this;
		}

		Vector4 operator*(const T n) const { return Vector4(this->m_x*n, this->m_y*n, this->m_z*n); }
		Vector4 &operator*=(const T n)
		{
			this->m_x *= n;
			this->m_y *= n;
			this->m_z *= n;
			return *this;
		}
		Vector4 Scale(const T n) const { return Vector4(this->m_x*n, this->m_y*n, this->m_z*n); }
		Vector4 &Scale(const T n)
		{
			this->m_x *= n;
			this->m_y *= n;
			this->m_z *= n;
			return *this;
		}

		Vector4 operator/(const T n) const { return Vector4(this->m_x / n, this->m_y / n, this->m_z / n); }
		Vector4 &operator/=(const T n)
		{
			this->m_x /= n;
			this->m_y /= n;
			this->m_z /= n;
			return *this;
		}
		Vector4 Division(T n) const { return Vector4(this->m_x / n, this->m_y / n, this->m_z / n); }
		Vector4 &Division(T n)
		{
			this->m_x /= n;
			this->m_y /= n;
			this->m_z /= n;
			return *this;
		}

		Vector4 &operator++(int)
		{
			T length = this->GetMagnitude();
			T mult = (length + 1) / length;
			this->m_x *= mult;
			this->m_y *= mult;
			this->m_z *= mult;
			return *this;
		}
		Vector4 &operator--(int)
		{
			T length = this->GetMagnitude();
			T mult = (length - 1) / length;
			this->m_x *= mult;
			this->m_y *= mult;
			this->m_z *= mult;
			return *this;
		}

		Vector3<T> ToVec3() const
		{
			Vector4<T> homogenized = this->Homogenize();
			return Vector3<T>(homogenized.m_x, homogenized.m_y, homogenized.m_z);
		}

		T& operator[](const int coord)
		{
			if (coord == 0)
				return this->m_x;
			if (coord == 1)
				return this->m_y;
			if (coord == 2)
				return this->m_z;
			if (coord == 3)
				return this->m_w;
			return this->m_x;
		}

		const T& operator[](const int coord) const
		{
			if (coord == 0)
				return this->m_x;
			if (coord == 1)
				return this->m_y;
			if (coord == 2)
				return this->m_z;
			if (coord == 3)
				return this->m_w;
			return this->m_x;
		}

		// Comparisons

		bool operator==(const Vector4 &other) const
		{
			return this->GetMagnitude() == other.GetMagnitude();
		}

		bool operator!=(const Vector4 &other) const
		{
			return this->GetMagnitude() != other.GetMagnitude();
		}

		bool operator<(const Vector4 &other) const
		{
			return this->GetMagnitude() < other.GetMagnitude();
		}

		bool operator<=(const Vector4 &other) const
		{
			return this->GetMagnitude() <= other.GetMagnitude();
		}

		bool operator>(const Vector4 &other) const
		{
			return this->GetMagnitude() > other.GetMagnitude();
		}

		bool operator>=(const Vector4 &other) const
		{
			return this->GetMagnitude() >= other.GetMagnitude();
		}

	};

	using Vec4 = Vector4<float>;
}
