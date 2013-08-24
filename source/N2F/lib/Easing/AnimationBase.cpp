#include "AnimationBase.h"

N2F::Iw3D::AnimationBase::AnimationBase(CIwFVec3 origin)
{
	this->origin = origin;
	this->position = origin;
	this->destination = CIwFVec3(0.0f, 0.0f, 0.0f);
}
N2F::Iw3D::AnimationBase::AnimationBase(CIwFVec3 origin, CIwFVec3 destination)
{
	this->origin = origin;
	this->position = origin;
	this->destination = destination;
}

CIwFVec3 N2F::Iw3D::AnimationBase::Update(int64 RunTime)
{
	return CIwFVec3(0.0f, 0.0f, 0.0f);
}
