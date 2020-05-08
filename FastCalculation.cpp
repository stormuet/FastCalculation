#include <iostream>
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
double CorrectAnswer( int x, int y, int cal) {
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
SDL_Renderer* rendererX;
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
	textRender(280, 200, 88, s.c_str(), renderer);
	if (b == 1) {
		textRender(360, 460, 45, ranswer1.c_str(), renderer);
		textRender(45, 610, 45, s0.c_str(), renderer);
		textRender(685, 610, 45, ranswer2.c_str(), renderer);
		textRender(360, 760, 45, ranswer3.c_str(), renderer);
	}
	if (b == 2) {
		textRender(360, 460, 45, s0.c_str(), renderer);
		textRender(45, 610, 45, ranswer1.c_str(), renderer);
		textRender(685, 610, 45, ranswer2.c_str(), renderer);
		textRender(360, 760, 45, ranswer3.c_str(), renderer);
	}
	if (b == 3) {
		textRender(360, 460, 45, ranswer2.c_str(), renderer);
		textRender(45, 610, 45, ranswer1.c_str(), renderer);
		textRender(685, 610, 45, s0.c_str(), renderer);
		textRender(360, 760, 45, ranswer3.c_str(), renderer);
	}
	if (b == 4) {
		textRender(360, 460, 45, ranswer2.c_str(), renderer);
		textRender(45, 610, 45, ranswer1.c_str(), renderer);
		textRender(685, 610, 45, ranswer3.c_str(), renderer);
		textRender(360, 760, 45, s0.c_str(), renderer);
	}
}
void waitUntilKeyPressed()
{
	SDL_Event e;
	while (true) {
		if (SDL_WaitEvent(&e) != 0 &&
			(e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
			return;
		SDL_Delay(400);
	}
}
int ChooseMode(Mix_Chunk *soundEffect, int c) {
	SDL_Event event;
	while (1) {
		if (SDL_PollEvent(&event) == 0) continue;
		if (event.type == SDL_QUIT) break;

		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE: break;
			case SDLK_LEFT: return 15;
				Mix_PlayChannel(-1, soundEffect, 0);
				break;
			case SDLK_RIGHT: return 5;
				Mix_PlayChannel(-1, soundEffect, 0);
				break;
			case SDLK_DOWN: return 0;
				Mix_PlayChannel(-1, soundEffect, 0);
				break;
			case SDLK_UP: return 10;
				Mix_PlayChannel(-1, soundEffect, 0);
				break;
			default:;
			}
		}
	}
}

int RestartOrExit(Mix_Chunk* soundEffect) {
	SDL_Event event;
	while (1) {
		if (SDL_PollEvent(&event) == 0) continue;
		if (event.type == SDL_QUIT) break;

		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN: return 0;
				Mix_PlayChannel(-1, soundEffect, 0);
				break;
			case SDLK_UP: return 1;
				Mix_PlayChannel(-1, soundEffect, 0);
				break;
			default:;
			}
		}
	}
}

