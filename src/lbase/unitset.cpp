/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			unitset.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "unitset.h"
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_UnitSet
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_UnitSet::LL_UnitSet()
{
}
//---------------------------------------------------------------------------- [General Unit Management] -
void LL_UnitSet::Clear()
{	myloScriptedUnits.Resize(0);
 	myloMonsters.Resize(0);
 	myloArmors.Resize(0);
 	myloWeapons.Resize(0);
 	myloScriptedItems.Resize(0);
 	myloChests.Resize(0);
 	myloGuts.Resize(0);
	myloTransports.Resize(0);
	myloVehicleObjects.Resize(0);
	myiOnlyRunUnit = -1;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitSet::RemoveUnit(int iSeg, int iOff)
{	//Vars
		int iMax = 0;
	//Decide what to do based on that seg
		switch(iSeg)
		{	case SEG_SCRIPTED_ITEMS:
			{	myloScriptedItems.Delete(iOff);
			}break;

			case SEG_WEAPONS:
			{	myloWeapons.Delete(iOff);
			}break;

			case SEG_ARMORS:
			{	myloArmors.Delete(iOff);
			}break;

			case SEG_MONSTERS:
			{	myloMonsters.Delete(iOff);
				iMax = NumMonsters();
			}break;
			
			case SEG_CHESTS:
			{	myloChests.Delete(iOff);
				iMax = NumChests();
			}break;
			
			case SEG_TRANSPORTS:
			{	myloTransports.Delete(iOff);
				iMax = NumTransports();
			}break;

			case SEG_SCRIPTED_UNITS:
			{	myloScriptedUnits.Delete(iOff);
				iMax = NumScriptedUnits();
			}break;

			case SEG_VEHICLES:
			{	myloVehicleObjects.Delete(iOff);
			}break;

			case SEG_SPAWNER:
			{	myloSpawners.Delete(iOff);
			}

			default: break;
		}
		
	//Promote all higher units within the same seg
		for(int i = iOff; i < iMax; i++)
		{	//Decide what to do based on the seg
				switch(iSeg)
				{	case SEG_SCRIPTED_ITEMS:
					{
					}break;

					case SEG_WEAPONS:
					{
					}break;

					case SEG_ARMORS:
					{
					}break;
	
					case SEG_MONSTERS:
					{	myloMonsters[i].SetOff(i);
					}break;
	
					case SEG_SCRIPTED_UNITS:
					{	myloScriptedUnits[i].SetOff(i);
					}break;
					
					case SEG_CHESTS:
					{	myloChests[i].SetOff(i);
					}break;
					
					case SEG_GUTS:
					{	myloGuts[i].SetOff(i);
					}break;

					case SEG_TRANSPORTS:
					{	myloTransports[i].SetOff(i);
					}break;

					case SEG_VEHICLES:
					{
					}break;

					case SEG_SPAWNER:
					{
					}break;
	
					default: break;
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitSet::Run()
{	//Loop through all units and run
		if(myiOnlyRunUnit < 0)
		{	//Global Script
				mypoGlobalScript->Run();
   			//Scripted Items
				//Don't run
			//Weapons
				//Don't run
			//Armors
				//Don't run
			//Monsters
				for(int i = 0; i < NumMonsters(); i++)
				{	myloMonsters[i]	.Run();
				}
		}
	//ScriptedUnits
		if(myiOnlyRunUnit < 0)
		{	for(int i = 0; i < NumScriptedUnits(); i++)
			{	ScriptedUnit(i).Run();
			}
		}
		else
		{	ScriptedUnit(myiOnlyRunUnit).Run();
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitSet::PlaceUnits()
{	//Clear
		mypoUnitMap->Clear();
	//Loop through scripted items
		for(int i = 0; i < NumScriptedItems(); i++)
		{	mypoUnitMap->SetUnitOn(	myloScriptedItems[i].iX,
   									myloScriptedItems[i].iY,
            						myloScriptedItems[i].iL,
   									SEG_SCRIPTED_ITEMS,
            						myloScriptedItems[i].iNum);
		}
	//Loop through weapons
		for(int i = 0; i < NumWeapons(); i++)
		{	mypoUnitMap->SetUnitOn(	myloWeapons[i].iX,
   									myloWeapons[i].iY,
            						myloWeapons[i].iL,
   									SEG_WEAPONS,
            						myloWeapons[i].iNum);
		}
	//Loop through armors
		for(int i = 0; i < NumArmors(); i++)
		{	mypoUnitMap->SetUnitOn(	myloArmors[i].iX,
   									myloArmors[i].iY,
            						myloArmors[i].iL,
   									SEG_ARMORS,
            						myloArmors[i].iNum);
		}
	//Loop through Monsters
		for(int i = 0; i < NumMonsters(); i++)
		{	mypoUnitMap->SetUnitOn(	myloMonsters[i].X(),
									myloMonsters[i].Y(),
									myloMonsters[i].Layer(),
									myloMonsters[i].Seg(),
									myloMonsters[i].Off());
		}
	//Loop through Chests
		for(int i = 0; i < NumChests(); i++)
		{	mypoUnitMap->SetUnitOn(	myloChests[i].X(),
									myloChests[i].Y(),
									myloChests[i].Layer(),
									myloChests[i].Seg(),
									myloChests[i].Off());
		}
	//Loop through Transports
		for(int i = 0; i < NumTransports(); i++)
		{	mypoUnitMap->SetUnitOn(	myloTransports[i].X(),
									myloTransports[i].Y(),
									myloTransports[i].Layer(),
									myloTransports[i].Seg(),
									myloTransports[i].Off());
		}
	//Loop through ScriptedUnits
		for(int i = 0; i < NumScriptedUnits(); i++)
		{	mypoUnitMap->SetUnitOn(	myloScriptedUnits[i].X(),
									myloScriptedUnits[i].Y(),
									myloScriptedUnits[i].Layer(),
									myloScriptedUnits[i].Seg(),
									myloScriptedUnits[i].Off());
		}
	//Loop through vehicles
		for(int i = 0; i < NumVehicles(); i++)
		{	mypoUnitMap->SetUnitOn(	myloVehicleObjects[i].iX,
   									myloVehicleObjects[i].iY,
            						myloVehicleObjects[i].iL,
   									SEG_VEHICLES,
            						myloVehicleObjects[i].iNum);
		}

}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_UnitSet::Save(ofstream &oFile)
{	//~.obj 0~
		oFile << ".obj 0";
	//[Check]
		oFile << " ! ";
	//<Save Scripted Items>
		oFile << NumScriptedItems() << " ";
		for(int i = 0; i < NumScriptedItems(); i++)
		{	//%iX% %iY% %iL% %Num%
				oFile << myloScriptedItems[i].iX << " " << myloScriptedItems[i].iY << " " << 
    			myloScriptedItems[i].iL << " " << myloScriptedItems[i].iNum << endl;
		}
	//[Check]
		oFile << " ! ";
	//<Save Weapons>
		oFile << NumWeapons() << " ";
		for(int i = 0; i < NumWeapons(); i++)
		{	//%iX% %iY% %iL% %Num%
				oFile << myloWeapons[i].iX << " " << myloWeapons[i].iY << " " << 
    			myloWeapons[i].iL <<  " " << myloWeapons[i].iNum << endl;
		}
	//[Check]
		oFile << " ! ";
	//<Save Armors>
		oFile << NumArmors() << " ";
		for(int i = 0; i < NumArmors(); i++)
		{	//%iX% %iY% %iL% %Num%
				oFile << myloArmors[i].iX << " " << myloArmors[i].iY << " " << 
    			myloArmors[i].iL << " " << myloArmors[i].iNum << endl;
		}
	//[Check]
		oFile << " ! ";
	//<Save Monsters>
		oFile << NumMonsters() << " ";
		for(int i = 0; i < NumMonsters(); i++)
		{	//%iX% %iY% %iL% %iNum%
				oFile << int(myloMonsters[i].X()) << " " << int(myloMonsters[i].Y()) << " "
					  << int(myloMonsters[i].Layer()) << " " << int(myloMonsters[i].Template())
					  << endl;
		}
	//[Check]
		oFile << " ! ";
	//<Save VehicleObjects>
		oFile << NumVehicles() << " ";
		for(int i = 0; i < NumVehicles(); i++)
		{	//%iX% %iY% %iL% %iNum%
				oFile << myloVehicleObjects[i].iX << " " << myloVehicleObjects[i].iY << " " << 
    			myloVehicleObjects[i].iL << " " << myloVehicleObjects[i].iNum << endl;
		}
	//[Check]
		oFile << " ! ";
	//<Save Chests>
		oFile << NumChests() << " ";
		for(int i = 0; i < NumChests(); i++)
		{	Chest(i).Save(oFile);
			oFile << " ";
		}
	//[Check]
		oFile << " ! ";
	//<Save Transports>
		oFile << NumTransports() << " ";
		for(int i = 0; i < NumTransports(); i++)
		{	Transport(i).Save(oFile);
			oFile << " ";
		}
	//[Check]
		oFile << " ! ";
	//<Save Spawners>
		oFile << NumSpawners() << " ";
		for(int i = 0; i < NumSpawners(); i++)
		{	myloSpawners[i].Save(oFile);
		}
	//[Check]
		oFile << " ! ";
	//<Save ScriptedUnits>
		oFile << NumScriptedUnits() << " ";
		for(int i = 0; i < NumScriptedUnits(); i++)
		{	ScriptedUnit(i).Save(oFile);
			oFile << " ";
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_UnitSet::Load(ifstream &oFile, string sGraphicsDir)
{	//Vars
		string sType;
		int iVer;
		int iNumScriptedItems, iNumWeapons, iNumArmors, iNumMonster, iNumChests, iNumTransports,
			iNumScriptedUnits, iNumVehicleObjs, iNumSpawners;
		int iX, iY, iL, iNum;
		char cTest;

	//Set defaults
		myiOnlyRunUnit = -1;
	//~.obj 0~
		oFile >> sType >> iVer;
		if(sType != ".obj" || iVer != 0)
			return false;
	//[Check]
		oFile >> cTest;
		if(cTest != '!') cerr << "Bad .obj file. Err loading. ERR Stop 1.\n";
	//<Load Scripted Items>
		oFile >> iNumScriptedItems;
		myloScriptedItems.Resize(iNumScriptedItems);
		for(int i = 0; i < NumScriptedItems(); i++)
		{	//%iX% %iY% %iL% %Num%
				oFile >> myloScriptedItems[i].iX;
				oFile >> myloScriptedItems[i].iY;
				oFile >> myloScriptedItems[i].iL;
				oFile >> myloScriptedItems[i].iNum;
			//Plot it
				mypoUnitMap->SetUnitOn(	myloScriptedItems[i].iX, myloScriptedItems[i].iY,
										myloScriptedItems[i].iL, SEG_SCRIPTED_ITEMS,
          								i);
		}
	//[Check]
		oFile >> cTest;
		if(cTest != '!') cerr << "Bad .obj file. Err loading. ERR Stop 2.\n";
	//<Load Weapons>
		oFile >> iNumWeapons;
		myloWeapons.Resize(iNumWeapons);
		for(int i = 0; i < NumWeapons(); i++)
		{	//%iX% %iY% %iL% %Num%
				oFile >> myloWeapons[i].iX;
				oFile >> myloWeapons[i].iY;
				oFile >> myloWeapons[i].iL;
				oFile >> myloWeapons[i].iNum;
			//Plot it
				mypoUnitMap->SetUnitOn(	myloWeapons[i].iX, myloWeapons[i].iY,
										myloWeapons[i].iL, SEG_WEAPONS,
          								i);
		}
	//[Check]
		oFile >> cTest;
		if(cTest != '!') cerr << "Bad .obj file. Err loading. ERR Stop 3.\n";
	//<Load Armors>
		oFile >> iNumArmors;
		myloArmors.Resize(iNumArmors);
		for(int i = 0; i < NumArmors(); i++)
		{	//%iX% %iY% %iL% %Num%
				oFile >> myloArmors[i].iX;
				oFile >> myloArmors[i].iY;
				oFile >> myloArmors[i].iL;
				oFile >> myloArmors[i].iNum;
			//Plot it
				mypoUnitMap->SetUnitOn(	myloArmors[i].iX, myloArmors[i].iY,
										myloArmors[i].iL, SEG_ARMORS,
          								i);
		}
	//[Check]
		oFile >> cTest;
		if(cTest != '!') cerr << "Bad .obj file. Err loading. ERR Stop 4.\n";
	//<Load Monsters>
		oFile >> iNumMonster;
		myloMonsters.Resize(0);
		for(int i = 0; i < iNumMonster; i++)
		{	//%iX% %iY% %iL% %iNum%
				oFile >> iX >> iY >> iL >> iNum;
			//Add this monster
				AddMonster(iX, iY, iL, sGraphicsDir, iNum);
				mypoUnitMap->SetUnitOn(iX, iY, iL, SEG_MONSTERS, NumMonsters() - 1);
		}
	//[Check]
		oFile >> cTest;
		if(cTest != '!') cerr << "Bad .obj file. Err loading. ERR Stop 5.\n";
	//<Load Vehicle Objects>
		oFile >> iNumVehicleObjs;
		myloVehicleObjects.Resize(0);
		for(int i = 0; i < iNumVehicleObjs; i++)
		{	//%iX% %iY% %iL% %iNum%
				oFile >> iX >> iY >> iL >> iNum;
			//Add this vehicle
				AddVehicle(iX, iY, iL, sGraphicsDir, iNum);
				mypoUnitMap->SetUnitOn(iX, iY, iL, SEG_VEHICLES, NumVehicles() - 1);
		}
	//[Check]
		oFile >> cTest;
		if(cTest != '!') cerr << "Bad .obj file. Err loading. ERR Stop 5.\n";
	//<Load Chests>
		oFile >> iNumChests;
		myloChests.Resize(iNumChests);
		for(int i = 0; i < iNumChests; i++)
		{	//Load & Plot
  				myloChests[i].Load(oFile, sGraphicsDir);
  				myloChests[i].SetSeg(SEG_CHESTS);
  				myloChests[i].SetOff(i);
  				myloChests[i].SetEventQueue(mypoEventQueue);
				mypoUnitMap->SetUnitOn(Chest(i).X(), Chest(i).Y(), int(Chest(i).Layer()), SEG_CHESTS, i);
		}
	//[Check]
		oFile >> cTest;
		if(cTest != '!') cerr << "Bad .obj file. Err loading. ERR Stop 6.\n";
	//<Load Transports>
		oFile >> iNumTransports;
		myloTransports.Resize(iNumTransports);
		for(int i = 0; i < iNumTransports; i++)
		{	//Load & Plot
  				myloTransports[i].Load(oFile, sGraphicsDir);
  				myloTransports[i].SetSeg(SEG_TRANSPORTS);
  				myloTransports[i].SetOff(i);
  				myloTransports[i].SetEventQueue(mypoEventQueue);
				mypoUnitMap->SetUnitOn(	Transport(i).X(), Transport(i).Y(),
										int(Transport(i).Layer()), SEG_TRANSPORTS, i);
		}

	//[Check]
		oFile >> cTest;
		if(cTest != '!') cerr << "Bad .obj file. Err loading. ERR Stop 6.1\n";
	//<Load Spawners>
		oFile >> iNumSpawners;
		myloSpawners.Resize(iNumSpawners);
		for(int i = 0; i < NumSpawners(); i++)
		{	myloSpawners[i].Load(oFile, sGraphicsDir);
		}
	//[Check]
		oFile >> cTest;
		if(cTest != '!') cerr << "Bad .obj file. Err loading. ERR Stop 6.1\n";
	//<Load ScriptedUnits>
		//mypoLOOP->ClearInstances();
		oFile >> iNumScriptedUnits;
		myloScriptedUnits.Resize(iNumScriptedUnits);
		for(int i = 0; i < NumScriptedUnits(); i++)
		{	//Give the scripted unit its basic knowledge
				ScriptedUnit(i).SetTerrainMap(mypoTerrainMap);
	  			ScriptedUnit(i).SetUnitMap(mypoUnitMap);
	  			ScriptedUnit(i).SetClock(mypoGameClock);
	  			ScriptedUnit(i).SetCLList(mypoCLList);
				ScriptedUnit(i).SetSeg(SEG_SCRIPTED_UNITS);
				ScriptedUnit(i).SetPathNodes(mypoPathNodes);
				ScriptedUnit(i).SetItemSet(mypoItemSet);
				ScriptedUnit(i).SetOff(i);
				ScriptedUnit(i).SetEventQueue(mypoEventQueue);
				
			//!!! More ???
			//Load er' up
	  			ScriptedUnit(i).Load(oFile, sGraphicsDir);
			//Create an instance if the class exists
				if(mypoLOOP->IsClass(ScriptedUnit(i).Class()))
				{	mypoLOOP->NewInstance(ScriptedUnit(i).Class(), ScriptedUnit(i).Identifier(),
										  SCOPE_LOCAL);
				}
				else
					DisplayMessage( "Error loading units set:",
									"Map contains instances of classes that do not exist.",
									"Please delete them.");
		}
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_UnitSet::SaveRecordingInfo(ofstream &oFile)
{ //Vars
	  unsigned char cX, cY, cL, cSeg;
	  int iOff;

	//Save the load bit and exit position
		oFile << mypoTerrainMap->FirstLoad() << " ";
		oFile << mypoTerrainMap->ExitX() << " " << mypoTerrainMap->ExitY() << " |";
	//<Save Scripted Items>
		oFile << NumScriptedItems() << " ";
		for(int i = 0; i < NumScriptedItems(); i++)
		{	//%iX% %iY% %iL% %Num%
				oFile << myloScriptedItems[i].iX << " " << myloScriptedItems[i].iY << " " << 
    			myloScriptedItems[i].iL << " " << myloScriptedItems[i].iNum << endl;
		}
	//[Check]
		oFile << " ! ";
	//<Save Weapons>
		oFile << NumWeapons() << " ";
		for(int i = 0; i < NumWeapons(); i++)
		{	//%iX% %iY% %iL% %Num%
				oFile << myloWeapons[i].iX << " " << myloWeapons[i].iY << " " << 
    			myloWeapons[i].iL <<  " " << myloWeapons[i].iNum << endl;
		}
	//[Check]
		oFile << " ! ";
	//<Save Armors>
		oFile << NumArmors() << " ";
		for(int i = 0; i < NumArmors(); i++)
		{	//%iX% %iY% %iL% %Num%
				oFile << myloArmors[i].iX << " " << myloArmors[i].iY << " " << 
    			myloArmors[i].iL << " " << myloArmors[i].iNum << endl;
		}
	//[Check]
		oFile << " ! ";
	//<Save Monsters>
		oFile << NumMonsters() << " ";
		for(int i = 0; i < NumMonsters(); i++)
		{	//%iX% %iY% %iL% %iNum%
				oFile << int(myloMonsters[i].X()) << " " << int(myloMonsters[i].Y()) << " "
					  << int(myloMonsters[i].Layer()) << " " << int(myloMonsters[i].Template())
					  << endl;
		}
	//[Check]
		oFile << " ! ";
	//<Save VehicleObjects>
		oFile << NumVehicles() << " ";
		for(int i = 0; i < NumVehicles(); i++)
		{	//%iX% %iY% %iL% %iNum%
				oFile << myloVehicleObjects[i].iX << " " << myloVehicleObjects[i].iY << " " << 
    			myloVehicleObjects[i].iL << " " << myloVehicleObjects[i].iNum << endl;
		}
	//[Check]
		oFile << " ! ";
	//<Save Chests>
		oFile << NumChests() << " ";
		for(int i = 0; i < NumChests(); i++)
		{	Chest(i).Save(oFile);
			oFile << " ";
		}
	//[Check]
		oFile << " ! ";
	//<Save Transports>
		oFile << NumTransports() << " ";
		for(int i = 0; i < NumTransports(); i++)
		{	Transport(i).Save(oFile);
			oFile << " ";
		}
	//[Check]
		oFile << " ! ";
	//<Save Spawners>
		oFile << NumSpawners() << " ";
		for(int i = 0; i < NumSpawners(); i++)
		{	myloSpawners[i].Save(oFile);
		}
	//[Check]
		oFile << " ! ";
	//<Save ScriptedUnits>
		oFile << NumScriptedUnits() << " ";
		for(int i = 0; i < NumScriptedUnits(); i++)
		{	ScriptedUnit(i).SaveRecordingInfo(oFile);
			oFile << " ";
		}
/*	//Loop through all locations saving any unit info
		for(int iLayer = 0; iLayer < LL_UnitMap::MAP_LAYERS; iLayer++)
		{	for(int iY = 0; iY < LL_UnitMap::MAP_HEIGHT; iY++)
			{	for(int iX = 0; iX < LL_UnitMap::MAP_WIDTH; iX++)
				{	if(	mypoUnitMap->SegOn(iX, iY, iLayer) != SEG_NULL &&
    					mypoUnitMap->SegOn(iX, iY, iLayer) != SEG_PLAYER)
					{	//Hold it
							cX = iX;
							cY = iY;
							cL = iLayer;
							cSeg = mypoUnitMap->SegOn(iX, iY, iLayer);
							iOff = mypoUnitMap->OffOn(iX, iY, iLayer);
							

     					//Save it
							oFile.write(&cX, 1);
							oFile.write(&cY, 1);
							oFile.write(&cL, 1);
							oFile.write(&cSeg, 1);
							oFile << iOff << ' ';

                		//If this is a scripted unit save the vars
                			if(cSeg == SEG_SCRIPTED_UNITS)
                			{	ScriptedUnit(iOff).SaveRecordingInfo(oFile);
                			}
					}
				}
			}
		}
*/
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_UnitSet::LoadRecordingInfo(ifstream &oFile, string sGraphicsDir)
{ //Vars
		unsigned char cX, cY, cL, cSeg, tc;
		int iOff;
		bool fFirstLoad;
		string sType;
		int iVer;
		int iNumScriptedItems, iNumWeapons, iNumArmors, iNumMonster, iNumChests, iNumTransports,
			iNumScriptedUnits, iNumVehicleObjs, iNumSpawners;
		int iX, iY, iL, iNum;
		char cTest;
		int iExitX, iExitY;

	//Set defaults
		myiOnlyRunUnit = -1;		
	//Clear out
		Clear();
	//Load the load bit and exit position
		oFile >> fFirstLoad >> iExitX >> iExitY;
		mypoTerrainMap->SetFirstLoad(fFirstLoad);
		mypoTerrainMap->SetExitX(iExitX);
		mypoTerrainMap->SetExitY(iExitY);
		oFile >> tc;		
	//<Load Scripted Items>
		oFile >> iNumScriptedItems;
		myloScriptedItems.Resize(iNumScriptedItems);
		for(int i = 0; i < NumScriptedItems(); i++)
		{	//%iX% %iY% %iL% %Num%
				oFile >> myloScriptedItems[i].iX;
				oFile >> myloScriptedItems[i].iY;
				oFile >> myloScriptedItems[i].iL;
				oFile >> myloScriptedItems[i].iNum;
			//Plot it
				mypoUnitMap->SetUnitOn(	myloScriptedItems[i].iX, myloScriptedItems[i].iY,
										myloScriptedItems[i].iL, SEG_SCRIPTED_ITEMS,
          								i);
		}
	//[Check]
		oFile >> cTest;
		if(cTest != '!') cerr << "Bad .obj file. Err loading. ERR Stop 2.\n";
	//<Load Weapons>
		oFile >> iNumWeapons;
		myloWeapons.Resize(iNumWeapons);
		for(int i = 0; i < NumWeapons(); i++)
		{	//%iX% %iY% %iL% %Num%
				oFile >> myloWeapons[i].iX;
				oFile >> myloWeapons[i].iY;
				oFile >> myloWeapons[i].iL;
				oFile >> myloWeapons[i].iNum;
			//Plot it
				mypoUnitMap->SetUnitOn(	myloWeapons[i].iX, myloWeapons[i].iY,
										myloWeapons[i].iL, SEG_WEAPONS,
          								i);
		}
	//[Check]
		oFile >> cTest;
		if(cTest != '!') cerr << "Bad .obj file. Err loading. ERR Stop 3.\n";
	//<Load Armors>
		oFile >> iNumArmors;
		myloArmors.Resize(iNumArmors);
		for(int i = 0; i < NumArmors(); i++)
		{	//%iX% %iY% %iL% %Num%
				oFile >> myloArmors[i].iX;
				oFile >> myloArmors[i].iY;
				oFile >> myloArmors[i].iL;
				oFile >> myloArmors[i].iNum;
			//Plot it
				mypoUnitMap->SetUnitOn(	myloArmors[i].iX, myloArmors[i].iY,
										myloArmors[i].iL, SEG_ARMORS,
          								i);
		}
	//[Check]
		oFile >> cTest;
		if(cTest != '!') cerr << "Bad .obj file. Err loading. ERR Stop 4.\n";
	//<Load Monsters>
		oFile >> iNumMonster;
		myloMonsters.Resize(0);
		for(int i = 0; i < iNumMonster; i++)
		{	//%iX% %iY% %iL% %iNum%
				oFile >> iX >> iY >> iL >> iNum;
			//Add this monster
				AddMonster(iX, iY, iL, sGraphicsDir, iNum);
				mypoUnitMap->SetUnitOn(iX, iY, iL, SEG_MONSTERS, NumMonsters() - 1);
		}
	//[Check]
		oFile >> cTest;
		if(cTest != '!') cerr << "Bad .obj file. Err loading. ERR Stop 5.\n";
	//<Load Vehicle Objects>
		oFile >> iNumVehicleObjs;
		myloVehicleObjects.Resize(0);
		for(int i = 0; i < iNumVehicleObjs; i++)
		{	//%iX% %iY% %iL% %iNum%
				oFile >> iX >> iY >> iL >> iNum;
			//Add this vehicle
				AddVehicle(iX, iY, iL, sGraphicsDir, iNum);
				mypoUnitMap->SetUnitOn(iX, iY, iL, SEG_VEHICLES, NumVehicles() - 1);
		}
	//[Check]
		oFile >> cTest;
		if(cTest != '!') cerr << "Bad .obj file. Err loading. ERR Stop 5.\n";
	//<Load Chests>
		oFile >> iNumChests;
		myloChests.Resize(iNumChests);
		for(int i = 0; i < iNumChests; i++)
		{	//Load & Plot
  				myloChests[i].Load(oFile, sGraphicsDir);
  				myloChests[i].SetSeg(SEG_CHESTS);
  				myloChests[i].SetOff(i);
  				myloChests[i].SetEventQueue(mypoEventQueue);
				mypoUnitMap->SetUnitOn(Chest(i).X(), Chest(i).Y(), int(Chest(i).Layer()), SEG_CHESTS, i);
		}
	//[Check]
		oFile >> cTest;
		if(cTest != '!') cerr << "Bad .obj file. Err loading. ERR Stop 6.\n";
	//<Load Transports>
		oFile >> iNumTransports;
		myloTransports.Resize(iNumTransports);
		for(int i = 0; i < iNumTransports; i++)
		{	//Load & Plot
  				myloTransports[i].Load(oFile, sGraphicsDir);
  				myloTransports[i].SetSeg(SEG_TRANSPORTS);
  				myloTransports[i].SetOff(i);
  				myloTransports[i].SetEventQueue(mypoEventQueue);
				mypoUnitMap->SetUnitOn(	Transport(i).X(), Transport(i).Y(),
										int(Transport(i).Layer()), SEG_TRANSPORTS, i);
		}
	//[Check]
		oFile >> cTest;
		if(cTest != '!') cerr << "Bad .obj file. Err loading. ERR Stop 7.\n";
	//<Load Spawners>
		oFile >> iNumSpawners;
		myloSpawners.Resize(iNumSpawners);
		for(int i = 0; i < NumSpawners(); i++)
		{	myloSpawners[i].Load(oFile, sGraphicsDir);
		}
	//[Check]
		oFile >> cTest;
		if(cTest != '!') cerr << "Bad .obj file. Err loading. ERR Stop 7.\n";
	//<Load ScriptedUnits>
		//mypoLOOP->ClearInstances();
		oFile >> iNumScriptedUnits;
		myloScriptedUnits.Resize(iNumScriptedUnits);
		for(int i = 0; i < NumScriptedUnits(); i++)
		{	//Give the scripted unit its basic knowledge
				ScriptedUnit(i).SetTerrainMap(mypoTerrainMap);
	  			ScriptedUnit(i).SetUnitMap(mypoUnitMap);
	  			ScriptedUnit(i).SetClock(mypoGameClock);
	  			ScriptedUnit(i).SetCLList(mypoCLList);
				ScriptedUnit(i).SetSeg(SEG_SCRIPTED_UNITS);
				ScriptedUnit(i).SetPathNodes(mypoPathNodes);
				ScriptedUnit(i).SetItemSet(mypoItemSet);
				ScriptedUnit(i).SetOff(i);
				ScriptedUnit(i).SetEventQueue(mypoEventQueue);
				
			//Load er' up
	  			ScriptedUnit(i).LoadRecordingInfo(oFile, sGraphicsDir);
			//Create an instance
				if(mypoLOOP->IsClass(ScriptedUnit(i).Class()))
				{	mypoLOOP->NewInstance(ScriptedUnit(i).Class(), ScriptedUnit(i).Identifier(), SCOPE_LOCAL);
				}
				else
					DisplayMessage( "Error loading units set:",
									"Map contains instances of classes that do not exist.",
									"Please delete them.");
			//Load more
				ScriptedUnit(i).SetLOOP(mypoLOOP);
	  			ScriptedUnit(i).LoadRecordingInfoVars(oFile, sGraphicsDir);
		}
/*
	//Loop through the file loading
		while(!oFile.eof())
		{	//Read in
				oFile.read(&cX, 1);
			 	oFile.read(&cY, 1);
			 	oFile.read(&cL, 1);
				oFile.read(&cSeg, 1);
			if(!oFile.eof())
			{	//Read mas
					oFile >> iOff;
					oFile.read(&tc, 1);
    			//Place a unit here
					mypoUnitMap->SetUnitOn(int(cX), int(cY), int(cL), int(cSeg), iOff);
				//Set this unit's info
					Unit(int(cSeg), iOff).SetX(int(cX));
					Unit(int(cSeg), iOff).SetY(int(cY));
					Unit(int(cSeg), iOff).SetLayer(int(cL));
				//If this is a scripted unit load the vars
    				if(int(cSeg) == SEG_SCRIPTED_UNITS)
        	        {
						ScriptedUnit(iOff).SetLOOP(mypoLOOP);
    	            	ScriptedUnit(iOff).LoadRecordingInfo(oFile);
        			}
			}
		}
*/
}
//------------------------------------------------------------------------- [General Unit Manipulation] -
void LL_UnitSet::ResetAnimations()
{	//Loop through all units reset their animation
		mypoPlayer->Reset();
		for(int i = 0; i < NumScriptedItems(); i++)
		{	//myloScriptedItems[i].Reset();
		}
 		for(int i = 0; i < NumWeapons(); i++)
 		{	//myloWeapons[i].Reset();
		}
 		for(int i = 0; i < NumArmors(); i++)
 		{	//myloArmors[i].Reset();
		}
 		for(int i = 0; i < NumMonsters(); i++)
 		{	myloMonsters[i].Reset();
		}
 		for(int i = 0; i < NumScriptedUnits(); i++)
 		{	myloScriptedUnits[i].Reset();
		}
		for(int i = 0; i < NumVehicles(); i++)
		{	//myloVehicleObjects[i].Reset();
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_Unit& LL_UnitSet::Unit(int iSeg, int iOff)
{	switch(iSeg)
	{	case SEG_SCRIPTED_ITEMS:
		{	return(mypoItemSet->ScriptedItem(myloScriptedItems[iOff].iNum));
		}break;
		
		case SEG_WEAPONS:
		{	return(mypoItemSet->Weapon(myloWeapons[iOff].iNum));
		}break;
		
		case SEG_ARMORS:
		{	return(mypoItemSet->Armor(myloArmors[iOff].iNum));
		}break;
		
		case SEG_MONSTERS:
		{	return(myloMonsters[iOff]);
		}break;
		
		case SEG_SCRIPTED_UNITS:
		{	return(ScriptedUnit(iOff));
		}break;
		
		case SEG_CHESTS:
		{	return(myloChests[iOff]);
		}break;

		case SEG_TRANSPORTS:
		{	return(myloTransports[iOff]);
		}break;
		
		case SEG_VEHICLES:
		{	return(mypoVehicleObjectSet->VehicleObject(myloVehicleObjects[iOff].iNum));
		}
		
		case SEG_PLAYER:
		{	return(*mypoPlayer);
		}break;
		
		default:
			cerr << "Request for invalid unit: " << iSeg << ":" << iOff << endl;
		break;
	};
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_UnitSet::UnitExists(int iSeg, int iOff)
{	switch(iSeg)
	{	case SEG_SCRIPTED_ITEMS:
		{	if(iOff < myloScriptedItems.Length())
			{	if(myloScriptedItems[iOff].iNum < mypoItemSet->NumScriptedItems())
					return true;
			}
		}break;
		
		case SEG_WEAPONS:
		{	if(iOff < myloWeapons.Length())
			{	if(myloWeapons[iOff].iNum < mypoItemSet->NumWeapons())
					return true;
			}
		}break;
		
		case SEG_ARMORS:
		{	if(iOff < myloArmors.Length())
			{	if(myloArmors[iOff].iNum < mypoItemSet->NumArmors())
					return true;
			}
		}break;
		
		case SEG_MONSTERS:
		{	if(iOff < myloMonsters.Length())
				return true;
		}break;
		
		case SEG_SCRIPTED_UNITS:
		{	if(iOff < myloScriptedUnits.Length())
				return true;
		}break;
		
		case SEG_CHESTS:
		{	if(iOff < myloChests.Length())
				return true;
		}break;

		case SEG_TRANSPORTS:
		{	if(iOff < myloTransports.Length())
				return true;
		}break;
		
		case SEG_VEHICLES:
		{	if(iOff < myloVehicleObjects.Length())
			{	if(myloVehicleObjects[iOff].iNum < mypoVehicleObjectSet->NumVehicleObject())
					return true;
			}
		}
		
		case SEG_PLAYER:
		{	return false;
		}break;
		
		break;
	};
	
	return false;
}
//------------------------------------------------------------------------------------------- [Monsters] -
int LL_UnitSet::NumMonsters()
{	return(myloMonsters.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitSet::AddMonster(int iX, int iY, int iL, string sGraphicsPath, int iNum)
{	myloMonsters.Resize(myloMonsters.Length() + 1);
	int iUnit = myloMonsters.Length() - 1;
	
	//Give this monsta' it's basic attributes
		myloMonsters[iUnit].SetTemplate(iNum);
		myloMonsters[iUnit].SetTerrainMap(mypoTerrainMap);
	  	myloMonsters[iUnit].SetUnitMap(mypoUnitMap);
		myloMonsters[iUnit].SetItemSet(mypoItemSet);
	  	myloMonsters[iUnit].SetClock(mypoGameClock);
	  	myloMonsters[iUnit].SetCLList(mypoCLList);
		myloMonsters[iUnit].SetSeg(SEG_MONSTERS);
		myloMonsters[iUnit].SetPathNodes(mypoPathNodes);
		myloMonsters[iUnit].SetOff(iUnit);
		myloMonsters[iUnit].SetEventQueue(mypoEventQueue);
		myloMonsters[iUnit].Place(iX, iY, iL);
	//Make him a monster
		mypoMonsterSet->Monster(iNum).MakeMonster(sGraphicsPath, &myloMonsters[iUnit]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_Monster& LL_UnitSet::Monster(int iOff)
{	return(myloMonsters[iOff]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_UnitSet::MonsterOn(int iX, int iY)
{	//Loop through all layers
		for(int iLayer = 0; iLayer < LL_UnitMap::MAP_LAYERS; iLayer++)
		{	if(mypoUnitMap->SegOn(iX, iY, iLayer) == SEG_MONSTERS)
			{	return(mypoUnitMap->OffOn(iX, iY, iLayer));
			}
		}
		
	//No monsters were found
 		return(-1);	
}
//-------------------------------------------------------------------------------------- [ScriptedUnits] -
int LL_UnitSet::NumScriptedUnits()
{	return(myloScriptedUnits.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_ScriptedUnit& LL_UnitSet::ScriptedUnit(int iOff)
{	return(myloScriptedUnits[iOff]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_ScriptedUnit& LL_UnitSet::ScriptedUnit(string sIdentifier)
{	//Loop through all scripted units
		for(int i = 0; i < NumScriptedUnits(); i++)
		{	if(ScriptedUnit(i).Identifier() == sIdentifier)
				return(ScriptedUnit(i));
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitSet::AddScriptedUnit(LL_ScriptedUnit &oNew)
{	myloScriptedUnits.Push(oNew);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitSet::AddScriptedUnit(LL_TerrainMap* poTerrainMap, LL_UnitMap* poUnitMap,
  								 LL_GameClock* poClock, LL_PathNodes* poPathNodes,
          						 LL_EventQueue* poQueue, LL_ItemSet* poItemSet,
                 				 string sGraphicsFile, string sGraphicsDir, string sClass,
            					 string sIdentifier, int iX, int iY, int iL)
{	//Vars
		int iUnit;

	//Resize for the new unit
		myloScriptedUnits.Resize(myloScriptedUnits.Length() + 1);
		iUnit = myloScriptedUnits.Length() - 1;
	//Give this unit its properties
		myloScriptedUnits[iUnit].SetTerrainMap(mypoTerrainMap);
  		myloScriptedUnits[iUnit].SetUnitMap(mypoUnitMap);
  		myloScriptedUnits[iUnit].SetClock(mypoGameClock);
  		myloScriptedUnits[iUnit].SetCLList(mypoCLList);
  		myloScriptedUnits[iUnit].SetPathNodes(mypoPathNodes);
  		myloScriptedUnits[iUnit].SetEventQueue(mypoEventQueue);
  		myloScriptedUnits[iUnit].SetItemSet(mypoItemSet);
	/*
		myloScriptedUnits[iUnit].SetTerrainMap(poTerrainMap);
  		myloScriptedUnits[iUnit].SetUnitMap(poUnitMap);
  		myloScriptedUnits[iUnit].SetClock(poClock);
  		myloScriptedUnits[iUnit].SetPathNodes(poPathNodes);
  		myloScriptedUnits[iUnit].SetEventQueue(poQueue);
  		myloScriptedUnits[iUnit].SetItemSet(poItemSet);
  		*/
	//Set more props
		myloScriptedUnits[iUnit].SetSeg(SEG_SCRIPTED_UNITS);
		myloScriptedUnits[iUnit].SetOff(iUnit);
  		myloScriptedUnits[iUnit].Place(iX, iY, iL);
		myloScriptedUnits[iUnit].LoadAnimation(sGraphicsFile, sGraphicsDir);
		myloScriptedUnits[iUnit].SetClass(sClass);
		myloScriptedUnits[iUnit].SetIdentifier(sIdentifier);
		//!!! TMP
			LL_Vehicle oVehicle;
			oVehicle.SetCode(0);
		myloScriptedUnits[iUnit].SetVehicle(oVehicle);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_UnitSet::IsScriptedUnit(string sIdentifier)
{	//Vars
		string sCapIdentifier = UpperString(sIdentifier);

	//Loop through all scripted units, if we have an identifier match return true
		for(int i = 0; i < NumScriptedUnits(); i++)
		{	if(UpperString(ScriptedUnit(i).Identifier()) == sCapIdentifier)
				return true;
		}
		
	//If we get here the identifier is free, yay!
		return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitSet::CallLabels(int iPlayerX, int iPlayerY)
{	//If a scripted unit or transport is on the same spopt where the player is on call the appropriate
	//label
		for(int i = 0; i < LL_UnitMap::MAP_LAYERS; i++)
		{	if(mypoUnitMap->SegOn(iPlayerX, iPlayerY, i) == SEG_SCRIPTED_UNITS)
			{	ScriptedUnit(mypoUnitMap->OffOn(iPlayerX, iPlayerY, i)).PlayerOn();
			}
			else if(mypoUnitMap->SegOn(iPlayerX, iPlayerY, i) == SEG_TRANSPORTS)
			{	Transport(mypoUnitMap->OffOn(iPlayerX, iPlayerY, i)).PlayerOn();
			}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitSet::CallInitLabels()
{	//Loop through all scripted units calling the INIT label
		for(int i = 0; i < NumScriptedUnits(); i++)
		{	ScriptedUnit(i).Init();
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitSet::Ping(string sLabel)
{	//Loop through all scripted units calling the label
		for(int i = 0; i < NumScriptedUnits(); i++)
		{	ScriptedUnit(i).Gosub(sLabel);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitSet::PingClass(string sClass, string sLabel)
{	//Capatalize the class name
		sClass = UpperString(sClass);
	//Loop through all scripted units calling the label if it is of class sClass
		for(int i = 0; i < NumScriptedUnits(); i++)
		{	if(sClass == ScriptedUnit(i).Class())
				ScriptedUnit(i).Gosub(sLabel);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitSet::PingClassAndDeriv(string sClass, string sLabel)
{	//Capatalize the class name
		sClass = UpperString(sClass);
	//Loop through all scripted units calling the label if it is of class sClass
		for(int i = 0; i < NumScriptedUnits(); i++)
		{	if(mypoLOOP->IsDerivative(ScriptedUnit(i).Class(), sClass))
				ScriptedUnit(i).Gosub(sLabel);
		}
}
//------------------------------------------------------------------------------------ [Armor Handeling] -
int	LL_UnitSet::NumArmors()
{	return(myloArmors.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitSet::AddArmor(int iX, int iY, int iL, int iNum)
{	myloArmors.Resize(myloArmors.Length() + 1);
	myloArmors[myloArmors.Length() - 1].iX = iX;
	myloArmors[myloArmors.Length() - 1].iY = iY;
	myloArmors[myloArmors.Length() - 1].iL = iL;
	myloArmors[myloArmors.Length() - 1].iNum = iNum;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_UnitSet::ArmorType(int iNum)
{	return(myloArmors[iNum].iNum);
}
//----------------------------------------------------------------------------------- [Weapon Handeling] -
int LL_UnitSet::NumWeapons()
{	return(myloWeapons.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitSet::AddWeapon(int iX, int iY, int iL, int iNum)
{	myloWeapons.Resize(myloWeapons.Length() + 1);
	myloWeapons[myloWeapons.Length() - 1].iX = iX;
	myloWeapons[myloWeapons.Length() - 1].iY = iY;
	myloWeapons[myloWeapons.Length() - 1].iL = iL;
	myloWeapons[myloWeapons.Length() - 1].iNum = iNum;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_UnitSet::WeaponType(int iNum)
{	return(myloWeapons[iNum].iNum);
}
//----------------------------------------------------------------------------- [ScriptedItem Handeling] -
int LL_UnitSet::NumScriptedItems()
{	return(myloScriptedItems.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitSet::AddScriptedItem(int iX, int iY, int iL, int iNum)
{	myloScriptedItems.Resize(myloScriptedItems.Length() + 1);
	myloScriptedItems[myloScriptedItems.Length() - 1].iX = iX;
	myloScriptedItems[myloScriptedItems.Length() - 1].iY = iY;
	myloScriptedItems[myloScriptedItems.Length() - 1].iL = iL;
	myloScriptedItems[myloScriptedItems.Length() - 1].iNum = iNum;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_UnitSet::ScriptedItemType(int iNum)
{	return(myloScriptedItems[iNum].iNum);
}
//------------------------------------------------------------------------------------ [Chest Handeling] -
int LL_UnitSet::NumChests()
{	return(myloChests.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitSet::AddChest(int iX, int iY, int iL)
{	myloChests.Resize(myloChests.Length() + 1);
	int iUnit = myloChests.Length() - 1;
	myloChests[iUnit].SetX(iX);
	myloChests[iUnit].SetY(iY);
	myloChests[iUnit].SetLayer(iL);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_Chest& LL_UnitSet::Chest(int iNum)
{	return(myloChests[iNum]);
}
//------------------------------------------------------------------------------------- [Guts Handeling] -
int LL_UnitSet::NumGuts()
{	return(myloGuts.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitSet::AddGuts(int iX, int iY, int iL, ASFC_Animation& oAnimation,
  						 LL_Inventory* poInventory, ASFC_Console* poConsole)
{	myloGuts.Resize(myloGuts.Length() + 1);
	int iUnit = myloGuts.Length() - 1;
	myloGuts[iUnit].SetX(iX);
	myloGuts[iUnit].SetY(iY);
	myloGuts[iUnit].SetLayer(iL);
	myloGuts[iUnit].SetAnimation(oAnimation);
	myloGuts[iUnit].SetInventory(poInventory);
	myloGuts[iUnit].SetConsole(poConsole);
	myloGuts[iUnit].SetUnitMap(mypoUnitMap);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_Guts& LL_UnitSet::Guts(int iNum)
{	return(myloGuts[iNum]);
}
//-------------------------------------------------------------------------------- [Transport Handeling] -
int LL_UnitSet::NumTransports()
{	return(myloTransports.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitSet::AddTransport(int iX, int iY, int iL)
{	myloTransports.Resize(myloTransports.Length() + 1);
	int iUnit = myloTransports.Length() - 1;
	myloTransports[iUnit].SetX(iX);
	myloTransports[iUnit].SetY(iY);
	myloTransports[iUnit].SetLayer(iL);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_Transport& LL_UnitSet::Transport(int iNum)
{	return(myloTransports[iNum]);
}
//------------------------------------------------------------------------------------ [Vehicle Objects] -
int LL_UnitSet::NumVehicles()
{	return(myloVehicleObjects.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitSet::AddVehicle(int iX, int iY, int iL, string sGraphicsPath, int iNum)
{	myloVehicleObjects.Resize(myloVehicleObjects.Length() + 1);
	myloVehicleObjects[myloVehicleObjects.Length() - 1].iX = iX;
	myloVehicleObjects[myloVehicleObjects.Length() - 1].iY = iY;
	myloVehicleObjects[myloVehicleObjects.Length() - 1].iL = iL;
	myloVehicleObjects[myloVehicleObjects.Length() - 1].iNum = iNum;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitSet::RemoveVehicle(int iNum)
{	mypoUnitMap->RemoveUnitOn(	myloVehicleObjects[iNum].iX, myloVehicleObjects[iNum].iY, 
								LL_UnitMap::LAYER_VEHICLE);
	myloVehicleObjects.Delete(iNum);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_UnitSet::VehicleType(int iNum)
{	return(myloVehicleObjects[iNum].iNum);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_VehicleObject& LL_UnitSet::VehicleObject(int iNum)
{	return(mypoVehicleObjectSet->VehicleObject(myloVehicleObjects[iNum].iNum));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_UnitSet::VehicleObjectNum(int iNum)
{	return(myloVehicleObjects[iNum].iNum);
}
//----------------------------------------------------------------------------------- [Spawner Handeling] -
int LL_UnitSet::NumSpawners()
{	return(myloSpawners.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_Spawner& LL_UnitSet::Spawner(int iNum)
{	return(myloSpawners[iNum]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitSet::AddSpawner(int iX, int iY)
{	myloSpawners.Resize(myloSpawners.Length() + 1);
	int iSpawner = myloSpawners.Length() - 1;
	myloSpawners[iSpawner].SetX(iX);
	myloSpawners[iSpawner].SetY(iY);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_UnitSet::SpawnerAt(int iX, int iY)
{	//Loop through all existing spawners looking for this one
		for(int i = 0; i < myloSpawners.Length(); i++)
		{	if(myloSpawners[i].X() == iX && myloSpawners[i].Y() == iY)
			{	return i;
			}
		}
	//No spawner's were found
		return NOTHING_FOUND;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitSet::HandleSpawners(string sGraphicsDir)
{	//Vars
		ASFC_LinkedList<int> liEnumaratedStack;
		ASFC_LinkedList<int> liRandomStack;

	//Form an enumarated stack containing the # of spawners
		for(int i = 0; i < myloSpawners.Length(); i++)
		{	liEnumaratedStack.Push(i);
		}
	//Randomize the random stack from elements in the enumarated stack
		while(liEnumaratedStack.Length() > 0)
		{	//Pick a random monsta'
				int iRand = PollRandom(liEnumaratedStack.Length());
			//Pull it out and push it yeah push it
				liRandomStack.Push(liEnumaratedStack[iRand]);
				liEnumaratedStack.Delete(iRand);
		}
	//Loop through the random stack
		for(int iSpawner = 0; iSpawner < liRandomStack.Length(); iSpawner++)
		{	//Set i equal to the spawner number
				int i = liRandomStack[iSpawner];
			//If the max monster limit hasn't been met and it's off the play field
				if(	myloMonsters.Length() < mypoTerrainMap->MaxMonsters() &&
					OffPlayField(	myloSpawners[i].X(), myloSpawners[i].Y(), 
									mypoPlayer->X(), mypoPlayer->Y()
								)
				  )
				{	//Pick a monster
						int iPickMonster = myloSpawners[i].PickMonster();
					//Create this monster
						AddMonster(	myloSpawners[i].X(),
									myloSpawners[i].Y(), 3,
									sGraphicsDir, iPickMonster);
						mypoUnitMap->SetUnitOn
						(	myloSpawners[i].X(),
							myloSpawners[i].Y(),
							3, LL_UnitSet::SEG_MONSTERS,
							NumMonsters() - 1
						);
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitSet::RemoveSpawner(int iNum)
{	//Remove it
		myloSpawners.Delete(iNum);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_UnitSet::OffPlayField(int iX, int iY, int iPlayerX, int iPlayerY)
{	if(	(iX <= iPlayerX - PLAYFIELD_TILEWIDTH  || iX >= iPlayerX + PLAYFIELD_TILEWIDTH) ||
		(iY <= iPlayerY - PLAYFIELD_TILEHEIGHT || iY >= iPlayerY + PLAYFIELD_TILEHEIGHT))
	{
		return(true);
	}
	return(false);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitSet::CopySpawner(int iX, int iY, int iCopyNum)
{	myloSpawners.Resize(myloSpawners.Length() + 1);
	int iSpawner = myloSpawners.Length() - 1;
	myloSpawners[iSpawner].SetX(iX);
	myloSpawners[iSpawner].SetY(iY);
	myloSpawners[iSpawner].Monsters().Resize(myloSpawners[iCopyNum].Monsters().Length());
	for(int i = 0; i < myloSpawners[iCopyNum].Monsters().Length(); i++)
	{	myloSpawners[iSpawner].Monsters()[i] = myloSpawners[iCopyNum].Monsters()[i];
	}
}
//-------------------------------------------------------------------------------------- [Global script] -
void LL_UnitSet::SetupGlobalScript(string sGraphicsDir)
{	//myoGlobalScript.Place(0, 0, -1);
	mypoGlobalScript->LoadAnimation("error.png", sGraphicsDir);	// !!! 
	mypoGlobalScript->SetClass(LL_UnitSet__GLOBAL_CLASS_IDENTIFIER);
	mypoGlobalScript->SetIdentifier(LL_UnitSet__GLOBAL_IDENTIFIER);
	LL_Vehicle oVehicle;
	oVehicle.SetCode(0);
	mypoGlobalScript->SetVehicle(oVehicle);
	mypoGlobalScript->SetTerrainMap(mypoTerrainMap);
	mypoGlobalScript->SetUnitMap(mypoUnitMap);
	mypoGlobalScript->SetClock(mypoGameClock);
	mypoGlobalScript->SetCLList(mypoCLList);
	mypoGlobalScript->SetSeg(SEG_SCRIPTED_UNITS);
	mypoGlobalScript->SetPathNodes(mypoPathNodes);
	mypoGlobalScript->SetOff(-2);
	mypoGlobalScript->SetEventQueue(mypoEventQueue);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitSet::RunGlobalScript()
{
}
//------------------------------------------------------------------------------------ [Error Handeling] -
void LL_UnitSet::DisplayMessage(string sLine1, string sLine2, string sLine3, int iFont)
{	//Vars
		int iNumChars;
		int iCenterX, iCenterY;
		int iFontWidth, iFontHeight;
		int iX;

	//Figure out the # of chars in the longest of those lines
		iNumChars = sLine1.size();
		if(sLine2.size() > iNumChars) iNumChars = sLine2.size();
		if(sLine3.size() > iNumChars) iNumChars = sLine3.size();
		
	//Figure out where the center of the screen is, and the fonts width and height
		iCenterX = myoScreen->GetWidth()  / 2;
		iCenterY = myoScreen->GetHeight() / 2;
		iFontWidth  = (*mypoFontPalette)[iFont].Width();
		iFontHeight = (*mypoFontPalette)[iFont].Height();
		
	//Using this info draw a rectangle border
		myoScreen->DrawRectangle(iCenterX - (iNumChars * iFontWidth)/2 - 4,
  								 iCenterY - (3 * iFontHeight)/2 - 4,
						  		 iFontWidth * iNumChars + 4, iFontHeight * 3 + 4, COLOR_WHITE, 200);
		myoScreen->DrawRectangle(iCenterX - (iNumChars * iFontWidth)/2 - 3,
  								 iCenterY - (3 * iFontHeight)/2 - 3,
						  		 iFontWidth * iNumChars + 3, iFontHeight * 3 + 3, COLOR_GRAY, 200);
		myoScreen->DrawFillRectangle(iCenterX - (iNumChars * iFontWidth)/2 - 2,
  									 iCenterY - (3 * iFontHeight)/2 - 2,
						  			 iFontWidth * iNumChars + 2, iFontHeight * 3 + 2, COLOR_BLACK, 200);
		
	//Draw these three lines of text
		(*mypoFontPalette)[iFont].WriteTo(*myoScreen, iCenterX - (sLine1.size() * iFontWidth)/2,
  									  iCenterY - iFontHeight - iFontHeight/2, sLine1);
		(*mypoFontPalette)[iFont].WriteTo(*myoScreen, iCenterX - (sLine2.size() * iFontWidth)/2,
  									  iCenterY - iFontHeight/2, sLine2);
		(*mypoFontPalette)[iFont].WriteTo(*myoScreen, iCenterX - (sLine3.size() * iFontWidth)/2,
	  								  iCenterY + iFontHeight/2, sLine3);
  	
  	//Draw the back buffer
  		myoScreen->Update();

	//Pause
		myoInput.Update();
		myoInput.Pause();
		while(myoInput.GetKey() != -1) {myoInput.Update();}
		myoInput.Update();
}
