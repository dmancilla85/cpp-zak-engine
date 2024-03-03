
#ifndef _Map_H_
#define _Map_H_

#include "renderer.h"
#include "Entity2D.h"
#include "TextureManager.h"
#include "AmeFormat.h"
#include <iostream>

#define MAP_TILE_WIDTH		64
#define MAP_TILE_HEIGHT		64

namespace zak {

class Tiles {
	public:
		float _fPosX, _fPosY, _fU, _fV, _fUW, _fUH;
};

/**
 *  Clase que permite cargar y mostrar mapas de mosaicos 
 *	en los formatos de los editores AnaConda Map Editor 
 *  y Mappy.
 *  Ejemplo de uso:
\code
bool TestGame::OnInit() {
	if (!_map.Load("./data/graphics/classic.bmp","./data/graphics/clasic.map",0xFF000000, false))
		return false;

	_map.SetPos(-400,300);
}

void TestGame::OnFrame() {
	_map.Update((float)_fpsMeter.GetDT());
}

void TestGame::OnDraw() {
	_map.Draw();
}
\endcode
 *
 *	@author Juan Pablo "McKrackeN" Bettini
 */
class ZAKENGINE_API Map : public Entity2D {
	private:
		TexVertex	*_Vertex;
		TexVertex	*_TempVert;
		Texture  	*_pTexture;
		float		_fUV[2];		// UV de la textura a usar
		float		_fW;			// Ancho del tile
		float		_fH;			// Alto del tile

		int			_iStartX,_iStartY;
		int			_iCountX,_iCountY;
		int			_iTempCountX,_iTempCountY;

		int			*_cMap;
		ameHeader	*_ame;
		Tiles		*_Tiles;

		int			_iActualTile;
		int			_iTileWidth;
		int			_iTileHeight;

		int			_iWidth;
		int			_iHeight;
		
		bool		_bEnableAlpha;

		bool LoadTexture(const char *pszTextureFilename, unsigned int uiColorKey, bool persist = false, DWORD filter=2, DWORD mipFilter=2); 
		bool LoadMap	(const char *pszMapFilename);
		bool LoadAnacondaMap(const char *pszMapFilename);

	public:
		/**
		 *  Activa el Alpha Blending para dibujar el mapa
		 */
		void EnableAlphaBlend () {
			_bEnableAlpha = true;
		}

		/**
		 *  Desactiva el Alpha Blending para dibujar el mapa
		 */
		void DisableAlphaBlend () {
			_bEnableAlpha = false;
		}

		/**
		 *  Devuelve en ancho de los mosaicos
		 *	@return devuelve un número entero correspondiente al ancho de cada mosaico
		 */
		int	 GetTileWidth() {
			return _iTileWidth;
		}
		/**
		 *  Devuelve en alto de los mosaicos
		 *	@return devuelve un número entero correspondiente al ancho de cada mosaico
		 */
		int	 GetTileHeight() {
			return _iTileHeight;
		}

		/**
		 *  Devuelve la cantidad de columnas que posee el mapa
		 *	@return devuelve un número entero correspondiente a la cantidad de columnas del mapa
		 */
		int GetMapWidth() {
			return _iWidth;
		}
		/**
		 *  Devuelve la cantidad de filas que posee el mapa
		 *	@return devuelve un número entero correspondiente a la cantidad de filas del mapa
		 */
		int GetMapHeight() {
			return _iHeight;
		}

		/**
		 *  Permite modificar el valor de un mosaico en una columna y fila determinadas
		 *	@param col columna en la cual modificar el mosaico
		 *  @param row fila en la cual modificar el mosaico
		 *  @param tileNum número de tile a colocar en la columna y fila determinada
		 */
		void SetTile (int col, int row, int tileNum);

		/**
		 *  Devuelve el valor del mosaico en la posición de mundo dada
		 *	@param x coordenada x de la posición de mundo
		 *  @param y coordenada y de la posición de mundo
		 *	@return devuelve un número entero correspondiente al valor del mosaico en dicha ubicación
		 */
		int GetTileFromWorldCoords(float x, float y);

		/**
		 *  Devuelve el valor del mosaico en la posición en coordenadas de columnas y filas dentro del mapa dada
		 *	@param col columna en el mapa del mosaico correspondiente
		 *  @param row fila en el mapa del mosaico correspondiente
		 *	@return devuelve un número entero correspondiente al valor del mosaico en dicha ubicación
		 */
		int GetTileFromColRow(int col, int row);

		/**
		 *  Transforma una coordenada de mundo en columnas y filas dentro del mapa
		 *	@param x coordenada x de la posición de mundo
		 *  @param y coordenada y de la posición de mundo
		 *	@param col se alojará en esta variable pasada por referencia la columna resultante
		 *  @param row se alojará en esta variable pasada por referencia la fila resultante
		 *	@return devuelve true en caso de que la posición de mundo dada se encuentre dentro del mapa y false en caso contrario
		 */
		bool GetColRowFromWorldCoords(float x, float y, int &col, int &row);

		/**
		 *  Transforma una columna y fila dentro del mapa en coordenadas de mundo
		 *	@param col columna dentro del mapa a transformar
		 *  @param row fila dentro del mapa a transformar
		 *	@param x se alojará en esta variable pasada por referencia la coordenada de mundo x resultante
		 *  @param y se alojará en esta variable pasada por referencia la coordenada de mundo y resultante
		 *	@return devuelve true en caso de que la posición de mundo dada se encuentre dentro del mapa y false en caso contrario
		 */
		bool GetWorldCoordsFromColRow(int col, int row, float &x, float &y);

