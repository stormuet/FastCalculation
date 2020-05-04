﻿#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>
#include <sstream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
using namespace std;


int RandomX(int lv) {
	if (lv > 0 && lv <= 5) { return 1 + rand() % 9; }
	else if (lv > 5 && lv <= 10) { return  10 + rand() % 10; }
	else if (lv > 10 && lv <= 15) { return 20 + rand() % 30; }
	else if (lv > 15 && lv <= 20) { return 50 + rand() % 50; }
	else return 100 + rand() % 900;
}
int RandomCal() {
	int a = 1 + rand() % 4;
	return a;
}
int RandomY(int a, int lv) {
	if (a == 1 || a == 2) {
		if (lv > 0 && lv <= 5) { return 1 + rand() % 9; }
		else if (lv > 5 && lv <= 10) { return  10 + rand() % 10; }
		else if (lv > 10 && lv <= 15) { return 20 + rand() % 30; }
		else if (lv > 15 && lv <= 20) { return 50 + rand() % 50; }
		else return 100 + rand() % 900;
	}
	if (a == 3) {
		if (lv > 0 && lv <= 20) { return 1 + rand() % 9; }
		else { return  10 + rand() % 10; }
	}
	if (a == 4) {
		return 1 + rand() % 9;
	}
}
double CorrectAnswer(int x, int y, int cal) {
	if (cal == 1) return x + y;
	else if (cal == 2) return x - y;
	else if (cal == 3) return x * y;
	else if (cal == 4) {
		return x * 1.0 / y;
	}
}
string PrintCal(int x, int y, int cal) {
	stringstream ss;
	ss << x;
	if (cal == 1) ss << " + ";
	else if (cal == 2) ss << " - ";
	else if (cal == 3) ss << " * ";
	else if (cal == 4) ss << " : ";
	ss << y << " = ?";
	string s = ss.str();
	return s;
}
int RandomABCD() {
	int b = 1 + rand() % 4;
	return b;
}
string PrintCorrectAnswer(int b, double CorrectAnswer) {
	stringstream ss;
	string s;
	if (b == 1) {
		ss << "A. ";
	}
	else if (b == 2) {
		ss << "B. ";
	}
	else if (b == 3) {
		ss << "C. ";
	}
	else if (b == 4) {
		ss << "D. ";
	}
	
	ss << CorrectAnswer;
	s = ss.str(); return s;
}
string RandomAnswer1(int b, double CorrectAnswer) {
	stringstream ss;
	string s;
	double r=0;
	if (b == 1) {
		r = CorrectAnswer + 1 + rand() % 2;
		ss << "B. ";
	}
	else if (b == 2) {
		r = CorrectAnswer - 2 + rand() % 2;
		ss << "A. ";
	}
	else if (b == 3) {
		r = CorrectAnswer - 4 + rand() % 2;
		ss << "A. ";
	}
	else if (b == 4) {
		r = CorrectAnswer - 6 + rand() % 2;
		ss << "A. ";
	}
	
	ss <<  r;
	s = ss.str();
	return s;
}
string RandomAnswer2(int b, double CorrectAnswer) {
	stringstream ss;
	string s;
	double r=0;
	if (b == 1) {
		r = CorrectAnswer + 3 + rand() % 2;
		ss << "C. ";
	}
	else if (b == 2) {
		r = CorrectAnswer + 1 + rand() % 2;
		ss << "C. ";
	}
	else if (b == 3) {
		r = CorrectAnswer - 2 + rand() % 2;
		ss << "B. ";
	}
	else if (b == 4) {
		r = CorrectAnswer - 4 + rand() % 2;
		ss << "B. ";
	}
	
	ss << r;
	s = ss.str();
	return s;
}
string RandomAnswer3(int b, double CorrectAnswer) {
	stringstream ss;
	string s;
	double r=0;
	if (b == 1) {
		r = CorrectAnswer + 5 + rand() % 2;
		ss << "D. ";
	}
	else if (b == 2) {
		r = CorrectAnswer + 3 + rand() % 2;
		ss << "D. ";
	}
	else if (b == 3) {
		r = CorrectAnswer + 1 + rand() % 2;
		ss << "D. ";
	}
	else if (b == 4) {
		r = CorrectAnswer - 2 + rand() % 2;
		ss << "C. ";
	}
	
	ss << r;
	s = ss.str();
	return s;
}
string QuestionNumber(int &lv) {
	stringstream ss;
	string s;
	ss << "Question " << lv << " :";
	s = ss.str();
	return s;
}

