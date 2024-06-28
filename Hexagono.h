#pragma once

#include "VectoresUtiles.h"

class Hexagono {
private:
	Vector2Dfloat centro;
	Vector2Dfloat lado0;
	Vector2Dfloat lado1;
	Vector2Dfloat lado2;
	Vector2Dfloat lado3;
	Vector2Dfloat lado4;
	Vector2Dfloat lado5;

public:
	friend class Baldosa;
	friend class Tablero;
};