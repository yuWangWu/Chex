#include <iostream>
#include <fstream>

#include "Tablero.h"
#include "Presets.h"
#include "freeglut.h"
#include "Raton.h"

Tablero::Tablero() {
	int rotadorColoresfilas = 0;
	int rotadorColorescolumnas = 0;
	std::ifstream fileDatosBaldosas("gameData/datosBaldosas.txt");

	// Estructura de los datos del archivo:
	// 1 baldosa por linea.
	// 7 puntos por linea.
	// x y separados por espacios.
	// Orden: centro, aristas comenzando desde la izquierda
	// y continuando en sentido horario.

	if (fileDatosBaldosas.good()) {
		for (int columna = 0; columna < tablero.size(); columna++) {	// Iterador columnas
			for (int fila = 0; fila < tablero[columna].size(); fila++) {
				tablero[columna][fila].identificador.col = columna;
				tablero[columna][fila].identificador.row = fila;

				fileDatosBaldosas >> tablero[columna][fila].hexagono.centro.x
					>> tablero[columna][fila].hexagono.centro.y
					>> tablero[columna][fila].hexagono.lado0.x
					>> tablero[columna][fila].hexagono.lado0.y
					>> tablero[columna][fila].hexagono.lado1.x
					>> tablero[columna][fila].hexagono.lado1.y
					>> tablero[columna][fila].hexagono.lado2.x
					>> tablero[columna][fila].hexagono.lado2.y
					>> tablero[columna][fila].hexagono.lado3.x
					>> tablero[columna][fila].hexagono.lado3.y
					>> tablero[columna][fila].hexagono.lado4.x
					>> tablero[columna][fila].hexagono.lado4.y
					>> tablero[columna][fila].hexagono.lado5.x
					>> tablero[columna][fila].hexagono.lado5.y;

				tablero[columna][fila].findPosicionesTodas(tablero[columna][fila], tablero);

				// Me da un aviso, no se si funciona pero lo dejo por si acaso.
				//tablero[columna][fila].color = (rotadorColores == 0) ? rotadorColores++, grisOscuro :
				//	(rotadorColores == 1) ? rotadorColores++, grisClaro : rotadorColores = 0, blanco;

				if (rotadorColoresfilas == 0)
					tablero[columna][fila].color = grisOscuro, rotadorColoresfilas++;
				else if (rotadorColoresfilas == 1)
					tablero[columna][fila].color = grisClaro, rotadorColoresfilas++;
				else
					tablero[columna][fila].color = blanco, rotadorColoresfilas = 0;

				tablero[columna][fila].colorDisplay = tablero[columna][fila].color;
			}
			if (columna < 5) {
				if (rotadorColorescolumnas == 0)
					rotadorColoresfilas = 1, rotadorColorescolumnas++;
				else if (rotadorColorescolumnas == 1)
					rotadorColoresfilas = 2, rotadorColorescolumnas++;
				else
					rotadorColoresfilas = 0, rotadorColorescolumnas = 0;
			}
			else {
				if (rotadorColorescolumnas == 0)
					rotadorColoresfilas = 2, rotadorColorescolumnas = 2;
				else if (rotadorColorescolumnas == 1)
					rotadorColoresfilas = 0, rotadorColorescolumnas--;
				else 
					rotadorColoresfilas = 1, rotadorColorescolumnas--;
			}

			// Footnote: despues de haber hecho toda la parte de renderizado
			// del tablero en el mismo dia, he de decir que los colores son lo 
			// que mas me han liado.
		}
	}
	else {
		throw std::exception("No se ha podido abrir.");
	}

	fileDatosBaldosas.close();
}

