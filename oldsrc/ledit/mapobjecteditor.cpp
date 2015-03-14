/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			mapobjecteditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//											Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "mapobjecteditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//										 LEDIT_MapObjectEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_MapObjectEditor::LEDIT_MapObjectEditor()
{
}
//-------------------------------------------------------------------------------------------- [Plotting] -
void LEDIT_MapObjectEditor::PlotNewInstance(LL_Game* poGame, LEDIT_ClassSetEditor* poClassSetEditor,
											int iX, int iY, int iLayer)
{	//Vars
		string	sIdentifier = "";
		string	sClass;
		string  sImageFile;
		LL_ScriptedUnit oNewUnit;
	//Map params to vars
		mypoGame			= poGame;
		mypoClassSetEditor	= poClassSetEditor;
	//Ask which class set, if global
		if(mypoPainter->PromptKey(SDLK_g, SDLK_l,
  								  "What class set holds the class this instance derive from?",
	          				   	  "(G) Global", "(L) Local", FONT_HIGHLIGHT))
 		{	//Grab class
				sClass = poClassSetEditor->GrabClass(poGame, &poGame->GlobalClassSet());
		}
		else
		{	sClass = poClassSetEditor->GrabClass(poGame, &poGame->ClassSet());
		}
		
	//If a valid class was returned
		if(sClass != "")
		{	//Grab a valid identifier
	  			while(sIdentifier == "")
				{	mypoPainter->MainConsole().Write("===================================================", 2);
					mypoPainter->MainConsole().CurrentFont(0);
					mypoPainter->MainConsole() << "What would you like the instance's identifier to be?\n";
					mypoPainter->MainConsole().CurrentFont(1);
					mypoPainter->MainConsole() << ">";
					mypoPainter->MainConsole() >> sIdentifier;
				
     				//Make sure sIdentifier is valid (e.g. not used!)	
     					if(mypoGame->UnitSet().IsScriptedUnit(sIdentifier))
     					{	mypoPainter->MainConsole().CurrentFont(0);
          					mypoPainter->MainConsole() << "\nIdentifier already taken, enter another:\n";
          					sIdentifier = "";
     					}

				}
			//Grab the image file, from the graphics dir
				sImageFile = mypoFileChooser->GrabFile(LL_MapObject__DEFAULT_GRAHPICS_DIR, "*");
				poGame->UnitSet().AddScriptedUnit
    			(	&mypoGame->TerrainMap(),
       				&mypoGame->UnitMap(),
  					&mypoGame->Clock(),
       				&mypoGame->PathNodes(),
          			&mypoGame->EventQueue(),
             		&mypoGame->ItemSet(),
             		sImageFile, LL_MapObject__DEFAULT_GRAHPICS_DIR,
          			sClass, sIdentifier,
            		iX, iY, iLayer
           		);
				poGame->UnitMap().SetUnitOn(iX, iY, iLayer, LL_UnitMap::SEG_SCRIPTED_UNITS,
    										poGame->UnitSet().NumScriptedUnits() - 1);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LEDIT_MapObjectEditor::PlotCopyInstance(LL_Game* poGame, LEDIT_ClassSetEditor* poClassSetEditor,
											 int iCX, int iCY, int iX, int iY, int iL)
{	//Vars
		LL_ScriptedUnit* poScriptedUnit;
		LL_ScriptedUnit oNewUnit;
		string sIdentifier;
		int iLoops = 0;
		
	//Map params to vars
		mypoGame			= poGame;
		mypoClassSetEditor	= poClassSetEditor;

	//If there isn't a top unit don't copy
		if(poGame->UnitMap().TopSegOn(iCX, iCY) != LL_UnitMap::SEG_SCRIPTED_UNITS)
			return;

	//Grab the top scripted units on iCX, iCY
  		poScriptedUnit = &poGame->UnitSet().ScriptedUnit
    	(	poGame->UnitMap().TopOffOn(iCX, iCY)
		);

	//Figure out a unique instance identifier
		sIdentifier = poScriptedUnit->Identifier();
		iLoops = 0;
		while(poGame->UnitSet().IsScriptedUnit(sIdentifier))
		{	sIdentifier = poScriptedUnit->Identifier() + Val(iLoops);
			iLoops++;
		}

	//Create this unit
		poGame->UnitSet().AddScriptedUnit
		(	&mypoGame->TerrainMap(),
       		&mypoGame->UnitMap(),
  			&mypoGame->Clock(),
       		&mypoGame->PathNodes(),
          	&mypoGame->EventQueue(),
            &mypoGame->ItemSet(),
            poScriptedUnit->ImageFile(), mypoGame->GraphicsDir(),
          	poScriptedUnit->Class(), sIdentifier,
            iX, iY, iL
       	);

	//Copy some attributes this unit
		int iUnit = poGame->UnitSet().NumScriptedUnits() - 1;
		poGame->UnitSet().ScriptedUnit(iUnit).SetWeight(poScriptedUnit->Weight());
		poGame->UnitSet().ScriptedUnit(iUnit).SetStrength(poScriptedUnit->Strength());
		poGame->UnitSet().ScriptedUnit(iUnit).SetDexterity(poScriptedUnit->Dexterity());
		poGame->UnitSet().ScriptedUnit(iUnit).SetIntelligence(poScriptedUnit->Intelligence());
		poGame->UnitSet().ScriptedUnit(iUnit).SetMP(poScriptedUnit->MP());
		poGame->UnitSet().ScriptedUnit(iUnit).SetMaxMP(poScriptedUnit->MaxMP());
		poGame->UnitSet().ScriptedUnit(iUnit).SetHP(poScriptedUnit->HP());
		poGame->UnitSet().ScriptedUnit(iUnit).SetMaxHP(poScriptedUnit->MaxHP());
		poGame->UnitSet().ScriptedUnit(iUnit).SetExperience(poScriptedUnit->Experience());
		LL_Vehicle oVehicle;
		oVehicle.SetCode(poScriptedUnit->Vehicle().Code());
		poGame->UnitSet().ScriptedUnit(iUnit).SetVehicle(oVehicle);
	//Copy the vars
		for(int i = 0; i < poScriptedUnit->DefaultStringsValues().Length(); i++)
		{	poGame->UnitSet().ScriptedUnit(iUnit).SetDefaultString(	poScriptedUnit->DefaultStrings()[i],
  																	poScriptedUnit->DefaultStringsValues()[i]);
		}
	//Now add this object to the map objects set and map
		poGame->UnitMap().SetUnitOn(iX, iY, iL, LL_UnitSet::SEG_SCRIPTED_UNITS, iUnit);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LEDIT_MapObjectEditor::PlotTemplateInstance(
	LL_Game* poGame, LEDIT_ClassSetEditor* poClassSetEditor, int iX, int iY,
  	int iLayer, string sTemplateClass, string sBaseName, string sImageFile)
{	//Vars
		LL_ScriptedUnit oNewUnit;
		string sIdentifier;
		int iLoops;
		
	//Map params to vars
		mypoGame			= poGame;
		mypoClassSetEditor	= poClassSetEditor;

	//Figure out a unique instance identifier
		sIdentifier = sBaseName;
		iLoops = 0;
		while(poGame->UnitSet().IsScriptedUnit(sIdentifier))
		{	sIdentifier = sBaseName + Val(iLoops);
			iLoops++;
		}

	//Create this unit
		poGame->UnitSet().AddScriptedUnit
		(	&mypoGame->TerrainMap(),
       		&mypoGame->UnitMap(),
  			&mypoGame->Clock(),
       		&mypoGame->PathNodes(),
          	&mypoGame->EventQueue(),
            &mypoGame->ItemSet(),
            sImageFile, LL_MapObject__DEFAULT_GRAHPICS_DIR,
          	sTemplateClass, sIdentifier,
            iX, iY, iLayer
       	);

	//Copy some attributes this unit
		int iUnit = poGame->UnitSet().NumScriptedUnits() - 1;
	//Now add this object to the map objects set and map
		poGame->UnitMap().SetUnitOn(iX, iY, iLayer, LL_UnitSet::SEG_SCRIPTED_UNITS, iUnit);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LEDIT_MapObjectEditor::PlotArmor(LL_Game* poGame, int iNum, int iX, int iY, int iL)
{	poGame->UnitSet().AddArmor(iX, iY, iL, iNum);
	poGame->UnitMap().SetUnitOn(iX, iY, iL, LL_UnitSet::SEG_ARMORS, poGame->UnitSet().NumArmors() - 1);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LEDIT_MapObjectEditor::PlotWeapon(LL_Game* poGame, int iNum, int iX, int iY, int iL)
{	poGame->UnitSet().AddWeapon(iX, iY, iL, iNum);
	poGame->UnitMap().SetUnitOn(iX, iY, iL, LL_UnitSet::SEG_WEAPONS, poGame->UnitSet().NumWeapons() - 1);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LEDIT_MapObjectEditor::PlotScriptedItem(LL_Game* poGame, int iNum, int iX, int iY, int iL)
{	poGame->UnitSet().AddScriptedItem(iX, iY, iL, iNum);
	poGame->UnitMap().SetUnitOn(iX, iY, iL, LL_UnitSet::SEG_SCRIPTED_ITEMS,
		poGame->UnitSet().NumScriptedItems() - 1);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LEDIT_MapObjectEditor::PlotMonster(LL_Game* poGame, int iNum, int iX, int iY, int iL)
{	if(iNum < 0)
		return;
	
	poGame->UnitSet().AddMonster(iX, iY, iL, poGame->GraphicsDir(), iNum);
	poGame->UnitMap().SetUnitOn(iX, iY, iL, LL_UnitSet::SEG_MONSTERS,
		poGame->UnitSet().NumMonsters() - 1);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LEDIT_MapObjectEditor::PlotChest(LL_Game* poGame, int iX, int iY, int iL, bool fTemplate)
{	//Vars
		string  sImageFile;
		int iUnit;
		
	//Map params to vars
		mypoGame = poGame;
	//Grab the image file, from the graphics dir. Then add in a new chest and load the graphic
		if(!fTemplate)
		{	sImageFile = mypoFileChooser->GrabFile(mypoGame->GraphicsDir(), "*");
		}
		poGame->UnitSet().AddChest(iX, iY, iL);
		iUnit = poGame->UnitSet().NumChests() - 1;
		if(!fTemplate)
		{	poGame->UnitSet().Chest(iUnit).LoadAnimation(sImageFile, poGame->GraphicsDir());
		}
	//Plot this unit on da' map
		poGame->UnitMap().SetUnitOn(iX, iY, iL, LL_UnitMap::SEG_CHESTS, iUnit);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LEDIT_MapObjectEditor::PlotTransport(LL_Game* poGame, int iX, int iY, int iL, bool fTemplate)
{	//Vars
		string  sImageFile;
		int iUnit;
		
	//Map params to vars
		mypoGame = poGame;
	//If this isn't a template
		if(!fTemplate)
		{	//Grab the image file, from the graphics dir. Then add in a new transport and load the graphic
				sImageFile = mypoFileChooser->GrabFile(mypoGame->GraphicsDir(), "*");
		}
	//Plot it
		poGame->UnitSet().AddTransport(iX, iY, iL);
		iUnit = poGame->UnitSet().NumTransports() - 1;
		if(!fTemplate)
		{	poGame->UnitSet().Transport(iUnit).LoadAnimation(sImageFile, poGame->GraphicsDir());
		}
	//Plot this unit on da' map
		poGame->UnitMap().SetUnitOn(iX, iY, iL, LL_UnitMap::SEG_TRANSPORTS, iUnit);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LEDIT_MapObjectEditor::PlotVehicleObject(LL_Game* poGame, int iNum, int iX, int iY, int iL)
{	//Vars
		string  sImageFile;
		int iUnit;
	//Place it
		poGame->UnitSet().AddVehicle(iX, iY, iL, sImageFile, iNum);
		iUnit = poGame->UnitSet().NumVehicles() - 1;
		poGame->UnitMap().SetUnitOn(iX, iY, iL, LL_UnitSet::SEG_VEHICLES, iUnit);
}
