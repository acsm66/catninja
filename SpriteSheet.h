#pragma once

#include "stdafx.h"

class SpriteSheet {
public:
	SpriteSheet() : _renderer(NULL), _texture(NULL), _numSprites(0), _spriteWidth(0), _spriteHeight(0), _curSprite(0) {}
	virtual ~SpriteSheet();

	void init(SDL_Renderer *renderer, const std::string &path, int numSprites, int width, int height);
	void renderCurrent(const SDL_Rect &dstRect, bool invert = false);
	void renderNext(const SDL_Rect &dstRect, bool invert = false);

private:
	void getCurSprite(SDL_Rect &spritePos);
	inline void nextSprite();

	SDL_Renderer *_renderer;
	SDL_Texture *_texture;

	int _numSprites;
	int _spriteWidth;
	int _spriteHeight;

	int _curSprite;
};
