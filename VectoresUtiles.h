 #pragma once

// Matriz
class Vector2Dint {
public:
	bool existe = true;
	int col, row;

public:
	bool operator==(Vector2Dint _vect);
};

// Punto 2D
class Vector2Dfloat {
public:
	double x, y;

public:
	// Inicializadores
	Vector2Dfloat();
	Vector2Dfloat(double nuevox, double nuevoy);

	Vector2Dfloat operator-(Vector2Dfloat _vect) { return Vector2Dfloat({ x - _vect.x, y - _vect.y }); };
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
