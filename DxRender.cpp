#include "DxRender.h"

int 
DXRender::Init(int width, int height)
{
	if(m_bInitiated)	return 0;
	
	m_nWidth	= width;
	m_nHeight	= height;

	memset(&m_ddsd,0,sizeof(m_ddsd));
	memset(&m_ddpf,0,sizeof(m_ddpf));
	memset(&m_blitFX, 0, sizeof(m_blitFX));
	m_ddsd.dwSize = sizeof(m_ddsd);
	m_ddpf.dwSize = sizeof(m_ddpf);
	m_blitFX.dwSize = sizeof(m_blitFX);

	DirectDrawCreate(NULL, &m_pDD, NULL);
	m_pDD->SetCooperativeLevel(m_frameHWnd, DDSCL_NORMAL);
	m_ddsd.dwFlags			= DDSD_CAPS;
	m_ddsd.ddsCaps.dwCaps	= DDSCAPS_PRIMARYSURFACE;
	m_ddsd.dwBackBufferCount= 0;
	m_pDD->CreateSurface(&m_ddsd,&m_pFB,NULL);
	m_pFB->GetPixelFormat(&m_ddpf);
	m_pixelFormat = m_ddpf.dwRGBBitCount;

	NewBitmap(&m_pBB, m_nWidth, m_nHeight);
	FillBitmap(m_pBB,0x0);

	RECT ScreenRect = {0,0,m_nWidth,m_nHeight};
	m_pClipper = AttachClipper(m_pBB,1,&ScreenRect);
	m_windowClientX0= -ScreenRect.left;
	m_windowClientY0= -ScreenRect.top;
	m_pDD->CreateClipper(0,&m_pWindowClipper,NULL);
	m_pWindowClipper->SetHWnd(0, m_frameHWnd);
	m_pFB->SetClipper(m_pWindowClipper);
	m_bInitiated= TRUE;
	return 1;
}

int 
DXRender::Exit(unsigned char bReleaseDD)
{
	if (m_pClipper)			m_pClipper->Release();
	if (m_pWindowClipper)	m_pWindowClipper->Release();
	if (m_pBB)				m_pBB->Release();
	if (m_pFB)				m_pFB->Release();
	if (m_pDD)				m_pDD->Release();
	m_bInitiated= FALSE;
	return(1);
}

IDirectDrawSurface*	
DXRender::GetFrontBuffer()
{
	return m_pFB;
}

IDirectDrawSurface*	
DXRender::GetBackBuffer()
{
	return m_pBB;
}

int 
DXRender::NewBitmap(IDirectDrawSurface **ppBitmap, unsigned int nWidth, unsigned int nHeight)
{
	HRESULT res;
	DDSURFACEDESC TempDescription;

	TempDescription.dwSize = sizeof(TempDescription);
	TempDescription.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;

	TempDescription.dwWidth = nWidth;
	TempDescription.dwHeight = nHeight;

//	TempDescription.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN|DDSCAPS_VIDEOMEMORY;

//	res= m_pDD->CreateSurface(&TempDescription,ppBitmap,NULL);
 
//	if(res == DDERR_OUTOFVIDEOMEMORY){
//		::MessageBox(0, "Hmmm .... Ran out of Video Memory ... What is this cheesy video card that you have?\n\r Anyway, I will use some system memory instead. ", 0, 0);
		TempDescription.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN|DDSCAPS_SYSTEMMEMORY;
		res= m_pDD->CreateSurface(&TempDescription,ppBitmap,NULL);
		if(res == DDERR_OUTOFMEMORY){
			::MessageBox(0, "Hmmm ... Man your in deep shit, no more video RAM, no more system RAM. Take this gun and shoot yourself!", 0, 0);
		}
//	}
	DDSetColorKey((*ppBitmap), RGB(0, 0, 0));

	return (1);
}

int 
DXRender::NewBitmapSystem(IDirectDrawSurface **ppBitmap, unsigned int nWidth, unsigned int nHeight)
{
	HRESULT res;
	DDSURFACEDESC TempDescription;

	TempDescription.dwSize = sizeof(TempDescription);
	TempDescription.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;

	TempDescription.dwWidth = nWidth;
	TempDescription.dwHeight = nHeight;

	TempDescription.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN|DDSCAPS_SYSTEMMEMORY;

	res= m_pDD->CreateSurface(&TempDescription,ppBitmap,NULL);
	if(res == DDERR_OUTOFMEMORY){
		::MessageBox(0, "Hmmm ... Man your in deep shit, no more system RAM. Take this gun and shoot yourself!", 0, 0);
	}
	DDSetColorKey((*ppBitmap), RGB(0, 0, 0));

	return (1);
}

