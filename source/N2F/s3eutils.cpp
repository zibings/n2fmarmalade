#include "s3eutils.h"

CIwFVec2* N2F::Iw3D::AllocClientScreenRectangle()
{
	CIwFVec2* pCoords = IW_GX_ALLOC(CIwFVec2, 4);

	pCoords[0].x = 0;
	pCoords[0].y = 0;
	pCoords[1].x = 0;
	pCoords[1].y = (int16)IwGxGetScreenHeight();
	pCoords[2].x = (int16)IwGxGetScreenWidth();
	pCoords[2].y = 0;
	pCoords[3].x = pCoords[2].x;
	pCoords[3].y = pCoords[1].y;

	return(pCoords);
}

bool N2F::Iw3D::s3eExitKeyHit()
{
	if (s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN || s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN)
	{
		return(true);
	}

	return(false);
}

void N2F::Iw3D::s3eDrawSpriteCentered(CIw2DImage* img, CIwFVec2 pos, int size)
{
	Iw2DDrawImage(img, CIwFVec2((float)pos.x, (float)pos.y) - CIwFVec2((float)(size/2), (float)(size/2)), CIwFVec2((float)size, (float)size));

	return;
}

void N2F::Iw3D::s3eDrawSpriteCentered(CIw2DImage* img, CIwFVec2 pos, CIwFVec2 size)
{
	Iw2DDrawImage(img, CIwFVec2((float)pos.x, (float)pos.y) - CIwFVec2((float)(size.x/2), (float)(size.y/2)), CIwFVec2(size.x, size.y));

	return;
}

void N2F::Iw3D::s3eDrawSpriteRotated(CIw2DImage *img, CIwFVec2 pos, float angle, float scale)
{
	CIwFMat2D m = CIwFMat2D::g_Identity;
	m.Scale(scale);
	m.SetRot(angle);
	m.ScaleRot(scale);
	m.SetTrans(CIwFVec2((float)pos.x, (float)pos.y));

	Iw2DSetTransformMatrix(m);
	Iw2DDrawImage(img, CIwFVec2((float)-(img->GetWidth() / 2), (float)-(img->GetHeight() / 2)));
	Iw2DSetTransformMatrix(CIwFMat2D::g_Identity);

	return;
}

void N2F::Iw3D::s3eDrawSpriteTransformed(CIw2DImage *img, CIwFVec2 pos, CIwFVec2 size, CIw2DImageTransform transform)
{
	Iw2DSetImageTransform(transform);
	Iw2DDrawImage(img, pos, size);
	Iw2DSetImageTransform(IW_2D_IMAGE_TRANSFORM_NONE);

	return;
}

void N2F::Iw3D::s3eFireWebView(s3eWebView* panel, const char* format_url, ...)
{
	s3eDeviceYield(0);

	va_list args;
	const int buflen = 2048;
	char fullurl[buflen];

	va_start(args, format_url);
	vsnprintf(fullurl, buflen, format_url, args);
	va_end(args);

	s3eWebViewNavigate(panel, fullurl);

	return;
}

void N2F::Iw3D::s3eClearCurrentSurface()
{
	uint16* screen = (uint16*)s3eSurfacePtr();
	int32 width = s3eSurfaceGetInt(S3E_SURFACE_WIDTH);
	int32 height = s3eSurfaceGetInt(S3E_SURFACE_HEIGHT);
	int32 pitch = s3eSurfaceGetInt(S3E_SURFACE_PITCH);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			screen[y * pitch/2 + x] = 0;
		}
	}

	return;
}

CIwTexture* N2F::Iw3D::s3eCreateTextureSetImage(const char* img)
{
	CIwTexture* ret = new CIwTexture;
	ret->LoadFromFile(img);
	ret->Upload();

	return(ret);
}

void N2F::Iw3D::s3eCreateTextureSetImage(CIwTexture& texture, const char* img)
{
	texture.LoadFromFile(img);
	texture.Upload();

	return;
}

CIwRect32 N2F::Iw3D::s3eCreatePositionRect(CIwFVec2 pos, CIwFVec2 size)
{
	return(CIwRect32((int)pos.x, (int)pos.y, (int)size.x, (int)size.y));
}

void N2F::Iw3D::s3eDrawGxFont(const char* str, CIwGxFont* font, uint32 colour, CIwRect32 rect, IwGxFontAlignHor hAlign, IwGxFontAlignVer vAlign, float scale)
{
	IwGxFontSetCol(colour);
	IwGxFontSetRect(rect);
	IwGxFontSetFont(font);
	IwGxFontSetAlignmentHor(hAlign);
	IwGxFontSetAlignmentVer(vAlign);
	IwGxFontDrawText(str);

	return;
}

void N2F::Iw3D::s3eShowDialog(const char* title, const char* msg, const char* button)
{
	s3eDeviceYield(0);

	s3eDialogAlertInfo info;
	info.m_Title = title;
	info.m_Message = msg;
	info.m_Button[0] = button;

	s3eDialogAlertBox(&info);

	return;
}
