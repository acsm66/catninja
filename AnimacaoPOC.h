#pragma once

#include "stdafx.h"
#include "Ninja.h"

class AnimacaoPOC {
public:
	AnimacaoPOC(int windowWidth, int windowHeight);
	void init();
	void run();

private:
	void updateAccelerationRate(int inc);
	void adjustMoveLimits(SDL_Rect &dst);
	bool moveHandler(const SDL_Event &event, SDL_Rect &dst);

	int _windowWidth;
	int _windowHeight;

	SDL_Window *_window;
	SDL_Renderer *_renderer;
	
	Ninja _ninja;
	int _accelerationRate;

	bool _finish;
};
