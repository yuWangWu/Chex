#include "Tablero.h"
#include "Presets.h"
#include "freeglut.h"

#include <fstream>

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

void Tablero::dibujar() {
	glDisable(GL_LIGHTING);
	// Dibujar todas las baldosas
	for (int columna = 0; columna < tablero.size(); columna++) {
		for (int fila = 0; fila < tablero[columna].size(); fila++) {
			glBegin(GL_POLYGON);
			glColor3ub(tablero[columna][fila].color.r, tablero[columna][fila].color.g, tablero[columna][fila].color.b);
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