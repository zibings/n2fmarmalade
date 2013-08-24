#ifndef _ANIMATION_TWEEN_H
#define _ANIMATION_TWEEN_H

#include "cmath"
#include "s3e.h"
#include "Iw2d.h"
#include "IwGx.h"
#include "s3eTimer.h"
#include "Helpers.h"
#include "AnimationBase.h"
#include "Trajectory.h"
#include "Easing.h"

namespace N2F
{
	namespace Iw3D
	{
		// This helper is responsible for updating and tracking the tweening (animation) of an object.
		class Tween : AnimationBase
		{
		public:
			// Default constructor
			Tween() { }

			// This helper is responsible for updating and tracking the tweening (animation) of an object.
			Tween(int64 _currentTime, int64 _duration, CIwFVec3 _origin, CIwFVec3 _destination) : AnimationBase(_origin, _destination)
			{
				this->started = _currentTime;
				this->duration = _duration;
				this->distance = this->GetDistanceToDestination();

				this->easeXAxis = &Easing::Linear;
				this->easeYAxis = &Easing::Linear;
				this->easeZAxis = &Easing::Linear;
			}
	
			// Set the easing method to control the x-axis.
			void SetEaseXAxis(float (&easeXAxys)(int64, int64, float, float, int64));
	
			// Set the easing method to control the y-axis.
			void SetEaseYAxis(float (&easeYAxis)(int64, int64, float, float, int64));
	
			// Set the easing method to control the z-axis.
			void SetEaseZAxis(float (&easeZAxis)(int64, int64, float, float, int64));
	
			// Set the easing methods of the x,y, and z axis'.
			void SetEasing(float (&easeXAxis)(int64, int64, float, float, int64), float (&easeYAxis)(int64, int64, float, float, int64), float (&easeZAxis)(int64, int64, float, float, int64));
	
			// Returns the position that the object should current be at, based on the time that is supplied.
			CIwFVec3 Update(int64 runTime);
	
			// Returns the position that the object started at.
			CIwFVec3 GetOrigin();
	
			// Returns the position that the object is heading towards.
			CIwFVec3 GetDestination();
	
			// Returns the distance that the object needs to travel.
			CIwFVec3 GetDistance();

			// Returns the speed at which the element is moving.
			CIwFVec3 GetVelocity();
	
			// Returns the time that the tween started.
			int64 GetStartTime();
	
			// Returns the length of time that the tween will run.
			int64 GetDuration();
	
			// Tells whether the tween has finished animating.
			bool IsFinished(int64 delta);

		protected:

			// Method to ease the x-axis of the object tween.
			float (*easeXAxis)(int64, int64, float, float, int64);

			// Method to ease the y-axis of the object tween.
			float (*easeYAxis)(int64, int64, float, float, int64);

			// Method to ease the y-axis of the object tween.
			float (*easeZAxis)(int64, int64, float, float, int64);

			// The time that the tween started.
			int64 started;

			// The amount of time that the object will be traveling.
			int64 duration;

			// The distance to travel (which is considered the "Change in Value", from origin to destination)
			CIwFVec3 distance;
	
			// Subtracts the destination position from the origin position.
			CIwFVec3 GetDistanceToDestination();
		};
	}
}

#endif