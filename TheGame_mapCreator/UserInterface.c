#include "UserInterface.h"
#include "CommonDefinitions.h"
#include "DrawingFunctions.h"
//#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
//#include <iostream.h>


int disp_refresh_counter = 0;

void _RefreshDisplay(SDL_Window *window, SDL_Surface *gui_pics_surface) {

	SDL_Surface *object_surface = NULL;

	int i;

	// get the window surface to set surface size
	object_surface = SDL_GetWindowSurface(window);
	if (object_surface == NULL)
		printf("Error SDL_GetWindowSurface.\n");

	// fill the surface with black
	SDL_FillRect(object_surface, NULL, DISPLAY_BACKGROUD_COLOR);

	for (i = MAX_OBJECTS_LIMIT - 1; i > 0; i--) {

		AddObjectToSurface(&ObjectsArray[i], object_surface, gui_pics_surface);

	}

	SDL_UpdateWindowSurface(window);

	SDL_FreeSurface(object_surface);
	object_surface = NULL;
}

void DisplayPalette(SDL_Window *window, SDL_Surface *gui_pics_surface)
{
	SDL_Surface *object_surface = NULL;

	int i;

	// get the window surface to set surface size
	object_surface = SDL_GetWindowSurface(window);
	if (object_surface == NULL)
		printf("Error SDL_GetWindowSurface.\n");

	for (i = 0; i < PALETTE_SIZE; i++) {

		AddObjectToSurface(&ObjectsPalette[i], object_surface, gui_pics_surface);

	}

	AddObjectToSurface(&ChoosenObject, object_surface, gui_pics_surface);

	SDL_UpdateWindowSurface(window);

	SDL_FreeSurface(object_surface);
	object_surface = NULL;
}

void DisplaySaveButton(SDL_Window *window, int row, int col, TTF_Font* font)
{
	SDL_Surface *surface = NULL;
	SDL_Rect pos;
	pos.x = OBJECT_SIZE*col + 4;
	pos.y = OBJECT_SIZE*row + 10;
	pos.w = pos.h = OBJECT_SIZE;

	// get the window surface to set surface size
	surface = SDL_GetWindowSurface(window);
	if (surface == NULL)
		printf("Error SDL_GetWindowSurface.\n");

	static SDL_Color color_white = { 255, 255, 255 };
	char* label = "SAVE";
	SDL_Surface *text = TTF_RenderText_Solid(font, label, color_white);

	SDL_BlitSurface(text, NULL, surface, &pos);

	SDL_UpdateWindowSurface(window);

	SDL_FreeSurface(surface);
	surface = NULL;
}

void DisplayDownpanel(SDL_Window *window, char* mapName, int nr_Objects, TTF_Font* font)
{
	static SDL_Color color_white = { 255, 255, 255 };
	static SDL_Color color_red = { 255, 0, 0 };

	SDL_Surface *surface = NULL;
	SDL_Surface *text = NULL;
	SDL_Rect pos;
	pos.y = IMAGE_SIZE_H + 10;
	char* label[MAX_LEVEL_NAME_CHARS + 10];

	// get the window surface to set surface size
	surface = SDL_GetWindowSurface(window);
	if (surface == NULL)
		printf("Error SDL_GetWindowSurface.\n");

	// display map name
	sprintf_s(label, 30, "Map name: %s", mapName);
	text = TTF_RenderText_Solid(font, label, (downpanel_selected ? color_red : color_white));
	pos.x = 10;
	pos.w = text->clip_rect.w;
	pos.h = text->clip_rect.h;
	SDL_BlitSurface(text, NULL, surface, &pos);
	
	// display map size
	sprintf_s(label, 30, "Total objects: %d", nr_Objects);
	text = TTF_RenderText_Solid(font, label, color_white);
	pos.x = 320;
	pos.w = text->clip_rect.w;
	pos.h = text->clip_rect.h;
	SDL_BlitSurface(text, NULL, surface, &pos);




	SDL_UpdateWindowSurface(window);
	SDL_FreeSurface(surface);
	surface = NULL;
}

