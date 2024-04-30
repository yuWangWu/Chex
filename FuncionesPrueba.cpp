#include "Baldosa.h"
#include <iostream>

Coordenadas Baldosa::getIzquierda(Baldosa actual) {
	Coordenadas resultado{};
	resultado.col = actual.coordenadas.col - 2;

	if (actual.coordenadas.col > 6)
		resultado.row = actual.coordenadas.row + 1;
	else if (actual.coordenadas.col == 6)
		resultado.row = actual.coordenadas.row;
	else if (actual.coordenadas.col < 6)
		resultado.row = actual.coordenadas.row - 1;

	// Cuando hay error, TEMPORAL
	if ((resultado.col < 0) || (resultado.row < 0) || (resultado.row > (5 - resultado.col)))
		resultado.existe = false,
        std::cout << "No tiene baldosa a su izquierda!" << std::endl;

	return resultado;
}

Coordenadas Baldosa::getDerecha(Baldosa actual) {
	Coordenadas resultado{};
	resultado.col = actual.coordenadas.col + 2;

	if (actual.coordenadas.col < 4)
		resultado.row = actual.coordenadas.row + 1;
	else if (actual.coordenadas.col == 4)
		resultado.row = actual.coordenadas.row;
	else if (actual.coordenadas.col > 4)
		resultado.row = actual.coordenadas.row - 1;

	// Cuando hay error, TEMPORAL
	if ((resultado.col > 10) || (resultado.row < 0) || (resultado.row > (15 - resultado.col)))
		resultado.existe = false,
        std::cout << "No tiene baldosa a su derecha!" << std::endl;

	return resultado;
}

Coordenadas Baldosa::getArriba(Baldosa actual) {
	Coordenadas resultado{};
	resultado.col = actual.coordenadas.col;

	if (((actual.coordenadas.col < 6) || (actual.coordenadas.row < (5 + actual.coordenadas.col))) ||
		((actual.coordenadas.col > 4) || (actual.coordenadas.row < (15 - actual.coordenadas.col))))
		resultado.row = actual.coordenadas.row + 1;
	// Cuando hay error, TEMPORAL
	else
        resultado.existe = false,
		std::cout << "No tiene baldosa encima!" << std::endl;

	return resultado;
}

Coordenadas Baldosa::getAbajo(Baldosa actual) {
	Coordenadas resultado{};
	resultado.col = actual.coordenadas.col;

	if (actual.coordenadas.row > 0)
		resultado.row = actual.coordenadas.row - 1;
	// Cuando hay error, TEMPORAL
	else
        resultado.existe = false,
		std::cout << "No tiene baldosa abajo!" << std::endl;

	return resultado;
}

Coordenadas Baldosa::getIzqArriba(Baldosa actual) {
	Coordenadas resultado{};
	resultado.col = actual.coordenadas.col - 1;

	if ((actual.coordenadas.col > 0) ||
		((actual.coordenadas.col < 6) && (actual.coordenadas.row < (5 + actual.coordenadas.col))))
		resultado.row = actual.coordenadas.row;
	// Cuando hay error, TEMPORAL
	else
        resultado.existe = false,
		std::cout << "No tiene baldosa arriba a la izquierda!" << std::endl;

	return resultado;
}

Coordenadas Baldosa::getIzqAbajo(Baldosa actual) {
	Coordenadas resultado{};
	resultado.col = actual.coordenadas.col - 1;

	if ((actual.coordenadas.col > 0) ||
		((actual.coordenadas.col < 6) && (actual.coordenadas.row > 0)))
		resultado.row = actual.coordenadas.row - 1;
	// Cuando hay error, TEMPORAL
	else
        resultado.existe = false,
		std::cout << "No tiene baldosa abajo a la izquierda!" << std::endl;

	return resultado;
}

Coordenadas Baldosa::getDerArriba(Baldosa actual) {
	Coordenadas resultado{};
	resultado.col = actual.coordenadas.col + 1;

	if ((actual.coordenadas.col < 10) ||
		((actual.coordenadas.col > 4) && (actual.coordenadas.row < (15 - actual.coordenadas.col))))
		resultado.row = actual.coordenadas.row;
	// Cuando hay error, TEMPORAL
	else
        resultado.existe = false,
		std::cout << "No tiene baldosa arriba a la derecha!" << std::endl;

	return resultado;
}

Coordenadas Baldosa::getDerAbajo(Baldosa actual) {
	Coordenadas resultado{};
	resultado.col = actual.coordenadas.col + 1;

	if ((actual.coordenadas.col < 10) ||
		((actual.coordenadas.col > 4) && (actual.coordenadas.row > 0)))
		resultado.row = actual.coordenadas.row - 1;
	// Cuando hay error, TEMPORAL
	else
        resultado.existe = false,
		std::cout << "No tiene baldosa abajo a la derecha!" << std::endl;

	return resultado;
}