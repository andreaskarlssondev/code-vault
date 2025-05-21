#include "Camera.h"
#include <cmath>

#define PI 3.14159265358979f

namespace Assignment
{
    Camera::Camera() :
        myNearPlane(0.f),
        myFarPlane(1.f)
    {
    }

    void Camera::SetPerspectiveProjection(const Vector2f& aResolution, const float& aFieldOfView, const float aNearPlane, float aFarPlane)
    {
        myFarPlane = aFarPlane;
        myNearPlane = aNearPlane;

        float fieldOfViewRad = aFieldOfView * (PI / 180.f);

        float angle = 1.f / std::tanf(fieldOfViewRad * 0.5f);

        float aspectRatio = aResolution.x / aResolution.y;
        aspectRatio;

        myProjection(1, 1) = angle;
        myProjection(2, 2) = aspectRatio * angle;
        myProjection(3, 3) = myFarPlane / (myFarPlane - myNearPlane);
        myProjection(3, 4) = 1.f;
        myProjection(4, 3) = (-myNearPlane * myFarPlane) / (myFarPlane - myNearPlane);
        myProjection(4, 4) = 0.f;

        myInversProjection = myProjection.GetInverse();
        myProjectionType = eProjectionType::Perspective;
    }

    void Camera::PointAt(Vector3f& aTarget, Vector3f& aUpDirection)
    {
        // Get a forward vector 
        Vector3f forward = aTarget - Vector3f{ myTransform(4,1), myTransform(4,2), myTransform(4,3) };
        forward.Normalize();

        // our up vector will change as the forward vector will give the y some elevation (pitching in the x axis)
        // new up is the difference
        Vector3f up = aUpDirection - (forward * aUpDirection.Dot(forward));
        up.Normalize();

        // Use cross product to get the new right vector
        Vector3f right = up.Cross(forward);

        // Add values to the transform matrix
        myTransform(1, 1) = right.x;
        myTransform(1, 2) = right.y;
        myTransform(1, 3) = right.z;
        myTransform(2, 1) = up.x;
        myTransform(2, 2) = up.y;
        myTransform(2, 3) = up.z;
        myTransform(3, 1) = forward.x;
        myTransform(3, 2) = forward.y;
        myTransform(3, 3) = forward.z;
    }

    const Vector4f Camera::ToPostProjectionSpace(Vector4f aPoint)
    {
        aPoint = aPoint * myTransform.GetFastInverse(myTransform); // world-to-camera 
        aPoint = aPoint * myProjection;

        return aPoint;
    }

    Ray Camera::ScreenPointToRay(float aX, float aY) const
    {
        Vector4f ndc =
        {
            ((aX / myResolution.x) - 0.5f) * 2.0f,
            -((1.0f - (aY / myResolution.y)) - 0.5f) * 2.0f,
            1.0f, // Z
            1.0f // W
        };

        Vector4f rayViewSpace = ndc * myInversProjection;
        rayViewSpace /= rayViewSpace.w;

        Vector4f rayWorldSpace = rayViewSpace * myTransform;

        Vector3f rayOrigin = myTransform.GetPosition();

        return Ray{
            rayOrigin,
            (Vector3f{rayWorldSpace.x, rayWorldSpace.y, rayWorldSpace.z} - rayOrigin).GetNormalized()
        };
    }
}
