#ifndef _N2F_CORE_H_
#define _N2F_CORE_H_

#include "IwGx.h"
#include "IwGxFont.h"

#include "s3ePointer.h"
#include "s3eKeyboard.h"

#include <map>
#include <vector>

namespace N2F
{
	namespace Iw3D
	{
		struct ScaleFactor
		{
			CIwFVec2 offset;
			float scale;
		};
	}
}

#endif