SDL_Renderer* renderer;
//SDL_Texture* loadTexture(string filePath, SDL_Renderer* renderer);
SDL_Texture* loadTexture(string filePath, SDL_Renderer* renderer) {
	SDL_Surface* loadIMG = nullptr;
	SDL_Texture* texture = nullptr;
	loadIMG = SDL_LoadBMP(filePath.c_str());
	if (loadIMG == NULL) {
		cout << "Error img";
	}
	else {
		texture = SDL_CreateTextureFromSurface(renderer, loadIMG);
		if (texture == NULL) {
			cout << "Error sur";
		}
	}
	SDL_FreeSurface(loadIMG); //Tốn bộ nhớ phải free
	return texture;
}

void textRender(int x, int y, int size, string str, SDL_Renderer* renderer) {
	TTF_Font* font = TTF_OpenFont("Sand.TTF", size);
	SDL_Color color = { 255, 255, 255, 255 };
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, str.c_str(), color);
	SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect textRect;
	textRect.x = x;
	textRect.y = y;
	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);
	SDL_FreeSurface(textSurface);
	SDL_RenderCopy(renderer, text, NULL, &textRect);
	SDL_DestroyTexture(text);
}
void Setup(int b, string ranswer1, string ranswer2, string ranswer3, string s, string s0) {
	textRender(310, 125, 88, s.c_str(), renderer);
	if (b == 1) {
		textRender(400, 440, 45, ranswer1.c_str(), renderer);
		textRender(85, 620, 45, s0.c_str(), renderer);
		textRender(725, 620, 45, ranswer2.c_str(), renderer);
		textRender(400, 790, 45, ranswer3.c_str(), renderer);
	}
	if (b == 2) {
		textRender(400, 440, 45, s0.c_str(), renderer);
		textRender(85, 620, 45, ranswer1.c_str(), renderer);
		textRender(725, 620, 45, ranswer2.c_str(), renderer);
		textRender(400, 790, 45, ranswer3.c_str(), renderer);
	}
	if (b == 3) {
		textRender(400, 440, 45, ranswer2.c_str(), renderer);
		textRender(85, 620, 45, ranswer1.c_str(), renderer);
		textRender(725, 620, 45, s0.c_str(), renderer);
		textRender(400, 790, 45, ranswer3.c_str(), renderer);
	}
	if (b == 4) {
		textRender(400, 440, 45, ranswer2.c_str(), renderer);
		textRender(85, 620, 45, ranswer1.c_str(), renderer);
		textRender(725, 620, 45, ranswer3.c_str(), renderer);
		textRender(400, 790, 45, s0.c_str(), renderer);
	}
}
void waitUntilKeyPressed()
{
	SDL_Event e;
	while (true) {
		if (SDL_WaitEvent(&e) != 0 &&
			(e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
			return;
		SDL_Delay(100);
	}
}

int main(int argc, char* argv[]) {
	
	SDL_Window* window = nullptr;
	SDL_Surface* windowSurface = nullptr;
	SDL_Surface* imageSurface = nullptr;
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	//initSDL(window, renderer, 800, 709, "FastCalculation_byVuDucLong(StormUET)");
	if (SDL_Init(SDL_INIT_VIDEO) < 0) cout << "Video Error: " << SDL_GetError() << endl;
	else
	{
		window = SDL_CreateWindow("FastCalculation_byVuDucLong(StormUET)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 886, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
			SDL_RENDERER_PRESENTVSYNC);
		if (window == NULL) cout << " WindowCreation Error" << SDL_GetError() << endl;
		if (renderer == NULL) cout << " WindowCreation Error" << SDL_GetError() << endl;
		SDL_RenderSetLogicalSize(renderer, 1000, 886);
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		cout << "Error: " << Mix_GetError() << endl;
	Mix_Music* bgm = Mix_LoadMUS("BackgroundMS.mp3");
	Mix_Chunk* soundEffect = Mix_LoadWAV("Clap.wav");
	if (!Mix_PlayingMusic()) Mix_PlayMusic(bgm, -1);
	else if (Mix_PausedMusic()) Mix_ResumeMusic();
	else Mix_PauseMusic();

	SDL_RenderClear(renderer);

	SDL_Texture* BGTexture;
	int textureWidth, textureHeight;
	BGTexture = loadTexture("BackgroundBTLL.BMP", renderer);
	SDL_QueryTexture(BGTexture, NULL, NULL, &textureWidth, &textureHeight);
	SDL_Rect player;
	player.x = 0;
	player.y = 0;
	player.w = textureWidth;
	player.h = textureHeight;

	SDL_Rect backGround;
	backGround.x = 0;
	backGround.y = 0;
	backGround.w = 1000;
	backGround.h = 886;
	SDL_RenderCopy(renderer, BGTexture, &player, &backGround);
	SDL_RenderPresent(renderer);
	
	SDL_Delay(2000);

	
	srand(time(NULL));

	
	double extratime = 0;
	int lv = 1;
	int x = RandomX(lv);
	int cal = RandomCal();
	int y = RandomY(cal, lv);
	double answer = CorrectAnswer(x, y, cal);
	cout << x << " " << y << " " << cal << " " << answer << endl;
	string s = PrintCal(x, y, cal);
	int b = RandomABCD();
	string s0 = PrintCorrectAnswer(b, answer);
	cout << b << " " << s0 << endl;
	cout << s << endl;
	string ranswer1 = RandomAnswer1(b, answer);
	string ranswer2 = RandomAnswer2(b, answer);
	string ranswer3 = RandomAnswer3(b, answer);
	cout << ranswer1 << endl << ranswer2 << endl << ranswer3 << endl;
	cout << endl;
	SDL_RenderClear(renderer);
	BGTexture = loadTexture("BTLL01.BMP", renderer);
	SDL_RenderCopy(renderer, BGTexture, &player, &backGround);
	
	int c = 0;

	Setup(b, ranswer1, ranswer2, ranswer3, s, s0);

	SDL_RenderPresent(renderer);

	SDL_Event e;
	while (1) {
		if (TTF_Init() < 0)
			cout << "Error TTF: " << TTF_GetError() << endl;
		
		BGTexture = loadTexture("BTLL01.BMP", renderer);
		SDL_RenderCopy(renderer, BGTexture, &player, &backGround);		
		Setup(b, ranswer1, ranswer2, ranswer3, s, s0);

		string QuestionNumbers = QuestionNumber(lv);
		textRender (20, 10, 30, QuestionNumbers.c_str() , renderer);

		int X = SDL_GetTicks() / 1000;
		int TimeLimit = 15 - X + 2 + extratime;
		
		textRender(850, 10, 30, "Time: ", renderer);
		textRender(950, 10, 30, to_string(TimeLimit), renderer);

		SDL_RenderPresent(renderer);
		
		if (TimeLimit <= 0) break;
		SDL_Delay(100);
		
			
		if (SDL_PollEvent(&e) == 0) continue;
		if (e.type == SDL_QUIT) break;
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			case SDLK_ESCAPE: break;
			case SDLK_LEFT: if (b == 1) c = 1;
						  else c = 2;
				Mix_PlayChannel(-1, soundEffect, 0);
				break;
			case SDLK_RIGHT: if (b == 3) c = 1;
						   else c = 2;
				Mix_PlayChannel(-1, soundEffect, 0);
				break;
			case SDLK_DOWN: if (b == 4) c = 1;
						  else c = 2;
				Mix_PlayChannel(-1, soundEffect, 0);
				break;
			case SDLK_UP: if (b == 2) c = 1;
						else c = 2;
				Mix_PlayChannel(-1, soundEffect, 0);
				break;
			default:;
			}
		}
		if (c == 1) { lv += 1;
			x = RandomX(lv);
			cal = RandomCal();
			y = RandomY(cal, lv);
			answer = CorrectAnswer(x, y, cal);
			cout << x << " " << y << " " << cal << " " << answer << endl;
			s = PrintCal(x, y, cal);
			b = RandomABCD();
			s0 = PrintCorrectAnswer(b, answer);
			cout << b << " " << s0 << endl;
			cout << s << endl;
			ranswer1 = RandomAnswer1(b, answer);
			ranswer2 = RandomAnswer2(b, answer);
			ranswer3 = RandomAnswer3(b, answer);
			cout << ranswer1 << endl << ranswer2 << endl << ranswer3 << endl;
			cout << endl;
			SDL_RenderClear(renderer);	
			extratime += 3;
		}
		if (c == 2) { break; }
		c = 0;	
	}

	waitUntilKeyPressed();
	Mix_FreeChunk(soundEffect);
	Mix_FreeMusic(bgm);
	bgm = nullptr;
	soundEffect = nullptr;
	SDL_FreeSurface(imageSurface);
	imageSurface = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;
	windowSurface = nullptr;
	//waitUntilKeyPressed();
	Mix_Quit();
	SDL_Quit();
	return 0;
	//	system("pause");
}
