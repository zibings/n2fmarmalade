#ifndef _ANIMATION_BASE_H
#define _ANIMATION_BASE_H

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
		This class contains an abstract base for animations.
		Place your animation code into the update method, which will return a CIwFVec3 with new coordinates.

		@author Chris Butcher
		@email c.butcher@hotmail.com
		@updated 9th August 2013
		*/
		class AnimationBase
		{
		public:
			// Default constructor
			AnimationBase() { }

			// Instantiates a new animation
			AnimationBase(CIwFVec3 origin);

			// Instantiates a new animation
			AnimationBase(CIwFVec3 origin, CIwFVec3 destination);

			// Updates the animation and returns the new position.
			virtual CIwFVec3 Update(int64 runTime);

		protected:

			// The position of the object when the tween was started.
			CIwFVec3 origin;
	
			// The position where the object is headed. Tween is finished when it reaches its destination.
			CIwFVec3 destination;

			// The current position of the object.
			CIwFVec3 position;
		};
	}
}

#endif
