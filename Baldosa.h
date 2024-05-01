#pragma once

#include "VectoresUtiles.h"
#include "Color.h"
#include "Hexagono.h"

class Baldosa {
public:
	Hexagono hexagono;
	Vector2Dint identificador;
	Color color;

	// Posicion baldosas colindantes
	Vector2Dint bArriba, bAbajo, bIzqArriba, bIzqAbajo, bDerArriba, bDerAbajo; // Tocan lados
	Vector2Dint bEsqIzquierda, bEsqDerecha, bEsqIzqArriba, bEsqIzqAbajo, bEsqDerArriba, bEsqDerAbajo; // "Tocan" esquinas
	Vector2Dint bCaballoDerArriba, bCaballoDerAbajo, bCaballoIzqArriba, bCaballoIzqAbajo,
		bCaballoEsqIzqArrArriba, bCaballoEsqIzqArrAbajo, bCaballoEsqDerArrArriba, bCaballoEsqDerArrAbajo,
		bCaballoEsqDerAbjArriba, bCaballoEsqDerAbjAbajo, bCaballoEsqIzqAbjArriba, bCaballoEsqIzqAbjAbajo; // Lo que sea que haga el caballo
};