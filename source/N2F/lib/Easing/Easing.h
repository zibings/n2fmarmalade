#ifndef _ANIMATION_EASING_H
#define _ANIMATION_EASING_H

#include "cmath"
#include "s3e.h"
#include "Iw2d.h"
#include "IwGx.h"
#include "s3eTimer.h"
#include "Helpers.h"

namespace N2F
{
	namespace Iw3D
	{
		/**
		* This class contains the methods for tween easing.
		*/
		class Easing
		{
		public:
			Easing();
			static float Linear(int64 currentTime, int64 startTime, float origin, float destination, int64 duration);
			static float QuadraticEaseIn(int64 currentTime, int64 startTime, float origin, float destination, int64 duration);
			static float QuadraticEaseOut(int64 currentTime, int64 startTime, float origin, float destination, int64 duration);
			static float QuadraticEaseInOut(int64 currentTime, int64 startTime, float origin, float destination, int64 duration);
			~Easing();
		};
	}
}

#endif
