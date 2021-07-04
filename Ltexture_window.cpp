
#include"Ltexture_window.h"

#define LENGTH 15 // кол-во выводимых чисел на экран

Ltexture_window::Ltexture_window() {
	display.w = 0;
	display.h = 0;
	color_text.r = color_text.g = color_text.b = 0;
	color_display.r = 230;
	color_display.g = 240;
	color_display.b = 230;
}

SDL_Rect Ltexture_window::Get_display_rect() {
	return this->display;
}

void Ltexture_window::Set_display_rect(SDL_Rect& disp){
	this->display = disp;
}

void Ltexture_window::Set_display_color(SDL_Color& color){
	this->color_display = color;
}

void Ltexture_window::Set_text_color(SDL_Color& color){
	this->color_text = color;
}

void Ltexture_window::Render_Display(SDL_Rect* dstrect){
	SDL_SetRenderDrawColor(this->gRenderer, color_display.r, color_display.g, color_display.b, 255);
	if(dstrect == NULL)
		SDL_RenderFillRect(this->gRenderer, &this->display);
	else
		SDL_RenderFillRect(this->gRenderer, dstrect);
}

void Ltexture_window::Render_text(SDL_Rect* clip, SDL_Rect* dstrect, std::string& str, bool flag) {

	if (flag) {

		std::string screen;

		for (int i = 0, len = str.size(); i < LENGTH && i < len; i++)
			screen += str[i];

		if (str.length() > LENGTH) {
			std::string tmp;
			screen += "E+";
			for (int i = 0, len = str.length() - LENGTH; len > 0; i++, len /= 10) {
				tmp += len % 10 + 48;
			}
			for (int i = 0, len = tmp.length(); i < len; i++) {
				screen += tmp[i];
			}
		}
		this->loadFromRenderedText(screen, color_text);
		dstrect->w = this->mWidth;
		this->render(NULL, dstrect);

	}
	else {
		this->loadFromRenderedText(str, color_text);
		dstrect->w = this->mWidth;
		this->render(NULL, dstrect);
	}
		
}

TTF_Font* Ltexture_window::get_TTF(void) {
	return this->gFont;
}

void Ltexture_window::set_TTF(TTF_Font* p) {
	this->gFont = p;
}

bool Ltexture_window::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	this->free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(this->gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		this->mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			this->mWidth = textSurface->w;
			this->mHeight = textSurface->h;
			//	std::cout << "w = " << textSurface->w << std::endl << "w = " << mWidth << std::endl;
			//	system("pause");
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return this->mTexture != NULL;
}

#undef LENGTH 