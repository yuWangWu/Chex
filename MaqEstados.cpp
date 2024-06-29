#include "MaqEstados.h"

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

		ETSIDI::setFont("gameData/fuentes/Bitwise.ttf", 20);
		ETSIDI::printxy("Pulse V durante el juego para cambiar de punto de vista", -35, -5);
		
		ETSIDI::setFont("gameData/fuentes/Bitwise.ttf", 10);
		ETSIDI::printxy("Trabajo de la asignatura Informática Industrial y Comunicaciones impartido en la ETSIDI-UPM", -35, -15);
		ETSIDI::printxy("Yu Wang Wu 2024", -35, -16);
		break;

	case IDLEBLANCO:
		if (!vistaElevada)
			camara.setOjo( {0, -80, 110} );
		else
			camara.setOjo( { 0, -30, 110 } );
		camara.setArriba({ 0, 0, 1 });
		camara.actualiza();
		tablero.dibujar();
		tablero.dibujaPiezas();

		break;

	case IDLENEGRO:
		if (!vistaElevada)
			camara.setOjo( { 0, 80, 110 } );
		else
			camara.setOjo( { 0, 30, 110 } );
		camara.setArriba({ 0, 0, 1 });
		camara.actualiza();
		tablero.dibujar();
		tablero.dibujaPiezas();

		break;

	case MOVEBLANCO:
		if (!vistaElevada)
			camara.setOjo( { 0, -80, 110 } );
		else
			camara.setOjo( { 0, -30, 110 } );
		camara.actualiza();
		tablero.dibujar();
		tablero.dibujaPiezas();
		break;

	case MOVENEGRO:
		if (!vistaElevada)
			camara.setOjo( { 0, 80, 110 } );
		else
			camara.setOjo( { 0, 30, 110 } );
		camara.actualiza();
		tablero.dibujar();
		tablero.dibujaPiezas();
		break;

	case PPROMOCIONBLANCO:
	case PPROMOCIONNEGRO:
		camara.setOjo({ 0, 0, 20 });
		camara.setArriba({ 0, 1, 0 });
		camara.actualiza();

		ETSIDI::setFont("gameData/fuentes/Bitwise.ttf", 30);
		ETSIDI::printxy("Pulse R para convertir en reina", -35, 6);
		ETSIDI::printxy("Pulse T para convertir en torre", -35, 3);
		ETSIDI::printxy("Pulse A para convertir en Alfil", -35, 0);
		ETSIDI::printxy("Pulse C para convertir en Caballo", -35, 0);
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
		if (tecla == 'j') {
			vistaElevada = false;
			tablero.resetColores();
			estado = IDLEBLANCO;
		}
		if (tecla == 'k') {
			vistaElevada = false;
			tablero.resetColores();
			estado = IDLEBLANCO;
		}
		break;

	case IDLEBLANCO:
	case IDLENEGRO:
	case MOVEBLANCO:
	case MOVENEGRO:
		if (tecla == 'v')
			if (vistaElevada)
				vistaElevada = false;
			else
				vistaElevada = true;
		break;

	case PPROMOCIONBLANCO:
		if (tecla == 'r')
			tablero.pPeonReina();
		else if (tecla == 't')
			tablero.pPeonTorre();
		else if (tecla == 'a')
			tablero.pPeonAlfil();
		else if (tecla == 'c')
			tablero.pPeonCaballo();
		estadoRey = tablero.checkJaque(true);
		if (estadoRey == JAQUE)
			ETSIDI::play("gameData/sonidos/impacto.wav");
		if (estadoRey == JAQUEMATE) {
			estado = FINBLANCO;
			break;
		}
		estado = IDLENEGRO;
		break;

	case PPROMOCIONNEGRO:
		if (tecla == 'r')
			tablero.pPeonReina();
		else if (tecla == 't')
			tablero.pPeonTorre();
		else if (tecla == 'a')
			tablero.pPeonAlfil();
		else if (tecla == 'c')
			tablero.pPeonCaballo();
		estadoRey = tablero.checkJaque(false);
		if (estadoRey == JAQUE)
			ETSIDI::play("gameData/sonidos/impacto.wav");
		if (estadoRey == JAQUEMATE) {
			estado = FINBLANCO;
			break;
		}
		estado = IDLEBLANCO;
		break;

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
				if (tablero.checkPromoPeon())
					estado = PPROMOCIONBLANCO;
				else estado = IDLENEGRO;
				estadoRey = tablero.checkJaque(true);
				if (estadoRey == JAQUE)
					ETSIDI::play("gameData/sonidos/impacto.wav");
				if (estadoRey == JAQUEMATE) {
					estado = FINBLANCO;
					break;
				}
				ETSIDI::play("gameData/sonidos/Move.wav");
			}
			else
				estado = IDLEBLANCO;
			break;

		case MOVENEGRO:
			if (tablero.intercambiaPiezas(Raton::MouseHandler(boton, estado, x, y))) {
				if (tablero.checkPromoPeon())
					estado = PPROMOCIONNEGRO;
				else estado = IDLEBLANCO;
				estadoRey = tablero.checkJaque(false);
				if (estadoRey == JAQUE)
					ETSIDI::play("gameData/sonidos/impacto.wav");
				if (estadoRey == JAQUEMATE) {
					estado = FINBLANCO;
					break;
				}
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