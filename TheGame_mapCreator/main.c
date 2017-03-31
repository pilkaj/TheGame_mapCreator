/**/
/* 28.3.2017 - bug resolved - remove object functionality works */
/*           - count down forgiven for player object */
/**/
/**/
/**/
/**/



#include "CommonDefinitions.h"
#include <stdio.h>
#include <SDL.h>
#include "UserInterface.h"
#include <memory.h>
#include "DrawingFunctions.h"
#include <string.h>

#define FILE_NAME		"levels.txt"

// write file definitions
#define LEVEL_IDENTIFIER		"#\0"
#define LEVEL_FOOTER			"&\0"
#define OBJECT_SEPARATOR		"|\0"
#define ATTRIBUTE_SEPARATOR		",\0"
#define FIRST_OBJECT_IN_ARRAY   1

int pushObject_cnt = FIRST_OBJECT_IN_ARRAY; // stupid design. first object must be empty for TheGame
bool downpanel_selected = false;

struct Object ObjectsArray[MAX_OBJECTS_LIMIT];
//struct Object ObjectsArray[MAX_OBJECTS_LIMIT] = {
//	empty,        UNDEFINED, UNDEFINED, false, UNDEFINED, UNDEFINED, false, no_action, false, -1, false, false, false, false, undefined, NULL, NULL, NULL, NULL, NULL,
//	player,           5, 5, true, UNDEFINED, UNDEFINED, false, no_action, false, -1, false, false, false, false, undefined, NULL, NULL, NULL, NULL, NULL,
//	brick,            5, 4, true, UNDEFINED, UNDEFINED, false, no_action, false, -1, false, false, false, false, undefined, NULL, NULL, NULL, NULL, NULL,
//	brick,            1, 5, true, UNDEFINED, UNDEFINED, false, no_action, false, -1, false, false, false, false, undefined, NULL, NULL, NULL, NULL, NULL,
//	wall_tmp,         1, 12, true, UNDEFINED, UNDEFINED, false, no_action, false,  2, false, true, false, false, undefined, NULL, NULL, NULL, NULL, NULL,
//	mine,             4, 1, true, UNDEFINED, UNDEFINED, false, no_action, false,  3, false, false, false, false, undefined, NULL, NULL, NULL, NULL, NULL,
//	surprise,         5, 1, true, UNDEFINED, UNDEFINED, false, no_action, false, -1, false, false, false, false, brick, NULL, NULL, NULL, NULL, NULL,
//	/* UpperLeft corner */
//	wall,             0, 0, true, UNDEFINED, UNDEFINED, false, no_action, true, -1, false, false, false, false, undefined, NULL, NULL, NULL, NULL, NULL,
//	wall,             0, 1, true, UNDEFINED, UNDEFINED, false, no_action, true, -1, false, false, false, false, undefined, NULL, NULL, NULL, NULL, NULL,
//	wall,             1, 0, true, UNDEFINED, UNDEFINED, false, no_action, true, -1, false, false, false, true, undefined, NULL, NULL, NULL, NULL, NULL,
//	/* UpperRight corner */
//	wall,             0, GAME_FIELD_SIZE_COLUMNS - 1, true, UNDEFINED, UNDEFINED, false, no_action, true, -1, false, false, false, false, undefined, NULL, NULL, NULL, NULL, NULL,
//	wall,             0, GAME_FIELD_SIZE_COLUMNS - 2, true, UNDEFINED, UNDEFINED, false, no_action, true, -1, false, false, false, false, undefined, NULL, NULL, NULL, NULL, NULL,
//	wall,             1, GAME_FIELD_SIZE_COLUMNS - 1, true, UNDEFINED, UNDEFINED, false, no_action, true, -1, false, false, false, false, undefined, NULL, NULL, NULL, NULL, NULL,
//	/* DownerRight corner */
//	wall,             GAME_FIELD_SIZE_ROWS - 2, GAME_FIELD_SIZE_COLUMNS - 1, true, UNDEFINED, UNDEFINED, false, no_action, true, -1, false, false, false, false, undefined, NULL, NULL, NULL, NULL, NULL,
//	wall,             GAME_FIELD_SIZE_ROWS - 1, GAME_FIELD_SIZE_COLUMNS - 1, true, UNDEFINED, UNDEFINED, false, no_action, true, -1, false, false, false, false, undefined, NULL, NULL, NULL, NULL, NULL,
//	wall,             GAME_FIELD_SIZE_ROWS - 1, GAME_FIELD_SIZE_COLUMNS - 2, true, UNDEFINED, UNDEFINED, false, no_action, true, -1, false, false, false, false, undefined, NULL, NULL, NULL, NULL, NULL,
//	/* DownerLeft corner */
//	wall,             GAME_FIELD_SIZE_ROWS - 1, 1, true, UNDEFINED, UNDEFINED, false, no_action, true, -1, false, false, false, false, undefined, NULL, NULL, NULL, NULL, NULL,
//	wall,             GAME_FIELD_SIZE_ROWS - 1, 0, true, UNDEFINED, UNDEFINED, false, no_action, true, -1, false, false, false, false, undefined, NULL, NULL, NULL, NULL, NULL,
//	wall,             GAME_FIELD_SIZE_ROWS - 2, 0, true, UNDEFINED, UNDEFINED, false, no_action, true, -1, false, false, false, true, undefined, NULL, NULL, NULL, NULL, NULL,
//};

