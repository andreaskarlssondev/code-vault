#pragma once

namespace CommonUtilities
{
	
	template <class T>
	class Vector2
	{
		public:
			T x;
			T y;
			
			// Create a null-vector
			Vector2<T>();	

			// Create a vector (aX, aY)
			Vector2<T>(const T& aX, const T& aY);

			Vector2<T>(const Vector2<T>& aVector) = default;

			Vector2<T>& operator=(const Vector2<T>& aVector2) = default;
			
			~Vector2<T>() = default;

			// Returns the squred length of the vector
			T LengthSqr() const;
			
			// Returns the length of the vector
			T Length() const;

			// Returns a normalized copy of the vector
			Vector2<T> GetNormalized() const;

			// Nomalizes the vector
			void Normalize();

			// Returns the dot product of this and aVector
			T Dot(const Vector2<T>& aVector) const;
	};

	// Returns the vector sum of aVector0 and aVector1
	template <class T> Vector2<T> operator+(const Vector2<T>& aVector0, const Vector2<T>& aVector1) 
	{
		return 
		{
			aVector0.x + aVector1.x,
			aVector0.y + aVector1.y,
		};
	}

	// Returns the vector difference of aVector0 and aVector1
	template <class T> Vector2<T> operator-(const Vector2<T>& aVector0, const Vector2<T>& aVector1) 
	{
		return 
		{
			aVector0.x - aVector1.x,
			aVector0.y - aVector1.y,
		};
	}

	// Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector2<T> operator*(const Vector2<T>& aVector, const T& aScalar) 
	{
		return 
		{
			aVector.x * aScalar,
			aVector.y * aScalar,
		};
	}

	// Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector2<T> operator*(const T& aScalar, const Vector2<T>& aVector)
	{
		return
		{
			aVector.x * aScalar,
			aVector.y * aScalar,
		};
	}


	// Returns the vector aVector divided by the scalar aScalar (equivalent to aVector multiplied by 1/aScalar)
	template <class T> Vector2<T> operator/(const Vector2<T>& aVector, const T& aScalar) 
	{
		return
		{
			aVector.x / aScalar,
			aVector.y / aScalar,
		};
	}

	// Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T> void operator+=(Vector2<T>& aVector0, const Vector2<T>& aVector1) 
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
	}

	// Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T> void operator-=(Vector2<T>& aVector0, const Vector2<T>& aVector1) 
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
	}

	// Equivalent to setting aVector to (aVector * aScalar)
	template <class T> void operator*=(Vector2<T>& aVector, const T& aScalar) 
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
	}

	// Equivalent to setting aVector to (aVector / aScalar)
	template <class T> void operator/=(Vector2<T>& aVector, const T& aScalar) 
	{
		aVector.x /= aScalar;
		aVector.y /= aScalar;
	}

	template<class T>
	inline Vector2<T>::Vector2(): x(), y()
	{}

	template<class T>
	inline Vector2<T>::Vector2(const T& aX, const T& aY): x(aX), y(aY)
	{}

	template<class T>
	inline T Vector2<T>::LengthSqr() const
	{
		return x * x + y * y;
	}

	template<class T>
	inline T Vector2<T>::Length() const
	{
		return std::sqrt(LengthSqr());
	}

	template<class T>
	inline void Vector2<T>::Normalize()
	{
		if (x == 0 && y == 0)
		{
			return;
		}
		
		*this /= Length();
	}

	template<class T>
	inline Vector2<T> Vector2<T>::GetNormalized() const
	{
		if (x == 0 && y == 0)
		{
			return {};
		}

		return *this / Length();
	}

	template<class T>
	inline T Vector2<T>::Dot(const Vector2<T>& aVector) const
	{
		return this->x * aVector.x + this->y * aVector.y;
	}

}