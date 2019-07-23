#include "stdafx.h"
#include "AnimacaoPOC.h"
#include "AnimacaoPOCException.h"
#include "FrameTimer.h"

AnimacaoPOC::AnimacaoPOC(int windowWidth, int windowHeight) : _windowWidth(windowWidth), _windowHeight(windowHeight),
	_window(NULL), _renderer(NULL), _ninja(6, 3, windowWidth), _accelerationRate(0), _finish(false) {}

void AnimacaoPOC::init() {
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Inicializando janela");
	_window = SDL_CreateWindow("AnimacaoPOC", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _windowWidth, _windowHeight,
		SDL_WINDOW_SHOWN);
	if (_window == NULL) {
		std::ostringstream ss;
		ss << "Falha ao criar janela: [" << SDL_GetError() << "]";
		throw AnimacaoPOCException(ss.str());
	}

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Inicializando renderizador");
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (_renderer == NULL) {
		std::ostringstream ss;
		ss << "Falha ao criar renderizador: [" << SDL_GetError() << "]";
		throw AnimacaoPOCException(ss.str());
	}

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Carregando Ninja");
	_ninja.init(_renderer, 10, 240);
}

void AnimacaoPOC::run() {
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Iniciando loop de execucao");

	SDL_ShowWindow(_window);

	SDL_Event event;
	FrameTimer timer(30);
	while (!_finish) {
		try {
			SDL_SetRenderDrawColor(_renderer, 0xff, 0xff, 0xff, 0);
			SDL_RenderClear(_renderer);

			if (SDL_PollEvent(&event) != 0) {
				switch (event.type) {
					case SDL_QUIT:
						_finish = true;
						break;

					case SDL_KEYDOWN:
					{
						SDL_Keycode keycode = event.key.keysym.sym;
						if (keycode == SDLK_LEFT) {
							_ninja.setDirection(Ninja::DIR_LEFT);
						} else if (keycode == SDLK_RIGHT) {
							_ninja.setDirection(Ninja::DIR_RIGHT);
						}
						break;
					}

					case SDL_KEYUP:
						_ninja.setDirection(Ninja::DIR_NONE);
						break;
				}
			}

			_ninja.refresh();

			SDL_RenderPresent(_renderer);
			timer.waitNextFrame();
		} catch (AnimacaoPOCException &e) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erro no loop de execucao: [%s]", e.what());
			_finish = true;
		}
	}
}
