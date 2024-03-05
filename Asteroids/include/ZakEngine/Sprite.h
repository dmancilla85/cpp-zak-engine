#ifndef _Sprite_H_
#define _Sprite_H_

//#include "Entity2D.h"
#include "Shape.h"
#include "renderer.h"
#include "TextureManager.h"

namespace zak {

class ZAKENGINE_API Sprite;

class Frame {
	public:
		float _fU, _fV, _fUW, _fUH;
};

/**
 *  Clase de manejo de animaciones para sprites
 *  Ejemplo de uso:
\code
bool TestGame::OnInit() {
	if (!_sprite.LoadIni("./data/graphics/roxy.spr"))
		return false;

	if (!_anim.Load("./data/graphics/example.ani")) {
		return false;
	}

	_sprite.SetAnimation(&_anim);
}
void TestGame::OnFrame() {
	_sprite.Update((float)_fpsMeter.GetDT());
}

void TestGame::OnDraw() {
	_sprite.Draw();
}
\endcode
 *
 * Ejempo de archivo .ani
\code
[SPRITE_ANIMATION]
FramesCount=10 ; Cantidad de cuadros total que posee la animación

Frame0=27 ; FrameX: número de cuadro de la animación - 27: cuadro dentro del bitmap a mostrar
Frame1=27
Frame2=28
Frame3=29
Frame4=30
Frame5=31
Frame6=32
Frame7=33
Frame8=32
Frame9=32

SpeedFPS=25 ; Cuadros por segundo a los que correrá la animación
Looped=true ; Si la animación debe volver a empezar al finalizar o no
\endcode
 *
 *	@author Juan Pablo "McKrackeN" Bettini
 */
class ZAKENGINE_API Animation : protected SupportScriptReferences {
public:
	/**
	 *  Carga un archivo de animación
	 *	@param filename nombre del archivo a cargar
	 *  @return retorna true si todo salió bien y false en caso contrario
	 */
	bool Load(char *filename);

	static bool RegisterAnimation(char *className=NULL);
	
	//Animation(int iSize);
	Animation();
	~Animation();

	friend class Sprite;
	friend class ScriptMgr;

private:
	bool Load(const string &filename);

	int		_iSize;
	float	_fAnimationSpeed;
	bool	_bLoop;
	int		*_iFrameList;

	void SetSize(int iSize)
	{
		if (_iFrameList != NULL) {
			delete [] _iFrameList;
		}
		if (iSize>0)
			_iFrameList = new int [iSize];
		else
			_iFrameList = NULL;
		_iSize = iSize;
	} //prevents frame array redefinition
};

/**
 *  Clase de manejo de  sprites
 *  Ejemplo de uso:
\code
bool TestGame::OnInit() {
	if (!_sprite.LoadIni("./data/graphics/roxy.spr"))
		return false;

	if (!_anim.Load("./data/graphics/example.ani")) {
		return false;
	}

	_sprite.SetAnimation(&_anim);
}
void TestGame::OnFrame() {
	_sprite.Update((float)_fpsMeter.GetDT());
}

void TestGame::OnDraw() {
	_sprite.Draw();
}
\endcode
 *
 * Ejempo de archivo .spr
\code
[SPRITE]
Filename="data/roxy.png" ; Ubicación del bitmap
TextureFilter=0 	; Filtro de textura 0-None 1-Point 2-Linear 3-Triangle 4-Box
TextureMipFilter=0	; Filtro de textura mipmap 0-None 1-Point 2-Linear 3-Triangle 4-Box
MinFilter=0 		; MinFilter 0-None 1-Point 2-Linear 3-Triangle 4-Box
MagFilter=0			; MagFilter 0-None 1-Point 2-Linear 3-Triangle 4-Box
ColorKey=4294967295	; Color que deseamos que sea transparente	
FramesCount=44 ; Cantidad de cuadros de animación en total
FrameWidth=146 ; Ancho de cada frame
FrameHeight=155	; Alto de cada frame
FramesCountPerWidth=7 ; Cantidad de cuadros que hay a lo ancho
OffsetX = 0 ; Offset del comienzo de los cuadros en la textura
OffsetY = 0
PosX=0 ; Posición inicial
PosY=0
PivotPosX=0 ; Posición del Pivot
PivotPosY=0 
Width=48 ; Ancho y alto del sprite en pantalla
Height=48
ScaleX=1.0 ; Escala
ScaleY=1.0
Visible=true ; Visible o no
CheckCollision=false ; Activa el chequeo de colisión
CollisionVisible=false ; Area de colisión visible o no
CollisionWidth=25 ; Ancho de la colisión
CollisionHeight=25 ; Alto de la colisión
Persist=false ; Persistencia de la textura en memoria ram o no
\endcode
 *
 *	@author Juan Pablo "McKrackeN" Bettini
 */
class ZAKENGINE_API Sprite : public Shape {
	private:
	
