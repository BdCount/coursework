#define DEBAG


#define MAIN main

#include "LTexture.h"
#include <string>
#include <regex>
#include <Windows.h>
#include "postfix.h"
#include <SDL_ttf.h>
#include "stroka_dec.h"
#include "Ltexture_window.h"
#include "Ltexture_button .h"

#define M 6
#define N 4

SDL_Window* gWindow = NULL;

int const SCREEN_WIDTH = 350;
int const SCREEN_HEIGHT = 500;

SDL_Rect gSpriteClips[M * N];
SDL_Rect butt_size;
SDL_Rect displayRect;
SDL_Rect screen_rect;
SDL_Rect screen2_rect;

Ltexture_button gSpriteSheetTexture;
Ltexture_window gResultTexture;

Ltexture_window display;


char grid[M][N] = {
	/**/
	'^', '&' , 'c', 'b', // ^ = pow, & = sqrt, c = C, b = backspace
	'(', ')' , '!', '/',
	'7', '8' , '9', '*',
	'4', '5' , '6', '-',
	'1', '2' , '3', '+',
	's', '0' , ' ', '=' // s = sign
};

bool init();
bool loadMedia();
void close();

int MAIN(int argc, char* args[])
{
	//FreeConsole();

	if (!init()) {
		std::cout << "Window could not be initialized! \n";
	}
	else {
		if (!loadMedia()) {
			std::cout << "Media could not be loaded! \n";
		}
		else {
			bool quit = false;
			SDL_Event e;
			std::string screen = "";		// вводимое выражение
			std::string screen_result = "";		// результат

			SDL_Color textColor = { 0, 0, 0 };
			
			SDL_Rect hoverRect;
			hoverRect.x = hoverRect.y = -1;

			char error = 0;		// проверка на корректность выражения

			bool newLine = false;	//
			bool line_refresh = false;

			displayRect.x = 0;
			displayRect.y = 0;
			displayRect.w = SCREEN_WIDTH;
			displayRect.h = SCREEN_HEIGHT - M * butt_size.h;

			while (!quit) {

				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					else {
						if (e.type == SDL_KEYDOWN)
						{

						}
						else 
						if (e.type == SDL_MOUSEMOTION) {
							int x = butt_size.w * (e.motion.x / butt_size.w);
							int y = SCREEN_HEIGHT / M + butt_size.h * (e.motion.y / butt_size.h);
							y = SCREEN_HEIGHT - ((SCREEN_HEIGHT - e.motion.y) / butt_size.h + 1) * (butt_size.h);
							
							if (e.motion.x < 1 || e.motion.x > SCREEN_WIDTH - 2 || e.motion.y > SCREEN_HEIGHT - 2) {
								x = -butt_size.w;
								y = -butt_size.h;
							}
							if (y < SCREEN_HEIGHT - butt_size.h * M)
								y = -butt_size.h;

							hoverRect.x = M - 1 - (SCREEN_HEIGHT - e.motion.y) / butt_size.h;;
							hoverRect.y = e.button.x / butt_size.w;

							std::cout << "x = " << hoverRect.x << std::endl;
							std::cout << "y = " << hoverRect.y << std::endl;
						}
						else
						if (e.type == SDL_MOUSEBUTTONDOWN) {
							if (e.button.button == SDL_BUTTON_LEFT) {
			
								hoverRect.x = M - 1 - (SCREEN_HEIGHT - e.motion.y) / butt_size.h;;
								hoverRect.y = e.button.x / butt_size.w;

								int y1 = e.button.x / butt_size.w;
								int x1 = M - 1 - (SCREEN_HEIGHT - e.motion.y) / butt_size.h;
								
								if (x1 >= 0 && x1 < M && y1 >= 0 && y1 < N) {
									std::cout << grid[y1][x1] << std::endl;
									
									if (grid[x1][y1] == 'c') {

										screen_result = "";
										screen = "";
										newLine = false;										
									}
									else
									if (grid[x1][y1] == 'b') {
										if (screen.size() > 0)
											screen.pop_back();
									}
									else
									if (grid[x1][y1] == 's') {
										if (screen.size() > 0) {
											if (screen[0] == '-') {
												screen.erase(0, 1);
											}
											else
											if (screen[0] == '+') {
												screen.erase(0, 1);
												screen = "-" + screen;
											}
											else {
												screen = "-" + screen;
											}
										}
										else
											screen += "-";
									}
									else
									if (grid[x1][y1] == '=' && screen.size() > 0) {		// обработка вычисления
										screen_result = "";
										newLine = true;
										line_refresh = true;
										error = check_exprassion(screen);
										if (!error) {
											error = infix_to_postfix(screen, screen_result);
											if (error)
												screen_result = "ERROR";
										}
										else {
											screen_result = "ERROR";
										}
									}
									else
									if(grid[x1][y1] != '=')
										screen += grid[x1][y1];

									system("cls");
									std::cout << screen << std::endl;
									std::cout << "res = " << screen_result << std::endl;
									std::cout << "newline = " << newLine<< std::endl;
									std::cout << "x1 = " << x1 << std::endl << "y1 = " << y1 << std::endl;
								}
							}
						}


					}



					SDL_RenderClear(gResultTexture.get_render());


					SDL_SetRenderDrawColor(gSpriteSheetTexture.get_render(), 0, 0, 0, 0);
					SDL_RenderClear(gSpriteSheetTexture.get_render());

					//highlighting signs and numbers
					SDL_SetRenderDrawColor(gSpriteSheetTexture.get_render(), 105, 105, 105, 0);
					
					//display

					gResultTexture.Set_display_rect(displayRect);
					gResultTexture.Render_Display(NULL);

					gSpriteSheetTexture.drow_button(hoverRect.x, hoverRect.y, SCREEN_WIDTH, SCREEN_HEIGHT, M, N);
//					draw_butt(hoverRect.x, hoverRect.y);


					// render input
					if (screen.size() > 0) {
						screen_rect.x = 0;
						screen_rect.y = 0;
						screen_rect.h = SCREEN_HEIGHT / 20;
						gResultTexture.Render_text(NULL, &screen_rect, screen, false);					
					}


					// render result
					if (newLine) {

						std::string tmp("=");
						screen_rect.y = screen_rect.h;
						gResultTexture.Render_text(NULL, &screen_rect, tmp, false);

						screen_rect.y = screen_rect.h * 2;
						gResultTexture.Render_text(NULL, &screen_rect, screen_result, true);
					}					


					SDL_RenderPresent(gResultTexture.get_render());
				}
//				SDL_RenderPresent(gResultTexture.get_render());
			}
		}
	}

	//system("pause");
	close();
	return 0;
}

