#ifndef _NODE_H_
#define _NODE_H_

#include <memory.h>
#include <windows.h>
#include "ZakEngine/defines.h"

namespace zak {

template <class LIST_TYPE>

class Node 
{

public:

	// set the value of an element
	void SetElement(LIST_TYPE Element) 
	{
		m_Element = Element;
	}

	//Set the Next list pointer
	void SetNextNode(Node<LIST_TYPE> *pNext)
	{
		m_pNext = pNext;
	}

	void SetPreviousNode(Node<LIST_TYPE> *pPrevious)
	{
		m_pPrevious = pPrevious;
	}
	// Read Element 
	LIST_TYPE GetElement()
	{
		return m_Element;
	}

	// Read Next
	Node<LIST_TYPE> *GetNextNode()
	{
		return m_pNext;
	}

	Node<LIST_TYPE> *GetPreviousNode()
	{
		return m_pPrevious;
	}
	
	// Constructor
	Node()
	{
		m_pNext = NULL;
		m_pPrevious = NULL;
	}

	// Copy Constructor
	Node(const Node<LIST_TYPE> &copyFrom)
	{
		
	}

	// Constructor that initialize an element	
	Node(LIST_TYPE Element)
	{
		m_Element = Element;
		m_pNext = NULL;
		m_pPrevious = NULL;
	}

	// Destructor
	~Node()
	{
		if (m_pNext != NULL) {
			delete m_pNext;
		}
	}

private:
	LIST_TYPE			 m_Element;			// type Element
	Node<LIST_TYPE>  *m_pNext;			// pointer to next
	Node<LIST_TYPE>  *m_pPrevious;		// pointer to previous
};

} // end namespace

#endif // _NODE_H_