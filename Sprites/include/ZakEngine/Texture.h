#ifndef _Texture_H_	
#define _Texture_H_

#include <stdio.h>
#include <io.h>
#include <string.h>
#include "renderer.h"

#define ZAK_TEXTURE_FILTER_NONE			0
#define ZAK_TEXTURE_FILTER_POINT		1
#define ZAK_TEXTURE_FILTER_LINEAR		2
#define ZAK_TEXTURE_FILTER_TRIANGULAR	3
#define ZAK_TEXTURE_FILTER_BOX			4

namespace zak {

class Texture
{
	private:
		TextureInfo _info;
		char * _pszTextureFileName;
		unsigned int _uiReferenceCount;

		DWORD	_filter;
		DWORD	_mipFilter;

		int _iTextureWidth;
		int _iTextureHeight;

		DWORD _color;

		DX_LPTEXTURE _pBitmapTexture;

	public:

		bool		 Load(const char * _pszTextureFileName, unsigned int ck, bool persist, DWORD filter=2, DWORD mipFilter=2);
		bool		 Reload();
		const char  *GetName()const{return const_cast<const char*>(_pszTextureFileName);}
		void		 DecRef(){_uiReferenceCount--;}  
		void		 IncRef(){_uiReferenceCount++;}  
		int			 GetRefCount(){return _uiReferenceCount;}
		int			 GetWidth(){return _iTextureWidth;} 
		int			 GetHeight(){return _iTextureHeight;}
		DX_LPTEXTURE GetTexture(){return _pBitmapTexture;}
		void		 Release() { if (_pBitmapTexture) _pBitmapTexture->Release(); _pBitmapTexture = NULL; }
  
	Texture();
	~Texture();
};

}

#endif