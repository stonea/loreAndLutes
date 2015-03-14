#ifndef ASFC_MATRIX_H_
#define ASFC_MATRIX_H_
//Aggregates
	#include <vector>
	using namespace std;
//Dependencies
	#include "utils.h"

template <class T>
class ASFC_Matrix
{	
	public:
	//- [Construction] -
		ASFC_Matrix();
		ASFC_Matrix(int width, int height);
	//- [Opps] -
//		const vector<T>& operator[ ] (int i) const;
			  vector<T>& operator[ ] (int i);
	//- [Statistics] -
		int Width();
		int Height();
	//- [Matrix Resizing] -
		void Resize(int width, int height);
		void RemoveRow(int row);
		void RemoveCol(int col);

	private:
	//Vars
		vector<vector<T> > _data;
};

//--------------------------------------------------------------------------------------- [Construction] -
template <class T>
ASFC_Matrix<T>::ASFC_Matrix<T>()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
template <class T>
ASFC_Matrix<T>::ASFC_Matrix<T>(int width, int height)
{
	//Resize
		Resize(iX, iY);
}
//----------------------------------------------------------------------------------------- [Statistics] -
template <class T>
int ASFC_Matrix<T>::Height()
{
	//If atleast 1 row exists
		if(_data.size() > 0)
		{
			//Return the length of that first row
				return(_data[0].size());
		}
	//Otherwise return a size of 0
		return(0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
template <class T>
int ASFC_Matrix<T>::Width()
{
	//Return the # of vectors
		return(_data.size());
}
//------------------------------------------------------------------------------------------------ [Opps] -
template <class T>
vector<T>& ASFC_Matrix<T>::operator[](int i)
{
	//Return this col list
		return _data[i];
}
//------------------------------------------------------------------------------------ [Matrix Resizing] -
template <class T>
void ASFC_Matrix<T>::Resize(int width, int height)
{
	//First resize the width:
		_data.resize(width);
	
	//Now resize all the heights:
		for(int i = 0; i < _data.size(); i++)
		{	
			_data[i].resize(height);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... 
template <class T>
void ASFC_Matrix<T>::RemoveRow(int row)
{
	//Loop through all the columns
		for(int i = 0; i < _data.size(); i++)
		{	
			//Delete this element
				_data[i].erase(_data[i].begin() + row);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
template <class T>
void ASFC_Matrix<T>::RemoveCol(int col)
{
	//Delete this column
		_data.Delete(col);
}

#endif
