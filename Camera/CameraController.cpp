#include "CameraController.h"

#include "../PostMaster/Postmaster.h"

CameraController::CameraController()
{
	Register();
}

CameraController::~CameraController()
{
	GameMessenger::GetInstance().KickObserver(this);
}

void CameraController::Init(Camera& aCamera, const float& aSpeed, const Transform& aTargetTransform, const Vector3f& aPositionOffset)
{
	myCamera = &aCamera;

	myFollowCamera.Init(aCamera, aSpeed, aTargetTransform, aPositionOffset);
	myCameraAnimator.Init(aCamera);
}

void CameraController::Update(const float aTimeDelta)
{
	if (!myCameraAnimator.IsFinished())
	{
		myCameraAnimator.Update(aTimeDelta);
	}

	myFollowCamera.Update(aTimeDelta);
}

void CameraController::LateUpdate(const float aTimeDelta)
{
	if (myCameraAnimator.IsFinished())
	{
		myFollowCamera.LateUpdate(aTimeDelta);
	}
}

void CameraController::OnNotify(const std::string anEvent, const std::any& someInformation)
{
	if (IfNotify("CameraAnimation", anEvent))
	{
		// One animation
		CameraAnimationFrame frame = std::any_cast<CameraAnimationFrame>(someInformation);
		myCameraAnimator.AddFrame(frame);
		myCameraAnimator.Play();
	}
	else if (IfNotify("CameraAnimationSequence", anEvent))
	{
		// Many animations
		std::vector<CameraAnimationFrame> frames = std::any_cast<std::vector<CameraAnimationFrame>>(someInformation);
		myCameraAnimator.AddFrames(frames);
		myCameraAnimator.Play();
	}
	if (IfNotify("CameraShake", anEvent))
	{
		myFollowCamera.TriggerShake();
	}
}
