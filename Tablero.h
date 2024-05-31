#pragma once

#include <vector>

#include "Baldosa.h"
#include "Esfera.h"

class Tablero {
public:
	std::vector<std::vector<Baldosa>> tablero{
		{std::vector<Baldosa>(6)},
		{std::vector<Baldosa>(7)},
		{std::vector<Baldosa>(8)},
		{std::vector<Baldosa>(9)},
		{std::vector<Baldosa>(10)},
		{std::vector<Baldosa>(11)},
		{std::vector<Baldosa>(10)},
		{std::vector<Baldosa>(9)},
		{std::vector<Baldosa>(8)},
		{std::vector<Baldosa>(7)},
		{std::vector<Baldosa>(6)}
	};

public:
	Tablero();
	void dibujar() const;

	void resetColores();
	void toggleColorB(Vector2Dint _identificador);

	bool seleccionRaton(Vector3Ddouble _posicion);
	Vector2Dint pos2baldosa(double x, double y) const;
	bool derecha(double x, double y, Vector2Dfloat p1, Vector2Dfloat p2) const;

	std::vector<Baldosa> operator[](int indice);

	auto begin() { return tablero.begin(); };
	auto end() { return tablero.end(); };
};