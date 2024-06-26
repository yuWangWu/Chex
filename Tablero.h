#pragma once

#include <vector>

#include "Baldosa.h"
#include "Esfera.h"
#include "Piezas.h"

enum EstadoRey { NADA, JAQUE, JAQUEMATE };

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

	void ponPiezas();
	void dibujaPiezas();

	void resetColores();
	void resetColoresMovimiento();
	void toggleColorB(Vector2Dint _identificador, Color _color);

	bool seleccionRaton(Vector3Ddouble _posicion, bool _equipo);
	Vector2Dint pos2baldosa(double x, double y) const;
	bool derecha(double x, double y, Vector2Dfloat p1, Vector2Dfloat p2) const;

	std::vector<Baldosa> operator[](int indice);

	void caminosPeon(Vector2Dint _bSeleccionada);
	void caminosAlfil(Vector2Dint _bSeleccionada);
	void caminosTorre(Vector2Dint _bSeleccionada);
	void caminosCaballo(Vector2Dint _bSeleccionada);
	void caminosReina(Vector2Dint _bSeleccionada);
	void caminosRey(Vector2Dint _bSeleccionada);
	void caminosReyCheck(Vector2Dint _bSeleccionada);

	EstadoRey checkJaque(bool equipo);

	bool intercambiaPiezas(Vector2Dint _bDestino);

	void borrarPiezas() {
		for (int col = 0; col < tablero.size(); col++) {
			for (int row = 0; row < tablero[col].size(); row++) {
				delete tablero[col][row].pieza;
			}
		}
	}
	void borrarTablero() {
		borrarPiezas();
		for (int col = 0; col < tablero.size(); col++) {
			tablero[col].clear();
		}
		tablero.clear();
	}

	auto begin() { return tablero.begin(); };
	auto end() { return tablero.end(); };
};