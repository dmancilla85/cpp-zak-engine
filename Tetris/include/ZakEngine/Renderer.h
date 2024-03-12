// El config file se lee en el metodo Startup de esta clase

#ifndef _Renderer_H_
#define _Renderer_H_

#include "dxtypes.h"

#ifndef USING_DIRECTX81

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")

#else

#pragma comment(lib, "d3d8.lib")
#pragma comment(lib, "d3dx8.lib")
#pragma comment(lib, "dxguid.lib")

#endif

#include <vector>

#include "Defines.h"
#include "MathUtil.h"
#include "Window.h"
#include "ConfigFile.h"
#include "FileLog.h"
#include "VertexBufferManager.h"

using namespace std;

#define D3DFVF_ZAKVERTEX    (D3DFVF_XYZ|D3DFVF_DIFFUSE)
#define D3DFVF_ZAKTEXVERTEX (D3DFVF_XYZ|D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0))

#define ZAK_TEXT_BOTTOM		 DT_BOTTOM
#define ZAK_TEXT_CALCRECT	 DT_CALCRECT
#define ZAK_TEXT_CENTER		 DT_CENTER
#define ZAK_TEXT_EXPANDTABS	 DT_EXPANDTABS
#define ZAK_TEXT_LEFT		 DT_LEFT
#define ZAK_TEXT_NOCLIP		 DT_NOCLIP
#define ZAK_TEXT_RIGHT		 DT_RIGHT
#define ZAK_TEXT_RTLREADING	 DT_RTLREADING
#define ZAK_TEXT_SINGLELINE  DT_SINGLELINE
#define ZAK_TEXT_TOP		 DT_TOP
#define ZAK_TEXT_VCENTER	 DT_VCENTER
#define ZAK_TEXT_WORDBREAK	 DT_WORDBREAK

namespace zak {

struct Formats
{
	char szFormat[32];
	D3DDEVTYPE d3dType;
	D3DFORMAT d3dFormat;
	BOOL bWindowed;
};

class TextureInfo{
	public:
		char * szFileName;
		char * pData;
		unsigned int texColorKey;
		int iMipLevels;
		unsigned int uiTexWidth;
		unsigned int uiTexHeight;
		unsigned int size;
		bool persist;

	TextureInfo()
	{
		pData = NULL;
		szFileName = NULL;
		texColorKey = 0;
		iMipLevels = 0;
		uiTexWidth = 0;
		uiTexHeight = 0;
		size = 0;
		persist = false;
	}
};

enum RenderStates {
	ZAK_RENDER_STATE_BLEND = 0,
	ZAK_RENDER_STATE_BLENDFUNCBRIGHT
};


class ZAKENGINE_API TexVertex {
	private:
		float _fX,_fY,_fZ;
		float _fU, _fV;

	public:
		void SetVal(float fX, float fY, float fZ, float fU, float fV);

		float GetValX() {
			return _fX;
		}

		float GetValY() {
			return _fY;
		}

	TexVertex();
};

class ZAKENGINE_API ColorVertex {

	private:
		float _fX,_fY,_fZ;
		DWORD _dwColor;

	public:
		void SetVal(float fX, float fY, float fZ, DWORD dwColor);

		float GetValX() {
			return _fX;
		}

		float GetValY() {
			return _fY;
		}

	ColorVertex();
};

enum DRAWPRIMITIVES
{
	ZAK_PRI_POINTLIST=0,
	ZAK_PRI_LINELIST,
	ZAK_PRI_LINESTRIP,
	ZAK_PRI_TRIANGLELIST,
	ZAK_PRI_TRIANGLESTRIP
};

enum MATRIX_MODES {
	ZAK_WORLD_MATRIX=0,
	ZAK_VIEW_MATRIX,
	ZAK_PROJECTION_MATRIX,
	ZAK_TEXTURE_MATRIX
};

enum ZAK_FONT_TYPES {
	FT_ARIAL = 0,
	FT_COURIER,
	FT_TIMES,
	FT_VERDANA,
	FT_TAHOMA
};

class ENTITY;

/**
 *  Clase que encapsula la comunicación con DirectX
 *  @author Juan Pablo "McKrackeN" Bettini
 */
class ZAKENGINE_API Renderer {
	public:

