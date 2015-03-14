/*   Protected under the GNU General Public License read and see copying.txt for details

	 * * *                          \ | / Annex Solutions
	* ASFC *---------------------- -- + -- Foundation
	 * * *                          / | \    Classes
	
	File:	linkedlist.h
    By:		Andy Stone
    Desc:	This file includes the prototype of the Linked List class.	
*/

#ifndef ASFC_LINKEDLIST_H_
#define ASFC_LINKEDLIST_H_
#include <SDL.h>
#include <assert.h>
#include <iostream>
using namespace std;

template <class T>
struct ASFC_ListNode
{
	T* _data;
	ASFC_ListNode *_prevNode, *_nextNode;

	ASFC_ListNode()
		: _prevNode(NULL),
		  _nextNode(NULL)
	{
		_data = new T;
	}

	~ASFC_ListNode()
	{
		delete _data;
	}
};

template <class T>
class ASFC_LinkedList
{
	public:
	//- [Construction] -
		ASFC_LinkedList();
		ASFC_LinkedList(int size);
		~ASFC_LinkedList();
	//- [List Statistics] -
		int Length();
	//- [Data Adding] -
		void Resize(int size);
		void Resize(int size, T object);
		T* Push();
		T* Push(T object);
		T* PushFront();
		void PushFront(T object);
		T* AddElement(int iter, T object);
		// ^ I'm assuming it adds the element after the iter, if not correct or this could screw up the
		// routing system.
	//- [Data retrieval] -
		T* Top();
		T& operator[](int element);
	//- [Data removal] -
		void Clear();
		void Delete(int element);
		void Pop();
	
	private:
	//P- [Data retrieval] -P
		ASFC_ListNode<T>* GetNode(int element);

	//Vars
		ASFC_ListNode<T> *_firstNode;
		ASFC_ListNode<T> *_lastNode;
		int _length;
};

