#pragma once

#include "VectoresUtiles.h"

class Hexagono {
public:
	Vector2Dfloat centro;
	Vector2Dfloat lado0;
	Vector2Dfloat lado1;
	Vector2Dfloat lado2;
	Vector2Dfloat lado3;
	Vector2Dfloat lado4;
	Vector2Dfloat lado5;

public:
	// Getters
	Vector2Dfloat getCentro() { return centro; };
	Vector2Dfloat getlado0() { return lado0; };
	Vector2Dfloat getlado1() { return lado1; };
	Vector2Dfloat getlado2() { return lado2; };
	Vector2Dfloat getlado3() { return lado3; };
	Vector2Dfloat getlado4() { return lado4; };
	Vector2Dfloat getlado5() { return lado5; };
};