#pragma once

#include <string>
#include <vector>
#include <memory>
#include <deque>

#include "COLOR.h"

struct SDL_Texture;


struct UIBOX_CHAR {
	uint8_t chr;
	COLOR col;
	COLOR bg_col = { 0,0,0,1 };
};

struct UIBOX_ELEMENT {
	std::string text;
	std::string over_text;
	bool over = false;
	bool sel = false;
	uint8_t type = 0; // 0 = button, >0 anything else
	bool* input_bool = nullptr;
	uint16_t* input_int = nullptr;
	uint16_t input_int_var = 0;
	bool is_pos = false;
	uint16_t px = 0;
	uint16_t py = 0;
};

struct UIBOX_INFO {
	bool creation_update = true;
	bool update = true;
	bool element_update = true;

	bool can_grab = true;
	bool in_grab = false;
	bool grab = false;

	bool can_shrink = true;
	bool in_shrink = false;
	bool shrink = false;

	std::vector<UIBOX_CHAR> charinfo;
	std::vector<UIBOX_ELEMENT> element;
	std::deque<uint16_t> update_stack;
	std::string title;
	SDL_Texture* texture;
	uint16_t tex_w;
	uint16_t tex_h;
	uint16_t chr_w;
	uint16_t chr_h;
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h;
	uint8_t alpha;
	uint16_t update_tick = 0;
};


void SYSTEM_UIBOX_UPDATE();

// returns if the mouse input was claimed by a uibox
bool SYSTEM_UIBOX_HANDLE_MOUSE_DOWN(bool is_click, int mouse_x, int mouse_y);
void SYSTEM_UIBOX_HANDLE_MOUSE_UP();

UIBOX_INFO* uibox_new(uint16_t _x, uint16_t _y, uint16_t _w, uint16_t _h, bool can_grab, std::string title);
void uibox_setchar(UIBOX_CHAR* ci, UIBOX_INFO* ui, uint16_t char_pos, uint8_t _CHR, COLOR _COL, COLOR _BG_COL, bool update);
void uibox_setstring(UIBOX_INFO* uibox, std::string _charlist, uint16_t x, uint16_t y, COLOR col, bool update);
void uibox_addinteract(UIBOX_INFO* uibox, std::string text, std::string over_text, uint8_t type, bool* bool_ptr, uint16_t* int_ptr, uint16_t int_var, bool is_pos, uint16_t px, uint16_t py);

void uibox_update_element(int16_t uibox_in, int16_t element_in);

/*
	Finds UIBOX though the title
	RETURN: ID of that UIBOX or -1 if it does not exist
*/
int16_t uibox_get_uibox_by_title(std::string title);

/*
	Finds ELEMENT though the text
	RETURN: ID of that UIBOX or -1 if it does not exist
*/
int16_t uibox_get_element_by_text(int16_t uibox_in, std::string text);

extern SDL_Texture* UI_TEXTURE_HUEBAR;
extern COLOR* UI_PIXELS_HUEBAR;
