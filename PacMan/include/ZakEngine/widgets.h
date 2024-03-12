#pragma once

#include <sstream>
#include "console.h"
#include "renderer.h"
#include "sprite.h"
#include "list.h"
#include "defines.h"

#define WIDGET_NONE				0
#define WIDGET_ROLLOVER			1
#define WIDGET_ROLLOUT			2
#define WIDGET_CLICK			3
#define WIDGET_PRESS			4
#define WIDGET_DBLCLICK			5
#define WIDGET_FOCUS			6
#define WIDGET_FOCUSLOST		7
#define WIDGET_DRAG				8
#define WIDGET_STOPDRAG			9
#define WIDGET_RETURN			10

#define WIDGET_DBLCLICK_DELAY	150

#define WIDGET_BLINK_DELAY		500

namespace zak {

class ZAKENGINE_API WidgetMgr;

/**
 *  Clase que define el esqueleto de los widgets con sus eventos
 *	Ejemplo de uso:
\code
\endcode

 *	@author Juan Pablo "McKrackeN" Bettini
 */
class ZAKENGINE_API Widget : public Sprite { 

public:
	/**
	 *  Método virtual que debe invocarse al crearse un widget. Además puede ser sobrecargado.
	 *  @return Devolverá true en el caso de que todo haya salido bien y false en caso contrario
	 */
	virtual bool Initialize();

	/**
	 *  Método virtual invocado cuando el widget toma el foco
	 */
	virtual void OnFocus() { }

	/**
	 *  Método virtual invocado cuando el widget pierde el foco
	 */
	virtual void OnFocusLost() {}

	/**
	 *  Método virtual invocado cuando el usuario hace click con el botón izquierdo del mouse sobre el widget
	 */
	virtual void OnClick() {}

	/**
	 *  Método virtual invocado cuando el usuario mantiene presionado el botón izquierdo del mouse sobre el widget
	 */
	virtual void OnPress() {}

	/**
	 *  Método virtual invocado cuando el usuario hace doble click con el botón izquierdo del mouse sobre el widget
	 */
	virtual void OnDoubleClick() {}

	/**
	 *  Método virtual invocado cuando el mouse pasa por sobre el widget
	 */
	virtual void OnRollOver() {}

	/**
	 *  Método virtual invocado cuando el mouse escapa de la zona del widget
	 */
	virtual void OnRollOut() {}

	/**
	 *  Método virtual invocado cuando el usuario trata de arrastrar el widget.
	 *  Debe estar activado el arrastre para el widget, sino el evento será ignorado.
	 */
	virtual void OnDrag() { }

	/**
	 *  Método virtual invocado si el usuario arrastra un widget sobre éste y lo suelta. 
	 *  @param widget Puntero al widget que está siendo arrastrado
	 */
	virtual void OnDropIn(Widget *widget) {}

	/**
	 *  Método virtual invocado si el usuario arrastra este widget y lo suelta sobre otro. 
	 *  @param widget Puntero al widget que donde lo está colocando
	 */
	virtual void OnDropOut(Widget *widget) {}

	/**
	 *  Método virtual invocado si se presiona enter mientras el widget está en foco
	 */
	virtual void OnReturn() {}

	/**
	 *  El método crea una fuente de sistema según los parámetros pasados´.
	 *  @param ft Tipo de fuente.
	 *  @param size Tamaño de la fuente.
	 *  @return Retorna true si fue posible crear la fuente y false en caso contrario
	 */
	bool SetFont(ZAK_FONT_TYPES ft, int size=15);

	/**
	 *  El método permite indicar el color de la fuente.
	 *  @param color Color de la fuente.
	 */
	void SetFontColor(unsigned int color) { _color = color; }

	/**
	 *  Devuelve el alto de la fuente.
	 *  @return Retorna un número entero que indica el alto de la fuente
	 */
	int GetFontHeight() { return _size; }

	/**
	 *  Devuelve el tipo de fuente actualmente seleccionada.
	 *  @return Retorna el tipo de fuente seleccionada actualmente.
	 */
	ZAK_FONT_TYPES GetFont();

	/**
	 *  Adjunta un widget al actual
	 *  @return Retorna true en caso de haber podido adjuntar el widget y false en caso contrario
	 */
	bool Attach(Widget &widget);

