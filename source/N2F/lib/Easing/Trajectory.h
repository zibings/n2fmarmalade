#ifndef _ANIMATION_TRAJECTORY_H
#define _ANIMATION_TRAJECTORY_H

#include "cmath"
#include "s3e.h"
#include "Iw2d.h"
#include "IwGx.h"
#include "s3eTimer.h"
#include "Helpers.h"
#include "AnimationBase.h"
#include "Easing.h"

namespace N2F
{
	namespace Iw3D
	{
		/**
		* This helper is responsible for updating and tracking the tweening (animation) of an object.
		*/
		class Trajectory : AnimationBase
		{
		public:
			Trajectory() { }

			Trajectory(int64 _startTime, CIwFVec3 _origin, float _velocity, float _angle, float _gravity) : AnimationBase(_origin)
			{
				this->startTime = _startTime;
				this->velocity  = _velocity;
				this->angle	 = _angle;
				this->gravity	 = _gravity;
			}

			// Returns the position that the object should current be at, based on the time that is supplied.
			CIwFVec3 Update(int64 currentTime);
	
			// Tells whether the animation has finished.
			bool IsFinished();

		protected:
			float angle;
			float velocity;
			float mass;
			float gravity;
			int64 runTime;
			int64 startTime;
		};
	}
}

#endif