void Tablero::dibujar() const {
	glDisable(GL_LIGHTING);
	// Dibujar todas las baldosas
	for (int columna = 0; columna < tablero.size(); columna++) {
		for (int fila = 0; fila < tablero[columna].size(); fila++) {
			glBegin(GL_POLYGON);
			glColor3ub(tablero[columna][fila].colorDisplay.r, tablero[columna][fila].colorDisplay.g, tablero[columna][fila].colorDisplay.b);
			glVertex3d(tablero[columna][fila].hexagono.lado0.x, tablero[columna][fila].hexagono.lado0.y, 0);
			glVertex3d(tablero[columna][fila].hexagono.lado1.x, tablero[columna][fila].hexagono.lado1.y, 0);
			glVertex3d(tablero[columna][fila].hexagono.lado2.x, tablero[columna][fila].hexagono.lado2.y, 0);
			glVertex3d(tablero[columna][fila].hexagono.lado3.x, tablero[columna][fila].hexagono.lado3.y, 0);
			glVertex3d(tablero[columna][fila].hexagono.lado4.x, tablero[columna][fila].hexagono.lado4.y, 0);
			glVertex3d(tablero[columna][fila].hexagono.lado5.x, tablero[columna][fila].hexagono.lado5.y, 0);
			glEnd();
		}
	}
	glEnable(GL_LIGHTING);
}


void Tablero::resetColores() {
	for (int columna = 0; columna < tablero.size(); columna++) 
		for (int fila = 0; fila < tablero[columna].size(); fila++) 
			tablero[columna][fila].colorDisplay = tablero[columna][fila].color;
}


void Tablero::ponPiezas() {
	// Piezas blancas (true)
	delete tablero[1][0].pieza;
	tablero[1][0].pieza = new Peon(tablero[1][0].hexagono.centro, true);
	delete tablero[2][1].pieza;
	tablero[2][1].pieza = new Peon(tablero[2][1].hexagono.centro, true);
	delete tablero[3][2].pieza;
	tablero[3][2].pieza = new Peon(tablero[3][2].hexagono.centro, true);
	delete tablero[4][3].pieza;
	tablero[4][3].pieza = new Peon(tablero[4][3].hexagono.centro, true);
	delete tablero[5][4].pieza;
	tablero[5][4].pieza = new Peon(tablero[5][4].hexagono.centro, true);
	delete tablero[6][3].pieza;
	tablero[6][3].pieza = new Peon(tablero[6][3].hexagono.centro, true);
	delete tablero[7][2].pieza;
	tablero[7][2].pieza = new Peon(tablero[7][2].hexagono.centro, true);
	delete tablero[8][1].pieza;
	tablero[8][1].pieza = new Peon(tablero[8][1].hexagono.centro, true);
	delete tablero[9][0].pieza;
	tablero[9][0].pieza = new Peon(tablero[9][0].hexagono.centro, true);

	delete tablero[2][0].pieza;
	tablero[2][0].pieza = new Torre(tablero[2][0].hexagono.centro, true);
	delete tablero[8][0].pieza;
	tablero[8][0].pieza = new Torre(tablero[8][0].hexagono.centro, true);
	
	delete tablero[5][0].pieza;
	tablero[5][0].pieza = new Alfil(tablero[5][0].hexagono.centro, true);
	delete tablero[5][1].pieza;
	tablero[5][1].pieza = new Alfil(tablero[5][1].hexagono.centro, true);
	delete tablero[5][2].pieza;
	tablero[5][2].pieza = new Alfil(tablero[5][2].hexagono.centro, true);
	
	delete tablero[3][0].pieza;
	tablero[3][0].pieza = new Caballo(tablero[3][0].hexagono.centro, true, true);
	delete tablero[7][0].pieza;
	tablero[7][0].pieza = new Caballo(tablero[7][0].hexagono.centro, true, true);

	delete tablero[4][0].pieza;
	tablero[4][0].pieza = new Rey(tablero[4][0].hexagono.centro, true);
	delete tablero[6][0].pieza;
	tablero[6][0].pieza = new Reina(tablero[6][0].hexagono.centro, true);

	// Piezas negras (false)
	delete tablero[1][6].pieza;
	delete tablero[2][6].pieza;
	delete tablero[3][6].pieza;
	delete tablero[4][6].pieza;
	delete tablero[5][6].pieza;
	delete tablero[6][6].pieza;
	delete tablero[7][6].pieza;
	delete tablero[8][6].pieza;
	delete tablero[9][6].pieza;
	for (int numero : {1, 2, 3, 4, 5, 6, 7, 8, 9})
		tablero[numero][6].pieza = new Peon(tablero[numero][6].hexagono.centro, false);

	delete tablero[2][7].pieza;
	tablero[2][7].pieza = new Torre(tablero[2][7].hexagono.centro, false);
	delete tablero[8][7].pieza;
	tablero[8][7].pieza = new Torre(tablero[8][7].hexagono.centro, false);

	delete tablero[5][10].pieza;
	tablero[5][10].pieza = new Alfil(tablero[5][10].hexagono.centro, false);
	delete tablero[5][9].pieza;
	tablero[5][9].pieza = new Alfil(tablero[5][9].hexagono.centro, false);
	delete tablero[5][8].pieza;
	tablero[5][8].pieza = new Alfil(tablero[5][8].hexagono.centro, false);

	delete tablero[3][8].pieza;
	tablero[3][8].pieza = new Caballo(tablero[3][8].hexagono.centro, false, false);
	delete tablero[7][8].pieza;
	tablero[7][8].pieza = new Caballo(tablero[7][8].hexagono.centro, false, false);

	delete tablero[4][9].pieza;
	tablero[4][9].pieza = new Rey(tablero[4][9].hexagono.centro, false);
	delete tablero[6][9].pieza;
	tablero[6][9].pieza = new Reina(tablero[6][9].hexagono.centro, false);
}

