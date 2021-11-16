#include<SDL_image.h>
#include"SDL.h"
#include <string>
#include<cmath>
#include<iostream>
using namespace std;
bool quit;
bool turn=true;
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
const int TILE_SIZE = 40;
int i, j, sum, c;
int sadf;
bool unit;
bool unat;
bool game=false;
bool gam;
bool billy=false;
bool una = true;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Surface* surface = nullptr;

struct darda
{
	int x;
	int y;
	const int h = 75;
	const int w = 75;
	SDL_Texture* cir;
};
void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, int w, int h)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}
void get(darda* van, int i,int b)
{
	int j;
	for (j = 0; j < 20; j++)
	{
		if (van[i].x == van[j].x && van[i].y == van[j].y)
		{
			van[i].x = van[i].x + 75;
			van[i].y = van[i].y - 75;
			if ( van[i].x>=750 || van[i].y < 0 )
			{
				van[i].x = van[i].x - 150;
				van[i].y = van[i].y +150;
				break;
			}
			else
			{
				SDL_DestroyTexture(van[j].cir);
				van[j].x = -8;
				van[j].y = -8;
				game = true;
				break;
			}
		}
	}
}
void get(darda* van, int i, int b,int c)
{
	int j;
	for (j = 20; j < 40; j++)
	{
		if (van[i].x == van[j].x && van[i].y == van[j].y)
		{
			van[i].x = van[i].x -75;
			van[i].y = van[i].y + 75;
			if (van[i].x < 0 ||  van[i].y>=750)
			{
				van[i].x = van[i].x +150;
				van[i].y = van[i].y - 150;
				break;
			}
			else
			{
				SDL_DestroyTexture(van[j].cir);
				van[j].x = -8;
				van[j].y = -8;
				game = true;
				break;
			}
		}
	}
}
void get(darda* van, int i, int b, int c,int d)
{
	int j;
	for (j = 20; j < 40; j++)
	{
		if (van[i].x == van[j].x && van[i].y == van[j].y)
		{
			van[i].x = van[i].x + 75;
			van[i].y = van[i].y + 75;
			if (van[i].x >= 750 || van[i].y>=750)
			{
				van[i].x = van[i].x - 150;
				van[i].y = van[i].y - 150;
				break;
			}
			else
			{
				SDL_DestroyTexture(van[j].cir);
				van[j].x = -8;
				van[j].y = -8;
				game = true;
				break;
			}
		}
	}
}
void get(darda* van, int i)
{
	int j;
	for (j = 0; j < 20; j++)
	{
		if (van[i].x == van[j].x && van[i].y == van[j].y)
		{
			van[i].x = van[i].x - 75;
			van[i].y = van[i].y - 75;
			if (van[i].x < 0 || van[i].y<0)
			{
				van[i].x = van[i].x + 150;
				van[i].y = van[i].y +150;
				break;
			}
			else
			{
				SDL_DestroyTexture(van[j].cir);
				van[j].x = -8;
				van[j].y = -8;
				game = true;
				break;
			}
		}
	}
}
void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y)
{
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderTexture(tex, ren, x, y, w, h);
}
void show(darda* vasda, SDL_Renderer* ren)
{
	for (int e = 0; e < 40; e++)
	{
		renderTexture(vasda[e].cir, renderer, vasda[e].x, vasda[e].y);
		
	}
}
void showfild(SDL_Texture* white, SDL_Texture* black, SDL_Renderer* ren)
{
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			sum = i + j;

			if (sum % 2 == 0)
			{
				renderTexture(white, renderer, 75 * j, 75 * i);
			}
			else
			{
				renderTexture(black, renderer, 75 * j, 75 * i);
				
			}
		}
		
	}
}

int setup()
{
	quit = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << SDL_GetError() << std::endl;
		return 1;
	}
	window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		return 2;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		return 3;
	}
}
/**
* Загружает изображение в текстуру для рендерера
* @param file Путь к изображению
* @param ren Рендерер, на который эту текстуру можно будет отрисовать
* @return Возвращает текстуру, либо nullptr в случае ошибки.
*/
SDL_Texture* loadTexture(const std::string& file, SDL_Renderer* ren)
{
	SDL_Texture* texture = IMG_LoadTexture(ren, file.c_str());
	if (!texture)
	{
		std::cout << IMG_GetError(); // Можно заменить на SDL_GetError()
	}
	return texture;
}

/**
* Отобразить SDL_Texture на SDL_Renderer на координатах x, y, с масштабированием
* @param tex Текстура для отображения
* @param ren Рендерер
* @param x Координаты
* @param y
* @param w Фактический размер при отрисовке
* @param h
*/



