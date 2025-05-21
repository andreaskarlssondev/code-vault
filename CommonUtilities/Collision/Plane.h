#pragma once

#include "Vector3.h"

namespace CommonUtilities
{
	template <class T>
	class Plane
	{
		public:
			// Default constructor.
			Plane();

			// Constructor taking three points where the normal is (aPoint1 - aPoint0) x (aPoint2 - aPoint0).
			Plane(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2);

			// Constructor taking a point and a normal.
			Plane(const Vector3<T>& aPoint0, const Vector3<T>& aNormal);

			// Init the plane with three points, the same as the constructor above.
			void InitWith3Points(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2);

			// Init the plane with a point and a normal, the same as the constructor above.
			void InitWithPointAndNormal(const Vector3<T>& aPoint, const Vector3<T>& aNormal);

			// Returns whether a point is inside the plane: it is inside when the point is on the plane or on the side the normal is pointing away from.
			bool IsInside(const Vector3<T>& aPosition) const;

			// Returns the normal of the plane.
			const Vector3<T>& GetNormal() const;

			// Return a point on the plane.
			const Vector3<T>& GetPoint() const;

		private:
			Vector3<T> myPoint;
			Vector3<T> myNormal;

	};

	template<class T>
	inline Plane<T>::Plane():
		myPoint(),
		myNormal()
	{}

	template<class T>
	inline Plane<T>::Plane(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2):
		myPoint(aPoint0)
	{
		const Vector3<T> v1 = aPoint1 - aPoint0;
		const Vector3<T> v2 = aPoint2 - aPoint0;

		myNormal = v1.Cross(v2).GetNormalized();
	}

	template<class T>
	inline Plane<T>::Plane(const Vector3<T>& aPoint0, const Vector3<T>& aNormal):
		myPoint(aPoint0),
		myNormal(aNormal.GetNormalized())
	{}

	template<class T>
	inline void Plane<T>::InitWith3Points(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2)
	{
		myPoint = aPoint0;
		const Vector3<T> v1 = aPoint1 - myPoint;
		const Vector3<T> v2 = aPoint2 - myPoint;

		myNormal = v1.Cross(v2).GetNormalized();
	}

	template<class T>
	inline void Plane<T>::InitWithPointAndNormal(const Vector3<T>& aPoint, const Vector3<T>& aNormal)
	{
		myPoint = aPoint;
		myNormal = aNormal;
	}

	template<class T>
	inline bool Plane<T>::IsInside(const Vector3<T>& aPosition) const
	{
		return myNormal.Dot(aPosition - myPoint) < T(0.000001);
	}

	template<class T>
	inline const Vector3<T>& Plane<T>::GetNormal() const
	{
		return myNormal;
	}

	template<class T>
	inline const Vector3<T>& Plane<T>::GetPoint() const
	{
		return myPoint;
	}

}