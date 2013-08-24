#ifndef _N2F_SCREEN_H_
#define _N2F_SCREEN_H_

#include "core.h"
#include "Element.h"

namespace N2F
{
	namespace Iw3D
	{
		class Screen
		{
		private:
			typedef std::map<const char *, Element *> ElementList;
			typedef std::pair<const char *, Element *> ElementListItem;
			typedef std::map<const char *, Element *>::iterator ElementListIter;

		public:
			enum State
			{
				Null,
				Loaded,
				Suspended,
				Visible,
				Active
			};

			Screen(const ScaleFactor &scaleFactor);
			~Screen();

			// Method to create (and return) an element object
			template<class C> C *createElement(const char *key)
			{
				for (ElementListIter it = this->elements.begin(); it != this->elements.end(); ++it)
				{
					if ((*it).first == key)
					{
						return(static_cast<C *>((*it).second));
					}
				}

				this->elements.insert(ElementListItem(key, new C(this->scaleFactor)));

				return(static_cast<C *>(this->elements[key]));
			}

			// Method to return an element object
			template<class C> C *getElement(const char *key)
			{
				for (ElementListIter it = this->elements.begin(); it != this->elements.end(); ++it)
				{
					if ((*it).first == key)
					{
						return(static_cast<C *>((*it).second));
					}
				}

				return(NULL);
			}

			// Method to delete an element object
			template<class C> void deleteElement(const char *key)
			{
				for (ElementListIter it = this->elements.begin(); it != this->elements.end(); ++it)
				{
					if ((*it).first == key)
					{
						delete (*it).second;
						this->elements.erase(it);

						break;
					}
				}

				return;
			}

			void init();
			void reset();
			void kill();

			virtual void OnInit() = 0;
			virtual void OnReset() = 0;
			virtual void OnKill() = 0;

			void beforeActive();
			void beforeSuspended();
			void beforeBackground();

			virtual void OnBeforeActive() = 0;
			virtual void OnBeforeSuspended() = 0;
			virtual void OnBeforeBackground() = 0;

			void draw(int64 delta);
			void font(int64 delta);
			void update(int64 delta);

			virtual void OnDraw(int64 delta) = 0;
			virtual void OnFont(int64 delta) = 0;
			virtual void OnUpdate(int64 delta) = 0;

			const CIwFVec2 getPosition() const;
			void setPosition(CIwFVec2 pos);

			const State getState() const;
			void setState(State state);

		protected:
			ScaleFactor scaleFactor;
			ElementList elements;
			CIwFVec2 position;
			State state;
		};
	}
};

#endif
