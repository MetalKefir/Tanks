#pragma once
#include<windows.h>
#include<thread>
#include<chrono>
#include<ctime>

enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

enum Direction {
	UP = 1,
	DOWN = 2,
	LEFT = 3,
	RIGHT = 4
};

void SetColor(ConsoleColor text=White, ConsoleColor background = Black)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}


class Coord
{ 
public:
	unsigned short x_;
	unsigned short y_;

	Coord() {

		x_ = 9;
		y_ = 15;
	}

	Coord(unsigned short x, unsigned short y) {

		x_ = x;
		y_ = y;
	}
};

struct TANK
{
	static const unsigned char symbolTank_ = '*';
	static const ConsoleColor colorTank_=Green;
	unsigned short directTank_;
	Coord coordTank_;
};

struct WALL
{
	static const unsigned char symbolWall_ = '#';
	static const ConsoleColor colorWall_=Cyan;
};

struct BULLET
{
	static const unsigned char symbolBullet_ = 167;
	static const ConsoleColor colorBullet_=Red;
	Coord coordBullet_;
};



