#include "Tween.h"

// Set the easing method to control the x-axis.
void N2F::Iw3D::Tween::SetEaseXAxis(float (&easeXAxis)(int64, int64, float, float, int64))
{
	this->easeXAxis = &easeXAxis;
}

// Set the easing method to control the y-axis.
void N2F::Iw3D::Tween::SetEaseYAxis(float (&easeYAxis)(int64, int64, float, float, int64))
{
	this->easeYAxis = &easeYAxis;
}

// Set the easing method to control the z-axis.
void N2F::Iw3D::Tween::SetEaseZAxis(float (&easeZAxis)(int64, int64, float, float, int64))
{
	this->easeZAxis = &easeZAxis;
}

// Set the easing methods of the x,y, and z axis'.
void N2F::Iw3D::Tween::SetEasing(float (&easeXAxis)(int64, int64, float, float, int64), float (&easeYAxis)(int64, int64, float, float, int64), float (&easeZAxis)(int64, int64, float, float, int64))
{
	this->SetEaseXAxis(easeXAxis);
	this->SetEaseYAxis(easeYAxis);
	this->SetEaseZAxis(easeZAxis);
}

// Returns the position that the object should current be at, based on the time that is supplied.
CIwFVec3 N2F::Iw3D::Tween::Update(int64 runTime)
{
	this->position.x = this->easeXAxis(runTime, this->started, this->origin.x, this->destination.x, this->duration);
	this->position.y = this->easeYAxis(runTime, this->started, this->origin.y, this->destination.y, this->duration);
	this->position.z = this->easeZAxis(runTime, this->started, this->origin.z, this->destination.z, this->duration);

	return this->position;
}

// Returns the position that the object started at.
CIwFVec3 N2F::Iw3D::Tween::GetOrigin()
{
	return this->origin;
}

// Returns the position that the object is heading towards.
CIwFVec3 N2F::Iw3D::Tween::GetDestination()
{
	return this->destination;
}

// Returns the distance that the object needs to travel.
CIwFVec3 N2F::Iw3D::Tween::GetDistance()
{
	return this->distance;
}

// Returns the time that the tween started.
int64 N2F::Iw3D::Tween::GetStartTime()
{
	return this->started;
}

// Returns the length of time that the tween will run.
int64 N2F::Iw3D::Tween::GetDuration()
{
	return this->duration;
}

// Tells whether the tween has finished animating.
bool N2F::Iw3D::Tween::IsFinished(int64 currentTime)
{
	if ((currentTime - this->started) < this->duration)
	{
		return false;
	}

	if (this->position.x != this->destination.x && this->position.y != this->destination.y && this->position.z != this->destination.z)
	{
		return false;
	}

	return true;
}

// Subtracts the destination position from the origin position.
CIwFVec3 N2F::Iw3D::Tween::GetDistanceToDestination()
{
	return CIwFVec3(
		roundf(this->destination.x - this->origin.x),
		roundf(this->destination.y - this->origin.y),
		roundf(this->destination.z - this->origin.z)
	);
}
