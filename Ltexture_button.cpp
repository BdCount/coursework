
#include "Ltexture_button .h"
Ltexture_button::Ltexture_button() {
	this->butt_size.w = 0;
	this->butt_size.h = 0;
	this->PTexture = NULL;
	this->head = 0;
}

void Ltexture_button::render_butt(SDL_Rect* clip, SDL_Rect* dstrect)
{
	SDL_RenderCopy(this->gRenderer, this->ButtTexture, clip, dstrect);
}

void Ltexture_button::set_size_button(SDL_Rect* button) {
	this->butt_size = *button;
}

void Ltexture_button::set_size_mass(int size) {
	delete PTexture;
	PTexture = NULL;
	PTexture = new SDL_Rect[size];
}

bool Ltexture_button::loadButtFromFile(std::string path) {
	bool success = true;
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		std::cout << "Unable to load image %s! SDL_image Error: \n" << SDL_GetError() << std::endl;
	}
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x00, 0xFF, 0xFF));

		newTexture = SDL_CreateTextureFromSurface(this->gRenderer, loadedSurface);
		if (newTexture == NULL) {
			std::cout << "Unable to create texture from %s! SDL Error: \n" << SDL_GetError() << std::endl;
		}
		else {
			this->ButtWidth = loadedSurface->w;
			this->ButtHeight = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	this->ButtTexture = newTexture;
	return this->ButtTexture != NULL;
}

bool Ltexture_button::set_texture(int const y, int const x, int const N, int const M) {
	SDL_Rect temp;
	temp.w = x;
	temp.h = y;
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++){
			PTexture[i * N + j].x = x * j;
			PTexture[i * N + j].y = y * i;
			PTexture[i * N + j].w = x;
			PTexture[i * N + j].h = y;
		}
	return 0;
}

void Ltexture_button::drow_button(int a, int b, int SCREEN_WIDTH, int SCREEN_HEIGHT, int M, int N) {
	for (int i = M - 1; i >= 0; i--)
		for (int j = N - 1; j >= 0; j--)
		{
			butt_size.x = SCREEN_WIDTH - butt_size.w * (N - j);
			butt_size.y = SCREEN_HEIGHT - butt_size.h * (M - i);
			if (a == i && b == j)
				this->render_butt(&PTexture[i * N + j], &butt_size);
			else
				this->render(&PTexture[i * N + j], &butt_size);
//						SDL_RenderPresent(this->get_render());
		}
}
