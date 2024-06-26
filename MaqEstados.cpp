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
		camara.setOjo({ 0, 0, 20 });
		camara.setArriba({ 0, 1, 0 });
		camara.actualiza();

		ETSIDI::setTextColor(0, 0.7, 1);
		ETSIDI::setFont("gameData/fuentes/Bitwise.ttf", 80);
		ETSIDI::printxy("CHEX, Ajedrez hexagonal", -35, 15);
		
		ETSIDI::setFont("gameData/fuentes/Bitwise.ttf", 30);
		ETSIDI::printxy("Pulse J para jugar en modo 2 jugadores", -35, 6);
		ETSIDI::printxy("Pulse K para jugar en modo 1 jugador", -35, 3);
		
		ETSIDI::setFont("gameData/fuentes/Bitwise.ttf", 10);
		ETSIDI::printxy("Trabajo de la asignatura Informática Industrial y Comunicaciones impartido en la ETSIDI-UPM", -35, -15);
		ETSIDI::printxy("Yu Wang Wu 2024", -35, -16);
		break;

	case IDLEBLANCO:
		camara.ojo = { 0, -80, 110 };
		camara.setArriba({ 0, 0, 1 });
		camara.actualiza();
		tablero.dibujar();
		tablero.dibujaPiezas();

		break;

	case IDLENEGRO:
		camara.ojo = { 0, 80, 110 };
		camara.setArriba({ 0, 0, 1 });
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
		camara.setOjo({ 0, 0, 20 });
		camara.setArriba({ 0, 1, 0 });
		camara.actualiza();

		ETSIDI::setTextColor(0, 0.7, 1);
		ETSIDI::setFont("gameData/fuentes/Bitwise.ttf", 80);
		ETSIDI::printxy("Ganan las piezas BLANCAS", -35, 15);

		ETSIDI::setFont("gameData/fuentes/Bitwise.ttf", 30);
		ETSIDI::printxy("Pulse f para volver a la pantalla de inicio", -35, 3);
		break;

	case FINNEGRO:
		camara.setOjo({ 0, 0, 20 });
		camara.setArriba({ 0, 1, 0 });
		camara.actualiza();

		ETSIDI::setTextColor(0, 0.7, 1);
		ETSIDI::setFont("gameData/fuentes/Bitwise.ttf", 80);
		ETSIDI::printxy("Ganan las piezas Negras", -35, 15);

		ETSIDI::setFont("gameData/fuentes/Bitwise.ttf", 30);
		ETSIDI::printxy("Pulse f para volver a la pantalla de inicio", -35, 3);
		break;

	default:
		break;
	}
}

void MaqEstados::tecla(unsigned char tecla) {
	switch (estado) {
	case PINICIO:
		if (tecla == 'j')
			estado = IDLEBLANCO;
		if (tecla == 'k')
			estado = IDLEBLANCO;
		break;

	case IDLEBLANCO:
	case IDLENEGRO:
	case MOVEBLANCO:
	case MOVENEGRO:
	case FINBLANCO:
		if (tecla == 'f') {
			tablero.quitaPiezas();
			tablero.ponPiezas();
			estado = PINICIO;
		}
	case FINNEGRO:
		if (tecla == 'f') {
			tablero.quitaPiezas();
			tablero.ponPiezas();
			estado = PINICIO;
		}
		break;

	default:
		break;
	}
}

void MaqEstados::raton(int boton, int e, int x, int y) {
	if (e == 0) {
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
			if (tablero.intercambiaPiezas(Raton::MouseHandler(boton, estado, x, y))) {
				estadoRey = tablero.checkJaque(false);
				if (estadoRey == JAQUE)
					estado = FINNEGRO;
				estadoRey = tablero.checkJaque(true);
				if (estadoRey == NADA)
					estado = IDLENEGRO;
				else if (estadoRey == JAQUE)
					estado = IDLENEGRO;
				else if (estadoRey == JAQUEMATE)
					estado = FINBLANCO;
				ETSIDI::play("gameData/sonidos/Move.wav");
			}
			else
				estado = IDLEBLANCO;
			break;

		case MOVENEGRO:
			if (tablero.intercambiaPiezas(Raton::MouseHandler(boton, estado, x, y))) {
				estadoRey = tablero.checkJaque(true);
				if (estadoRey == JAQUE)
					estado = FINBLANCO;
				estadoRey = tablero.checkJaque(false);
				if (estadoRey == NADA)
					estado = IDLEBLANCO;
				else if (estadoRey == JAQUE)
					estado = IDLEBLANCO;
				else if (estadoRey == JAQUEMATE)
					estado = FINNEGRO;
				ETSIDI::play("gameData/sonidos/Move.wav");
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