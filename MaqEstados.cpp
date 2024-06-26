#include "MaqEstados.h"
#include "Raton.h"
#include "freeglut.h"

MaqEstados::MaqEstados() : 
	camara({ 0, -80, 125 }, { 0, 0, 0 }, { 0, 0, 1 }) {
	tablero.ponPiezas();
}

void MaqEstados::dibuja() {
	switch (estado) {
	case PINICIO:
		estado = IDLEBLANCO;
		break;

	case IDLEBLANCO:
		camara.ojo = { 0, -80, 110 };
		camara.actualiza();
		tablero.dibujar();
		tablero.dibujaPiezas();

		break;

	case IDLENEGRO:
		camara.ojo = { 0, 80, 110 };
		camara.actualiza();
		tablero.dibujar();
		tablero.dibujaPiezas();

		break;

	case MOVEBLANCO:
		camara.actualiza();
		tablero.dibujar();
		tablero.dibujaPiezas();
		break;

	case MOVENEGRO:
		camara.actualiza();
		tablero.dibujar();
		tablero.dibujaPiezas();
		break;

	case FINBLANCO:
		camara.ojo = { 80, 80, 110 };
		camara.actualiza();
		tablero.dibujar();
		tablero.dibujaPiezas();
		break;

	case FINNEGRO:
		camara.ojo = { 80, 80, 110 };
		camara.actualiza();
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
	case FINBLANCO:
	case FINNEGRO:
		
		break;

	default:
		break;
	}
}

void MaqEstados::raton(int boton, int e, int x, int y) {
	if (e == 0) {
		Vector3Ddouble coordPinchado = Raton::MouseHandler(boton, estado, x, y);
		switch (estado) {
		case IDLEBLANCO:
			if (tablero.seleccionRaton(Raton::MouseHandler(boton, estado, x, y), true))
				estado = MOVEBLANCO;
			break;

		case IDLENEGRO:
			if (tablero.seleccionRaton(Raton::MouseHandler(boton, estado, x, y), false))
				estado = MOVENEGRO;
			break;

		case MOVEBLANCO:
			if (tablero.intercambiaPiezas(tablero.pos2baldosa(coordPinchado.x, coordPinchado.y))) {
				estadoRey = tablero.checkJaque(true);
				if (estadoRey == NADA)
					estado = IDLENEGRO;
				else if (estadoRey == JAQUE)
					estado = IDLENEGRO;
				else if (estadoRey == JAQUEMATE)
					estado = FINBLANCO;
				ETSIDI::play("gameData/sonidos/impacto.wav");
			}
			else
				estado = IDLEBLANCO;
			break;

		case MOVENEGRO:
			if (tablero.intercambiaPiezas(tablero.pos2baldosa(coordPinchado.x, coordPinchado.y))) {
				estadoRey = tablero.checkJaque(false);
				if (estadoRey == NADA)
					estado = IDLEBLANCO;
				else if (estadoRey == JAQUE)
					estado = IDLEBLANCO;
				else if (estadoRey == JAQUEMATE)
					estado = FINNEGRO;
				ETSIDI::play("gameData/sonidos/impacto.wav");
			}
			else
				estado = IDLENEGRO;
			break;

		case FINBLANCO:
		case FINNEGRO:
			break;

		default:
			break;
		}
	}
}

void MaqEstados::timer() {
	double angulo;
	switch (estado) {
	case IDLEBLANCO:
	case IDLENEGRO:
	case MOVEBLANCO:
	case MOVENEGRO:
	case FINBLANCO:
	case FINNEGRO:
		//muevePiezas();
		break;

	default:
		break;
	}
}