int 
DXRender::FreeBitmap(IDirectDrawSurface **ppBitmap)
{
	(*ppBitmap)->Release();
	(*ppBitmap)= NULL;
	return (1);
}
int 
DXRender::GetWidth(IDirectDrawSurface *pBitmap)
{
	m_ddsd.dwFlags = DDSD_WIDTH;

	pBitmap->GetSurfaceDesc(&m_ddsd);
	return (int)m_ddsd.dwWidth;
}

int
DXRender::GetHeight(IDirectDrawSurface *pBitmap)
{
	m_ddsd.dwFlags = DDSD_HEIGHT;

	pBitmap->GetSurfaceDesc(&m_ddsd);
	return (int)m_ddsd.dwHeight;
}

int 
DXRender::PutBitmap_i(IDirectDrawSurface *pDestBitmap, int nDx, int nDy, int nDw, int nDh, int nMode, IDirectDrawSurface *pSrcBitmap, int nSx, int nSy, int nSw, int nSh)
{
	HRESULT res;
	RECT dstRect={nDx, nDy, nDx+nDw, nDy+nDh};
	RECT srcRect={nSx, nSy, nSx+nSw, nSy+nSh};
	if(!pDestBitmap)	pDestBitmap= m_pBB;

	if(nMode == 1)
		res= pDestBitmap->Blt(&dstRect, pSrcBitmap, &srcRect, DDBLT_WAIT, NULL);
	else
		res= pDestBitmap->Blt(&dstRect, pSrcBitmap, &srcRect, DDBLT_WAIT|DDBLT_KEYSRC, NULL);
	return 0;
}

IDirectDrawSurface* 
DXRender::BeginScene()
{
	return m_pBB;
}


void
DXRender::BeginDraw()
{
}

void 
DXRender::EndDraw()
{
}

void 
DXRender::EndScene(IDirectDrawSurface** p_bit)
{
	RECT dest;
	::GetWindowRect(m_frameHWnd, &dest);
	dest.left		+= m_windowClientX0;
	dest.top		+= m_windowClientY0;
	dest.right	= dest.left+ m_nWidth;
	dest.bottom = dest.top + m_nHeight;
	m_pFB->Blt(&dest, m_pBB, NULL, DDBLT_WAIT,NULL);
}

int 
DXRender::FillBitmap(IDirectDrawSurface *pBitmap, long lColor)
{
	if(!pBitmap) pBitmap= m_pBB;
	memset(&m_blitFX, 0x0, sizeof(m_blitFX));
	m_blitFX.dwSize = sizeof(m_blitFX);
	m_blitFX.dwFillColor = lColor;
	pBitmap->Blt(NULL,NULL,NULL,DDBLT_COLORFILL | DDBLT_WAIT,&m_blitFX);
	return (1);
}

int 
DXRender::FillRect_i(IDirectDrawSurface *pBitmap, int left, int top,	int right, int bottom, long lColor)
{
	RECT rec= {left, top, right, bottom};
	m_blitFX.dwFillColor = lColor;
	pBitmap->Blt(&rec,NULL,NULL,DDBLT_COLORFILL | DDBLT_WAIT,&m_blitFX);
	return (1);
}
unsigned short 
DXRender::GetPixel_i(IDirectDrawSurface *pBitmap, unsigned int nX, unsigned int nY)
{
	return 0;
}
void 
DXRender::PutPixel_i(IDirectDrawSurface *pBitmap, unsigned int nX, unsigned int nY, long lColor)
{
}

