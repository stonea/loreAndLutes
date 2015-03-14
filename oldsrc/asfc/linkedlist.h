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


static int myiTAdded, myiTDeleted;
static int myiAdded, myiDeleted;

using namespace std;
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//											cNode
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
/*A cNode is simply a something that holds a piece of data and a pointer to another piece of data, nodes
  can be linked together to form a linked list. Infact that's what the LinkedList class does*/
template <class T>
struct cNode
{	T* mypzData;				//Data this element holds
	cNode* mypNext;				//Next element in the list
	cNode* mypLast;				//Previous element in the list

	cNode()	//By default set the next element pointed in the list to NULL
	{	mypNext = NULL;
		mypLast = NULL;
		mypzData = new T;
		myiTAdded++;
	}
	~cNode()
	{	delete mypzData;
		myiTDeleted++;
	}
};

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//									ASFC_LinkedList prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
template <class T>
class ASFC_LinkedList
{	public:
	//- [Constructors\Deconstructors] -
		ASFC_LinkedList();
		ASFC_LinkedList(int iLength);
		ASFC_LinkedList(ASFC_LinkedList<T> &oRHS);
		~ASFC_LinkedList();
	//- [Data Appending & Adding] -
		void	Resize(int iNewLength);
		void	Resize(int iNewLength, T &zDefault);
		void	Resize(int iNewLength, T* zDefault);
		void	Push(T zWhat);
		void	PushFront(T zWhat);
		void	AddElement(int iElement, T zWhat);
	//- [Data Reading and Changing] -
			T		ReadLast();
			T 		Pop();
			T&		operator[](int iElement);
			int 	Length();
	//- [Data Deletion] -
		void	Delete(int iElement);
	//- [Operators] -
		ASFC_LinkedList<T>& operator=(ASFC_LinkedList<T> oRHS);
		  		
	private:
		//- [Data Appending & Adding] -
			void	AddNode(cNode<T>* pPrevNode, cNode<T>* pNextNode, T* zData);
			void	RemoveNode(cNode<T>* pNode);
		//P-[Traversing] -P
			void	Traverse(int iWhere);
			void	TraverseNextNode();
			void	TraversePrevNode();
			void	Rewind();
			void	FastForward();
			