void Tablero::dibujaPiezas() {
	for (int i = 0; i < tablero.size(); i++) {
		for (int j = 0; j < tablero[i].size(); j++) {
			if (tablero[i][j].pieza->getTipo() != VACIO) {
				tablero[i][j].pieza->dibuja();
			}
		}
	}
}

// Desarrollo, borrar despues
bool Tablero::seleccionRaton(Vector3Ddouble _posicion, bool _equipo) {
	resetColores();
	Equipo equipo = (_equipo) ? BLANCO : NEGRO;

	Vector2Dint baldosaSeleccionada = pos2baldosa(_posicion.x, _posicion.y);
	if (baldosaSeleccionada.existe && (tablero[baldosaSeleccionada.col][baldosaSeleccionada.row].pieza->getEquipo() == equipo)) {
		switch (tablero[baldosaSeleccionada.col][baldosaSeleccionada.row].pieza->getTipo()) {
		case PEON:
			caminosPeon(baldosaSeleccionada);
			break;
		
		case ALFIL:
			caminosAlfil(baldosaSeleccionada);
			break;

		case TORRE:
			caminosTorre(baldosaSeleccionada);
			break;

		case CABALLO:
			caminosCaballo(baldosaSeleccionada);
			break;

		case REINA:
			caminosReina(baldosaSeleccionada);
			break;

		case REY:
			caminosRey(baldosaSeleccionada);
			break;

		default:
			return false;
			break;
		}
		toggleColorB(baldosaSeleccionada, verdeClaro);
		return true;
	}
	else
		return false;
}

void Tablero::caminosPeon(Vector2Dint _bSeleccionada) {
	Vector2Dint bCursor;
	if (tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo() == BLANCO) { // Blanco
		bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bIzqArriba;
		if ((bCursor.existe) &&
			(tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo()) &&
			(tablero[bCursor.col][bCursor.row].pieza->getTipo() != VACIO))
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
		bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bDerArriba;
		if ((bCursor.existe) &&
			(tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo()) &&
			(tablero[bCursor.col][bCursor.row].pieza->getTipo() != VACIO))
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);

		if (tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getMovido()) { // No primer movimiento
			bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bArriba;
			if ((bCursor.existe) &&
				(tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO))
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		}
		else { // Primer movimiento
			bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bArriba;
			if ((bCursor.existe) &&
				(tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO))
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
			else
				return;
			bCursor = tablero[bCursor.col][bCursor.row].bArriba;
			if ((bCursor.existe) &&
				(tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO))
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
			tablero[bCursor.col][bCursor.row].pieza->setMovido(true);
		}
	}
	else { // Negro
		bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bIzqAbajo;
		if ((bCursor.existe) &&
			(tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo()) &&
			(tablero[bCursor.col][bCursor.row].pieza->getTipo() != VACIO))
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
		bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bDerAbajo;
		if ((bCursor.existe) &&
			(tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo()) &&
			(tablero[bCursor.col][bCursor.row].pieza->getTipo() != VACIO))
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);

		if (tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getMovido()) { // No primer movimiento
			bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bAbajo;
			if ((bCursor.existe) &&
				(tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO))
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		}
		else { // Primer movimiento
			bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bAbajo;
			if ((bCursor.existe) &&
				(tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO))
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
			else
				return;
			bCursor = tablero[bCursor.col][bCursor.row].bAbajo;
			if ((bCursor.existe) &&
				(tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO))
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
			tablero[bCursor.col][bCursor.row].pieza->setMovido(true);
		}
	}
}