unsigned short*
DXRender::LockSurface(IDirectDrawSurface *pBitmap)
{
	pBitmap->Lock(NULL, &m_ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
	return (unsigned short*)m_ddsd.lpSurface;
}

unsigned short*
DXRender::LockBB()
{
	m_pBB->Lock(NULL, &m_ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
	return (unsigned short*)m_ddsd.lpSurface;
}


void 
DXRender::PutPixel_locked(unsigned long *pImage, unsigned int nX, unsigned int nY, long lColor)
{
	if(m_ddpf.dwRGBBitCount == 32){
		PutPixel32_locked(pImage, nX, nY, lColor);
	}else if(m_ddpf.dwRGBBitCount == 16){
		PutPixel16_locked((unsigned short*)pImage, nX, nY, lColor);
	}
}

void 
DXRender::PutPixel16_locked(unsigned short *pImage, unsigned int nX, unsigned int nY, long lColor)
{
	if((nX < 0)|| (nX > m_ddsd.dwWidth) || (nY < 0)|| (nY > m_ddsd.dwHeight))	return;
	
	*(pImage + (nY*(m_ddsd.lPitch>>1)) + nX)=	(unsigned long)lColor;
}

void 
DXRender::PutPixel32_locked(unsigned long *pImage, unsigned int nX, unsigned int nY, long lColor)
{
	if((nX < 0)|| (nX > m_ddsd.dwWidth) || (nY < 0)|| (nY > m_ddsd.dwHeight))	return;
	
	*(pImage + (nY*(m_ddsd.lPitch>>2)) + nX)=	(unsigned long)lColor;
}

void 
DXRender::DrawLineOctant0(unsigned long *pImage, long lColor, unsigned int X0, unsigned int Y0, unsigned int DeltaX, unsigned int DeltaY, int XDirection)
{
	int DeltaYx2;
	int DeltaYx2MinusDeltaXx2;
	int ErrorTerm;

	DeltaYx2 = DeltaY * 2;
	DeltaYx2MinusDeltaXx2 = DeltaYx2 - (int)(DeltaX * 2);
	ErrorTerm = DeltaYx2 - (int)DeltaX;

	PutPixel_locked(pImage, X0, Y0, lColor);
	while(DeltaX--){
		if(ErrorTerm >= 0){
			Y0++;
			ErrorTerm += DeltaYx2MinusDeltaXx2;
		}else{
			ErrorTerm += DeltaYx2;
		}
		X0 += XDirection;
		PutPixel_locked(pImage, X0, Y0, lColor);
	}
}

void 
DXRender::DrawLineOctant1(unsigned long *pImage, long lColor, unsigned int X0, unsigned int Y0, unsigned int DeltaX, unsigned int DeltaY, int XDirection)
{
	int DeltaXx2;
	int DeltaXx2MinusDeltaYx2;
	int ErrorTerm;

	DeltaXx2 = DeltaX * 2;
	DeltaXx2MinusDeltaYx2 = DeltaXx2 - (int)(DeltaY * 2);
	ErrorTerm = DeltaXx2 - (int) DeltaY;

	PutPixel_locked(pImage, X0, Y0, lColor);
	while(DeltaY--){
		if(ErrorTerm >= 0){
			X0 += XDirection;
			ErrorTerm += DeltaXx2MinusDeltaYx2;
		}else{
			ErrorTerm += DeltaXx2;
		}
		Y0++;
		PutPixel_locked(pImage, X0, Y0, lColor);
	}
}

void 
DXRender::DrawLine_locked(unsigned long *pImage, long X0, long Y0, long X1, long Y1, long width, long lColor)
{
   int		DeltaX
	   ,	DeltaY;
   int		Temp;

   if(Y0 > Y1){
      Temp = Y0;
      Y0 = Y1;
      Y1 = Temp;
	  
      Temp = X0;
      X0 = X1;
      X1 = Temp;
   }

   DeltaX = X1 - X0;
   DeltaY = Y1 - Y0;

   if(DeltaX > 0){
      if(DeltaX > DeltaY){
         DrawLineOctant0(pImage, lColor, X0, Y0, DeltaX, DeltaY, 1);
      }else{
         DrawLineOctant1(pImage, lColor, X0, Y0, DeltaX, DeltaY, 1);
      }
   }else{
      DeltaX= -DeltaX;
      if(DeltaX > DeltaY){
         DrawLineOctant0(pImage, lColor, X0, Y0, DeltaX, DeltaY, -1);
      } else {
         DrawLineOctant1(pImage, lColor, X0, Y0, DeltaX, DeltaY, -1);
      }
   }
}

void 
DXRender::DrawCircle_locked(unsigned long *pImage, int p_ptX, int p_ptY, int radius, long lColor)
{
	float i;
	float curX;
	float curY;

	i=255;
	while(i--){
		curX= p_ptX + cos(i)*radius;
		curY= p_ptY + sin(i)*radius;
		PutPixel_locked(pImage, curX, curY, lColor);
	}
}

void
DXRender::UnLockSurface(IDirectDrawSurface *pBitmap, unsigned short *pImage)
{
	pBitmap->Unlock(pImage);
}

void
DXRender::UnLockBB(unsigned short *pImage)
{
	m_pBB->Unlock(pImage);
}

unsigned char
DXRender::BitmapDoClipping(int& nDx, int& nDy, int& nDw, int& nDh, int& nSx, int& nSy, int& nSw, int& nSh) 
{  
	int ret= 0;                                          

//	+------			
//	|					Clip this part
//	|					
//	|					
	if (nDx+nDw <= 0)	return ret;
	if (nDy+nDh <= 0)	return ret;

	
	if (nDx < 0){
		nSx -= nDx;
		nSw += nDx;
		nDx = 0;
		ret|= 1;
	}
	if (nDy < 0){
		nSy -= nDy;
		nSh += nDy;
		nDy = 0;
		ret|= 1;
	}

//	 			|
//	 			|		Clip this part
//	 			|		
//	------+		
	if (nDx >= 240)	return 0;
	if (nDy >= 320)	return 0;

	int sortX= (nDx + nDw) - 240
		, sortY= (nDy + nDh) - 320;

	if (sortX > 0){	
		nSw -= sortX;
		nDw -= sortX;
	}
	if (sortY > 0){	
		nSh -= sortY;
		nDh -= sortY;
	}
	return 1;
}  

IDirectDrawClipper*
DXRender::AttachClipper(IDirectDrawSurface* surface, int RectCount, LPRECT ClipList)
{
	int Count;
	LPDIRECTDRAWCLIPPER Clipper;
	LPRGNDATA RegionData;

	m_pDD->CreateClipper(0,&Clipper,NULL);

	RegionData = (LPRGNDATA)malloc(sizeof(RGNDATAHEADER)+(RectCount*sizeof(RECT)));
	memcpy(RegionData->Buffer, ClipList, sizeof(RECT)*RectCount);

	RegionData->rdh.dwSize          = sizeof(RGNDATAHEADER);
	RegionData->rdh.iType           = RDH_RECTANGLES;
	RegionData->rdh.nCount          = RectCount;
	RegionData->rdh.nRgnSize        = RectCount*sizeof(RECT);

	RegionData->rdh.rcBound.left    =  64000;
	RegionData->rdh.rcBound.top     =  64000;
	RegionData->rdh.rcBound.right   = -64000;
	RegionData->rdh.rcBound.bottom  = -64000;

	for (Count = 0; Count < RectCount; Count++){
		if (ClipList[Count].left	< RegionData->rdh.rcBound.left)		RegionData->rdh.rcBound.left	= ClipList[Count].left;
		if (ClipList[Count].right	> RegionData->rdh.rcBound.right)	RegionData->rdh.rcBound.right = ClipList[Count].right;
		if (ClipList[Count].top		< RegionData->rdh.rcBound.top)		RegionData->rdh.rcBound.top		= ClipList[Count].top;
		if (ClipList[Count].bottom> RegionData->rdh.rcBound.bottom)	RegionData->rdh.rcBound.bottom= ClipList[Count].bottom;
	};

	if (FAILED(Clipper->SetClipList(RegionData,0))){
		free(RegionData);
		return(NULL);
	};

	if (FAILED(surface->SetClipper(Clipper))){
		free(RegionData);
		return(NULL);
	};

	free(RegionData);
	return Clipper;
};

DWORD 
DXRender::DDColorMatch(IDirectDrawSurface *pdds, COLORREF rgb)
{
    COLORREF rgbT;
    HDC hdc;
    DWORD dw = CLR_INVALID;
    DDSURFACEDESC ddsd;
    HRESULT hres;

    if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK){
        rgbT = GetPixel(hdc, 0, 0);             // save current pixel value
        SetPixel(hdc, 0, 0, rgb);               // set our value
        pdds->ReleaseDC(hdc);
    }
    ddsd.dwSize = sizeof(ddsd);
    while ((hres = pdds->Lock(NULL, &ddsd, 0, NULL)) == DDERR_WASSTILLDRAWING)
        ;

    if (hres == DD_OK){
        dw  = *(DWORD *)ddsd.lpSurface;                     // get DWORD
        dw &= (1 << ddsd.ddpfPixelFormat.dwRGBBitCount)-1;  // mask it to bpp
        pdds->Unlock(NULL);
    }
    if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK){
        SetPixel(hdc, 0, 0, rgbT);
        pdds->ReleaseDC(hdc);
    }

    return dw;
}

HRESULT 
DXRender::DDSetColorKey(IDirectDrawSurface *pdds, COLORREF rgb)
{
    DDCOLORKEY          ddck;

    ddck.dwColorSpaceLowValue  = DDColorMatch(pdds, rgb);
    ddck.dwColorSpaceHighValue = ddck.dwColorSpaceLowValue;
    return pdds->SetColorKey(DDCKEY_SRCBLT, &ddck);
}