		//var
			int 		myiLength;
			int			myiCurrentElement;
			cNode<T>*	mypFirstNode;
			cNode<T>*	mypLastNode;
			cNode<T>*	mypCurrentNode;
		//const
			const static int ELEMENT_INVALID = -1;
};

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//										ASFC_LinkedList code
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//------------------------------------------------------------------------- [Constructors\Deconstructors] -
template <class T>
ASFC_LinkedList<T>::ASFC_LinkedList<T>()
{	//Okay set their defaults:
		myiLength			= 0;
		myiCurrentElement	= ELEMENT_INVALID;
		mypFirstNode		= NULL;
		mypLastNode			= mypFirstNode;
		mypCurrentNode		= mypFirstNode;
		
		myiTAdded = 0;
		myiTDeleted = 0;
		myiAdded = 0;
  		myiDeleted = 0;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
template <class T>
ASFC_LinkedList<T>::ASFC_LinkedList<T>(int iLength)
{	//Okay set their defaults:
		myiLength			= 0;
		myiCurrentElement	= ELEMENT_INVALID;
		mypFirstNode		= NULL;
		mypLastNode			= mypFirstNode;
		mypCurrentNode		= mypFirstNode;
	//And resize
		Resize(iLength);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
template <class T>
ASFC_LinkedList<T>::ASFC_LinkedList<T>(ASFC_LinkedList<T> &oRHS)
{	//Okay set their defaults:
		myiLength			= 0;
		myiCurrentElement	= ELEMENT_INVALID;
		mypFirstNode		= NULL;
		mypLastNode			= mypFirstNode;
		mypCurrentNode		= mypFirstNode;

	//Resize to the 2nd list
		Resize(oRHS.Length());
	//Copy Elements
		for(int i = 0; i < oRHS.Length(); i++)
		{	operator[](i) = oRHS[i];
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
template <class T>
ASFC_LinkedList<T>::~ASFC_LinkedList()
{	Resize(0);
}
//---------------------------------------------------------------------------- [Data Appending & Adding] -
template <class T>
void ASFC_LinkedList<T>::Resize(int iNewLength)
{	//Resize setting new nodes to NULL
		Resize(iNewLength, NULL);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
template <class T>
void ASFC_LinkedList<T>::Resize(int iNewLength, T &zDefault)
{	Resize(iNewLength, &zDefault);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
template <class T>
void ASFC_LinkedList<T>::Resize(int iNewLength, T* zDefault)
{	//Vars
		int tiLength;
		
	//If we're resizing to zero (clearing the list)
		if(iNewLength == 0)
		{	//Delete Nodes
				tiLength = abs(iNewLength - Length());
				for(int i = 0; i < tiLength; i++)
				{	RemoveNode(mypLastNode);
				}
  			//Reset the list's state
				myiLength			= 0;
				myiCurrentElement	= ELEMENT_INVALID;
				mypFirstNode		= NULL;
				mypLastNode			= mypFirstNode;
				mypCurrentNode		= mypFirstNode;
		}
	//If we're resizing to another length
		else
		{	//If we should add nodes
			if(iNewLength - Length() > 0)
			{	//Add iNewLength nodes
					tiLength = iNewLength - Length();
					for(int i = 0; i < tiLength; i++)
						AddNode(mypLastNode, NULL, zDefault);
			}
		//If we should remove nodes
			if(iNewLength - Length() < 0)
			{	//Delete Nodes
					tiLength = abs(iNewLength - Length());
					for(int i = 0; i < tiLength; i++)
						RemoveNode(mypLastNode);
			}
		}
}

//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
template <class T>
void ASFC_LinkedList<T>::Push(T zWhat)
{	//Resize+1 and add a new node at the end
		Resize(Length() + 1, zWhat);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
template <class T>
void ASFC_LinkedList<T>::PushFront(T zWhat)
{	//If there's no nodes just do a normal push
		if(Length() == 0)
		{	Push(zWhat);
			return;
		}

	//Traverse to the first element
		Traverse(0);
	//Now add a node before there
		AddNode(mypCurrentNode->mypLast, mypCurrentNode, &zWhat);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
template <class T>
void ASFC_LinkedList<T>::AddElement(int iElement, T zWhat)
{	//Traverse to element iElement
		Traverse(iElement);
	//Now add a node after there
		AddNode(mypCurrentNode, mypCurrentNode->mypNext, &zWhat);
}
//-------------------------------------------------------------------------- [Data Reading and Changing] -
template <class T>
T ASFC_LinkedList<T>::ReadLast()
{	//Return the last node on the list
		return(operator[](Length() - 1));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
template <class T>
T ASFC_LinkedList<T>::Pop()
{	//Copy the last node, delete it (the node not the copy), and return the copy
		T zTemp;
		zTemp = ReadLast();
		Delete(Length() - 1);
		return(zTemp);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
template <class T>
T& ASFC_LinkedList<T>::operator[](int iElement)
{	//Make sure this is a valid element
		if(iElement >= Length())
		{	cout << "ASFC_ERR ASFC_LinkedList::opeator[] #000, attempt at access an illegal index\n";
			cout << "--[Index]--> " << iElement << endl;
		}
	//Traverse to element iElement
		Traverse(iElement);
	//Return what's held there
		return(*mypCurrentNode->mypzData);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
template <class T>
int ASFC_LinkedList<T>::Length()
{	//Return the length
		return(myiLength);
}
//-------------------------------------------------------------------------------------- [Data Deletion] -
template <class T>
void ASFC_LinkedList<T>::Delete(int iElement)
{	//Make sure this is a valid element
		if(iElement >= Length())
		{	cout << "ASFC_ERR ASFC_LinkedList::opeator[] #000, attempt at access an illegal index\n";
			cout << "--[Index]--> " << iElement << endl;
		}
	//Traverse to element iElement
		Traverse(iElement);
	//Delete what's held there
		RemoveNode(mypCurrentNode);
}
//------------------------------------------------------------------------------------------ [Operators] -
template <class T>
ASFC_LinkedList<T>& ASFC_LinkedList<T>::operator=(ASFC_LinkedList<T> oRHS)
{	//Okay set their defaults:
		myiLength			= 0;
		myiCurrentElement	= ELEMENT_INVALID;
		mypFirstNode		= new(cNode<T>);		myiAdded++;
		mypLastNode			= mypFirstNode;
		mypCurrentNode		= mypFirstNode;

	//Resize to the 2nd list
		Resize(oRHS.Length());
	//Copy Elements
		for(int i = 0; i < oRHS.Length(); i++)
		{	operator[](i) = oRHS[i];
		}
}
//P-------------------------------------------------------------------------- [Data Appending & Adding] -P
template <class T>
void ASFC_LinkedList<T>::AddNode(cNode<T>* pPrevNode, cNode<T>* pNextNode, T* zData)
{	//Vars
		cNode<T>* pNewNode;

	//Okay, set this new node after myPrevNode and set the next node's previous node to the new node
		if(pPrevNode == NULL)
		{	pNewNode = new(cNode<T>);	myiAdded++;
		}
		else
		{	pPrevNode->mypNext = new(cNode<T>);	myiAdded++;
			pNewNode = pPrevNode->mypNext;
		}

		if(pNextNode != NULL)
			pNextNode->mypLast = pNewNode;
	//Incriment the size counter
		myiLength++;
	//If this is the first element
		if(Length() == 1)
		{	mypFirstNode = pNewNode;
			mypLastNode  = pNewNode;
		}
	
	//And set this new node's previous node, next node, and data
		pNewNode->mypLast = pPrevNode;
		pNewNode->mypNext = pNextNode;
		if(zData != NULL)
		{	*pNewNode->mypzData = *zData;
		}
		
	//If this node is the new last node
		if(pNextNode == NULL)
		{	//Set the new node to be the last node			
				mypLastNode = pNewNode;
		}		
	//If this node is the new first node
		if(pPrevNode == NULL)
		{	//Set the new node to be the last node
				mypFirstNode = pNewNode;
			//Rewind so our traversed point is no longer NULL
				Rewind();
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
template <class T>
void ASFC_LinkedList<T>::RemoveNode(cNode<T>* pNode)
{	//If this is a valid node
		if(pNode != NULL)
		{	//If this node is the first node
				if(pNode == mypFirstNode)
				{	//Set the new first node
						mypFirstNode = pNode->mypNext;
			
					//Set the new first node's prev node to NULL (if possible)
						if(mypFirstNode != NULL)
							mypFirstNode->mypLast = NULL;
				}
			
			//If this node is in the middle of the list
				if(pNode != mypFirstNode && pNode != mypLastNode)
				{	//Set the last node's next node (if possible)
						if(pNode->mypLast != NULL)
							pNode->mypLast->mypNext = pNode->mypNext;
			
					//Set the next node's prev node (if possible)
						if(pNode->mypNext != NULL)
							pNode->mypNext->mypLast = pNode->mypLast;
				}
			//If this node is at the end of the list
				if(pNode == mypLastNode)
				{	//Set the new last node (if possible)
						if(mypLastNode != NULL)
							mypLastNode = pNode->mypLast;
			
					//Set the new first node's next node to NULL (if possible)
						if(mypLastNode != NULL)
							mypLastNode->mypNext = NULL;
				}
	
			//Okay now delete this node!
				delete(pNode);		myiDeleted++;
	
			//Update the linked list size counter
				myiLength--;
		}
		
	//Traverse back to the start of the list for safety
		Rewind();
}
//P----------------------------------------------------------------------------------------[Traversing] -P
template <class T>
void ASFC_LinkedList<T>::Traverse(int iWhere)
{	//If we're at iWhere return
		if(iWhere == myiCurrentElement)
			return;

	//If its the first or last node just move there
		if(iWhere == myiLength)
			FastForward();
		else if(iWhere == 0)
			Rewind();

	//Otherwise while we haven't reached element iWhere
		else
		{	while(iWhere != myiCurrentElement)
			{	//If we need to move up
					if(myiCurrentElement < iWhere)
					{	//Move to the next node
							mypCurrentNode = mypCurrentNode->mypNext;
							myiCurrentElement++;
					}
				//If we need to move back
					else if(myiCurrentElement > iWhere)
					{	//Move to the previous node
							mypCurrentNode = mypCurrentNode->mypLast;
							myiCurrentElement--;		
					}
			}
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
template <class T>
void ASFC_LinkedList<T>::TraverseNextNode()
{	mypCurrentNode = mypCurrentNode->mypNext;
	myiCurrentElement++;
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
template <class T>
void ASFC_LinkedList<T>::TraversePrevNode()
{	mypCurrentNode = mypCurrentNode->mypLast;
	myiCurrentElement--;
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
template <class T>
void ASFC_LinkedList<T>::Rewind()
{	mypCurrentNode		= mypFirstNode;
	myiCurrentElement	= 0;
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ..P
template <class T>
void ASFC_LinkedList<T>::FastForward()
{	mypCurrentNode 		= mypLastNode;
	myiCurrentElement 	= Length() - 1;
}

#endif
