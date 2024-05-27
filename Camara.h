#pragma once
#include "VectoresUtiles.h"

class Camara {
public:
	Vector3Ddouble ojo;
	Vector3Ddouble direccion;
	Vector3Ddouble arriba;

public:
	Camara(Vector3Ddouble nuevoOjo, Vector3Ddouble nuevoDireccion, Vector3Ddouble nuevoArriba);
	void inicia() const;
};