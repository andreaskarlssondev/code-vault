#pragma once

#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Matrix4x4.h>
#include <Ray.h>

using Matrix4x4f = CommonUtilities::Matrix4x4<float>;
using Vector2f = CommonUtilities::Vector2<float>;
using Vector3f = CommonUtilities::Vector3<float>;
using Vector4f = CommonUtilities::Vector4<float>;

enum eProjectionType
{
	Ortographi,
	Perspective
};

class Camera
{

	public:
		Camera();
		~Camera() = default;

		void SetPerspectiveProjection(const Vector2f& aResolution, const float& aFieldOfView, const float aNearPlane, float aFarPlane);

		inline const Matrix4x4f& GetProjection() const { return myProjection; }
		inline const Matrix4x4f& GetTransform() const { return myTransform; }

		inline const float& GetNearPlane() const { return myNearPlane; }
		inline const float& GetFarPlane() const { return myFarPlane; }

		inline eProjectionType GetProjectionType() const { return myProjectionType; }

		void PointAt(Vector3f& aTarget, Vector3f& up);

		void SetTransform(const Matrix4x4f& aTransform) { myTransform = aTransform; };

		const Vector4f ToPostProjectionSpace(Vector4f aPoint);

		Ray ScreenPointToRay(float aX, float aY) const;

	private:
		Matrix4x4f myTransform;  // camera-to-world
		Matrix4x4f myProjection;
		Matrix4x4f myInversProjection;

		float myNearPlane;
		float myFarPlane;

		eProjectionType myProjectionType;
};