void DisplayGrid(SDL_Window* window, int size)
{
	SDL_Surface *surface = NULL;

	// get the window surface to set surface size
	surface = SDL_GetWindowSurface(window);
	if (surface == NULL)
		printf("Error SDL_GetWindowSurface.\n");

	//horizontal downpanel line
	drawBoldLine(surface, 0, WINDOW_SIZE_H - OBJECT_SIZE, WINDOW_SIZE_W, WINDOW_SIZE_H - OBJECT_SIZE, size, WHITE_RGB);
	//vertical palette line
	drawBoldLine(surface, WINDOW_SIZE_W - OBJECT_SIZE, 0, WINDOW_SIZE_W - OBJECT_SIZE, WINDOW_SIZE_H, size, WHITE_RGB);
	//vertical save button line
	drawBoldLine(surface, WINDOW_SIZE_W - 2 * OBJECT_SIZE, WINDOW_SIZE_H - OBJECT_SIZE, WINDOW_SIZE_W - 2*OBJECT_SIZE, WINDOW_SIZE_H, size, WHITE_RGB);
	
	//lines around the window
	drawBoldLine(surface, 0, 0, WINDOW_SIZE_W, 0, size, WHITE_RGB);
	drawBoldLine(surface, WINDOW_SIZE_W, 0, WINDOW_SIZE_W, WINDOW_SIZE_H, size, WHITE_RGB);
	drawBoldLine(surface, WINDOW_SIZE_W, WINDOW_SIZE_H, 0, WINDOW_SIZE_H, size, WHITE_RGB);
	drawBoldLine(surface, 0, WINDOW_SIZE_H, 0, 0, size, WHITE_RGB);

	SDL_UpdateWindowSurface(window);

	SDL_FreeSurface(surface);
	surface = NULL;
}

bool AddObjectToSurface(struct Object* object_ptr, SDL_Surface* surface, SDL_Surface *picture_form) {

	SDL_Rect blit_rect;
	SDL_Rect render_rect;

	/* clip the object type to the displayed surface */
	// set the posiiton of picture to be cliped out
	if (object_ptr->is_alive)
	{
		blit_rect.x = OBJECT_SIZE * ((int)object_ptr->object_type - 1); // ObjectType


		blit_rect.y = OBJECT_SIZE * ((int)object_type - 1); // ObjectCategory object_type
		blit_rect.h = blit_rect.w = OBJECT_SIZE;

		// if there is redirector, clip pics from redirector category
		if (object_ptr->object_type == redirector)
		{
			blit_rect.x = OBJECT_SIZE * ((int)object_ptr->redirect - 1); // direction
			blit_rect.y = OBJECT_SIZE * ((int)redirector_dir - 1); // ObjectCategory redirector_dir
		}

		// set the position of the object within displayed surface
		render_rect.x = OBJECT_SIZE * object_ptr->position_col;
		render_rect.y = OBJECT_SIZE * object_ptr->position_row;
		render_rect.h = render_rect.w = OBJECT_SIZE;

		// blit to the surface
		SDL_BlitScaled(picture_form, &blit_rect, surface, &render_rect);


		/* clip sharpness to the displayed surface */
		// set the position of picture to be cliped out
		if (object_ptr->sharpness_up) {
			blit_rect.x = OBJECT_SIZE * ((int)dir_up - 1); // sharpness direction
			blit_rect.y = OBJECT_SIZE * ((int)sharpness - 1); // ObjectCategory sharpness
			blit_rect.h = SHARPNESS_H;
			blit_rect.w = SHARPNESS_W;

			// set the position of the object within displayed surface
			render_rect.x = OBJECT_SIZE * object_ptr->position_col + SHARPNESS_OFFSET1;
			render_rect.y = OBJECT_SIZE * object_ptr->position_row + SHARPNESS_OFFSET0;
			render_rect.h = SHARPNESS_H;
			render_rect.w = SHARPNESS_W;

			// blit to the surface
			SDL_BlitScaled(picture_form, &blit_rect, surface, &render_rect);
		}
		if (object_ptr->sharpness_down) {
			blit_rect.x = OBJECT_SIZE * ((int)dir_down - 1); // sharpness direction
			blit_rect.y = OBJECT_SIZE * ((int)sharpness - 1); // ObjectCategory sharpness
			blit_rect.h = SHARPNESS_H;
			blit_rect.w = SHARPNESS_W;

			// set the position of the object within displayed surface
			render_rect.x = OBJECT_SIZE * object_ptr->position_col + SHARPNESS_OFFSET1;
			render_rect.y = OBJECT_SIZE * object_ptr->position_row + SHARPNESS_OFFSET2;
			render_rect.h = SHARPNESS_H;
			render_rect.w = SHARPNESS_W;

			// blit to the surface
			SDL_BlitScaled(picture_form, &blit_rect, surface, &render_rect);
		}
		if (object_ptr->sharpness_left) {
			blit_rect.x = OBJECT_SIZE * ((int)dir_left - 1); // sharpness direction
			blit_rect.y = OBJECT_SIZE * ((int)sharpness - 1); // ObjectCategory sharpness
			blit_rect.h = SHARPNESS_W;
			blit_rect.w = SHARPNESS_H;

			// set the position of the object within displayed surface
			render_rect.x = OBJECT_SIZE * object_ptr->position_col + SHARPNESS_OFFSET0;
			render_rect.y = OBJECT_SIZE * object_ptr->position_row + SHARPNESS_OFFSET1;
			// size of rotated sharpness switched
			render_rect.h = SHARPNESS_W;
			render_rect.w = SHARPNESS_H;

			// blit to the surface
			SDL_BlitScaled(picture_form, &blit_rect, surface, &render_rect);
		}
		if (object_ptr->sharpness_right) {
			blit_rect.x = OBJECT_SIZE * ((int)dir_right - 1); // sharpness direction
			blit_rect.y = OBJECT_SIZE * ((int)sharpness - 1); // ObjectCategory sharpness
			blit_rect.h = SHARPNESS_W;
			blit_rect.w = SHARPNESS_H;

			// set the position of the object within displayed surface
			render_rect.x = OBJECT_SIZE * object_ptr->position_col + SHARPNESS_OFFSET2;
			render_rect.y = OBJECT_SIZE * object_ptr->position_row + SHARPNESS_OFFSET1;
			// size of rotated sharpness switched
			render_rect.h = SHARPNESS_W;
			render_rect.w = SHARPNESS_H;

			// blit to the surface
			SDL_BlitScaled(picture_form, &blit_rect, surface, &render_rect);
		}

		if (object_ptr->countdown >= 0) {
			blit_rect.x = OBJECT_SIZE * object_ptr->countdown; // countdown
			blit_rect.y = OBJECT_SIZE * ((int)countdown_number - 1); // ObjectCategory countdown_number
			blit_rect.h = COUNTDOWN_H;
			blit_rect.w = COUNTDOWN_W;

			// set the position of the object within displayed surface
			render_rect.x = OBJECT_SIZE * object_ptr->position_col + COUNTDOWN_OFFSET_X;
			render_rect.y = OBJECT_SIZE * object_ptr->position_row + COUNTDOWN_OFFSET_Y;
			render_rect.h = COUNTDOWN_H;
			render_rect.w = COUNTDOWN_W;

			// blit to the surface
			SDL_BlitScaled(picture_form, &blit_rect, surface, &render_rect);
		}
	}
		

	if (surface == NULL) {
		printf("Error bliting object_surface.\n");
		return false;
	}

	return true;
}


