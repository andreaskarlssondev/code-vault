#include "CameraAnimator.h"

#include "CameraController.h"

#include "../PostMaster/Postmaster.h"

#include <graphics/Camera.h>
#include <engine.h>
#include <texture/TextureManager.h>
#include <settings/settings.h>
#include <graphics/GraphicsEngine.h>

#include <assert.h>


void CameraAnimator::Init(Camera& aCameraToAnimate)
{
	myCamera = &aCameraToAnimate;
	myFinished = true;

	Engine& engine = Engine::GetInstance();

	Vector2ui intResolution = engine.GetRenderSize();

	mySpriteSharedData.myTexture = engine.GetTextureManager().GetTexture(L"Sprites/black_2x2.png");

	mySpriteInstanceData.mySize = { (float)intResolution.x, (float)intResolution.y };
	mySpriteInstanceData.myColor = Color(0.f, 0.f, 0.f, 1.f);
}

CameraAnimator* CameraAnimator::AddFrame(const CameraAnimationFrame& aFrame)
{
	myFrames.push_back(aFrame);
	return this;
}

CameraAnimator* CameraAnimator::AddFrames(const std::vector<CameraAnimationFrame>& someFrames)
{
	myFrames.insert(myFrames.end(), someFrames.begin(), someFrames.end());
	return this;
}

void CameraAnimator::Update(const float& aDeltaTime)
{
	if (!myShouldPlay)
	{
		return;
	}
	assert(myFrames.size() > 0 && L"No animation to play");

	// Handle start delay
	if (myCurrentAnimationDelay < CurrentFrame().delay)
	{
		myCurrentAnimationDelay += aDeltaTime;
		return;
	}

	// Handle animation
	myCurrentAnimationDuration += aDeltaTime;
	if (myCurrentAnimationDuration < CurrentFrame().duration)
	{

		// Get procentage of duration
		float animationDuration = myCurrentAnimationDuration / CurrentFrame().duration;
		float scale = CurrentFrame().easingFn(animationDuration);

		myCamera->SetPosition(Vector3f::Lerp(myFrameStartPosition, CurrentFrame().endPosition, scale));

		// Handle fading
		if (CurrentFrame().screenFade.easingFn)
		{
			// TODO: Implement fadding
		}

		return;
	}

	myCamera->SetPosition(CurrentFrame().endPosition);
	myFrameStartPosition = CurrentFrame().endPosition;

	// Handle end delay;
	if (myCurrentAnimationEndDelay < CurrentFrame().endDelay)
	{
		myCurrentAnimationEndDelay += aDeltaTime;
		return;
	}

	// Step to new animation frame
	if (myCurrentAnimatinIndex >= myFrames.size() - 1)
	{
		Exit(false);
		return;
	}

	++myCurrentAnimatinIndex;
	ResetCounters();
}

void CameraAnimator::Play()
{
	myCurrentAnimatinIndex = 0;
	ResetCounters();
	myShouldPlay = true;
	myFinished = false;
	myStartPosition = myCamera->GetTransform().GetPosition();
	myFrameStartPosition = myStartPosition;
}


void CameraAnimator::Restart()
{
	myCamera->SetPosition(myStartPosition);

	Play();
}

void CameraAnimator::Exit(bool endAnimation)
{
	if (endAnimation)
	{
		myCamera->SetPosition(myFrames.back().endPosition);
	}

	myShouldPlay = false;
	myFinished = true;
	Clear();

	GameMessenger::GetInstance().NotifyObservers("AnimationDone");
}


void CameraAnimator::ResetCounters()
{
	myCurrentAnimationDuration = 0.f;
	myCurrentAnimationDelay = 0.f;
	myCurrentAnimationEndDelay = 0.f;
}