/**
* Отрисовать SDL_Texture на SDL_Renderer на координатах x, y, без масштабирования
* @param tex Текстура
* @param ren Рендерер
* @param x Координаты
* @param y
*/


int main(int argc, char*argv[])
{
	setup();
	SDL_Texture* background = loadTexture("background.png", renderer);
	SDL_Texture* image = loadTexture("image.png", renderer);
	sum = i + j;
	
	// Проверка
	
	if (!background || !image )
	{
		// В оригинале, эта часть использовала шаблонную функцию cleanup(), рассмотренную в P.S. к первому уроку, добавленному уже после написания перевода, и посему, не попавшему в перевод. 
		SDL_DestroyTexture(background);
		SDL_DestroyTexture(image);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	// Определение количества плиток, необходимого для покрытия всего окна
// От переводчика: я бы заменил на ceil(float(SCREEN_WIDTH) / TILE_SIZE), чтобы в том случае, кода размер окна не кратен размеру плитки, оставшаяся часть окна не оставалась пустой; однако, в данном примере размеры заданы константой и кратны, так что это не страшно.
	int xTiles = SCREEN_WIDTH / TILE_SIZE;
	int yTiles = SCREEN_HEIGHT / TILE_SIZE;

	// Отрисовка фона
	for (int i = 0; i < xTiles * yTiles; ++i)
	{
		int x = i % xTiles;
		int y = i / xTiles;
		renderTexture(background, renderer, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
	}
	int iW, iH;
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	int x = SCREEN_WIDTH / 2 - iW / 2;
	int y = SCREEN_HEIGHT / 2 - iH / 2;
	renderTexture(image, renderer, x, y);
	SDL_Event e;
	while (quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = false;
				return 5;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.x<400 && e.button.x>250 && e.button.y<320 && e.button.y>170)
				{
					quit = false;
			    }
			}
			SDL_RenderPresent(renderer);
		}
	}
	quit = true;
	SDL_Event b;
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(image);
	SDL_RenderClear(renderer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SCREEN_WIDTH = 750;
	SCREEN_HEIGHT = 750;
	setup();
	SDL_Texture* white = loadTexture("whitefoot.png", renderer);
	SDL_Texture* black = loadTexture("blakfoot.png", renderer);
	/*SDL_Texture* imag = loadTexture("image.png", renderer);*/
	SDL_RenderClear(renderer);
	/*SDL_Texture* circle = loadTexture("circle.png", renderer);*/
	/*surface = SDL_GetWindowSurface(window);*/
	if(!white|| !black )
	{
		SDL_DestroyTexture(black);
		SDL_DestroyTexture(white);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	int r = 0;
	darda vang[40];
	for(i=0;i<20;i++)
	{
		vang[i].cir = loadTexture("circle.png", renderer);
	}
	for (i = 0; i < 20; i++)
	{
		vang[i+20].cir=loadTexture("fishka.png", renderer);
	}
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			sum = i + j;
			if (sum % 2 != 0)
			{
				if (i>=0 && i<4)
				{
					vang[r].x = 75 * j;
					vang[r].y = 75 * i;
					r++;
				}
				if (i > 5 && i < 10)
				{
					vang[r].x = 75 * j;
					vang[r].y = 75 * i;
					r++;
				}
			}
				
		}
		
	}
	showfild(white, black, renderer);
	show(vang, renderer);
	/*show1(vana, renderer);*/
	while (quit)
	{
		while (SDL_PollEvent(&b))
		{
			if  (b.type == SDL_QUIT)
			
				quit = false;
		
					if (b.type == SDL_MOUSEBUTTONDOWN)
					{
                         if(b.button.button== SDL_BUTTON_LEFT)
						 { 
							 if (turn)
							 {
								 for (i = 20; i < 40; i++)
								 {
									 if (b.button.x < vang[i].x + 75 && b.button.x > vang[i].x && b.button.y < vang[i].y + 75 && b.button.y>vang[i].y)
									 {
										 vang[i].x = vang[i].x - 75;
										 vang[i].y = vang[i].y - 75;
										 for (int p = 20; p < 40; p++)
										 {
											 if (vang[i].x == vang[p].x && vang[i].y == vang[p].y)
											 {
												 if (p != i)
												 {
													 vang[i].x = vang[i].x + 75;
													 vang[i].y = vang[i].y +75;
													 unat = true;
													 break;
												 }
											 }
										 }
										 if (unat)
										 {
											 unat = false;
											 break;
										 }
										
										 if (vang[i].x < 0 || vang[i].y < 0)
										 {
											 vang[i].x = vang[i].x + 75;
											 vang[i].y = vang[i].y + 75;
											 break;
										}
										 get(vang, i);
										 if (game)
										 {
											 game = false;
											 break;
										 }
											 turn = false;
											 break;
										 
									 }
								 }
								 
							 }
							 else
							 { 
								 for (i = 0; i < 20; i++)
								 {
									 if (b.button.x < vang[i].x + 75 && b.button.x > vang[i].x && b.button.y < vang[i].y + 75 && b.button.y>vang[i].y)
									 {

										 vang[i].x = vang[i].x - 75;
										 vang[i].y = vang[i].y + 75;
										 for (int p = 0; p < 20; p++)
										 {
											 if (vang[i].x == vang[p].x && vang[i].y == vang[p].y)
											 {
												 if (p != i)
												 {
													 vang[i].x = vang[i].x + 75;
													 vang[i].y = vang[i].y - 75;
													 unit = true;
													 break;
												 }
											 }
										 }
										 if (unit)
										 {
											 unit = false;
											 break;
										 }
										 if (vang[i].x < 0 || vang[i].y >= 750)
										 {
											 vang[i].x = vang[i].x + 75;
											 vang[i].y = vang[i].y - 75;
											 
										 }
										 get(vang, i, 0, 0);
										 if (game)
										 {
											 game = false;
											 break;
										 }
											 turn = true;
											 break;
										 
									 }
									
								 }
								 
						}
						}
						
						 if (b.button.button == SDL_BUTTON_RIGHT)
						 {
							 if (turn)
							 {
								 for (i = 20; i < 40; i++)
								 {
									 if (b.button.x < vang[i].x + 75 && b.button.x > vang[i].x && b.button.y < vang[i].y + 75 && b.button.y>vang[i].y)
									 {
										 vang[i].x = vang[i].x +75;
										 vang[i].y = vang[i].y - 75;
										 for (int p = 20; p < 40; p++)
										 {
											 if (vang[i].x == vang[p].x && vang[i].y == vang[p].y)
											 {
												 if (p != i)
												 {
													 vang[i].x = vang[i].x - 75;
													 vang[i].y = vang[i].y + 75;
													 unat = true;
													 break;
												 }
											 }
										 }
										 if (unat)
										 {
											 unat = false;
											 break;
										 }
										 if (vang[i].x >=750 || vang[i].y < 0)
										 {
											 vang[i].x = vang[i].x - 75;
											 vang[i].y = vang[i].y + 75;
											 break;
										 }
										 get(vang, i, 0);
										 if (game)
										 {
											 game = false;
											 break;
										 }
											 turn = false;
											 break;
										 
									 }
								 }
							 }
							 else
							 {
								 for (i = 0; i < 20; i++)
								 {
									 if (b.button.x < vang[i].x + 75 && b.button.x > vang[i].x && b.button.y < vang[i].y + 75 && b.button.y>vang[i].y)
									 {

										 vang[i].x = vang[i].x + 75;
										 vang[i].y = vang[i].y + 75;
										 for (int p = 0; p < 20; p++)
										 {
											 if (vang[i].x == vang[p].x && vang[i].y == vang[p].y)
											 {
												 if (p != i)
												 {
													 vang[i].x = vang[i].x - 75;
													 vang[i].y = vang[i].y - 75;
													 unit = true;
													 break;
												 }
											 }
										 }
										 if (unit)
										 {
											 unit = false;
											 break;
										 }
										 if (vang[i].x >= 750 || vang[i].y >= 750)
										 {
											 vang[i].x = vang[i].x - 75;
											 vang[i].y = vang[i].y - 75;

										 }
										 get(vang, i, 0, 0, 0);
										 if (game)
										 {
											 game = false;
											 break;
										 }
											 turn = true;
											 break;
										 
									 }
								 }
							 }
						 }
					}
					
				SDL_RenderClear(renderer);
			showfild(white, black, renderer);
			show(vang, renderer);
			SDL_RenderPresent(renderer);	
		}
	}
	for (i = 0; i < 40; i++)
	{
		SDL_DestroyTexture(vang[i].cir);
	}
	//SDL_DestroyTexture(circle);
	SDL_DestroyTexture(white);
	
	SDL_DestroyTexture(black);
	SDL_DestroyRenderer(renderer);
	/*SDL_Delay(20000);*/
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	return 0;
}