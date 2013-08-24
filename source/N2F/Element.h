#ifndef _N2F_ELEMENT_H_
#define _N2F_ELEMENT_H_

#include "core.h"

namespace N2F
{
	namespace Iw3D
	{
		class Element
		{
		public:
			Element(const ScaleFactor &scaleFactor);
			~Element();

			const ScaleFactor getScaleFactor() const;

			const CIwFVec2 getPosition() const;
			void setPosition(CIwFVec2 pos);

			const CIwFVec2 getSize() const;
			void setSize(CIwFVec2 size);

			const bool getVisible() const;
			void setVisible(bool isVisible);

			const bool getActive() const;
			void setActive(bool isActive);

			void kill();
			virtual void draw(int64 delta) = 0;
			virtual void OnKill();
			virtual void move(float x, float y);
			virtual void move(CIwFVec2 move);

		protected:
			const ScaleFactor scaleFactor;
			bool isVisible, isActive;
			CIwFVec2 pos, size;
		};
	}
}

#endif
