#include "stdafx.h"
#include "AnimacaoPOCException.h"
#include "SpriteSheet.h"

SpriteSheet::~SpriteSheet() {
	// nao destroi renderer pois eh so uma referencia
	if (_texture != NULL) {
		SDL_DestroyTexture(_texture);
	}
}

void SpriteSheet::init(SDL_Renderer *renderer, const std::string &path, int numSprites, int width, int height) {
	if (renderer == NULL) {
		throw AnimacaoPOCException("Renderizador invalido");
	}
	_renderer = renderer;

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Carregando textura no arquivo: [%s]", path.c_str());
	_texture = IMG_LoadTexture(renderer, "resources/ninjacorrendo.png");
	if (_texture == NULL) {
		std::ostringstream ss;
		ss << "Falha ao carregar textura: [" << IMG_GetError() << "]";
		throw AnimacaoPOCException(ss.str());
	}

	_numSprites = numSprites;
	_spriteWidth = width;
	_spriteHeight = height;
}

void SpriteSheet::renderCurrent(const SDL_Rect &dstRect, bool invert) {
	SDL_Rect spritePos;
	getCurSprite(spritePos);
	
	if (SDL_RenderCopyEx(_renderer, _texture, &spritePos, &dstRect, 0.0f, NULL,
		(invert ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE)) != 0) {
		std::ostringstream ss;
		ss << "Falha ao carregar renderizar textura: [" << SDL_GetError() << "]";
		throw AnimacaoPOCException(ss.str());
	}
}

void SpriteSheet::renderNext(const SDL_Rect &dstRect, bool invert) {
	renderCurrent(dstRect, invert);
	nextSprite();
}

void SpriteSheet::getCurSprite(SDL_Rect &spritePos) {
	spritePos.x = _curSprite * _spriteWidth;
	spritePos.y = 0;
	spritePos.w = _spriteWidth;
	spritePos.h = _spriteHeight;
}

inline void SpriteSheet::nextSprite() {
	_curSprite = _curSprite == (_numSprites - 1) ? 0 : _curSprite + 1;
	//SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Showing sprite [%d]", _curSprite);
}
