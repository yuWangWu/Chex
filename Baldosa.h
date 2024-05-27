#pragma once

#include <vector>

#include "VectoresUtiles.h"
#include "Color.h"
#include "Hexagono.h"

class Baldosa {
public:
	Hexagono hexagono;
	Vector2Dint identificador;
	Color color, colorDisplay;

	// Posicion baldosas colindantes
	Vector2Dint bArriba, bAbajo, bIzqArriba, bIzqAbajo, bDerArriba, bDerAbajo;								// Tocan lados
	Vector2Dint bEsqIzquierda, bEsqDerecha, bEsqIzqArriba, bEsqIzqAbajo, bEsqDerArriba, bEsqDerAbajo;		// "Tocan" esquinas
	Vector2Dint bCaballoDerArriba, bCaballoDerAbajo, bCaballoIzqArriba, bCaballoIzqAbajo,
		bCaballoEsqIzqArrArriba, bCaballoEsqIzqArrAbajo, bCaballoEsqDerArrArriba, bCaballoEsqDerArrAbajo,
		bCaballoEsqDerAbjArriba, bCaballoEsqDerAbjAbajo, bCaballoEsqIzqAbjArriba, bCaballoEsqIzqAbjAbajo;	// Lo que sea que haga el caballo

public:
	// Finders
	Vector2Dint findbArriba(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero);
	Vector2Dint findbAbajo(Baldosa actual);
	Vector2Dint findbIzqArriba(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero);
	Vector2Dint findbIzqAbajo(Baldosa actual);
	Vector2Dint findbDerArriba(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero);
	Vector2Dint findbDerAbajo(Baldosa actual);
	Vector2Dint findbEsqIzquierda(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero);
	Vector2Dint findbEsqDerecha(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero);

	Vector2Dint findbEsqIzqArriba(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero);
	Vector2Dint findbEsqIzqAbajo(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero);
	Vector2Dint findbEsqDerArriba(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero);
	Vector2Dint findbEsqDerAbajo(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero);

	Vector2Dint findbCaballoDerArriba(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero);
	Vector2Dint findbCaballoDerAbajo(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero);
	Vector2Dint findbCaballoIzqArriba(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero);
	Vector2Dint findbCaballoIzqAbajo(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero);
	Vector2Dint findbCaballoEsqIzqArrArriba(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero);
	Vector2Dint findbCaballoEsqIzqArrAbajo(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero);
	Vector2Dint findbCaballoEsqDerArrArriba(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero);
	Vector2Dint findbCaballoEsqDerArrAbajo(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero);
	Vector2Dint findbCaballoEsqIzqAbjArriba(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero);
	Vector2Dint findbCaballoEsqIzqAbjAbajo(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero);
	Vector2Dint findbCaballoEsqDerAbjArriba(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero);
	Vector2Dint findbCaballoEsqDerAbjAbajo(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero);

	void findPosicionesTodas(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero);
};