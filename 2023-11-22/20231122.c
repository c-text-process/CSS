#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>

#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2_ttf.lib")

struct Object {
	char* name;
	int x;
	int y;
	int width;
	int height;
	int zIndex;
	char type;
	char* innerText;
	struct Color* color;
	struct Color* textColor;
};

struct Button {
	int id;
	int x;
	int y;
	int w;
	int h;
	int textX;
	int textY;
	int BTK;
	char* BGC;
	char* HOVC;
	char* BRC;
	char* TXC;
	char* TXT;
	char* FONT;
	int FS;
};

struct Color {
	int R;
	int G;
	int B;
	int A;
};

SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font* font;
struct Button* button = NULL;
int buttoncount = 0;
int last_hovered_button = -1;

int setup(int, int, char[]);
void setUI(TTF_Font*);
int Text(const char*, int, int, char*, int, char*);
struct Color toRGB(char*);
void Rect(int, int, int, int, char*, int, char*);
void Button(int update, int boxx, int boxy, int boxw, int boxh, int textx, int texty, char* boxc, char* hoverc, char* borderc, int bordert, char* textc, char* text, char* font, int fonts);
char* itos(int);
int ctoi(char);

const char* KOREAN_TEXT = "안녕하세요, SDL!";

int main(int argc, char* argv[]) {
	setup(960, 480, "TEST window");
	if (TTF_Init() == -1)
	{
		return 0;
	}
	font = TTF_OpenFont("NotoSansKR-Regular.ttf", 30);
	if (font == NULL) {
		printf("Could not open font! (%s)\n", TTF_GetError());
		return -1;
	}
	setUI(font);
	FILE* file = fopen("20231117.txt", "w+");
	if (file == NULL) {
		printf("Failed to open save file!\n");
		return 0;
	}
	

	struct Object objects;
	printf("Start\n");
	SDL_Event event;
	int done = 0;
	double mouseX = -999;
	double mouseY = -999;

	Text(KOREAN_TEXT, 20, 100, "fonts/NanumGothic.ttf", 15, "#00445500");

	while (1) {
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) {
			break;
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN) {
			mouseX = event.button.x;
			mouseY = event.button.y;
		}
		else if (event.type == SDL_MOUSEMOTION) {
			mouseX = event.motion.x;
			mouseY = event.motion.y;
			if (last_hovered_button == -1) {
				for (int i = 0; i < buttoncount; i++) {
					if (mouseX >= button[i].x && mouseX <= button[i].x + button[i].w && mouseY >= button[i].y && mouseY <= button[i].y + button[i].h) {
						Button(1, button[i].x, button[i].y, button[i].w, button[i].h,
							button[i].textX, button[i].textY, button[i].BGC, button[i].HOVC,
							button[i].BRC, button[i].BTK, button[i].TXC, button[i].TXT,
							button[i].FONT, button[i].FS);
						SDL_Delay(100);
						last_hovered_button = button[i].id;
						break;
					}
				}
			}
		}
		if (last_hovered_button != -1) {
			if (!(mouseX >= button[last_hovered_button - 1].x && mouseX <= button[last_hovered_button - 1].x + button[last_hovered_button - 1].w && mouseY >= button[last_hovered_button - 1].y && mouseY <= button[last_hovered_button - 1].y + button[last_hovered_button - 1].h)) {
				Button(1, button[last_hovered_button - 1].x, button[last_hovered_button - 1].y,
					button[last_hovered_button - 1].w, button[last_hovered_button - 1].h,
					button[last_hovered_button - 1].textX, button[last_hovered_button - 1].textY, button[last_hovered_button - 1].BGC,
					button[last_hovered_button - 1].HOVC, button[last_hovered_button - 1].BRC,
					button[last_hovered_button - 1].BTK, button[last_hovered_button - 1].TXC,
					button[last_hovered_button - 1].TXT,
					button[last_hovered_button - 1].FONT, button[last_hovered_button - 1].FS);
				last_hovered_button = -1;
			}
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	TTF_Quit();

	fclose(file);
	printf("End\n");

	return 0;
}





//함수들
struct Color toRGB(char* hex) {
	struct Color returnColor = {
		ctoi(hex[1]) * 16 + ctoi(hex[2]),
		ctoi(hex[3]) * 16 + ctoi(hex[4]),
		ctoi(hex[5]) * 16 + ctoi(hex[6]),
		ctoi(hex[7]) * 16 + ctoi(hex[8]),
	};
		
	return returnColor;
}

//창 생성 함수
int setup(int window_width, int window_height, char name[]) {
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Could not initialize SDL! (%s)\n", SDL_GetError());
		return -1;
	}

	// Create window
	window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_OPENGL);
	if (window == NULL) {
		printf("Could not create window! (%s)\n", SDL_GetError());
		return -1;
	}

	// Create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	if (renderer == NULL) {
		printf("Could not create renderer! (%s)\n", SDL_GetError());
		return -1;
	}

	// Clear renderer (white)
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}


