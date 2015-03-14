/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			leditstart.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "leditstart.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//											 LEDIT_LEditStart
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//-------------------------------------------------------------------------------------------- [Editting] -
LEDIT_MapEditor::LEDIT_TestInformation LEDIT_LEditStart::StartEditor(ASFC_Screen* poScreen, string sGame,
																	 int iMap, int iX, int iY)
{	//Vars
		LEDIT_MapEditor::LEDIT_TestInformation oTestInfo;

	//Set the screen
		mypoScreen = poScreen;
		
	LL_Painter myoPaint;
	//Declare game objects
		LL_Game oGame;
		LL_LOOPLib_LoreLinker 	myoLOOPLibLinker;
		LL_LOOPLib_Lore 		myoLOOPLib;

	//!!!! TURN SOUND OFF !!!!
		oGame.Sound().TurnSoundOff();
	//Setup the user interface
		myoPaint.SetScreen(mypoScreen);
		myoPaint.SetGame(&oGame);
		if(!myoPaint.Load("./data/gui/editor.gui"))
		{	cerr << "UI Loading failure.\n";
			cerr << "Make sure file: ./data/gui/editor.gui exists.\n";
			cerr << "You may have to reinstall Lore And Lutes to fix the error.\n";
			cerr << "Now exitting...\n";
			return oTestInfo;
		}
	//Display the hard coded greeting message
		myoPaint.TalkConsole().CurrentFont(1);
		myoPaint.TalkConsole() << "- - - - - - - - - - -\n";
		myoPaint.TalkConsole().CurrentFont(0);
		myoPaint.TalkConsole() << "      Welcome to     \n";
		myoPaint.TalkConsole() << "~Lore And Lutes Edit~\n";
		myoPaint.TalkConsole() << "    By: Andy Stone   \n";
		myoPaint.TalkConsole().CurrentFont(1);
		myoPaint.TalkConsole() << "- - - - - - - - - - -\n";
		myoPaint.Draw();
		myoPaint.TalkConsole().Draw(0xFF);
	//Setup the Lore LOOP Library (and the linker)
		myoLOOPLib.SetGame(&oGame);
		myoLOOPLib.SetScreen(mypoScreen);
		myoLOOPLib.SetPainter(&myoPaint);
		myoLOOPLib.Link(&oGame.LOOP());
	//Load up the ol' sample game
		oGame.SetGameFile(sGame);
		if(!oGame.Load("./games/" + sGame + "/" + sGame + ".game", mypoScreen, &myoPaint.FontPalette()))
		{	myoPaint.PromptYN("Unable to load game", "See stderr.txt or console output for details.",
							  "Press Y to exit...", 1);
			return oTestInfo;
		}
	//!!!!!!!!
	//Set up the battle engine
		oGame.SetInBattleMode(true);
		oGame.LoadMap(-1);
		oGame.LoadClasses("", mypoScreen);
		oGame.SetInBattleMode(false);
	//Load the first map
		if(iMap == -1)
			oGame.LoadMap(0);
		else
		{cerr << "LODIZING MAP: " << iMap << endl;
  				oGame.LoadMap(iMap);
		}
//		oGame.LoadClasses("", mypoScreen);
		if(!oGame.LoadClasses("./games/" + sGame + "/" + sGame + ".game", mypoScreen))
		{	myoPaint.PromptYN("Unable to load game classes",
							  "See stderr.txt or console output for details.",
							  "Press Y to exit...", 1);
			return oTestInfo;
		}

		myoLOOPLibLinker.Link(&oGame, &myoLOOPLib);
		LEDIT_FileChooser oFileChoose;
		oFileChoose.SetScreen(mypoScreen);
		oFileChoose.SetPainter(&myoPaint);
		oFileChoose.SetFileManager(&oGame.FileManager());
		
		LEDIT_MobilityEditor oMobilityEdit;
		oMobilityEdit.SetScreen(mypoScreen);
		oMobilityEdit.SetPainter(&myoPaint);
		
		LEDIT_VehicleSetEditor oVehicleEditor;
		oVehicleEditor.SetScreen(mypoScreen);
		oVehicleEditor.SetPainter(&myoPaint);
		oVehicleEditor.SetVehicleSet(&oGame.VehicleSet());
		
		LEDIT_TerrainEditor oTerrainEditor;
		oTerrainEditor.SetScreen(mypoScreen);
		oTerrainEditor.SetPainter(&myoPaint);
		oTerrainEditor.SetMobilityEditor(&oMobilityEdit);
		oTerrainEditor.SetFileChooser(&oFileChoose);
		oTerrainEditor.SetVehicleSetEditor(&oVehicleEditor);
		oTerrainEditor.SetMobilityTerrainMap(&oGame.MobilityTerrainMap());
		
		LEDIT_TerrainSetEditor oTMEdit;
		oTMEdit.SetScreen(mypoScreen);
		oTMEdit.SetPainter(&myoPaint);
		oTMEdit.SetGame(&oGame);
		oTMEdit.SetTerrainEditor(&oTerrainEditor);

		LEDIT_MapSetEditor oMapSetEditor;
		oMapSetEditor.SetScreen(mypoScreen);
		oMapSetEditor.SetPainter(&myoPaint);

		LEDIT_MapInfoEditor oInfo;
		oInfo.SetScreen(mypoScreen);
		oInfo.SetPainter(&myoPaint);
		oInfo.SetMapSet(&oGame.MapSet());
		oInfo.SetMapSetEdit(&oMapSetEditor);
		oInfo.SetGame(&oGame);
		oInfo.SetFileChooser(&oFileChoose);

		LL_Help oHelp;
		oHelp.Setup(&myoPaint, mypoScreen);

		LEDIT_MapObjectRemover oMapObjectRemover;
		oMapObjectRemover.SetGame(&oGame);

		LEDIT_ClassSetEditor oClassSetEdit;
		oClassSetEdit.SetScreen(mypoScreen);
		oClassSetEdit.SetPainter(&myoPaint);
		oClassSetEdit.SetMapObjectRemover(&oMapObjectRemover);
		oClassSetEdit.SetLinker(&myoLOOPLibLinker);
		oClassSetEdit.SetLoreLib(&myoLOOPLib);
		
		LEDIT_GlobalScriptEditor oScriptEditor;
		oScriptEditor.SetScreen(mypoScreen);
		oScriptEditor.SetPainter(&myoPaint);
		oScriptEditor.Setup(&myoPaint);
		oScriptEditor.SetLinker(&myoLOOPLibLinker);
		oScriptEditor.SetLoreLib(&myoLOOPLib);

		LEDIT_MapObjectEditor oMapObjectEditor;
		oMapObjectEditor.SetScreen(mypoScreen);
		oMapObjectEditor.SetPainter(&myoPaint);
		oMapObjectEditor.SetFileChooser(&oFileChoose);
		
		LEDIT_RouteEditor oRouteEditor(&oGame);
		oRouteEditor.SetScreen(mypoScreen);
		oRouteEditor.SetPainter(&myoPaint);
		
		LEDIT_LocationPicker oLocationPicker;
		oLocationPicker.SetScreen(mypoScreen);
		oLocationPicker.SetPainter(&myoPaint);
		oLocationPicker.SetGame(&oGame);
		oLocationPicker.SetRouteEditor(&oRouteEditor);
		
		LEDIT_DailyRoutineEditor oDailyRoutineEditor;
		oDailyRoutineEditor.SetScreen(mypoScreen);
		oDailyRoutineEditor.SetPainter(&myoPaint);
		oDailyRoutineEditor.SetLocationPicker(&oLocationPicker);

		LEDIT_ScriptedUnitEditor oScriptedUnitEditor;
		oScriptedUnitEditor.SetScreen(mypoScreen);
		oScriptedUnitEditor.SetPainter(&myoPaint);
		oScriptedUnitEditor.SetFileChooser(&oFileChoose);
		oScriptedUnitEditor.SetClassSetEditor(&oClassSetEdit);
		oScriptedUnitEditor.SetLinker(&myoLOOPLibLinker);
		oScriptedUnitEditor.SetLoreLib(&myoLOOPLib);
		oScriptedUnitEditor.SetDailyRoutineEditor(&oDailyRoutineEditor);

		LEDIT_ArmorEditor oArmorEditor;
		oArmorEditor.SetScreen(mypoScreen);
		oArmorEditor.SetPainter(&myoPaint);
		oArmorEditor.SetGame(&oGame);
		oArmorEditor.SetFileChooser(&oFileChoose);
		
		LEDIT_WeaponEditor oWeaponEditor;
		oWeaponEditor.SetScreen(mypoScreen);
		oWeaponEditor.SetPainter(&myoPaint);
		oWeaponEditor.SetGame(&oGame);
		oWeaponEditor.SetFileChooser(&oFileChoose);
		
		LEDIT_ScriptedItemEditor oScriptedItemEditor;
		oScriptedItemEditor.SetScreen(mypoScreen);
		oScriptedItemEditor.SetPainter(&myoPaint);
		oScriptedItemEditor.SetGame(&oGame);
		oScriptedItemEditor.SetFileChooser(&oFileChoose);
		oScriptedItemEditor.SetClassSetEditor(&oClassSetEdit);
		
		LEDIT_ItemSetEditor oItemSetEditor;
		oItemSetEditor.SetScreen(mypoScreen);
		oItemSetEditor.SetPainter(&myoPaint);
		oItemSetEditor.SetArmorEditor(&oArmorEditor);
		oItemSetEditor.SetWeaponEditor(&oWeaponEditor);
		oItemSetEditor.SetScriptedItemEditor(&oScriptedItemEditor);
		oItemSetEditor.SetFileChooser(&oFileChoose);
		oItemSetEditor.SetGame(&oGame);
		
		LEDIT_ChestEditor oChestEditor;
		oChestEditor.SetScreen(mypoScreen);
		oChestEditor.SetPainter(&myoPaint);
		oChestEditor.SetFileChooser(&oFileChoose);
		oChestEditor.SetItemSetEditor(&oItemSetEditor);
		oChestEditor.SetGame(&oGame);
		
		LEDIT_FriendEditor oFriendEditor;
		oFriendEditor.SetScreen(mypoScreen);
		oFriendEditor.SetPainter(&myoPaint);
		oFriendEditor.SetGame(&oGame);
	
		LEDIT_MonsterEditor oMonsterEditor;
		oMonsterEditor.SetScreen(mypoScreen);
		oMonsterEditor.SetPainter(&myoPaint);
		oMonsterEditor.SetVehicleSetEditor(&oVehicleEditor);
		oMonsterEditor.SetFileChooser(&oFileChoose);
		oMonsterEditor.SetItemSetEditor(&oItemSetEditor);
		oMonsterEditor.SetChestEditor(&oChestEditor);
		oMonsterEditor.SetFriendEditor(&oFriendEditor);

		LEDIT_MonsterSetEditor oMonsterSetEditor;
		oMonsterSetEditor.SetScreen(mypoScreen);
		oMonsterSetEditor.SetPainter(&myoPaint);
		oMonsterSetEditor.SetMonsterEdit(&oMonsterEditor);
		
		LEDIT_PlayerEditor oPlayerEditor;
		oPlayerEditor.SetScreen(mypoScreen);
		oPlayerEditor.SetPainter(&myoPaint);
		oPlayerEditor.SetVehicleSetEditor(&oVehicleEditor);
		oPlayerEditor.SetFileChooser(&oFileChoose);
		
		LEDIT_PlayerSetEditor oPlayerSetEditor;
		oPlayerSetEditor.SetScreen(mypoScreen);
		oPlayerSetEditor.SetPainter(&myoPaint);
		oPlayerSetEditor.SetPlayerEdit(&oPlayerEditor);
		
		LEDIT_GlobalInfoEditor oGlobalInfo;
		oGlobalInfo.SetScreen(mypoScreen);
		oGlobalInfo.SetPainter(&myoPaint);
		oGlobalInfo.SetMapSet(&oGame.MapSet());
		oGlobalInfo.SetMapSetEdit(&oMapSetEditor);
		oGlobalInfo.SetGame(&oGame);
		oGlobalInfo.SetPlayerSetEdit(&oPlayerSetEditor);

		LEDIT_TransportEditor oTransportEditor;
		oTransportEditor.SetScreen(mypoScreen);
		oTransportEditor.SetPainter(&myoPaint);
		oTransportEditor.SetFileChooser(&oFileChoose);
		oTransportEditor.SetMapSetEdit(&oMapSetEditor);
		oTransportEditor.SetGame(&oGame);

		LEDIT_VehicleBattleKeyEditor oVehicleBattleKeyEditor;
		oVehicleBattleKeyEditor.SetScreen(mypoScreen);
		oVehicleBattleKeyEditor.SetPainter(&myoPaint);
		oVehicleBattleKeyEditor.SetMobilityTerrainMap(&oGame.MobilityTerrainMap());
		oVehicleBattleKeyEditor.SetVehicleSet(&oGame.VehicleSet());
		oVehicleBattleKeyEditor.SetVehicleSetEditor(&oVehicleEditor);

		LEDIT_VehicleObjectEditor oVehicleObjectEditor;
		oVehicleObjectEditor.SetScreen(mypoScreen);
		oVehicleObjectEditor.SetPainter(&myoPaint);
		oVehicleObjectEditor.SetGame(&oGame);
		oVehicleObjectEditor.SetFileChooser(&oFileChoose);

		LEDIT_VehicleObjectSetEditor oVehicleObjectSetEditor;
		oVehicleObjectSetEditor.SetScreen(mypoScreen);
		oVehicleObjectSetEditor.SetPainter(&myoPaint);
		oVehicleObjectSetEditor.SetGame(&oGame);
		oVehicleObjectSetEditor.SetVehicleSetEditor(&oVehicleEditor);
		oVehicleObjectSetEditor.SetVehicleObjectEditor(&oVehicleObjectEditor);

		LEDIT_ButtonsStrip oButtonsStrip;
		oButtonsStrip.Load("data/gui/buttons/editbar/buttons.strip");		//!!!
		oButtonsStrip.SetOffsetX(CELESTIALVIEW_X + 1);
		oButtonsStrip.SetOffsetY(CELESTIALVIEW_Y);
		oButtonsStrip.SetScreen(mypoScreen);
		oButtonsStrip.SetPainter(&myoPaint);

		LEDIT_SpawnerEditor oSpawnerEditor;
		oSpawnerEditor.SetPainter(&myoPaint);
		oSpawnerEditor.SetScreen(mypoScreen);
		oSpawnerEditor.SetGame(&oGame);
		oSpawnerEditor.SetMonsterSetEditor(&oMonsterSetEditor);
		
		LEDIT_GraphicsList oGraphicsList;
		oGraphicsList.SetPainter(&myoPaint);
		oGraphicsList.SetScreen(mypoScreen);
		
	//Setup a map editor and run it
		LEDIT_MapEditor oMapEdit;
		oMapEdit.SetGame(&oGame);
		oMapEdit.SetScreen(mypoScreen);
		oMapEdit.SetPainter(&myoPaint);
		oMapEdit.SetTerrainSetEditor(&oTMEdit);
		oMapEdit.SetMapInfoEditor(&oInfo);
		oMapEdit.SetGlobalInfoEditor(&oGlobalInfo);
		oMapEdit.SetMapSetEditor(&oMapSetEditor);
		oMapEdit.SetVehicleSetEditor(&oVehicleEditor);
		oMapEdit.SetHelp(&oHelp);
		oMapEdit.SetClassSetEditor(&oClassSetEdit);
		oMapEdit.SetGlobalScriptEditor(&oScriptEditor);
		oMapEdit.SetMapObjectEditor(&oMapObjectEditor);
		oMapEdit.SetMapObjectRemover(&oMapObjectRemover);
		oMapEdit.SetScriptedUnitEditor(&oScriptedUnitEditor);
		oMapEdit.SetMonsterSetEditor(&oMonsterSetEditor);
		oMapEdit.SetPlayerSetEditor(&oPlayerSetEditor);
		oMapEdit.SetRouteEditor(&oRouteEditor);
		oMapEdit.SetItemSetEditor(&oItemSetEditor);
		oMapEdit.SetChestEditor(&oChestEditor);
		oMapEdit.SetTransportEditor(&oTransportEditor);
		oMapEdit.SetKeyEditor(&oVehicleBattleKeyEditor);
		oMapEdit.SetVehicleObjectEditor(&oVehicleObjectEditor);
		oMapEdit.SetVehicleObjectSetEditor(&oVehicleObjectSetEditor);
		oMapEdit.SetButtonsStrip(&oButtonsStrip);
		oMapEdit.SetSpawnerEditor(&oSpawnerEditor);
		oMapEdit.SetGraphicsList(&oGraphicsList);
		return(oMapEdit.Edit(iX, iY));
}
