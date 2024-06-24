#include "MaqEstados.h"
#include "Raton.h"
#include "freeglut.h"

MaqEstados::MaqEstados() {
	camara.ojo = { 0, -100, 100 };
	camara.direccion = { 0, 0, 0 };
	camara.arriba = { 0, 0, 1 };
	camara.actualiza();

	tablero.ponPiezas();

	//piezasBlancas.inicializarBlanco();
	//piezasNegras.inicializarNegro();

	//piezasBlancas.asignarPosMundo(tablero);
	//piezasNegras.asignarPosMundo(tablero);
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
		tablero.dibujaPiezas();
		//dibujaPiezas();

		break;

	case IDLENEGRO:
		//camara.ojo = { 0, 100, 100 };
		camara.actualiza();
		tablero.dibujar();
		tablero.dibujaPiezas();
		//dibujaPiezas();

		break;

	case MOVEBLANCO:
		tablero.dibujar();
		tablero.dibujaPiezas();
		break;

	case MOVENEGRO:
		tablero.dibujar();
		tablero.dibujaPiezas();
		break;

	default:
		break;
	}
}

void MaqEstados::tecla() {
	switch (estado) {
	case IDLEBLANCO:
	case IDLENEGRO:
	case MOVEBLANCO:
	case MOVENEGRO:
		
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

		case MOVEBLANCO:
			tablero.seleccionRaton(Raton::MouseHandler(boton, estado, x, y));
			break;

		case MOVENEGRO:
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
	case MOVEBLANCO:
	case MOVENEGRO:
		//muevePiezas();
		break;

	default:
		break;
	}
}