#pragma once

#include "LTexture.h"

class Ltexture_button : public LTexture {
protected:
	SDL_Rect butt_size;	// размер кнопок
	SDL_Rect* PTexture; // массив полей для обрезки текстуры
	int head; // счетчик текстур
	SDL_Texture* ButtTexture;
	int ButtWidth;
	int ButtHeight;

public:
	Ltexture_button();
	void render_butt(SDL_Rect* clip, SDL_Rect* dstrect);
	bool loadButtFromFile(std::string);
	void set_size_button(SDL_Rect*);
	void set_size_mass(int);
	bool set_texture(int const y, int const x, int const N, int const M);
	void drow_button(int a, int b, int SCREEN_WIDTH, int SCREEN_HEIGHT, int M, int N);



};