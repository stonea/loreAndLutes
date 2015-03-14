/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			templatereader.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "templatereader.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LEDIT_TemplateReader
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//--------------------------------------------------------------------------------------- [Construction] -
LEDIT_TemplateReader::LEDIT_TemplateReader()
{
}
//-------------------------------------------------------------------------------------- [Tag Handeling] -
void LEDIT_TemplateReader::SetTag(char c, string sText)
{	//Loop through all existing tags, if this tag exists set it and return
		for(int i = 0; i < lcTags.Length(); i++)
		{	if(lcTags[i].cTag == c)
			{	lcTags[i].sReplace = sText;
			
				return;
			}
		}
		
	//If we have a new tag push it in
		LEDIT_Tag toTag;
		toTag.cTag = c;
		toTag.sReplace = sText;
		lcTags.Push(toTag);
}
//-------------------------------------------------------------------------------------------- [Reading] -
void  LEDIT_TemplateReader::ReadTemplate(string sFile, TE_Text* poText, int* iStart, int* iEnd)
{	//Vars
		string 		s;
		char		str[100000];
		string		sTag;
		ifstream	fInFile(sFile.c_str());
		int			iRowPosition = *iStart;

	//Keep on reading until we reach the end or the interrupt tag <!>
		while(!fInFile.eof())
		{	//Read in one line
				fInFile.getline(str, 100000);
				s = str;

			//Now search the string for a tag
				for(int i = 0; i < int(s.size() - 3); i++)
				{	if(s[i] == '<' && s[i+1] == '!' && s[i+2] == '>')
					{	//Read in the tag
							sTag = s[i+3];
							
						//Delete out the tag
							s.erase(s.begin() + i, s.begin() + i+4);
							
						//Decide what to do based on the tag:
							for(int j = 0; j < lcTags.Length(); j++)
							{	if(lcTags[j].cTag == sTag[0])
								{	s.insert(i, lcTags[j].sReplace);
								}
							}
					}
				}
			
			//Output s
				poText->AddLine(s, iRowPosition-1);
				iRowPosition++;
		}
		
	//Set the end to the new end
		*iEnd = iRowPosition-1;
}
