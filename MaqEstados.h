#pragma once

#include "Tablero.h"
#include "Camara.h"
#include "ListaPiezas.h"
#include "ETSIDI.h"

class MaqEstados {
	enum Estado { PINICIO, IDLEBLANCO, IDLENEGRO, MOVEBLANCO, MOVENEGRO, FINBLANCO, FINNEGRO } estado{};
	EstadoRey estadoRey{};

	Tablero tablero;

	Camara camara;

public:
	// Inicializador
	MaqEstados();

	//void dibujaPiezas() { piezasBlancas.dibuja(); piezasNegras.dibuja(); };
	//void muevePiezas() { piezasBlancas.mueve(); piezasNegras.mueve(); };

	void dibuja();
	void tecla(unsigned char tecla);
	void raton(int boton, int estado, int x, int y);
	void timer();
};

