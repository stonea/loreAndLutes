/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			datarecorder.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Runner
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "datarecorder.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//											LL_DataRecorder
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LL_DataRecorder::LL_DataRecorder()
{	SetBaseName();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_DataRecorder::~LL_DataRecorder()
{	//Vars
		vector<LL_FileManager::LL_FileInfo> myoFiles;
		string ts;

	//Be good and clean up this mess
		//Enumerate all files in the temp directory
			mypoFileManager->EnumerateFiles(LL_DataRecorder_RUNNING_INFO, &myoFiles);
		//Loop through 'em
			for(int i = 0; i < myoFiles.size(); i++)
			{	//If this file is prefixed with the base name then its. Diggidy diggidy DELETED!
					if(myoFiles[i].sFileName.substr(0, sBaseName.size()) == sBaseName)
					{	ts =  LL_DataRecorder_RUNNING_INFO;
						ts += "/";
      					ts += myoFiles[i].sFileName;
						mypoFileManager->DeleteFile(ts);
					}
			}
	//Delete the game information file
		mypoFileManager->DeleteFile(GameInfoFile());
}
//------------------------------------------------------------------------------------------- [Recording] -
void LL_DataRecorder::RecordInformation(int iMap)
{	//Vars
		string sFileToSave;
		ofstream oFile;
		
	//Figure out what file we're saving the information to
		sFileToSave = LL_DataRecorder_RUNNING_INFO;
	 	sFileToSave += "/" + FileName(iMap) + ".save";
	//Now save it
  		oFile.open(sFileToSave.c_str());
		mypoUnitSet->SaveRecordingInfo(oFile);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_DataRecorder::LoadInformation(int iMap, string sGraphicsDir)
{	//Vars
		string sFileToSave;
		ifstream oFile;
	
	//Figure out what file we're saving the information to
		sFileToSave =  LL_DataRecorder_RUNNING_INFO;
  		sFileToSave += "/" + FileName(iMap) + ".save";
	//Now load it
  		oFile.open(sFileToSave.c_str());
  		if(oFile.is_open())
			mypoUnitSet->LoadRecordingInfo(oFile, sGraphicsDir);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_DataRecorder::SaveGame(string sFileName)
{	//Vars
		vector<LL_FileManager::LL_FileInfo> myoFiles;
		ASFC_LinkedList<string> mysFileNames;
		string ts;

	//Get a list of all the files that need to be saved
		//Add the game information file
			mysFileNames.Push(GameInfoFile());
		//Enumerate all files in the temp directory
			mypoFileManager->EnumerateFiles(LL_DataRecorder_RUNNING_INFO, &myoFiles);
		//Loop through 'em
			for(int i = 0; i < myoFiles.size(); i++)
			{	//If this file is prefixed with the base name then its than it needs not be saved
					if(myoFiles[i].sFileName.substr(0, sBaseName.size()) == sBaseName)
					{	ts =  LL_DataRecorder_RUNNING_INFO;
						ts += "/";
      					ts += myoFiles[i].sFileName;
						mysFileNames.Push(ts);
					}
			}
	//Save this
		mypoFileManager->Archive(mysFileNames, sFileName);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_DataRecorder::LoadGame(string sFileName, string sGraphicsDir)
{	//Vars
		string sExpandedFile;
	//Dearchive this sucker!
		sExpandedFile = mypoFileManager->DeArchive(sFileName);
	//Reset the base name to that of the first expanded file
		sBaseName = ExtractBaseName(sExpandedFile);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LL_DataRecorder::File(int iMap)
{	//Vars
		string sFile;
	//Figure out what file we're saving the information to
		sFile =  LL_DataRecorder_RUNNING_INFO;
  		sFile += "/" + FileName(iMap) + ".save";
	//Return it
		return(sFile);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
string LL_DataRecorder::GameInfoFile()
{	//Vars
		string sFile;
	//Figure out what file we're saving the information to
		sFile =  LL_DataRecorder_RUNNING_INFO;
  		sFile += "/" + sBaseName + '_' + "game.save";
	//Return it
		return(sFile);
}
//P----------------------------------------------------------------------------------- [File management] -P
void LL_DataRecorder::SetBaseName()
{	//vars
		time_t oTime;

	//Getime
		time(&oTime);
	//Form the name
		sBaseName = Val(oTime);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
string LL_DataRecorder::FileName(int iMap)
{	return(sBaseName + '_' + Val(iMap));
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
string LL_DataRecorder::ExtractBaseName(string sFile)
{	//Vars
		int iPosition;

	//Grab where the directory marker is
		iPosition = sFile.rfind("/", sFile.size());
	//Extract everything after that
		sFile = sFile.substr(iPosition + 1, sFile.size() - iPosition);
	//Grab where the map name is
		iPosition = sFile.rfind("_", sFile.size());
	//Extract everything before that
		sFile = sFile.substr(0, iPosition);
	//This is the base name
		return(sFile);
}
