#pragma once

#include "freeglut.h"
#include "Tablero.h"
#include "Raton.h"
#include "Camara.h"
#include "ETSIDI.h"
#include <string>

class MaqEstados {
public:
	enum Estado { PINICIO, IDLEBLANCO, IDLENEGRO, MOVEBLANCO, MOVENEGRO, PPROMOCIONBLANCO, PPROMOCIONNEGRO, FINBLANCO, FINNEGRO, PAUSA } estado{};
	EstadoRey estadoRey{};

	Tablero tablero;

	Camara camara;

	

	bool vistaElevada{ false };

private:
	std::string CaminoInicio = "StandarStart.txt";
	bool estadoant = 0; // indica el estado anterior para el menu de pausa 0 negras 1 blancas

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

