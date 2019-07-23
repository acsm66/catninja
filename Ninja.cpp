#include "stdafx.h"
#include "Ninja.h"

static const std::string SPRITE_SHEET_PATH("/resources/ninjacorrendo.png");
static const int NUM_SPRITES = 6;
static const int SPRITE_WIDTH = 50;
static const int SPRITE_HEIGHT = 50;

Ninja::Ninja(int maxSpeed, int maxPaceLevel, int xSize) : _spriteSheet(), _maxSpeed(maxSpeed), _maxPaceLevel(maxPaceLevel),
	_paceStep(maxSpeed/maxPaceLevel), _xSize(xSize), _curSpeed(0), _curPos(), _prevDir(DIR_NONE), _curDir(DIR_NONE),
	_startDir(0) {}

void Ninja::init(SDL_Renderer *renderer, int initX, int initY) {
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Carregando sprite sheet em [%s]", SPRITE_SHEET_PATH.c_str());
	_spriteSheet.init(renderer, SPRITE_SHEET_PATH, NUM_SPRITES, SPRITE_WIDTH, SPRITE_HEIGHT);
	_curPos = { initX,  initY, SPRITE_WIDTH, SPRITE_HEIGHT };
}

void Ninja::setDirection(Direction dir) {
	if (dir != _curDir) {
		_startDir = SDL_GetTicks();
	}
	_prevDir = _curDir;
	_curDir = dir;
}

void Ninja::refresh() {
	bool invert = false;
	if (_curDir == DIR_LEFT) {
		invert = true;
	} else if (_curDir == DIR_RIGHT) {
		invert = false;
	} else {
		if (_prevDir == DIR_LEFT) {
			invert = true;
		} else if (_prevDir == DIR_RIGHT) {
			invert = false;
		}
	}

	calculateSpeed();
	if (_curSpeed > 0) {
		calculatePosition();
		_spriteSheet.renderNext(_curPos, invert);
	} else {
		_spriteSheet.renderCurrent(_curPos, invert);
	}
}

void Ninja::calculateSpeed() {
	Uint32 now = SDL_GetTicks();
	if (_curDir == DIR_NONE) {
		if (now > (_startDir + 50)) {
			_curSpeed -= _paceStep;
			_startDir = SDL_GetTicks();
		}
	} else {
		if (now > (_startDir + 100)) {
			_curSpeed += _paceStep;
			_startDir = SDL_GetTicks();
		}
	}

	if (_curSpeed > _maxSpeed) {
		_curSpeed = _maxSpeed;
	} else if (_curSpeed < 0) {
		_curSpeed = 0;
	}

	if (_curSpeed > 0) {
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "_curSpeed: [%d]", _curSpeed);
	}
}

void Ninja::calculatePosition() {
	if (_curDir == DIR_RIGHT) {
		int curPosCandidate = _curPos.x + _curSpeed;
		if (curPosCandidate > _xSize) {
			_curPos.x = -30; // @todo gambiarra!! Cria area invisivel.
		} else {
			_curPos.x = _curPos.x + _curSpeed;
		}
	} else if (_curDir == DIR_LEFT) {
		int curPosCandidate = _curPos.x - _curSpeed;
		if (curPosCandidate < -30) {
			_curPos.x = _xSize + 30; // @todo gambiarra!! Cria area invisivel.
		} else {
			_curPos.x = _curPos.x - _curSpeed;
		}
	} else {
		if (_prevDir == DIR_RIGHT) {
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "PREV_DIR_RIGHT");
			int curPosCandidate = _curPos.x + _curSpeed;
			if (curPosCandidate > _xSize) {
				_curPos.x = -30; // @todo gambiarra!! Cria area invisivel.
			} else {
				_curPos.x = _curPos.x + _curSpeed;
			}
		} else if (_prevDir == DIR_LEFT) {
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "PREV_DIR_LEFT");
			int curPosCandidate = _curPos.x - _curSpeed;
			if (curPosCandidate < -30) {
				_curPos.x = _xSize + 30; // @todo gambiarra!! Cria area invisivel.
			} else {
				_curPos.x = _curPos.x - _curSpeed;
			}
		}
	}
}
