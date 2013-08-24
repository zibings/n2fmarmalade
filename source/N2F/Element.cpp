#include "Element.h"

N2F::Iw3D::Element::Element(const N2F::Iw3D::ScaleFactor &scaleFactor)
	: scaleFactor(scaleFactor)
{
	this->pos = CIwFVec2(0.0f, 0.0f);
	this->size = CIwFVec2(0.0f, 0.0f);
	this->isActive = false;
	this->isVisible = false;

	return;
}

N2F::Iw3D::Element::~Element()
{
	return;
}

const N2F::Iw3D::ScaleFactor N2F::Iw3D::Element::getScaleFactor() const
{
	return(this->scaleFactor);
}

const CIwFVec2 N2F::Iw3D::Element::getPosition() const
{
	return(this->pos);
}

void N2F::Iw3D::Element::setPosition(CIwFVec2 pos)
{
	this->pos = pos;

	return;
}

const CIwFVec2 N2F::Iw3D::Element::getSize() const
{
	return(this->size);
}

void N2F::Iw3D::Element::setSize(CIwFVec2 size)
{
	this->size = size;

	return;
}

const bool N2F::Iw3D::Element::getVisible() const
{
	return(this->isVisible);
}

void N2F::Iw3D::Element::setVisible(bool isVisible)
{
	this->isVisible = isVisible;

	return;
}

const bool N2F::Iw3D::Element::getActive() const
{
	return(this->isActive);
}

void N2F::Iw3D::Element::setActive(bool isActive)
{
	this->isActive = isActive;

	return;
}

void N2F::Iw3D::Element::kill()
{
	this->OnKill();

	return;
}

void N2F::Iw3D::Element::OnKill()
{
	return;
}

void N2F::Iw3D::Element::move(float x, float y)
{
	this->pos.x += x;
	this->pos.y += y;

	return;
}

void N2F::Iw3D::Element::move(CIwFVec2 move)
{
	this->pos += move;

	return;
}
