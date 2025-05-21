#pragma once

namespace CommonUtilities
{

	template <class T>
	class Vector4
	{
	public:
		T x;
		T y;
		T z;
		T w;

		// Create a null-vector
		Vector4<T>();

		// Create a vector (aX, aY, aZ, aW)
		Vector4<T>(const T& aX, const T& aY, const T& aZ, const T& aW);

		Vector4<T>(const Vector4<T>& aVector) = default;

		Vector4<T>& operator=(const Vector4<T>& aVector4) = default;

		~Vector4<T>() = default;

		// Predefined vectors
		static const Vector4<T> zero;
		static const Vector4<T> one;

		// Returns the squred length of the vector
		T LengthSqr() const;

		// Returns the length of the vector
		T Length() const;

		// Returns a normalized copy of the vector
		Vector4<T> GetNormalized() const;

		// Nomalizes the vector
		void Normalize();

		// Returns the dot product of this and aVector
		T Dot(const Vector4<T>& aVector) const;
	};

	// Returns the vector sum of aVector0 and aVector1
	template <class T> Vector4<T> operator+(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		return
		{
			aVector0.x + aVector1.x,
			aVector0.y + aVector1.y,
			aVector0.z + aVector1.z,
			aVector0.w + aVector1.w,
		};
	}

	// Returns the vector difference of aVector0 and aVector1
	template <class T> Vector4<T> operator-(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		return
		{
			aVector0.x - aVector1.x,
			aVector0.y - aVector1.y,
			aVector0.z - aVector1.z,
			aVector0.w - aVector1.w,
		};
	}

	// Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector4<T> operator*(const Vector4<T>& aVector, const T& aScalar)
	{
		return
		{
			aVector.x * aScalar,
			aVector.y * aScalar,
			aVector.z * aScalar,
			aVector.w * aScalar,
		};
	}

	// Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector4<T> operator*(const T& aScalar, const Vector4<T>& aVector)
	{
		return
		{
			aVector.x * aScalar,
			aVector.y * aScalar,
			aVector.z * aScalar,
			aVector.w * aScalar,
		};
	}

	// Returns the vector aVector divided by the scalar aScalar (equivalent to aVector multiplied by 1/aScalar)
	template <class T> Vector4<T> operator/(const Vector4<T>& aVector, const T& aScalar)
	{
		return
		{
			aVector.x / aScalar,
			aVector.y / aScalar,
			aVector.z / aScalar,
			aVector.w / aScalar,
		};
	}


	// Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T> void operator+=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
		aVector0.z += aVector1.z;
		aVector0.w += aVector1.w;
	}

	// Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T> void operator-=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
		aVector0.z -= aVector1.z;
		aVector0.w -= aVector1.w;
	}

	// Equivalent to setting aVector to (aVector * aScalar)
	template <class T> void operator*=(Vector4<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
		aVector.z *= aScalar;
		aVector.w *= aScalar;
	}

	// Equivalent to setting aVector to (aVector / aScalar)
	template <class T> void operator/=(Vector4<T>& aVector, const T& aScalar)
	{
		aVector.x /= aScalar;
		aVector.y /= aScalar;
		aVector.z /= aScalar;
		aVector.w /= aScalar;
	}

	// Comparing two vectors (aVector == aVector)
	template <class T> bool operator==(const Vector4<T>& aVector, const Vector4<T>& aSecondVector)
	{
		return aVector.x == aSecondVector.x
			&& aVector.y == aSecondVector.y
			&& aVector.z == aSecondVector.z
			&& aVector.w == aSecondVector.w;
	}


	// Comparing two vectors (aVector != aVector)
	template <class T> bool operator!=(const Vector4<T>& aVector, const Vector4<T>& aSecondVector)
	{
		return !(aVector == aSecondVector);
	}

	template<class T>
	inline Vector4<T>::Vector4(): x(), y(), z(), w()
	{}

	template<class T>
	inline Vector4<T>::Vector4(const T& aX, const T& aY, const T& aZ, const T& aW) : x(aX), y(aY), z(aZ), w(aW)
	{}

	template<class T>
	const Vector4<T> Vector4<T>::zero;

	template<class T>
	const Vector4<T> Vector4<T>::one = { T(1), T(1), T(1), T(1) };


	template<class T>
	inline T Vector4<T>::LengthSqr() const
	{
		return x * x + y * y + z * z + w * w;
	}

	template<class T>
	inline T Vector4<T>::Length() const
	{
		return (T)std::sqrt(LengthSqr());
	}

	template<class T>
	inline void Vector4<T>::Normalize()
	{
		if (x == 0 && y == 0 && z == 0 && w == 0)
		{
			return;
		}

		*this /= Length();
	}

	template<class T>
	inline Vector4<T> Vector4<T>::GetNormalized() const
	{
		if (x == 0 && y == 0 && z == 0 && w == 0)
		{
			return {};
		}

		return *this / Length();
	}

	template<class T>
	inline T Vector4<T>::Dot(const Vector4<T>& aVector) const
	{
		return this->x * aVector.x + this->y * aVector.y + this->z * aVector.z + this->w * aVector.w;
	}


}