// ---------------------------------------------------------------------
// Archivo: error.h
// Desc: Clase de manejo de errores.
//
// Autor: Juan Pablo (McKrackeN) Bettini
// ---------------------------------------------------------------------

#ifndef _ERROR_H_
#define _ERROR_H_

#include <string>
#include <sstream>
#include "defines.h"
#include "configFile.h"

using namespace std;

namespace zak {

class ZAKENGINE_API Message {
public:
	enum MessageCodes {
		NoError=0,
		CreateWindowError=1,
		D3DDeviceError=2,
		GetAdapterDisplayError=3,
		CreateDeviceError=4,
		GetViewportError=5,
		ProjectionMatrixError=6,
		Supported=7,
		NotSupported=8,
		VertexProcess=9,
		FullscreenMode=10,
		WindowedMode=11,
		ScreenWidth=12,
		ScreenHeight=13,
		AdapterCheckBegin=14,
		AdapterAvailable=15,
		Adapter=16,
		Driver=17,
		DriverDesc=18,
		DriverVersion=19,
		PixelFormatCheckBegin=20,
		Format=21,
		TexArrayFull=22,
		ConfigIniNotFound=23,
		InitializingEngine=24,
		EngineInitialized=25,
		RendererLoadTextureErrror=26,
		InvalidData=27,
		NotAvailable=28,
		OutOfVideoMemory=29,
		InvalidCall=30,
		OutOfMemory=31,
		CantCreateFont=32,
		SSEOperativeSystemSupported=33,
		Processor=34,
		CheckProcessor=35,
		CheckAudioDevices=36,
		InitGame=37,
		BitsPerPixel=38,
		VSync=39,
		Refresh=40,
		CantRead=41,
		MissingFileNameInDefFile=42,
		CannotInitFrames=43,
		FramesCount=44,
		AnimationSpeed=45,
		InitInput=46,
		InputEnumError=47,
		CreateDeviceJoy=48,
		DeviceNotReg=49,
		InvalidParam=50,
		NoInterface=51,
		NotInitialized=52,
		CoopLevel=53,
		DataFormat=54,
		Device=55,
		Number=56,
		MsgBox=57,
		ScriptCompile=58,
		ScriptException=59,
		FuncProt=60,
		Line=61,
		Module=62,
		Section=63,
		Description=64,
		NoContext=65,
		CreateNewFile=66,
		CantCreateFile=67,
		AnimationSpeedFPS=68,
		InvalidStatement=69,
		UnrecognizedCommand=70,
		CommandList=71,
		Loading=72,
		Compiled=73,
		Added=74,
		Removed=75,
		ScriptListCleared=76,
		ExecuteScript=77,
		Usage=78,
	};

	static bool CreateMsgFile(string filename);
	static int getLastErrorNum();
	static string getLastMessage();
	//static string getMessage(MessageCodes msgNum);
	static string getMessage(int msgNum);
	static void setError(int msgNum);
	static void setLanguaje(string lang);
	static string getLanguaje();
	static bool openDefaultMsgFile();
	static bool openMsgFile(string filename);
	static void closeMsgFile();

private:
	static int			_message;
	static string		_description;
	static string		_languaje;
	static string		_msgFilename;
	static FILE			_msgFile;
	static ConfigFile*	_parser;

};

} // end namespace

#endif