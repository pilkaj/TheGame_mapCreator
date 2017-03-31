#pragma once

#include "CommonDefinitions.h"
#include <SDL.h>
#include <SDL_ttf.h>

/* other definitions */
#define ARROW_KEY_PUSHED   224

#define COUNTDOWN_W			16
#define COUNTDOWN_H			22
#define COUNTDOWN_OFFSET_X	12
#define COUNTDOWN_OFFSET_Y	9
#define SHARPNESS_W			27
#define SHARPNESS_H			8
#define SHARPNESS_OFFSET0	0
#define SHARPNESS_OFFSET1	6
#define SHARPNESS_OFFSET2	33
#define IMAGE_SIZE_W	(GAME_FIELD_SIZE_COLUMNS)*OBJECT_SIZE
#define IMAGE_SIZE_H	(GAME_FIELD_SIZE_ROWS)*OBJECT_SIZE

#define GREY_RGB	150, 150, 150
#define WHITE_RGB	255, 255, 255

#define DISPLAY_BACKGROUD_COLOR	0x00000000

typedef enum userInput {
	error,
	gamePlay,
	menu
} userInput;

void _RefreshDisplay(SDL_Window *window, SDL_Surface *gui_pics_surface);
void DisplayPalette(SDL_Window *window, SDL_Surface *gui_pics_surface);
void DisplaySaveButton(SDL_Window *window, int row, int col, TTF_Font* font);
void DisplayDownpanel(SDL_Window *window, char* mapName, int nr_Objects, TTF_Font* font);
void DisplayGrid(SDL_Window* window, int size);
bool AddObjectToSurface(struct Object* object_ptr, SDL_Surface* surface, SDL_Surface *picture_form);
userInput _GetMovement(Direction* direction_ptr, GameStatus* status_ptr, SDL_Event* ev);

// Private functions

bool WaitForKeyboardInput(char* output_ptr);
char* Dir2Str(Direction integer);
char* Int2Str(int integer);