struct Object ObjectsPalette[PALETTE_SIZE] = {
	player,		0, PALETTE_POSITION_COL, true, UNDEFINED, UNDEFINED, false, no_action, true, no_direction, -1, false, false, false, false, undefined, no_direction, NULL, NULL, NULL, NULL, NULL,
	brick,		1, PALETTE_POSITION_COL, true, UNDEFINED, UNDEFINED, false, no_action, true, no_direction, -1, false, false, false, false, undefined, no_direction, NULL, NULL, NULL, NULL, NULL,
	wall,		2, PALETTE_POSITION_COL, true, UNDEFINED, UNDEFINED, false, no_action, true, no_direction, -1, false, false, false, false, undefined, no_direction, NULL, NULL, NULL, NULL, NULL,
	wall_tmp,	3, PALETTE_POSITION_COL, true, UNDEFINED, UNDEFINED, false, no_action, true, no_direction, -1, false, false, false, false, undefined, no_direction, NULL, NULL, NULL, NULL, NULL,
	mine,		4, PALETTE_POSITION_COL, true, UNDEFINED, UNDEFINED, false, no_action, true, no_direction, -1, false, false, false, false, undefined, no_direction, NULL, NULL, NULL, NULL, NULL,
	surprise,	5, PALETTE_POSITION_COL, true, UNDEFINED, UNDEFINED, false, no_action, true, no_direction, -1, false, false, false, false, undefined, no_direction, NULL, NULL, NULL, NULL, NULL,
	box,		6, PALETTE_POSITION_COL, true, UNDEFINED, UNDEFINED, false, no_action, true, no_direction, -1, false, false, false, false, undefined, no_direction, NULL, NULL, NULL, NULL, NULL,
	goal,		7, PALETTE_POSITION_COL, true, UNDEFINED, UNDEFINED, false, no_action, true, no_direction, -1, false, false, false, false, undefined, no_direction, NULL, NULL, NULL, NULL, NULL,
	redirector,	8, PALETTE_POSITION_COL, true, UNDEFINED, UNDEFINED, false, no_action, true, no_direction, -1, false, false, false, false, undefined, dir_left, NULL, NULL, NULL, NULL, NULL,
	empty,		9, PALETTE_POSITION_COL, false, UNDEFINED, UNDEFINED, false, no_action, false, no_direction, -1, false, false, false, false, undefined, no_direction, NULL, NULL, NULL, NULL, NULL,
};

struct Object ChoosenObject = { player, 10, PALETTE_POSITION_COL, true, UNDEFINED, UNDEFINED, false, no_action, true, no_direction, -1, false, false, false, false, undefined, no_direction, NULL, NULL, NULL, NULL, NULL };

struct LevelHeader Level = {"jakubko", 65535};



void Init_ObjectsArray();
int TakeAction(SDL_Event *ev);
int SaveTheMap(char* mapName, char* fileName);
int InsertObjectToMap(int pos_x, int pos_y);
int WriteLevelHeaderToFile(char* levelName, int levelTime, FILE *file_ptr);
int WriteObjectToFile(struct Object *object_ptr, FILE *file_ptr);
int WriteAttributeToFile(int attribute, FILE *file_ptr);
int WriteIntToFile(int integer, FILE *file_ptr);
int WriteToFile(char* string, FILE *file_ptr);
int SelectObject(struct Object *object_ptr);
int pushSelectedObject(int row, int col);
int insertSelectedObject(struct Object *object_ptr);
int removeObject(int object_number);
int ModifySharpness(bool *sharpness_ptr);
int ModifyCountdown(int *countdown_ptr);
int GetObjectsArrayRepletion(struct Object* objectArray_ptr);

