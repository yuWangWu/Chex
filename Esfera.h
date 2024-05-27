#pragma once
#include "VectoresUtiles.h"

class Esfera {
public:
	float radio, rings, slices;
	Vector3Ddouble posicion;

public:
	Esfera(float nradio, float nrings, float nslices, Vector3Ddouble nposicion);

	void dibuja();

};

class Linea {
public:
	Vector3Ddouble origen, final;

public:
	Linea(Vector3Ddouble norigen, Vector3Ddouble nfinal);
	
	void dibuja();
};

