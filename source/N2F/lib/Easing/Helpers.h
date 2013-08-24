#ifndef _N2F_LIB_EASING_HELPERS_H_
#define _N2F_LIB_EASING_HELPERS_H_

#include "IwGeom.h"

namespace N2F
{
	namespace Iw3D
	{
		CIwFVec2 Vector3To2(CIwFVec3 vector);
		CIwFVec3 Vector2To3(CIwFVec2 vector);
		CIwFVec3 Vector2To3(CIwFVec2 vector, float zaxis);
	}
}

#endif