		void BindTexture(DX_LPTEXTURE pBitmapTexture);

		DX_LPTEXTURE LoadTexture(TextureInfo * pTexInfo, DWORD filter=2, DWORD mipFilter=2);
		unsigned int GetViewPortHeight();
		unsigned int GetViewPortWidth();

		/**
		 *  Devuelve los bits por píxel (32 o 16) que están activados
		 *  @return Devuelve los bits por píxel (32 o 16) que están activados
		 */
		int	 GetBits() {
			return _iBits;
		}

		/**
		 *  Devuelve si la aplicación está corriendo a pantalla completa o no
		 *  @return Devuelve true si la aplicación está corriendo a pantalla completa o false en caso contrario
		 */
		bool GetFullscreen() { return _fullScreen; }

		/**
		 *  Carga la identidad en la matriz seleccionada actualmente
		 */
		void LoadIdentity();

		/**
		 *  Aplica la escala a la matriz actual
		 *  @param fX componente X de la escala
		 *  @param fY componente Y de la escala
		 */
		void Scale(float fX, float fY);

		/**
		 *  Aplica la traslación a la matriz actual
		 *  @param fX componente X de la traslación
		 *  @param fY componente Y de la traslación
		 *  @param fZ componente Z de la traslación
		 */
		void Translate(float fX, float fY, float fZ);

		/**
		 *  Aplica la rotación en el eje Z a la matriz actual
		 *  @param fAngle ángulo de rotación en grados centígrados
		 */
		void RotationZ(float fAngle);

		/**
		 *  Apila la matriz actual
		 */
		void PushMatrix();

		/**
		 *  Desapila la matriz actual
		 */
		void PopMatrix();

		/**
		 *  Selecciona la matriz actual.
		 *  @param matType Tipo de matriz (mundo, vista o proyección) indicado por el enumerador MATRIX_MODES
		 */
		void SetMatrixMode(enum MATRIX_MODES matType) {
			_CurrentMatrixMode=matType;
		}

		/**
		 *  Selecciona la fuente actual del texto de debug
		 *  @param ft Tipo de fuente definido por el tipo ZAK_FONT_TYPES
		 */
		bool SetFont(ZAK_FONT_TYPES ft, int size=15);

		/**
		 *  Permite indicar el color de fuente
		 *  @param color color de la fuente
		 */
		void SetFontColor(unsigned int color) { _color = color; }

		/**
		 *  Devuelve la fuente actual
		 *  @return Retorna el tipo de fuente definido por el tipo ZAK_FONT_TYPES
		 */
		ZAK_FONT_TYPES GetFont();

		/**
		 *  Permite mostrar texto de debug en pantalla 
			\verbatim
		      x       
		      |
		   y -+-----------------+ -
		      | texto           | .
		      |                 | . h
		      |                 | .
		      |                 | .
		      +-----------------+ -
		      |.................|
		               w
		 
		    Alineaciones posibles:

			ZAK_TEXT_BOTTOM		 
			ZAK_TEXT_CALCRECT	 
			ZAK_TEXT_CENTER		 
			ZAK_TEXT_EXPANDTABS	 
			ZAK_TEXT_LEFT		 
			ZAK_TEXT_NOCLIP		 
			ZAK_TEXT_RIGHT		 
			ZAK_TEXT_RTLREADING	 
			ZAK_TEXT_SINGLELINE  
			ZAK_TEXT_TOP		 
			ZAK_TEXT_VCENTER	 
			ZAK_TEXT_WORDBREAK	 
		   
		   \endverbatim
		 *  @param text texto a mostrar del tipo wstring
		 *  @param x posición de pantalla en x del comienzo de la caja de texto donde se encontrará el mismo
		 *  @param y posición de pantalla en y del comienzo de la caja de texto donde se encontrará el mismo
		 *  @param w ancho de la caja de texto donde se encontrará el mismo
		 *  @param h alto de la caja de texto donde se encontrará el mismo
		 *  @param align alineación que llevará el texto que puede ser
		 */
		void DrawString(wstring &text, float x, float y, float w, float h, unsigned int align=ZAK_TEXT_LEFT);

