#pragma once

#include "CameraAnimationFrame.h"

#include <sprite/sprite.h>
#include <math/Vector3.h>

#include <vector>


class Camera;
class SpriteDrawer;
class CameraController;

class CameraAnimator
{

public:
	CameraAnimator() = default;
	~CameraAnimator() = default;

	void Init(Camera& aCameraToAnimate);

	void SetCameraController(CameraController* aCameraController) { myCameraController = aCameraController; }

	CameraAnimator* AddFrame(const CameraAnimationFrame& aFrame);
	CameraAnimator* AddFrames(const std::vector<CameraAnimationFrame>& someFrames);

	void Update(const float& aDeltaTime);

	void Play();
	void Pause() { myShouldPlay = false; }
	void UnPause() { myShouldPlay = true; }
	void Restart();

	// Exit the animation (true = goes directly to end, false = does nothing)
	void Exit(bool endAnimation = false);

	void Clear() { myFrames.clear(); }

	bool IsFinished() const { return myFinished; }

private:
	CameraAnimationFrame& CurrentFrame() { return myFrames[myCurrentAnimatinIndex]; }
	void ResetCounters();

private:
	bool myShouldPlay;
	bool myFinished;

	Vector3f myStartPosition;
	Vector3f myFrameStartPosition;

	int myCurrentAnimatinIndex;
	float myCurrentAnimationDuration;
	float myCurrentAnimationDelay;
	float myCurrentAnimationEndDelay;

	std::vector<CameraAnimationFrame> myFrames;

	// Image for screen fading
	SpriteSharedData mySpriteSharedData;
	Sprite2DInstanceData mySpriteInstanceData;

	Camera* myCamera;
	CameraController* myCameraController;
};

