#pragma once
#include "stdafx.h"

class Enemigo {

private:
	Texture _enemyTex;
	Sprite _enemySpr;
	bool _estaVivo;
	bool _estaVisible;
	Clock _clock;
	float _tiempoVisible;
	float _tiempoApagado;

	Vector2f _randomPos(Vector2u maxPos) {
		Vector2f random((float)(rand() % maxPos.x), (float)(rand() % maxPos.y));
		return random;
	}

public:
	Enemigo() {
		_enemyTex.loadFromFile("Images/enemigo.png");
		_enemySpr.setTexture(_enemyTex);
		_enemySpr.setScale(0.4f, 0.4f);
		_estaVivo = true;
		_estaVisible = false;
		_tiempoVisible = 0.5f;
		_tiempoApagado = 0.5f;
	}

	bool estaVivo() {
		return _estaVivo;
	}

	bool estaActivo() {
		return _estaVivo && _estaVisible;
	}

	bool estaEncima(float x, float y) {
		FloatRect bounds = _enemySpr.getGlobalBounds();
		return bounds.contains(x, y);
	}

	void Derrotar() {
		_estaVivo = false;
	}

	void Dibujar(RenderWindow* _wnd) {
		_wnd->draw(_enemySpr);
	}

	void Actualizar(RenderWindow* _wnd) {
		if (!_estaVivo) {
			return;
		}

		if (!_estaVisible) { //Tiramos una probabilidad para ver si lo activamos
			if (_clock.getElapsedTime().asSeconds() > _tiempoApagado) {
				_clock.restart();
				if (rand() % 100 < 25) {
					_estaVisible = true;
					_enemySpr.setPosition(_randomPos(_wnd->getSize()));
				}
			}
		} else {
			if (_clock.getElapsedTime().asSeconds() > _tiempoVisible) {
				_estaVisible = false;
				_clock.restart();
			}
		}
	}
};
