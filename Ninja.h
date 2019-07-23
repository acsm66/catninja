#pragma once

#include "stdafx.h"

#include "SpriteSheet.h"

class Ninja {
public:
	enum Direction { DIR_NONE, DIR_RIGHT, DIR_LEFT };

	Ninja(int maxSpeed, int maxPaceLevel, int xSize);

	void init(SDL_Renderer *renderer, int initX, int initY);
	void setDirection(Direction dir);
	void refresh();

private:
	void calculateSpeed();
	void calculatePosition();

	SpriteSheet _spriteSheet;
	int _maxSpeed;
	int _maxPaceLevel;
	int _paceStep;
	int _xSize;
	int _curSpeed;
	SDL_Rect _curPos;
	Direction _prevDir;
	Direction _curDir;
	Uint32 _startDir;
};
