#pragma once

#include <vector>

#include "VectoresUtiles.h"
#include "Color.h"

enum Tipo { PEON, TORRE, ALFIL, CABALLO, REY, REINA, VACIO };
enum Equipo { BLANCO, NEGRO };

class Pieza {
protected:
	Tipo tipo;
	Equipo equipo;
	Vector2Dfloat posMundo, posMundoAnterior;
	bool sincronia = false;
	bool movido = false;
	Color color;
	std::vector<Vector3Dfloat> vertices;
	std::vector<Vector3Dfloat> normales;

public:
	Pieza(Vector2Dfloat _pos, bool _equipo);
	void cargarModelo(const char* modelo);

	// Getters
	Vector2Dfloat getPosMundo() const { return posMundo; };
	Vector2Dfloat getPosMundoAnterior() const { return posMundoAnterior; };
	bool getSincronia() const { return sincronia; };
	bool getMovido() const { return movido; };
	Tipo getTipo() const { return tipo; };
	Equipo getEquipo() const { return equipo; };

	// Setters
	void setPosMundo(Vector2Dfloat _posMundo) { posMundo = _posMundo; };
	void setPosMundoAnterior(Vector2Dfloat _posMundo) { posMundoAnterior = _posMundo; };
	void setSincronia(bool _sincronia) { sincronia = _sincronia; };
	void setMovido(bool _movido) { movido = _movido; };

	// Misc
	void dibuja();
	void mover();
	//virtual std::vector<Vector2Dint> caminosPosibles(Tablero _tablero) = 0;
};

class bVacio : public Pieza {
public:
	bVacio(Vector2Dfloat _pos, bool _equipo);
};

class Peon : public Pieza {
public:
	Peon(Vector2Dfloat _pos, bool _equipo);

	//std::vector<Vector2Dint> caminosPosibles(Tablero _tablero) override;
};

class Torre : public Pieza {
public:
	Torre(Vector2Dfloat _pos, bool _equipo);

	//bool caminosPosibles() override;
};

class Alfil : public Pieza {
public:
	Alfil(Vector2Dfloat _pos, bool _equipo);

	//bool caminosPosibles() override;
};

class Caballo : public Pieza {
public:
	Caballo(Vector2Dfloat _pos, bool _equipo, bool equipo);

	//bool caminosPosibles() override;
};

class Reina : public Pieza {
public:
	Reina(Vector2Dfloat _pos, bool _equipo);

	//bool caminosPosibles() override;
};

class Rey : public Pieza {
public:
	Rey(Vector2Dfloat _pos, bool _equipo);

	//bool caminosPosibles() override;
};