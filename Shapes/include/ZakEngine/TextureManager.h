#ifndef _TextureManager_H_
#define _TextureManager_H_

#include "Texture.h"

namespace zak {

class ZAKENGINE_API TextureManager {
	private:
		//EntityList	Map;
		vector<Texture*> Map;

	public:
		Texture		*Load(const char *szFilename, unsigned int uiColorKey, bool persist, DWORD filter=2, DWORD mipFilter=2);
		void		Remove(const char *szFilename);
		void		Remove(Texture *pTexture);
		void		ReleaseAll();
		void		Clear();
		int			GetCount();
		bool		Reload();

	TextureManager();
	~TextureManager();
};

extern ZAKENGINE_API TextureManager g_textureManager;

}

#endif // _TextureManager_H_