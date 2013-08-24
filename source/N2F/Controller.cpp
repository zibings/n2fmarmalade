#include "Controller.h"

N2F::Iw3D::Controller::Controller()
{
	this->topScreen = this->screens.end();

	return;
}

N2F::Iw3D::Controller::~Controller()
{
	return;
}

N2F::Iw3D::Screen *N2F::Iw3D::Controller::getScreen(const char *key)
{
	for (ScreenListIter it = this->screens.begin(); it != this->screens.end(); ++it)
	{
		if ((*it).first == key)
		{
			return((*it).second);
		}
	}

	return(NULL);
}

const N2F::Iw3D::ScaleFactor N2F::Iw3D::Controller::getScaleFactor() const
{
	return(this->scaleFactor);
}

void N2F::Iw3D::Controller::setScaleFactor(N2F::Iw3D::ScaleFactor scaleFactor)
{
	this->scaleFactor = scaleFactor;

	return;
}

void N2F::Iw3D::Controller::init()
{
	this->OnInit();

	return;
}

void N2F::Iw3D::Controller::update(int64 delta)
{
	this->OnUpdate(delta);

	if (this->visibleScreens.size() > 0)
	{
		for (ScreenStackIter it = this->visibleScreens.begin(); it != this->visibleScreens.end(); ++it)
		{
			(*it)->update(delta);
		}
	}

	if (this->topScreen != this->screens.end())
	{
		this->topScreen->second->update(delta);
	}

	return;
}

void N2F::Iw3D::Controller::render(int64 delta)
{
	this->OnRender(delta);

	if (this->visibleScreens.size() > 0)
	{
		for (ScreenStackIter it = this->visibleScreens.begin(); it != this->visibleScreens.end(); ++it)
		{
			(*it)->draw(delta);
		}
	}

	if (this->topScreen != this->screens.end())
	{
		this->topScreen->second->draw(delta);
	}

	this->OnPostRender(delta);

	return;
}

void N2F::Iw3D::Controller::kill()
{
	for (ScreenListIter it = this->screens.begin(); it != this->screens.end(); ++it)
	{
		(*it).second->kill();
		delete (*it).second;
	}

	this->visibleScreens.clear();
	this->screens.clear();

	this->OnKill();

	return;
}
