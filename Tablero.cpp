#include "Tablero.h"
#include<string>
#include "Presets.h"
#include"MaqEstados.h"

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

void Tablero::resetColoresMovimiento() {
	for (int columna = 0; columna < tablero.size(); columna++)
		for (int fila = 0; fila < tablero[columna].size(); fila++)
			if ((tablero[columna][fila].colorDisplay != rojo) && (tablero[columna][fila].colorDisplay != amarillo))
				tablero[columna][fila].colorDisplay = tablero[columna][fila].color;
}


void Tablero::ponPiezas(std::string path) {
	for (int col = 0; col < tablero.size(); col++)
		for (int row = 0; row < tablero[col].size(); row++)
			tablero[col][row].pieza = new bVacio({ -1, -1 }, true);

	// Comienzo de piezas basadas en fichero
	//equipo 0 para negras 1 para blancas
	// tipo p->Peón  a->Alfil  t->Torre  c->Caballo  k->Rey(King) q->Reina(Queen)

	char tipo;
	int coord1, coord2;
	bool equipo;

	std::ifstream myfile;
	myfile.open(path);

	if (myfile.is_open()) {
		while (myfile >> coord1 >> coord2 >> tipo >> equipo) {

			if (tipo == 'p') {
				delete tablero[coord1][coord2].pieza;
				tablero[coord1][coord2].pieza = new Peon(tablero[coord1][coord2].hexagono.centro, equipo);
			}
			else if (tipo == 't') {
				delete tablero[coord1][coord2].pieza;
				tablero[coord1][coord2].pieza = new Torre(tablero[coord1][coord2].hexagono.centro, equipo);
			}
			else if (tipo == 'a') {
				delete tablero[coord1][coord2].pieza;
				tablero[coord1][coord2].pieza = new Alfil(tablero[coord1][coord2].hexagono.centro, equipo);
			}
			else if (tipo == 'c') {
				delete tablero[coord1][coord2].pieza;
				tablero[coord1][coord2].pieza = new Caballo(tablero[coord1][coord2].hexagono.centro, equipo, equipo);
			}
			else if (tipo == 'k') {
				delete tablero[coord1][coord2].pieza;
				tablero[coord1][coord2].pieza = new Rey(tablero[coord1][coord2].hexagono.centro, equipo);
			}
			else if (tipo == 'q') {
				delete tablero[coord1][coord2].pieza;
				tablero[coord1][coord2].pieza = new Reina(tablero[coord1][coord2].hexagono.centro, equipo);
			}

		}

	}
	else  std::cerr << "no se ha encontrado el fichero de inicio de partida" << path << std::endl;

	myfile.close();
	
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

void Tablero::guardaPiezas(std::string path, bool turno) {

	std::ofstream save;
	save.open(path);
	if (save.is_open()) {

		save << turno<<std::endl;

		for (int i = 0; i < tablero.size(); i++) {
			for (int j = 0; j < tablero[i].size(); j++) {
				if (tablero[i][j].pieza->getTipo() != VACIO) {
					save << i << " " << j << " " << tablero[i][j].pieza->getTipo() << " " << tablero[i][j].pieza->getEquipo() << " " << tablero[i][j].pieza->getMovido() << " " << tablero[i][j].pieza->getMovido1vez() << std::endl;
				}
			}
		}
	}
	else std::cerr << "no se ha podido crear o sobreescribir el fichero de destino" << std::endl;

	save.close();
}

bool Tablero::cargaPartida(std::string path) {
	for (int col = 0; col < tablero.size(); col++)
		for (int row = 0; row < tablero[col].size(); row++)
			tablero[col][row].pieza = new bVacio({ -1, -1 }, true);

	int coord1, coord2, tipo;
	bool equipo, turno=0, mov1, mov;

	std::ifstream save;
	save.open(path);

	if (save.is_open()) {

		save >> turno;

		while (save >> coord1 >> coord2 >> tipo >> equipo >> mov >> mov1) {

			//si no salen cambiados de equipo, no se muy bien porque
			if (equipo == 1) equipo = 0;
			else if (equipo == 0) equipo = 1;

			if (tipo == PEON) {
				delete tablero[coord1][coord2].pieza;
				tablero[coord1][coord2].pieza = new Peon(tablero[coord1][coord2].hexagono.centro, equipo);
				tablero[coord1][coord2].pieza->setMovido(mov);
				tablero[coord1][coord2].pieza->setMovido1vez(mov1);
			}
			else if (tipo == TORRE) {
				delete tablero[coord1][coord2].pieza;
				tablero[coord1][coord2].pieza = new Torre(tablero[coord1][coord2].hexagono.centro, equipo);
				tablero[coord1][coord2].pieza->setMovido(mov);
				tablero[coord1][coord2].pieza->setMovido1vez(mov1);
			}
			else if (tipo == ALFIL) {
				delete tablero[coord1][coord2].pieza;
				tablero[coord1][coord2].pieza = new Alfil(tablero[coord1][coord2].hexagono.centro, equipo);
				tablero[coord1][coord2].pieza->setMovido(mov);
				tablero[coord1][coord2].pieza->setMovido1vez(mov1);
			}
			else if (tipo == CABALLO) {
				delete tablero[coord1][coord2].pieza;
				tablero[coord1][coord2].pieza = new Caballo(tablero[coord1][coord2].hexagono.centro, equipo, equipo);
				tablero[coord1][coord2].pieza->setMovido(mov);
				tablero[coord1][coord2].pieza->setMovido1vez(mov1);
			}
			else if (tipo == REY) {
				delete tablero[coord1][coord2].pieza;
				tablero[coord1][coord2].pieza = new Rey(tablero[coord1][coord2].hexagono.centro, equipo);
				tablero[coord1][coord2].pieza->setMovido(mov);
				tablero[coord1][coord2].pieza->setMovido1vez(mov1);
			}
			else if (tipo == REINA) {
				delete tablero[coord1][coord2].pieza;
				tablero[coord1][coord2].pieza = new Reina(tablero[coord1][coord2].hexagono.centro, equipo);
				tablero[coord1][coord2].pieza->setMovido(mov);
				tablero[coord1][coord2].pieza->setMovido1vez(mov1);
			}

		}
	}
	else  std::cerr << "no se ha encontrado el fichero de partida guardada: "<< path <<std::endl;



	save.close();

	return turno;
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

void Tablero::caminosPeon(Vector2Dint _bSeleccionada, bool check) {
	Vector2Dint bCursor;
	if (tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo() == BLANCO) { // Blanco
		bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bIzqArriba;
		if ((bCursor.existe) &&
			(tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo()) &&
			(tablero[bCursor.col][bCursor.row].pieza->getTipo() != VACIO))
			if (!check)
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
			else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bDerArriba;
		if ((bCursor.existe) &&
			(tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo()) &&
			(tablero[bCursor.col][bCursor.row].pieza->getTipo() != VACIO))
			if (!check)
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
			else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);

		// Comprobar en pasant
		bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bIzqAbajo;
		if ((bCursor.existe) &&
			(tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo()) &&
			(tablero[bCursor.col][bCursor.row].pieza->getTipo() == PEON) &&
			(tablero[bCursor.col][bCursor.row].pieza->getMovido1vez()))
			toggleColorB(tablero[_bSeleccionada.col][_bSeleccionada.row].bIzqArriba, rojo);
		bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bDerAbajo;
		if ((bCursor.existe) &&
			(tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo()) &&
			(tablero[bCursor.col][bCursor.row].pieza->getTipo() == PEON) &&
			(tablero[bCursor.col][bCursor.row].pieza->getMovido1vez()))
			toggleColorB(tablero[_bSeleccionada.col][_bSeleccionada.row].bDerArriba, rojo);

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
		}
	}
	else { // Negro
		bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bIzqAbajo;
		if ((bCursor.existe) &&
			(tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo()) &&
			(tablero[bCursor.col][bCursor.row].pieza->getTipo() != VACIO))
			if (!check)
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
			else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bDerAbajo;
		if ((bCursor.existe) &&
			(tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo()) &&
			(tablero[bCursor.col][bCursor.row].pieza->getTipo() != VACIO))
			if (!check)
				toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
			else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);

		// Comprobar en pasant
		bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bIzqArriba;
		if ((bCursor.existe) &&
			(tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo()) &&
			(tablero[bCursor.col][bCursor.row].pieza->getTipo() == PEON) &&
			(tablero[bCursor.col][bCursor.row].pieza->getMovido1vez()))
			toggleColorB(tablero[_bSeleccionada.col][_bSeleccionada.row].bIzqAbajo, rojo);
		bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bDerArriba;
		if ((bCursor.existe) &&
			(tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo()) &&
			(tablero[bCursor.col][bCursor.row].pieza->getTipo() == PEON) &&
			(tablero[bCursor.col][bCursor.row].pieza->getMovido1vez()))
			toggleColorB(tablero[_bSeleccionada.col][_bSeleccionada.row].bDerAbajo, rojo);

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
		}
	}
}

