#include "MaqEstados.h"
#include "Raton.h"

void MaqEstados::dibuja() {
	switch (estado) {
	case PINICIO:
		estado = IDLEBLANCO;
		break;

	case IDLEBLANCO:
		tablero.dibujar();
		break;

	case IDLENEGRO:
		tablero.dibujar();
		break;

	case MOVE:
		tablero.dibujar();
		break;

	default:
		estado = IDLEBLANCO;
		break;
	}
}

void MaqEstados::tecla() {

}

void MaqEstados::raton(int boton, int estado, int x, int y) {
	switch (estado) {
	case IDLEBLANCO:
	case IDLENEGRO:
	case MOVE:

		break;

	default:
		break;
	}

}