	protected:
		TexVertex	_sprVertex[4];
		Texture  	*_pTexture;
		float		_fUV[2];		// UV de la textura a usar
		float		_fW;			// Ancho del tile
		float		_fH;			// Alto del tile
		Frame		*_Frames;
		int			_iFramesCount;
		int			_iActualFrame;
		Animation	*_Animation;
		bool		_bAnimationRuning;
		float		_fTime;

		int			_offsetX;
		int			_offsetY;
		float		_offsetU;
		float		_offsetV;

		DWORD		_minFilter;
		DWORD		_magFilter;
		
		void SetUVWH(float fU, float fV, float fW, float fH); // TEMPORAL!!!!! BORRAMEEE!

		bool InitFrames(int iFramesCount, int iFrameWidth, int iFrameHeight,int iFramesCountPerWidth);
		bool Load(const char *pszImageFilename, unsigned int uiColorKey, bool persist = false, DWORD filter=2, DWORD mipFilter=2);
		bool Load(const string& filename) { return LoadIni((char*)filename.c_str()); }

	public:
		/**
		 *  Permite la carga de un sprite a partir de un archivo de definición de sprites
		 *  @param iniFile nombre del archivo a cargar
		 *	@return retorna true si todo salió bien y false en caso contrario
		 */
		bool LoadIni(const char *iniFile);

		/**
		 *  Permite liberar la memoria RAM y de video de la textura cargada
		 *	@return retorna true si todo salió bien y false en caso contrario
		 */
		bool Unload();

		/**
		 *  Permite indicar qué cuadro mostrar
		 *  @param iFrame cuadro a mostrar
		 */
		void SetFrame(int iFrame);

		/**
		 *  Devuelve el cuadro de animación que se está mostrando
		 *  @return cuadro de animación que se está mostrando
		 */
		int GetCurrentFrame(void){return _iActualFrame;}

		/**
		 *  Permite indicar la animación a correr
		 *  @param Animation puntero a la animación a mostrar que, en caso de ser NULL, cortará la animación actual
		 */
		void SetAnimation(Animation *Animation);

		/**
		 *  Devuelve la animación que se está ejecutando
		 *  @return puntero a la animación que está corriendo. En caso de no haber ninguna, retornará NULL.
		 */
		Animation *GetAnimation() { return _Animation; }

		/**
		 *  Devuelve si la animación está corriendo
		 *  @return devuelve true en caso de que la animación esté corriendo y false en caso contrario.
		 */
		bool IsAnimationRunning();

		/**
		 *  Muestra el sprite en pantalla
		 */
		virtual void Draw();

		/**
		 *  Actualiza el sprite y la animación
		 *  @param fTimeBetweenFrames tiempo transcurrido entre iteraciones
		 */
		void Update(float fTimeBetweenFrames);

		static bool RegisterSprite(char *className=NULL);

	/**
	 *  Constructor
	 */
	Sprite();

	/**
	 *  Destructor
	 */
	~Sprite();
};

}

#endif // _Sprite_H_