void Tablero::caminosAlfil(Vector2Dint _bSeleccionada) {
	Vector2Dint bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].identificador;
	// Caminos derecha
	do {
		bCursor = tablero[bCursor.col][bCursor.row].bEsqIzquierda;
		if (bCursor.existe) {
			if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO) {
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
			}
			else {
				if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
					toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
				break;
			}
		}
		else {
			break;
		}
	} while (true);

	// Caminos esquina izquierda arriba
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].identificador;
	do {
		bCursor = tablero[bCursor.col][bCursor.row].bEsqIzqArriba;
		if (bCursor.existe) {
			if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO) {
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
			}
			else {
				if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
					toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
				break;
			}
		}
		else {
			break;
		}
	} while (true);

	// Caminos esquina derecha arriba
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].identificador;
	do {
		bCursor = tablero[bCursor.col][bCursor.row].bEsqDerArriba;
		if (bCursor.existe) {
			if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO) {
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
			}
			else {
				if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
					toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
				break;
			}
		}
		else {
			break;
		}
	} while (true);

	// Caminos derecha
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].identificador;
	do {
		bCursor = tablero[bCursor.col][bCursor.row].bEsqDerecha;
		if (bCursor.existe) {
			if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO) {
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
			}
			else {
				if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
					toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
				break;
			}
		}
		else {
			break;
		}
	} while (true);

	// Caminos esquina derecha abajo
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].identificador;
	do {
		bCursor = tablero[bCursor.col][bCursor.row].bEsqDerAbajo;
		if (bCursor.existe) {
			if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO) {
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
			}
			else {
				if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
					toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
				break;
			}
		}
		else {
			break;
		}
	} while (true);

	// Caminos esquina izquierda abajo
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].identificador;
	do {
		bCursor = tablero[bCursor.col][bCursor.row].bEsqIzqAbajo;
		if (bCursor.existe) {
			if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO) {
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
			}
			else {
				if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
					toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
				break;
			}
		}
		else {
			break;
		}
	} while (true);
}

void Tablero::caminosTorre(Vector2Dint _bSeleccionada) {
	Vector2Dint bCursor;
	// Caminos izquierda arriba
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].identificador;
	do {
		bCursor = tablero[bCursor.col][bCursor.row].bIzqArriba;
		if (bCursor.existe) {
			if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO) {
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
			}
			else {
				if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
					toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
				break;
			}
		}
		else {
			break;
		}
	} while (true);

	// Caminos arriba
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].identificador;
	do {
		bCursor = tablero[bCursor.col][bCursor.row].bArriba;
		if (bCursor.existe) {
			if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO) {
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
			}
			else {
				if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
					toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
				break;
			}
		}
		else {
			break;
		}
	} while (true);

	// Caminos derecha arriba
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].identificador;
	do {
		bCursor = tablero[bCursor.col][bCursor.row].bDerArriba;
		if (bCursor.existe) {
			if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO) {
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
			}
			else {
				if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
					toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
				break;
			}
		}
		else {
			break;
		}
	} while (true);

	// Caminos derrecha abajo
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].identificador;
	do {
		bCursor = tablero[bCursor.col][bCursor.row].bDerAbajo;
		if (bCursor.existe) {
			if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO) {
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
			}
			else {
				if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
					toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
				break;
			}
		}
		else {
			break;
		}
	} while (true);

	// Caminos abajo
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].identificador;
	do {
		bCursor = tablero[bCursor.col][bCursor.row].bAbajo;
		if (bCursor.existe) {
			if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO) {
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
			}
			else {
				if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
					toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
				break;
			}
		}
		else {
			break;
		}
	} while (true);

	// Caminos izquierda abajo
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].identificador;
	do {
		bCursor = tablero[bCursor.col][bCursor.row].bIzqAbajo;
		if (bCursor.existe) {
			if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO) {
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
			}
			else {
				if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
					toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
				break;
			}
		}
		else {
			break;
		}
	} while (true);
}

