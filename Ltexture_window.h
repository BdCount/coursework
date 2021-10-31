#pragma once

#include "LTexture.h"

class Ltexture_window : public LTexture {
protected:

	SDL_Rect display;
	SDL_Color color_text, color_display;
	TTF_Font* gFont = NULL;

public:
	 
	Ltexture_window();
	SDL_Rect Get_display_rect();
	void Set_display_rect(SDL_Rect&);
	void Set_display_color(SDL_Color&);
	void Set_text_color(SDL_Color&);
	void Render_Display(SDL_Rect*);
	void Render_text(SDL_Rect*, SDL_Rect*, std::string&, bool);
	TTF_Font* get_TTF();
	void set_TTF(TTF_Font*);
	bool loadFromRenderedText(std::string, SDL_Color);


};
