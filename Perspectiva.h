#pragma once

// Includes del usuario
#include "freeglut.h"

class Perspectiva {
private:
	float fov;
	float ancho, alto;
	float znear, zfar;

public:
	// Inicializadores
	Perspectiva(float nuevoFov, float nuevoAncho, float nuevoAlto, float nuevoZnear, float nuevoZfar);

	// Misc
	void crearVentana() const;
	void inicializa() const;
};

