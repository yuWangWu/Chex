#pragma once

#include "freeglut.h"
#include "Tablero.h"
#include "Raton.h"
#include "Camara.h"
#include "ETSIDI.h"
#include <string>

class MaqEstados {
	enum Estado { PINICIO, IDLEBLANCO, IDLENEGRO, MOVEBLANCO, MOVENEGRO, PPROMOCIONBLANCO, PPROMOCIONNEGRO, FINBLANCO, FINNEGRO } estado{};
	EstadoRey estadoRey{};

	Tablero tablero;

	Camara camara;

	

	bool vistaElevada{ false };

	std::string CaminoInicio = "StandarStart.txt";

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

