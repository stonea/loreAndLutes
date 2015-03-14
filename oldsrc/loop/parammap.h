/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: cParamMap
*/

//��������������������������������������������������������������������������������������������������������
//												Initilization
//��������������������������������������������������������������������������������������������������������
//Multiple inclusion protection:
	#ifndef PARAMMAP_H_
	#define PARAMMAP_H_

//Foundation
	#include <vector>
	using namespace std;

//��������������������������������������������������������������������������������������������������������
//												eParam
//��������������������������������������������������������������������������������������������������������
enum eParam
{	PARAM_INT 		= 0,
	PARAM_FLOAT,
	PARAM_STRING,
	PARAM_INT_REF,
	PARAM_FLOAT_REF,
	PARAM_STRING_REF
};

//��������������������������������������������������������������������������������������������������������
//												cParamMap
//��������������������������������������������������������������������������������������������������������
class LOOP_ParamMap
{	public:
	//- [Constuctors] -
 		LOOP_ParamMap();
 		
	//- [Param Map Updating] -
		void 	Clear();
		void 	New(eParam iWhat);
		eParam	Param(int iNumber);
		int		NumParams();
 	
 	private:
 	//Vars
 		vector<eParam> mylPasses;
};

//Now ending parammap.h
	#endif
