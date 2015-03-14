/* Protected under the GNU General Public License read and see copying.txt For details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			mapeditor.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: <Please Enter Here>
*/
#ifndef LEDIT_MAPEDITOR_H_
#define LEDIT_MAPEDITOR_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Parent
	#include "editor.h"
//Aggregates
	#include <asfc/input.h>
	#include <asfc/timer.h>
	#include <asfc/effects.h>
//Realizes
	#include <lbase/game.h>
	#include "filechooser.h"
	#include "terrainseteditor.h"
	#include "mapinfoeditor.h"
	#include "mapseteditor.h"
	#include "vehicleseteditor.h"
	#include <lbase/help.h>
	#include "classseteditor.h"
	#include "globalscripteditor.h"
	#include "mapobjecteditor.h"
	#include "scripteduniteditor.h"
	#include "mapobjectremover.h"
	#include "monsterseteditor.h"
	#include "playerseteditor.h"
	#include "routeeditor.h"
	#include "itemseteditor.h"
	#include "chesteditor.h"
	#include "transporteditor.h"
	#include "vehiclebattlekeyeditor.h"
	#include "vehicleobjecteditor.h"
	#include "vehicleobjectseteditor.h"
	#include "buttonsstrip.h"
	#include "globalinfoeditor.h"
	#include "spawnereditor.h"
	#include "graphicslist.h"