		/**
		 *  Permite mostrar texto de debug en pantalla 
			\verbatim
		      x       
		      |
		   y -+-----------------+ -
		      | texto           | .
		      |                 | . h
		      |                 | .
		      |                 | .
		      +-----------------+ -
		      |.................|
		               w
		 
		    Alineaciones posibles:

			ZAK_TEXT_BOTTOM		 
			ZAK_TEXT_CALCRECT	 
			ZAK_TEXT_CENTER		 
			ZAK_TEXT_EXPANDTABS	 
			ZAK_TEXT_LEFT		 
			ZAK_TEXT_NOCLIP		 
			ZAK_TEXT_RIGHT		 
			ZAK_TEXT_RTLREADING	 
			ZAK_TEXT_SINGLELINE  
			ZAK_TEXT_TOP		 
			ZAK_TEXT_VCENTER	 
			ZAK_TEXT_WORDBREAK	 
		   
		   \endverbatim
		 *  @param text texto a mostrar del tipo string
		 *  @param x posición de pantalla en x del comienzo de la caja de texto donde se encontrará el mismo
		 *  @param y posición de pantalla en y del comienzo de la caja de texto donde se encontrará el mismo
		 *  @param w ancho de la caja de texto donde se encontrará el mismo
		 *  @param h alto de la caja de texto donde se encontrará el mismo
		 *  @param align alineación que llevará el texto que puede ser
		 */
		void DrawString(string &text, float x, float y, float w, float h, unsigned int align=ZAK_TEXT_LEFT);

		/**
		 *  Permite mostrar texto de debug en pantalla 
			\verbatim
		      x       
		      |
		   y -+-----------------+ -
		      | texto           | .
		      |                 | . h
		      |                 | .
		      |                 | .
		      +-----------------+ -
		      |.................|
		               w
		 
		    Alineaciones posibles:

			ZAK_TEXT_BOTTOM		 
			ZAK_TEXT_CALCRECT	 
			ZAK_TEXT_CENTER		 
			ZAK_TEXT_EXPANDTABS	 
			ZAK_TEXT_LEFT		 
			ZAK_TEXT_NOCLIP		 
			ZAK_TEXT_RIGHT		 
			ZAK_TEXT_RTLREADING	 
			ZAK_TEXT_SINGLELINE  
			ZAK_TEXT_TOP		 
			ZAK_TEXT_VCENTER	 
			ZAK_TEXT_WORDBREAK	 
		   
		   \endverbatim
		 *  @param text texto a mostrar del tipo char* terminada en \0
		 *  @param x posición de pantalla en x del comienzo de la caja de texto donde se encontrará el mismo
		 *  @param y posición de pantalla en y del comienzo de la caja de texto donde se encontrará el mismo
		 *  @param w ancho de la caja de texto donde se encontrará el mismo
		 *  @param h alto de la caja de texto donde se encontrará el mismo
		 *  @param align alineación que llevará el texto que puede ser
		 */
		void DrawString(char* text, float x, float y, float w, float h, unsigned int align=ZAK_TEXT_LEFT);


		/**
		 *  Activa la modulación del color
		 *  Ejemplo de uso:
		 \code
				g_renderer.EnableModulate();
				g_renderer.SetModulationColor(0xFFFF0000); // selecciono el color rojo
				
				// Dibujo los elementos que serán coloreados

				g_renderer.DisableModulate();
		 \endcode
		 */
		void EnableModulate() {
			_pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_MODULATE);
			_pD3DDevice->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
			_pD3DDevice->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_TFACTOR);

