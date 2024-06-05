#pragma once

#include "Tablero.h"
#include "Camara.h"
#include "ListaPiezas.h"

class MaqEstados {
	enum Estado { PINICIO, IDLEBLANCO, IDLENEGRO, MOVE } estado{};
	
	Tablero tablero;

	Camara camara;

	ListaPiezas piezasBlancas, piezasNegras;

public:
	// Inicializador
	MaqEstados();

	void dibujaPiezas() { piezasBlancas.dibuja(); piezasNegras.dibuja(); };
	void muevePiezas() { piezasBlancas.mueve(); piezasNegras.mueve(); };

	void dibuja();
	void tecla();
	void raton(int boton, int estado, int x, int y);
	void timer();
};

