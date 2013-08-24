#ifndef _N2F_RENDER_IW2D_H_
#define _N2F_RENDER_IW2D_H_

#include "..\core.h"
#include "..\Element.h"
#include "..\..\iw2d\h\Iw2D.h"
#include "..\Screen.h"

namespace N2F
{
	namespace Iw3D
	{
		class Iw2DHelper
		{
		public:
			static void Init();
			static void ClearScreen();
			static void PreFont();
			static void EndTick();
			static void Clean();
		};

		class Image : public Element
		{
		public:
			Image(const ScaleFactor &scaleFactor);
			~Image();

			const char *getFile() const;
			void setFile(const char *file);

			virtual void draw(int64 delta);
			virtual void draw(int64 delta, CIwFVec2 offset);
			virtual void draw(int64 delta, CIwFVec2 offset, float angle);
			virtual void draw(int64 delta, CIwFVec2 offset, float angle, float scale);

			virtual void OnKill();

		protected:
			CIw2DImage *img;
			const char *file;
		};

		class Button : public Element
		{
		public:
			enum State
			{
				Normal,
				Active,
				Disabled
			};

			Button(Screen *screen);
			~Button();

			void setNormalFile(const char *file);
			const char *getNormalFile() const;

			void setActiveFile(const char *file);
			const char *getActiveFile() const;

			void setDisabledFile(const char *file);
			const char *getDisabledFile() const;

			void draw(float delta);
			void draw(float delta, CIwFVec2 offset);
			void draw(float delta, CIwFVec2 offset, float angle);
			void draw(float delta, CIwFVec2 offset, float angle, float scale);

		protected:
			Image *imgNormal, *imgActive, *imgDisabled;
			State state;

		};

		class TextField : public Element
		{
		};
	}
}

#endif