			_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
			_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
			_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_TFACTOR);
		}

		/**
		 *  Permite la selección del color de modulación
		 *  Ejemplo de uso:
		 \code
				g_renderer.EnableModulate();
				g_renderer.SetModulationColor(0xFFFF0000); // selecciono el color rojo
				
				// Dibujo los elementos que serán coloreados

				g_renderer.DisableModulate();
		 \endcode
		 */
		void SetModulationColor(DWORD dwColor) {
			_pD3DDevice->SetRenderState(D3DRS_TEXTUREFACTOR, dwColor);
		}

		/**
		 *  Desactiva la modulación del color
		 *  Ejemplo de uso:
		 \code
				g_renderer.EnableModulate();
				g_renderer.SetModulationColor(0xFFFF0000); // selecciono el color rojo
				
				// Dibujo los elementos que serán coloreados

				g_renderer.DisableModulate();
		 \endcode
		 */
		void DisableModulate() {
			_pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_MODULATE);
			_pD3DDevice->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
			_pD3DDevice->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_CURRENT);

			_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_SELECTARG1);
			_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
			_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_CURRENT);
		}

		void SetMinFilter(unsigned int stage, DWORD filter)
		{
			#ifdef USING_DIRECTX81
				_pD3DDevice->SetTextureStageState(stage, D3DTSS_MINFILTER, filter);
			#else 
				_pD3DDevice->SetSamplerState(stage, D3DSAMP_MINFILTER, filter);
			#endif
		}
		
		void SetMagFilter(unsigned int stage, DWORD filter)
		{
			#ifdef USING_DIRECTX81
				_pD3DDevice->SetTextureStageState(stage, D3DTSS_MAGFILTER, filter);
			#else 
				_pD3DDevice->SetSamplerState(stage, D3DSAMP_MAGFILTER, filter);
			#endif
		}


		/**
		 *  Permite indicar la posición de mundo de la vista.
		 *  @param fPosX posición de mundo en el eje X de la vista
		 *  @param fPosY posición de mundo en el eje Y de la vista
		 */
		void SetViewPosition(float fPosX, float fPosY) {
			_fViewPosX = fPosX;
			_fViewPosY = fPosY;

			D3DXVECTOR3 d3dvEyePos   (MathUtil::Round(fPosX), MathUtil::Round(fPosY), -5.0f);
			D3DXVECTOR3 d3dvLookPos  (MathUtil::Round(fPosX), MathUtil::Round(fPosY),  0.0f);
			D3DXVECTOR3 d3dvUpVector (0.0f,  1.0f,   0.0f);

			SetMatrixMode(ZAK_VIEW_MATRIX);

			D3DXMatrixLookAtLH(&_theMatrix,&d3dvEyePos,&d3dvLookPos, &d3dvUpVector);

			_pD3DDevice->SetTransform(D3DTS_VIEW,&_theMatrix);
		}

		/**
		 *  Devuelve la posición de mundo de la vista.
		 *  @param fPosX posición de mundo en el eje X de la vista
		 *  @param fPosY posición de mundo en el eje Y de la vista
		 */
		void GetViewPosition(float &fPosX, float &fPosY) {
			fPosX = _fViewPosX;
			fPosY = _fViewPosY;
		}

#ifndef USING_DIRECTX81
		/**
		 *  Activa el scissor que permite dibujar solo en el area indicada por SetScissor
		 */
		void EnableScissor() {
			_pD3DDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
		}

		/**
		 *  Desactiva el scissor
		 */
		void DisableScissor() {
			_pD3DDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
		}

		/**
		 *  Permite indicar el recuadro en coordenadas de pantalla donde se quiere dibujar.
		 *  Lo que quede fuera del recuadro será ignorado.
		 *	@param rect un puntero a un tipo RECT que definirá el rectángulo
		 *  @return devuelve true en caso de ser un rectángulo válido y false en caso contrario
		 */
		bool SetScissor(CONST RECT *rect) {
			if (_pD3DDevice->SetScissorRect(rect) != D3D_OK)
				return false;

			return true;
		}
