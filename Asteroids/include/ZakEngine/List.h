#ifndef _LIST_H_
#define _LIST_H_

#include <windows.h>
#include <memory.h>
#include "ZakEngine/defines.h"
#include "ZakEngine/Node.h" 


namespace zak {

template <class LIST_TYPE>

/**
 *  Clase que maneja una lista doblemente enlazada
 *	@author Juan Pablo "McKrackeN" Bettini
 */
class List 
{
	// Get Previous Node of a certain Node
	Node<LIST_TYPE> *Previous(Node<LIST_TYPE> *pNode) 
	{
		if (pNode) {
			if (pNode->GetPreviousNode() != NULL)
				return (m_pActualNode = pNode->GetPreviousNode());
			else
				return NULL;
		} else
			return NULL;
	}

	// Move to the next node
	Node<LIST_TYPE> *Next(Node<LIST_TYPE> *pNode) 
	{
		if (pNode) {
			if (pNode->GetNextNode() != NULL)
				return (m_pActualNode = pNode->GetNextNode());
			else
				return NULL;
		} else
			return NULL;
	}

public:

	/**
	 *  Fuerza a apuntar el puntero al nodo actual al primer elemento de la lista
	 */
	void MoveToFirst(void)
	{
		m_pActualNode = m_pFirstNode;
	}

	/**
	 *  Fuerza a apuntar el puntero al nodo actual al último elemento de la lista
	 */
	void MoveToLast(void)
	{
		m_pActualNode = m_pLastNode;
	}

	/**
	 *  Mueve el puntero al nodo actual al siguiente elemento de la lista
	 *	@return devuelve true si existe un nodo siguiente y false en caso contrario
	 */
	bool MoveToNext(void) 
	{
		if (m_pActualNode = Next(m_pActualNode))
			return true;
		else
			return false;
	}

	/**
	 *  Mueve el puntero al nodo actual al anterior elemento de la lista
	 *	@return devuelve true si existe un nodo anterior y false en caso contrario
	 */
	bool MoveToPrevious(void) 
	{
		if (m_pActualNode = Previous(m_pActualNode))
			return true;
		else
			return false;
	}

	/**
	 *  Busca un elemento en particular pasado por parámetro y, 
	 *  en caso de encontrarlo, el puntero al nodo actual apuntará al mismo
	 *	y devolverá true. En caso contrario, devolverá false.
	 *	@param Referencia al elemento a buscar
	 *	@return devuelve true si se encontró el elemento y false en caso contrario
	 */
	bool SearchForElement(const LIST_TYPE &Element)
	{
		Node<LIST_TYPE> *pNode = m_pFirstNode;
		while (pNode != NULL) {
			if (pNode->GetElement() == Element) {
				m_pActualNode = pNode;
				return true;
			}
			pNode = pNode->GetNextNode();
		}
		return false;
	}

	/**
	 *  Inserta un elemento en la posición en la que está apuntando
	 *	el puntero al nodo actual
	 *	@param Referencia al elemento a insertar
	 *	@return devuelve true si fue posible insertar el elemento y false en caso contrario
	 */
	bool InsertCurrent(const LIST_TYPE &Element)
	{
		Node<LIST_TYPE> *pNode, *pTmp;

		pNode = new Node<LIST_TYPE>;
		if (pNode != NULL) { 
			if (m_pActualNode != NULL) {
				pNode->SetNextNode(m_pActualNode->GetNextNode());
				pNode->SetPreviousNode(m_pActualNode);
				pNode->SetElement(Element);
				pTmp = m_pActualNode->GetNextNode();
				if (pTmp != NULL) pTmp->SetPreviousNode(pNode);
				m_pActualNode->SetNextNode(pNode);
				m_lCount++;
				return true;
			}
			else {
				if (InsertFront(Element)) {
					m_pFirstNode = pNode;
					return true;
				}
				else
					return false;
			}
		}
		else
			return false;
	}

	/**
	 *  Borra el nodo que está apuntando el puntero al nodo actual.
	 *	@return devuelve true si fue posible eliminar el nodo y false en caso contrario
	 */
	bool DeleteCurrent(void)
	{
		Node<LIST_TYPE> *pNextNode, *pPrevNode;
		if (m_pActualNode != NULL) {
			pNextNode = m_pActualNode->GetNextNode();
			pPrevNode = m_pActualNode->GetPreviousNode();
			if (pNextNode != NULL)
				pNextNode->SetPreviousNode(pPrevNode);
			else
				m_pLastNode = pPrevNode;
			if (pPrevNode != NULL)
				pPrevNode->SetNextNode(pNextNode);
			else
				m_pFirstNode = pNextNode;
			m_pActualNode->SetNextNode(NULL);
			delete m_pActualNode;
			m_pActualNode = NULL;
			m_lCount--;
			return true;
		}
		return false;
	}

	/**
	 *  Inserta un elemento por delante en la lista.
	 *	@param Referencia al elemento a insertar.
	 *	@return devuelve true si fue posible insertar el elemento y false en caso contrario
	 */
	bool InsertFront(const LIST_TYPE &Element)
	{
		Node<LIST_TYPE> *pNode;

		pNode = new Node<LIST_TYPE>;

		if (pNode != NULL) {
			pNode->SetNextNode(m_pFirstNode);
			pNode->SetElement(Element);
			if (m_pFirstNode != NULL) 
				m_pFirstNode->SetPreviousNode(pNode);
			
			if (IsEmpty()) m_pLastNode = pNode;
			
			
			m_pFirstNode = pNode;
			m_lCount++;
			return true;
		} 
		else 
			return false;
	}