//Dependencies
	#include <asfc/utils.h>
	#include <lbase/guimetrics.h>
	#include <lbase/pathnodes.h>
	#include <lbase/painter.h>

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LEDIT_MapEditor : public LEDIT_Editor
{	public:
	//type
		struct LEDIT_TestInformation
		{	//Vars
  				bool fTest;
	  			int iMap, iX, iY;
  
  			LEDIT_TestInformation()
			{	fTest = false;
				iMap  = -1;
				iX    = -1;
				iY    = -1;
			}
		};

	//- [Construction] -
		LEDIT_MapEditor();
	//- [Editting] -
		LEDIT_TestInformation Edit(int iX, int iY);
		void SwitchMap(int iNewMap);
		MEMVAR_SETGET(SetTerrainSetEditor,	TerrainSetEditor,	LEDIT_TerrainSetEditor*, mypoTerrainSetEditor);
		MEMVAR_SETGET(SetMapInfoEditor,		MapInfoEditor,		LEDIT_MapInfoEditor*,	 mypoMapInfoEditor);
		MEMVAR_SETGET(SetGlobalInfoEditor,	GlobalInfoEditor,	LEDIT_GlobalInfoEditor*, mypoGlobalInfoEditor);
		MEMVAR_SETGET(SetMapSetEditor,		MapSetEditor,		LEDIT_MapSetEditor*,	 mypoMapSetEditor);
		MEMVAR_SETGET(SetVehicleSetEditor,	VehicleSetEditor,	LEDIT_VehicleSetEditor*, mypoVehicleSetEditor);
		MEMVAR_SETGET(SetHelp,				Help,				LL_Help*,				 mypoHelp);
		MEMVAR_SETGET(SetClassSetEditor,	ClassSetEditor,		LEDIT_ClassSetEditor*,	 mypoClassSetEditor);
		MEMVAR_SETGET(SetGlobalScriptEditor,GlobalScriptEditor,	LEDIT_GlobalScriptEditor*,mypoGlobalScriptEditor);
		MEMVAR_SETGET(SetMapObjectEditor,	MapObjectEditor,	LEDIT_MapObjectEditor*,	 mypoMapObjectEditor);
		MEMVAR_SETGET(SetScriptedUnitEditor,ScriptedUnitEditor,	LEDIT_ScriptedUnitEditor*,mypoScriptedUnitEditor);
		MEMVAR_SETGET(SetMapObjectRemover,	MapObjectRemover,	LEDIT_MapObjectRemover*, mypoMapObjectRemover);
		MEMVAR_SETGET(SetMonsterSetEditor,	MonsterSetEditor,	LEDIT_MonsterSetEditor*, mypoMonsterSetEditor);
		MEMVAR_SETGET(SetPlayerSetEditor,	PlayerSetEditor,	LEDIT_PlayerSetEditor*, mypoPlayerSetEditor);
		MEMVAR_SETGET(SetRouteEditor,		RouteEditor,		LEDIT_RouteEditor*,		 mypoRouteEditor);
		MEMVAR_SETGET(SetItemSetEditor,		ItemSetEditor,		LEDIT_ItemSetEditor*,	 mypoItemSetEditor);
		MEMVAR_SETGET(SetChestEditor,		ChestEditor,		LEDIT_ChestEditor*,	 	 mypoChestEditor);
		MEMVAR_SETGET(SetTransportEditor,	TransportEditor,	LEDIT_TransportEditor*,	 mypoTransportEditor);
		MEMVAR_SETGET(SetKeyEditor,			KeyEditor,			LEDIT_VehicleBattleKeyEditor*, mypoKeyEditor);
		MEMVAR_SETGET(SetVehicleObjectEditor, VehicleObjectEditor, LEDIT_VehicleObjectEditor*, mypoVehicleObjectEditor);
		MEMVAR_SETGET(SetVehicleObjectSetEditor, VehicleObjectSetEditor, LEDIT_VehicleObjectSetEditor*, mypoVehiclObjectSetEditor);
		MEMVAR_SETGET(SetButtonsStrip,		ButtonsStrip,		LEDIT_ButtonsStrip*,	 mypoButtonsStrip);
		MEMVAR_SETGET(SetSpawnerEditor,		SpawnerEditor,		LEDIT_SpawnerEditor*,	 mypoSpawnerEditor);
		MEMVAR_SETGET(SetGraphicsList,		GraphicsList,		LEDIT_GraphicsList*,	 mypoGraphicsList);
	//- [Map Settings] -
		void SetGame(LL_Game* poGame);
		MEMVAR_GET(Game, LL_Game*, mypoGame);
		
	protected:
	//Type
		//A map edit state describes what "state" the map editor is in. Recursive definition? You  bet 'Ya!
		enum MAPEDIT_STATE
		{	MAPEDIT_STATE_GOOD = 0,
			MAPEDIT_STATE_TEST,
			MAPEDIT_STATE_EXIT
		};
	
	//P- [Editting] -P
		void 	Update();
		SDLKey	GetEdittingKey(SDLKey* piMod);
		bool 	HandleMouse();
		void 	HandleEdittingKey(SDLKey iKey, SDLKey iMod);
		void	DrawStats();
		void 	Draw();
		void	WaitForAKey();
		void	MoveScreen(ASFC_DIRECTION iDir);
		void	MoveViewports(ASFC_DIRECTION iDir);
		void	MoveViewportsTo(int iX, int iY);
		void	Plot();
		void	PlotSquare(C_i4(iRad, iCenterX, iCenterY, iTerrain));
		void	Fill(int iX, int iY, int iTo, int iFrom);
		bool	LegalFill(int iX, int iY, int iLegalTerrain);
		int		CursorX();
		int		CursorY();
		MEMVAR_SETGET(SetCursorLayer, CursorLayer, int, myiCursorLayer);
		void 	DrawQuickKeys();
		void	DrawOtherInfo();
		void	GemView();
		void	PressButton(int iNum);
		ASFC_DIRECTION PromptDirection();
	//Const
		//Images
			#define LEDIT_MapEditor__Logo_Image "data/gui/editor/logo.png"
		//Layers
			static const int LAYER_VEHICLE = 2;
		//Mods
			static const SDLKey MOD_NONE			= SDLKey(int(-1));
			static const SDLKey MOD_CTRL			= SDLK_LCTRL;
  		//NoMod + 
			static const SDLKey KEY_EXIT			= SDLK_ESCAPE;
			static const SDLKey KEY_EXIT2			= SDLK_q;
			static const SDLKey KEY_TEST			= SDLK_y;
			static const SDLKey KEY_MOVECUR_NORTH	= SDLK_UP;
			static const SDLKey KEY_MOVECUR_NORTH2	= SDLK_KP8;
			static const SDLKey KEY_MOVECUR_SOUTH	= SDLK_DOWN;
			static const SDLKey KEY_MOVECUR_SOUTH2	= SDLK_KP2;
			static const SDLKey KEY_MOVECUR_WEST	= SDLK_LEFT;
			static const SDLKey KEY_MOVECUR_WEST2	= SDLK_KP4;
			static const SDLKey KEY_MOVECUR_EAST	= SDLK_RIGHT;
			static const SDLKey KEY_MOVECUR_EAST2	= SDLK_KP6;
			static const SDLKey KEY_MOVECUR_NRTHWST	= SDLK_KP7;
			static const SDLKey KEY_MOVECUR_NRTHEST	= SDLK_KP9;
			static const SDLKey KEY_MOVECUR_STHWST	= SDLK_KP1;
			static const SDLKey KEY_MOVECUR_STHEST	= SDLK_KP3;
			static const SDLKey KEY_GEM_VIEW		= SDLK_g;
			static const SDLKey KEY_PLOT			= SDLK_SPACE;
			static const SDLKey KEY_PENMODE_SWITCH	= SDLK_p;
			static const SDLKey KEY_FILL			= SDLK_x;
			static const SDLKey KEY_CHANGETERRAIN	= SDLK_TAB;
			static const SDLKey KEY_CHANGETERRAIN2	= SDLK_F2;
			static const SDLKey KEY_EDIT_INFO		= SDLK_i;
			static const SDLKey KEY_EDIT_GLOBAL_INFO= SDLK_u;
			static const SDLKey KEY_SWITCH_MAPS		= SDLK_m;
			static const SDLKey KEY_SWITCH_MAPS2	= SDLK_F4;
			static const SDLKey KEY_SWITCH_PREV_MAP	= SDLK_COMMA;
			static const SDLKey KEY_SWITCH_NEXT_MAP	= SDLK_PERIOD;
			static const SDLKey KEY_EDIT_BATTLE_MAP	= SDLK_b;
			static const SDLKey KEY_ABOUT 			= SDLK_a;
			static const SDLKey KEY_ABOUT2 			= SDLK_F12;
			static const SDLKey KEY_SAVE			= SDLK_s;
			static const SDLKey KEY_EDIT_VEHICLE_SET= SDLK_F3;
			static const SDLKey KEY_CLEAR_MAP		= SDLK_k;
			static const SDLKey KEY_HELP			= SDLK_h;
			static const SDLKey KEY_HELP2			= SDLK_F1;
			static const SDLKey KEY_JOT_NOTES		= SDLK_j;
			static const SDLKey KEY_EDIT_CLASS_SET	= SDLK_F7;
			static const SDLKey KEY_EDIT_GLOBAL_CLASS_SET	= SDLK_F8;
			static const SDLKey KEY_EDIT_GLOBAL_SCRIPT = SDLK_F9;
			static const SDLKey KEY_PLOT_INSTANCE	= SDLK_o;
			static const SDLKey KEY_KILL_INSTANCE	= SDLK_DELETE;
			static const SDLKey KEY_EDIT_INSTANCE	= SDLK_RETURN;
			static const SDLKey KEY_EDIT_DAILY_PATH	= SDLK_d;
			static const SDLKey KEY_COPY			= SDLK_c;
			static const SDLKey KEY_PASTE			= SDLK_v;
			static const SDLKey KEY_EDIT_MONSTER_SET= SDLK_F6;
			static const SDLKey KEY_PLOT_MONSTER	= SDLK_f;
			static const SDLKey KEY_EDIT_ROUTES		= SDLK_r;
			static const SDLKey KEY_EDIT_PLACE_ROUTE= SDLK_l;
			static const SDLKey KEY_NEXT_LAYER		= SDLK_QUOTE;
			static const SDLKey KEY_PREV_LAYER		= SDLK_SEMICOLON;
			static const SDLKey KEY_EDIT_ITEM_SET	= SDLK_F5;
			static const SDLKey KEY_PLOT_ITEM		= SDLK_w;
			static const SDLKey KEY_PLOT_CHEST		= SDLK_LEFTBRACKET;
			static const SDLKey KEY_EDIT_VEHICLE_OBJECT_SET	= SDLK_RIGHTBRACKET;
			static const SDLKey KEY_PLOT_VEHICLE_OBJECT		= SDLK_SLASH;
			static const SDLKey KEY_PLOT_TRANSPORT	= SDLK_t;
			static const SDLKey KEY_EDIT_KEYS		= SDLK_BACKSLASH;
			static const SDLKey KEY_PLOT_PLAYER		= SDLK_z;
			static const SDLKey KEY_BUTTON_0		= SDLK_1;
			static const SDLKey KEY_BUTTON_1		= SDLK_2;
			static const SDLKey KEY_BUTTON_2		= SDLK_3;
			static const SDLKey KEY_BUTTON_3		= SDLK_4;
			static const SDLKey KEY_BUTTON_4		= SDLK_5;
			static const SDLKey KEY_BUTTON_5		= SDLK_6;
			static const SDLKey KEY_BUTTON_6		= SDLK_7;
			static const SDLKey KEY_BUTTON_7		= SDLK_8;
			static const SDLKey KEY_BUTTON_8		= SDLK_9;
			static const SDLKey KEY_BUTTON_9		= SDLK_0;
			static const SDLKey KEY_BUTTON_10		= SDLK_MINUS;
			static const SDLKey KEY_BUTTON_11		= SDLK_EQUALS;
			static const SDLKey KEY_MAIN_MENU		= SDLK_BACKQUOTE;
			static const SDLKey KEY_PLOT_SPAWNER	= SDLK_n;
		//Control +
			static const SDLKey KEY_MOVESCRN_NORTH	= SDLK_UP;
			static const SDLKey KEY_MOVESCRN_NORTH2	= SDLK_KP8;
			static const SDLKey KEY_MOVESCRN_SOUTH	= SDLK_DOWN;
			static const SDLKey KEY_MOVESCRN_SOUTH2	= SDLK_KP2;
			static const SDLKey KEY_MOVESCRN_WEST	= SDLK_LEFT;
			static const SDLKey KEY_MOVESCRN_WEST2	= SDLK_KP4;
			static const SDLKey KEY_MOVESCRN_EAST	= SDLK_RIGHT;
			static const SDLKey KEY_MOVESCRN_EAST2	= SDLK_KP6;
			static const SDLKey KEY_MOVESCRN_NRTHWST= SDLK_KP7;
			static const SDLKey KEY_MOVESCRN_NRTHEST= SDLK_KP9;
			static const SDLKey KEY_MOVESCRN_STHWST	= SDLK_KP1;
			static const SDLKey KEY_MOVESCRN_STHEST	= SDLK_KP3;
			static const SDLKey KEY_PLOT_SQUARE1	= SDLK_1;
			static const SDLKey KEY_PLOT_SQUARE2	= SDLK_2;
			static const SDLKey KEY_PLOT_SQUARE3	= SDLK_3;
			static const SDLKey KEY_PLOT_SQUARE4	= SDLK_4;
			static const SDLKey KEY_PLOT_SQUARE5	= SDLK_5;
			static const SDLKey KEY_PLOT_SQUARE6	= SDLK_6;
			static const SDLKey KEY_PLOT_SQUARE7	= SDLK_7;
			static const SDLKey KEY_PLOT_SQUARE8	= SDLK_8;
			static const SDLKey KEY_PLOT_SQUARE9	= SDLK_9;
			static const SDLKey KEY_EDIT_PLAYER_SET = SDLK_MINUS;
			static const SDLKey KEY_HIGHLIGHT		= SDLK_EQUALS;
			static const SDLKey KEY_MOVETO			= SDLK_BACKQUOTE;
			static const SDLKey KEY_PICK_TERRAIN	= SDLK_SLASH;
	//Button menus:
		enum BUTTONS_MENUS
		{	BUTTONS_MENU_MAIN = 0,
			BUTTONS_MENU_MAP_OPTIONS,
			BUTTONS_MENU_TERRAINS,
			BUTTONS_MENU_ITEMS,
			BUTTONS_MENU_MONSTERS,
			BUTTONS_MENU_VEHICLES,
			BUTTONS_MENU_SCRIPTS,
			BUTTONS_MENU_TRANSPORTS,
			BUTTONS_MENU_DECORATIONS,
			BUTTONS_MENU_VIEWS,
		};		
		enum MENU_MAIN
		{	MAIN_MAP_OPTIONS = 0,
			MAIN_TERRAINS,
			MAIN_ITEMS,
			MAIN_MONSTERS,
			MAIN_VEHICLES,
			MAIN_SCRIPTING,
			MAIN_TRANSPORTS,
			MAIN_DECORATIONS,
			MAIN_USER_CONFIG,
			MAIN_PLAYER_SET,
			MAIN_ROUTING,
			MAIN_SPECIAL_VIEWS
		};
		enum MENU_MAP_OPTIONS
		{	MAP_OPTIONS_SAVE = 0,
			MAP_OPTIONS_LOAD,
			MAP_OPTIONS_SWITCH,
			MAP_OPTIONS_SWITCH_BATTLE,
			MAP_OPTIONS_CLEAR,
			MAP_OPTIONS_INFORMATION,
			MAP_OPTIONS_GLOBAL_INFORMATION,
			MAP_OPTIONS_MOVE_TO,
			MAP_OPTIONS_PREV_LAYER,
			MAP_OPTIONS_NEXT_LAYER,
			MAP_OPTIONS_HELP,
			MAP_OPTIONS_ABOUT
		};
		enum MENU_TERRAINS
		{	TERRAINS_EDIT_SET = 0,
			TERRAINS_PICK
		};
		enum MENU_ITEMS
		{	ITEMS_EDIT_SET = 0,
			ITEMS_PLACE,
			ITEMS_TEMPLATE_CHEST,
			ITEMS_TEMPLATE_BARREL,
			ITEMS_TEMPLATE_SACK,
			ITEMS_TEMPLATE_DRAWERS
		};
		enum MENU_MONSTERS
		{	MONSTERS_EDIT_SET = 0,
			MONSTERS_KEYS,
			MONSTERS_PLACE
		};
		enum MENU_DECORATIONS
		{	DECORATIONS_CHAIR = 0,
			DECORATIONS_TABLE,
			DECORATIONS_CANDLES,
			DECORATIONS_BED_W,
			DECORATIONS_BED_E,
			DECORATIONS_TOMB,
			DECORATIONS_FOUNTAIN,
			DECORATIONS_SIGN,
			DECORATIONS_CORPSE
		};
		enum MENU_VEHICLES
		{	VEHICLES_EDIT_SET = 0,
			VEHICLES_EDIT_OBJECTS_SET,
			VEHICLES_KEYS,
			VEHICLES_PLACE
		};
		enum MENU_SCRIPTS
		{	SCRIPTS_LOCAL_CLASSES = 0,
			SCRIPTS_GLOBAL_CLASSES,
			SCRIPTS_GLOBAL_SCRIPT,
			SCRIPTS_PLACE
		};
		enum MENU_TRANSPORTS
		{	TRANSPORTS_TEMPLATE_STAIRS_UP = 0,
			TRANSPORTS_TEMPLATE_STAIRS_DOWN,
			TRANSPORTS_TEMPLATE_LADDER_UP,
			TRANSPORTS_TEMPLATE_LADDER_DOWN,
			TRANSPORTS_TEMPLATE_VILLAGE
		};
		enum MENU_VIEWS
		{	VIEWS_GEM_VIEW = 0,
			VIEWS_HIGHLIGHT,
			VIEWS_HELP,
			VIEWS_JOT_NOTES
		};

	//Vars
		ASFC_Matrix<bool> lNoLight;
		ASFC_Surface	myoLogo;
		ASFC_Input		myoInput;
		ASFC_Timer		myoTimer;
		LL_Game*		mypoGame;
		MAPEDIT_STATE	myiCurrentState;
		int				myiSelectedTerrain;
		bool			myfPenDown;
		int				myiCursorSpeed;
		int				iCopyX, iCopyY, iCopySpawner;
		bool			myfRouteEditting;
		bool			myfLayingArea;
		int				myiAreaStartX, myiAreaStartY;
		int				myiCursorLayer;
		bool			myfBattleEdit;
		int				myiBattleEdgeX1, myiBattleEdgeX2, myiBattleEdgeY1, myiBattleEdgeY2;
		LEDIT_TerrainSetEditor*	mypoTerrainSetEditor;
		LEDIT_MapInfoEditor*	mypoMapInfoEditor;
		LEDIT_GlobalInfoEditor* mypoGlobalInfoEditor;
		LEDIT_MapSetEditor*		mypoMapSetEditor;
		LEDIT_VehicleSetEditor*	mypoVehicleSetEditor;
		LL_Help*				mypoHelp;
		LEDIT_ClassSetEditor*	mypoClassSetEditor;
		LEDIT_GlobalScriptEditor*	mypoGlobalScriptEditor;
		LEDIT_MapObjectEditor*		mypoMapObjectEditor;
		LEDIT_ScriptedUnitEditor*	mypoScriptedUnitEditor;
		LEDIT_MapObjectRemover*		mypoMapObjectRemover;
		LEDIT_MonsterSetEditor*		mypoMonsterSetEditor;
		LEDIT_PlayerSetEditor*		mypoPlayerSetEditor;
		LEDIT_RouteEditor*			mypoRouteEditor;
		LEDIT_ItemSetEditor*		mypoItemSetEditor;
		LEDIT_ChestEditor*			mypoChestEditor;
		LEDIT_TransportEditor*		mypoTransportEditor;
		LEDIT_VehicleBattleKeyEditor*	mypoKeyEditor;
		LEDIT_VehicleObjectEditor*		mypoVehicleObjectEditor;
		LEDIT_VehicleObjectSetEditor*	mypoVehiclObjectSetEditor;
		LEDIT_ButtonsStrip*				mypoButtonsStrip;
		LEDIT_SpawnerEditor*			mypoSpawnerEditor;
		LEDIT_GraphicsList*				mypoGraphicsList;
		LL_PathNodes*					mypoPathNodes;
		bool						myfHighlightUnits;
		bool						myfUpdateButtons;
		ASFC_Effects				myoEffects;
};

#endif
