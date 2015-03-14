/*	Lore And Lutes Object Oriented Programming Language
	By: Andy Stone
	(C) 2002
*********************************************************************************************************/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

#include "class.h"
#include "code.h"
#include "command.h"
#include "info.h"
#include "instance.h"
#include "label.h"
#include "parameters.h"
#include "parammap.h"
#include "variables.h"
#include "reader.h"

#include "callbacklibrary.h"
#include "instanceset.h"
#include "interpreter.h"

#include "loop.h"
#include "looplib_standard.h"

#include <asfc/screen.h>
#include <asfc/font.h>
#include <asfc/fontpalette.h>
#include <asfc/console.h>
#include <iostream>
using namespace std;


ASFC_Console oCon;
LOOP_LOOP	 oLOOP;

void LOOPCMD_Write(LOOP_Info oInfo, void* pObj)
{	oCon.Write(oInfo.GrabString(0), 0);
}
void LOOPCMD_WriteLn(LOOP_Info oInfo, void* pObj)
{	oCon.Write(oInfo.GrabString(0) + "\n", 0);
}

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Main
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
int main(int argc, char *argv[])
{	fstream oFile;
	oFile.open("test.txt", ios::in);
	char(c);
	oFile.get(c);
	cerr << c << endl;
	c = oFile.peek();
	cerr << c << endl;
	c = oFile.peek();
	cerr << c << endl;

	return 1;
}
