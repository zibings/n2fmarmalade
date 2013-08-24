#ifndef _N2F_S3EUTILS_H_
#define _N2F_S3EUTILS_H_

#include "s3e.h"
#include "Iw2D.h"
#include "IwGx.h"
#include "IwGxFont.h"
#include "IwGxPrint.h"
#include "IwTexture.h"
#include "IwMaterial.h"
#include "IwGeom.h"
#include "IwDebug.h"
#include "s3eDialog.h"
#include "s3ePointer.h"
#include "s3eKeyboard.h"
#include <cstdarg>
#include "s3eWebView.h"

namespace N2F
{
	namespace Iw3D
	{
		// Allocate (and configure) a vertex stream for rendering a 'fullscreen' backdrop that
		// does not obscure the Ideaworks logo & softkeys
		CIwFVec2* AllocClientScreenRectangle();

		// Function to check if common exit "keys" have been sent
		bool s3eExitKeyHit();
		// Function to draw a sprite centered at the specified position
		void s3eDrawSpriteCentered(CIw2DImage* img, CIwFVec2 pos, int size);
		// Function to draw a sprite centered at the specified position
		void s3eDrawSpriteCentered(CIw2DImage* img, CIwFVec2 pos, CIwFVec2 size);
		// Function to draw a sprite rotated and scaled at the specified position
		void s3eDrawSpriteRotated(CIw2DImage *img, CIwFVec2 pos, float angle = 0, float scale = 1.0);
		// Function to draw a sprite with a basic image transform at the specified position
		void s3eDrawSpriteTransformed(CIw2DImage *img, CIwFVec2 pos, CIwFVec2 size, CIw2DImageTransform transform);
		// Function to aim a web view at the formatted URL and then fire
		void s3eFireWebView(s3eWebView* panel, const char* format_url, ...);
		// Function to clear the currently active surface (quickly)
		void s3eClearCurrentSurface();
		// Function to create a texture from an image
		CIwTexture* s3eCreateTextureSetImage(const char* img);
		// Function to assign an image for the texture from a file
		void s3eCreateTextureSetImage(CIwTexture& texture, const char* img);
		// Function to create a rect from position and size vectors
		CIwRect32 s3eCreatePositionRect(CIwFVec2 pos, CIwFVec2 size);
		// Function to draw font with IwGxFont library
		void s3eDrawGxFont(const char* str, CIwGxFont* font, uint32 colour, CIwRect32 rect, IwGxFontAlignHor hAlign, IwGxFontAlignVer vAlign, float scale = 1.0f);
		// Function to show a message box
		void s3eShowDialog(const char* title, const char* msg, const char* button);
	}
}

#endif