	/**
	 *  Inserta un elemento por detrás en la lista.
	 *	@param Referencia al elemento a insertar.
	 *	@return devuelve true si fue posible insertar el elemento y false en caso contrario
	 */
	bool InsertBack (const LIST_TYPE &Element)
	{
		Node<LIST_TYPE> *pNode;

		pNode = new Node<LIST_TYPE>;

		if (pNode != NULL) {
			pNode->SetNextNode(NULL);
			pNode->SetPreviousNode(m_pLastNode);
			pNode->SetElement(Element);

			if (IsEmpty()) {
				m_pFirstNode = pNode;
				m_pLastNode = pNode;
			} else {
				m_pLastNode->SetNextNode(pNode);
				m_pLastNode = pNode;
			}
			
			m_lCount++;
			return true;
		} 
		else
			return false;
	}

	/**
	 *  Extrae un elemento por delante eliminándolo de la lista.
	 *	@param Pasamos por referencia una variable para que nos aloje allí el elemento a extraer.
	 *	@return devuelve true si fue posible extraer el elemento y false en caso contrario
	 */
	bool ExtractFront(LIST_TYPE &Element)
	{
		Node<LIST_TYPE> *pNode;

		if (!IsEmpty()) {
			Element = m_pFirstNode->GetElement();
			pNode = m_pFirstNode;
			m_pFirstNode = m_pFirstNode->GetNextNode();
			
			if (m_pFirstNode)
				m_pFirstNode->SetPreviousNode(NULL);

			pNode->SetNextNode(NULL);

			delete pNode;

			m_lCount--;

			if (IsEmpty()){
				m_pFirstNode = NULL;
				m_pLastNode = NULL;
			}
			return true;
		} 
		else
			return false;
	}

	/**
	 *  Extrae un elemento por detrás eliminándolo de la lista.
	 *	@param Pasamos por referencia una variable para que nos aloje allí el elemento a extraer.
	 *	@return devuelve true si fue posible extraer el elemento y false en caso contrario
	 */
	bool ExtractBack(LIST_TYPE &Element)
	{
		Node<LIST_TYPE>  *pNode;

		if (!IsEmpty()) {
			Element = m_pLastNode->GetElement();

			pNode = m_pLastNode->GetPreviousNode();

			if (pNode != NULL)
				pNode->SetNextNode(NULL);
			
			delete m_pLastNode;

			m_lCount--;

			if (IsEmpty()) {
				m_pFirstNode = NULL;
				m_pLastNode = NULL;
			} else
				m_pLastNode = pNode;

			return true;
		} else
			return false;
	}

	/**
	 *  Devuelve la cantidad de elementos insertos en la lista
	 *	@return devuelve la cantidad de elementos insertos en la lista
	 */
	long GetCount()
	{
		return m_lCount;
	}

	/**
	 *  Devuelve si la lista está vacía o no
	 *	@return devuelve true si la lista está vacía y false en caso contrario
	 */
	bool IsEmpty()
	{
		return (GetCount() == 0);
	}

	/**
	 *  Elimina todos los nodos de la lista
	 */
	void Clear()
	{
		if (m_pFirstNode != NULL) 
			delete m_pFirstNode;
		m_pFirstNode = NULL;
		m_pLastNode = NULL;
		m_lCount = 0;
	}

	
	/**
	 *  Devuelve el primer elemento de la lista sin eliminarlo de la misma.
	 *	@param Pasamos por referencia una variable para que nos aloje allí el elemento.
	 *	@return devuelve true si fue posible tomar el elemento y false en caso contrario
	 */
	bool GetFirst(LIST_TYPE &Element)
	{
		if (m_pFirstNode != NULL) {
			Element = m_pFirstNode->GetElement();
			return true;
		} else 
			return false;
	}		

	/**
	 *  Devuelve el elemento apuntado por el puntero al nodo actual de la lista sin eliminarlo de la misma.
	 *	@param Pasamos por referencia una variable para que nos aloje allí el elemento.
	 *	@return devuelve true si fue posible tomar el elemento y false en caso contrario
	 */
	bool GetCurrent(LIST_TYPE &Element)
	{
		if (m_pActualNode != NULL) {
			Element = m_pActualNode->GetElement();
			return true;
		}
		else
			return false;
	}

	/**
	 *  Devuelve el último elemento de la lista sin eliminarlo de la misma.
	 *	@param Pasamos por referencia una variable para que nos aloje allí el elemento.
	 *	@return devuelve true si fue posible tomar el elemento y false en caso contrario
	 */
	bool GetLast(LIST_TYPE &Element)
	{
		if (m_pLastNode != NULL) {
			Element = m_pLastNode->GetElement();
			return true;
		} else 
			return false;
	}

	/**
	 *  Constructor
	 */
	List()
	{
		m_lCount = 0;
		m_pFirstNode = NULL;
		m_pLastNode = NULL;
	}

	/**
	 *  Destructor
	 */
	~List()
	{
		if (m_pFirstNode != NULL) 
			delete m_pFirstNode;
	}

private:
	Node<LIST_TYPE> *m_pFirstNode;	 // pointer lo first
	Node<LIST_TYPE> *m_pLastNode;	 // pointer to last
	Node<LIST_TYPE> *m_pActualNode; // pointer to actual node
	long m_lCount;					 // Node Count

};

} // end namespace

#endif // _LIST_H_