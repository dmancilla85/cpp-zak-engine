#ifndef _Font_H_
#define _Font_H_

#include <string.h>
#include "Entity2D.h"
#include "renderer.h"
#include "TextureManager.h"



namespace zak {

/**
*	Clase que muestra texto en pantalla
*	Ejemplo de uso:
\code
bool TestGame::OnInit() {

	if (!_font.LoadIni("data/font.ini"))
		return false;

	_font.SetPos(-380, 250);

	return true;
}

void TestGame::OnFrame() {

	_font.SetText("FPS: %d", _fpsMeter.GetFps());

	_font.Update(_fpsMeter.GetDT());
}

void TestGame::OnDraw() {
	_font.Draw();
}
\endcode
*
*	Archivo font.ini:
\code
[FONT]
Filename="data/font.tga"
TextureFilter=0 	; 0-None 1-Point 2-Linear 3-Triangle 4-Box
TextureMipFilter=0	; 0-None 1-Point 2-Linear 3-Triangle 4-Box
MinFilter=0 		; 0-None 1-Point 2-Linear 3-Triangle 4-Box
MagFilter=0			; 0-None 1-Point 2-Linear 3-Triangle 4-Box
Set=0
ColorKey=0
SideCount=16
Width=32
Height=32
PosX=0
PosY=0
Persist=false
Spacing=16
\endcode
*
*	El archivo font.tga puede ser generado utilizando la herramienta Bitmap Font Builder.
*
*	@Author: Juan Pablo "McKrackeN" Bettini
*/
class ZAKENGINE_API Font : public Entity2D {
	private:
		TexVertex	*_pVertex;
		Texture  	*_pTexture;
		char		*_pszText;
		int			_iTextLenght;
		int			_fontWidth;
		int			_fontHeight;
		int			_fontSideCount;
		float		_spacing;
		int			_set;

		DWORD		_magFilter;
		DWORD		_minFilter;

		bool Load(const char *pszImageFilename, unsigned int uiColorKey, bool persist = false);

	public:

		/**
		*	Permite almacenar el set de fuentes a mostrar del bitmap.
		*	@param set Set de fuentes a mostrar. Debrá ser 0 <= set <= 1.
		*/
		void ShowSet(int set) { if (set <= 1 && set >= 0) _set = set; }

		/**
		*	Almacena el texto formateado a mostrar (estilo printf).
		*	Nota: si se modifica las dimensiones utilizando el método SetDim, 
		*	éste método debe invocarse inmediatamente después.
		*	@param pszText texto formateado a mostrar
		*/
		void SetText(char *psz_Text,...); 

		/**
		*	Dibuja el texto en pantalla
		*/
		void Draw();

		/**
		*	Carga un texto desde un archivo de inicialización .ini
		*	@param pszFilename nombre del archivo a cargar
		*	@return Verdadero si se cargó correctamente y falso en caso contrario
		*/
		bool LoadIni(const char *pszFilename);

		/**
		 *  Permite liberar la memoria RAM y de video de la textura cargada
		 *	@return retorna true si todo salió bien y false en caso contrario
		 */
		bool Unload();

	/**
	*	Constructor
	*/
	Font();

	/**
	*	Destructor
	*/
	~Font();
};

}

#endif // _Font_H_
