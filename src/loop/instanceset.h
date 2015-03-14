/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: cInstanceSet
*/

//��������������������������������������������������������������������������������������������������������
//												Initilization
//��������������������������������������������������������������������������������������������������������
//Multiple inclusion protection:
	#ifndef INSTANCESET_H_
	#define INSTANCESET_H_

//Aggregates
	#include "class.h"
	#include "instance.h"

//��������������������������������������������������������������������������������������������������������
//												eScope
//��������������������������������������������������������������������������������������������������������
enum eScope
{	SCOPE_LOCAL,
	SCOPE_GLOBAL
};
	
//��������������������������������������������������������������������������������������������������������
//												cInstanceSet
//��������������������������������������������������������������������������������������������������������
class LOOP_InstanceSet
{	public:
	//- [Constuctors] -
 		LOOP_InstanceSet();

	//- [Instance Handeling] -
		void 			NewInstance			(LOOP_Class* poOfClass, eScope iScope);
		void 			RemoveInstance		(string sIdentifier);
		void			RemoveLocalInstances();
		void			ClearInstances		();
		int 			NumInstances		();
		LOOP_Instance*	GetInstance			(string sIdentifier);
		LOOP_Instance*	GetInstance			(int iLocation);
 	
 	private:
 	//-P [Instance Handeling] -P
 		int		GetInstanceLocation(string sIdentifier);
 		
 	//Vars
 		vector<LOOP_Instance> 	myloInstances;
 		vector<eScope>			myliInstancesScope;
};

//Now ending instanceset.h
	#endif
