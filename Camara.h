#pragma once
#include "VectoresUtiles.h"

class Camara {
public:
	Vector3Ddouble ojo;
	Vector3Ddouble direccion;
	Vector3Ddouble arriba;
	double distancia, vRotacion;
	double yAnterior;

public:
	// Constructores
	Camara() = default;
	Camara(Vector3Ddouble nuevoOjo, Vector3Ddouble nuevoDireccion, Vector3Ddouble nuevoArriba);
	
	// Getters
	Vector3Ddouble getOjo() const { return ojo; };
	Vector3Ddouble getDireccion() const { return direccion; };
	Vector3Ddouble getArriba() const { return arriba; };

	// Setters
	void setOjo(Vector3Ddouble _nuevoOjo) { this->ojo = _nuevoOjo; };
	void setDireccion(Vector3Ddouble _nuevoDireccion) { this->direccion = _nuevoDireccion; };
	void setArriba(Vector3Ddouble _nuevoArriba) { this->arriba = _nuevoArriba; };

	// Misc
	void actualiza() const;
};