/*Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			looplib_lore.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: The main LOOP library that interfaces with Lore And Lutes! This gives Lore a heck' of a
 				 lot of power. It's really cool! :-) <---Even smiley here thinks so
 				        ________________
                ,      / Thats right    `           See smiley even says so!
 			 *   \   _/  Having LOOP in |
 				  ) <_   Lore is neato! |
 			 *   /    `-----------------'
 				' 
*/
#ifndef LOOPLIB_LORE_H_
#define LOOPLIB_LORE_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//											Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Foundation
	#include <loop/loopmacros.h>
//Aggregates
	#include "looplib_loreinfo.h"
	#include <textedit/texteditor.h>
	#include <textedit/text.h>
	#include <asfc/timer.h>
//Dependencies
	#include <loop/info.h>
	#include <loop/loop.h>
	#include "zstats.h"
//Realizes
	#include <asfc/screen.h>
	#include "game.h"
	#include "painter.h"
//Dependencies
	#include <asfc/input.h>
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//										LL_LOOPLib_Lore
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_LOOPLib_Lore
{	public:
	//- [Constuctors] -
 		LL_LOOPLib_Lore();
 		void Link(LOOP_LOOP* poLOOP);
 		MEMVAR_SETGET(SetGame,		Game,		LL_Game*,		mypoGame);
 		MEMVAR_SETGET(SetScreen, 	Screen, 	ASFC_Screen*,	mypoScreen);
 		MEMVAR_SETGET(SetPainter,	Painter,	LL_Painter*,	mypoPainter);
		MEMVAR_SETGET(SetZStats,	ZStats,		LL_ZStats*,		mypoZStats);
		MEMVAR_GETREF(LoreInfo,		LL_LOOPLib_LoreInfo, myoLoreInfo);
	//- [Battle Info] -
		MEMVAR_SETGET(SetBattlePlayerX, BattlePlayerX, int, myiBattlePlayerX);
  		MEMVAR_SETGET(SetBattlePlayerY, BattlePlayerY, int, myiBattlePlayerY);
	//- [Graphics] -
		LOOPPORT(LOOPCMDPRT_SetColor,			LL_LOOPLib_Lore,		LOOPCMD_SetColor);			//III
		LOOPPORT(LOOPCMDPRT_SetAlpha,			LL_LOOPLib_Lore,		LOOPCMD_SetAlpha);			//I
		LOOPPORT(LOOPCMDPRT_DrawPixel,			LL_LOOPLib_Lore,		LOOPCMD_DrawPixel);			//II
		LOOPPORT(LOOPCMDPRT_DrawLine,			LL_LOOPLib_Lore,		LOOPCMD_DrawLine);			//III
		LOOPPORT(LOOPCMDPRT_DrawRectangle,		LL_LOOPLib_Lore,		LOOPCMD_DrawRectangle);		//IIII
		LOOPPORT(LOOPCMDPRT_DrawFillRectangle,	LL_LOOPLib_Lore,		LOOPCMD_DrawFillRectangle);	//IIII
		LOOPPORT(LOOPCMDPRT_DrawCircle,			LL_LOOPLib_Lore,		LOOPCMD_DrawCircle);		//III
		LOOPPORT(LOOPCMDPRT_DrawFillCircle,		LL_LOOPLib_Lore,		LOOPCMD_DrawFillCircle);	//III
		LOOPPORT(LOOPCMDPRT_DrawText,			LL_LOOPLib_Lore,		LOOPCMD_DrawText);			//IIS
		LOOPPORT(LOOPCMDPRT_LoadFont,			LL_LOOPLib_Lore,		LOOPCMD_LoadFont);			//S
		LOOPPORT(LOOPCMDPRT_DrawImage,			LL_LOOPLib_Lore,		LOOPCMD_DrawImage);			//SII
		LOOPPORT(LOOPCMDPRT_DrawImageEffect,	LL_LOOPLib_Lore,		LOOPCMD_DrawImageEffect);	//SIII
		LOOPPORT(LOOPCMDPRT_DrawTerrain,		LL_LOOPLib_Lore,		LOOPCMD_DrawTerrain);		//III
		LOOPPORT(LOOPCMDPRT_Clear, 				LL_LOOPLib_Lore,		LOOPCMD_Clear);				//
		LOOPPORT(LOOPCMDPRT_Narate,				LL_LOOPLib_Lore,		LOOPCMD_Narate);			//S
		LOOPPORT(LOOPCMDPRT_ClearNarate,		LL_LOOPLib_Lore,		LOOPCMD_ClearNarate);		//
		LOOPPORT(LOOPCMDPRT_ReDrawMap,			LL_LOOPLib_Lore,		LOOPCMD_ReDrawMap);			//
		LOOPPORT(LOOPCMDPRT_DoEffect,			LL_LOOPLib_Lore,		LOOPCMD_DoEffect);			//I
	//- [Scripted Unit Commands] -
		LOOPPORT(LOOPCMDPRT_Move,					LL_LOOPLib_Lore,	LOOPCMD_Move);				//I
		LOOPPORT(LOOPCMDPRT_MoveNorth,				LL_LOOPLib_Lore,	LOOPCMD_MoveNorth);			//
		LOOPPORT(LOOPCMDPRT_MoveSouth,				LL_LOOPLib_Lore,	LOOPCMD_MoveSouth);			//
		LOOPPORT(LOOPCMDPRT_MoveWest,				LL_LOOPLib_Lore,	LOOPCMD_MoveWest);			//
		LOOPPORT(LOOPCMDPRT_MoveEast,				LL_LOOPLib_Lore,	LOOPCMD_MoveEast);			//
		LOOPPORT(LOOPCMDPRT_MovePath,				LL_LOOPLib_Lore,	LOOPCMD_MovePath);			//S
		LOOPPORT(LOOPCMDPRT_Push,					LL_LOOPLib_Lore,	LOOPCMD_Push);				//
		LOOPPORT(LOOPCMDPRT_EndTurn,				LL_LOOPLib_Lore,	LOOPCMD_EndTurn);			//
		LOOPPORT(LOOPCMDPRT_Die, 					LL_LOOPLib_Lore,	LOOPCMD_Die);				//
		LOOPPORT(LOOPCMDPRT_Attack,					LL_LOOPLib_Lore,	LOOPCMD_Attack);			//
		LOOPPORT(LOOPCMDPRT_SetScriptArmor,			LL_LOOPLib_Lore,	LOOPCMD_SetScriptArmor);	//I
		LOOPPORT(LOOPCMDPRT_SetScriptWeapon,		LL_LOOPLib_Lore,	LOOPCMD_SetScriptWeapon);	//I
		LOOPPORT(LOOPCMDPRT_SetScriptVehicle,		LL_LOOPLib_Lore,	LOOPCMD_SetScriptVehicle);	//I
	//- [Console Commands] -
		LOOPPORT(LOOPCMDPRT_Write,					LL_LOOPLib_Lore,	LOOPCMD_Write);				//S
		LOOPPORT(LOOPCMDPRT_Writeln,				LL_LOOPLib_Lore,	LOOPCMD_Writeln);			//S
		LOOPPORT(LOOPCMDPRT_Endl,					LL_LOOPLib_Lore,	LOOPCMD_Endl);				//
		LOOPPORT(LOOPCMDPRT_SetFont,				LL_LOOPLib_Lore,	LOOPCMD_SetFont);			//I
		LOOPPORT(LOOPCMDPRT_PromptString,			LL_LOOPLib_Lore,	LOOPCMD_PromptString);		//[S]
		LOOPPORT(LOOPCMDPRT_PromptInt,				LL_LOOPLib_Lore,	LOOPCMD_PromptInt);			//[I]
		LOOPPORT(LOOPCMDPRT_PromptFloat,			LL_LOOPLib_Lore,	LOOPCMD_PromptFloat);		//[F]
		LOOPPORT(LOOPCMDPRT_RefreshConsole,			LL_LOOPLib_Lore,	LOOPCMD_RefreshConsole);	//
		LOOPPORT(LOOPCMDPRT_RefreshScreen,			LL_LOOPLib_Lore,	LOOPCMD_RefreshScreen);		//
		LOOPPORT(LOOPCMDPRT_ScrollOn,				LL_LOOPLib_Lore,	LOOPCMD_ScrollOn);			//
		LOOPPORT(LOOPCMDPRT_ScrollOff,				LL_LOOPLib_Lore,	LOOPCMD_ScrollOff);			//
		LOOPPORT(LOOPCMDPRT_ViewScroll,				LL_LOOPLib_Lore,	LOOPCMD_ViewScroll);		//
		LOOPPORT(LOOPCMDPRT_ClearScroll,			LL_LOOPLib_Lore,	LOOPCMD_ClearScroll);		//
	//- [Speech] -
		LOOPPORT(LOOPCMDPRT_GosubTalkResponse,		LL_LOOPLib_Lore,	LOOPCMD_GosubTalkResponse);	//
		LOOPPORT(LOOPCMDPRT_Say,					LL_LOOPLib_Lore,	LOOPCMD_Say);				//S
		LOOPPORT(LOOPCMDPRT_SayInt,					LL_LOOPLib_Lore,	LOOPCMD_SayInt);			//I
		LOOPPORT(LOOPCMDPRT_Ask,					LL_LOOPLib_Lore,	LOOPCMD_Ask);				//[S]S
		LOOPPORT(LOOPCMDPRT_AskInt,					LL_LOOPLib_Lore,	LOOPCMD_AskInt);			//[I]S
		LOOPPORT(LOOPCMDPRT_IfAskYN,				LL_LOOPLib_Lore,	LOOPCMD_IfAskYN);			//S
		LOOPPORT(LOOPCMDPRT_Pause,					LL_LOOPLib_Lore,	LOOPCMD_Pause);				//II
		LOOPPORT(LOOPCMDPRT_PauseMs,				LL_LOOPLib_Lore,	LOOPCMD_PauseMs);			//I
		LOOPPORT(LOOPCMDPRT_WaitForKey,				LL_LOOPLib_Lore,	LOOPCMD_WaitForKey);		//
		LOOPPORT(LOOPCMDPRT_DisplayFile,			LL_LOOPLib_Lore,	LOOPCMD_DisplayFile);		//S
	//- [Maps] -
		LOOPPORT(LOOPCMDPRT_MoveToMapN,				LL_LOOPLib_Lore,	LOOPCMD_MoveToMapN);
		LOOPPORT(LOOPCMDPRT_MoveToMapS,				LL_LOOPLib_Lore,	LOOPCMD_MoveToMapS);
		LOOPPORT(LOOPCMDPRT_MoveToMapW,				LL_LOOPLib_Lore,	LOOPCMD_MoveToMapW);
		LOOPPORT(LOOPCMDPRT_MoveToMapE,				LL_LOOPLib_Lore,	LOOPCMD_MoveToMapE);
		LOOPPORT(LOOPCMDPRT_MoveToMap,				LL_LOOPLib_Lore,	LOOPCMD_MoveToMap);			//II
	//- [Date\Time] -
		LOOPPORT(LOOPCMDPRT_GetDay,					LL_LOOPLib_Lore,	LOOPCMD_GetDay);			//[I]
		LOOPPORT(LOOPCMDPRT_GetMonth,				LL_LOOPLib_Lore,	LOOPCMD_GetMonth);			//[I]
		LOOPPORT(LOOPCMDPRT_GetYear,				LL_LOOPLib_Lore,	LOOPCMD_GetYear);			//[I]
		LOOPPORT(LOOPCMDPRT_GetHour,				LL_LOOPLib_Lore,	LOOPCMD_GetHour);			//[I]
		LOOPPORT(LOOPCMDPRT_GetMinute,				LL_LOOPLib_Lore,	LOOPCMD_GetMinute);			//[I]
		LOOPPORT(LOOPCMDPRT_SetDay,					LL_LOOPLib_Lore,	LOOPCMD_SetDay);			//I
		LOOPPORT(LOOPCMDPRT_SetMonth,				LL_LOOPLib_Lore,	LOOPCMD_SetMonth);			//I
		LOOPPORT(LOOPCMDPRT_SetYear,				LL_LOOPLib_Lore,	LOOPCMD_SetYear);			//I
		LOOPPORT(LOOPCMDPRT_SetHour,				LL_LOOPLib_Lore,	LOOPCMD_SetHour);			//I
		LOOPPORT(LOOPCMDPRT_SetMinute,				LL_LOOPLib_Lore,	LOOPCMD_SetMinute);			//I
		LOOPPORT(LOOPCMDPRT_AddDays,				LL_LOOPLib_Lore,	LOOPCMD_AddDays);			//I
		LOOPPORT(LOOPCMDPRT_CelestialClockOn,		LL_LOOPLib_Lore,	LOOPCMD_CelestialClockOn);	//
		LOOPPORT(LOOPCMDPRT_CelestialClockOff,		LL_LOOPLib_Lore,	LOOPCMD_CelestialClockOff);	//
		LOOPPORT(LOOPCMDPRT_TurnLightingOn,			LL_LOOPLib_Lore,	LOOPCMD_TurnLightingOn);	//
		LOOPPORT(LOOPCMDPRT_TurnLightingOff,		LL_LOOPLib_Lore,	LOOPCMD_TurnLightingOff);	//
	//- [AI Path Finding Commands] -
		LOOPPORT(LOOPCMDPRT_MoveToPosition,			LL_LOOPLib_Lore,	LOOPCMD_MoveToPosition);	//II
	//- [Battle Commands] -
		LOOPPORT(LOOPCMDPRT_Battle,					LL_LOOPLib_Lore,	LOOPCMD_Battle);			//II
	//- [Player Commands] -
		LOOPPORT(LOOPCMDPRT_PromptPlayer,			LL_LOOPLib_Lore,	LOOPCMD_PromptPlayer);		//[I]
		LOOPPORT(LOOPCMDPRT_GivePlayer,				LL_LOOPLib_Lore,	LOOPCMD_GivePlayer);		//I
		LOOPPORT(LOOPCMDPRT_RemovePlayer,			LL_LOOPLib_Lore,	LOOPCMD_RemovePlayer);		//I
		LOOPPORT(LOOPCMDPRT_SetPlayerVehicle,		LL_LOOPLib_Lore,	LOOPCMD_SetPlayerVehicle);	//I
		LOOPPORT(LOOPCMDPRT_PutPlayer,				LL_LOOPLib_Lore,	LOOPCMD_PutPlayer);			//II
		LOOPPORT(LOOPCMDPRT_GiveHP,					LL_LOOPLib_Lore,	LOOPCMD_GiveHP);			//II
		LOOPPORT(LOOPCMDPRT_TakeHP,					LL_LOOPLib_Lore,	LOOPCMD_TakeHP);			//IIS
		LOOPPORT(LOOPCMDPRT_SetHP,					LL_LOOPLib_Lore,	LOOPCMD_SetHP);				//II
		LOOPPORT(LOOPCMDPRT_GetHP,					LL_LOOPLib_Lore,	LOOPCMD_GetHP);				//II
		LOOPPORT(LOOPCMDPRT_GiveMaxHP,				LL_LOOPLib_Lore,	LOOPCMD_GiveMaxHP);			//II
		LOOPPORT(LOOPCMDPRT_TakeMaxHP,				LL_LOOPLib_Lore,	LOOPCMD_TakeMaxHP);			//IIS
		LOOPPORT(LOOPCMDPRT_SetMaxHP,				LL_LOOPLib_Lore,	LOOPCMD_SetMaxHP);			//II
		LOOPPORT(LOOPCMDPRT_GetMaxHP,				LL_LOOPLib_Lore,	LOOPCMD_GetMaxHP);			//II
	//- [Inventory] -
		LOOPPORT(LOOPCMDPRT_GiveGold,				LL_LOOPLib_Lore,	LOOPCMD_GiveGold);			//I
		LOOPPORT(LOOPCMDPRT_TakeGold,				LL_LOOPLib_Lore,	LOOPCMD_TakeGold); 			//IS
		LOOPPORT(LOOPCMDPRT_GetGold,				LL_LOOPLib_Lore,	LOOPCMD_GetGold); 			//[i]
		LOOPPORT(LOOPCMDPRT_SetGold,				LL_LOOPLib_Lore,	LOOPCMD_SetGold);  			//I
		LOOPPORT(LOOPCMDPRT_GiveFood,				LL_LOOPLib_Lore,	LOOPCMD_GiveFood);			//I
		LOOPPORT(LOOPCMDPRT_TakeFood,				LL_LOOPLib_Lore,	LOOPCMD_TakeFood);			//IS
		LOOPPORT(LOOPCMDPRT_GetFood,				LL_LOOPLib_Lore,	LOOPCMD_GetFood);			//[i]
		LOOPPORT(LOOPCMDPRT_SetFood,				LL_LOOPLib_Lore,	LOOPCMD_SetFood);			//I
		LOOPPORT(LOOPCMDPRT_GiveWeapon,				LL_LOOPLib_Lore,	LOOPCMD_GiveWeapon);		//II
		LOOPPORT(LOOPCMDPRT_TakeWeapon,				LL_LOOPLib_Lore,	LOOPCMD_TakeWeapon);		//IIS
		LOOPPORT(LOOPCMDPRT_GetWeapon,				LL_LOOPLib_Lore,	LOOPCMD_GetWeapon);			//[i]I
		LOOPPORT(LOOPCMDPRT_SetWeapon,				LL_LOOPLib_Lore,	LOOPCMD_SetWeapon);			//II
		LOOPPORT(LOOPCMDPRT_GiveArmor,				LL_LOOPLib_Lore,	LOOPCMD_GiveArmor);			//II
		LOOPPORT(LOOPCMDPRT_TakeArmor,				LL_LOOPLib_Lore,	LOOPCMD_TakeArmor);			//IIS
		LOOPPORT(LOOPCMDPRT_GetArmor,				LL_LOOPLib_Lore,	LOOPCMD_GetArmor);			//[i]I
		LOOPPORT(LOOPCMDPRT_SetArmor,				LL_LOOPLib_Lore,	LOOPCMD_SetArmor);			//II
		LOOPPORT(LOOPCMDPRT_GiveTorches,			LL_LOOPLib_Lore,	LOOPCMD_GiveTorches);		//I
		LOOPPORT(LOOPCMDPRT_TakeTorches,			LL_LOOPLib_Lore,	LOOPCMD_TakeTorches);		//IS
		LOOPPORT(LOOPCMDPRT_GetTorches,				LL_LOOPLib_Lore,	LOOPCMD_GetTorches);		//[i]
		LOOPPORT(LOOPCMDPRT_SetTorches,				LL_LOOPLib_Lore,	LOOPCMD_SetTorches);		//I
		LOOPPORT(LOOPCMDPRT_GiveScriptedItem,		LL_LOOPLib_Lore,	LOOPCMD_GiveScriptedItem);	//II
		LOOPPORT(LOOPCMDPRT_TakeScriptedItem,		LL_LOOPLib_Lore,	LOOPCMD_TakeScriptedItem);	//IIS
		LOOPPORT(LOOPCMDPRT_GetScriptedItem,		LL_LOOPLib_Lore,	LOOPCMD_GetScriptedItem);	//[i]I
		LOOPPORT(LOOPCMDPRT_SetScriptedItem,		LL_LOOPLib_Lore,	LOOPCMD_SetScriptedItem);	//II
	//- [Message Commands] -
		LOOPPORT(LOOPCMDPRT_Call,					LL_LOOPLib_Lore,	LOOPCMD_Call);				//SS
		LOOPPORT(LOOPCMDPRT_CallNorth,				LL_LOOPLib_Lore,	LOOPCMD_CallNorth);			//S
		LOOPPORT(LOOPCMDPRT_CallSouth,				LL_LOOPLib_Lore,	LOOPCMD_CallSouth);			//S
		LOOPPORT(LOOPCMDPRT_CallWest,				LL_LOOPLib_Lore,	LOOPCMD_CallWest);			//S
		LOOPPORT(LOOPCMDPRT_CallEast,				LL_LOOPLib_Lore,	LOOPCMD_CallEast);			//S
		LOOPPORT(LOOPCMDPRT_CallGlobal,				LL_LOOPLib_Lore,	LOOPCMD_CallGlobal);		//S
		LOOPPORT(LOOPCMDPRT_Ping,					LL_LOOPLib_Lore,	LOOPCMD_Ping);				//S
		LOOPPORT(LOOPCMDPRT_PingClass,				LL_LOOPLib_Lore,	LOOPCMD_PingClass);			//SS
		LOOPPORT(LOOPCMDPRT_PingClassAndDeriv,		LL_LOOPLib_Lore,	LOOPCMD_PingClassAndDeriv);	//SS
	//- [Viewport Commands] -
		LOOPPORT(LOOPCMDPRT_MoveViewportTo,			LL_LOOPLib_Lore,	LOOPCMD_MoveViewportTo);	//II
		LOOPPORT(LOOPCMDPRT_MoveViewportNorth,		LL_LOOPLib_Lore,	LOOPCMD_MoveViewportNorth);
		LOOPPORT(LOOPCMDPRT_MoveViewportSouth,		LL_LOOPLib_Lore,	LOOPCMD_MoveViewportSouth);
		LOOPPORT(LOOPCMDPRT_MoveViewportWest,		LL_LOOPLib_Lore,	LOOPCMD_MoveViewportWest);
		LOOPPORT(LOOPCMDPRT_MoveViewportEast,		LL_LOOPLib_Lore,	LOOPCMD_MoveViewportEast);
	//- [Transportation Commands] -
		LOOPPORT(LOOPCMDPRT_Transport,				LL_LOOPLib_Lore,	LOOPCMD_Transport);			//IIII
	//- [Flags] -
		LOOPPORT(LOOPCMDPRT_FlagOn,					LL_LOOPLib_Lore,	LOOPCMD_FlagOn);			//S
		LOOPPORT(LOOPCMDPRT_FlagOff,				LL_LOOPLib_Lore,	LOOPCMD_FlagOff);			//S
		LOOPPORT(LOOPCMDPRT_FlagSwitch,				LL_LOOPLib_Lore,	LOOPCMD_FlagSwitch);		//S
		LOOPPORT(LOOPCMDPRT_FlagExists,				LL_LOOPLib_Lore,	LOOPCMD_FlagExists);		//[I]S
		LOOPPORT(LOOPCMDPRT_IfFlagExists,			LL_LOOPLib_Lore,	LOOPCMD_IfFlagExists);		//S		
		LOOPPORT(LOOPCMDPRT_IfFlag,					LL_LOOPLib_Lore,	LOOPCMD_IfFlag);			//S
		LOOPPORT(LOOPCMDPRT_IfMapType,				LL_LOOPLib_Lore,	LOOPCMD_IfMapType);			//S
	//- [Spawn] -
		LOOPPORT(LOOPCMDPRT_SpawnVehicleObject,		LL_LOOPLib_Lore,	LOOPCMD_SpawnVehicleObject);//III
	//- [Misc.] -
		LOOPPORT(LOOPCMDPRT_IfInBox,				LL_LOOPLib_Lore,	LOOPCMD_IfInBox);			//IIII
		LOOPPORT(LOOPCMDPRT_IfOnTerrainGroup,		LL_LOOPLib_Lore,	LOOPCMD_IfOnTerrainGroup);	//S
		LOOPPORT(LOOPCMDPRT_Sleep,					LL_LOOPLib_Lore,	LOOPCMD_Sleep);				//III
		LOOPPORT(LOOPCMDPRT_IfPlayerVehicle,		LL_LOOPLib_Lore,	LOOPCMD_IfPlayerVehicle);	//I

	protected:
	//Vars
		LL_Game*			mypoGame;
		ASFC_Screen*		mypoScreen;
		LL_Painter*			mypoPainter;
		LL_LOOPLib_LoreInfo	myoLoreInfo;
		LL_ZStats*			mypoZStats;
		bool				myfScroll;
		TE_Text 			myoText;
		TE_TextEditor 		myoTextEditor;
		ASFC_Timer			myoTimer;
		//Battle Info
			int myiBattlePlayerX, myiBattlePlayerY;
		//Graphics
			int myiColorRed, myiColorGreen, myiColorBlue, myiColorAlpha;
};

#endif
