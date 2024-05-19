#include "Camara.h"
#include "freeglut.h"

Camara::Camara(Vector3Dfloat nuevoOjo, Vector3Dfloat nuevoDireccion, Vector3Dfloat nuevoArriba) {
	ojo = nuevoOjo;
	direccion = nuevoDireccion;
	arriba = nuevoArriba;
}

void Camara::inicia() const {
	gluLookAt(ojo.x, ojo.y, ojo.z,
		direccion.x, direccion.y, direccion.z,
		arriba.x, arriba.y, arriba.z);
}
