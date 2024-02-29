  //---------------------------------------------------------------------------  
 
#ifndef CAMEFormatH  
#define CAMEFormatH  

#include "console.h"
#include "defines.h"
#include <fstream>  

using namespace std;

namespace zak {
 
  /**
 *  Clase que contiene las propiedades de un
 *	mosaico de los mapas guardados en formato
 *	AnaConda Map Editor.
 *
 *	@author Juan Pablo "McKrackeN" Bettini
 */
 class ZAKENGINE_API ameBlockInfo  
 
 {  
	 friend class ameHeader;
	 friend class Map;

     void Clear(unsigned short usTileDef);  

 public:  
 
	/**
	 *  Aloja valor del mosaico
	 */
     unsigned short sTileNum;  
 
	/**
	 *  Flags del mosaico
	 */
     unsigned char ucFlags; 

    /**
	 *  8 etiquetas del mosaico de tipo char
	 */
     char szTag1[8];  

    /**
	 *  8 etiquetas del mosaico de tipo char
	 */
     char szTag2[8];  

    /**
	 *  4 etiquetas del mosaico de tipo float
	 */
	 float fValues[4];  
 
 
    /**
	 *  Código del tag que se utiliza para saber 
	 *  que tag represnetar sobre el mosaico
	 *  correspondiente. Nota: -1 significa que el
	 *  mosaico no se encuentra etiquetado
	 */
     short sTagCode;  
 
 
     ameBlockInfo();  
 
     ~ameBlockInfo();  
 
 
 };  
 
  
 /**
 *  Clase que permite cargar y mostrar mapas de mosaicos 
 *	en el formato del editor AnaConda Map Editor. Además 
 *  contiene las etiquetas del mapa que podemos utilizar
 *  en el juego.
 *
 *	@author Juan Pablo "McKrackeN" Bettini
 */
 class ZAKENGINE_API ameHeader  
 
 {  
     // Información General  
 
     unsigned long ulMagic;  
 
     unsigned short usVersion;  
 
  
 public:
    /**
	 *  Información del mapa
	 */
     char szMapName[48];  
 
 private: 
 
     // Nombre del game template (opcional)  
 
     char szGameTemplateName[16];  
 
 public:
 
    /**
	 *  Flags del mapa
	 */
     unsigned char ucFlags;  
 
    /**
	 *  Etiqueta tipo cadena de caracteres
	 */
     char szMapTag1[64];  
 
    /**
	 *  Etiqueta tipo cadena de caracteres
	 */
     char szMapTag2[64];  
 
     /**
	 *  4 etiquetas del mapa de tipo float
	 */
    float fValues[4];  
 
 private:  
 
     // Información del bitmap relacionado al mapa  
 
     char szDefBitmapFile[128];  
 
     unsigned long ulColorKey;  
 
     unsigned short usBitmapWidth;  
 
     unsigned short usBitmapHeight;  
 
     unsigned short usTileWidth;  
 
     unsigned short usTileHeight;  
 
     unsigned short usTileCountX;  
 
     unsigned short usTileCountY;  
 
     unsigned short usDefTileBlock;  
 
	 friend class Map;

 public: 
 
   /**
	 *  Información de los mosaicos
	 */
      ameBlockInfo * pbiBlock;  
 

 

 public:  
   
    /**
	 *  Constructor
	 */
     ameHeader();  
 
    /**
	 *  Destructor
	 */
     ~ameHeader();  
 
    /**
	 *  Limpia todo el mapa
	 */
     void Clear();  
 
    /**
	 *  Carga un mapa
	 *  @param pszFile nombre del archivo a cargar
	 *	@return Retorna true en el caso de que todo salga bien y false en caso contrario
	 */
     bool ReadFile(const char * pszFile);  
 
    /**
	 *  Escribe el mapa 
	 *  @param pszFile nombre del archivo a guardar
	 *	@return Retorna true en el caso de que todo salga bien y false en caso contrario
	 */
     bool WriteFile(const char * pszFile);  
 
    /**
	 *  Inicializa un nuevo mapa
	 *  @param usCountX cantidad de columnas del mapa
	 *  @param usCountY cantidad de filas del mapa
	 *	@return Retorna true en el caso de que todo salga bien y false en caso contrario
	 */
     bool Init(unsigned short usCountX, unsigned short usCountY);  
 };  
 
 } // end namespace

 #endif   
