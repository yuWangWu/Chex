#pragma once

#include "Vector2d.h"
#include "Color.h"
#include "Hexagono.h"

class Baldosa {
public:
	Hexagono posicion;
	Coordenadas coordenadas;
	Color color;

	// Posicion baldosas colindantes
	Coordenadas bArriba, bAbajo, bIzqArriba, bIzqAbajo, bDerArriba, bDerAbajo; // Tocan lados
	Coordenadas bEsqIzquierda, bEsqDerecha, bEsqIzqArriba, bEsqIzqAbajo, bEsqDerArriba, bEsqDerAbajo; // "Tocan" esquinas
	Coordenadas bCaballoDerArriba, bCaballoDerAbajo, bCaballoIzqArriba, bCaballoIzqAbajo,
		bCaballoEsqIzqArrArriba, bCaballoEsqIzqArrAbajo, bCaballoEsqDerArrArriba, bCaballoEsqDerArrAbajo,
		bCaballoEsqDerAbjArriba, bCaballoEsqDerAbjAbajo, bCaballoEsqIzqAbjArriba, bCaballoEsqIzqAbjAbajo; // Lo que sea que haga el caballo
};