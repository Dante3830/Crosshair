#pragma once
#include "stdafx.h"
#include "Enemigo.h"
#include "PlayerCrosshair.h"
using namespace sf;
using namespace std;

class Juego {
private:

	// Texture fondo
	// Sprite backg

	RenderWindow *_wnd;
	PlayerCrossHair *_player;
	Enemigo* _enemigos;
	Text _puntaje;
	Font _fuente;
	int _puntos;
	void _actualizarPuntaje() {
		char pts[100];
		_itoa_s(_puntos, pts, 10); //Transforma el entero a string
		_puntaje.setString(pts);
	}

public:

	Juego() {
		_wnd = new RenderWindow(VideoMode(800, 600), "Crosshair");
		_player = new PlayerCrossHair();
		_enemigos = new Enemigo[10];
		_puntos = 0;

		// fondo.loadFromFile("West.png");
		// backg.setTexture(fondo);

		_fuente.loadFromFile("IBMPlexMono-Bold.ttf");
		_puntaje.setFont(_fuente);
		_puntaje.setPosition(0.0f, 0.0f);
		_puntaje.setCharacterSize(50.0f);
		_puntaje.setColor(Color::Black);

		_actualizarPuntaje();
	}

	void Loop() {
		while (_wnd->isOpen()) {
			procesarEventos();
			Actualizar();
			Dibujar();
		}
	}

	void procesarEventos() {
		//Procesamos los eventos que ocurran
		Event evt;
		while (_wnd->pollEvent(evt)) {
			switch (evt.type) {
			case Event::Closed:
				_wnd->close();
				break;
			case Event::MouseMoved:
				_player->Posicionar(evt.mouseMove.x, evt.mouseMove.y);
				break;
			case Event::MouseButtonPressed:
				if (evt.mouseButton.button == Mouse::Button::Left)
					Disparar();
				break;
			}
		}
	}

	void Actualizar() {
		//Actualizamos la posicion del crosshair
		for (size_t i = 0; i < 10; i++) {
			_enemigos[i].Actualizar(_wnd);
		}
	}

	void Disparar() {
		//Chequeamos colisiones con el disparo
		Vector2f playerPos = _player->obtenerPosicion();
		for (int i = 0; i < 10; i++) {
			if (_enemigos[i].estaActivo()) {
				if (_enemigos[i].estaEncima(playerPos.x, playerPos.y)) {
					_enemigos[i].Derrotar();
					_puntos++;
				}
			}
		}
		_actualizarPuntaje();
	}

	void Dibujar() {
		_wnd->clear(Color::White);
		//Dibujar los elementos de juego
		// _wnd->draw(backg);

		for (int i = 0; i < 10; i++) { //Se dibujan los enemigos
			if (_enemigos[i].estaActivo())
				_enemigos[i].Dibujar(_wnd);
		}

		_wnd->draw(_puntaje); //El puntaje
		_player->Dibujar(_wnd); //La mira
		_wnd->display();
	}

	~Juego() {
		delete[] _enemigos;
		delete _player;
		delete _wnd;
	}
};
