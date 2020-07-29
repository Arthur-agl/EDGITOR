#pragma once

#include <string>
#include <vector>
#include <memory>
#include <deque>
#include <iostream>

#include "COLOR.h"
#include "CANVAS.h"
#include "BRUSH.h"

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

struct UIBOX_ELEMENT_MAIN;

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

	std::vector<std::unique_ptr<UIBOX_ELEMENT_MAIN>> element_list;

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
void uibox_set_char(UIBOX_CHAR* ci, UIBOX_INFO* ui, uint16_t char_pos, uint8_t _CHR, COLOR _COL, COLOR _BG_COL, bool update);
void uibox_set_string(UIBOX_INFO* uibox, std::string _charlist, uint16_t x, uint16_t y, COLOR col, bool update);
//void uibox_add_element(UIBOX_INFO* uibox, std::string text, std::string over_text, uint8_t type, bool* bool_ptr, uint16_t* int_ptr, uint16_t int_var, bool is_pos, uint16_t px, uint16_t py);

void uibox_add_element_textbox(UIBOX_INFO* uibox, uint16_t x, uint16_t y, std::string text);
void uibox_add_element_button(UIBOX_INFO* uibox, uint16_t x, uint16_t y, std::string text, uint16_t* input_var, uint16_t button_var);
void uibox_add_element_toggle(UIBOX_INFO* uibox, uint16_t x, uint16_t y, std::string text, bool* input_var);
void uibox_add_element_slider(UIBOX_INFO* uibox, uint16_t x, uint16_t y, std::string text, uint16_t* input_var);
void uibox_add_element_textinput(UIBOX_INFO* uibox, uint16_t x, uint16_t y, std::string text);
void uibox_add_element_numinput(UIBOX_INFO* uibox, uint16_t x, uint16_t y, std::string text);

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

  //
 //   ELEMENTS   ///////////////////////////////////////////////// ///////  //////   /////    ////     ///      //       /
//

// UIBOX_ELEMENT_MAIN
struct UIBOX_ELEMENT_MAIN {
	std::string text = "";
	uint16_t x = 0;
	uint16_t y = 0;
	virtual void create(UIBOX_INFO*) = 0;
	virtual void update(void) = 0;
};

// TEXTBOX
struct UIBOX_ELEMENT_TEXTBOX : public UIBOX_ELEMENT_MAIN {
	void create(UIBOX_INFO* uibox)
	{
		uibox_set_string(uibox, text, x, y, COL_WHITE, false);
	}
	void update()
	{
		std::cout << "TEXTBOX" << std::endl;
	}
};

// BUTTON
struct UIBOX_ELEMENT_BUTTON : public UIBOX_ELEMENT_MAIN {
	uint16_t* input_var = nullptr;
	uint16_t button_var = 0;
	void create(UIBOX_INFO* uibox)
	{
		uibox_set_string(uibox, text, x, y, COL_WHITE, false);
	};
	void update()
	{
		*input_var = button_var;
		std::cout << button_var << std::endl;
	}
};

// TOGGLE
struct UIBOX_ELEMENT_TOGGLE : public UIBOX_ELEMENT_MAIN {
	void create(UIBOX_INFO* uibox) {};
	void update()
	{
		std::cout << "TOGGLE" << std::endl;
	}
};

// SLIDER
struct UIBOX_ELEMENT_SLIDER : public UIBOX_ELEMENT_MAIN {
	void create(UIBOX_INFO* uibox) {};
	void update()
	{
		std::cout << "SLIDER" << std::endl;
	}
};

// TEXTINPUT
struct UIBOX_ELEMENT_TEXTINPUT : public UIBOX_ELEMENT_MAIN {
	void create(UIBOX_INFO* uibox) {};
	void update()
	{
		std::cout << "TEXTINPUT" << std::endl;
	}
};

// NUM_INPUT
struct UIBOX_ELEMENT_NUMINPUT : public UIBOX_ELEMENT_MAIN {
	void create(UIBOX_INFO* uibox) {};
	void update()
	{
		std::cout << "NUMINPUT" << std::endl;
	}
};