	/**
	 *  Desprende un widget al actual
	 *  @return Retorna true en caso de haber podido desprender el widget y false en caso contrario
	 */
	bool Detach(Widget &widget);

	/**
	 *  Desprende todos los widgets del actual
	 */
	void DetachAll();

	/**
	 *  Método virtual que muestra el widget
	 */
	virtual void Draw();

	/**
	 *  Método virtual que actualiza el widget
	 */
	virtual void Update(float dt);

	/**
	 *  Devuelve si el widget está en foco o no
	 *  @return Devuelve true en caso de estar en foco y false en caso contrario.
	 */
	bool GetFocused() { return _isFocused; } 

	/**
	 *  Permite indicar la posición relativa al widget que contiene al actual.
	 *  @param x Componente x de la posición relativa 
	 */
	void SetRelPosX(float x) { _relPosX = x; }

	/**
	 *  Permite indicar la posición relativa al widget que contiene al actual.
	 *  @param y Componente y de la posición relativa 
	 */
	void SetRelPosY(float y) { _relPosY = y; }

	/**
	 *  Permite indicar la posición relativa al widget que contiene al actual.
	 *  @param x Componente x de la posición relativa 
	 *  @param y Componente y de la posición relativa 
	 */
	void SetRelPos (float x, float y) { _relPosX = x; _relPosY = y; }

	/**
	 *  Devuelve la posición relativa al widget que contiene al actual.
	 *  @return Componente x de la posición relativa 
	 */
	float GetRelPosX() { return _relPosX; }

	/**
	 *  Devuelve la posición relativa al widget que contiene al actual.
	 *  @return Componente y de la posición relativa 
	 */
	float GetRelPosY() { return _relPosY; }

	/**
	 *  Indica si el widget puede arrastrarse
	 *  @param dragable Indica si el widget puede arrastrarse
	 */
	void SetDragable(bool dragable) { _dragable = dragable; }

	/**
	 *  Devuelve si el widget puede arrastrarse
	 *  @return Devuelve si el widget puede arrastrarse
	 */
	bool GetDragable() { return _dragable; }
	
	/**
	 *  Permite activar o desactivar el widget. En caso de estar desactivado, se mostrará pero no recibirá eventos.
	 *  @param enable Indica si está activado o no
	 */
	void SetEnable(bool enable) { _enable = enable; }

	/**
	 *  Devuelve si el widget se encuentra activado o no.
	 *  @return Devuelve si está activado o no
	 */
	bool GetEnable() { return _enable; }

	/**
	 *  Permite indicar el intervalo entre clicks para ser tomado como un doble click (en milisegundos)
	 *  @param dblClickDelay Número flotante que indica el intervalo de tiempo en milisegundos entre clicks
	 */
	void SetDoubleClickDelay(float dblClickDelay) { _dblClickDelay = dblClickDelay; }

	/**
	 *  Devuelve el intervalo entre clicks para ser tomado como un doble click (en milisegundos)
	 *  @return Número flotante que indica el intervalo de tiempo en milisegundos entre clicks
	 */
	float GetDoubleClickDelay() { return _dblClickDelay; } 

	/**
	 *  Constructor
	 */
	Widget();

	/**
	 *  Destructor
	 */
	virtual ~Widget();

protected:
	virtual void OnFocusInternal() { _isFocused = true; }
	virtual void OnFocusLostInternal() {_isFocused = false;  }
	virtual void OnClickInternal() {}

	void DrawString(string &text, float x, float y, float w, float h, unsigned int align=ZAK_TEXT_LEFT);
	void DrawString(wstring &text, float x, float y, float w, float h, unsigned int align=ZAK_TEXT_LEFT);
	void DrawString(char* text, float x, float y, float w, float h, unsigned int align=ZAK_TEXT_LEFT);

	Widget *DoEvents(int &event);

	Widget *GetParent() { return _parent; }
	WidgetMgr *GetMgr() { return _mgr; }

	void Release();
	void Reset();  

