#ifndef ASFC_FILEMANAGER_H_
#define ASFC_FILEMANAGER_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Define (FOR WINDOWS !!!!)
//	#define _WINDOWS
//	#define ZLIB_DLL
//ZLib for file compression
	#include <zlib.h>
//PhysFS (for directory management functions, e.g. enumerate files)
	#include <physfs.h>
//Aggregates
	#include <vector>
//Dependencies
	#include <string>
	#include <fstream>
	#include <asfc/linkedlist.h>
	#include <asfc/utils.h>
	#include <unistd.h>
	using namespace std;

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class ASFC_FileManager
{	public:
	//Type
		//Type
		enum ASFC_FILE_TYPE
		{	FILETYPE_FILE = 0,
			FILETYPE_DIR,
			FILETYPE_GOBACKDIR
		};
		
		struct ASFC_FileInfo
		{	string 			sFileName;
			ASFC_FILE_TYPE	iFileType;
		};

	//- [Construction] -
		ASFC_FileManager();
		~ASFC_FileManager();
	//- [File Managment] -
		void EnumerateFiles(string sDir, vector<ASFC_FileInfo>* poFileInfo);
		void DeleteFile(string sPath);
		void DeleteDir(string sPath);
		void MakeDir(string sSubDir, string sDirName);
	//- [Compression] -
		void CompressToFile(istream& oIn, string sFileOut);
		void ExpandFromFile(string sFileIn, ostream& oOut);
		void Archive(ASFC_LinkedList<string>& lsFileList, string sArchiveName);
		void DeArchive(string sArchiveName);
};

#endif
