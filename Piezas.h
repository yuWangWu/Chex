#pragma once

#include <vector>

#include "VectoresUtiles.h"
#include "Color.h"

class Pieza {
protected:
	Vector2Dint posTablero;
	Vector2Dfloat posMundo{ 0, 0 }, posMundoAnterior;
	bool sincronia = false;
	Color color;
	std::vector<Vector3Dfloat> vertices;
	std::vector<Vector3Dfloat> normales;

public:
	Pieza(Vector2Dint _pos, Color _color);
	void cargarModelo(const char* modelo);

	// Getters
	Vector2Dint getPosTablero() { return posTablero; };
	Vector2Dfloat getPosMundo() { return posMundo; };
	Vector2Dfloat getPosMundoAnterior() { return posMundoAnterior; };
	bool getSincronia() { return sincronia; };

	// Setters
	void setPosTablero(Vector2Dint _posTablero) { posTablero = _posTablero; };
	void setPosMundo(Vector2Dfloat _posMundo) { posMundo = _posMundo; };
	void setPosMundoAnterior(Vector2Dfloat _posMundo) { posMundoAnterior = _posMundo; };
	void setSincronia(bool _sincronia) { sincronia = _sincronia; };

	// Misc
	void dibuja();
	void mover();
	//virtual bool caminosPosibles() = 0;
};


class Peon : public Pieza {
public:
	Peon(Vector2Dint _pos, Color _color);

	//bool caminosPosibles() override;
};

class Torre : public Pieza {
public:
	Torre(Vector2Dint _pos, Color _color);

	//bool caminosPosibles() override;
};

class Alfil : public Pieza {
public:
	Alfil(Vector2Dint _pos, Color _color);

	//bool caminosPosibles() override;
};

class Caballo : public Pieza {
public:
	Caballo(Vector2Dint _pos, Color _color, bool equipo);

	//bool caminosPosibles() override;
};

class Reina : public Pieza {
public:
	Reina(Vector2Dint _pos, Color _color);

	//bool caminosPosibles() override;
};

class Rey : public Pieza {
public:
	Rey(Vector2Dint _pos, Color _color);

	//bool caminosPosibles() override;
};