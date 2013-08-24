#include "Helpers.h"

CIwFVec2 N2F::Iw3D::Vector3To2(CIwFVec3 vector)
{
	return CIwFVec2(vector.x, vector.y);
}

CIwFVec3 N2F::Iw3D::Vector2To3(CIwFVec2 vector)
{
	return CIwFVec3(vector.x, vector.y, 0.0f);
}

CIwFVec3 N2F::Iw3D::Vector2To3(CIwFVec2 vector, float zaxis)
{
	return CIwFVec3(vector.x, vector.y, zaxis);
}