int TURN = 1;
int main(int argc, char* argv[]) {
	//Create Window
	SDL_Window* window = nullptr;
	SDL_Surface* windowSurface = nullptr;
	SDL_Surface* imageSurface = nullptr;
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
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
	//Create Music Song and Music Chunk
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		cout << "Error: " << Mix_GetError() << endl;
	Mix_Music* bgm = Mix_LoadMUS("BackgroundMS.mp3");
	Mix_Chunk* soundEffect = Mix_LoadWAV("Clap.wav");
	
	//Create Texture
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
	/*SDL_Delay(2000);*/
	waitUntilKeyPressed();
	SDL_RenderClear(renderer);
	
	

	//Start Music
	if (!Mix_PlayingMusic()) Mix_PlayMusic(bgm, -1);
	else if (Mix_PausedMusic()) Mix_ResumeMusic();
	else Mix_PauseMusic();
	SDL_RenderClear(renderer);
	
	//Keys to play
	BGTexture = loadTexture("BTLL03.BMP", renderer);
	SDL_RenderCopy(renderer, BGTexture, &player, &backGround);
	SDL_RenderPresent(renderer);
	waitUntilKeyPressed();
	
	int c = 0;
	do {
		//Choosing mode
		BGTexture = loadTexture("BTLL02.BMP", renderer);
		SDL_RenderCopy(renderer, BGTexture, &player, &backGround);
		SDL_RenderPresent(renderer);


		int mode = ChooseMode(soundEffect, c);
		if (mode == 0) break;
		
		SDL_RenderClear(renderer);
		//Loading BG Ques
		BGTexture = loadTexture("BTLL01.BMP", renderer);
		SDL_RenderCopy(renderer, BGTexture, &player, &backGround);

		//Set up Ques-Ans
		srand(time(NULL));
		double extratime = 0;
		int lv = 1;
		int x = RandomX(lv);
		int cal = RandomCal();
		int y = RandomY(cal, lv);
		double answer = CorrectAnswer(x, y, cal);
		string s = PrintCal(x, y, cal);
		int b = RandomABCD();
		string s0 = PrintCorrectAnswer(b, answer);
		string ranswer1 = RandomAnswer1(b, answer);
		string ranswer2 = RandomAnswer2(b, answer);
		string ranswer3 = RandomAnswer3(b, answer);

		
		double start = SDL_GetTicks() / 1000;
		Setup(b, ranswer1, ranswer2, ranswer3, s, s0);
		//currentTick = getTicks()
		//SDL_RenderPresent(renderer);
		SDL_FreeSurface(imageSurface);
		imageSurface = nullptr;
		SDL_Event e;
		int Score = 0;
		double timepause = 0;
		double timepauseX = 0;
		double timepausebefore = 0;
		double timepauseafter = 0;
		int u = 0;
		//int pause = 0;
		while (1) {
			if (TTF_Init() < 0)
				cout << "Error TTF: " << TTF_GetError() << endl;
			BGTexture = loadTexture("BTLL01.BMP", renderer);
			SDL_RenderCopy(renderer, BGTexture, &player, &backGround);
			Setup(b, ranswer1, ranswer2, ranswer3, s, s0);

			string QuestionNumbers = QuestionNumber(lv);
			textRender(20, 10, 30, QuestionNumbers.c_str(), renderer);
			
			//Timer
			double X = SDL_GetTicks() / 1000;

			if (u == 1) {
				timepauseafter = SDL_GetTicks() / 1000;
				timepause = timepauseafter - timepausebefore;
				timepauseX += timepause;
			}

			cout << timepausebefore << endl;
			cout << timepauseafter << endl;
			
			
			int TimeLimit = mode - X + start + extratime + timepauseX;
			
			cout << TimeLimit << " = " << mode << " - " << X << " + " << start << " + " << extratime << " + " << timepauseafter << " - " << timepausebefore << endl;
			cout << timepause << endl;
			
			
			//Print Score and Time
			textRender(850, 10, 30, "Time: ", renderer);
			textRender(950, 10, 30, to_string(TimeLimit), renderer);
			textRender(450, 10, 30, "Score: ", renderer);
			textRender(550, 10, 30, to_string(Score), renderer);
			
			SDL_RenderPresent(renderer);

			u = 0;
			if (TimeLimit <= 0) break;
			SDL_Delay(400);

			
			if (SDL_PollEvent(&e) == 0) continue;
			if (e.type == SDL_QUIT) break;
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_0: while (1) {
					timepausebefore = SDL_GetTicks() / 1000;
					u = 1; 
					BGTexture = loadTexture("Gameover.BMP", renderer);
					SDL_RenderCopy(renderer, BGTexture, &player, &backGround);
					textRender(350, 100, 80, "Paused", renderer);
					textRender(370, 230, 40, "Time: ", renderer);
					textRender(550, 230, 40, to_string(TimeLimit), renderer);
					textRender(370, 310, 40, "Score: ", renderer);
					//textRender(600, 230, 40, "s", renderer);
					textRender(550, 310, 40, to_string(Score), renderer);

					SDL_RenderPresent(renderer);

					waitUntilKeyPressed();
					SDL_RenderClear(renderer);
					break;
					};
			
					cout << "Tang " << timepausebefore << endl;
					break;
				
				//case SDLK_1: break;
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
			
			if (c == 1) {
				lv += 1;
				Score += 10;
				x = RandomX(lv);
				cal = RandomCal();
				y = RandomY(cal, lv);
				answer = CorrectAnswer(x, y, cal);
				s = PrintCal(x, y, cal);
				b = RandomABCD();
				s0 = PrintCorrectAnswer(b, answer);
				ranswer1 = RandomAnswer1(b, answer);
				ranswer2 = RandomAnswer2(b, answer);
				ranswer3 = RandomAnswer3(b, answer);
				SDL_RenderClear(renderer);
				extratime += 2;
			}
			if (c == 2) { break; }
			c = 0;
		}
		SDL_RenderClear(renderer);
		//Print Score (end)
		BGTexture = loadTexture("Gameover.BMP", renderer);
		SDL_RenderCopy(renderer, BGTexture, &player, &backGround);
		textRender(350, 250, 80, "Score: ", renderer);
		textRender(600, 250, 80, to_string(Score), renderer);
		SDL_RenderPresent(renderer);

		waitUntilKeyPressed();
		//Restart or Exit
		SDL_RenderClear(renderer);
		BGTexture = loadTexture("Gameover.BMP", renderer);
		SDL_RenderCopy(renderer, BGTexture, &player, &backGround);
		textRender(350, 200, 80, "Play Again", renderer);
		textRender(450, 400, 80, "Exit", renderer);
		SDL_RenderPresent(renderer);
		TURN = RestartOrExit(soundEffect);
		c = 0;
		Score = 0;
	} while (TURN==1);

	Mix_FreeChunk(soundEffect);
	Mix_FreeMusic(bgm);
	bgm = nullptr;
	soundEffect = nullptr;
	SDL_FreeSurface(imageSurface);
	imageSurface = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;
	windowSurface = nullptr;
	Mix_Quit();
	SDL_Quit();
	return 0;
}
