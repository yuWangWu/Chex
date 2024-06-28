#include "Perspectiva.h"

Perspectiva::Perspectiva(float nuevoFov, float nuevoAncho, float nuevoAlto, float nuevoZnear, float nuevoZfar) {
	fov =	(nuevoFov > 10)		? nuevoFov : 10.0f;
	ancho = (nuevoAncho > 100)	? nuevoAncho : 100.0f;
	alto =	(nuevoAlto > 100)	? nuevoAlto : 100.0f;
	znear = (nuevoZnear < 5)	? nuevoZnear : 5.0f;
	zfar =	(nuevoZfar > 100)	? nuevoZfar : 100.0f;
}

void Perspectiva::crearVentana() const {
	glutInitWindowSize(ancho, alto);
}

void Perspectiva::inicializa() const {
	gluPerspective(fov, ancho / alto, znear, zfar);
}