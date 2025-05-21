#pragma once

#include "FollowCamera.h"
#include "CameraAnimator.h"

#include "../PostMaster/HowToReceive/GameObserver.h"

#include "Camera.h"

class CameraController: public GameObserver
{
	public:
		CameraController();
		~CameraController();

		void Init(Camera& aCamera, const float& aSpeed, const Transform& aTargetTransform, const Vector3f& aPositionOffset);
		
		void Update(const float aTimeDelta);
		void LateUpdate(const float aTimeDelta);

		const Camera* GetCamera() const { return myCamera; }
		const CameraAnimator& GetCameraAnimator() const { return myCameraAnimator; }

		void OnNotify(const std::string anEvent, const std::any& someInformation) override;

	private:
		Camera* myCamera;


		FollowCamera myFollowCamera;
		CameraAnimator myCameraAnimator;

		
};

