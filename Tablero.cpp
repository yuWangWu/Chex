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

bool Tablero::seleccionRaton(Vector3Ddouble _posicion) {
	resetColores();

	Vector2Dint baldosaSeleccionada = pos2baldosa(_posicion.x, _posicion.y);
	if (baldosaSeleccionada.existe) {
		toggleColorB(baldosaSeleccionada);
		return true;
	}
	else
		return false;
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


void Tablero::toggleColorB(Vector2Dint _identificador) {
	tablero[_identificador.col][_identificador.row].colorDisplay = rojo;
}


std::vector<Baldosa> Tablero::operator[](int indice)
{
	if (indice >= tablero.size()) indice = (int)(tablero.size()) -1;
	if (indice < 0) indice = 0;
	return tablero[indice];
}
