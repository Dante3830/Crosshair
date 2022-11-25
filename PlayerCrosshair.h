#pragma once
#include "stdafx.h"

class PlayerCrossHair {

	Texture _crossTex;
	Sprite _crossSpr;

public:

	PlayerCrossHair() {
		_crossTex.loadFromFile("Images/crosshair.png");
		_crossSpr.setTexture(_crossTex);
		_crossSpr.setScale(0.1f, 0.1f);
		Vector2u size = _crossTex.getSize();
		_crossSpr.setOrigin(size.x / 2.0f, size.y / 2.0f);
	}

	void Dibujar(RenderWindow* wnd) {
		wnd->draw(_crossSpr);
	}

	void Posicionar(float x, float y) {
		_crossSpr.setPosition(x, y);
	}

	Vector2f obtenerPosicion() {
		return _crossSpr.getPosition();
	}
};