void Button(int update, int boxx, int boxy, int boxw, int boxh, int textx, int texty, char* boxc, char* hoverc, char* borderc, int bordert, char* textc, char* text, char* font, int fonts) {
	if (!update) {
		buttoncount++;
		button = (struct Button*)realloc(button ,sizeof(struct Button) * buttoncount);
		(button[buttoncount - 1]).id = buttoncount;
		(button[buttoncount - 1]).x = boxx;
		(button[buttoncount - 1]).y = boxy;
		(button[buttoncount - 1]).w = boxw;
		(button[buttoncount - 1]).h = boxh;
		(button[buttoncount - 1]).textX = textx;
		(button[buttoncount - 1]).textY = texty;
		(button[buttoncount - 1]).BGC = boxc;
		(button[buttoncount - 1]).HOVC = hoverc;
		(button[buttoncount - 1]).BRC = borderc;
		(button[buttoncount - 1]).BTK = bordert;
		(button[buttoncount - 1]).TXC = textc;
		(button[buttoncount - 1]).TXT = text;
		(button[buttoncount - 1]).FONT = font;
		(button[buttoncount - 1]).FS = fonts;
	}
	if (last_hovered_button != -1 || update == 0) {
		Rect(boxx, boxy, boxw, boxh, boxc, bordert, borderc);
	}
	else{
		Rect(boxx, boxy, boxw, boxh, hoverc, bordert, borderc);
	}
	Text(text, textx, texty, font, fonts, textc);
}
//UI 생성
void setUI(TTF_Font* font) {
	Rect(0, 0, 960, 30, "#cccccc00", 2, "0xffffff00");
	Button(0, 2, 2, 60, 26, 20, 3, "#cccccc00", "#ffffff00", "#00000000", 1, "#00000000", "File", "NotoSansKR-Regular.ttf", 15);
	Button(0, 61, 2, 60, 26, 80, 3, "#cccccc00", "#ffffff00", "#00000000", 1, "#00000000", "Edit", "NotoSansKR-Regular.ttf", 15);
}

//사각형 생성
void Rect(int x, int y, int width, int height, char* fillColor, int borderThickness, char* borderColor) {
	struct Color Fillc = toRGB(fillColor);
	struct Color Borderc = toRGB(borderColor);
	SDL_Rect shape = { x + borderThickness, y + borderThickness, width - borderThickness * 2, height - borderThickness * 2 };
	SDL_Rect outline = { x , y , width, height};
	SDL_SetRenderDrawColor(renderer, Borderc.R, Borderc.G, Borderc.B, Borderc.A);
	SDL_RenderFillRect(renderer, &outline);
	SDL_SetRenderDrawColor(renderer, Fillc.R, Fillc.G, Fillc.B, Fillc.A);
	SDL_RenderFillRect(renderer, &shape);

	// Update screen
	SDL_RenderPresent(renderer);
}

int Text(const char* strings, int x, int y, char * fontRoot, int fontSize, char* color) {
	TTF_Font* font = TTF_OpenFont(fontRoot, fontSize);
	if (font == NULL) {
		printf("폰트 로딩 오류!\n");
		return -1;
	}
	struct Color c = toRGB(color);
	SDL_Color tcolor = { c.R , c.G, c.B, c.A };
	SDL_Surface* surface = TTF_RenderUTF8_Blended(font, strings, tcolor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_Rect r = { x, y, surface->w, surface->h };
	SDL_RenderCopy(renderer, texture, NULL, &r);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);
	return 0;
}

char* itos(int input) {
	int n = input;
	char* output;
	int length = 0;
	int w = 1;

	for (; n != 0; n /= 10, ++length, w *= 10);
	w /= 10;
	output = (char*)malloc(sizeof(char) * length);
	for (int i = length - 1; i >= 0; i--) {
		if (i == 0) {
			output[length - i - 1] = '0' + (input % (w * 10));
			output[length] = '\0';
			break;
		}
		else {
			output[length - i - 1] = '0' + (input / w);
			input = input % w;
			w /= 10;
		}
	}

	printf("length = %d", length);
	printf("output = %s", output);
	return 0;
}

int ctoi(char c) {
	if ((c >= 'a' && c <= 'f') && (c < '0' || c > '9')) {
		c += 'A';
	}
	switch (c)
	{
	case '0':
		return 0;
		break;
	case '1':
		return 1;
		break;
	case '2':
		return 2;
		break;
	case '3':
		return 3;
		break;
	case '4':
		return 4;
		break;
	case '5':
		return 5;
		break;
	case '6':
		return 6;
		break;
	case '7':
		return 7;
		break;
	case '8':
		return 8;
		break;
	case '9':
		return 9;
		break;
	case 'A':
		return 10;
		break;
	case 'B':
		return 11;
		break;
	case 'C':
		return 12;
		break;
	case 'D':
		return 13;
		break;
	case 'E':
		return 14;
		break;
	case 'F':
		return 15;
		break;
	default:
		break;
	}
}
