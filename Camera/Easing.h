#pragma once

#include <cmath>
#include <functional>

#define M_PI 3.14159f
#define M_PI_HALF 1.57079f

enum class eEasing
{
	Linear,
	Ease,
	EaseIn,
	EaseOut,
	EaseInOut,

	Sin,
    Quadratic,
	Cubic,
	Exponential,
	Elastic,
	Bounce,
};

using EasingFunctionType = std::function<float(float)>;

// Usable easing functions
class Easing
{
	public:

        static EasingFunctionType GetFrom(eEasing aEasing)
        {
            switch (aEasing)
            {
                case eEasing::Linear:
                {
                    return Linear;
                }
                case eEasing::Ease:
                {
                    return Ease;
                }
                case eEasing::EaseIn:
                {
                    return EaseIn;
                }
                case eEasing::EaseOut:
                {
                    return EaseOut;
                }
                case eEasing::EaseInOut:
                {
                    return EaseInOut;
                }
                case eEasing::Sin:
                {
                    return Sin;
                }
                case eEasing::Quadratic:
                {
                    return Quadratic;
                }
                case eEasing::Cubic:
                {
                    return Cubic;
                }
                case eEasing::Exponential:
                {
                    return Exponential;
                }
                case eEasing::Elastic:
                {
                    return Elastic;
                }
                case eEasing::Bounce:
                {
                    return Bounce;
                }
            }

            return Linear;
        }

        // Linear easing function
        static float Linear(float t)
        {
            return t;
        }

        // Standard easing function
        static float Ease(float t)
        {
            return t < 0.5f ? 2.f * t * t : -1.f + (4.f - 2.f * t) * t;
        }

        // EaseIn easing function
        static float EaseIn(float t)
        {
            return t * t;
        }

        // EaseOut easing function
        static float EaseOut(float t)
        {
            return 1.f - (1.f - t) * (1.f - t);
        }

        // EaseInOut easing function
        static float EaseInOut(float t)
        {
            return t < 0.5f ? 2.f * t * t : -1.f + (4.f - 2.f * t) * t;
        }

        // Sine easing function
        static float Sin(float t)
        {
            return sin(t * M_PI / 2.f);
        }

        // Quadratic easing function
        static float Quadratic(float t)
        {
            return t * t;
        }

        // Cubic easing function
        static float Cubic(float t)
        {
            return t * t * t;
        }

        // Exponential easing function
        static float Exponential(float t)
        {
            return t == 0.f ? 0.f : static_cast<float>(pow(2, 10.f * (t - 1.f)));
        }

        // Elastic easing function
        static float Elastic(float t)
        {
            return sin(13.f * M_PI_HALF * t) * static_cast<float>(pow(2, 10.f * (t - 1.f)));
        }

        // Bounce easing function
        static float Bounce(float t)
        {
            if (t < (1.f / 2.75))
                return 7.5625f * t * t;
            else if (t < (2.f / 2.75f))
                return 7.5625f * (t -= (1.5f / 2.75f)) * t + 0.75f;
            else if (t < (2.5f / 2.75f))
                return 7.5625f * (t -= (2.25f / 2.75f)) * t + 0.9375f;
            else
                return 7.5625f * (t -= (2.625f / 2.75f)) * t + 0.984375f;
        }

};


