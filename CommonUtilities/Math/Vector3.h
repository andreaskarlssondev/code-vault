#pragma once

namespace CommonUtilities
{

	template <class T>
	class Vector3
	{
	public:
		T x;
		T y;
		T z;

		// Create a null-vector
		Vector3<T>();

		// Create a vector (aX, aY, aZ)
		Vector3<T>(const T& aX, const T& aY, const T& aZ);

		Vector3<T>(const Vector3<T>& aVector) = default;

		Vector3<T>& operator=(const Vector3<T>& aVector3) = default;

		~Vector3<T>() = default;

		// Predefined vectors
		static const Vector3<T> zero;
		static const Vector3<T> one;
		static const Vector3<T> up;
		static const Vector3<T> down;
		static const Vector3<T> left;
		static const Vector3<T> right;
		static const Vector3<T> forward;
		static const Vector3<T> back;

		// Returns the squred length of the vector
		T LengthSqr() const;

		// Returns the length of the vector
		T Length() const;

		// Returns a normalized copy of the vector
		Vector3<T> GetNormalized() const;

		// Nomalizes the vector
		void Normalize();

		// Returns the dot product of this and aVector
		T Dot(const Vector3<T>& aVector) const;

		// Returns the cross product of this and aVector
		Vector3<T> Cross(const Vector3<T>& aVector) const;


	};

	// Returns the vector sum of aVector0 and aVector1
	template <class T> Vector3<T> operator+(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		return
		{
			aVector0.x + aVector1.x,
			aVector0.y + aVector1.y,
			aVector0.z + aVector1.z,
		};
	}

	// Returns the vector difference of aVector0 and aVector1
	template <class T> Vector3<T> operator-(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		return
		{
			aVector0.x - aVector1.x,
			aVector0.y - aVector1.y,
			aVector0.z - aVector1.z,
		};
	}

	// Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector3<T> operator*(const Vector3<T>& aVector, const T& aScalar)
	{
		return
		{
			aVector.x * aScalar,
			aVector.y * aScalar,
			aVector.z * aScalar,
		};
	}


	// Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector3<T> operator*(const T& aScalar, const Vector3<T>& aVector)
	{
		return
		{
			aVector.x * aScalar,
			aVector.y * aScalar,
			aVector.z * aScalar,
		};
	}



	// Returns the vector aVector divided by the scalar aScalar (equivalent to aVector multiplied by 1/aScalar)
	template <class T> Vector3<T> operator/(const Vector3<T>& aVector, const T& aScalar)
	{
		return
		{
			aVector.x / aScalar,
			aVector.y / aScalar,
			aVector.z / aScalar,
		};
	}

	// Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T> void operator+=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
		aVector0.z += aVector1.z;
	}

	// Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T> void operator-=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
		aVector0.z -= aVector1.z;
	}

	// Equivalent to setting aVector to (aVector * aScalar)
	template <class T> void operator*=(Vector3<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
		aVector.z *= aScalar;
	}


	// Equivalent to setting aVector to (aVector / aScalar)
	template <class T> void operator/=(Vector3<T>& aVector, const T& aScalar)
	{
		aVector.x /= aScalar;
		aVector.y /= aScalar;
		aVector.z /= aScalar;
	}


	// Comparing two vectors (aVector == aVector)
	template <class T> bool operator==(const Vector3<T>& aVector, const Vector3<T>& aSecondVector)
	{
		return aVector.x == aSecondVector.x
			&& aVector.y == aSecondVector.y
			&& aVector.z == aSecondVector.z;
	}


	// Comparing two vectors (aVector != aVector)
	template <class T> bool operator!=(const Vector3<T>& aVector, const Vector3<T>& aSecondVector)
	{
		return !(aVector == aSecondVector);
	}

	template<class T>
	inline Vector3<T>::Vector3(): x(), y(), z()
	{}

	template<class T>
	inline Vector3<T>::Vector3(const T& aX, const T& aY, const T& aZ) : x(aX), y(aY), z(aZ)
	{}

	template<class T>
	const Vector3<T> Vector3<T>::zero;

	template<class T>
	const Vector3<T> Vector3<T>::one = { T(1), T(1), T(1) };

	template<class T>
	const Vector3<T> Vector3<T>::up = { T(0), T(1), T(0) };

	template<class T>
	const Vector3<T> Vector3<T>::down = { T(0), T(-1), T(0) };

	template<class T>
	const Vector3<T> Vector3<T>::left = { T(-1), T(0), T(0) };

	template<class T>
	const Vector3<T> Vector3<T>::right = { T(1), T(0), T(0) };

	template<class T>
	const Vector3<T> Vector3<T>::forward = { T(0), T(0), T(1) };

	template<class T>
	const Vector3<T> Vector3<T>::back = { T(0), T(0), T(-1) };

	template<class T>
	inline T Vector3<T>::LengthSqr() const
	{
		return x * x + y * y + z * z;
	}

	template<class T>
	inline T Vector3<T>::Length() const
	{
		return (T)std::sqrt(LengthSqr());
	}

	template<class T>
	inline void Vector3<T>::Normalize()
	{
		if (x == 0 && y == 0 && z == 0)
		{
			return;
		}

		*this /= Length();
	}

	template<class T>
	inline Vector3<T> Vector3<T>::GetNormalized() const
	{
		if (x == 0 && y == 0 && z == 0)
		{
			return {};
		}

		return *this / Length();
	}

	template<class T>
	inline T Vector3<T>::Dot(const Vector3<T>& aVector) const
	{
		return this->x * aVector.x + this->y * aVector.y + this->z * aVector.z;
	}

	template<class T>
	inline Vector3<T> Vector3<T>::Cross(const Vector3<T>& aVector) const
	{
		return
		{
			this->y * aVector.z - this->z * aVector.y,
			this->z * aVector.x - this->x * aVector.z,
			this->x * aVector.y - this->y * aVector.x,
		};
	}

}