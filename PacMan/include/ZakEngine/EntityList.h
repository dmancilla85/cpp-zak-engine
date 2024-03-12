#ifndef _ENTITYLIST_H_
#define _ENTITYLIST_H_

#include "Defines.h"
#include "Entity2D.h"

namespace zak {

/**
*  Clase que almacena elementos de cualquier tipo.
*	@author Juan Pablo "McKrackeN" Bettini
*/
class EntityList {
	protected:
		void		**Map;			// puntero a un array de punteros 
									// a objetos tipo void
		int			iActualCursor;
		int			iLastIndice;
		
		int			_iSize;

	public:

		/**
		*	Agrega una entidad a la lista
		*	@param pEntity entidad a adjuntar a la lista
		*	@return Retorna verdadero si fue posible adjuntar la entidad
		*/
		bool Attach(void *pEntity);

		/**
		*	Extrae una entidad de la lista
		*	@param pEntity entidad a extraer de la lista
		*	@return Retorna verdadero si fue posible extraer la entidad
		*/
		bool Detach(void *pEntity);

		/**
		*	Extrae la entidad actual de la lista
		*	@return Retorna verdadero si fue posible extraer la entidad
		*/
		bool DetachActual();

		/**
		*	Apunta a la primera entidad de la lista
		*	@return Retorna verdadero si fue posible apuntar a la primera entidad
		*/
		bool Begin();

		/**
		*	Apunta a la siguiente entidad de la lista
		*	@return Retorna verdadero si fue posible apuntar a la entidad siguiente 
		*/
		bool Next();

		/**
		*	Apunta a la anterior entidad de la lista
		*	@return Retorna verdadero si fue posible apuntar a la entidad anterior 
		*/
		bool Prev();

		/**
		*	Extrae todos los elementos de la lista
		*	@return Retorna verdadero si fue posible extraer las entidades
		*/
		bool DetachAll();

		/**
		*	Devuelve la cantidad de entidades adjuntadas
		*	@return Devuelve la cantidad de entidades adjuntadas
		*/
		int	 GetCount();

		/**
		*	Devuelve la entidad apuntada actualmente
		*	@return Devuelve la entidad apuntada actualmente
		*/
		void *GetEntity();

				
	/**
	*	Constructor
	*	@param iSize tamaño de la lista
	*/
	EntityList(int iSize);

	/**
	*	Destructor
	*/
	~EntityList();
};

}

#endif // _ENTITYLIST_H_
