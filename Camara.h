#pragma once
#include "VectoresUtiles.h"

class Camara {
public:
	Vector3Dfloat ojo;
	Vector3Dfloat direccion;
	Vector3Dfloat arriba;

public:
	Camara(Vector3Dfloat nuevoOjo, Vector3Dfloat nuevoDireccion, Vector3Dfloat nuevoArriba);
	void inicia();
};