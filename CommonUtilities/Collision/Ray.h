#pragma once

#include "Vector3.h"

namespace CommonUtilities
{
	template <class T>
	class Ray
	{
		public:
			// Default constructor: there is no ray, the origin and direction are the zero vector.
			Ray();

			// Copy constructor.
			Ray(const Ray<T>& aRay);

			// Constructor that takes two points that define the ray, the direction is 
			// aDirectionm and the origin is aOrigin.
			Ray(const Vector3<T>& aOrigin, const Vector3<T>& aDirection);

			// Init the ray with two points, the same as the constructor above.
			void InitWith2Points(const Vector3<T>& aOrigin, const Vector3<T>& aPoint);

			// Init the ray with an origin and a direction.
			void InitWithOriginAndDirection(const Vector3<T>& aOrigin, const Vector3<T>& aDirection);

			const Vector3<T>& GetOrigin() const;
			const Vector3<T>& GetDirection() const;
			const Vector3<T>& GetDirectionInverse() const;

		private:
			Vector3<T> myOrigin;
			Vector3<T> myDirection;
			Vector3<T> myDirectionInverse;

			const Vector3<T> CalculateDirectionInverse(const Vector3<T>& aDirection) const;
	};

	template<class T>
	inline Ray<T>::Ray():
		myOrigin(),
		myDirection(),
		myDirectionInverse()
	{}

	template<class T>
	inline Ray<T>::Ray(const Ray<T>& aRay):
		myOrigin(aRay.myOrigin),
		myDirection(aRay.myDirection),
		myDirectionInverse(aRay.myDirectionInverse)
	{}

	template<class T>
	inline Ray<T>::Ray(const Vector3<T>& aOrigin, const Vector3<T>& aDirection):
		myOrigin(aOrigin),
		myDirection(aDirection.GetNormalized()),
		myDirectionInverse(CalculateDirectionInverse(myDirection))
	{}

	template<class T>
	inline void Ray<T>::InitWith2Points(const Vector3<T>& aOrigin, const Vector3<T>& aPoint)
	{
		myOrigin = aOrigin;
		myDirection = aPoint - myOrigin;
		myDirection.Normalize();
		myDirectionInverse = CalculateDirectionInverse(myDirection);
	}

	template<class T>
	inline void Ray<T>::InitWithOriginAndDirection(const Vector3<T>& aOrigin, const Vector3<T>& aDirection)
	{
		myOrigin = aOrigin;
		myDirection = aDirection.GetNormalized();
		myDirectionInverse = CalculateDirectionInverse(myDirection);
	}

	template<class T>
	inline const Vector3<T>& Ray<T>::GetOrigin() const
	{
		return myOrigin;
	}

	template<class T>
	inline const Vector3<T>& Ray<T>::GetDirection() const
	{
		return myDirection;
	}

	template<class T>
	inline const Vector3<T>& Ray<T>::GetDirectionInverse() const
	{
		return myDirectionInverse;
	}

	template<class T>
	inline const Vector3<T> Ray<T>::CalculateDirectionInverse(const Vector3<T>& aDirection) const
	{
		return
		{
			T(1.0) / aDirection.x,
			T(1.0) / aDirection.y,
			T(1.0) / aDirection.z
		};
	}



}