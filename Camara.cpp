#include "Camara.h"

Camara::Camara(Vector3Ddouble nuevoOjo, Vector3Ddouble nuevoDireccion, Vector3Ddouble nuevoArriba) {
	ojo = nuevoOjo;
	direccion = nuevoDireccion;
	arriba = nuevoArriba;
}

void Camara::actualiza() const {
	gluLookAt(ojo.x, ojo.y, ojo.z,
		direccion.x, direccion.y, direccion.z,
		arriba.x, arriba.y, arriba.z);
}
