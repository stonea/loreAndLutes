/*	ANNEX SOLUTIONS
	By: Andy Stone

	File for: LOOP_Class
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "class.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LOOP_Class
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LOOP_Class::LOOP_Class()
{	mysIdentifier = "#######ERR########";
	mypoParent = NULL;
}
//------------------------------------------------------------------------------------- [Code Handeling] -
void  LOOP_Class::ClearCode()
{	mylCodes.resize(0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void  LOOP_Class::PushCode(LOOP_Code oNewCode)
{	mylCodes.push_back(oNewCode);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LOOP_Code LOOP_Class::GetCode(int iCodeNum)
{	return(mylCodes[iCodeNum]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int   LOOP_Class::NumCodes()
{	return(mylCodes.size());
}
//------------------------------------------------------------------------------------ [Label Handeling] -
void LOOP_Class::ClearLabels()
{	mylLabels.resize(0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Class::PushLabel(LOOP_Label oNewLabel)
{	mylLabels.push_back(oNewLabel);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LOOP_Label LOOP_Class::GetLabel(int iLabelNum)
{	if(iLabelNum < 0 || iLabelNum >= mylLabels.size())
	{	LOOP_Label oLabelInvalid;
		oLabelInvalid.SetIdentifier("");
		return(oLabelInvalid);
	}

	return(mylLabels[iLabelNum]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LOOP_Label LOOP_Class::GetLabel(string sIdentifier, int iIgnore)
{	//Vars
		int iIgnored = 0;

	//Loop through all labels
		for(int i = 0; i < NumLabels(); i++)
		{	if(mylLabels[i].Identifier() == sIdentifier && iIgnored >= iIgnore)
			{	return(mylLabels[i]);
			}
			else
			{	if(mylLabels[i].Identifier() == sIdentifier)
					iIgnored++;
			}
		}
		
	//If we have an invalid label return invalid
		LOOP_Label oLabelInvalid;
		oLabelInvalid.SetIdentifier("");
		return(oLabelInvalid);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LOOP_Label 	LOOP_Class::GetLabel(string sIdentifier)
{	//Loop through all labels
		for(int i = 0; i < NumLabels(); i++)
		{	if(mylLabels[i].Identifier() == sIdentifier)
			{	return(mylLabels[i]);
			}
		}
		
	//If we have an invalid label return invalid
		LOOP_Label oLabelInvalid;
		oLabelInvalid.SetIdentifier("");
		return(oLabelInvalid);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int  LOOP_Class::NumLabels()
{	return(mylLabels.size());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
vector<LOOP_Label>* LOOP_Class::Labels()
{	return(&mylLabels);
}
//----------------------------------------------------------------------------- [Parent Class Handeling] -
void LOOP_Class::Derive(LOOP_Class* pFrom)
{	//Set the parent class
		mypoParent = pFrom;
		
	//Copy Variables
		myoVars.CopyIn(pFrom->GetVariables());

	//Copy Labels (loop through all labels in the parent class)
		for(int i = 0; i < pFrom->Labels()->size(); i++)
		{	//Push this label in
				mylLabels.push_back(pFrom->Labels()->operator[](i));
		}
}
//------------------------------------------------------------------------------- [Identifier Handeling] -
//MEMVAR_SETGET(SetIdentifier, Identifier, string, mysIdentifier)
//------------------------------------------------------------------------------------------ [Debugging] -
void LOOP_Class::WriteDebuggingInfo()
{	//Output the class name
		cout << "Class: " << Identifier() << endl;

	//Loop through all codes
		for(int i = 0; i < mylCodes.size(); i++)
		{	//Output info on this code (if its not to a null command)
				if(mylCodes[i].Command() != NULL)
				{	cout << "Code " << i << ": " << mylCodes[i].Command()->Identifier();
					cout << endl;
				}
			//Else
				else
				{	cout << "Code " << i << ": NULL (probably a label)";
    				cout << endl;
				}
		}
}
//-------------------------------------------------------------------------------- [Variable Handelings] -
LOOP_Variables*	LOOP_Class::GetVariables()
{	return(&myoVars);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Class::NewInt(string sIdentifier, int iValue, bool fPublic)
{	myoVars.NewInt(sIdentifier, iValue, fPublic);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Class::NewFloat(string sIdentifier, double dValue, bool fPublic)
{	myoVars.NewFloat(sIdentifier, dValue, fPublic);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LOOP_Class::NewString(string sIdentifier, string sValue, bool fPublic)
{	myoVars.NewString(sIdentifier, sValue, fPublic);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LOOP_Class::FindInt(string sIdentifier)
{	return(myoVars.FindInt(sIdentifier));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LOOP_Class::FindFloat(string sIdentifier)
{	return(myoVars.FindFloat(sIdentifier));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LOOP_Class::FindString(string sIdentifier)
{	return(myoVars.FindString(sIdentifier));
}