bool WaitForKeyboardInput(char* output_ptr) {

	char ch = 0;

	do {
		if (_kbhit()) {
			ch = _getch();
		}
	} while (ch == 0);

	*output_ptr = ch;

	return true;
}

userInput _GetMovement(Direction* direction_ptr, GameStatus* status_ptr, SDL_Event* ev) {

	if ((direction_ptr == NULL) || (status_ptr == NULL)) {
		printf("[ERROR] GetMovement(): NULL pointer input.");
		return error;
	}

	//SDL_Event ev;

	bool keyPressed = false;

	// wait for keyboard input
	while (!keyPressed)
	{
		// wait for input to be analyzed
		while (SDL_PollEvent(ev) != 0)
		{
			// analyze the input
			if (ev->type == SDL_KEYDOWN) // some key was pressed - pushed down
			{
				// check which key was it
				DebugPrint("Key pressed: ");
				switch (ev->key.keysym.sym)
				{
				case SDLK_UP:
					DebugPrint("up\n");
					*direction_ptr = dir_up;
					break;

				case SDLK_DOWN:
					DebugPrint("down\n");
					*direction_ptr = dir_down;
					break;

				case SDLK_LEFT:
					DebugPrint("left\n");
					*direction_ptr = dir_left;
					break;

				case SDLK_RIGHT:
					DebugPrint("right\n");
					*direction_ptr = dir_right;
					break;

				case SDLK_ESCAPE:
					DebugPrint("ESC\n");
					return menu;

				default:
					DebugPrint("undefined\n");
					*direction_ptr = no_direction;
					break;
				}
				keyPressed = true;
			}
		}
	}


	*status_ptr = game_in_progress;

	if (DEBUG_ENABLE) printf("Direction: %i\n", *direction_ptr);

	return gamePlay;
}


char* Dir2Str(Direction integer) {
	if (integer == dir_up) return "dir_up";
	else if (integer == dir_down) return "dir_down";
	else if (integer == dir_left) return "dir_left";
	else if (integer == dir_right) return "dir_right";
	else if (integer == no_direction) return "no_direction";

	return "unknown";
}

char* Int2Str(int integer)
{
	char* str[4];
	sprintf_s(str, 4, "%d", integer);
	return str;
}