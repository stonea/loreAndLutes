/*	Protected under the GNU General Public License read and see copying.txt for details

	 * * *                          \ | / Annex Solutions
	* ASFC *---------------------- -- + -- Foundation
	 * * *                          / | \    Classes
	
	File:	matrix.h
    By:		Andy Stone
    Desc:	Emulates a matrix (2 dimensional array) with Linked List Objects
*/

#ifndef ASFC_MATRIX_H_
#define ASFC_MATRIX_H_
//*********************************************************************************************************
//											Initilization
//*********************************************************************************************************
//Foundation objects
	#include "linkedlist.h"
	#include "utils.h"
	#include <fstream>

//********************************************************************************************************
//											ASFC_Matrix Prototype
//********************************************************************************************************
template <class T>
class ASFC_Matrix
{	public:
	//- [Construction] -
		ASFC_Matrix();				//Default construct
		ASFC_Matrix(C_i2(iX, iY));	//Alt construct, resizes the matrix
		~ASFC_Matrix();				//Deconstruct
	//- [Opps] -
		const ASFC_LinkedList<T>& operator[ ] (int i) const;
			  ASFC_LinkedList<T>& operator[ ] (int i);
  			  ASFC_Matrix<T>& operator=(ASFC_Matrix<T> &oRHS);	
	//- [File Handeling] -
		void Load(string sFileName);			//Loads a matix file
	//- [Statistics] -
		int Height();							//Returns the height of the matrix
		int Width();							//Returns the width of the matrix
	//- [Matrix Resizing] -
		void Resize(int iWidth, int iHeight);		//Resize the matrix
		void RemoveRow(int iRow);					//Deletes a row out of the matrix
		void RemoveCol(int iCol);					//Deletes a column out of the matrix

	private:
	//Vars
		ASFC_LinkedList<ASFC_LinkedList<T> > lData;		//Data, each linked list = 1 column (yeah I know that seems a bit backwards but it makes programming a bit easier...)
};

//********************************************************************************************************
//											ASFC_Matrix Data
//********************************************************************************************************
//--------------------------------------------------------------------------------------- [Construction] -
//Default construct
template <class T>
ASFC_Matrix<T>::ASFC_Matrix<T>()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Alt construct, resizes the matrix
template <class T>
ASFC_Matrix<T>::ASFC_Matrix<T>(C_i2(iX, iY))
{	Debug = false;
	
	//Resize
		Resize(iX, iY);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Deconstruct
template <class T>
ASFC_Matrix<T>::~ASFC_Matrix()
{	//Simply
		lData.Resize(0);
}

//----------------------------------------------------------------------------------------- [Statistics] -
//Returns the height of the matrix
template <class T>
int ASFC_Matrix<T>::Height()
{	//If atleast 1 row exists
		if(lData.Length() > 0)
		{	//Return the length of that first row
				return(lData[0].Length());
		}
	//Otherwise
		else
		{	//Return 0
				return(0);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Returns the width of the matrix
template <class T>
int ASFC_Matrix<T>::Width()
{	//Return the # of linked lists
		return(lData.Length());
}
//------------------------------------------------------------------------------------------------ [Opps] -
template <class T>
const ASFC_LinkedList<T>& ASFC_Matrix<T>::operator[ ] (int i) const
{	//Range check i
		if(i < 0 || i >= lData.Length())
		{	cout << "ERR in const cLinkedList<T>& ASFC_Matrix<T>::operator[ ] #000, invalid element\n";
			cout << "--ELMNT-->	" << i << endl;
		}
	
	//Return this col list
		return lData[i];
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
template <class T>
ASFC_Matrix<T>& ASFC_Matrix<T>::operator=(ASFC_Matrix<T> &oRHS)
{	//Resize data
		lData.Resize(oRHS.lData.Length());

	//Loop through all lists
		for(int i = 0; i < oRHS.lData.Length(); i++)
  		{	lData[i] = oRHS.lData[i];
  		}
}
//-------------------------------------------------------------------------------------- [File Handeling] -
//Loads a matix file
/*	A matrix file consists of the following format:

	Width	Height
	#	#	#	#
	#	#	#	#
	#	#	#	#

	Where # is a numeric value in a matrix
*/
template <class T>
void ASFC_Matrix<T>::Load(string sFileName)
{	//Vars	
		int iWidth, iHeight;
		ifstream oFile;
		char tc;
	
	//Debug info
		cout << "Loading Matrix\n";
	
	//Open up the file
		oFile.open(sFileName.c_str());
	
	//Read in the header info
		oFile >> iWidth;
		oFile >> iHeight;
		//Debug info
			if(fDebug)
			{	cout << "--[Width]--> " << iWidth << endl;
				cout << "--[Height]--> " << iHeight << endl;
			}
	
	//Resize the matrix
		Resize(iWidth, iHeight);
	
	//Read in the matrix data
		//Loop through all the matrix values
			for(int iY = 0; iY < iHeight; iY++)
			{	for(int iX = 0; iX < iWidth; iX++)
				{	//Read in 1 value
						oFile >> tc;
					
					//Set this value in the matrix
						this->operator[](iX)[iY] = tc;
					
					//Debug info
						cout << tc;
				}
				
				//Debug info
				if(fDebug)
				{	cout << endl;
				}
			}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
template <class T>
ASFC_LinkedList<T>& ASFC_Matrix<T>::operator[ ] (int i)
{	//Range check i
		if(i < 0 || i >= lData.Length())
		{	cout << "ERR in const cLinkedList<T>& ASFC_Matrix<T>::operator[ ] #000, invalid element\n";
			cout << "--ELEMENT--> " << i << endl;
		}

	//Return this col list
		return lData[i];
}
//------------------------------------------------------------------------------------ [Matrix Resizing] -
//Resize the matrix
template <class T>
void ASFC_Matrix<T>::Resize(int iWidth, int iHeight)
{	//First resize the width:
		lData.Resize(iWidth);
	
	//Now resize all the heights:
		for(int i = 0; i < lData.Length(); i++)
		{	lData[i].Resize(iHeight);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... 
//Deletes a row out of the matrix
template <class T>
void ASFC_Matrix<T>::RemoveRow(int iRow)
{	//Loop through all the columns
		for(int i = 0; i < lData.Length(); i++)
		{	//Delete this element
				lData[i].Delete(iRow);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Deletes a column out of the matrix
template <class T>
void ASFC_Matrix<T>::RemoveCol(int iCol)
{	//Delete this column
		lData.Delete(iCol);
}

#endif
