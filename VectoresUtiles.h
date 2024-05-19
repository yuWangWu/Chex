 #pragma once

// Matriz
class Vector2Dint {
public:
	bool existe = true;
	int col, row;
};

// Punto 2D
class Vector2Dfloat {
public:
	double x, y;

public:
	// Inicializadores
	Vector2Dfloat();
	Vector2Dfloat(double nuevox, double nuevoy);
};

// Punto 3D
class Vector3Dfloat {
public:
	double x, y, z;

public:
	// Inicializadores
	Vector3Dfloat();
	Vector3Dfloat(double nuevox, double nuevoy, double nuevoz);

	// Sobrecarga de operadores
	Vector3Dfloat operator+(Vector3Dfloat otroVector);
	Vector3Dfloat operator-(Vector3Dfloat otroVector);
	Vector3Dfloat operator*(double valor);
	Vector3Dfloat operator/(double valor);

	// Operaciones
	double modulo();
	Vector3Dfloat unitario();
	Vector3Dfloat crossProduct(Vector3Dfloat otroVector);
};

class Vector4Dfloat {
public:
	double x, y, z, w;

public:
	Vector4Dfloat(double nuevox, double nuevoy, double nuevoz, double nuevow);
};