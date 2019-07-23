#include "stdafx.h"

#include "AnimacaoPOC.h"
#include "AnimacaoPOCException.h"

int main(int argc, char **argv) {
	try {
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Animacao POC Versao 0.1");

		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Inicializando SDL");
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			std::ostringstream ss;
			ss << "Falha ao inicializar SDL : [" << SDL_GetError() << "]";
			throw AnimacaoPOCException(ss.str());
		}

		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Inicializando SDL/IMG");
		int imgFlags = IMG_INIT_PNG;
		if (IMG_Init(imgFlags) != imgFlags) {
			std::ostringstream ss;
			ss << "Falha ao inicializar SDL/IMG: [" << IMG_GetError() << "]";
			throw AnimacaoPOCException(ss.str());
		}

		AnimacaoPOC poc(640, 480);
		poc.init();
		poc.run();
	} catch (AnimacaoPOCException &e) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", e.what());
	}

	IMG_Quit();
	SDL_Quit();

	SDL_Delay(5000);

	return 0;
}