	ID3DXFont		*_pDefDXFont;
	Widget			*_parent;
	WidgetMgr		*_mgr;
	bool			_editing;
	unsigned int	_color;
	int				_size;


private:
	bool CheckRollOver() {
		static float x1;
		static float y1;
		static float width;
		static float height;
		static float x2;
		static float y2;
		static float xv, yv;

		width	= GetCollisionWidth();
		height	= GetCollisionHeight();
		x1		= GetPosX()-width*0.5f+GetPivotPosX();
		y1		= GetPosY()-height*0.5f+GetPivotPosY();

		g_renderer.GetViewPosition(xv, yv);

		x2 = MouseAbsPosf(ZAK_INPUT_MOUSE_POS_X)-(int)(g_renderer.GetViewPortWidth()/2)+xv;
		y2 = MouseAbsPosf(ZAK_INPUT_MOUSE_POS_Y)-(int)(g_renderer.GetViewPortHeight()/2)+yv;

		if (x2 > x1 && x2 < x1+width && y2 > y1 && y2 < y1+height) {
			return true;
		}

		return false;
	}	

	List<Widget*>	_widgets;

	float			_relPosX;
	float			_relPosY;

	bool			_mouseOver;
	bool			_dragging;
	
	bool			_dragable;
	bool			_enable;

	float			_dblClickDelay;
	float			_accumTime;

	bool			_isFocused;
	bool			_mouseClick;

	ZAK_FONT_TYPES	_pDefDXFontType;

	friend class WidgetMgr;
	friend class Widget;
};

/**
 *  Clase que define un widget estilo EditBox (caja de edición de texto)
 *  @author Juan Pablo "McKrackeN" Bettini
 */
class ZAKENGINE_API WdgEditBox : public Widget {
public:
	/**
	 *  Devuelve una cadena de caracteres con el texto que contiene la caja de texto
	 *  @return Cadena de caracteres
	 */
	string GetText() { return _string; } 

	/**
	 *  Permite indicar el texto que muestra la caja de texto
	 *  @param str Cadena de caracteres
	 */
	void SetText(string str);

	/**
	 *  Muestra el widget en pantalla
	 */
	virtual void Draw();

	/**
	 *  Actualiza el widget
	 *  @param dt Intervalo de tiempo entre iteraciones del bucle principal
	 */
	virtual void Update(float dt);

	virtual void OnFocus() {
		OnFocusInternal();
	}
	virtual void OnFocusLost() {
		OnFocusLostInternal();
	}

	/**
	 *  Constructor
	 */
	WdgEditBox();

protected:

	void OnFocusInternal();
	void OnFocusLostInternal();
	void OnClickInternal();

private:
	float		_timeAccum;
	bool		_blink;

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
	basic_string <char>::iterator _iter;

};

#define MAX_CONSOLE_LINES		20 
#define CONSOLE_HEIGHT			300

class ZAKENGINE_API WdgConsoleEdit : public WdgEditBox {
public:

	void OnReturn();

	WdgConsoleEdit(){}
	~WdgConsoleEdit(){}
private:
};

/**
 *  Clase que define un widget estilo consola tipo Quake
 *  Ejemplo de uso:
\code
// game.h
#pragma once

#include <sstream>
#include "ZakEngine/zak.h"

using namespace zak;

class TestGame : public Game {
public:

	void OnFrame();
	bool OnShutdown();
	bool OnInit();
	void OnDraw();

	TestGame();
	~TestGame();

private:

	WdgConsole	_console;
	WidgetMgr	_wdgMgr;
};
\endcode

\code
#include "game.h"

TestGame::TestGame() {
}

TestGame::~TestGame() { 

}
bool TestGame::OnInit() {
		
	_console.Initialize();
	_console.SetColor(0x80000000);
	_console.SetFont(FT_COURIER,15);
	_console.SetFontColor(0xFF00FF00);
	_console.SetEditColor(0xA0000000);
	_console.SetEditFontColor(0xFF00FF00);
	_console.SetEditFont(FT_COURIER,15);
	_console.SetHeight(300);

	_clearScreen = true;

	g_renderer.SetFont(FT_TAHOMA, 15);
	g_renderer.SetFontColor(0xFFFF0000);

	return true;
}

void TestGame::OnFrame() {

	if (KeyPressed(DIK_ESCAPE)) 
		PostQuitMessage(0);

	if (KeyDown(DIK_GRAVE)) {
		if (_wdgMgr.IsAttached(_console))
			_wdgMgr.Detach(_console);
		else
			_wdgMgr.Attach(_console);
	}


	_wdgMgr.Update((float)_fpsMeter.GetDT());
}

void TestGame::OnDraw() {
	wstringstream ss;

	ss << ZAK_ENGINE_NAME << endl << "FPS: " << _fpsMeter.GetFps() << endl;

	_wdgMgr.Draw();

	g_renderer.DrawString(ss.str(),10,10,800-20,600-20,ZAK_TEXT_LEFT|ZAK_TEXT_BOTTOM);
}

bool TestGame::OnShutdown() {
	_wdgMgr.DetachAll();

	ScriptMgr::ClearScriptList();

	return true;
}

\endcode
 *  @author Juan Pablo "McKrackeN" Bettini
 */
class ZAKENGINE_API WdgConsole : public Widget {

public:
	/**
	 *  Inicializa el widget
	 *  @return Retorna true si todo salió bien y false en caso contrario
	 */
	bool Initialize();

