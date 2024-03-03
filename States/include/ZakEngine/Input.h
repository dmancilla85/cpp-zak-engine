#ifndef _INPUT_H_
#define _INPUT_H_

#include <stdio.h>
#include "renderer.h"
#include "Defines.h"
#include <dinput.h>

#pragma comment (lib, "dinput8.lib")

BOOL CALLBACK DIEnumDevicesCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);

namespace zak {

#define ZAK_MAX_INPUT_DEVICE						10

#define ZAK_INPUT_STATE_NOTHING						0
#define ZAK_INPUT_STATE_REACQUIRE					1
#define ZAK_INPUT_STATE_UNACQUIRE					2

#define ZAK_INPUT_POS_X                             0
#define ZAK_INPUT_POS_Y                             1
#define ZAK_INPUT_POS_Z                             2
#define ZAK_INPUT_MOUSE_POS_X                       0
#define ZAK_INPUT_MOUSE_POS_Y                       1
#define ZAK_INPUT_MOUSE_POS_Z                       2
#define ZAK_INPUT_MOUSE_BTN_1                       0
#define ZAK_INPUT_MOUSE_BTN_2                       1
#define ZAK_INPUT_MOUSE_BTN_3                       2

#define ZAK_INPUT_KEY_NONE							0
#define ZAK_INPUT_KEY_DOWN							1
#define ZAK_INPUT_KEY_UP							2
#define ZAK_INPUT_KEY_PRESSED						3

#define KeyUp(n)							(g_input._KeyEvent[n] == ZAK_INPUT_KEY_UP)
#define KeyDown(n)							(g_input._KeyEvent[n] == ZAK_INPUT_KEY_DOWN)
#define KeyPressed(n)						(g_input._KeyBuffer[n] & 0x80)
#define KeyEvent(n)							(g_input._KeyEvent[n])
#define MousePress(n)						(g_input._MouseData.Button[n] & 0x80)
#define MouseClick(n)                       (g_input._MouseData.ButtonClick[n])
#define MouseAbsPos(n)                      (g_input._MouseData.AbsPosition[n])
#define MouseAbsPosf(n)                     (float)(g_input._MouseData.AbsPosition[n])
#define MouseRelPos(n)                      (g_input._MouseData.RelPosition[n])
#define MouseRelPosf(n)                     (float)(g_input._MouseData.RelPosition[n])
#define MouseWorldPos(n)                    (g_input._MouseData.TtlPosition[n])
#define MouseWorldPosf(n)                   (float)(g_input._MouseData.TtlPosition[n])
#define JoystickPos(devNum, axis)			(g_input._joyData[devNum].Pos[axis])
#define JoystickRot(devNum, axis)			(g_input._joyData[devNum].Rot[axis])
#define JoystickPosf(devNum, axis)			(float)(g_input._joyData[devNum].Pos[axis])
#define JoystickRotf(devNum, axis)			(float)(g_input._joyData[devNum].Rot[axis])
#define JoystickButtons(devNum, button)		(g_input._joyData[devNum].Buttons[button] > 0)
#define JoystickCount()						(g_input._deviceCount)

struct InputJoystickData {
	long Pos[3];
	long Rot[3];
	BYTE Buttons[32];
};

struct InputMouseData {
	long TtlPosition[3];
	long AbsPosition[3];
	long RelPosition[3];
	BYTE Button[3];
    bool ButtonClick[3];
};

/**
 *	Clase de manejo de dispositivos de entrada (GamePad, Mouse, Teclado, etc).
 *	Ejemplo de uso:
 \code
 bool TestGame::OnInit() {

	_clearScreen = true;

	_shape.SetDim(100,100);
	_shape.SetPos(0,0);
	_shape.SetColor(0xFF00FF00);
	_shape.SetShape(ZAK_SHAPE_QUAD);

	_speedX = 0.0f;
	_speedY = 0.0f;

	g_renderer.SetViewPosition((float)(g_renderer.GetViewPortWidth()/2),(float)(g_renderer.GetViewPortHeight()/2));

	g_renderer.SetFont(FT_ARIAL);
	g_renderer.SetFontColor(0xFFFF0000);

	return true;
}

void TestGame::OnFrame() {
	
	_posX = _shape.GetPosX();
	_posY = _shape.GetPosY();
	
	_speedX = 0.0f;
	_speedY = 0.0f;

	if (KeyDown(DIK_ESCAPE))
		PostQuitMessage(0);

	// Si mantengo presionada la tecla cursor izquierda
	if (KeyPressed(DIK_LEFT)){ 
		_speedX = -SPEED;
		
	// Si mantengo presionada la tecla cursor derecha
	} else if (KeyPressed(DIK_RIGHT)) { 
		_speedX = SPEED;
	} 

	// Si mantengo presionada la tecla  cursor arriba
	if (KeyPressed(DIK_UP)) { 
		_speedY = SPEED;
	
	// Si mantengo presionada la tecla cursor abajo
	} else if (KeyPressed(DIK_DOWN)) { 
		_speedY = -SPEED;

	} 

	// Si muevo el mouse
	if (MouseRelPosf(ZAK_INPUT_MOUSE_POS_X) != 0.0f) { 
		_posX += MouseRelPosf(ZAK_INPUT_MOUSE_POS_X);
	} 
	if (MouseRelPosf(ZAK_INPUT_MOUSE_POS_Y) != 0.0f) { 
		_posY += MouseRelPosf(ZAK_INPUT_MOUSE_POS_Y);
	}

	// Si hay algún joystick conectado 
	if (JoystickCount() > 0) { 

		// Verifico si la posición del joystick es diferente del centro
		if (JoystickPosf(0, ZAK_INPUT_POS_X) != 0.0f) { 

			// Muevo el pad respecto de la posición del joystick
			_speedX = JoystickPosf(0, ZAK_INPUT_POS_X)/1024*SPEED;
		}
		// Verifico si la posición del joystick es diferente del centro
		if (JoystickPosf(0, ZAK_INPUT_POS_Y) != 0.0f) { 

			// Muevo el pad respecto de la posición del joystick
			_speedY = -JoystickPosf(0, ZAK_INPUT_POS_Y)/1024*SPEED;
		}
	}

	// Actualizamos la posición
	_posX += _speedX*(float)_fpsMeter.GetDT();
	_posY += _speedY*(float)_fpsMeter.GetDT();

	_shape.SetPos(_posX, _posY);
	_shape.Update((float)_fpsMeter.GetDT());
}

void TestGame::OnDraw() {

	_shape.Draw();

	wstringstream ss;

	ss << ZAK_ENGINE_NAME << endl << "FPS: " << _fpsMeter.GetFps() << endl;
	// Si hay algún joystick conectado 
	if (JoystickCount() > 0) { 
		ss << "JoyX: " << JoystickPosf(0, ZAK_INPUT_POS_X) << " - JoyY: " << JoystickPosf(0, ZAK_INPUT_POS_Y) << endl;
	}
	ss << "MouseAbsPosX: " << MouseAbsPosf(ZAK_INPUT_MOUSE_POS_X)  << " - MouseAbsPosY: " << MouseAbsPosf(ZAK_INPUT_MOUSE_POS_Y)  << endl;
	ss << "MouseWorldPosX: " << MouseWorldPosf(ZAK_INPUT_MOUSE_POS_X)  << " - MouseWorldPosY: " << MouseWorldPosf(ZAK_INPUT_MOUSE_POS_Y)  << endl;


	g_renderer.DrawString(ss.str(),10,10,800-20,600-20,ZAK_TEXT_LEFT);
}
 \endcode
 *	@author Juan Pablo "McKrackeN" Bettini
 */
class ZAKENGINE_API Input {
public:
	BYTE			        _KeyBuffer[256];       // keyboard buffer for received data
	BYTE			        _KeyPrevBuffer[256];   // keyboard buffer for received data
	BYTE			        _KeyEvent[256];        // keyboard buffer for received data
	InputMouseData	        _MouseData;            // Mouse buffer for received data
	DIMOUSESTATE            MouseTaken;
	DIJOYSTATE				JoyTaken[ZAK_MAX_INPUT_DEVICE];
	InputJoystickData		_joyData[ZAK_MAX_INPUT_DEVICE];

