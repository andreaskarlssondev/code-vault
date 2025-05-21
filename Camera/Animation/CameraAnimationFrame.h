#pragma once

#include "Easing.h"

#include <math/Vector3.h>

struct ScreenFade
{
	float duration;
	EasingFunctionType easingFn;
};

struct CameraAnimationFrame
{
	Vector3<float> endPosition;
	float duration;
	float delay;
	float endDelay;
	EasingFunctionType easingFn;
	ScreenFade screenFade;

	

	// Whould be nice
	// autoplay
	// loop 
	// rotation
	// scale

};