	/**
	 *  Muestra el widget en pantalla
	 */
	void Draw();

	/**
	 *  Actualiza el widget
	 *  @param dt Intervalo de tiempo entre iteraciones del bucle principal
	 */
	void Update(float dt);

	/**
	 *  Permite indicar el color de la caja de texto de la consola
	 *  @param color Color de la caja de texto
	 */
	void SetEditColor(DWORD color) { _edit.SetColor(color); }

	/**
	 *  Permite indicar el color del texto de la caja de texto de la consola
	 *  @param color Color del texto
	 */
	void SetEditFontColor(DWORD color) { _edit.SetFontColor(color); }

	/**
	 *  Permite indicar la fuente de la caja de texto de la consola
	 *  @param ft Tipo de fuente
	 *  @param size Tamaño de la fuente
	 */
	void SetEditFont(ZAK_FONT_TYPES ft, int size=15);

	void OnFocus() { _edit.OnFocus(); }
	void OnFocusLost() { _edit.OnFocusLost(); }

	/**
	 *  Constructor
	 */
	WdgConsole();

	/**
	 *  Destructor
	 */
	~WdgConsole();

private:
	string			_text;
	WdgConsoleEdit	_edit;
};

/**
 *  Clase que manejará los widgets
 *  @author Juan Pablo "McKrackeN" Bettini
 */
class ZAKENGINE_API WidgetMgr {

public:

	/**
	 *  Constructor
	 */
	WidgetMgr();

	/**
	 *  Destructor
	 */
	virtual ~WidgetMgr();

	/**
	 *  Muestra los widgets que se encuentren adjuntos al manager
	 */
	void Draw();

	/**
	 *  Actualiza los widgets que se encuentran adjuntos al manager
	 *  @param dt Intervalo de tiempo entre iteraciones del bucle principal
	 */
	void Update(float dt);

	/**
	 *  Permite poner en foco un widget en particular.
	 *  @param widget Referencia al widget que deseamos poner en foco.
	 *  @return Devuelve false en caso de que el widget no se encuentre adjunto al manager
	 */
	bool SetFocus(Widget &widget);

	/**
	 *  Devuelve si un widget en particular está ajunto o no al manager
	 *  @param widget Referencia al widget en particular
	 *  @return Devuelve true en caso de encontrarse adjunto y false en caso contrario
	 */
	bool IsAttached(Widget &widget);

	/**
	 *  Adjunta un widget al manager
	 *  @param widget Referencia al widget que se desea adjuntar
	 *  @return Devuelve true si pudo ser adjuntado y false en caso contrario
	 */
	bool Attach(Widget &widget);

	/**
	 *  Desprende un widget del manager
	 *  @param widget Referencia al widget que se desea desprender
	 *  @return Devuelve true si pudo ser desprendido y false en caso contrario
	 */
	bool Detach(Widget &widget);

	/**
	 *  Desprende todos los widgets del manager
	 */
	void DetachAll();

	void ReleaseAll();
	void ResetAll();

private:
	List<Widget*> _widgets;

	Widget *_focused;
	Widget *_dragging;
};

}