	// Initialize DirecInput
	int  InitializeDirectInput(HINSTANCE hInstance, HWND hWnd);

	// End DirectInput
	void EndDirectInput(void);

	// Acquire Keyboard and mouse
	void Acquire(void);

	// Clean the input buffer
	void CleanBuffer(void);

	// Reacquire the input
	void Reacquire(void);

	// Unacquire the input
	void Unacquire(void);

	// Get the key events
	void GetKeyEvent(void);

	// Set the current input position
	void SetPosition(long x, long y, long z);

	// Clean the events
	void EventClean(void);

	bool ToggleMouseExclusive(bool mouseExclusive);
	bool IsMouseExclusive() { return _mouseExclusive; }

	Input();
	~Input();

	static int			_deviceCount;
	static GUID			_guid[ZAK_MAX_INPUT_DEVICE];

private:
	LPDIRECTINPUT8          _lpObjectOne;		// Direct Input ( Add )
	LPDIRECTINPUT8          _lpObjectTwo;		// Direct Input ( Add )
	LPDIRECTINPUT8          _lpObjectThree;		// Direct Input ( Add )
	LPDIRECTINPUTDEVICE8	_lpKeyboard;		// Keyboard Device ( Add )
	LPDIRECTINPUTDEVICE8    _lpMouse;			// Mouse Device (Add)
	LPDIRECTINPUTDEVICE8    _lpJoystick[ZAK_MAX_INPUT_DEVICE];	// Joystick Device (Add)
	bool                    _bButtonState[3];
	bool					_bMouseLastFrameState[3];
	bool					_mouseExclusive;

};

extern ZAKENGINE_API Input g_input;

}

#endif //_INPUT_H_