void Tablero::caminosAlfil(Vector2Dint _bSeleccionada, bool check) {
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
					if (!check)
						toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
					else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
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
					if (!check)
						toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
					else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
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
					if (!check)
						toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
					else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
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
					if (!check)
						toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
					else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
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
					if (!check)
						toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
					else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
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
					if (!check)
						toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
					else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
				break;
			}
		}
		else {
			break;
		}
	} while (true);
}

void Tablero::caminosTorre(Vector2Dint _bSeleccionada, bool check) {
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
					if (!check)
						toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
					else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
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
					if (!check)
						toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
					else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
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
					if (!check)
						toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
					else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
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
					if (!check)
						toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
					else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
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
					if (!check)
						toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
					else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
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
					if (!check)
						toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
					else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
				break;
			}
		}
		else {
			break;
		}
	} while (true);
}

void Tablero::caminosCaballo(Vector2Dint _bSeleccionada, bool check) {
	Vector2Dint bCursor;
	// Caminos esquina izquierda
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bCaballoIzqAbajo;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
				if (!check)
					toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
				else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
	}
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bCaballoIzqArriba;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
				if (!check)
					toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
				else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
	}

	// Caminos esquina izquierda arriba
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bCaballoEsqIzqArrAbajo;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
				if (!check)
					toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
				else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
	}
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bCaballoEsqIzqArrArriba;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
				if (!check)
					toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
				else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
	}

	// Caminos esquina derecha arriba
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bCaballoEsqDerArrArriba;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
				if (!check)
					toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
				else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
	}
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bCaballoEsqDerArrAbajo;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
				if (!check)
					toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
				else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
	}

	// Caminos esquina derecha
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bCaballoDerArriba;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
				if (!check)
					toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
				else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
	}
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bCaballoDerAbajo;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
				if (!check)
					toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
				else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
	}

	// Caminos esquina derecha abajo
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bCaballoEsqDerAbjArriba;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
				if (!check)
					toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
				else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
	}
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bCaballoEsqDerAbjAbajo;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
				if (!check)
					toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
				else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
	}

	// Caminos esquina izquierda abajo
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bCaballoEsqIzqAbjAbajo;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
				if (!check)
					toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
				else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
	}
	bCursor = tablero[_bSeleccionada.col][_bSeleccionada.row].bCaballoEsqIzqAbjArriba;
	if (bCursor.existe) {
		if (tablero[bCursor.col][bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
		else
			if (tablero[bCursor.col][bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
				if (!check)
					toggleColorB(tablero[bCursor.col][bCursor.row].identificador, rojo);
				else toggleColorB(tablero[bCursor.col][bCursor.row].identificador, cyan);
	}
}

void Tablero::caminosReina(Vector2Dint _bSeleccionada, bool check) {
	caminosAlfil(_bSeleccionada, check);
	caminosTorre(_bSeleccionada, check);
}

void Tablero::caminosRey(Vector2Dint b, bool check) {
	Vector2Dint bCursor;
	bCursor = tablero[b.col][b.row].bEsqIzquierda;
	coloreaMovimientoBaldosa(b, bCursor, check);
	bCursor = tablero[b.col][b.row].bIzqArriba;
	coloreaMovimientoBaldosa(b, bCursor, check);
	bCursor = tablero[b.col][b.row].bEsqIzqArriba;
	coloreaMovimientoBaldosa(b, bCursor, check);
	bCursor = tablero[b.col][b.row].bArriba;
	coloreaMovimientoBaldosa(b, bCursor, check);
	bCursor = tablero[b.col][b.row].bEsqDerArriba;
	coloreaMovimientoBaldosa(b, bCursor, check);
	bCursor = tablero[b.col][b.row].bDerArriba;
	coloreaMovimientoBaldosa(b, bCursor, check);
	bCursor = tablero[b.col][b.row].bEsqDerecha;
	coloreaMovimientoBaldosa(b, bCursor, check);
	bCursor = tablero[b.col][b.row].bDerAbajo;
	coloreaMovimientoBaldosa(b, bCursor, check);
	bCursor = tablero[b.col][b.row].bEsqDerAbajo;
	coloreaMovimientoBaldosa(b, bCursor, check);
	bCursor = tablero[b.col][b.row].bAbajo;
	coloreaMovimientoBaldosa(b, bCursor, check);
	bCursor = tablero[b.col][b.row].bEsqIzqAbajo;
	coloreaMovimientoBaldosa(b, bCursor, check);
	bCursor = tablero[b.col][b.row].bIzqAbajo;
	coloreaMovimientoBaldosa(b, bCursor, check);
}

void Tablero::caminosReyCheck(Vector2Dint b) {
	Vector2Dint bCursor;
	toggleColorB(tablero[b.col][b.row].identificador, amarillo);
	bCursor = tablero[b.col][b.row].bEsqIzquierda;
	coloreaMovimientoBaldosaCheck(b, bCursor);
	bCursor = tablero[b.col][b.row].bIzqArriba;
	coloreaMovimientoBaldosaCheck(b, bCursor);
	bCursor = tablero[b.col][b.row].bEsqIzqArriba;
	coloreaMovimientoBaldosaCheck(b, bCursor);
	bCursor = tablero[b.col][b.row].bArriba;
	coloreaMovimientoBaldosaCheck(b, bCursor);
	bCursor = tablero[b.col][b.row].bEsqDerArriba;
	coloreaMovimientoBaldosaCheck(b, bCursor);
	bCursor = tablero[b.col][b.row].bDerArriba;
	coloreaMovimientoBaldosaCheck(b, bCursor);
	bCursor = tablero[b.col][b.row].bEsqDerecha;
	coloreaMovimientoBaldosaCheck(b, bCursor);
	bCursor = tablero[b.col][b.row].bDerAbajo;
	coloreaMovimientoBaldosaCheck(b, bCursor);
	bCursor = tablero[b.col][b.row].bEsqDerAbajo;
	coloreaMovimientoBaldosaCheck(b, bCursor);
	bCursor = tablero[b.col][b.row].bAbajo;
	coloreaMovimientoBaldosaCheck(b, bCursor);
	bCursor = tablero[b.col][b.row].bEsqIzqAbajo;
	coloreaMovimientoBaldosaCheck(b, bCursor);
	bCursor = tablero[b.col][b.row].bIzqAbajo;
	coloreaMovimientoBaldosaCheck(b, bCursor);
}


bool Tablero::checkPromoPeon() {
	for (int col = 0; col < tablero.size(); col++) {
		if ((tablero[col][0].pieza->getTipo() == PEON) && (tablero[col][0].pieza->getEquipo() == NEGRO)) {
			return true;
		}
		if ((tablero[col][tablero[col].size() - 1].pieza->getTipo() == PEON) && (tablero[col][tablero[col].size() - 1].pieza->getEquipo() == BLANCO)) {
			return true;
		}
	}
	return false;
}

bool Tablero::pPeonReina() {
	for (int col = 0; col < tablero.size(); col++) {
		if ((tablero[col][0].pieza->getTipo() == PEON) && (tablero[col][0].pieza->getEquipo() == NEGRO)) {
			delete tablero[col][0].pieza;
			tablero[col][0].pieza = new Reina(tablero[col][0].hexagono.centro, false);
			return true;
		}
		if ((tablero[col][tablero[col].size() - 1].pieza->getTipo() == PEON) && (tablero[col][tablero[col].size() - 1].pieza->getEquipo() == BLANCO)) {
			delete tablero[col][tablero[col].size() - 1].pieza;
			tablero[col][tablero[col].size() - 1].pieza = new Reina(tablero[col][tablero[col].size() - 1].hexagono.centro, true);
			return true;
		}
	}
	return false;
}

bool Tablero::pPeonTorre() {
	for (int col = 0; col < tablero.size(); col++) {
		if ((tablero[col][0].pieza->getTipo() == PEON) && (tablero[col][0].pieza->getEquipo() == NEGRO)) {
			delete tablero[col][0].pieza;
			tablero[col][0].pieza = new Torre(tablero[col][0].hexagono.centro, false);
			return true;
		}
		if ((tablero[col][tablero[col].size() - 1].pieza->getTipo() == PEON) && (tablero[col][tablero[col].size() - 1].pieza->getEquipo() == BLANCO)) {
			delete tablero[col][tablero[col].size() - 1].pieza;
			tablero[col][tablero[col].size() - 1].pieza = new Torre(tablero[col][tablero[col].size() - 1].hexagono.centro, true);
			return true;
		}
	}
	return false;
}

bool Tablero::pPeonAlfil() {
	for (int col = 0; col < tablero.size(); col++) {
		if ((tablero[col][0].pieza->getTipo() == PEON) && (tablero[col][0].pieza->getEquipo() == NEGRO)) {
			delete tablero[col][0].pieza;
			tablero[col][0].pieza = new Alfil(tablero[col][0].hexagono.centro, false);
			return true;
		}
		if ((tablero[col][tablero[col].size() - 1].pieza->getTipo() == PEON) && (tablero[col][tablero[col].size() - 1].pieza->getEquipo() == BLANCO)) {
			delete tablero[col][tablero[col].size() - 1].pieza;
			tablero[col][tablero[col].size() - 1].pieza = new Alfil(tablero[col][tablero[col].size() - 1].hexagono.centro, true);
			return true;
		}
	}
	return false;
}

bool Tablero::pPeonCaballo() {
	for (int col = 0; col < tablero.size(); col++) {
		if ((tablero[col][0].pieza->getTipo() == PEON) && (tablero[col][0].pieza->getEquipo() == NEGRO)) {
			delete tablero[col][0].pieza;
			tablero[col][0].pieza = new Caballo(tablero[col][0].hexagono.centro, false, false);
			return true;
		}
		if ((tablero[col][tablero[col].size() - 1].pieza->getTipo() == PEON) && (tablero[col][tablero[col].size() - 1].pieza->getEquipo() == BLANCO)) {
			delete tablero[col][tablero[col].size() - 1].pieza;
			tablero[col][tablero[col].size() - 1].pieza = new Caballo(tablero[col][tablero[col].size() - 1].hexagono.centro, true, true);
			return true;
		}
	}
	return false;
}


bool Tablero::coloreaMovimientoBaldosa(Vector2Dint _bSeleccionada, Vector2Dint _bCursor, bool check) {
	if (_bCursor.existe) {
		if (tablero[_bCursor.col][_bCursor.row].pieza->getTipo() == VACIO)
			toggleColorB(tablero[_bCursor.col][_bCursor.row].identificador, cyan);
		else
			if (tablero[_bCursor.col][_bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo())
				if (!check)
					toggleColorB(tablero[_bCursor.col][_bCursor.row].identificador, rojo);
				else toggleColorB(tablero[_bCursor.col][_bCursor.row].identificador, cyan);
		return true;
	}
	return false;
}

bool Tablero::coloreaMovimientoBaldosaCheck(Vector2Dint _bSeleccionada, Vector2Dint _bCursor) {
	if (_bCursor.existe) {
		if ((tablero[_bCursor.col][_bCursor.row].pieza->getTipo() == VACIO) ||
			(tablero[_bCursor.col][_bCursor.row].pieza->getEquipo() != tablero[_bSeleccionada.col][_bSeleccionada.row].pieza->getEquipo()))
			toggleColorB(tablero[_bCursor.col][_bCursor.row].identificador, amarillo);
		return true;
	}
	return false;
}


EstadoRey Tablero::checkJaque(bool _equipo) {
	EstadoRey estado{};
	Vector2Dint posRey{ false, -1, -1 };
	
	for (int col = 0; col < tablero.size(); col++) {
		for (int row = 0; row < tablero[col].size(); row++) {
			if (tablero[col][row].pieza->getTipo() == REY) {
				if ((tablero[col][row].pieza->getEquipo() == NEGRO) && _equipo) {
					posRey = { true, col, row };
					break;
				}
				if ((tablero[col][row].pieza->getEquipo() == BLANCO) && !_equipo) {
					posRey = { true, col, row };
					break;	
				}
			}
		}
	}

	if (!posRey.existe)
		return JAQUEMATE;

	// Colorea de amarillo los posibles movimientos del rey
	caminosReyCheck(tablero[posRey.col][posRey.row].identificador);

	if (_equipo) { // Chequea si el equipo negro esta en jaque
		for (int col = 0; col < tablero.size(); col++) {
			for (int row = 0; row < tablero[col].size(); row++) {
				if (tablero[col][row].pieza->getEquipo() == BLANCO) {
					switch (tablero[col][row].pieza->getTipo()) {
					case PEON:
						caminosPeon(tablero[col][row].identificador, true);
						//resetColoresMovimiento();
						break;

					case ALFIL:
						caminosAlfil(tablero[col][row].identificador, true);
						//resetColoresMovimiento();
						break;

					case TORRE:
						caminosTorre(tablero[col][row].identificador, true);
						//resetColoresMovimiento();
						break;

					case CABALLO:
						caminosCaballo(tablero[col][row].identificador, true);
						//resetColoresMovimiento();
						break;

					case REINA:
						caminosReina(tablero[col][row].identificador, true);
						//resetColoresMovimiento();
						break;

					case REY:
						caminosRey(tablero[col][row].identificador, true);
						//resetColoresMovimiento();
						break;

					default:
						break;
					}
				}
			}
		}
	}
	else { // Chequea si el equipo blanco esta en jaque
		for (int col = 0; col < tablero.size(); col++) {
			for (int row = 0; row < tablero[col].size(); row++) {
				if (tablero[col][row].pieza->getEquipo() == NEGRO) {
					switch (tablero[col][row].pieza->getTipo()) {
					case PEON:
						caminosPeon(tablero[col][row].identificador, true);
						//resetColoresMovimiento();
						break;

					case ALFIL:
						caminosAlfil(tablero[col][row].identificador, true);
						//resetColoresMovimiento();
						break;

					case TORRE:
						caminosTorre(tablero[col][row].identificador, true);
						//resetColoresMovimiento();
						break;

					case CABALLO:
						caminosCaballo(tablero[col][row].identificador, true);
						//resetColoresMovimiento();
						break;

					case REINA:
						caminosReina(tablero[col][row].identificador, true);
						//resetColoresMovimiento();
						break;

					case REY:
						caminosRey(tablero[col][row].identificador, true);
						//resetColoresMovimiento();
						break;

					default:
						break;
					}
				}
			}
		}
	}

	// Todas las baldosas con movimientos posibles quedan en rojo
	// Chequeamos si quedan baldosas amarillas 
	if (tablero[posRey.col][posRey.row].colorDisplay == cyan) {
		// Estado de Jaque
		estado = JAQUE;
		for (int col = 0; col < tablero.size(); col++) {
			for (int row = 0; row < tablero[col].size(); row++) {
				if (tablero[col][row].colorDisplay == amarillo) {
					resetColores();
					return estado;
				}
			}
		}
		estado = JAQUEMATE;
		return estado;
	}
	
	resetColores();
	return estado;
}


bool Tablero::intercambiaPiezas(Vector3Ddouble _identificador) {
	// Validez del movimiento
	Vector2Dint _bDestino = pos2baldosa(_identificador.x, _identificador.y);
	if (_bDestino.existe) {
		if (!((tablero[_bDestino.col][_bDestino.row].colorDisplay == rojo) ||
			(tablero[_bDestino.col][_bDestino.row].colorDisplay == cyan))) {
			resetColores();
			return false;
		}
	}
	else {
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
	if ((tablero[_bDestino.col][_bDestino.row].colorDisplay == cyan) || 
		((tablero[_bDestino.col][_bDestino.row].pieza->getTipo() == VACIO) && (tablero[_bDestino.col][_bDestino.row].colorDisplay == rojo))) { // Movimiento normal o en pasant
		tablero[bOrigen.col][bOrigen.row].pieza->setPosMundoAnterior(tablero[bOrigen.col][bOrigen.row].pieza->getPosMundo());

		// BAGUETTEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
		if ((tablero[_bDestino.col][_bDestino.row].pieza->getTipo() == VACIO) &&
			(tablero[_bDestino.col][_bDestino.row].colorDisplay == rojo)) {
			Vector2Dint bCursor{};
			if (tablero[bOrigen.col][bOrigen.row].pieza->getEquipo() == BLANCO)
				bCursor = tablero[_bDestino.col][_bDestino.row].bAbajo;
			else
				bCursor = tablero[_bDestino.col][_bDestino.row].bArriba;

			delete tablero[bCursor.col][bCursor.row].pieza;
			tablero[bCursor.col][bCursor.row].pieza = new bVacio({ -1, -1 }, true);
		}
		
		Pieza* pAux = tablero[bOrigen.col][bOrigen.row].pieza;
		tablero[bOrigen.col][bOrigen.row].pieza = tablero[_bDestino.col][_bDestino.row].pieza;
		tablero[_bDestino.col][_bDestino.row].pieza = pAux;

		tablero[_bDestino.col][_bDestino.row].pieza->setPosMundo(tablero[_bDestino.col][_bDestino.row].hexagono.centro);
		tablero[_bDestino.col][_bDestino.row].pieza->setSincronia(false);
		tablero[_bDestino.col][_bDestino.row].pieza->mover();

		if (tablero[_bDestino.col][_bDestino.row].pieza->getMovido1vez())
			tablero[_bDestino.col][_bDestino.row].pieza->setMovido1vez(false);
		if (!tablero[_bDestino.col][_bDestino.row].pieza->getMovido()) {
			tablero[_bDestino.col][_bDestino.row].pieza->setMovido(true);
			tablero[_bDestino.col][_bDestino.row].pieza->setMovido1vez(true);
		}

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

		if (!tablero[_bDestino.col][_bDestino.row].pieza->getMovido())
			tablero[_bDestino.col][_bDestino.row].pieza->setMovido(true);

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