void Tablero::caminosCaballo(Vector2Dint _bSeleccionada) {
	Vector2Dint bCursor;
	// Caminos esquina izquierda
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bCaballoIzqAbajo;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
	}
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bCaballoIzqArriba;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
	}

	// Caminos esquina izquierda arriba
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bCaballoEsqIzqArrAbajo;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
	}
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bCaballoEsqIzqArrArriba;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
	}

	// Caminos esquina derecha arriba
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bCaballoEsqDerArrArriba;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
	}	
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bCaballoEsqDerArrAbajo;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
	}

	// Caminos esquina derecha
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bCaballoDerArriba;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
	}
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bCaballoDerAbajo;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
	}

	// Caminos esquina derecha abajo
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bCaballoEsqDerAbjArriba;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
	}
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bCaballoEsqDerAbjAbajo;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
	}

	// Caminos esquina izquierda abajo
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bCaballoEsqIzqAbjAbajo;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
	}
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bCaballoEsqIzqAbjArriba;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
	}
}

void Tablero::caminosReina(Vector2Dint _bSeleccionada) {
	caminosAlfil(_bSeleccionada);
	caminosTorre(_bSeleccionada);
}

void Tablero::caminosRey(Vector2Dint b) {
	Vector2Dint bCursor;
	bCursor = tablero[b.col][b.row].bEsqIzquierda;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[b.col][b.row].pieza->getEquipo())
				toggleColorB(tablero[bCursor.col][bCursor.col].identificador, rojo);
	}
	bCursor = tablero[b.col][b.row].bIzqArriba;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[b.col][b.row].pieza->getEquipo())
				toggleColorB(tablero[bCursor.col][bCursor.col].identificador, rojo);
	}
	bCursor = tablero[b.col][b.row].bEsqIzqArriba;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[b.col][b.row].pieza->getEquipo())
				toggleColorB(tablero[bCursor.col][bCursor.col].identificador, rojo);
	}
	bCursor = tablero[b.col][b.row].bArriba;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[b.col][b.row].pieza->getEquipo())
				toggleColorB(tablero[bCursor.col][bCursor.col].identificador, rojo);
	}
	bCursor = tablero[b.col][b.row].bEsqDerArriba;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[b.col][b.row].pieza->getEquipo())
				toggleColorB(tablero[bCursor.col][bCursor.col].identificador, rojo);
	}
	bCursor = tablero[b.col][b.row].bEsqDerecha;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[b.col][b.row].pieza->getEquipo())
				toggleColorB(tablero[bCursor.col][bCursor.col].identificador, rojo);
	}
	bCursor = tablero[b.col][b.row].bDerAbajo;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[b.col][b.row].pieza->getEquipo())
				toggleColorB(tablero[bCursor.col][bCursor.col].identificador, rojo);
	}
	bCursor = tablero[b.col][b.row].bEsqDerAbajo;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[b.col][b.row].pieza->getEquipo())
				toggleColorB(tablero[bCursor.col][bCursor.col].identificador, rojo);
	}
	bCursor = tablero[b.col][b.row].bAbajo;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[b.col][b.row].pieza->getEquipo())
				toggleColorB(tablero[bCursor.col][bCursor.col].identificador, rojo);
	}
	bCursor = tablero[b.col][b.row].bEsqIzqAbajo;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[b.col][b.row].pieza->getEquipo())
				toggleColorB(tablero[bCursor.col][bCursor.col].identificador, rojo);
	}
	bCursor = tablero[b.col][b.row].bIzqAbajo;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[b.col][b.row].pieza->getEquipo())
				toggleColorB(tablero[bCursor.col][bCursor.col].identificador, rojo);
	}
}


bool Tablero::hayReyBlanco() {
	for (int col = 0; col < tablero.size(); col++) {
		for (int row = 0; row < tablero[col].size(); row++) {
			if ((tablero[col][row].pieza->getTipo() == REY) && (tablero[col][row].pieza->getEquipo() == BLANCO))
				return true;
		}
	}
	return false;
}

bool Tablero::hayReyNegro() {
	for (int col = 0; col < tablero.size(); col++) {
		for (int row = 0; row < tablero[col].size(); row++) {
			if ((tablero[col][row].pieza->getTipo() == REY) && (tablero[col][row].pieza->getEquipo() == NEGRO))
				return true;
		}
	}
	return false;
}