int main()
{
	SDL_Event ev;
	SDL_Window *main_window = NULL;
	SDL_Surface *gui_pics_surface = NULL;
	TTF_Font *font = NULL;

	Init_ObjectsArray();

	int is_map_saved = 0;

	if (SDL_Init(SDL_INIT_VIDEO) == -1 || TTF_Init() == -1)
		printf("Error initialising SDL or TTF.\n");

	main_window = SDL_CreateWindow("Main Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_SIZE_W, WINDOW_SIZE_H, SDL_WINDOW_SHOWN);
	if (main_window == NULL)
		printf("Error creating main window.\n");

	gui_pics_surface = SDL_LoadBMP("gui_pics_black.bmp");
	if (gui_pics_surface == NULL)
		printf("Error in loading .bmp image.\n");

	font = TTF_OpenFont("OpenSans-Regular.ttf", 14);
	if (font == NULL) {
		printf("Error in loading .ttf font: %s\n", TTF_GetError());
	}

	while(is_map_saved == 0)
	{
		_RefreshDisplay(main_window, gui_pics_surface);
		DisplayPalette(main_window, gui_pics_surface);
		DisplaySaveButton(main_window, GAME_FIELD_SIZE_ROWS, GAME_FIELD_SIZE_COLUMNS-1, font);
		DisplayDownpanel(main_window, Level.levelName, GetObjectsArrayRepletion(ObjectsArray), font);
		DisplayGrid(main_window, 1);
		is_map_saved = TakeAction(&ev);
	}

	return 0;
}

void Init_ObjectsArray()
{
	for (int i = 0; i < MAX_OBJECTS_LIMIT; i++)
	{
		ObjectsArray[i].position_row = UNDEFINED;
		ObjectsArray[i].position_col = UNDEFINED;
	}
}

int TakeAction(SDL_Event *ev)
{
	int row, col;
	char character[2] = { '\0', '\0'};
	int pos_in_object_x, pos_in_object_y;

	while(1)
	{
		while (SDL_PollEvent(ev))
		{
			switch(ev->type)
			{
			case SDL_QUIT:
				return 2;
			case SDL_KEYDOWN:
				if (ev->key.keysym.sym == 13)
				{
					downpanel_selected = false;
					return 0;
				}
				if (downpanel_selected)
				{
					character[0] = (char) ev->key.keysym.sym - ((97 <= ev->key.keysym.sym) ? 32 : 0); // write as capital letters
					strcat_s(Level.levelName, MAX_LEVEL_NAME_CHARS, character);
				}
				return 0;

			case SDL_MOUSEBUTTONDOWN:
				row = ev->button.y / OBJECT_SIZE;
				col = ev->button.x / OBJECT_SIZE;

				pos_in_object_x = ev->button.x - col*OBJECT_SIZE;
				pos_in_object_y = ev->button.y - row*OBJECT_SIZE;

				printf("%3d %3d %3d %3d %3d %3d\n", ev->button.x, ev->button.y, col, row, pos_in_object_x, pos_in_object_y);

				// if mouse click within the game field
				if (col < GAME_FIELD_SIZE_COLUMNS && row < GAME_FIELD_SIZE_ROWS)
				{
					InsertObjectToMap(row, col);
				}
				// if mouse click is within the palette
				else if ((col == PALETTE_POSITION_COL) && (row < PALETTE_SIZE))
				{
					// if object already choosen, then attributes of the object may be changed
					if (ObjectsPalette[row].object_type == ChoosenObject.object_type)
					{
						if (ObjectsPalette[row].object_type == redirector)
						{
							if (ObjectsPalette[row].redirect < dir_right)
								ObjectsPalette[row].redirect++;
							else
								ObjectsPalette[row].redirect = dir_up;
						}
						else
						{
							if ((pos_in_object_x < SHARPNESS_H) && (pos_in_object_y > SHARPNESS_OFFSET1) && (pos_in_object_y < SHARPNESS_OFFSET2))
								ModifySharpness(&ObjectsPalette[row].sharpness_left);
							else if ((pos_in_object_x > SHARPNESS_OFFSET2) && (pos_in_object_y > SHARPNESS_OFFSET1) && (pos_in_object_y < SHARPNESS_OFFSET2))
								ModifySharpness(&ObjectsPalette[row].sharpness_right);
							else if ((pos_in_object_x < SHARPNESS_OFFSET2) && (pos_in_object_x > SHARPNESS_OFFSET1) && (pos_in_object_y < SHARPNESS_H))
								ModifySharpness(&ObjectsPalette[row].sharpness_up);
							else if ((pos_in_object_x < SHARPNESS_OFFSET2) && (pos_in_object_x > SHARPNESS_OFFSET1) && (pos_in_object_y > SHARPNESS_OFFSET2))
								ModifySharpness(&ObjectsPalette[row].sharpness_down);

							else if ((pos_in_object_x > COUNTDOWN_OFFSET_X) && (pos_in_object_x < (COUNTDOWN_OFFSET_X + COUNTDOWN_W)) && (pos_in_object_y > COUNTDOWN_OFFSET_Y) && (pos_in_object_y < (COUNTDOWN_OFFSET_Y + COUNTDOWN_H)))
								ModifyCountdown(&ObjectsPalette[row].countdown);
						}
					}
					SelectObject(&ObjectsPalette[row]);
				}
				// if mouse click within the SAVE button
				else if ((col == GAME_FIELD_SIZE_COLUMNS - 1) && (row == GAME_FIELD_SIZE_ROWS))
				{
					SaveTheMap(Level.levelName, FILE_NAME);
					return 1;
				}
				// if mouse click within the downpanel
				else if ((col < GAME_FIELD_SIZE_COLUMNS - 1) && (row == GAME_FIELD_SIZE_ROWS))
				{
					if (!downpanel_selected)
					{
						downpanel_selected = true;
						sprintf_s(Level.levelName, MAX_LEVEL_NAME_CHARS, "");
					}
					else
					{
						downpanel_selected = false;
					}
					return 0;
				}

				return 0;

			default:
				break;
			}
		}
	}
}

int SaveTheMap(char* mapName, char* fileName)
{
	FILE* file_ptr;
	int i = 1; // skip first empty object

	/* Opens for reading and appending. The appending operation includes the removal of 
	the EOF marker before new data is written to the file and the EOF marker is restored 
	after writing is complete. Creates the file if it doesn't exist. */
	fopen_s(&file_ptr, fileName, "a+");

	if (file_ptr == NULL)
	{
		printf("SaveTheMap(): Error openning the file.\n");
		return 1;
	}

	if (WriteLevelHeaderToFile(mapName, -1, file_ptr) == 0)
	{
		while (i < MAX_OBJECTS_LIMIT && ObjectsArray[i].object_type != empty)
		{
			WriteObjectToFile(&ObjectsArray[i++], file_ptr);
		}
		WriteToFile(LEVEL_FOOTER, file_ptr);
	}

	fclose(file_ptr);
	return 0;
}

int WriteLevelHeaderToFile(char* levelName, int levelTime, FILE *file_ptr)
{
	WriteToFile(LEVEL_IDENTIFIER, file_ptr);
	WriteToFile(levelName, file_ptr);
	//WriteToFile(OBJECT_SEPARATOR, file_ptr);
	//WriteIntToFile(levelTime, file_ptr);

	return 0;
}

int WriteObjectToFile(struct Object *object_ptr, FILE *file_ptr)
{
	WriteToFile(OBJECT_SEPARATOR, file_ptr);

	WriteAttributeToFile(object_ptr->object_type, file_ptr);

	WriteAttributeToFile(object_ptr->position_row, file_ptr);
	WriteAttributeToFile(object_ptr->position_col, file_ptr);

	WriteAttributeToFile(object_ptr->is_alive, file_ptr);

	WriteAttributeToFile(object_ptr->next_position_row, file_ptr);
	WriteAttributeToFile(object_ptr->next_position_col, file_ptr);

	WriteAttributeToFile(object_ptr->move_permission, file_ptr);

	WriteAttributeToFile(object_ptr->action, file_ptr);

	WriteAttributeToFile(object_ptr->will_be_alive, file_ptr);

	WriteAttributeToFile(object_ptr->next_direction, file_ptr);

	WriteAttributeToFile(object_ptr->countdown, file_ptr);

	WriteAttributeToFile(object_ptr->sharpness_up, file_ptr);
	WriteAttributeToFile(object_ptr->sharpness_down, file_ptr);
	WriteAttributeToFile(object_ptr->sharpness_left, file_ptr);
	WriteAttributeToFile(object_ptr->sharpness_right, file_ptr);

	WriteAttributeToFile(object_ptr->surprise, file_ptr);

	WriteAttributeToFile(object_ptr->redirect, file_ptr);

	WriteAttributeToFile((int)NULL, file_ptr); // joint_up
	WriteAttributeToFile((int)NULL, file_ptr); // joint_down
	WriteAttributeToFile((int)NULL, file_ptr); // joint_left
	WriteAttributeToFile((int)NULL, file_ptr); // joint_right

	WriteAttributeToFile((int)NULL, file_ptr); // goal_object

	return 0;
}

int WriteAttributeToFile(int attribute, FILE *file_ptr)
{
	WriteToFile(ATTRIBUTE_SEPARATOR, file_ptr);
	WriteIntToFile(attribute, file_ptr);

	return 0;
}

int WriteIntToFile(int integer, FILE *file_ptr)
{
	char attribute_s[20];

	sprintf_s(attribute_s, 20, "%d\0", integer);

	WriteToFile(attribute_s, file_ptr);

	return 0;
}

int WriteToFile(char* string, FILE *file_ptr)
{
	fprintf(file_ptr, "%s", string);

	return 0;
}

int InsertObjectToMap(int pos_row, int pos_col)
{
	int i = FIRST_OBJECT_IN_ARRAY;

	// check whether there is existing object on the input position already
	while ((i < MAX_OBJECTS_LIMIT) && (ObjectsArray[i].object_type != empty))
	{
		if ((ObjectsArray[i].position_row == pos_row) && (ObjectsArray[i].position_col == pos_col))
		{
			if (ChoosenObject.object_type == empty)
				// remove existing object
				removeObject(i);
			else
				// rewrite existing object
				insertSelectedObject(&ObjectsArray[i]);

			return 0;
		}

		i++;
	}

	// insert new object to the end of array
	pushSelectedObject(pos_row, pos_col);

	return 0;
}

int SelectObject(struct Object *object_ptr)
{
	ChoosenObject.object_type = object_ptr->object_type;

	ChoosenObject.countdown = object_ptr->countdown;
	ChoosenObject.sharpness_left = object_ptr->sharpness_left;
	ChoosenObject.sharpness_right = object_ptr->sharpness_right;
	ChoosenObject.sharpness_up = object_ptr->sharpness_up;
	ChoosenObject.sharpness_down = object_ptr->sharpness_down;

	ChoosenObject.surprise = object_ptr->surprise;
	ChoosenObject.redirect = object_ptr->redirect;

	return 0;
}

/*  */
int pushSelectedObject(int row, int col)
{
	if (pushObject_cnt >= MAX_OBJECTS_LIMIT)
	{
		printf("Error: Objects counter %d exceeds MAX_OBJECTS_LIMIT.\n", pushObject_cnt);
		return 1;
	}

	ObjectsArray[pushObject_cnt] = ChoosenObject;
	ObjectsArray[pushObject_cnt].position_row = row;
	ObjectsArray[pushObject_cnt].position_col = col;

	pushObject_cnt++;
	return 0;
}

/* changes attributes of the existing object */
int insertSelectedObject(struct Object *object_ptr)
{
	object_ptr->object_type = ChoosenObject.object_type;

	object_ptr->sharpness_left = ChoosenObject.sharpness_left;
	object_ptr->sharpness_right = ChoosenObject.sharpness_right;
	object_ptr->sharpness_up = ChoosenObject.sharpness_up;
	object_ptr->sharpness_down = ChoosenObject.sharpness_down;

	object_ptr->countdown = ChoosenObject.countdown;

	return 0;
}

int removeObject(int i)
{
	// object on position i replace by next object
	while((i < MAX_OBJECTS_LIMIT - 1) && (ObjectsArray[i].object_type != empty))
	{
		ObjectsArray[i] = ObjectsArray[i + 1];
		i++;
	}

	if (i >= MAX_OBJECTS_LIMIT)
	{
		printf("Error: i >= MAX_OBJECTS_LIMIT.\n");
		return -1;
	}

	/* Warning: Be careful! Last object is untouched. In case of full array, this object will not change. */

	pushObject_cnt--;

	return 0;
}

int ModifySharpness(bool *sharpness_ptr)
{
	if (*sharpness_ptr == true)
		*sharpness_ptr = false;
	else
		*sharpness_ptr = true;

	return 0;
}

int ModifyCountdown(int *countdown_ptr)
{
    if (ChoosenObject.object_type == player)
        return 0;

	if (*countdown_ptr == COUNTDOWN_LIMIT)
		*countdown_ptr = -1;
	else
		(*countdown_ptr)++;

	return 0;
}

int GetObjectsArrayRepletion(struct Object* objectArray_ptr)
{
	int i = 0;
	while (i < MAX_OBJECTS_LIMIT && objectArray_ptr[i+1].object_type != empty)
	{
		i++;
	}

	return i;
}