#endif 
		void GetWorldRect(RECT &Rect) {
			D3DXMATRIX mProj;
			_pD3DDevice->GetTransform(D3DTS_VIEW, &_theMatrix);
			_pD3DDevice->GetTransform(D3DTS_PROJECTION, &mProj);

			float fx = _theMatrix(3,0);
			float fy = _theMatrix(3,1);

			Rect.left   = (LONG) (-fx - 1/mProj(0,0));
			Rect.right  = (LONG) (-fx + 1/mProj(0,0));
			Rect.top    = (LONG) (-fy + 1/mProj(1,1));
			Rect.bottom = (LONG) (-fy - 1/mProj(1,1));
		}

		/**
		 *  Permite activar un estado definido por el tipo RenderStates
		 *	@param eRenderState estado que se desea activar
		 */
		void EnableState(RenderStates eRenderState) {
			if (eRenderState == ZAK_RENDER_STATE_BLEND) {
				_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			} else if (eRenderState == ZAK_RENDER_STATE_BLENDFUNCBRIGHT) {
				_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			}
		}

		/**
		 *  Permite desactivar un estado definido por el tipo RenderStates
		 *	@param eRenderState estado que se desea desactivar
		 */
		void DisableState(RenderStates eRenderState) {
			if (eRenderState == ZAK_RENDER_STATE_BLEND) {
				_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
			} else if (eRenderState == ZAK_RENDER_STATE_BLENDFUNCBRIGHT) {
//				_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
				_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
				_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			}
		}

		/**
		 *  Permite procesar y dibujar en pantalla un arreglo de vértices de color (ColorVertex)
		 *	@param VertexCollection arreglo de vértices que se desea mostrar
		 *  @param ePrim tipo de primitiva definida por DRAWPRIMITIVES
		 *  @param uiVertexCount cantidad de vértices en total
		 */
		void Draw(ColorVertex * VertexCollection, DRAWPRIMITIVES ePrim, unsigned int uiVertexCount);

		/**
		 *  Permite procesar y dibujar en pantalla un arreglo de vértices texturados (TexVertex)
		 *	@param VertexCollection arreglo de vértices que se desea mostrar
		 *  @param ePrim tipo de primitiva definida por DRAWPRIMITIVES
		 *  @param uiVertexCount cantidad de vértices en total
		 */
		void Draw(TexVertex * vertexCollection, DRAWPRIMITIVES prim, unsigned int uiVertexCount);

		void DrawLine(float x1, float y1, DWORD c1, float x2, float y2, DWORD c2);

		/**
		 *  Inicializa DirectX
		 *	@param iAncho ancho de la resolución de pantalla
		 *  @param iAlto alto de la resolución de pantalla
		 *  @param iBits bits de color
		 *  @param bFullScreen si deseamos pantalla completa o no
		 *  @param refreshRate ciclos de refresco expresados en hertz
		 *  @param vsync si deseamos activar la sincronización vertical o no
		 */
		bool Startup (unsigned int iAncho, unsigned int iAlto, int iBits, bool bFullScreen, int refreshRate, bool vsync);

		/**
		 *  Apaga el DirectX
		 */
		void ShutDown();

		/**
		 *  Comienzo del dibujado de la escena
		 */ 
		void BeginScene() {
			HRESULT hr = _pD3DDevice->BeginScene();
		}

		/**
		 *  Fin del dibujado de la escena
		 */ 
		void EndEscene() {
			_pD3DDevice->EndScene();
		}

		/**
		 *  Borrar todas las texturas
		 */ 
		void ClearTextures();

		/**
		 *  Selección del color con el que se rellenará la pantalla al borrarla
		 */ 
		void SetClearColor(D3DCOLOR ClearColor);

		/**
		 *  Borrado de pantalla
		 */ 
		void Clear() {
			_pD3DDevice->Clear(0,NULL,D3DCLEAR_TARGET, _ClearColor,1.0f,0);
		}

		/**
		 *  Presenta la escena en pantalla
		 */ 
		void Present(void) {
			if (_pD3DDevice->Present(NULL,NULL,NULL,NULL) != D3D_OK) {
				_deviceLost = true;
			}
		}

		/**
		 *  Cambio de resolución en tiempo real
		 */ 
		bool ChangeResolution(unsigned int uiAncho, unsigned int uiAlto, int iBits, bool bFullScreen, int refreshRate, bool vsync);

		DX_LPDIRECT3DDEVICE GetDevice() { return _pD3DDevice; }

		void Register(ENTITY* entity) { _entities.push_back(entity); }
		void Unregister(ENTITY* entity);

	Renderer();
	~Renderer();

	private:
		friend class Game;

		ID3DXFont*		_pDefDXFont;
		ZAK_FONT_TYPES	_pDefDXFontType;
		D3DCOLOR		_color;

		vector<Formats*> _validFormats;

		vector<ENTITY*>	_entities;

		int		_width;
		int		_height;
		int		_bits;
		bool	_fullScreen;
		int		_refreshRate;
		bool	_vsync;



		D3DPRESENT_PARAMETERS	D3DPresentParameter;
		bool					_deviceLost;
		//LPDIRECT3DSURFACE9		_BackSurface;

		D3DCOLOR				_ClearColor;
		float					_fViewPosX;
		float					_fViewPosY;

		int						_iBits;

		D3DFORMAT				_d3DFormat;

		DX_VIEWPORT				vp;//objeto tipo viewport

		DX_LPDIRECT3D			_pD3D;
		DX_LPDIRECT3DDEVICE		_pD3DDevice;
		DX_LPVERTEXBUFFER		_pD3DVertexBuffer;


		MATRIX_MODES			_CurrentMatrixMode;

		D3DXMATRIX _theMatrix;

		//Pila de matrices
		LPD3DXMATRIXSTACK		_pWorldMatrixStack;
		LPD3DXMATRIXSTACK		_pProjectionMatrixStack;
		LPD3DXMATRIXSTACK		_pViewMatrixStack;
		LPD3DXMATRIXSTACK		_pTextureMatrixStack;

		D3DPRIMITIVETYPE		_PrimitiveVector[5];

		ConfigFile			*_ConfigFile;

		VertexBufferManager<ColorVertex,D3DFVF_ZAKVERTEX>		_VertexBufferManager;
		VertexBufferManager<TexVertex,D3DFVF_ZAKTEXVERTEX>	_VertexBufferTexManager;

		DX_LPTEXTURE			_pCurrentBitmapTexture;

		bool IniciarDX		(unsigned int uiAncho, unsigned int uiAlto, int iBits, bool bFullScreen, int refreshRate, bool vsync);
		void ApagarDX		();
		bool SetupDX		();
		void CheckModes();

		/**
		 *  Devuelve verdadero si se ha perdido el dispositivo de DirectX
		 *	@return devuelve true si se ha perdido el dispositivo DirectX y false en caso contrario
		 */ 
		bool IsDeviceLost() {
			return _deviceLost;
		}

		/**
		 *  Chequea si se perdió el dispositivo de DirectX e intenta recuperarlo
		 *	@return devuelve true si se ha perdido el dispositivo DirectX y false en caso contrario
		 */ 
		bool CheckForLostDevice();

		/**
		 *  Intenta reinicializar el dispositivo de DirectX
		 *	@return devuelve true si todo salio bien y false en caso contrario
		 */ 
		bool Reset() {
			if (_pD3DDevice->Reset(&D3DPresentParameter) != D3D_OK)
				return false;

			return true;
		}
};

extern ZAKENGINE_API Renderer g_renderer;

}

#endif //_Renderer_H_
