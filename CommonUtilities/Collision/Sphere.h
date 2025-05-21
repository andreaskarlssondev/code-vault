#pragma once

#include "Vector3.h"

namespace CommonUtilities
{

	template <class T>
	class Sphere
	{

		public:
			// Default constructor: there is no sphere, the radius is zero and the position is the zero vector.
			Sphere();

			// Copy constructor.
			Sphere(const Sphere<T>& aSphere);

			// Constructor that takes the center position and radius of the sphere.
			Sphere(const Vector3<T>& aCenter, const T aRadius);

			// Init the sphere with a center and a radius, the same as the constructor above.
			void InitWithCenterAndRadius(const Vector3<T>& aCenter, const T aRadius);

			// Returns whether a point is inside the sphere: it is inside when the point is on the
			// sphere surface or inside of the sphere.
			bool IsInside(const Vector3<T>& aPosition) const;

			const Vector3<T>& GetCenter() const;
			const T GetRadius() const;

		private:
			Vector3<T> myCenter;
			T myRadius;

	};

	template<class T>
	inline Sphere<T>::Sphere():
		myCenter(),
		myRadius()
	{}

	template<class T>
	inline Sphere<T>::Sphere(const Sphere<T>& aSphere):
		myCenter(aSphere.myCenter),
		myRadius(aSphere.myRadius)
	{}

	template<class T>
	inline Sphere<T>::Sphere(const Vector3<T>& aCenter, const T aRadius):
		myCenter(aCenter),
		myRadius(aRadius)
	{}

	template<class T>
	inline void Sphere<T>::InitWithCenterAndRadius(const Vector3<T>& aCenter, const T aRadius)
	{
		myCenter = aCenter;
		myRadius = aRadius;
	}

	template<class T>
	inline bool Sphere<T>::IsInside(const Vector3<T>& aPosition) const
	{
		const Vector3<T> distance = aPosition - myCenter;
		return distance.LengthSqr() <= myRadius * myRadius;
	}

	template<class T>
	inline const Vector3<T>& Sphere<T>::GetCenter() const
	{
		return myCenter;
	}

	template<class T>
	inline const T Sphere<T>::GetRadius() const
	{
		return myRadius;
	}
}