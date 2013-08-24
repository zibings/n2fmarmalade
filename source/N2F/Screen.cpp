#include "Screen.h"

N2F::Iw3D::Screen::Screen(const ScaleFactor &scaleFactor)
{
	this->scaleFactor = scaleFactor;

	return;
}

N2F::Iw3D::Screen::~Screen()
{
	return;
}

void N2F::Iw3D::Screen::init()
{
	this->OnInit();

	return;
}

void N2F::Iw3D::Screen::reset()
{
	this->OnReset();

	return;
}

void N2F::Iw3D::Screen::kill()
{
	if (this->elements.size() > 0)
	{
		for (ElementListIter it = this->elements.begin(); it != this->elements.end(); ++it)
		{
			(*it).second->kill();
			delete (*it).second;
		}

		this->elements.clear();
	}

	this->OnKill();

	return;
}

void N2F::Iw3D::Screen::beforeActive()
{
	this->OnBeforeActive();

	return;
}

void N2F::Iw3D::Screen::beforeSuspended()
{
	this->OnBeforeSuspended();

	return;
}

void N2F::Iw3D::Screen::beforeBackground()
{
	this->OnBeforeBackground();

	return;
}

void N2F::Iw3D::Screen::draw(int64 delta)
{
	this->OnDraw(delta);

	return;
}

void N2F::Iw3D::Screen::font(int64 delta)
{
	this->OnFont(delta);

	return;
}

void N2F::Iw3D::Screen::update(int64 delta)
{
	this->OnUpdate(delta);

	return;
}

const CIwFVec2 N2F::Iw3D::Screen::getPosition() const
{
	return(this->position);
}

void N2F::Iw3D::Screen::setPosition(CIwFVec2 pos)
{
	this->position = pos;

	return;
}

const N2F::Iw3D::Screen::State N2F::Iw3D::Screen::getState() const
{
	return(this->state);
}

void N2F::Iw3D::Screen::setState(N2F::Iw3D::Screen::State state)
{
	this->state = state;

	return;
}
