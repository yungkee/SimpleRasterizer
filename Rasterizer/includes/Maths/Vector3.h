#pragma once

#include <string>
#include <SDL_stdinc.h>

namespace Maths
{
	template<typename T>
	class Vector3
	{
		public:
			T m_x;
			T m_y;
			T m_z;

	public:
		static float ToDegree(const double &angle)
		{
			return angle * 180.0 / M_PI;
		}
		static float ToRad(const double &angle)
		{
			return static_cast<float>(angle * M_PI / 180.0f);
		}

		Vector3(T out_x, T out_y, T out_z = 0.0f) : m_x{ out_x }, m_y{ out_y }, m_z{ out_z } {}
		Vector3(const Vector3 &other) : m_x{other.m_x} , m_y{other.m_y}, m_z{other.m_z}
		{
		}

		Vector3& operator=(const Vector3& other)
		{
			this->m_x = other.m_x;
			this->m_y = other.m_y;
			this->m_z = other.m_z;
			return *this;
		}

		~Vector3() = default;

		Vector3 Normalize() const
		{
			float mag = this->GetMagnitude();
			if (mag != 0 && mag != 1)
			{
				return this->Divison(mag);
			}
			return *this;
		}

		void Normalize()
		{
			float mag = this->GetMagnitude();
			if (mag != 0 && mag != 1)
			{
				this->Divison(mag);
			}
		}

		T MagSq() const { return (this->m_x * this->m_x) + (this->m_y * this->m_y) + (this->m_z * this->m_z); }

		T GetMagnitude() const { return sqrt(MagSq()); }
		T DotProduct(const Vector3 &other) const { return (this->m_x * other.m_x) + (this->m_y * other.m_y) + (this->m_z * other.m_z); }
		Vector3 CrossProduct(const Vector3 &other) const
		{
			float crossX = (this->m_y * other.m_z) - (other.y * this->m_z);
			float crossY = (this->m_z * other.m_x) - (other.z * this->m_x);
			float crossZ = (this->m_x * other.m_y) - (other.x * this->m_y);

			return Vector3(crossX, crossY, crossZ);
		}		
		float CrossProduct2D(const Vector3 &other) const
		{
			return ((this->m_x * other.m_y) - (this->m_y - other.m_x));
		}

		float AngleBetween(const Vector3 &other) const
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

		T operator,(const Vector3 &other) const { return this->DotProduct(other); }

		Vector3 operator+(const Vector3 &other) const { return Vector3(this->m_x + other.m_x, this->m_y + other.m_y, this->m_z + other.m_z); }
		Vector3 &operator+=(const Vector3 &other)
		{
			this->m_x += other.m_x;
			this->m_y += other.m_y;
			this->m_z += other.m_z;
			return *this;
		}

		Vector3 Add(const Vector3 &other) const { return Vector3(this->m_x + other.m_x, this->m_y + other.m_y, this->m_z + other.m_z); }
		Vector3 &Add(const Vector3 &other)
		{
			this->m_x += other.m_x;
			this->m_y += other.m_y;
			this->m_z += other.m_z;
			return *this;
		}

		Vector3 operator-(const Vector3 &other) const { return Vector3(this->m_x - other.m_x, this->m_y - other.m_y, this->m_z - other.m_z); }
		Vector3 &operator-=(const Vector3 &other)
		{
			this->m_x -= other.m_x;
			this->m_y -= other.m_y;
			this->m_z -= other.m_z;
			return *this;
		}
		Vector3 Sub(const Vector3 &other) const { return Vector3(this->m_x - other.m_x, this->m_y - other.m_y, this->m_z - other.m_z); }
		Vector3 &Sub(const Vector3 &other)
		{
			this->m_x -= other.m_x;
			this->m_y -= other.m_y;
			this->m_z -= other.m_z;
			return *this;
		}

		Vector3 operator*(const T n) const { return Vector3(this->m_x*n, this->m_y*n, this->m_z*n); }
		Vector3 &operator*=(const T n)
		{
			this->m_x *= n;
			this->m_y *= n;
			this->m_z *= n;
			return *this;
		}
		Vector3 Scale(const T n) const { return Vector3(this->m_x*n, this->m_y*n, this->m_z*n); }
		Vector3 &Scale(const T n)
		{
			this->m_x *= n;
			this->m_y *= n;
			this->m_z *= n;
			return *this;
		}

		Vector3 operator/(const T n) const { return Vector3(this->m_x / n, this->m_y / n, this->m_z / n); }
		Vector3 &operator/=(const T n)
		{
			this->m_x /= n;
			this->m_y /= n;
			this->m_z /= n;
			return *this;
		}
		Vector3 Divison(T n) const { return Vector3(this->m_x / n, this->m_y / n, this->m_z / n); }
		Vector3 &Division(T n)
		{
			this->m_x /= n;
			this->m_y /= n;
			this->m_z /= n;
			return *this;
		}

		Vector3 &operator++(int)
		{
			T length = this->GetMagnitude();
			T mult = (length + 1) / length;
			this->m_x *= mult;
			this->m_y *= mult;
			this->m_z *= mult;
			return *this;
		}
		Vector3 &operator--(int)
		{
			T length = this->GetMagnitude();
			T mult = (length - 1) / length;
			this->m_x *= mult;
			this->m_y *= mult;
			this->m_z *= mult;
			return *this;
		}

	
	};

	using Vec3 = Vector3<float>;
	using Vector3f =  Vector3<float>;
	using Vector3d = Vector3<double>;
	using Vector3i = Vector3<int>;
}
