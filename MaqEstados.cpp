#include "MaqEstados.h"
#include "Raton.h"
#include "freeglut.h"

MaqEstados::MaqEstados() {
	camara.ojo = { 0, -100, 100 };
	camara.direccion = { 0, 0, 0 };
	camara.arriba = { 0, 0, 1 };
	camara.actualiza();

	piezasBlancas.inicializarBlanco();
	piezasNegras.inicializarNegro();

	piezasBlancas.asignarPosMundo(tablero);
	piezasNegras.asignarPosMundo(tablero);
}

void MaqEstados::dibuja() {
	switch (estado) {
	case PINICIO:
		estado = IDLEBLANCO;
		break;

	case IDLEBLANCO:
		//camara.ojo = { 0, -100, 100 };
		camara.actualiza();
		tablero.dibujar();
		dibujaPiezas();

		break;

	case IDLENEGRO:
		//camara.ojo = { 0, 100, 100 };
		camara.actualiza();
		tablero.dibujar();
		dibujaPiezas();

		break;

	case MOVE:
		tablero.dibujar();
		break;

	default:
		break;
	}
}

void MaqEstados::tecla() {
	switch (estado) {
	case IDLEBLANCO:
	case IDLENEGRO:
	case MOVE:
		
		break;

	default:
		break;
	}
}

void MaqEstados::raton(int boton, int e, int x, int y) {
	if (e == 0) {
		switch (estado) {
		case IDLEBLANCO:
			tablero.seleccionRaton(Raton::MouseHandler(boton, estado, x, y));
			estado = IDLENEGRO;
			break;

		case IDLENEGRO:
			tablero.seleccionRaton(Raton::MouseHandler(boton, estado, x, y));
			estado = IDLEBLANCO;
			break;

		case MOVE:
			tablero.seleccionRaton(Raton::MouseHandler(boton, estado, x, y));
			break;

		default:
			break;
		}
	}
}

void MaqEstados::timer() {
	switch (estado) {
	case IDLEBLANCO:
	case IDLENEGRO:
	case MOVE:
		muevePiezas();
		break;

	default:
		break;
	}
}