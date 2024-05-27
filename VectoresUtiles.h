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
struct Vector3Dfloat {
	// Solo se usa para el STL loader
	float x, y, z;
};

class Vector3Ddouble {
public:
	double x, y, z;

public:
	// Inicializadores
	Vector3Ddouble();
	Vector3Ddouble(double nuevox, double nuevoy, double nuevoz);

	// Sobrecarga de operadores
	Vector3Ddouble operator+(Vector3Ddouble otroVector);
	Vector3Ddouble operator-(Vector3Ddouble otroVector);
	Vector3Ddouble operator*(double valor);
	Vector3Ddouble operator/(double valor);

	// Operaciones
	double modulo();
	Vector3Ddouble unitario();
	Vector3Ddouble crossProduct(Vector3Ddouble otroVector);
};

class Vector4Dfloat {
public:
	double x, y, z, w;

public:
	Vector4Dfloat(double nuevox, double nuevoy, double nuevoz, double nuevow);
};