#pragma once
#include "VectoresUtiles.h"

class Esfera {
public:
	float radio, rings, slices;
	Vector3Dfloat posicion;

public:
	Esfera(float nradio, float nrings, float nslices, Vector3Dfloat nposicion);

	void dibuja();

};

class Linea {
public:
	Vector3Dfloat origen, final;

public:
	Linea(Vector3Dfloat norigen, Vector3Dfloat nfinal);
	
	void dibuja();
};

