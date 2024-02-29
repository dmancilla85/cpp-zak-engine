#ifndef _Window_H_
#define _Window_H_

#include "Defines.h"
#include "FileLog.h"
#include "Input.h"
#include "Messages.h"

namespace zak {

enum Return
{
	WindowNone,
	WindowEscape,
	WindowReturn,
};

/**
 *  Clase que maneja la ventana
 *  @author Juan Pablo "McKrackeN" Bettini
 */
class ZAKENGINE_API Window {
	private:
		HWND		hWnd;
		int			_width;
		int			_height;
		bool 		_cursorVisible;
		HCURSOR		_cursorType;
		RECT		_rect;

	public:
		RECT		_margins;
		bool		_canEnter;
		bool		_blinked;
		bool		_inserting;
		bool		_textinput;
		int			_lastElement;
		int			_maxElement;
		int			_cursor;
		int			_return;
		int			_blinking;
		string		_string;
		bool		_editing;
		basic_string <char>::iterator _iter;

		bool		ActiveWindow;
		int         Reacquire;

		ATOM RegistrarClase ();

		bool CrearVentana   (wstring *titulo,
							 int iAncho, int iAlto);

		/**
		 *  Guarda un screenshot en formato .bmp en el disco
		 *  @param szArchivo cadena de caracteres terminada en \0 con la ruta y el nombre del archivo a guardar
		 *  @param w ancho de la ventana
		 *  @param h alto de la ventana
		 *  @param bpp bits por píxel
		 */
		void SaveScreenshot(char *szArchivo,int w,int h,int bpp);

		/**
		 *  Devuelve el ancho de la ventana
		 *  @return retorna el ancho de la ventana
		 */
		int	GetWidth() { return _width; }

		/**
		 *  Devuelve el alto de la ventana
		 *  @return retorna el alto de la ventana
		 */
		int	GetHeight() { return _height; }

		/**
		 *  Permite seleccionar un cursor de windows desde un archivo
		 *  @param filename nombre del archivo que contiene el cursor
		 */
		void SetCursorFromFile(LPCWSTR filename) { _cursorType = LoadCursorFromFile(filename); }

		/**
		 *  Permite seleccionar el cursor de windows
		 *  @param cursor cursor que se desea seleccionar
		 */
		void SetCursor(LPCWSTR cursor) { _cursorType = LoadCursor(NULL, cursor); } 

		/**
		 *  Devuelve el tipo de cursor actual
		 *  @return devuelve el tipo de cursor actual
		 */
		HCURSOR GetCursor() { return _cursorType; }

		/**
		 *  Permite indicar si deseamos que el cursor permanezca visible al entrar en la ventana o no
		 *  @param cursor indica si deseamos que el cursor permanezca visible al entrar en la ventana o no
		 */
		void SetCursorVisible(bool cursor) { _cursorVisible = cursor; }

		/**
		 *  Devuelve si el cursor permanece visible al entrar en la ventana o no
		 *  @return Devuelve true si el cursor permanece visible al entrar en la ventana o false en caso contrario
		 */
		bool GetCursorVisible() { return _cursorVisible; } 

		/**
		 *  Devuelve el handler de la ventana
		 *  @return devuelve el handler de la ventana
		 */
		HWND GetHWnd() { return hWnd; }

		/**
		 *  Constructor
		 */
		Window();

};

extern ZAKENGINE_API Window g_window;

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#endif // _Window_H_
