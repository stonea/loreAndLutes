/* Protected under the GNU General Public License read and see copying.txt for details
*/
#ifndef LL_FILEMANAGER_H_
#define LL_FILEMANAGER_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//PhysFS (for directory management functions, e.g. enumerate files)
	#include <physfs.h>
//Aggregates
	#include <vector>
//Dependencies
	#include <string>
	#include <fstream>
	#include <unistd.h>
	#include <asfc/linkedlist.h>
	#include <asfc/utils.h>
	#include <unistd.h>
	using namespace std;

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LL_FileManager
{	public:
	//Type
		//Type
		enum LL_FILE_TYPE
		{	FILETYPE_FILE = 0,
			FILETYPE_DIR,
			FILETYPE_GOBACKDIR
		};
		
		struct LL_FileInfo
		{	string 			sFileName;
			LL_FILE_TYPE	iFileType;
		};

	//- [Construction] -
		LL_FileManager();
		~LL_FileManager();
	//- [File Managment] -
		void EnumerateFiles(string sDir, vector<LL_FileInfo>* poFileInfo);
		void DeleteFile(string sPath);
		void DeleteDir(string sPath);
		void MakeDir(string sSubDir, string sDirName);

	//- [Compression] -
//		void CompressToFile(istream& oIn, string sFileOut);
//		void ExpandFromFile(string sFileIn, ostream& oOut);
		void Archive(ASFC_LinkedList<string>& lsFileList, string sArchiveName);
		string DeArchive(string sArchiveName, string sChangeDirTo = "");
		string ChangeDir(string sPath, string sToDir);
};

#endif
