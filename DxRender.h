#ifndef _DX_RENDER_H_
#define _DX_RENDER_H_

#include <ddraw.h>
#include <math.h>


class DXRender
{
public:
	DXRender():m_bInitiated(FALSE){};
	int					Init					(int width, int height);
	int					Exit					(unsigned char bReleaseDD);
	IDirectDrawSurface*	GetFrontBuffer			(void);
	IDirectDrawSurface*	GetBackBuffer			(void);
	int					NewBitmap				(IDirectDrawSurface **ppBitmap, unsigned int nWidth, unsigned int nHeight);
	int					NewBitmapSystem			(IDirectDrawSurface **ppBitmap, unsigned int nWidth, unsigned int nHeight);
	int					FreeBitmap				(IDirectDrawSurface **ppBitmap);
	int					GetWidth				(IDirectDrawSurface *pBitmap);
	int					GetHeight				(IDirectDrawSurface *pBitmap);
	int					PutBitmap_i				(IDirectDrawSurface *pDestBitmap, int nDx, int nDy, int nDw, int nDh, int nMode, 
												 IDirectDrawSurface *pSrcBitmap, int nSx, int nSy, int nSw, int nSh);
	IDirectDrawSurface* BeginScene				(void);
	void				BeginDraw				(void);
	void				EndDraw					(void);
	void				EndScene				(IDirectDrawSurface** p_bit);
	int					FillBitmap				(IDirectDrawSurface *pBitmap, long lColor);
	int					FillRect_i				(IDirectDrawSurface *pBitmap, int left, int top, int right, int bottom, long lColor);
	void				DrawRect_i				(IDirectDrawSurface *pBitmap, int left, int top, int right, int bottom, long lColor);
	unsigned short		GetPixel_i				(IDirectDrawSurface *pBitmap, unsigned int nX, unsigned int nY);
	void				PutPixel_i				(IDirectDrawSurface *pBitmap, unsigned int nX, unsigned int nY, long lColor);
	unsigned short*		LockSurface				(IDirectDrawSurface *pBitmap);
	unsigned short*		LockBB					(void);
	void				PutPixel_locked		(unsigned long *pImage, unsigned int nX, unsigned int nY, long lColor);
	void				PutPixel32_locked		(unsigned long *pImage, unsigned int nX, unsigned int nY, long lColor);
	void				PutPixel16_locked		(unsigned short *pImage, unsigned int nX, unsigned int nY, long lColor);
	void				DrawLine_locked			(unsigned long *pImage, long X0, long Y0, long X1, long Y1, long width, long lColor);
	void				DrawLineOctant0			(unsigned long *pImage, long lColor, unsigned int X0, unsigned int Y0, unsigned int DeltaX, unsigned int DeltaY, int XDirection);
	void				DrawLineOctant1			(unsigned long *pImage, long lColor, unsigned int X0, unsigned int Y0, unsigned int DeltaX, unsigned int DeltaY, int XDirection);
	void				DrawCircle_locked		(unsigned long *pImage, int p_ptX, int p_ptY, int radius, long lColor);
	void				UnLockSurface			(IDirectDrawSurface *pBitmap, unsigned short *pImage);
	void				UnLockBB				(unsigned short *pImage);
	void				DrawLine				(IDirectDrawSurface *pBitmap, float fX1, float fY1, float fX2, float fY2, long lColor);
	unsigned char		BitmapDoClipping		(int& nDx, int& nDy, int& nDw, int& nDh, int& nSx, int& nSy, int& nSw, int& nSh);
	IDirectDrawClipper*	AttachClipper			(IDirectDrawSurface* surface, int RectCount, LPRECT ClipList);
	DWORD				DDColorMatch			(IDirectDrawSurface *pdds, COLORREF rgb);
	HRESULT				DDSetColorKey			(IDirectDrawSurface *pdds, COLORREF rgb);

	RECT				RendererRect;
	RECT				ViewRect;
	DDBLTFX				m_blitFX;
	DDSURFACEDESC		m_ddsd;
	DDSCAPS				m_ddscaps;
	DDPIXELFORMAT		m_ddpf;
	HWND				m_frameHWnd;
	IDirectDrawSurface*	m_pBB;
	IDirectDrawSurface*	m_pFB;
	IDirectDraw*		m_pDD;
	IDirectDrawClipper*	m_pClipper;
	IDirectDrawClipper*	m_pWindowClipper;
	int					m_pixelFormat;
	int					m_windowClientX0;
	int					m_windowClientY0;
	int					m_bFS;
	int					m_nWidth, m_nHeight;
	BOOL				m_bInitiated;
};
#endif // _DX_RENDER_H_