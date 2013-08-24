#include "Easing.h"

N2F::Iw3D::Easing::Easing()
{
	return;
}

// Move in a straight line at a continuous speed
float N2F::Iw3D::Easing::Linear(int64 currentTime, int64 startTime, float origin, float destination, int64 duration)
{
	return roundf((destination - origin) * (((float)currentTime - (float)startTime) / (float)duration) + origin);
}

// Move in a curve at the beginning of the transition.
float N2F::Iw3D::Easing::QuadraticEaseIn(int64 currentTime, int64 startTime, float origin, float destination, int64 duration)
{
	float newTime = ((float)currentTime - (float)startTime) / (float)duration;

	return roundf((destination - origin) * newTime * newTime + origin);
}

// Move in a curve towards the end of the transition.
float N2F::Iw3D::Easing::QuadraticEaseOut(int64 currentTime, int64 startTime, float origin, float destination, int64 duration)
{
	float newTime = ((float)currentTime - (float)startTime) / (float)duration;

	return roundf((-(destination - origin)) * newTime * (newTime-2) + origin);
}

// Move in a curve going one direction for the first half, and then switch directions for the second half of the transition.
float N2F::Iw3D::Easing::QuadraticEaseInOut(int64 currentTime, int64 startTime, float origin, float destination, int64 duration)
{
	float newTime = ((float)currentTime - (float)startTime) / ((float)duration / 2);

	if(newTime < 1)
	{
		return roundf((destination - origin) / 2 * newTime * newTime + origin);
	}

	newTime--;

	return roundf((-(destination - origin) / 2) * (newTime * (newTime-2) - 1) + origin);
}

N2F::Iw3D::Easing::~Easing()
{
	return;
}
