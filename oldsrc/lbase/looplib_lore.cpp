/*Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			looplib_lore.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//											Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "looplib_lore.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//											cLOOPLib_Standard
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_LOOPLib_Lore::LL_LOOPLib_Lore()
	:	myiColorRed(255),
		myiColorGreen(255),
		myiColorBlue(255),
		myiColorAlpha(255)
{	myiColorAlpha = 255;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_LOOPLib_Lore::Link(LOOP_LOOP* poLOOP)
{	//Set defaults
		myfScroll = false;
		myoTextEditor.SetConsole(&mypoPainter->MainConsole());
	//- [Graphics] -
		poLOOP->NewCommand("SetColor",			&LOOPCMDPRT_SetColor,			this);	//III
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("SetAlpha",			&LOOPCMDPRT_SetAlpha,			this);	//I
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("DrawPixel",			&LOOPCMDPRT_DrawPixel,			this);	//II
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("DrawLine",			&LOOPCMDPRT_DrawLine,			this);	//III
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("DrawRectangle",		&LOOPCMDPRT_DrawRectangle,		this);	//IIII
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("DrawFillRectangle",	&LOOPCMDPRT_DrawFillRectangle,	this);	//IIII
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("DrawCircle", 		&LOOPCMDPRT_DrawCircle,			this);	//III
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("DrawFillCircle",	&LOOPCMDPRT_DrawFillCircle,		this);	//III
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("DrawText",			&LOOPCMDPRT_DrawText,			this);	//IIS
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("LoadFont",			&LOOPCMDPRT_LoadFont,			this);	//S
			poLOOP->AddParam(PARAM_INT_REF);
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("DrawImage",			&LOOPCMDPRT_DrawImage,			this);	//SII
			poLOOP->AddParam(PARAM_STRING);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("DrawImageEffect",	&LOOPCMDPRT_DrawImageEffect,	this);	//SIII
			poLOOP->AddParam(PARAM_STRING);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("DrawTerrain",		&LOOPCMDPRT_DrawTerrain,		this);	//III
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("Clear",				&LOOPCMDPRT_Clear,				this);	//
		poLOOP->NewCommand("Narate",			&LOOPCMDPRT_Narate,				this);	//S
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("ClearNarate",		&LOOPCMDPRT_ClearNarate,		this);	//
		poLOOP->NewCommand("ReDrawMap",			&LOOPCMDPRT_ReDrawMap,			this);	//
		poLOOP->NewCommand("DoEffect",			&LOOPCMDPRT_DoEffect,			this);	//I
			poLOOP->AddParam(PARAM_INT);
	//- [Scripted Unit Commands] -
		poLOOP->NewCommand("Move",					&LOOPCMDPRT_Move,			this);	//I
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("MoveNorth",				&LOOPCMDPRT_MoveNorth,		this);	//
		poLOOP->NewCommand("MoveSouth",				&LOOPCMDPRT_MoveSouth,		this);	//
		poLOOP->NewCommand("MoveWest",				&LOOPCMDPRT_MoveWest,		this);	//
		poLOOP->NewCommand("MoveEast",				&LOOPCMDPRT_MoveEast,		this);	//
		poLOOP->NewCommand("MovePath",				&LOOPCMDPRT_MovePath,		this);	//S
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("Push",					&LOOPCMDPRT_Push,			this);	//
		poLOOP->NewCommand("EndTurn",				&LOOPCMDPRT_EndTurn,		this);	//
		poLOOP->NewCommand("Die",					&LOOPCMDPRT_Die,			this);	//
		poLOOP->NewCommand("Attack",				&LOOPCMDPRT_Attack,			this);	//
		poLOOP->NewCommand("SetScriptArmor",		&LOOPCMDPRT_SetScriptArmor,	this);	//I
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("SetScriptWeapon",		&LOOPCMDPRT_SetScriptWeapon,this);	//I
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("SetScriptVehicle",		&LOOPCMDPRT_SetScriptVehicle,this);	//I
			poLOOP->AddParam(PARAM_INT);
	//- [Console Commands] -
		poLOOP->NewCommand("Write", 				&LOOPCMDPRT_Write,			this); //S
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("Writeln", 				&LOOPCMDPRT_Writeln,		this); //S
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("Endl", 					&LOOPCMDPRT_Endl,			this); //
		poLOOP->NewCommand("SetFont", 				&LOOPCMDPRT_SetFont,		this); //I
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("PromptString", 			&LOOPCMDPRT_PromptString,	this); //[S]
			poLOOP->AddParam(PARAM_STRING_REF);
		poLOOP->NewCommand("PromptInt", 			&LOOPCMDPRT_PromptInt,		this); //[I]
			poLOOP->AddParam(PARAM_INT_REF);
		poLOOP->NewCommand("PromptFloat", 			&LOOPCMDPRT_PromptFloat,	this); //[F]
			poLOOP->AddParam(PARAM_FLOAT_REF);
		poLOOP->NewCommand("RefreshScreen",			&LOOPCMDPRT_RefreshScreen,	this); //
		poLOOP->NewCommand("RefreshConsole",		&LOOPCMDPRT_RefreshConsole, this); //
		poLOOP->NewCommand("ScrollOn",				&LOOPCMDPRT_ScrollOn,		this); //
		poLOOP->NewCommand("ScrollOff",				&LOOPCMDPRT_ScrollOff, 		this); //
		poLOOP->NewCommand("ViewScroll",			&LOOPCMDPRT_ViewScroll, 	this); //
		poLOOP->NewCommand("ClearScroll",			&LOOPCMDPRT_ClearScroll, 	this); //
	//- [Speech] -
		poLOOP->NewCommand("GosubTalkResponse",		&LOOPCMDPRT_GosubTalkResponse,this);//
		poLOOP->NewCommand("Say",					&LOOPCMDPRT_Say, 			this);	//S
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("SayInt",				&LOOPCMDPRT_SayInt,			this);	//I
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("Ask",					&LOOPCMDPRT_Ask, 			this);	//[S]S
			poLOOP->AddParam(PARAM_STRING_REF);
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("AskInt",				&LOOPCMDPRT_AskInt,			this);	//[I]S
			poLOOP->AddParam(PARAM_INT_REF);
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("IfAskYN",				&LOOPCMDPRT_IfAskYN,		this);	//S
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("Pause",					&LOOPCMDPRT_Pause, 			this);	//II
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("PauseMs",				&LOOPCMDPRT_PauseMs,		this); //I
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("WaitForKey",			&LOOPCMDPRT_WaitForKey,		this);	
		poLOOP->NewCommand("DisplayFile",			&LOOPCMDPRT_DisplayFile,	this);	//S
			poLOOP->AddParam(PARAM_STRING);
	//- [Maps] -
		poLOOP->NewCommand("MoveToMapN",			&LOOPCMDPRT_MoveToMapN,		this);	
		poLOOP->NewCommand("MoveToMapS",			&LOOPCMDPRT_MoveToMapS,		this);	
		poLOOP->NewCommand("MoveToMapW",			&LOOPCMDPRT_MoveToMapW,		this);	
		poLOOP->NewCommand("MoveToMapE",			&LOOPCMDPRT_MoveToMapE,		this);	
		poLOOP->NewCommand("MoveToMap",				&LOOPCMDPRT_MoveToMap,		this);	//IIII
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
	//- [Date\Time] -
		poLOOP->NewCommand("GetDay",				&LOOPCMDPRT_GetDay,			this);	//[I]
			poLOOP->AddParam(PARAM_INT_REF);
		poLOOP->NewCommand("GetMonth",				&LOOPCMDPRT_GetMonth,		this);	//[I]
			poLOOP->AddParam(PARAM_INT_REF);
		poLOOP->NewCommand("GetYear",				&LOOPCMDPRT_GetYear,		this);	//[I]
			poLOOP->AddParam(PARAM_INT_REF);
		poLOOP->NewCommand("GetHour",				&LOOPCMDPRT_GetHour,		this);	//[I]
			poLOOP->AddParam(PARAM_INT_REF);
		poLOOP->NewCommand("GetMinute",				&LOOPCMDPRT_GetMinute,		this);	//[I]
			poLOOP->AddParam(PARAM_INT_REF);
		poLOOP->NewCommand("SetDay",				&LOOPCMDPRT_SetDay,			this);	//I
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("SetMonth",				&LOOPCMDPRT_SetMonth,		this);	//I
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("SetYear",				&LOOPCMDPRT_SetYear,		this);	//I
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("SetHour",				&LOOPCMDPRT_SetHour,		this);	//I
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("SetMinute",				&LOOPCMDPRT_SetMinute,		this);	//I
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("AddDays",				&LOOPCMDPRT_AddDays,		this);	//I
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("CelestialClockOn",		&LOOPCMDPRT_CelestialClockOn,	this);	//
		poLOOP->NewCommand("CelestialClockOff",		&LOOPCMDPRT_CelestialClockOff,	this);  //
		poLOOP->NewCommand("TurnLightingOn",		&LOOPCMDPRT_TurnLightingOn,		this);	//
		poLOOP->NewCommand("TurnLightingOff",		&LOOPCMDPRT_TurnLightingOff,	this);	//
	//- [AI Path Finding Commands] -
		poLOOP->NewCommand("MoveToPosition",		&LOOPCMDPRT_MoveToPosition, this); //II
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
	//- [Battle Commands] -
		poLOOP->NewCommand("Battle",				&LOOPCMDPRT_Battle,			this);	//II
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
	//- [Player Commands] -
		poLOOP->NewCommand("PromptPlayer",			&LOOPCMDPRT_PromptPlayer,	this);	//[I]
			poLOOP->AddParam(PARAM_INT_REF);
		poLOOP->NewCommand("GivePlayer",			&LOOPCMDPRT_GivePlayer,		this);	//I
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("RemovePlayer",			&LOOPCMDPRT_RemovePlayer,	this);	//I
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("SetPlayerVehicle",		&LOOPCMDPRT_SetPlayerVehicle, this);//I
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("PutPlayer",				&LOOPCMDPRT_PutPlayer,		this);	//II
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("GiveHP",				&LOOPCMDPRT_GiveHP,			this);			//II
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("TakeHP",				&LOOPCMDPRT_TakeHP,			this);			//IIS
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("SetHP",					&LOOPCMDPRT_SetHP,			this);			//II
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("GetHP",					&LOOPCMDPRT_GetHP,			this);			//II
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("GiveMaxHP",				&LOOPCMDPRT_GiveMaxHP,		this);			//II
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("TakeMaxHP",				&LOOPCMDPRT_TakeMaxHP,		this);			//IIS
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("SetMaxHP",				&LOOPCMDPRT_SetMaxHP,		this);			//II
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("GetMaxHP",				&LOOPCMDPRT_GetMaxHP,		this);			//II
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
	//- [Inventory] -
		poLOOP->NewCommand("GiveGold",				&LOOPCMDPRT_GiveGold,		this);	//I
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("TakeGold",				&LOOPCMDPRT_TakeGold,		this);	//IS
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("GetGold",				&LOOPCMDPRT_GetGold,		this);	//[i]
			poLOOP->AddParam(PARAM_INT_REF);
		poLOOP->NewCommand("SetGold",				&LOOPCMDPRT_SetGold,		this);	//I
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("GiveFood",				&LOOPCMDPRT_GiveFood,		this);	//I
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("TakeFood",				&LOOPCMDPRT_TakeFood,		this);	//IS
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("GetFood",				&LOOPCMDPRT_GetFood,		this);	//[i]
			poLOOP->AddParam(PARAM_INT_REF);
		poLOOP->NewCommand("SetFood",				&LOOPCMDPRT_SetFood,		this);	//I
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("GiveTorches",			&LOOPCMDPRT_GiveTorches,	this);	//I
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("TakeTorches",			&LOOPCMDPRT_TakeTorches,	this);	//IS
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("GetTorches",			&LOOPCMDPRT_GetTorches,		this);	//[i]
			poLOOP->AddParam(PARAM_INT_REF);
		poLOOP->NewCommand("SetTorches",			&LOOPCMDPRT_SetTorches,		this);	//I
			poLOOP->AddParam(PARAM_INT);			
		poLOOP->NewCommand("GiveWeapon",			&LOOPCMDPRT_GiveWeapon,		this);	//II
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("TakeWeapon",			&LOOPCMDPRT_TakeWeapon,		this);	//IIS
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("GetWeapon",				&LOOPCMDPRT_GetWeapon,		this);	//[i]I
			poLOOP->AddParam(PARAM_INT_REF);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("SetWeapon",				&LOOPCMDPRT_SetWeapon,		this);	//II
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("GiveArmor",				&LOOPCMDPRT_GiveArmor,		this);	//II
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("TakeArmor",				&LOOPCMDPRT_TakeArmor,		this);	//IIS
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("GetArmor",				&LOOPCMDPRT_GetArmor,		this);	//[i]I
			poLOOP->AddParam(PARAM_INT_REF);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("SetArmor",				&LOOPCMDPRT_SetArmor,		this);	//II
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("GiveScriptedItem",		&LOOPCMDPRT_GiveScriptedItem,	this);	//II
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("TakeScriptedItem",		&LOOPCMDPRT_TakeScriptedItem,	this);	//IIS
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("GetScriptedItem",		&LOOPCMDPRT_GetScriptedItem,	this);	//[i]I
			poLOOP->AddParam(PARAM_INT_REF);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("SetScriptedItem",		&LOOPCMDPRT_SetScriptedItem,	this);	//II
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
	//- [Message Commands] -
		poLOOP->NewCommand("Call",					&LOOPCMDPRT_Call,			this);		//SS
			poLOOP->AddParam(PARAM_STRING);
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("CallNorth",					&LOOPCMDPRT_CallNorth,		this);	//S
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("CallSouth",					&LOOPCMDPRT_CallSouth,		this);	//S
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("CallWest",					&LOOPCMDPRT_CallWest,		this);	//S
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("CallEast",					&LOOPCMDPRT_CallEast,		this);	//S
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("CallGlobal",			&LOOPCMDPRT_CallGlobal,		this);		//S
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("Ping",					&LOOPCMDPRT_Ping,			this);		//S
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("PingClass",				&LOOPCMDPRT_PingClass,		this);		//SS
			poLOOP->AddParam(PARAM_STRING);
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("PingClassAndDeriv",		&LOOPCMDPRT_PingClassAndDeriv, this);	//SS
			poLOOP->AddParam(PARAM_STRING);
			poLOOP->AddParam(PARAM_STRING);
	//- [Viewport Commands] -
		poLOOP->NewCommand("MoveViewportTo",		&LOOPCMDPRT_MoveViewportTo,		this);	//II
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("MoveViewportNorth",		&LOOPCMDPRT_MoveViewportNorth,	this);
		poLOOP->NewCommand("MoveViewportSouth",		&LOOPCMDPRT_MoveViewportSouth,	this);
		poLOOP->NewCommand("MoveViewportWest",		&LOOPCMDPRT_MoveViewportWest,	this);
		poLOOP->NewCommand("MoveViewportEast",		&LOOPCMDPRT_MoveViewportEast,	this);
	//- [Transportation Commands] -
		poLOOP->NewCommand("Transport",				&LOOPCMDPRT_Transport,			this);	//IIII
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
	//- [Flags] -
		poLOOP->NewCommand("FlagOn",				&LOOPCMDPRT_FlagOn,				this);	//S
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("FlagOff",				&LOOPCMDPRT_FlagOff,			this);	//S
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("FlagSwitch",			&LOOPCMDPRT_FlagSwitch,			this);	//S
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("FlagExists",			&LOOPCMDPRT_FlagExists,			this);	//[I]S
			poLOOP->AddParam(PARAM_INT_REF);
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("IfFlagExists",			&LOOPCMDPRT_IfFlagExists,		this);	//S		
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("IfFlag",				&LOOPCMDPRT_IfFlag,				this);	//S
			poLOOP->AddParam(PARAM_STRING);
		poLOOP->NewCommand("IfMapType",				&LOOPCMDPRT_IfMapType,			this);	//S
			poLOOP->AddParam(PARAM_STRING);
	//- [Spawn] -
		poLOOP->NewCommand("SpawnVehicleObject",	&LOOPCMDPRT_SpawnVehicleObject,	this);	//III
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
	//- [Misc.] -
		poLOOP->NewCommand("IfInBox",				&LOOPCMDPRT_IfInBox,			this);	//IIII
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("IfOnTerrainGroup",		&LOOPCMDPRT_IfOnTerrainGroup,	this);	//S
			poLOOP->AddParam(PARAM_STRING);		
		poLOOP->NewCommand("Sleep",					&LOOPCMDPRT_Sleep,				this);	//III
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
			poLOOP->AddParam(PARAM_INT);
		poLOOP->NewCommand("IfPlayerVehicle",		*LOOPCMDPRT_IfPlayerVehicle,	this);	//I
			poLOOP->AddParam(PARAM_INT);
}
//------------------------------------------------------------------------------------------- [Graphics] -
//III
void LL_LOOPLib_Lore::LOOPCMD_SetColor(LOOP_Info oInfo)
{	//Set the colors
		myiColorRed		= oInfo.GrabInt(0);
		myiColorGreen	= oInfo.GrabInt(1);
		myiColorBlue	= oInfo.GrabInt(2);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_LOOPLib_Lore::LOOPCMD_SetAlpha(LOOP_Info oInfo)
{	//Set the colors
		myiColorAlpha	= oInfo.GrabInt(0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//II
void LL_LOOPLib_Lore::LOOPCMD_DrawPixel(LOOP_Info oInfo)
{	mypoScreen->DrawPixel(oInfo.GrabInt(0), oInfo.GrabInt(1), myiColorRed, myiColorGreen, myiColorBlue,
						  myiColorAlpha);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//III
void LL_LOOPLib_Lore::LOOPCMD_DrawLine(LOOP_Info oInfo)
{	mypoScreen->DrawLine(oInfo.GrabInt(0), oInfo.GrabInt(1), oInfo.GrabInt(2), oInfo.GrabInt(3),
						 myiColorRed, myiColorGreen, myiColorBlue, myiColorAlpha);

	mypoScreen->DrawLine(0, 0, 200, 200, COLOR_RED, myiColorAlpha);
	mypoScreen->DrawRectangle(0, 0, 200, 200, COLOR_RED, myiColorAlpha);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//IIII
void LL_LOOPLib_Lore::LOOPCMD_DrawRectangle(LOOP_Info oInfo)
{	mypoScreen->DrawRectangle(oInfo.GrabInt(0), oInfo.GrabInt(1), oInfo.GrabInt(2), oInfo.GrabInt(3),
							  myiColorRed, myiColorGreen, myiColorBlue, myiColorAlpha);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//IIII
void LL_LOOPLib_Lore::LOOPCMD_DrawFillRectangle(LOOP_Info oInfo)
{	mypoScreen->DrawFillRectangle(oInfo.GrabInt(0), oInfo.GrabInt(1), oInfo.GrabInt(2), oInfo.GrabInt(3),
								  myiColorRed, myiColorGreen, myiColorBlue, myiColorAlpha);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//III
void LL_LOOPLib_Lore::LOOPCMD_DrawCircle(LOOP_Info oInfo)
{	mypoScreen->DrawCircle(oInfo.GrabInt(0), oInfo.GrabInt(1), oInfo.GrabInt(2),
						   myiColorRed, myiColorGreen, myiColorBlue, myiColorAlpha);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//III
void LL_LOOPLib_Lore::LOOPCMD_DrawFillCircle(LOOP_Info oInfo)
{	mypoScreen->DrawFillCircle(oInfo.GrabInt(0), oInfo.GrabInt(1), oInfo.GrabInt(2),
							   myiColorRed, myiColorGreen, myiColorBlue, myiColorAlpha);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//IIS
void LL_LOOPLib_Lore::LOOPCMD_DrawText(LOOP_Info oInfo)
{	mypoPainter->MainConsole().FontPalette()->operator[](mypoPainter->TalkConsole().CurrentFont()).WriteTo
	(	*mypoScreen,
   		oInfo.GrabInt(0),
     	oInfo.GrabInt(1),
      	oInfo.GrabString(0)
  	);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[I]S
void LL_LOOPLib_Lore::LOOPCMD_LoadFont(LOOP_Info oInfo)
{	mypoPainter->MainConsole().FontPalette()->AddFont
	(	"./" + mypoGame->GraphicsDir() + "/" + oInfo.GrabString(0), 8, 14, COLOR_BLUE
 	);
	oInfo.SetInt(oInfo.GrabIntRef(0), mypoPainter->MainConsole().FontPalette()->Length() - 1);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//SII
void LL_LOOPLib_Lore::LOOPCMD_DrawImage(LOOP_Info oInfo)
{	ASFC_Surface toSurface;
	toSurface.LoadImage("./" + mypoGame->GraphicsDir() + "/" + oInfo.GrabString(0), COLOR_BLUE);
	toSurface.BlitTo(*mypoScreen, oInfo.GrabInt(0), oInfo.GrabInt(1));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//SIII 
void LL_LOOPLib_Lore::LOOPCMD_DrawImageEffect(LOOP_Info oInfo)
{	mypoGame->EventQueue().DoEffect(oInfo.GrabInt(0), myoLoreInfo.Off());
	
	mypoGame->EventQueue().DeEffectWithImage
 	(	oInfo.GrabInt(2),
  		myoLoreInfo.Off(),
    	oInfo.GrabInt(0),
     	oInfo.GrabInt(1),
      	"./" + mypoGame->GraphicsDir() + "/" + oInfo.GrabString(0)
	);

	myoLoreInfo.SetTurnEnded(true);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//III
void LL_LOOPLib_Lore::LOOPCMD_DrawTerrain(LOOP_Info oInfo)
{	mypoGame->TerrainSet().Terrain(oInfo.GrabInt(0)).BlitTo
	(	*mypoScreen, oInfo.GrabInt(1), oInfo.GrabInt(2)
  	);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//
void LL_LOOPLib_Lore::LOOPCMD_Clear(LOOP_Info oInfo)
{	mypoScreen->DrawFillRectangle
	(	0, 0, mypoScreen->GetWidth(), mypoScreen->GetHeight(), COLOR_BLACK, 0xFF
  	);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//S
void LL_LOOPLib_Lore::LOOPCMD_Narate(LOOP_Info oInfo)
{	mypoPainter->NarateConsole() << oInfo.GrabString(0);
	mypoPainter->DrawNarateConsole();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//
void LL_LOOPLib_Lore::LOOPCMD_ClearNarate(LOOP_Info oInfo)
{	mypoPainter->NarateConsole().Clear();
	mypoPainter->DrawNarateConsole();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//
void LL_LOOPLib_Lore::LOOPCMD_ReDrawMap(LOOP_Info oInfo)
{	mypoGame->EventQueue().ReDrawMap(myoLoreInfo.Off());
	myoLoreInfo.SetTurnEnded(true);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//I
void LL_LOOPLib_Lore::LOOPCMD_DoEffect(LOOP_Info oInfo)
{	mypoGame->EventQueue().DoEffect(oInfo.GrabInt(0), myoLoreInfo.Off());
	myoLoreInfo.SetTurnEnded(true);
}
//----------------------------------------------------------------------------------- [Console Commands] -
//S
void LL_LOOPLib_Lore::LOOPCMD_Write(LOOP_Info oInfo)
{	if(!myfScroll)
		mypoPainter->TalkConsole() << oInfo.GrabString(0);
	else
		myoText << oInfo.GrabString(0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//S
void LL_LOOPLib_Lore::LOOPCMD_Writeln(LOOP_Info oInfo)
{	if(!myfScroll)
		mypoPainter->TalkConsole() << oInfo.GrabString(0) << "\n";
	else
		myoText << oInfo.GrabString(0) << "\n";
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//
void LL_LOOPLib_Lore::LOOPCMD_Endl(LOOP_Info oInfo)
{	mypoPainter->TalkConsole() << "\n";
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//I
void LL_LOOPLib_Lore::LOOPCMD_SetFont(LOOP_Info oInfo)
{	if(myfScroll)
	{	if(oInfo.GrabInt(0) >= 0 && oInfo.GrabInt(0) < mypoPainter->MainConsole().FontPalette()->Length())
		{	mypoPainter->MainConsole().CurrentFont(oInfo.GrabInt(0));
		}
		else
			mypoPainter->MainConsole().CurrentFont(0);
	}
	else
	{	if(oInfo.GrabInt(0) >= 0 && oInfo.GrabInt(0) < mypoPainter->MainConsole().FontPalette()->Length())
		{	mypoPainter->TalkConsole().CurrentFont(oInfo.GrabInt(0));
		}
		else
			mypoPainter->TalkConsole().CurrentFont(0);
	}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[S]
void LL_LOOPLib_Lore::LOOPCMD_PromptString(LOOP_Info oInfo)
{	string s;
	s = mypoPainter->TalkConsole().GrabString(mypoPainter->TalkConsole().CurrentFont());
	oInfo.SetString(oInfo.GrabStringRef(0), s);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[I]
void LL_LOOPLib_Lore::LOOPCMD_PromptInt(LOOP_Info oInfo)
{	int i;
	i = mypoPainter->TalkConsole().GrabInt(mypoPainter->TalkConsole().CurrentFont());
	oInfo.SetInt(oInfo.GrabIntRef(0), i);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[F]
void LL_LOOPLib_Lore::LOOPCMD_PromptFloat(LOOP_Info oInfo)
{	double d;
	d = mypoPainter->TalkConsole().GrabDouble(mypoPainter->TalkConsole().CurrentFont());
	oInfo.SetFloat(oInfo.GrabFloatRef(0), d);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_LOOPLib_Lore::LOOPCMD_RefreshScreen(LOOP_Info oInfo)
{	mypoScreen->Update();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//
void LL_LOOPLib_Lore::LOOPCMD_RefreshConsole(LOOP_Info oInfo)
{	mypoPainter->Draw();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//
void LL_LOOPLib_Lore::LOOPCMD_ScrollOn(LOOP_Info oInfo)
{	myfScroll = true;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//
void LL_LOOPLib_Lore::LOOPCMD_ScrollOff(LOOP_Info oInfo)
{	myfScroll = false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//
void LL_LOOPLib_Lore::LOOPCMD_ViewScroll(LOOP_Info oInfo)
{	//Draw in a black background
		mypoScreen->DrawFillRectangle(PLAYFIELD_X, PLAYFIELD_Y, PLAYFIELD_X2 - PLAYFIELD_X,
 	 							  	  PLAYFIELD_Y2 - PLAYFIELD_Y, COLOR_BLACK, myiColorAlpha);

	//View the text
		myoTextEditor.ViewText(&myoText);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//
void LL_LOOPLib_Lore::LOOPCMD_ClearScroll(LOOP_Info oInfo)
{	myoText.Clear();
}
//----------------------------------------------------------------------------- [Scripted Unit Commands] -
//I
void LL_LOOPLib_Lore::LOOPCMD_Move(LOOP_Info oInfo)
{	switch(oInfo.GrabInt(0))
	{	case 0: LOOPCMD_MoveNorth(oInfo); break;
		case 1: LOOPCMD_MoveSouth(oInfo); break;
		case 2: LOOPCMD_MoveWest(oInfo); break;
		case 3: LOOPCMD_MoveEast(oInfo); break;
		default: break;
	};
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
/*

 NOTICE YOU SILLY PROGRAMMER:
 	These move commands can screw up the daily routes of scripted units!!!! Fix it you lazy bum!

*/
//
void LL_LOOPLib_Lore::LOOPCMD_MoveNorth(LOOP_Info oInfo)
{	//Move the unit north
		if(myoLoreInfo.Seg() == LL_UnitSet::SEG_SCRIPTED_UNITS)
		{	mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).Move(DIR_NORTH);
		}
		else if(myoLoreInfo.Seg() == LL_UnitSet::SEG_SCRIPTED_ITEMS)
		{	// !!!
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//
void LL_LOOPLib_Lore::LOOPCMD_MoveSouth(LOOP_Info oInfo)
{	//Move the unit south
		if(myoLoreInfo.Seg() == LL_UnitSet::SEG_SCRIPTED_UNITS)
		{	mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).Move(DIR_SOUTH);
		}
		else if(myoLoreInfo.Seg() == LL_UnitSet::SEG_SCRIPTED_ITEMS)
		{	// !!!
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//
void LL_LOOPLib_Lore::LOOPCMD_MoveWest(LOOP_Info oInfo)
{	//Move the unit west
		if(myoLoreInfo.Seg() == LL_UnitSet::SEG_SCRIPTED_UNITS)
		{	mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).Move(DIR_WEST);
		}
		else if(myoLoreInfo.Seg() == LL_UnitSet::SEG_SCRIPTED_ITEMS)
		{	// !!!
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//
void LL_LOOPLib_Lore::LOOPCMD_MoveEast(LOOP_Info oInfo)
{	//Move the unit east
		if(myoLoreInfo.Seg() == LL_UnitSet::SEG_SCRIPTED_UNITS)
		{	mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).Move(DIR_EAST);
		}
		else if(myoLoreInfo.Seg() == LL_UnitSet::SEG_SCRIPTED_ITEMS)
		{	// !!!
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//S
void LL_LOOPLib_Lore::LOOPCMD_MovePath(LOOP_Info oInfo)
{	//Vars
		string s = oInfo.GrabString(0);

	//Loop through each char
		for(int i = 0; i < s.size(); i++)
		{		 if(s[i] == 'n' || s[i] == 'N') LOOPCMD_MoveNorth(oInfo);
			else if(s[i] == 's' || s[i] == 'S') LOOPCMD_MoveSouth(oInfo);
			else if(s[i] == 'w' || s[i] == 'W') LOOPCMD_MoveWest(oInfo);
			else if(s[i] == 'e' || s[i] == 'E') LOOPCMD_MoveEast(oInfo);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//
void LL_LOOPLib_Lore::LOOPCMD_Push(LOOP_Info oInfo)
{	//Vars
		int iOldX, iOldY, iChairX, iChairY;

	//If we're out of battle mode
		if(!mypoGame->InBattleMode())
		{	//Figure out if the player is North, South, West, or East of this object
				//- [North] -
					if(mypoGame->Player().Y() < mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).Y())
					{	if(!mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).Move(DIR_SOUTH))
						{	//Swap the player and chair
								iOldX = mypoGame->Player().X();
								iOldY = mypoGame->Player().Y();
								iChairX = mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).X();
								iChairY = mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).Y();
								mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).MoveFromTo
								(	iChairX,
									iChairY,
									iOldX,
									iOldY
								);
								mypoGame->Player().Place(iChairX, iChairY);
								mypoGame->Player().ChangeDir(DIR_NORTH);
								mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).ChangeDir(DIR_NORTH);
						}
						else
							mypoGame->Player().Move(DIR_SOUTH);
					}
				//- [South] -
					else if(mypoGame->Player().Y() > mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).Y())
					{	if(!mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).Move(DIR_NORTH))
						{	//Swap the player and chair
								iOldX = mypoGame->Player().X();
								iOldY = mypoGame->Player().Y();
								iChairX = mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).X();
								iChairY = mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).Y();
								mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).MoveFromTo
								(	iChairX,
									iChairY,
									iOldX,
									iOldY
								);
								mypoGame->Player().Place(iChairX, iChairY);
								mypoGame->Player().ChangeDir(DIR_SOUTH);
								mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).ChangeDir(DIR_SOUTH);
						}
						else
							mypoGame->Player().Move(DIR_NORTH);
					}
				//- [West] -
					else if(mypoGame->Player().X() < mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).X())
					{	if(!mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).Move(DIR_EAST))
						{	//Swap the player and chair
								iOldX = mypoGame->Player().X();
								iOldY = mypoGame->Player().Y();
								iChairX = mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).X();
								iChairY = mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).Y();
								mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).MoveFromTo
								(	iChairX,
									iChairY,
									iOldX,
									iOldY
								);
								mypoGame->Player().Place(iChairX, iChairY);
								mypoGame->Player().ChangeDir(DIR_WEST);
								mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).ChangeDir(DIR_WEST);
						}
						else
							mypoGame->Player().Move(DIR_EAST);
					}
				//- [East] -
					else if(mypoGame->Player().X() > mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).X())
					{	if(!mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).Move(DIR_WEST))
						{	//Swap the player and chair
								iOldX = mypoGame->Player().X();
								iOldY = mypoGame->Player().Y();
								iChairX = mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).X();
								iChairY = mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).Y();
								mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).MoveFromTo
								(	iChairX,
									iChairY,
									iOldX,
									iOldY
								);
								mypoGame->Player().Place(iChairX, iChairY);
								mypoGame->Player().ChangeDir(DIR_EAST);
								mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).ChangeDir(DIR_EAST);
						}
						else
							mypoGame->Player().Move(DIR_WEST);
					}
 		}
	//If we're fighting like a wild man
		else
		{	//Figure out if the player is North, South, West, or East of this object
				//- [North] -
					if(myiBattlePlayerY < mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).Y())
					{	LOOPCMD_MoveSouth(oInfo);
					}
				//- [South] -
					else if(myiBattlePlayerY > mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).Y())
					{	LOOPCMD_MoveNorth(oInfo);
					}
				//- [West] -
					else if(myiBattlePlayerX < mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).X())
					{	LOOPCMD_MoveEast(oInfo);
					}
				//- [East] -
					else if(myiBattlePlayerX > mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off()).X())
					{	LOOPCMD_MoveWest(oInfo);
					}
 		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//
