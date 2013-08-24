#include "Trajectory.h"

// Returns the position that the object should current be at, based on the time that is supplied.
CIwFVec3 N2F::Iw3D::Trajectory::Update(int64 currentTime)
{
	this->runTime = currentTime - this->startTime;
	this->runTime /= 1000;

	this->position.x += (float)(this->velocity * cos(this->angle * PI/180));
	this->position.y -= (float)(this->velocity * sin(this->angle * PI/180) - this->gravity * this->runTime);

	return this->position;
}

// Tells whether the animation has finished.
bool N2F::Iw3D::Trajectory::IsFinished()
{
	return false;
}