		/**
		 *  Busca un mosaico en particular y devuelve la columna y fila en la que se encuentra la primer aparición del mismo
		 *	@param tile mosaico a buscar
		 *	@param col columna resultante de la búsqueda
		 *  @param row fila resultante de la búsqueda
		 *	@return devuelve true en caso de haber encontrado el valor del mosaico y false en caso contrario
		 */
		bool GetColRowFromTile(int tile, int &col, int &row);

		/**
		 *  Busca un mosaico en particular y devuelve la posición en coordenadas de mundo en la que se encuentra la primer aparición del mismo
		 *	@param tile mosaico a buscar
		 *	@param x coordenada de mundo x en la que se encuentra el mosaico buscado
		 *  @param y coordenada de mundo y en la que se encuentra el mosaico buscado
		 *	@return devuelve true en caso de haber encontrado el valor del mosaico y false en caso contrario
		 */
		bool GetWorldCoordsFromTile(int tile, float &x, float &y);

		/**
		 *  Devuelve la cantidad de mosaicos del tipo pasado por parámetro
		 *	@param tile tipo de mosaico
		 *	@return devuelve la cantidad de mosaicos del tipo dado encontrados en el mapa
		 */
		int	 GetTileNumCount(int tile);

		/**
		 *  Permite tomar la información completa de un mosaico especificado por una columna y una fila de un mapa del tipo .AMF del AnaConda Map Editor
		 *	@param col columna en la cual se encuentra el mosaico
		 *  @param row fila en la cual se encuentra el mosaico
		 *  @return devuelve un puntero a la información del mosaico. En caso de error, devuelve NULL.
		 */
		ameBlockInfo *GetAmeTileInfoFromColRow(int col, int row);

		/**
		 *  Permite tomar la información completa de un mosaico especificado por una posición en coordenadas de mundo de un mapa del tipo .AMF del AnaConda Map Editor
		 *	@param x componente x de la posición de mundo en la cual se encuentra el mosaico
		 *  @param y componente y de la posición de mundo en la cual se encuentra el mosaico
		 *  @return devuelve un puntero a la información del mosaico. En caso de error, devuelve NULL.
		 */
		ameBlockInfo *GetAmeTileInfoFromWorldCoords(float x, float y);

		/**
		 *  Permite tomar la información completa de un mapa en formato .AMF (AnaConda Map Editor)
		 *  @return devuelve un puntero a la información del mapa. En caso de error, devuelve NULL.
		 */
		ameHeader *GetAmeMapDetails() { return _ame; } 

		/**
		 *  Carga un mapa exportado a .map por el editor Mappy
		 *	@param pszTextureFilename nombre de la textura en la que se encuentran los mosaicos
		 *	@param pszMapFilename nombre del archivo con extensión .map
		 *	@param uiColorKey color clave que no deseamos que se muestre en pantalla
		 *	@param tileWidth ancho de cada mosaico
		 *	@param tileHeight alto de cada mosaico
		 *	@param persist (opcional por defecto false) si deseamos que la textura quede persistente en memoria ram o no
		 *	@return devuelve true en caso de que la carga sea satisfactoria y false en caso contrario
		 */
		bool Load		(const char *pszTextureFilename, const char *pszMapFilename, unsigned int uiColorKey, int tileWidth, int tileHeight, bool persist = false, DWORD filter=2, DWORD mipFilter=2);

		/**
		 *  Carga un mapa exportado a .map por el editor AnaConda Map Editor
		 *	@param pszTextureFilename nombre de la textura en la que se encuentran los mosaicos
		 *	@param pszMapFilename nombre del archivo con extensión .map
		 *	@param uiColorKey color clave que no deseamos que se muestre en pantalla
		 *	@param persist (opcional por defecto false) si deseamos que la textura quede persistente en memoria ram o no
		 *	@return devuelve true en caso de que la carga sea satisfactoria y false en caso contrario
		 */
		bool Load		(const char *pszTextureFilename, const char *pszMapFilename, unsigned int uiColorKey, bool persist = false, DWORD filter=2, DWORD mipFilter=2);

		/**
		 *  Carga un mapa a partir del formato .AMF del editor AnaConda Map Editor
		 *	@param pszTextureFilename nombre de la textura en la que se encuentran los mosaicos
		 *	@param pszMapFilename nombre del archivo con extensión .map
		 *	@param uiColorKey color clave que no deseamos que se muestre en pantalla
		 *	@param persist (opcional por defecto false) si deseamos que la textura quede persistente en memoria ram o no
		 *	@return devuelve true en caso de que la carga sea satisfactoria y false en caso contrario
		 */
		bool LoadAMF	(const char *pszMapFilename, unsigned int uiColorKey, bool persist = false, DWORD filter=2, DWORD mipFilter=2);

		/**
		 *  Permite liberar la memoria RAM y de video de la textura cargada
		 *	@return retorna true si todo salió bien y false en caso contrario
		 */
		bool Unload();

		/**
		 *  Muestra el mapa en pantalla
		 */
		void Draw		();

	/**
	 *  Constructor
	 */
	Map();

	/**
	 *  Destructor
	 */
	~Map();
};

}
#endif // _Map_H_