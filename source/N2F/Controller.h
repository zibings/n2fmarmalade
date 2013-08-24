#ifndef _N2F_CONTROLLER_H_
#define _N2F_CONTROLLER_H_

#include "core.h"
#include "Screen.h"
#include "Element.h"
#include "render\Iw2D.h"

namespace N2F
{
	namespace Iw3D
	{
		class Controller
		{
		private:
			typedef std::map<const char *, Screen *> ScreenList;
			typedef std::pair<const char *, Screen *> ScreenListItem;
			typedef std::map<const char *, Screen *>::iterator ScreenListIter;
			typedef std::vector<Screen *> ScreenStack;
			typedef std::vector<Screen *>::iterator ScreenStackIter;

		public:
			Controller();
			~Controller();

			// Method to create (and return) a screen object
			template<class C> C *createScreen(const char *key)
			{
				for (ScreenListIter it = this->screens.begin(); it != this->screens.end(); ++it)
				{
					if ((*it).first == key)
					{
						return(static_cast<C *>((*it).second));
					}
				}

				this->screens.insert(ScreenListItem(key, new C(this->scaleFactor)));

				return(static_cast<C *>(this->screens[key]));
			}

			// Method to return a screen object
			template<class C> C *getScreen(const char *key)
			{
				for (ScreenListIter it = this->screens.begin(); it != this->screens.end(); ++it)
				{
					if ((*it).first == key)
					{
						return(static_cast<C *>((*it).second));
					}
				}

				return(NULL);
			}

			// Method to delete a screen object
			template<class C> void deleteScreen(const char *key)
			{
				for (ScreenListIter it = this->screens.begin(); it != this->screens.end(); ++it)
				{
					if ((*it).first == key)
					{
						delete (*it).second;
						this->screens.erase(it);

						break;
					}
				}

				return;
			}

			Screen *getScreen(const char *key);

			const ScaleFactor getScaleFactor() const;
			void setScaleFactor(ScaleFactor scaleFactor);

			void init();
			void update(int64 delta);
			void render(int64 delta);
			void kill();

			virtual void OnInit() = 0;
			virtual void OnUpdate(int64 delta) = 0;
			virtual void OnRender(int64 delta) = 0;
			virtual void OnPostRender(int64 delta) = 0;
			virtual void OnKill() = 0;

		protected:
			ScreenStack visibleScreens;
			ScreenListIter topScreen;
			ScreenList screens;

			ScaleFactor scaleFactor;
		};
	}
}

#endif
