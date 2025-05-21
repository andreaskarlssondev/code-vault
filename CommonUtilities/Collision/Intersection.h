#pragma once

#include "Vector3.h"
#include "Plane.h"
#include "Line.h"
#include "AABB3D.h"
#include "Sphere.h"
#include "Ray.h"

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

namespace CommonUtilities
{
	// If the ray does not intersect the plane aOutIntersectionPoint remains unchanged and false is returned. 
	// If the ray intersects the plane the intersection point is stored in aOutIntersectionPoint and true is returned.
	template<typename T>
	bool IntersectionPlaneRay(const Plane<T>& aPlane, const Ray<T>& aRay, Vector3<T>& aOutIntersectionPoint)
	{
		T directionDot = aRay.GetDirection().Dot(aPlane.GetNormal());
		T positionDot = aPlane.GetNormal().Dot(aPlane.GetPoint() - aRay.GetOrigin());

		// Ray is parallel to the plane
		if (directionDot == T())
		{
			// On same plane
			if (positionDot == T())
			{
				aOutIntersectionPoint = aRay.GetOrigin();
				return true;
			}

			return false;
		}

		T t = positionDot / directionDot;

		if (t < T())
		{
			return false;
		}

		aOutIntersectionPoint = aRay.GetOrigin() + t * aRay.GetDirection();
		return true;
	}

	// If the ray intersects the AABB, true is returned, if not, false is returned.
	// Any ray starting on the inside is considered to intersect the AABB
	template<typename T>
	bool IntersectionAABBRay(const AABB3D<T>& aAABB, const Ray<T>& aRay, Vector3<T>& aOutIntersectionPoint)
	{
		T tMin = T(), tMax = INFINITY;

		T t1 = (aAABB.GetMin().x - aRay.GetOrigin().x) * aRay.GetDirectionInverse().x;
		T t2 = (aAABB.GetMax().x - aRay.GetOrigin().x) * aRay.GetDirectionInverse().x;

		tMin = min(max(t1, tMin), max(t2, tMin));
		tMax = max(min(t1, tMax), min(t2, tMax));

		t1 = (aAABB.GetMin().y - aRay.GetOrigin().y) * aRay.GetDirectionInverse().y;
		t2 = (aAABB.GetMax().y - aRay.GetOrigin().y) * aRay.GetDirectionInverse().y;

		tMin = min(max(t1, tMin), max(t2, tMin));
		tMax = max(min(t1, tMax), min(t2, tMax));

		t1 = (aAABB.GetMin().z - aRay.GetOrigin().z) * aRay.GetDirectionInverse().z;
		t2 = (aAABB.GetMax().z - aRay.GetOrigin().z) * aRay.GetDirectionInverse().z;

		tMin = min(max(t1, tMin), max(t2, tMin));
		tMax = max(min(t1, tMax), min(t2, tMax));

		if (tMax < 0 || tMin > tMax)
		{
			return false;
		}

		aOutIntersectionPoint = aRay.GetOrigin() + tMin * aRay.GetDirection();
		return true;
	}

	// If the ray intersects the sphere, true is returned, if not, false is returned.
	// Any ray starting on the inside is considered to intersect the sphere
	template<typename T>
	bool IntersectionSphereRay(const Sphere<T>& aSphere, const Ray<T>& aRay, Vector3<T>& aOutIntersectionPoint)
	{
		Vector3<T> distanceToCenter = aSphere.GetCenter() - aRay.GetOrigin();
		T t = distanceToCenter.Dot(aRay.GetDirection());

		if (t < T())
		{
			return false;
		}

		T shortSideSqr = distanceToCenter.LengthSqr() - t * t;
		if (shortSideSqr > aSphere.GetRadius() * aSphere.GetRadius())
		{
			return false;
		}

		T distanceBetweenCircleEdgeAndT = std::sqrt(aSphere.GetRadius() * aSphere.GetRadius() - shortSideSqr);
		T distanceToIntersectionPoint = t - distanceBetweenCircleEdgeAndT;
		aOutIntersectionPoint = aRay.GetOrigin() + distanceToIntersectionPoint * aRay.GetDirection();
		return true;

		/*
			if (t < 0 || !aSphere.IsInside(aRay.GetOrigin() + t * aRay.GetDirection()))
			{
				return false;
			}

			T distanceBetweenCircleEdgeAndT = std::sqrt(aSphere.GetRadius() * aSphere.GetRadius() - (distanceToCenter.LengthSqr()) + t * t);
			T distanceToIntersectionPoint = t - distanceBetweenCircleEdgeAndT;
			aOutIntersectionPoint = aRay.GetOrigin() + distanceToIntersectionPoint * aRay.GetDirection();

			return true;
			*/
	}
}