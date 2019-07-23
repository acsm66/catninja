#pragma once

#include <SDL.h>

class FrameTimer {
public:
	FrameTimer(int fps) : _fps(fps), _frameTime(1000/fps) {
		reset();
	}

	void waitNextFrame() {
		Uint32 now = SDL_GetTicks();
		if (now <= _nextFrameTime) {
			//SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "####Frame: [%d], Delay: [%d]####", _frameCount, (_nextFrameTime - now));
			SDL_Delay(_nextFrameTime - now);
		}

		_nextFrameTime += _frameTime;
		++_frameCount;

		if (_frameCount > _fps) {
			reset();
		}
	}

private:
	void reset() {
		//SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "####Reset####");
		_frameCount = 1;
		_nextFrameTime = SDL_GetTicks() + _frameTime;
	}

	int _fps;
	int _frameTime;
	int _frameCount;
	Uint32 _nextFrameTime;
	
};
