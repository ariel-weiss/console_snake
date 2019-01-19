#pragma once
#include <Windows.h>

class Utilities {

public:

	enum Game_States {
		GAME_OVER = 0, GAME_START, GAME_DRAW,
		GAME_WAIT, GAME_RESET
	};
	static const int WIDTH = 75;
	static const int HEIGHT = 20;

	static constexpr COORD START_POS = { (SHORT)(WIDTH / 2), (SHORT)(HEIGHT / 2) };
	
	//Must call this function before using the utilities
	//static void initialize() { 
	//	hConsole_c = GetStdHandle(STD_OUTPUT_HANDLE);
	//}

	//Drawing functions:
	static void drawOn(int x, int y) {
		
		COORD pos = { (SHORT)x, (SHORT)y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}
	static void drawOn(const COORD& pos) {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}
	static void drawChar(int x, int y, const char& c) {
		drawOn(x, y);
		std::cout << c;
	}
	static void drawChar(const COORD& pos, const char& c) {
		drawOn(pos);
		std::cout << c;
	}
	static void drawString(int x,int y,const char* str){
		drawOn(x, y);
		std::cout << str;
	}
	static void deleteString(int x, int y,int len) {
		drawOn(x, y);
		std::string str;
		for (int i = 0; i < len; i++) {
			str+= ' ';
		}
		drawString(x, y, str.c_str());
	}
private:
	//static HANDLE hConsole_c;
};
