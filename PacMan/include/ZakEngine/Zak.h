#ifndef _ZAK_H_
#define _ZAK_H_

/*! \mainpage Documentaci�n de Zak Engine
 *
 * \section intro_sec Introducci�n al motor
 *
 * El nombre surgi� en honor a la memorable aventura gr�fica �Zak McKracken and the Alien Mindbenders� de la empresa LucasFilm, donde �Zak McKracken� es el nombre del protagonista y apodo que utilizo desde hace ya muchos a�os.
 *
 * El Zak Engine es un motor basado en DirectX 8.1 y DirectX 9.0 desarrollado para facilitar la creaci�n de juegos 2d. Entre sus facultades en constante crecimiento se encuentran:

    - Sprites animados
    - Mapas de tiles generados a partir del formato de los editores Anaconda Map Editor y Mappy
    - Sonido y m�sica en diversos formatos (wav, mp3, ogg, etc) a trav�s de la librer�a gratuita Audiere
    - Sistema de scripting (AngelScript)
    - Bitmap Fonts creados a partir de la aplicaci�n Bitmap Font Creator
    - Sistema de part�culas
    - Controles visuales (botones, cajas de edici�n de textos, ventanas, etc).
    - Sistema de red cliente/servidor para juegos multijugador basado en la librer�a gratuita Enet

 * Esta librer�a es completamente gratuita para uso comercial y no comercial siempre y cuando se cumplan los requisitos que indica la \ref licence_sec. Espero que sea de su utilidad y no dude en contactarse ante cualquier duda, sugerencia o bug encontrado en <a href="http://www.zakengine.com">http://www.zakengine.com/</a href>.
 * 
 * Puede ver la lista de \ref changes_page.
 *
 * Adem�s, para crear su primera clase Game puede ver el \ref tutorial1_page.
 *
 * \section licence_sec Licencia

LICENCIA ZAK ENGINE

Por medio de la presente licencia, Juan Pablo Bettini le otorga a usted, el desarrollador, el derecho a utilizar el kit de desarrollo y la librer�a �Zak Engine� libre de cargo para la creaci�n de software comercial y no comercial siempre y cuando se cumpla con todos los requisitos que este documento establece.

VISUALIZACI�N DEL LOGOTIPO DE ZAK ENGINE

La aplicaci�n (ej: videojuego) que utilice el �Zak Engine� deber� visualizar como primer imagen, el logotipo del �Zak Engine� durante un per�odo no menor a cuatro segundos.

El logotipo se encuentra incluido y deber� ser visualizado sin modificaci�n alguna de forma, color o tama�o.

SIN GARANT�AS

El software es provisto �como est�, sin garant�a alguna de ning�n tipo, bien expresa o impl�cita, con inclusi�n, pero sin limitaci�n a las garant�as mercantiles impl�citas o a la conveniencia para un prop�sito particular.

Cualquier riesgo referente a la calidad y prestaciones del programa es asumido por usted. Si se probase que el Programa es defectuoso, asume el coste de cualquier servicio, reparaci�n o correcci�n.

 * \section author_sec Sobre el autor
Mi nombre es Juan Pablo Bettini, soy Argentino nacido en Bah�a Blanca, provincia de Buenos Aires. Hoy en d�a vivo en Capital Federal. Comenc� en la programaci�n a la muy temprana edad de 8 a�os con mi Commodore 64. A lo largo de mi vida pas� por muchos lenguajes de programaci�n como el Basic, Assembler x86, Modula, Pascal, Delphi, Java, C, C++, Action Script, Lingo, entre otros. Me recib� de Programador Profesional de Juegos en Image Campus en diciembre del 2004. Trabaj� en Games And Web desarrollando videojuegos para Cartoon Network. Actualmente me dedico a dar clases de programaci�n en el instituto donde me recib�. Tambi�n estoy escribiendo un libro sobre el desarrollo de videojuegos para la editorial MP Ediciones. Adem�s, contin�o en el rubro trabajando freelance y en proyectos personales.

\page changes_page Cambios en versiones
v1.0
- Se arregl� un bug en el m�todo ToggleMouseExclusive de la clase Input
- Se arregl� un bug en la clase Entity2D
- Se agregaron los m�todos Tan, ATan, ASin, ACos y Round a la clase MathUtil 
- Se agreg� la posibilidad de modificar el pivot en el emisor de particulas

v1.0.0.0 RC 6 Patch
- Se arregl� un bug en MouseRelPos que se sum� en RC6

v1.0.0.0 RC 6
- Se arregl� un bug en MouseWorldPos
- Se arregl� un bug en MouseRelPos

v1.0.0.0 RC 5
- Se arregl� el c�lculo de los UV de las texturas de los mapas y sprites
- Se agreg� la posibilidad de utilizar #include en scritps
- Se hicieron modificaciones menores en la clase Entity2D
- Se agregaron las funciones RadToDegree y DegreeToRad al motor de scripts
- Se implement� la registraci�n de clases y m�todos escalonada en el motor de script
- Se recompil� la librer�a AngelScript para que evitar el log a disco
- Se agregaron las opciones TextureFilter y TextureMipFilter al archivo de definici�n de sprites que permite seleccionar los diferentes filtros para las texturas
- Se arregl� un bug en la clase Input (posici�n del mouse en el mundo)

v1.0.0.0 RC 4 Patch
- Se arregl� el c�lculo de los UV de las texturas de los mapas y sprites

v1.0.0.0 RC 4
- Se arregl� un bug en la clase Game que si no le pasamos la configuraci�n lanzaba una violaci�n de acceso
- Se arregl� un bug en la clase Texture Manager al remover las texturas
- Se arregl� un bug en la clase Input que invert�a el mouse verticalmente en MouseWorldPos
- Se arregl� un bug en la consola 

v1.0.0.0 RC 3
- Se agreg� que si est� activada la propiedad CollisionVisible se dibuje al momento de dibujar el sprite.
- Se agreg� el dibujado del �rea de colisi�n circular
- Se agreg� la posibilidad de cargar sonidos por tipo efecto sonoro o m�sica para poder modificar el volumen por tipo
- Se modific� la clase Sprite de manera tal de poder funcionar tambi�n como un Shape
- Se actualiz� la librer�a AngelScript a la versi�n 2.8.0a
- Se cre� un sistema de consola in-game
- Se arregl� un bug en el m�todo SetAngleZ y GetAngleZ
- Se optimizaron las rotaciones
- Se registr� la clase Entity2D en el motor de script
- Se arregl� un bug que al hacer resetear el dispositivo D3D no se liberaban las texturas y cortaba la ejecuci�n (Gracias Jonee)
- Se modific� la clase TextureManager para que use un vector de texturas
- Se elimin� la clase EntityList
- Se agreg� la clase GameConfig que permite, si as� lo deseamos, cargar y guardar la configuraci�n del motor desde el archivo .ini
- Se arregl� un bug en la clase SoundMgr y Sound
- Se agreg� el m�todo virtual OnLostDevice en la clase Game que ser� invocado al perderse el dispositivo D3D ante un ALT+TAB

v1.0.0.0 RC 2
- Se agreg� en la clase Map la posibilidad de cargar, mostrar y hacer uso de mapas en formato .AMF (AnaConda Map Editor) 
- Ahora es posible descargar las texturas cargadas de memoria RAM y de video por medio del m�todo Unload
- Se arreglo un bug en el m�todo SetToPreviousPos de la clase Entity2D (Gracias NEXUS)

v1.0.0.0 RC 1
- Se arregl� un bug en la clase Input donde la posici�n relativa del mouse en modo no exclusivo no coincid�a con la posici�n absoluta
- Se arregl� un bug en el m�todo FlipVertical de la clase Sprite que a veces no invert�a verticalmente
- Se agregaron dos variables en el archivo de definici�n de los sprites: OffsetX y OffsetY que permiten decidir en qu� posici�n de la textura est�n las figuras
- Se agreg� la variable CollisionRadius en el archivo de definici�n de sprites que permite indicar el radio de colisi�n del mismo
- Se agreg� un m�todo GetAnimation a la clase Sprite que devuelve un puntero a la animaci�n actual
- Se agregaron los m�todos GetTileNumCount, GetWorldCoordsFromTile y GetColRowFromTile en la clase Map
- Se modific� la clase Window para que el area de cliente sea del tama�o indicado y no menor (Gracias Santiago Isidro!)
- Se arregl� el bug que no permit�a readquirir el foco de la ventana con un click del mouse
- Se agreg� la variable Set a la clase Font que permite seleccionar el set de fuentes a mostrar
- Se agregaron los m�todos getRepeat, getLength, getPosition, setPosition, setPan, getPan, reset e isPlaying a la clase Sound
- Se separaron las librer�as del motor con las de red para evitar confusiones en las dependencias entre ambas

v0.3.4.3
- Ahora se muestran los fonts de debug en DirectX 8.1
- Se agreg� un m�todo IsEnabledSystem para determinar si el sistema de part�culas esta activado o no

v0.3.4.2
- Se agreg� una clase est�tica MathUtil que permite tomar senos, cosenos y n�meros aleatorios a partir de una tabla utilizando los m�todos SinCos y Random
- Se optimizaron las clases Entity2D y ParticleSystem
- Se arregl� un bug que no permit�a quitar la sincronizaci�n vertical en pantalla completa
- Se agreg� un m�todo SetCursorFromFile en la clase Window que permite la carga de un puntero del mouse personalizado

v0.3.4.1
- El mouse ahora es adquirido en modo cooperativo
- Ahora el m�todo MouseAbsPos devuelve la posici�n del mouse con respecto a la ventana tomada a partir de las coordenadas de windows
- Se recompil� el framework utilizando la versi�n 2.7.1b del motor de scripting AngelScript
- Ahora el motor est� compilado para DirectX81 y DirectX9
- Se agreg� la posibilidad de determinar la velocidad de las animaciones de los sprites en FPS por medio de la variable SpeedFPS
- Se agreg� el sistema de part�culas 
- Se agregaron las constantes DegreeToRad, RadToDegree y PI 
- Ahora es posible cambiar la posici�n del pivot de un sprite desde el archivo de configuraci�n del mismo

v0.3.3.1
- Se implement� la carga de mapas exportados con el formato .map del editor Anaconda Map Editor
- Se arregl� un bug de compatibilidad con m�ltiples procesadores en la clase FPSMeter 
- Se agreg� un m�todo setGlobalVolume a la clase SoundMgr que permite modificar el volumen de todos los sonidos abiertos

v0.3.2.5
- Se arregl� un bug en el m�todo DrawString que provocaba un cuelgue aleatorio en el motor.
- Se arregl� un bug en el m�todo SetTile que modificaba el tile visualmente pero no l�gicamente
- Se modific� el m�todo GetWorldCoordsFromColRow para que devuelva true si la columna y fila dada est� dentro del mapa y false en caso contrario

v0.3.2.4
- Se agreg� que si el archivo config.ini y msg.ini no existen, se cree uno nuevo sin provocar error

v0.3.2.3
- Se agreg� un m�todo GetTileFromColRow en la clase Map para adquirir un tile mediante una columna y una fila del mapa
- Se arregl� un bug en el m�todo GetWorldCoordsFromColRow de la clase Map
- Se arregl� un bug en la traslaci�n de la clase Entity2D

v0.3.2.2b
- Se agregaron dos m�todos a la clase Sound que permiten adquirir y setear el volumen

v0.3.2.2
- Se arregl� un bug en la clase Map
- Se implement� sistema de cambio de resoluci�n en tiempo de ejecuci�n
- Se arregl� un bug en la clase List (Gracias Juan Manuel Alvarez)
- Se agregaron m�todos para adquirir la posici�n anterior de una entidad GetPreviousPosX, GetPreviousPosY y GetPreviousPos
- Se agreg� la posibilidad de forzar la inicializaci�n del motor evitando las opciones del archivo config.ini
- Se agreg� el m�todo GetLastMessage en la clase Log que permite leer el �ltimo mensaje escrito en el archivo de log

v0.3.2.1
- Se arregl� un bug en la clase Map
- Se implement� el sistema de Scripting y est� funcionando (AngelScript)
- Se implement� el sistema de red por medio de paquetes UDP utilizando la librer�a gratuita ENet
- Se reimplement� la clase List

v0.3.1.11
- Se arregl� un bug en la clase Message
- Se implement� una clase para el manejo de redes a trav�s de la librer�a Enet por paquetes UDP
- Se agreg� la propiedad Spacing a la clase Font para permitir la parametrizaci�n del espaciado de los Bitmap Fonts
- Se agreg� la macro KeyEvent en la clase Input que permite chequear las teclas por eventos Down, Up y Pressed
- Cambi� el nombre de la macro para verificar si una tecla est� presionada de KeyDown a KeyPressed

v0.3.1.10
- Se arregl� el bug de la clase Sprite que no permit�a mostrar un frame en particular con el m�todo SetFrame
- Se implement� la clase Font que permite dibujar en pantalla Bitmap Fonts creados a partir del programa Bitmap Font Creator (gracias Thom Wetzel, Jr)
- Se arregl� el bug en la toma de valores enteros negativos durante el parseo de archivos .ini en la clase ConfigFile

v0.3.1.9
- Varias optimizaciones
- Aparentemente se arregl� el problema visual en modo ventana y pantalla completa (Gracias Santiago Isidro)
- Se invirti� el eje Y en el mouse para que coincida con el eje Y de la pantalla
- Se agregaron las propiedades de posici�n del p�vot en X e Y

v0.3.1.8
- Se agreg� el flipeo horizontal y vertical de las entidades.
- Se optimiz� la actualizaci�n y el dibujado de las entidades.
- Ahora la clase Input enumera los dispositivos de entrada y adquiere la informaci�n de todos ellos.
- Adquisici�n del estado de los joysticks.

v0.3.1.7
- Cambio en el m�todo Draw de las entidades. Ahora no es necesario pasarle el deltaT por par�metro.
- Se agregaron dos m�todos m�s en la clase Entity2D que permiten cambiar la posici�n en X y en Y independientemente.
- Se agreg� un m�todo SetTile en la clase mapa que permite cambiar un tile en particular.
- Se implement� la carga de animaciones desde un archivo de definici�n.
- Arreglo de un bug que al tratar de apagar el motor cuando fall� la inicializaci�n daba una violaci�n de acceso.

v0.3.1.6
- Arreglo de un bug al mostrar el �rea de colisi�n de un Sprite.
- Se agregaron las opciones de cambio de tama�o de las �reas de colisi�n desde el archivo de definici�n de los Sprites.
- Se modific� el nombre del tipo enumerador de ShapeTYPE a ShapeType.
- Se cambi� el sistema de Update de los Shapes y los Sprites. 

v0.3.1.5
- Arreglo de algunos bugs en la carga de archivos de definici�n de los sprites (gracias Alejandro Luna).
- Arreglo de un bug al mostrar un sprite que no pudo ser cargado (se colgaba la aplicaci�n).
- Arreglo de un bug en el parser de archivos de definici�n.
- Arreglo de mensajes de error en el log sobre archivos que no pueden ser cargados.
- Se implement� un sistema de scripting a trav�s de AngelScript (no testeado).

v0.3.1.4
- Se implement� el sistema de carga de texturas en modo no persistente.
- Arreglo de un bug referente a la recarga de las texturas ante un ALT+TAB.
- Cambio en parte de algunos headers del motor por el problema con las carpetas relativas (Gracias Gabriel Beranger). 
- Arreglo de un par de bugs del sonido. Adem�s se agreg� la opci�n en el config.ini que permite apagar el sonido.

v0.3.1.3
- Se implementaron las clase SoundMgr y Sound embebiendo la librer�a Audiere.
- Se implement� el sistema de recuperaci�n del dispositivo D3D y recarga de texturas ante un ALT+TAB.

v0.3.0.0
- Primera versi�n del motor 2d.


\page tutorial1_page Tutorial 1 - C�mo crear la clase principal del juego

\code
// game.h
#pragma once

#include <sstream>
#include "zakengine/zak.h"

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

};
\endcode

\code
// game.cpp
#include "game.h"

TestGame::TestGame() {

}

TestGame::~TestGame() { 

}
bool TestGame::OnInit() {

	_clearScreen = true;

	return true;
}

void TestGame::OnFrame() {
	if (KeyDown(DIK_ESCAPE))
		PostQuitMessage(0);
}

void TestGame::OnDraw() {
	wstringstream ss;

	ss << ZAK_ENGINE_NAME << endl << "FPS: " << _fpsMeter.GetFps() << endl;
	g_renderer.SetFontColor(0xFFFF0000);
	g_renderer.DrawString(ss.str(),10,10,800-20,600-20,ZAK_TEXT_LEFT);
}

bool TestGame::OnShutdown() {
	return true;
}
\endcode

\code
// main.cpp
#include "game.h"

using namespace zak;

//#define USING_DIRECTX81

#ifdef USING_DIRECTX81

#ifdef _DEBUG
#pragma comment (lib, "zakengine81d.lib")
#else
#pragma comment (lib, "zakengine81.lib")
#endif

#else

#ifdef _DEBUG
#pragma comment (lib, "zakengined.lib")
#else
#pragma comment (lib, "zakengine.lib")
#endif

#endif

int main () {
	string desc;
	TestGame game;
	GameConfig config;

	if (!config.Load("config.ini"))
		return false;

	if (game.StartUp(&config)) {
		game.Loop();
	} else {
		game.Shutdown();

		MessageBoxA(g_window.GetHWnd(),Log.GetLastMessage(),"Error",MB_ICONERROR|MB_OK);

		return 1;
	}

	if (!game.Shutdown()) {

		MessageBoxA(g_window.GetHWnd(),Log.GetLastMessage(),"Error",MB_ICONERROR|MB_OK);
		return 1;
	}
	
	return 0;
}
\endcode
 */


#include "console.h"
#include "Renderer.h"
#include "ConfigFile.h"
#include "FileLog.h"
#include "Shape.h"
#include "Game.h"
#include "Sprite.h"
#include "Input.h"
#include "Font.h"
#include "Map.h"
#include "MathUtil.h"
#include "Particle.h"
#include "SoundMgr.h"
#include "ScriptMgr.h"
#include "widgets.h"
#include "GameConfig.h"


#endif // _H_