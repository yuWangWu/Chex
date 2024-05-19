#pragma once

class Perspectiva {
public:
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

