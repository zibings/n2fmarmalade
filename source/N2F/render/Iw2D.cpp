#include "Iw2D.h"

void N2F::Iw3D::Iw2DHelper::Init()
{
	Iw2DInit();
	IwGxInit();
	IwGxFontInit();
	IwGxLightingOn();
	IwGxSetColClear(0, 0, 0, 0xff);

	return;
}

void N2F::Iw3D::Iw2DHelper::ClearScreen()
{
	IwGxClear();

	return;
}

void N2F::Iw3D::Iw2DHelper::PreFont()
{
	Iw2DFinishDrawing();

	return;
}

void N2F::Iw3D::Iw2DHelper::EndTick()
{
	IwGxFlush();
	Iw2DSurfaceShow();
	s3eDeviceYield(0);

	return;
}

void N2F::Iw3D::Iw2DHelper::Clean()
{
	IwGxFontTerminate();
	Iw2DTerminate();
	IwGxTerminate();

	return;
}

N2F::Iw3D::Image::Image(const ScaleFactor &scaleFactor)
	: Element(scaleFactor)
{
	this->img = NULL;

	return;
}

N2F::Iw3D::Image::~Image()
{
	return;
}

const char *N2F::Iw3D::Image::getFile() const
{
	return(this->file);
}

void N2F::Iw3D::Image::setFile(const char *file)
{
	this->file = file;
	this->img = Iw2DCreateImage(file);
	this->img->GetMaterial()->SetFiltering(false);
	this->size = CIwFVec2(this->img->GetWidth(), this->img->GetHeight());

	return;
}

void N2F::Iw3D::Image::draw(int64 delta)
{
	CIwFVec2 p = CIwFVec2(
		((this->pos.x * this->scaleFactor.scale) + this->scaleFactor.offset.x),
		((this->pos.y * this->scaleFactor.scale) + this->scaleFactor.offset.y)
	);
	CIwFVec2 s = CIwFVec2(
		(this->size.x * this->scaleFactor.scale),
		(this->size.y * this->scaleFactor.scale)
	);

	Iw2DDrawImage(this->img, p, s);

	return;
}

void N2F::Iw3D::Image::draw(int64 delta, CIwFVec2 offset)
{
	CIwFVec2 p = CIwFVec2(
		((this->pos.x * this->scaleFactor.scale) + this->scaleFactor.offset.x + offset.x),
		((this->pos.y * this->scaleFactor.scale) + this->scaleFactor.offset.y + offset.y)
	);
	CIwFVec2 s = CIwFVec2(
		(this->size.x * this->scaleFactor.scale),
		(this->size.y * this->scaleFactor.scale)
	);

	Iw2DDrawImage(this->img, p, s);

	return;
}

void N2F::Iw3D::Image::draw(int64 delta, CIwFVec2 offset, float angle)
{
	CIwFVec2 p = CIwFVec2(
		((this->pos.x * this->scaleFactor.scale) + this->scaleFactor.offset.x + offset.x),
		((this->pos.y * this->scaleFactor.scale) + this->scaleFactor.offset.y + offset.y)
	);
	CIwFVec2 s = CIwFVec2(
		(this->size.x * this->scaleFactor.scale),
		(this->size.y * this->scaleFactor.scale)
	);

	CIwFMat2D m = CIwFMat2D::g_Identity;
	m.Scale(this->scaleFactor.scale);
	m.SetRot(angle);
	m.ScaleRot(this->scaleFactor.scale);
	m.SetTrans(CIwFVec2((p.x + (s.x / 2)), (p.y + (s.y / 2))));

	Iw2DSetTransformMatrix(m);
	Iw2DDrawImage(this->img, CIwFVec2(-(s.x / 2), -(s.y / 2)), s);
	Iw2DSetTransformMatrix(CIwFMat2D::g_Identity);

	return;
}

void N2F::Iw3D::Image::draw(int64 delta, CIwFVec2 offset, float angle, float scale)
{
	CIwFVec2 p = CIwFVec2(
		((this->pos.x * this->scaleFactor.scale) + this->scaleFactor.offset.x + offset.x),
		((this->pos.y * this->scaleFactor.scale) + this->scaleFactor.offset.y + offset.y)
	);
	CIwFVec2 s = CIwFVec2(
		(this->size.x * scale),
		(this->size.y * scale)
	);

	CIwFMat2D m = CIwFMat2D::g_Identity;
	m.Scale(scale);
	m.SetRot(angle);
	m.ScaleRot(scale);
	m.SetTrans(CIwFVec2((p.x + (s.x / 2)), (p.y + (s.y / 2))));

	Iw2DSetTransformMatrix(m);
	Iw2DDrawImage(this->img, CIwFVec2(-(s.x / 2), -(s.y / 2)), s);
	Iw2DSetTransformMatrix(CIwFMat2D::g_Identity);

	return;
}

void N2F::Iw3D::Image::OnKill()
{
	if (this->img != NULL)
	{
		delete this->img;
	}

	return;
}
