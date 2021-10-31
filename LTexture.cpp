/**/
#include "LTexture.h"
#include <string>

/**/
LTexture::LTexture()
{
	this->mTexture = NULL;
	this->mWidth = 0;
	this->mHeight = 0;
}


LTexture::~LTexture()
{
	this->free();
}

bool LTexture::loadFromFile(std::string path) {
	this->free();
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
			this->mWidth = loadedSurface->w;
			this->mHeight = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	this->mTexture = newTexture;
	return this->mTexture != NULL;
}

void LTexture::free()
{
	if (this->mTexture != NULL) {
		SDL_DestroyTexture(this->mTexture);
		this->mTexture = NULL;
		this->mWidth = 0;
		this->mHeight = 0;
	}
}

void LTexture::render(SDL_Rect* clip, SDL_Rect* dstrect)
{
	SDL_RenderCopy(this->gRenderer, this->mTexture, clip, dstrect);
}

void LTexture::set_render(SDL_Renderer* render) {
	this->gRenderer = render;
}

SDL_Renderer* LTexture::get_render(void) {
	return this->gRenderer;
}

int LTexture::getWidth() { return this->mWidth; }

int LTexture::getHeight() { return this->mHeight; }
/**/