void LL_LOOPLib_Lore::LOOPCMD_EndTurn(LOOP_Info oInfo)
{	//End the turn
		myoLoreInfo.SetTurnEnded(true);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//
void LL_LOOPLib_Lore::LOOPCMD_Die(LOOP_Info oInfo)
{	//Vars
		int iOff = myoLoreInfo.Off();
		int iSeg = myoLoreInfo.Seg();

	//If it's a scripted unit
		if(iSeg == LL_UnitSet::SEG_SCRIPTED_UNITS)
		{	int iX = mypoGame->UnitSet().ScriptedUnit(iOff).X();
			int iY = mypoGame->UnitSet().ScriptedUnit(iOff).Y();
			int iL = mypoGame->UnitSet().ScriptedUnit(iOff).Layer();
			
			mypoGame->UnitSet().ScriptedUnit(iOff).Null(true);
			mypoGame->UnitSet().ScriptedUnit(iOff).SetX(-1);
			mypoGame->UnitSet().ScriptedUnit(iOff).SetY(-1);
			mypoGame->UnitMap().SetUnitOn(iX, iY, iL, LL_UnitMap::SEG_NULL, LL_UnitMap::OFF_NULL);
		}
	//If it's an item
		//<CODE> !!!
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//
void LL_LOOPLib_Lore::LOOPCMD_Attack(LOOP_Info oInfo)
{	//Code !!!
		mypoPainter->TalkConsole() << "Battle!\n";
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//I
void LL_LOOPLib_Lore::LOOPCMD_SetScriptArmor(LOOP_Info oInfo)
{	
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//I
void LL_LOOPLib_Lore::LOOPCMD_SetScriptWeapon(LOOP_Info oInfo)
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//I
void LL_LOOPLib_Lore::LOOPCMD_SetScriptVehicle(LOOP_Info oInfo)
{	//Vars
		int iOff = myoLoreInfo.Off();
		int iSeg = myoLoreInfo.Seg();

	//If it's a scripted unit
		if(iSeg == LL_UnitSet::SEG_SCRIPTED_UNITS)
		{	LL_Vehicle oVehicle = mypoGame->UnitSet().ScriptedUnit(iOff).Vehicle();
			oVehicle.SetCode(oInfo.GrabInt(0));
			mypoGame->UnitSet().ScriptedUnit(iOff).SetVehicle(oVehicle);
		}
}
//--------------------------------------------------------------------------------------------- [Speech] -
//S
void LL_LOOPLib_Lore::LOOPCMD_GosubTalkResponse(LOOP_Info oInfo)
{	string s;
	int iFont = mypoPainter->TalkConsole().CurrentFont();

	//Grab a response
		mypoPainter->TalkConsole().CurrentFont(1);
  		s = mypoPainter->TalkConsole().GrabString(mypoPainter->TalkConsole().CurrentFont());
		mypoPainter->TalkConsole() << "\n";
		mypoPainter->TalkConsole().CurrentFont(iFont);

	//If s = "" then say bye
		if(s == "") s = "BYE";

	//Cut the string down to five letters if its too big
		if(s.size() > 5)
		{	s = s.substr(0, 5);
		}
		
	//Now turn s into the label
		s = "TALK_" + UpperString(s);

	//Create a new offset
		oInfo.NewOffset();

	//Now seek to that label, if we failed try seeking to TALK_What if that fails we're done
		if(!oInfo.Seek(s))
			if(!oInfo.Seek("TALK_WHAT"))
				oInfo.DelOffset();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//S
void LL_LOOPLib_Lore::LOOPCMD_Say(LOOP_Info oInfo)
{	//If something was previousley said and the cursor isn't at the start of a line place in a space
		if(myoLoreInfo.Talking())
		{	if(mypoPainter->TalkConsole().CursorX() != 0)
				mypoPainter->TalkConsole() << " ";
		}
		else
			myoLoreInfo.SetTalking(true);

	//Write text
		int iOldFont = mypoPainter->TalkConsole().CurrentFont();
		mypoPainter->TalkConsole().CurrentFont(3);
		mypoPainter->TalkConsole() << oInfo.GrabString(0);
		mypoPainter->TalkConsole().CurrentFont(iOldFont);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//I
void LL_LOOPLib_Lore::LOOPCMD_SayInt(LOOP_Info oInfo)
{	//If something was previousley said and the cursor isn't at the start of a line place in a space
		if(myoLoreInfo.Talking())
		{	if(mypoPainter->TalkConsole().CursorX() != 0)
				mypoPainter->TalkConsole() << " ";
		}
		else
			myoLoreInfo.SetTalking(true);

	//Write text
		int iOldFont = mypoPainter->TalkConsole().CurrentFont();
		mypoPainter->TalkConsole().CurrentFont(3);
		mypoPainter->TalkConsole() << oInfo.GrabInt(0);
		mypoPainter->TalkConsole().CurrentFont(iOldFont);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[S]S
void LL_LOOPLib_Lore::LOOPCMD_Ask(LOOP_Info oInfo)
{	//If something was previousley said and the cursor isn't at the start of a line place in a space
		if(myoLoreInfo.Talking())
		{	if(mypoPainter->TalkConsole().CursorX() != 0)
				mypoPainter->TalkConsole() << " ";
		}
		else
			myoLoreInfo.SetTalking(true);
	//Write text
		int iOldFont = mypoPainter->TalkConsole().CurrentFont();
		mypoPainter->TalkConsole().CurrentFont(2);
		mypoPainter->TalkConsole() << oInfo.GrabString(1);
		mypoPainter->TalkConsole() << "\n";
		mypoPainter->TalkConsole() << ">";
		mypoPainter->TalkConsole().CurrentFont(1);
		
	//Now ask away
		string s;
  		s = mypoPainter->TalkConsole().GrabString(mypoPainter->TalkConsole().CurrentFont());
		oInfo.SetString(oInfo.GrabStringRef(0), s);
		mypoPainter->TalkConsole() << "\n";
		
	//Set the font back
		mypoPainter->TalkConsole().CurrentFont(iOldFont);	
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[I]S
void LL_LOOPLib_Lore::LOOPCMD_AskInt(LOOP_Info oInfo)
{	//If something was previousley said and the cursor isn't at the start of a line place in a space
		if(myoLoreInfo.Talking())
		{	if(mypoPainter->TalkConsole().CursorX() != 0)
				mypoPainter->TalkConsole() << " ";
		}
		else
			myoLoreInfo.SetTalking(true);
	//Write text
		int iOldFont = mypoPainter->TalkConsole().CurrentFont();
		mypoPainter->TalkConsole().CurrentFont(2);
		mypoPainter->TalkConsole() << oInfo.GrabString(0);
		mypoPainter->TalkConsole() << "\n";
		mypoPainter->TalkConsole() << ">";
		mypoPainter->TalkConsole().CurrentFont(1);
		
	//Now ask away
		int i = mypoPainter->TalkConsole().GrabInt(mypoPainter->TalkConsole().CurrentFont());
		oInfo.SetInt(oInfo.GrabIntRef(0), i);
		mypoPainter->TalkConsole() << "\n";
		
	//Set the font back
		mypoPainter->TalkConsole().CurrentFont(iOldFont);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//S
void LL_LOOPLib_Lore::LOOPCMD_IfAskYN(LOOP_Info oInfo)
{	//If something was previousley said and the cursor isn't at the start of a line place in a space
		if(myoLoreInfo.Talking())
		{	if(mypoPainter->TalkConsole().CursorX() != 0)
				mypoPainter->TalkConsole() << " ";
		}
		else
			myoLoreInfo.SetTalking(true);
	//Write text
		int iOldFont = mypoPainter->TalkConsole().CurrentFont();
		mypoPainter->TalkConsole().CurrentFont(2);
		mypoPainter->TalkConsole() << oInfo.GrabString(0);
		mypoPainter->TalkConsole() << "\n";
		mypoPainter->TalkConsole() << ">";
		mypoPainter->TalkConsole().CurrentFont(1);
	//Now ask away
		char c;
		c = mypoPainter->TalkConsole().GrabChar((mypoPainter->TalkConsole().CurrentFont()));
		mypoPainter->TalkConsole() << "\n";
	//Set the font back
		mypoPainter->TalkConsole().CurrentFont(iOldFont);

	//If c is yes
		if(c == 'y' || c == 'Y')
		{
		}
	//Otherwise
		else
		{	//If the next line is "begin"
				if(oInfo.NextLine("BEGIN"))
				{	//Seek to the appropriate end
						oInfo.SeekToCommand("END", "BEGIN");
				}
			//Otherwise
				else
				{	//Skip a line
						oInfo.SeekSkip();
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//II
void LL_LOOPLib_Lore::LOOPCMD_Pause(LOOP_Info oInfo)
{	ASFC_Timer oTime;
	bool fBreak = false;
	ASFC_Input oInput;
	
	for(int i = 0; i < oInfo.GrabInt(0) && !fBreak; i++)
	{	mypoPainter->TalkConsole() << ".";	
		mypoPainter->Draw();
		oTime.Reset();
		
		while(oTime.Ellapsed() < oInfo.GrabInt(1) && !fBreak)
		{	oInput.Update();
  			if(	(oInput.KeyDown(SDLK_LCTRL) && oInput.KeyDown(SDLK_c))		||
				(oInput.KeyDown(SDLK_RCTRL) && oInput.KeyDown(SDLK_c))		||
				(oInput.KeyDown(SDLK_LCTRL) && oInput.KeyDown(SDLK_PAUSE))	||
				(oInput.KeyDown(SDLK_RCTRL) && oInput.KeyDown(SDLK_PAUSE)))
			{
				mypoPainter->TalkConsole() << "<LL Hard break>\n";
				fBreak = true;
			}
		}
		
		mypoScreen->Update();
	}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//I
void LL_LOOPLib_Lore::LOOPCMD_PauseMs(LOOP_Info oInfo)
{	myoTimer.Reset();
	myoTimer.Delay(oInfo.GrabInt(0));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_LOOPLib_Lore::LOOPCMD_WaitForKey(LOOP_Info oInfo)
{	//Sit here waiting for a key to be pressed
		mypoGame->Player().Input()->Update();
		mypoPainter->Draw();
		mypoScreen->Update();
		mypoGame->Player().Input()->Pause();
		while(mypoGame->Player().Input()->GetKey() != -1) {mypoGame->Player().Input()->Update();}
		mypoGame->Player().Input()->Update();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//S
void LL_LOOPLib_Lore::LOOPCMD_DisplayFile(LOOP_Info oInfo)
{	//Draw a black background & info
		mypoScreen->DrawFillRectangle(PLAYFIELD_X, PLAYFIELD_Y, PLAYFIELD_X2 - PLAYFIELD_X,
									  PLAYFIELD_Y2 - PLAYFIELD_Y, COLOR_BLACK, 255);
	//Now view the text
		myoText.Load("./" + mypoGame->DocumentationDir() + "/" + oInfo.GrabString(0));
		myoTextEditor.ViewText(&myoText);
}
//---------------------------------------------------------------------------------------------- [Maps] -
void LL_LOOPLib_Lore::LOOPCMD_MoveToMapN(LOOP_Info oInfo)
{	//w00t! Time to add an event to the queue. Pronouncced: Key-yew-yew
		mypoGame->EventQueue().GoMapNorth();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_LOOPLib_Lore::LOOPCMD_MoveToMapS(LOOP_Info oInfo)
{	mypoGame->EventQueue().GoMapSouth();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_LOOPLib_Lore::LOOPCMD_MoveToMapW(LOOP_Info oInfo)
{	mypoGame->EventQueue().GoMapWest();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_LOOPLib_Lore::LOOPCMD_MoveToMapE(LOOP_Info oInfo)
{	mypoGame->EventQueue().GoMapEast();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//II
void LL_LOOPLib_Lore::LOOPCMD_MoveToMap(LOOP_Info oInfo)
{	mypoGame->EventQueue().GoMap(oInfo.GrabInt(0), oInfo.GrabInt(1), oInfo.GrabInt(2), oInfo.GrabInt(3));
}
//------------------------------------------------------------------------------------------ [Date\Time] -
//[I]
void LL_LOOPLib_Lore::LOOPCMD_GetDay(LOOP_Info oInfo)
{	oInfo.SetInt(oInfo.GrabIntRef(0), mypoGame->Clock().Day());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[I]
void LL_LOOPLib_Lore::LOOPCMD_GetMonth(LOOP_Info oInfo)
{	oInfo.SetInt(oInfo.GrabIntRef(0), mypoGame->Clock().Month());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[I]
void LL_LOOPLib_Lore::LOOPCMD_GetYear(LOOP_Info oInfo)
{	oInfo.SetInt(oInfo.GrabIntRef(0), mypoGame->Clock().Year());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[I]
void LL_LOOPLib_Lore::LOOPCMD_GetHour(LOOP_Info oInfo)
{	oInfo.SetInt(oInfo.GrabIntRef(0), mypoGame->Clock().Hour());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[I]
void LL_LOOPLib_Lore::LOOPCMD_GetMinute(LOOP_Info oInfo)
{	oInfo.SetInt(oInfo.GrabIntRef(0), mypoGame->Clock().Minute());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//I
void LL_LOOPLib_Lore::LOOPCMD_SetDay(LOOP_Info oInfo)
{	mypoGame->Clock().SetDay(oInfo.GrabInt(0));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//I
void LL_LOOPLib_Lore::LOOPCMD_SetMonth(LOOP_Info oInfo)
{	mypoGame->Clock().SetMonth(oInfo.GrabInt(0));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//I
void LL_LOOPLib_Lore::LOOPCMD_SetYear(LOOP_Info oInfo)
{	mypoGame->Clock().SetYear(oInfo.GrabInt(0));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//I
void LL_LOOPLib_Lore::LOOPCMD_SetHour(LOOP_Info oInfo)
{	mypoGame->Clock().SetHour(oInfo.GrabInt(0));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//I
void LL_LOOPLib_Lore::LOOPCMD_SetMinute(LOOP_Info oInfo)
{	mypoGame->Clock().SetMinute(oInfo.GrabInt(0));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//I
void LL_LOOPLib_Lore::LOOPCMD_AddDays(LOOP_Info oInfo)
{	mypoGame->Clock().AddTicks
	(	mypoGame->Clock().TicksPerMinute() * oInfo.GrabInt(0) * 60 * 24
	);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//
void LL_LOOPLib_Lore::LOOPCMD_CelestialClockOn(LOOP_Info oInfo)
{	mypoGame->Clock().SetClockOn(true);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_LOOPLib_Lore::LOOPCMD_CelestialClockOff(LOOP_Info oInfo)
{	mypoGame->Clock().SetClockOn(false);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//
void LL_LOOPLib_Lore::LOOPCMD_TurnLightingOn(LOOP_Info oInfo)
{	mypoGame->EventQueue().Lighting(true, myoLoreInfo.Off());
	myoLoreInfo.SetTurnEnded(true);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//
void LL_LOOPLib_Lore::LOOPCMD_TurnLightingOff(LOOP_Info oInfo)
{	mypoGame->EventQueue().Lighting(false, myoLoreInfo.Off());
	myoLoreInfo.SetTurnEnded(true);
}
//-------------------------------------------------------------------------- [AI Path Finding Commands] -
//II
void LL_LOOPLib_Lore::LOOPCMD_MoveToPosition(LOOP_Info oInfo)
{	mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Identifier()).Call(
		oInfo.GrabInt(0), oInfo.GrabInt(1));
}
//----------------------------------------------------------------------------------- [Battle Commands] -
//II
void LL_LOOPLib_Lore::LOOPCMD_Battle(LOOP_Info oInfo)
{	mypoGame->EventQueue().Attack(-1, -1, -1, -1, oInfo.GrabInt(0), oInfo.GrabInt(1));
}
//----------------------------------------------------------------------------------- [Player Commands] -
//[I]
void LL_LOOPLib_Lore::LOOPCMD_PromptPlayer(LOOP_Info oInfo)
{	//Vars
		int iPlayer;
	//Get and set the player
		iPlayer = mypoZStats->GetPlayer(mypoGame);
		oInfo.SetInt(oInfo.GrabIntRef(0), iPlayer);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//I
void LL_LOOPLib_Lore::LOOPCMD_GivePlayer(LOOP_Info oInfo)
{	//Make sure this player exists
		if(oInfo.GrabInt(0) < 0 || oInfo.GrabInt(0) >= mypoGame->PlayerSet().NumPlayers())
		{	mypoPainter->TalkConsole() << "\nLOOP ERR: Invalid player.\n";
  			return;
		}
	//Now give it
		mypoGame->Player().PartyMembers().Resize(mypoGame->Player().PartyMembers().Length() + 1);
		mypoGame->PlayerSet().Player(
  			oInfo.GrabInt(0)).MakePartyMember(mypoGame->GraphicsDir(),
     		&mypoGame->Player().PartyMembers()[mypoGame->Player().PartyMembers().Length() - 1]);
     //And set additional info
  	 	mypoGame->Player().PartyMembers()
     		[mypoGame->Player().PartyMembers().Length() - 1].SetItemSet(&mypoGame->ItemSet());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//I
void LL_LOOPLib_Lore::LOOPCMD_RemovePlayer(LOOP_Info oInfo)
{	//Make sure this party member exists
		if(oInfo.GrabInt(0) < 0 || oInfo.GrabInt(0) >= mypoGame->Player().PartyMembers().Length())
		{	mypoPainter->TalkConsole() << "\nLOOP ERR: Invalid player.\n";
  			return;
		}
	//Remove it
		mypoGame->Player().PartyMembers().Delete(oInfo.GrabInt(0));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//I
void LL_LOOPLib_Lore::LOOPCMD_SetPlayerVehicle(LOOP_Info oInfo)
{	LL_Vehicle oVehicle = mypoGame->Player().Vehicle();
	oVehicle.SetCode(oInfo.GrabInt(0));
	mypoGame->Player().SetVehicle(oVehicle);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//II
void LL_LOOPLib_Lore::LOOPCMD_PutPlayer(LOOP_Info oInfo)
{	mypoGame->Player().Place(oInfo.GrabInt(0), oInfo.GrabInt(1));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//II
void LL_LOOPLib_Lore::LOOPCMD_GiveHP(LOOP_Info oInfo)
{	//If the player num is nonexistant do nada
		if(oInfo.GrabInt(0) < 0 || oInfo.GrabInt(0) >= mypoGame->Player().PartyMembers().Length())
			return;

	if(mypoGame->Player().PartyMembers()[oInfo.GrabInt(0)].HP() + oInfo.GrabInt(1) >
		mypoGame->Player().PartyMembers()[oInfo.GrabInt(0)].MaxHP())
	{
		mypoGame->Player().PartyMembers()[oInfo.GrabInt(0)].SetHP(mypoGame->Player().PartyMembers()[oInfo.GrabInt(0)].MaxHP());
	}
	else
		mypoGame->Player().PartyMembers()[oInfo.GrabInt(0)].SetHP(mypoGame->Player().PartyMembers()[oInfo.GrabInt(0)].HP() +
  			oInfo.GrabInt(1));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//IIS
void LL_LOOPLib_Lore::LOOPCMD_TakeHP(LOOP_Info oInfo)
{	//If the player num is nonexistant do nada
		if(oInfo.GrabInt(0) < 0 || oInfo.GrabInt(0) >= mypoGame->Player().PartyMembers().Length())
			return;
			
	if(mypoGame->Player().PartyMembers()[oInfo.GrabInt(0)].HP() - oInfo.GrabInt(1) <= 0)
	{	oInfo.Seek(oInfo.GrabString(0));
		return;
	}
	mypoGame->Player().PartyMembers()[oInfo.GrabInt(0)].SetHP(mypoGame->Player().PartyMembers()[oInfo.GrabInt(0)].HP() -
		oInfo.GrabInt(1));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//II
void LL_LOOPLib_Lore::LOOPCMD_SetHP(LOOP_Info oInfo)
{	//If the player num is nonexistant do nada
		if(oInfo.GrabInt(0) < 0 || oInfo.GrabInt(0) >= mypoGame->Player().PartyMembers().Length())
			return;

	if(oInfo.GrabInt(1) > mypoGame->Player().PartyMembers()[oInfo.GrabInt(0)].MaxHP())
		mypoGame->Player().PartyMembers()[oInfo.GrabInt(0)].SetHP(mypoGame->Player().PartyMembers()[oInfo.GrabInt(0)].MaxHP());
	else
		mypoGame->Player().PartyMembers()[oInfo.GrabInt(0)].SetHP(oInfo.GrabInt(1));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//II
void LL_LOOPLib_Lore::LOOPCMD_GetHP(LOOP_Info oInfo)
{	//If the player num is nonexistant do nada
		if(oInfo.GrabInt(0) < 0 || oInfo.GrabInt(0) >= mypoGame->Player().PartyMembers().Length())
			return;

	oInfo.SetInt(oInfo.GrabIntRef(0), mypoGame->Player().PartyMembers()[oInfo.GrabInt(0)].HP());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//II
void LL_LOOPLib_Lore::LOOPCMD_GiveMaxHP(LOOP_Info oInfo)
{	//If the player num is nonexistant do nada
		if(oInfo.GrabInt(0) < 0 || oInfo.GrabInt(0) >= mypoGame->Player().PartyMembers().Length())
			return;

	mypoGame->Player().PartyMembers()[oInfo.GrabInt(0)].SetMaxHP(mypoGame->Player().PartyMembers()[oInfo.GrabInt(0)].MaxHP() +
		oInfo.GrabInt(1));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//IIS
void LL_LOOPLib_Lore::LOOPCMD_TakeMaxHP(LOOP_Info oInfo)
{	//If the player num is nonexistant do nada
		if(oInfo.GrabInt(0) < 0 || oInfo.GrabInt(0) >= mypoGame->Player().PartyMembers().Length())
			return;

	if(mypoGame->Player().PartyMembers()[oInfo.GrabInt(0)].MaxHP() - oInfo.GrabInt(1) <= 0)
	{	oInfo.Seek(oInfo.GrabString(0));
		return;
	}
	mypoGame->Player().PartyMembers()[oInfo.GrabInt(0)].SetMaxHP(mypoGame->Player().PartyMembers()[oInfo.GrabInt(0)].MaxHP() -
 		oInfo.GrabInt(1));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//II
void LL_LOOPLib_Lore::LOOPCMD_SetMaxHP(LOOP_Info oInfo)
{	//If the player num is nonexistant do nada
		if(oInfo.GrabInt(0) < 0 || oInfo.GrabInt(0) >= mypoGame->Player().PartyMembers().Length())
			return;

	mypoGame->Player().PartyMembers()[oInfo.GrabInt(0)].SetMaxHP(oInfo.GrabInt(1));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//II
void LL_LOOPLib_Lore::LOOPCMD_GetMaxHP(LOOP_Info oInfo)
{	//If the player num is nonexistant do nada
		if(oInfo.GrabInt(0) < 0 || oInfo.GrabInt(0) >= mypoGame->Player().PartyMembers().Length())
			return;

	oInfo.SetInt(oInfo.GrabIntRef(0), mypoGame->Player().PartyMembers()[oInfo.GrabInt(0)].MaxHP());
}
//---------------------------------------------------------------------------------------- [Inventory] -
//I
void LL_LOOPLib_Lore::LOOPCMD_GiveGold(LOOP_Info oInfo)
{	//If negative do nada
		if(oInfo.GrabInt(0) < 0)
			return;

	mypoGame->Player().Inventory().GiveGold(oInfo.GrabInt(0));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//IS
void LL_LOOPLib_Lore::LOOPCMD_TakeGold(LOOP_Info oInfo)
{	//If negative do nada
		if(oInfo.GrabInt(0) < 0)
			return;

	//Take it, if too poor goto the proper label
		if(!mypoGame->Player().Inventory().TakeGold(oInfo.GrabInt(0)))
		{	oInfo.Seek(oInfo.GrabString(0));
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[i]
void LL_LOOPLib_Lore::LOOPCMD_GetGold(LOOP_Info oInfo)
{	//Return the amount of gold
		oInfo.SetInt(oInfo.GrabIntRef(0), mypoGame->Player().Inventory().Gold());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//I
void LL_LOOPLib_Lore::LOOPCMD_SetGold(LOOP_Info oInfo)
{	//If negative do nada
		if(oInfo.GrabInt(0) < 0)
			return;

	//Set the amount of gold
		mypoGame->Player().Inventory().SetGold(oInfo.GrabInt(0));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//I
void LL_LOOPLib_Lore::LOOPCMD_GiveFood(LOOP_Info oInfo)
{	//If negative do nada
		if(oInfo.GrabInt(0) < 0)
			return;
			
	mypoGame->Player().Inventory().GiveFood(oInfo.GrabInt(0));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//IS
void LL_LOOPLib_Lore::LOOPCMD_TakeFood(LOOP_Info oInfo)
{	//If negative do nada
		if(oInfo.GrabInt(0) < 0)
			return;

	//Take it, if too poor goto the proper label
		if(!mypoGame->Player().Inventory().TakeFood(oInfo.GrabInt(0)))
		{	oInfo.Seek(oInfo.GrabString(0));
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[i]
void LL_LOOPLib_Lore::LOOPCMD_GetFood(LOOP_Info oInfo)
{	//Return the amount of Food
		oInfo.SetInt(oInfo.GrabIntRef(0), mypoGame->Player().Inventory().Food());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//I
void LL_LOOPLib_Lore::LOOPCMD_SetFood(LOOP_Info oInfo)
{	//If negative do nada
		if(oInfo.GrabInt(0) < 0)
			return;

	//Set the amount of Food
		mypoGame->Player().Inventory().SetFood(oInfo.GrabInt(0));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//I
void LL_LOOPLib_Lore::LOOPCMD_GiveTorches(LOOP_Info oInfo)
{	//If negative do nada
		if(oInfo.GrabInt(0) < 0)
			return;

	mypoGame->Player().Inventory().GiveTorches(oInfo.GrabInt(0));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//IS
void LL_LOOPLib_Lore::LOOPCMD_TakeTorches(LOOP_Info oInfo)
{	//If negative do nada
		if(oInfo.GrabInt(0) < 0)
			return;

	//Take it, if too poor goto the proper label
		if(!mypoGame->Player().Inventory().TakeTorches(oInfo.GrabInt(0)))
		{	oInfo.Seek(oInfo.GrabString(0));
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[i]
void LL_LOOPLib_Lore::LOOPCMD_GetTorches(LOOP_Info oInfo)
{	//Return the amount of torches
		oInfo.SetInt(oInfo.GrabIntRef(0), mypoGame->Player().Inventory().Torches());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//I
void LL_LOOPLib_Lore::LOOPCMD_SetTorches(LOOP_Info oInfo)
{	//If negative do nada
		if(oInfo.GrabInt(0) < 0)
			return;

	//Set the amount of Food
		mypoGame->Player().Inventory().SetTorches(oInfo.GrabInt(0));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//II
void LL_LOOPLib_Lore::LOOPCMD_GiveWeapon(LOOP_Info oInfo)
{	//If negative do nada
		if(oInfo.GrabInt(0) < 0)
			return;

	mypoGame->Player().Inventory().GiveWeapon(oInfo.GrabInt(0), oInfo.GrabInt(1));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//IIS
void LL_LOOPLib_Lore::LOOPCMD_TakeWeapon(LOOP_Info oInfo)
{	//If negative do nada
		if(oInfo.GrabInt(0) < 0)
			return;

	//Take it, if too poor goto the proper label
		if(!mypoGame->Player().Inventory().TakeWeapon(oInfo.GrabInt(0), oInfo.GrabInt(1)))
		{	oInfo.Seek(oInfo.GrabString(0));
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[i]I
void LL_LOOPLib_Lore::LOOPCMD_GetWeapon(LOOP_Info oInfo)
{	//Return the amount of this weapon
		oInfo.SetInt(
  			oInfo.GrabIntRef(0), mypoGame->Player().Inventory().Weapons(oInfo.GrabInt(1)));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//II
void LL_LOOPLib_Lore::LOOPCMD_SetWeapon(LOOP_Info oInfo)
{	//If negative do nada
		if(oInfo.GrabInt(0) < 0)
			return;

	mypoGame->Player().Inventory().SetWeapons(oInfo.GrabInt(0), oInfo.GrabInt(1));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//II
void LL_LOOPLib_Lore::LOOPCMD_GiveArmor(LOOP_Info oInfo)
{	//If negative do nada
		if(oInfo.GrabInt(0) < 0)
			return;

	mypoGame->Player().Inventory().GiveArmor(oInfo.GrabInt(0), oInfo.GrabInt(1));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//IIS
void LL_LOOPLib_Lore::LOOPCMD_TakeArmor(LOOP_Info oInfo)
{	//If negative do nada
		if(oInfo.GrabInt(0) < 0)
			return;

	//Take it, if too poor goto the proper label
		if(!mypoGame->Player().Inventory().TakeArmor(oInfo.GrabInt(0), oInfo.GrabInt(1)))
		{	oInfo.Seek(oInfo.GrabString(0));
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[i]I
void LL_LOOPLib_Lore::LOOPCMD_GetArmor(LOOP_Info oInfo)
{	//Return the amount of this armor
		oInfo.SetInt(
  			oInfo.GrabIntRef(0), mypoGame->Player().Inventory().Armors(oInfo.GrabInt(1)));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//II
void LL_LOOPLib_Lore::LOOPCMD_SetArmor(LOOP_Info oInfo)
{	//If negative do nada
		if(oInfo.GrabInt(0) < 0)
			return;

	mypoGame->Player().Inventory().SetArmors(oInfo.GrabInt(0), oInfo.GrabInt(1));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//II
void LL_LOOPLib_Lore::LOOPCMD_GiveScriptedItem(LOOP_Info oInfo)
{	//If negative do nada
		if(oInfo.GrabInt(0) < 0)
			return;

	mypoGame->Player().Inventory().GiveScriptedItem(oInfo.GrabInt(0), oInfo.GrabInt(1));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//IIS
void LL_LOOPLib_Lore::LOOPCMD_TakeScriptedItem(LOOP_Info oInfo)
{	//If negative do nada
		if(oInfo.GrabInt(0) < 0)
			return;

	//Take it, if too poor goto the proper label
		if(!mypoGame->Player().Inventory().TakeScriptedItem(oInfo.GrabInt(0), oInfo.GrabInt(1)))
		{	oInfo.Seek(oInfo.GrabString(0));
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[i]I
void LL_LOOPLib_Lore::LOOPCMD_GetScriptedItem(LOOP_Info oInfo)
{	//If negative do nada
		if(oInfo.GrabInt(0) < 0)
			return;

	//Return the amount of this scripted item
		oInfo.SetInt(
  			oInfo.GrabIntRef(0), mypoGame->Player().Inventory().ScriptedItems(oInfo.GrabInt(1)));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//II
void LL_LOOPLib_Lore::LOOPCMD_SetScriptedItem(LOOP_Info oInfo)
{	//If negative do nada
		if(oInfo.GrabInt(0) < 0)
			return;

	mypoGame->Player().Inventory().SetScriptedItems(oInfo.GrabInt(0), oInfo.GrabInt(1));
}
//---------------------------------------------------------------------------------- [Message Commands] -
//SS
void LL_LOOPLib_Lore::LOOPCMD_Call(LOOP_Info oInfo)
{	//Call it
		mypoGame->EventQueue().Call(oInfo.GrabString(0), oInfo.GrabString(1), myoLoreInfo.Off());
	//End the turn
		myoLoreInfo.SetTurnEnded(true);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//S
void LL_LOOPLib_Lore::LOOPCMD_CallNorth(LOOP_Info oInfo)
{	//Call it
		mypoGame->EventQueue().CallPosition
  		(	myoLoreInfo.X(),
    		myoLoreInfo.Y() - 1,
      		myoLoreInfo.Off(),
        	oInfo.GrabString(0)
		);
	//End the turn
		myoLoreInfo.SetTurnEnded(true);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//S
void LL_LOOPLib_Lore::LOOPCMD_CallSouth(LOOP_Info oInfo)
{	//Call it
		mypoGame->EventQueue().CallPosition
  		(	myoLoreInfo.X(),
    		myoLoreInfo.Y() + 1,
      		myoLoreInfo.Off(),
        	oInfo.GrabString(0)
		);
		
	//End the turn
		myoLoreInfo.SetTurnEnded(true);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//S
void LL_LOOPLib_Lore::LOOPCMD_CallWest(LOOP_Info oInfo)
{	//Call it
		mypoGame->EventQueue().CallPosition
  		(	myoLoreInfo.X() - 1,
    		myoLoreInfo.Y(),
      		myoLoreInfo.Off(),
        	oInfo.GrabString(0)
		);
		
	//End the turn
		myoLoreInfo.SetTurnEnded(true);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//S
void LL_LOOPLib_Lore::LOOPCMD_CallEast(LOOP_Info oInfo)
{	//Call it
		mypoGame->EventQueue().CallPosition
  		(	myoLoreInfo.X()+ 1,
    		myoLoreInfo.Y(),
      		myoLoreInfo.Off(),
        	oInfo.GrabString(0)
		);
	
	//End the turn
		myoLoreInfo.SetTurnEnded(true);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//S
void LL_LOOPLib_Lore::LOOPCMD_CallGlobal(LOOP_Info oInfo)
{	mypoGame->EventQueue().GosubGlobal(oInfo.GrabString(0));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//S
void LL_LOOPLib_Lore::LOOPCMD_Ping(LOOP_Info oInfo)
{	mypoGame->EventQueue().Ping(oInfo.GrabString(0));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//SS
void LL_LOOPLib_Lore::LOOPCMD_PingClass(LOOP_Info oInfo)
{	mypoGame->EventQueue().PingClass(oInfo.GrabString(0), oInfo.GrabString(1));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//SS
void LL_LOOPLib_Lore::LOOPCMD_PingClassAndDeriv(LOOP_Info oInfo)
{	mypoGame->EventQueue().PingClassDeriv(oInfo.GrabString(0), oInfo.GrabString(1));
}
//--------------------------------------------------------------------------------- [Viewport Commands] -
//II
void LL_LOOPLib_Lore::LOOPCMD_MoveViewportTo(LOOP_Info oInfo)
{	//Move it
		mypoGame->TerrainMap().SetViewX(oInfo.GrabInt(0));
		mypoGame->TerrainMap().SetViewY(oInfo.GrabInt(1));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_LOOPLib_Lore::LOOPCMD_MoveViewportNorth(LOOP_Info oInfo)
{	//Move it
		mypoGame->TerrainMap().SetViewX(mypoGame->TerrainMap().ViewX());
		mypoGame->TerrainMap().SetViewY(mypoGame->TerrainMap().ViewY() - 1);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_LOOPLib_Lore::LOOPCMD_MoveViewportSouth(LOOP_Info oInfo)
{	//Move it
		mypoGame->TerrainMap().SetViewX(mypoGame->TerrainMap().ViewX());
		mypoGame->TerrainMap().SetViewY(mypoGame->TerrainMap().ViewY() + 1);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_LOOPLib_Lore::LOOPCMD_MoveViewportWest(LOOP_Info oInfo)
{	//Move it
		mypoGame->TerrainMap().SetViewX(mypoGame->TerrainMap().ViewX() - 1);
		mypoGame->TerrainMap().SetViewY(mypoGame->TerrainMap().ViewY());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_LOOPLib_Lore::LOOPCMD_MoveViewportEast(LOOP_Info oInfo)
{	//Move it
		mypoGame->TerrainMap().SetViewX(mypoGame->TerrainMap().ViewX() + 1);
		mypoGame->TerrainMap().SetViewY(mypoGame->TerrainMap().ViewY());
}
//-------------------------------------------------------------------------- [Transportation Commands] -
//IIII
void LL_LOOPLib_Lore::LOOPCMD_Transport(LOOP_Info oInfo)
{	mypoGame->EventQueue().GoMap(oInfo.GrabInt(0), oInfo.GrabInt(1), oInfo.GrabInt(2), oInfo.GrabInt(3));
	//End the turn
		myoLoreInfo.SetTurnEnded(true);
}
//------------------------------------------------------------------------------------------- [Flags] -
//S
void LL_LOOPLib_Lore::LOOPCMD_FlagOn(LOOP_Info oInfo)
{	mypoGame->SetFlagOn(oInfo.GrabString(0));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//S
void LL_LOOPLib_Lore::LOOPCMD_FlagOff(LOOP_Info oInfo)
{	mypoGame->SetFlagOff(oInfo.GrabString(0));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//S
void LL_LOOPLib_Lore::LOOPCMD_FlagSwitch(LOOP_Info oInfo)
{	mypoGame->SwitchFlag(oInfo.GrabString(0));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//[I]S
void LL_LOOPLib_Lore::LOOPCMD_FlagExists(LOOP_Info oInfo)
{	if(mypoGame->FlagExists(oInfo.GrabString(0)))
		oInfo.SetInt(oInfo.GrabIntRef(0), 1);
	else
		oInfo.SetInt(oInfo.GrabIntRef(0), 0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//S
void LL_LOOPLib_Lore::LOOPCMD_IfFlagExists(LOOP_Info oInfo)
{	//If the flag exists
		if(mypoGame->FlagExists(oInfo.GrabString(0)))
		{
		}
	//Otherwise
		else
		{	//If the next line is "begin"
				if(oInfo.NextLine("BEGIN"))
				{	//Seek to the appropriate end
						oInfo.SeekToCommand("END", "BEGIN");
				}
			//Otherwise
				else
				{	//Skip a line
						oInfo.SeekSkip();
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//S
void LL_LOOPLib_Lore::LOOPCMD_IfFlag(LOOP_Info oInfo)
{	//If the flag is on
		if(mypoGame->IsFlagOn(oInfo.GrabString(0)))
		{
		}
	//Otherwise
		else
		{	//If the next line is "begin"
				if(oInfo.NextLine("BEGIN"))
				{	//Seek to the appropriate end
						oInfo.SeekToCommand("END", "BEGIN");
				}
			//Otherwise
				else
				{	//Skip a line
						oInfo.SeekSkip();
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//S
void LL_LOOPLib_Lore::LOOPCMD_IfMapType(LOOP_Info oInfo)
{	//If the flag is on
		if(mypoGame->TerrainMap().MapType() == UpperString(oInfo.GrabString(0)))
		{
		}
	//Otherwise
		else
		{	//If the next line is "begin"
				if(oInfo.NextLine("BEGIN"))
				{	//Seek to the appropriate end
						oInfo.SeekToCommand("END", "BEGIN");
				}
			//Otherwise
				else
				{	//Skip a line
						oInfo.SeekSkip();
				}
		}
}
//-------------------------------------------------------------------------------------------- [Spawn] -
//III
void LL_LOOPLib_Lore::LOOPCMD_SpawnVehicleObject(LOOP_Info oInfo)
{	//Vars
		int iUnit;
	//Place it
		mypoGame->UnitSet().AddVehicle(oInfo.GrabInt(1), oInfo.GrabInt(2), 2, "", oInfo.GrabInt(0));
		iUnit = mypoGame->UnitSet().NumVehicles() - 1;
		mypoGame->UnitMap().SetUnitOn(oInfo.GrabInt(1), oInfo.GrabInt(2), 2, LL_UnitSet::SEG_VEHICLES, iUnit);
}
//--------------------------------------------------------------------------------------------- [Misc.] -
//IIII
void LL_LOOPLib_Lore::LOOPCMD_IfInBox(LOOP_Info oInfo)
{	//If this unit is within that box and is a scripted unit
		if(myoLoreInfo.Seg() == LL_UnitSet::SEG_SCRIPTED_UNITS)
		{	//Vars
				LL_ScriptedUnit* mypoUnit = &mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off());
				
			//If it's in that box
				if(mypoUnit->X() >= oInfo.GrabInt(0) && mypoUnit->Y() >= oInfo.GrabInt(1) &&
				   mypoUnit->X() <= oInfo.GrabInt(2) && mypoUnit->Y() <= oInfo.GrabInt(3))
   				{
   				}
			//Otherwise
				else
				{	//If the next line is "begin"
						if(oInfo.NextLine("BEGIN"))
						{	//Seek to the appropriate end
								oInfo.SeekToCommand("END", "BEGIN");
						}
					//Otherwise
						else
						{	//Skip a line
								oInfo.SeekSkip();
						}
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//S
void LL_LOOPLib_Lore::LOOPCMD_IfOnTerrainGroup(LOOP_Info oInfo)
{	//If this unit is within that group and is a scripted unit
		if(myoLoreInfo.Seg() == LL_UnitSet::SEG_SCRIPTED_UNITS)
		{	//Vars
				LL_ScriptedUnit* mypoUnit = &mypoGame->UnitSet().ScriptedUnit(myoLoreInfo.Off());
				
			//If it's in that group
				if(mypoGame->TerrainMap().GetTerrain(mypoUnit->X(), mypoUnit->Y()).IsGroup(oInfo.GrabString(0)))
   				{
   				}
			//Otherwise
				else
				{	//If the next line is "begin"
						if(oInfo.NextLine("BEGIN"))
						{	//Seek to the appropriate end
								oInfo.SeekToCommand("END", "BEGIN");
						}
					//Otherwise
						else
						{	//Skip a line
								oInfo.SeekSkip();
						}
				}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//III
void LL_LOOPLib_Lore::LOOPCMD_Sleep(LOOP_Info oInfo)
{	mypoGame->EventQueue().Sleep(oInfo.GrabInt(0), oInfo.GrabInt(1), oInfo.GrabInt(2));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//I
void LL_LOOPLib_Lore::LOOPCMD_IfPlayerVehicle(LOOP_Info oInfo)
{	//If the flag is on
		if(mypoGame->Player().Vehicle().Code() == oInfo.GrabInt(0))
		{
		}
	//Otherwise
		else
		{	//If the next line is "begin"
				if(oInfo.NextLine("BEGIN"))
				{	//Seek to the appropriate end
						oInfo.SeekToCommand("END", "BEGIN");
				}
			//Otherwise
				else
				{	//Skip a line
						oInfo.SeekSkip();
				}
		}
}
