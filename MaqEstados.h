#pragma once
#include "Tablero.h"

class MaqEstados {
	enum Estado { PINICIO, IDLEBLANCO, IDLENEGRO, MOVE } estado{};
	Tablero tablero;

public:
	void dibuja();
	void tecla();
	void raton(int boton, int estado, int x, int y);
};