bool Tablero::intercambiaPiezas(Vector2Dint _bDestino) {
	// Validez del movimiento
	if (!((tablero[_bDestino.col][_bDestino.row].colorDisplay == rojo) || (tablero[_bDestino.col][_bDestino.row].colorDisplay == cyan))) {
		resetColores();
		return false;
	}

	// Obtener pieza a mover
	Vector2Dint bOrigen{};
	for (int col = 0; col < tablero.size(); col++) {
		for (int row = 0; row < tablero[col].size(); row++) {
			if (tablero[col][row].colorDisplay == verdeClaro)
				bOrigen = tablero[col][row].identificador;
		}
	}

	// Tipo de movimiento
	if (tablero[_bDestino.col][_bDestino.row].colorDisplay == cyan) { // Movimiento normal
		tablero[bOrigen.col][bOrigen.row].pieza->setPosMundoAnterior(tablero[bOrigen.col][bOrigen.row].pieza->getPosMundo());
		
		Pieza* pAux = tablero[bOrigen.col][bOrigen.row].pieza;
		tablero[bOrigen.col][bOrigen.row].pieza = tablero[_bDestino.col][_bDestino.row].pieza;
		tablero[_bDestino.col][_bDestino.row].pieza = pAux;

		tablero[_bDestino.col][_bDestino.row].pieza->setPosMundo(tablero[_bDestino.col][_bDestino.row].hexagono.centro);
		tablero[_bDestino.col][_bDestino.row].pieza->setSincronia(false);
		tablero[_bDestino.col][_bDestino.row].pieza->mover();

		resetColores();
		return true;
	}
	else { // Movimiento come
		tablero[bOrigen.col][bOrigen.row].pieza->setPosMundoAnterior(tablero[bOrigen.col][bOrigen.row].pieza->getPosMundo());

		delete tablero[_bDestino.col][_bDestino.row].pieza;
		tablero[_bDestino.col][_bDestino.row].pieza = tablero[bOrigen.col][bOrigen.row].pieza;
		tablero[bOrigen.col][bOrigen.row].pieza = new bVacio({ -1, -1 }, true);

		tablero[_bDestino.col][_bDestino.row].pieza->setPosMundo(tablero[_bDestino.col][_bDestino.row].hexagono.centro);
		tablero[_bDestino.col][_bDestino.row].pieza->setSincronia(false);
		tablero[_bDestino.col][_bDestino.row].pieza->mover();

		resetColores();
		return true;
	}
}


Vector2Dint Tablero::pos2baldosa(double x, double y) const {
	for (int columna = 0; columna < tablero.size(); columna++) {
		for (int fila = 0; fila < tablero[columna].size(); fila++) {
			if (derecha(x, y, tablero[columna][fila].hexagono.lado3, tablero[columna][fila].hexagono.lado2))
				if (!derecha(x, y, tablero[columna][fila].hexagono.lado0, tablero[columna][fila].hexagono.lado1))
					return tablero[columna][fila].identificador;
			if (derecha(x, y, tablero[columna][fila].hexagono.lado4, tablero[columna][fila].hexagono.lado3))
				if (!derecha(x, y, tablero[columna][fila].hexagono.lado5, tablero[columna][fila].hexagono.lado0))
					return tablero[columna][fila].identificador;
		}
	}

	return Vector2Dint{ false, -1, -1};
}

bool Tablero::derecha(double x, double y, Vector2Dfloat p1, Vector2Dfloat p2) const {
	if (((y >= p1.y) && (y <= p2.y)) && ((x <= p1.x) || (x <= p2.x))) {
		double interseccionX = (y - p1.y) * ((p2.x - p1.x) / (p2.y - p1.y)) + p1.x;
		if (x <= interseccionX)
			return true;
	}
	return false;
}


void Tablero::toggleColorB(Vector2Dint _identificador, Color _color) {
	tablero[_identificador.col][_identificador.row].colorDisplay = _color;
}


std::vector<Baldosa> Tablero::operator[](int indice)
{
	if (indice >= tablero.size()) indice = (int)(tablero.size()) -1;
	if (indice < 0) indice = 0;
	return tablero[indice];
}
