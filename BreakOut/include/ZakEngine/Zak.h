#ifndef _ZAK_H_
#define _ZAK_H_

/*! \mainpage Documentación de Zak Engine
 *
 * \section intro_sec Introducción al motor
 *
 * El nombre surgió en honor a la memorable aventura gráfica “Zak McKracken and the Alien Mindbenders” de la empresa LucasFilm, donde “Zak McKracken” es el nombre del protagonista y apodo que utilizo desde hace ya muchos años.
 *
 * El Zak Engine es un motor basado en DirectX 8.1 y DirectX 9.0 desarrollado para facilitar la creación de juegos 2d. Entre sus facultades en constante crecimiento se encuentran:

    - Sprites animados
    - Mapas de tiles generados a partir del formato de los editores Anaconda Map Editor y Mappy
    - Sonido y música en diversos formatos (wav, mp3, ogg, etc) a través de la librería gratuita Audiere
    - Sistema de scripting (AngelScript)
    - Bitmap Fonts creados a partir de la aplicación Bitmap Font Creator
    - Sistema de partículas
    - Controles visuales (botones, cajas de edición de textos, ventanas, etc).
    - Sistema de red cliente/servidor para juegos multijugador basado en la librería gratuita Enet

 * Esta librería es completamente gratuita para uso comercial y no comercial siempre y cuando se cumplan los requisitos que indica la \ref licence_sec. Espero que sea de su utilidad y no dude en contactarse ante cualquier duda, sugerencia o bug encontrado en <a href="http://www.zakengine.com">http://www.zakengine.com/</a href>.
 * 
 * Puede ver la lista de \ref changes_page.
 *
 * Además, para crear su primera clase Game puede ver el \ref tutorial1_page.
 *
 * \section licence_sec Licencia

LICENCIA ZAK ENGINE

Por medio de la presente licencia, Juan Pablo Bettini le otorga a usted, el desarrollador, el derecho a utilizar el kit de desarrollo y la librería “Zak Engine” libre de cargo para la creación de software comercial y no comercial siempre y cuando se cumpla con todos los requisitos que este documento establece.

VISUALIZACIÓN DEL LOGOTIPO DE ZAK ENGINE

La aplicación (ej: videojuego) que utilice el “Zak Engine” deberá visualizar como primer imagen, el logotipo del “Zak Engine” durante un período no menor a cuatro segundos.

El logotipo se encuentra incluido y deberá ser visualizado sin modificación alguna de forma, color o tamaño.

SIN GARANTÍAS

El software es provisto “como está”, sin garantía alguna de ningún tipo, bien expresa o implícita, con inclusión, pero sin limitación a las garantías mercantiles implícitas o a la conveniencia para un propósito particular.

Cualquier riesgo referente a la calidad y prestaciones del programa es asumido por usted. Si se probase que el Programa es defectuoso, asume el coste de cualquier servicio, reparación o corrección.

 * \section author_sec Sobre el autor
Mi nombre es Juan Pablo Bettini, soy Argentino nacido en Bahía Blanca, provincia de Buenos Aires. Hoy en día vivo en Capital Federal. Comencé en la programación a la muy temprana edad de 8 años con mi Commodore 64. A lo largo de mi vida pasé por muchos lenguajes de programación como el Basic, Assembler x86, Modula, Pascal, Delphi, Java, C, C++, Action Script, Lingo, entre otros. Me recibí de Programador Profesional de Juegos en Image Campus en diciembre del 2004. Trabajé en Games And Web desarrollando videojuegos para Cartoon Network. Actualmente me dedico a dar clases de programación en el instituto donde me recibí. También estoy escribiendo un libro sobre el desarrollo de videojuegos para la editorial MP Ediciones. Además, continúo en el rubro trabajando freelance y en proyectos personales.

\page changes_page Cambios en versiones
v1.0
- Se arregló un bug en el método ToggleMouseExclusive de la clase Input
- Se arregló un bug en la clase Entity2D
- Se agregaron los métodos Tan, ATan, ASin, ACos y Round a la clase MathUtil 
- Se agregó la posibilidad de modificar el pivot en el emisor de particulas

v1.0.0.0 RC 6 Patch
- Se arregló un bug en MouseRelPos que se sumó en RC6

v1.0.0.0 RC 6
- Se arregló un bug en MouseWorldPos
- Se arregló un bug en MouseRelPos

v1.0.0.0 RC 5
- Se arregló el cálculo de los UV de las texturas de los mapas y sprites
- Se agregó la posibilidad de utilizar #include en scritps
- Se hicieron modificaciones menores en la clase Entity2D
- Se agregaron las funciones RadToDegree y DegreeToRad al motor de scripts
- Se implementó la registración de clases y métodos escalonada en el motor de script
- Se recompiló la librería AngelScript para que evitar el log a disco
- Se agregaron las opciones TextureFilter y TextureMipFilter al archivo de definición de sprites que permite seleccionar los diferentes filtros para las texturas
- Se arregló un bug en la clase Input (posición del mouse en el mundo)

v1.0.0.0 RC 4 Patch
- Se arregló el cálculo de los UV de las texturas de los mapas y sprites

v1.0.0.0 RC 4
- Se arregló un bug en la clase Game que si no le pasamos la configuración lanzaba una violación de acceso
- Se arregló un bug en la clase Texture Manager al remover las texturas
- Se arregló un bug en la clase Input que invertía el mouse verticalmente en MouseWorldPos
- Se arregló un bug en la consola 

v1.0.0.0 RC 3
- Se agregó que si está activada la propiedad CollisionVisible se dibuje al momento de dibujar el sprite.
- Se agregó el dibujado del área de colisión circular
- Se agregó la posibilidad de cargar sonidos por tipo efecto sonoro o música para poder modificar el volumen por tipo
- Se modificó la clase Sprite de manera tal de poder funcionar también como un Shape
- Se actualizó la librería AngelScript a la versión 2.8.0a
- Se creó un sistema de consola in-game
- Se arregló un bug en el método SetAngleZ y GetAngleZ
- Se optimizaron las rotaciones
- Se registró la clase Entity2D en el motor de script
- Se arregló un bug que al hacer resetear el dispositivo D3D no se liberaban las texturas y cortaba la ejecución (Gracias Jonee)
- Se modificó la clase TextureManager para que use un vector de texturas
- Se eliminó la clase EntityList
- Se agregó la clase GameConfig que permite, si así lo deseamos, cargar y guardar la configuración del motor desde el archivo .ini
- Se arregló un bug en la clase SoundMgr y Sound
- Se agregó el método virtual OnLostDevice en la clase Game que será invocado al perderse el dispositivo D3D ante un ALT+TAB

v1.0.0.0 RC 2
- Se agregó en la clase Map la posibilidad de cargar, mostrar y hacer uso de mapas en formato .AMF (AnaConda Map Editor) 
- Ahora es posible descargar las texturas cargadas de memoria RAM y de video por medio del método Unload
- Se arreglo un bug en el método SetToPreviousPos de la clase Entity2D (Gracias NEXUS)

v1.0.0.0 RC 1
- Se arregló un bug en la clase Input donde la posición relativa del mouse en modo no exclusivo no coincidía con la posición absoluta
- Se arregló un bug en el método FlipVertical de la clase Sprite que a veces no invertía verticalmente
- Se agregaron dos variables en el archivo de definición de los sprites: OffsetX y OffsetY que permiten decidir en qué posición de la textura están las figuras
- Se agregó la variable CollisionRadius en el archivo de definición de sprites que permite indicar el radio de colisión del mismo
- Se agregó un método GetAnimation a la clase Sprite que devuelve un puntero a la animación actual
- Se agregaron los métodos GetTileNumCount, GetWorldCoordsFromTile y GetColRowFromTile en la clase Map
- Se modificó la clase Window para que el area de cliente sea del tamaño indicado y no menor (Gracias Santiago Isidro!)
- Se arregló el bug que no permitía readquirir el foco de la ventana con un click del mouse
- Se agregó la variable Set a la clase Font que permite seleccionar el set de fuentes a mostrar
- Se agregaron los métodos getRepeat, getLength, getPosition, setPosition, setPan, getPan, reset e isPlaying a la clase Sound
- Se separaron las librerías del motor con las de red para evitar confusiones en las dependencias entre ambas

v0.3.4.3
- Ahora se muestran los fonts de debug en DirectX 8.1
- Se agregó un método IsEnabledSystem para determinar si el sistema de partículas esta activado o no

v0.3.4.2
- Se agregó una clase estática MathUtil que permite tomar senos, cosenos y números aleatorios a partir de una tabla utilizando los métodos SinCos y Random
- Se optimizaron las clases Entity2D y ParticleSystem
- Se arregló un bug que no permitía quitar la sincronización vertical en pantalla completa
- Se agregó un método SetCursorFromFile en la clase Window que permite la carga de un puntero del mouse personalizado

v0.3.4.1
- El mouse ahora es adquirido en modo cooperativo
- Ahora el método MouseAbsPos devuelve la posición del mouse con respecto a la ventana tomada a partir de las coordenadas de windows
- Se recompiló el framework utilizando la versión 2.7.1b del motor de scripting AngelScript
- Ahora el motor está compilado para DirectX81 y DirectX9
- Se agregó la posibilidad de determinar la velocidad de las animaciones de los sprites en FPS por medio de la variable SpeedFPS
- Se agregó el sistema de partículas 
- Se agregaron las constantes DegreeToRad, RadToDegree y PI 
- Ahora es posible cambiar la posición del pivot de un sprite desde el archivo de configuración del mismo

v0.3.3.1
- Se implementó la carga de mapas exportados con el formato .map del editor Anaconda Map Editor
- Se arregló un bug de compatibilidad con múltiples procesadores en la clase FPSMeter 
- Se agregó un método setGlobalVolume a la clase SoundMgr que permite modificar el volumen de todos los sonidos abiertos

v0.3.2.5
- Se arregló un bug en el método DrawString que provocaba un cuelgue aleatorio en el motor.
- Se arregló un bug en el método SetTile que modificaba el tile visualmente pero no lógicamente
- Se modificó el método GetWorldCoordsFromColRow para que devuelva true si la columna y fila dada está dentro del mapa y false en caso contrario

v0.3.2.4
- Se agregó que si el archivo config.ini y msg.ini no existen, se cree uno nuevo sin provocar error

v0.3.2.3
- Se agregó un método GetTileFromColRow en la clase Map para adquirir un tile mediante una columna y una fila del mapa
- Se arregló un bug en el método GetWorldCoordsFromColRow de la clase Map
- Se arregló un bug en la traslación de la clase Entity2D

v0.3.2.2b
- Se agregaron dos métodos a la clase Sound que permiten adquirir y setear el volumen

v0.3.2.2
- Se arregló un bug en la clase Map
- Se implementó sistema de cambio de resolución en tiempo de ejecución
- Se arregló un bug en la clase List (Gracias Juan Manuel Alvarez)
- Se agregaron métodos para adquirir la posición anterior de una entidad GetPreviousPosX, GetPreviousPosY y GetPreviousPos
- Se agregó la posibilidad de forzar la inicialización del motor evitando las opciones del archivo config.ini
- Se agregó el método GetLastMessage en la clase Log que permite leer el último mensaje escrito en el archivo de log

v0.3.2.1
- Se arregló un bug en la clase Map
- Se implementó el sistema de Scripting y está funcionando (AngelScript)
- Se implementó el sistema de red por medio de paquetes UDP utilizando la librería gratuita ENet
- Se reimplementó la clase List

v0.3.1.11
- Se arregló un bug en la clase Message
- Se implementó una clase para el manejo de redes a través de la librería Enet por paquetes UDP
- Se agregó la propiedad Spacing a la clase Font para permitir la parametrización del espaciado de los Bitmap Fonts
- Se agregó la macro KeyEvent en la clase Input que permite chequear las teclas por eventos Down, Up y Pressed
- Cambió el nombre de la macro para verificar si una tecla está presionada de KeyDown a KeyPressed

v0.3.1.10
- Se arregló el bug de la clase Sprite que no permitía mostrar un frame en particular con el método SetFrame
- Se implementó la clase Font que permite dibujar en pantalla Bitmap Fonts creados a partir del programa Bitmap Font Creator (gracias Thom Wetzel, Jr)
- Se arregló el bug en la toma de valores enteros negativos durante el parseo de archivos .ini en la clase ConfigFile

v0.3.1.9
- Varias optimizaciones
- Aparentemente se arregló el problema visual en modo ventana y pantalla completa (Gracias Santiago Isidro)
- Se invirtió el eje Y en el mouse para que coincida con el eje Y de la pantalla
- Se agregaron las propiedades de posición del pívot en X e Y

v0.3.1.8
- Se agregó el flipeo horizontal y vertical de las entidades.
- Se optimizó la actualización y el dibujado de las entidades.
- Ahora la clase Input enumera los dispositivos de entrada y adquiere la información de todos ellos.
- Adquisición del estado de los joysticks.

v0.3.1.7
- Cambio en el método Draw de las entidades. Ahora no es necesario pasarle el deltaT por parámetro.
- Se agregaron dos métodos más en la clase Entity2D que permiten cambiar la posición en X y en Y independientemente.
- Se agregó un método SetTile en la clase mapa que permite cambiar un tile en particular.
- Se implementó la carga de animaciones desde un archivo de definición.
- Arreglo de un bug que al tratar de apagar el motor cuando falló la inicialización daba una violación de acceso.

v0.3.1.6
- Arreglo de un bug al mostrar el área de colisión de un Sprite.
- Se agregaron las opciones de cambio de tamaño de las áreas de colisión desde el archivo de definición de los Sprites.
- Se modificó el nombre del tipo enumerador de ShapeTYPE a ShapeType.
- Se cambió el sistema de Update de los Shapes y los Sprites. 

v0.3.1.5
- Arreglo de algunos bugs en la carga de archivos de definición de los sprites (gracias Alejandro Luna).
- Arreglo de un bug al mostrar un sprite que no pudo ser cargado (se colgaba la aplicación).
- Arreglo de un bug en el parser de archivos de definición.
- Arreglo de mensajes de error en el log sobre archivos que no pueden ser cargados.
- Se implementó un sistema de scripting a través de AngelScript (no testeado).

v0.3.1.4
- Se implementó el sistema de carga de texturas en modo no persistente.
- Arreglo de un bug referente a la recarga de las texturas ante un ALT+TAB.
- Cambio en parte de algunos headers del motor por el problema con las carpetas relativas (Gracias Gabriel Beranger). 
- Arreglo de un par de bugs del sonido. Además se agregó la opción en el config.ini que permite apagar el sonido.

v0.3.1.3
- Se implementaron las clase SoundMgr y Sound embebiendo la librería Audiere.
- Se implementó el sistema de recuperación del dispositivo D3D y recarga de texturas ante un ALT+TAB.

v0.3.0.0
- Primera versión del motor 2d.


\page tutorial1_page Tutorial 1 - Cómo crear la clase principal del juego

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