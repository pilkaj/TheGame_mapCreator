#pragma once

#include <stdbool.h>

/************ HEADER *************/
#define PROGRAM_NAME "TheGame"
#define AUTHOR       "jakub"
#define VERSION      "ver0.9"
/*********************************/

/*************************************************************/
/* ver0.2 updates                                            */
/*  game engine modified.                                    */
/*  Different dynamics                                       */
/*  Able to do basic movement including obstacle recognition */
/*                                                           */
/* ver0.3 updates                                            */
/*  basic game engine is fully functional:
- movement
- collision detection
- explosion
- destruction
- bricks connection
- special properties of all objects                     */
/*  Does not include goal positions for the solid            */
/*  Does not include box object                              */

/*  ver0.4 - rejected                                        */

/*  ver0.5_graphical - rejected                              */

/*  ver0.6_graphical                                         */
/*  Updates:                                                 */
/*   UserInterface.c/.h:                                     */
/*     includes new graphical functions using SDL libraries  */
/*      _GetMovement()                                       */
/*      _RefreshDisplay()                                    */
/*   CommonDefinitions.h:                                    */
/*      enumeration ObjectCategory                           */
/*   main.c:                                                 */

/*  ver0.7_graphical                                         */
/*   Updates:                                                */
/*    added countdow, sharpness                              */
/*    goal positions added, end of game                      */

/*  ver0.8_graphical                                         */
/*   Updates:                                                */
/*    user menu created                                      */
/*    new functionalities: box and redirector                */

/*  ver0.9_graphical                                         */
/*************************************************************/

#define DEBUG_ENABLE    true
#define DebugPrint      if(DEBUG_ENABLE) printf

/* Game field definitions */
#define GAME_FIELD_SIZE_ROWS		10
#define GAME_FIELD_SIZE_COLUMNS		14
#define OBJECT_SIZE					40
#define GAME_FIELD_SIZE_W			GAME_FIELD_SIZE_COLS*OBJECT_SIZE
#define GAME_FIELD_SIZE_H			GAME_FIELD_SIZE_ROWS*OBJECT_SIZE

#define WINDOW_SIZE_W				(GAME_FIELD_SIZE_COLUMNS+1)*OBJECT_SIZE
#define WINDOW_SIZE_H				(GAME_FIELD_SIZE_ROWS+1)*OBJECT_SIZE
#define PALETTE_POSITION_COL		GAME_FIELD_SIZE_COLUMNS
#define DOWNPANEL_POSITION_ROW		GAME_FIELD_SIZE_ROWS
#define PALETTE_SIZE				10
#define COUNTDOWN_LIMIT				7

// Static objects
#define EMPTY           ' '
#define WALL			   '#'
#define WALL_SHARP_DN	'v'
#define WALL_SHARP_UP	'^'
#define WALL_SHARP_L	   '<'
#define WALL_SHARP_R	   '>'
#define GOAL_FIELD		'@'
#define MINE 		      'A'
#define WALL_TMP		   'a'
#define QUESTION_MARK	'?'
#define DEAD_OBJECT			'X'

// Dynamic objects
#define PLAYER          '$'
#define BRICK           '&'
#define BOX             'X'

// movement
#define MOVE_UP			72
#define MOVE_DOWN		   80
#define MOVE_LEFT		   75
#define MOVE_RIGHT		77
#define NO_MOVEMENT     0

// Coding definitions
#define ROW						0
#define COLUMN					1
//#define NULL					0
#define UNDEFINED				65535
#define MAX_OBJECTS_LIMIT		GAME_FIELD_SIZE_ROWS*GAME_FIELD_SIZE_COLUMNS
#define MAX_LEVEL_NAME_CHARS	30
#define GAME_REFRESH_DELAY		50    /* in ms */

typedef enum ObjectType {
	empty,
	player,
	brick,
	wall,
	wall_tmp,
	mine,
	surprise,
	box,
	goal,
	explosion,
	redirector,
	undefined
} ObjectType;

typedef enum ObjectCategory {
	no_category,
	object_type,
	countdown_number,
	sharpness,
	redirector_dir
} ObjectCategory;

typedef enum Direction {
	no_direction,
	dir_up,
	dir_down,
	dir_left,
	dir_right
} Direction;

typedef enum Action {
	no_action,
	decrease,
	destroy,
	destroy_itself,
	give_movement,
	join,
	reveal_surprise
} Action;

typedef enum GameStatus {
	game_in_progress,
	game_waiting,
	game_finished
} GameStatus;

struct Object {
	ObjectType object_type;// = undefined;

						   /* current state */
	int position_row;// = UNDEFINED;
	int position_col;// = UNDEFINED;
	bool is_alive;// = false

				  /* next state */
				  /* position vars */
	int next_position_row;// = UNDEFINED;
	int next_position_col;// = UNDEFINED;
						  /* action vars */
	bool move_permission;// = false;
	Action action;// = no_action;
	bool will_be_alive;// = false;
	Direction next_direction;// = no_direction

							 /* special object properties */
	int countdown;// = -1;
	bool sharpness_up;// = false;
	bool sharpness_down;// = false;
	bool sharpness_left;// = false;
	bool sharpness_right;// = false;
	ObjectType surprise;// = undefined

	Direction redirect;// = no_direction

					   /* object connections */
	struct Object* joint_up;// = NULL;
	struct Object* joint_down;// = NULL;
	struct Object* joint_left;// = NULL;
	struct Object* joint_right;// = NULL;

							   /* end game */
							   /* this is applicable only for objects having object_type either brick, player or goal. For other this shall be NULL. */
							   /* If goal object is overlayed by brick or player, variable contains its pointer and vice versa, brick(player) contains goal's pointer. */
	struct Object* goal_object;// = NULL;
};

struct LevelHeader
{
	char	levelName[MAX_LEVEL_NAME_CHARS];
	int		levelBestTime;
};

// Global variables
extern struct Object ObjectsArray[MAX_OBJECTS_LIMIT];
extern struct Object ObjectsPalette[PALETTE_SIZE];
extern struct Object ChoosenObject;
extern struct LevelHeader Level;
extern bool downpanel_selected;
/* gameField_CharType - used to update game field into Console output */
//extern char gameField_CharType[GAME_FIELD_SIZE_ROWS][GAME_FIELD_SIZE_COLUMNS];

/* gameField_ObjectType - main game field */
extern struct Object* gameField_ObjectType[GAME_FIELD_SIZE_ROWS][GAME_FIELD_SIZE_COLUMNS];

extern struct Object* ObjectsJoined_list[MAX_OBJECTS_LIMIT];