//-------------------------------------------------------- [Construction] -
template <class T>
ASFC_LinkedList<T>::ASFC_LinkedList()
	: _firstNode(NULL),
	  _lastNode(NULL),
	  _length(0)
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
template <class T>
ASFC_LinkedList<T>::ASFC_LinkedList(int size)
	: _firstNode(NULL),
	  _lastNode(NULL),
	  _length(0)
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
template <class T>
ASFC_LinkedList<T>::~ASFC_LinkedList()
{
	//Clear the list
	//	Clear();
}
//----------------------------------------------------- [List Statistics] -
template <class T>
int ASFC_LinkedList<T>::Length()
{
	//Return the length
		return _length;
}
//--------------------------------------------------------- [Data Adding] -
template <class T>
void ASFC_LinkedList<T>::Resize(int size)
{
	//Vars
		int deltaElements;

	//If new nodes need to be created
		if(size > Length())
		{
			//Loop through and create the new nodes
				deltaElements = size - Length();
				for(int i = 0; i < deltaElements; i++)
				{
					Push();
				}
		}
	//If nodes need to be deleted
		else if(size < Length())
		{
			//Loop through and delete the nodes
				deltaElements = Length() - size;
				for(int i = 0; i < deltaElements; i++)
				{
					Pop();
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..
template <class T>
void ASFC_LinkedList<T>::Resize(int size, T object)
{
	//Vars
		int deltaElements;

	//If new nodes need to be created
		if(size > Length())
		{
			//Loop through and create the new nodes
				deltaElements = size - Length();
				for(int i = 0; i < deltaElements; i++)
				{
					Push(object);
				}
		}
	//If nodes need to be deleted
		else if(size < Length())
		{
			//Loop through and delete the nodes
				deltaElements = Length() - size;
				for(int i = 0; i < deltaElements; i++)
				{
					Pop();
				}
		}

}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
template <class T>
T* ASFC_LinkedList<T>::Push()
{
	//If we're creating the first element
		if(_firstNode == NULL)
		{
			_firstNode = new(ASFC_ListNode<T>);
			_firstNode->_prevNode = _firstNode;
			_firstNode->_nextNode = _firstNode;
			_lastNode = _firstNode;
			_length++;
			return _firstNode->_data;
		}
	//Create a new node
		ASFC_ListNode<T> *newNode = new ASFC_ListNode<T>;
		newNode->_prevNode    = _lastNode;
		newNode->_nextNode    = _firstNode;
		_lastNode->_nextNode  = newNode;
		_firstNode->_prevNode = newNode;
		_lastNode = newNode;
		_length++;
		return newNode->_data;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
template <class T>
T* ASFC_LinkedList<T>::Push(T object)
{
	Push();
	*Top() = object;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
template <class T>
T* ASFC_LinkedList<T>::PushFront()
{
	//If we're creating the first element
		if(_firstNode == NULL)
		{
			_firstNode = new(ASFC_ListNode<T>);
			_firstNode->_prevNode = _firstNode;
			_firstNode->_nextNode = _firstNode;
			_lastNode = _firstNode;
			_length++;
			return _firstNode->_data;
		}
	//Create a new node
		ASFC_ListNode<T> *newNode = new ASFC_ListNode<T>;
		newNode->_prevNode    = _lastNode;
		newNode->_nextNode    = _firstNode;
		_lastNode->_nextNode  = newNode;
		_firstNode->_prevNode = newNode;
		_firstNode = newNode;
		_length++;
		return newNode->_data;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..
template <class T>
void ASFC_LinkedList<T>::PushFront(T object)
{
	//If we're creating the first element
		if(_firstNode == NULL)
		{
			_firstNode = new(ASFC_ListNode<T>);
			_firstNode->_prevNode = _firstNode;
			_firstNode->_nextNode = _firstNode;
			_lastNode = _firstNode;
			*_firstNode->_data = object;
			_length++;
			return; 
		}
	//Create a new node
		ASFC_ListNode<T> *newNode = new ASFC_ListNode<T>;
		newNode->_prevNode    = _lastNode;
		newNode->_nextNode    = _firstNode;
		_lastNode->_nextNode  = newNode;
		_firstNode->_prevNode = newNode;
		_firstNode = newNode;
		_length++;
		*newNode->_data = object;
		return;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..
template <class T>
T* ASFC_LinkedList<T>::AddElement(int iter, T object)
{
	//Vars
		ASFC_ListNode<T> *prevNode, *nextNode;

	//Get the nodes that need to be modified
		prevNode = GetNode(iter);
		nextNode = prevNode->_nextNode;
	//Create the new node
		ASFC_ListNode<T> *newNode = new ASFC_ListNode<T>;
		*newNode->_data    = object;
		newNode->_prevNode = prevNode;
		newNode->_nextNode = nextNode;
		_length++;
	//Link the previous and next nodes to this new one
		if(prevNode != NULL)
			prevNode->_nextNode = newNode;
		if(nextNode != NULL)
			nextNode->_prevNode = newNode;
	//If this is the first or last node set it to be
		if(prevNode == NULL)
			_firstNode = newNode;
		if(nextNode == NULL)
			_lastNode = newNode;
}
//------------------------------------------------------ [Data retrieval] -
template <class T>
T* ASFC_LinkedList<T>::Top()
{
	if(_lastNode == NULL)
	{
		cerr << "List error: Trying to recieve invalid node through Top() "
			 << "method.\n";
	}
	return _lastNode->_data;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
template <class T>
T& ASFC_LinkedList<T>::operator[](int element)
{
	//Insure that this is a legal node to get
		if(element >= Length() || element < 0)
		{
			cerr << "List error: Trying to retrieve nonexistant node "
				 << element << " through [] operator.\n";
		}
	//Get the node, and return its data
		return *GetNode(element)->_data;
}
//-------------------------------------------------------- [Data removal] -
template <class T>
void ASFC_LinkedList<T>::Clear()
{
	//Simply resize the list to zero
		Resize(0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
template <class T>
void ASFC_LinkedList<T>::Delete(int element)
{
	//Vars
		ASFC_ListNode<T> *nodeToDelete;

	//Insure that this is a legal node to delete
		if(element >= Length() || element < 0)
		{
			cerr << "List error: Trying to remove nonexistant node "
				 << element << " through Delete() method.\n";
		}
	//Get the node to delete
		nodeToDelete = GetNode(element);	
	//If we're deleting the first or last element, reset those vars
		if(element == 0)
		{
			_firstNode = _firstNode->_nextNode;
		}
		else if(element == _length-1)
		{
			_lastNode  = _lastNode->_prevNode;
		}
	//Link the previous element to the next element	
		nodeToDelete->_prevNode->_nextNode = nodeToDelete->_nextNode;
		nodeToDelete->_nextNode->_prevNode = nodeToDelete->_prevNode;
	//And delete it
		delete nodeToDelete;
		_length--;
	//If the list is cleared reset the start and end links
		if(_length == 0)
		{
			_firstNode = NULL;
			_lastNode  = NULL;
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
template <class T>
void ASFC_LinkedList<T>::Pop()
{
	//Display an error if there is no element to pop
		if(_lastNode == NULL)
		{
			cerr << "List error: Trying to remove nonexistant node through Pop() "
			 << "method.\n";
		}
	//Delete the last element
		Delete(Length() - 1);
}
//P---------------------------------------------------- [Data retrieval] -P
template <class T>
ASFC_ListNode<T>* ASFC_LinkedList<T>::GetNode(int element)
{
	ASFC_ListNode<T> *currentNode;
	int deltaElements;

	//If this element is more than 1/2 the length traverse backwards
	//to retrieve
		if(element > Length() / 2)
		{		
			currentNode = _lastNode;
			deltaElements = Length() - element;
			for(int i = 0; i < deltaElements-1; i++)
			{
				currentNode = currentNode->_prevNode;
			}
			return currentNode;
		}
	//Otherwise traverse from the start
		currentNode = _firstNode;
		for(int i = 0; i < element; i++)
		{
			currentNode = currentNode->_nextNode;
		}
		return currentNode;
}

#endif
