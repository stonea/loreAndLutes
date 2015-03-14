//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "filemanager.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//											 ASFC_FileManager
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
ASFC_FileManager::ASFC_FileManager()
{	PHYSFS_init("");
	char pathname[1024];
	getwd(pathname);
	PHYSFS_addToSearchPath(pathname, 0);
	PHYSFS_setWriteDir(pathname);
cerr << "===========================================================\n";
cerr << "ADDED: " << pathname << endl;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
ASFC_FileManager::~ASFC_FileManager()
{//	PHYSFS_deinit();
}
//------------------------------------------------------------------------------------- [File Managment] -
void ASFC_FileManager::EnumerateFiles(string sDir, vector<ASFC_FileInfo>* poFileInfo)
{	//Vars
cerr << "Enumerated!\n";
		string s;
		string sFullPath;
		ASFC_FileInfo toFileInfo;
		
	//Use PhysFS to Enumerate files
		char **rc = PHYSFS_enumerateFiles(sDir.c_str());
		char **i;

	//Resize the list to zero (so old data will run away trembeling in little linked list fear!!)
  		poFileInfo->resize(0);

	//Loop through all the enumerated files, translate each to a string and put it onto the list
		for (i = rc; *i != NULL; i++)
	    {	//Convert the physFS filename to a C++ string
				s = *i;
			//Grab the full path name of this file
				if(sDir.length() > 0)
					sFullPath = sDir + "/" + s;
				else
					sFullPath = s;
				
			//Push this information into a file info struct
    			toFileInfo.sFileName = s;    			
				
     		//Figure out what type of file we're dealing with here
				if(PHYSFS_isDirectory(sFullPath.c_str()) != 0)
					toFileInfo.iFileType = FILETYPE_DIR;
				else
					toFileInfo.iFileType = FILETYPE_FILE;
	    	
	    	//Push this information into an ASFC list	    	
				poFileInfo->push_back(toFileInfo);
    	}

	//Free the PhysFS list
		PHYSFS_freeList(rc);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_FileManager::DeleteFile(string sPath)
{	//Do it
//		PHYSFS_delete(sPath.c_str());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_FileManager::DeleteDir(string sPath)
{	//Do it
//		PHYSFS_delete(sPath.c_str());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_FileManager::MakeDir(string sSubDir, string sDirName)
{	//Switch write dir
		PHYSFS_setWriteDir(sSubDir.c_str());
	//Make it
		PHYSFS_mkdir(sDirName.c_str());
	//Switch write dir back
		PHYSFS_setWriteDir(PHYSFS_getBaseDir());
}
//---------------------------------------------------------------------------------------- [Compression] -
void ASFC_FileManager::CompressToFile(istream& oIn, string sFileOut)
{	//Const
		const static int BUFFER_MAX = 512;
	//Vars
		gzFile oFile;
		char* strDataIn;
		int iCharsRead;
		strDataIn = new char[BUFFER_MAX];
		
	//Open up a file to write compressed data to
		oFile = gzopen(sFileOut.c_str(), "wb");
	//Until we reach the end read some data in and output it to the gzstream
		while(!oIn.eof())
		{	oIn.read(strDataIn, BUFFER_MAX);
			iCharsRead = oIn.gcount();
 			gzwrite(oFile, strDataIn, iCharsRead);
 			gzflush(oFile, Z_FULL_FLUSH);
		}
 	//Close the output file up
		gzclose(oFile);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_FileManager::ExpandFromFile(string sFileIn, ostream& oOut)
{	//Const
		const static int BUFFER_MAX = 512;
	//Vars
		gzFile oFile;
		char cBuffer[BUFFER_MAX];
		int iCharsRead;

 	//Open up the compressed input file for reading
		oFile = gzopen(sFileIn.c_str(), "rb");
	//Until we've reached the end read some compressed data in, uncompress it and stash it in oOut
		while(!gzeof(oFile))
		{	iCharsRead = gzread(oFile, cBuffer, BUFFER_MAX);
			oOut.write (cBuffer, iCharsRead);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
/* Archive format:
   <file 1>
   <file 2>
   ...
   <file n-1>
   <file n>
   <# representing location of file 1>
   ...
   <# representing location of file n>
   <# representing location of the first number>
*/
//  TODO: Check to make sure no |s exist in the file names!!!
void ASFC_FileManager::Archive(ASFC_LinkedList<string>& lsFileList, string sArchiveName)
{	//Const
		const static int BUFFER_MAX = 512;
	//Vars
		ASFC_LinkedList<long> ldFileOffset;
		ifstream oFileIn;
		ofstream oFileOut;
		gzFile oArchiveFile;
		char* strDataIn;
		int iCharsRead, iCharsToWrite;
		strDataIn = new char[BUFFER_MAX];
		long dLastOffset;
		
	//Size the offset list to the size of the file list
		ldFileOffset.Resize(lsFileList.Length());
	//Open up the compressed input file for writing
		oArchiveFile = gzopen(sArchiveName.c_str(), "wb");
	//Loop through each file to archive
		for(int i = 0; i < lsFileList.Length(); i++)
		{	//Open this file
	  			oFileIn.open(lsFileList[i].c_str());
	  		//Record what offset this file is starting at
	  			ldFileOffset[i] = gztell(oArchiveFile);
			//Until we reach the end read some data in and output it to the gzstream
				while(!oFileIn.eof())
				{	oFileIn.read(strDataIn, BUFFER_MAX);
					iCharsRead = oFileIn.gcount();
 					gzwrite(oArchiveFile, strDataIn, iCharsRead);
		 			gzflush(oArchiveFile, Z_FULL_FLUSH);
				}
	  		//Close this file
	  			oFileIn.close();
		}
	//Get the current position
		dLastOffset = gztell(oArchiveFile);
	//Close the archive
		gzclose(oArchiveFile);
	//Open the archive to append location data to
		oFileOut.open(sArchiveName.c_str(), ofstream::app);
	//Write a special marker byte
		oFileOut << " | " << dLastOffset << " ";
	//Write the location of the last offset
	//Loop through each file again
		for(int i = 0; i < ldFileOffset.Length(); i++)
  		{	//Write the file name
  				oFileOut << Qoute(lsFileList[i]) << " ";
    		//Write this location
  				oFileOut << ldFileOffset[i];
      		//If this isn't the last entry put a space
        		if(i != ldFileOffset.Length()-1)
	       			oFileOut << " ";
  		}
  	//Close this file
  		oFileOut.close();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_FileManager::DeArchive(string sArchiveName)
{	//Const
		const static int BUFFER_MAX = 512;
	//Vars
		gzFile oFile;
		char cIn;
		char cBuffer[BUFFER_MAX];
		long dCurrentPos;
		int iCharsRead;
		double dOffset;
		long dEndPos;
		ifstream oFileIn;
		ofstream oFileOut;
		string sFileName;
		ASFC_LinkedList<string> lsFileNames;
		ASFC_LinkedList<long> ldFileOffset;
		
	//Open up the compressed file as a normal stream
		oFileIn.open(sArchiveName.c_str());
  	//Read backwards until the special marker character ('|') is found
		dCurrentPos = -1;
  		oFileIn.seekg(dCurrentPos, ios::end);
  		cIn = ' ';
  		while(cIn != '|')
  		{	oFileIn.get(cIn);
  			dCurrentPos--;
	  		oFileIn.seekg(dCurrentPos, ios::end);
 		}
 	//Move the cursor down past the marker
 		dCurrentPos += 2;
  		oFileIn.seekg(dCurrentPos, ios::end);
	//Read in the end of the last file thingy
		oFileIn >> dEndPos;
  	//Read in the offset information
		while(!oFileIn.eof())
  		{	sFileName = ReadString(oFileIn);
    		oFileIn >> dOffset;
	  		cerr << sFileName << " " << dOffset << endl;
	  		lsFileNames.Push(sFileName);
    		ldFileOffset.Push(dOffset);
  		}
		ldFileOffset.Push(dEndPos);
  	//Close this file
  		oFileIn.close();
 	//Open up the compressed input file for reading
		oFile = gzopen(sArchiveName.c_str(), "rb");
	//Loop through each file
		for(int i = 0; i < lsFileNames.Length(); i++)
		{	//Open up the output file
				oFileOut.open(lsFileNames[i].c_str());
			//Set the cursor in the compreseed string to where this file begins
				gzseek(oFile, ldFileOffset[i], SEEK_SET);
			//Figure out the end position. It's the next file offset.
				dEndPos = ldFileOffset[i+1];
			//Keep reading until the next block would go past the end of the file
				while(gztell(oFile) + BUFFER_MAX < dEndPos)
				{	iCharsRead = gzread(oFile, cBuffer, BUFFER_MAX);
					oFileOut.write(cBuffer, iCharsRead);
				}
			//Read in the last partial block
				iCharsRead = gzread(oFile, cBuffer, dEndPos - gztell(oFile));
				oFileOut.write(cBuffer, iCharsRead);
			//Close the output file
				oFileOut.close();
		}
	//Close the archive
		gzclose(oFile);
	//Until we've reached the end read some compressed data in, uncompress it and stash it in oOut
//		while(!gzeof(oFile))
	//	{	iCharsRead = gzread(oFile, cBuffer, BUFFER_MAX);
//			oOut.write (cBuffer, iCharsRead);
	//	}
}