bool init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!");
	}
	else
	gWindow = SDL_CreateWindow("Calculator", /**/1050/*SDL_WINDOWPOS_UNDEFINED/**/, /*0/**/SDL_WINDOWPOS_UNDEFINED/**/, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		std::cout << "Window could not be created! SDL Error: \n" << SDL_GetError() << std::endl;
		success = false;
	}
	else {
		gSpriteSheetTexture.set_render(SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED));
		if (gSpriteSheetTexture.get_render() == NULL) {
			std::cout << "Renderer could not be created! SDL Error: \n" << SDL_GetError() << std::endl;
			success = false;
		}
		else {
			SDL_SetRenderDrawColor(gSpriteSheetTexture.get_render(), 0xFF, 0xFF, 0xFF, 0xFF);

			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				std::cout << "SDL_image could not initialize! SDL_image Error: \n" << IMG_GetError() << std::endl;
				success = false;
			}
			if (TTF_Init() == -1)
			{
				printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				success = false;
			}
		}
	}

	return success;
}

bool loadMedia() {
	bool success = true;


	if (!gSpriteSheetTexture.loadFromFile("calculator.png")) {
		std::cout << "Failed to load texture image!\n";
		success = false;
	}
	else
	if (!gSpriteSheetTexture.loadButtFromFile("calculator_clic.png")) {
		std::cout << "Failed to load texture image!\n";
		success = false;
	}


	else {
		butt_size.h = SCREEN_HEIGHT * 2 / 3 / M; // высота 1 кнопки
		butt_size.w = SCREEN_WIDTH / N; // ширина 1 кнопки
		int y = gSpriteSheetTexture.getHeight() / M;
		int x = gSpriteSheetTexture.getWidth() / N;
		gSpriteSheetTexture.set_size_mass(M * N);
		gSpriteSheetTexture.set_size_button(&butt_size);
		gSpriteSheetTexture.set_texture(y, x, N, M);
		
	
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
			{

				gSpriteClips[i * N + j].x = x * j;
				gSpriteClips[i * N + j].y = y * i;
				gSpriteClips[i * N + j].w = x;
				gSpriteClips[i * N + j].h = y;
				gSpriteSheetTexture.render(&gSpriteClips[i * N + j], &butt_size);
			//	SDL_RenderPresent(gSpriteSheetTexture.get_render());
			}
	}
	gResultTexture.set_render(gSpriteSheetTexture.get_render());
	gResultTexture.set_TTF(TTF_OpenFont("456.ttf", 28));
	if (gResultTexture.get_TTF() == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}/**/	

//	draw_butt(-1,-1);
//	SDL_RenderPresent(gResultTexture.get_render());
	return success;
}


void close() {
	gSpriteSheetTexture.free();

	SDL_DestroyRenderer(gSpriteSheetTexture.get_render());
	SDL_DestroyWindow(gWindow);
	gSpriteSheetTexture.set_render(NULL);
	gResultTexture.set_render(NULL);
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();
}