#pragma once
#include "libs.h"
#include <SDL_ttf.h>
/**/
class LTexture
{
public:
	LTexture();
	~LTexture();
	bool loadFromFile(std::string);
	void free();
	void render(SDL_Rect*, SDL_Rect*);
	void set_render(SDL_Renderer* );
	SDL_Renderer* get_render();
	int getWidth();
	int getHeight();

protected:
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
	SDL_Renderer* gRenderer = NULL;

};
/**/