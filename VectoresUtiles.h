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
	float x, y;
};

// Punto 3D
class Vector3Dfloat {
public:
	float x, y, z;

public:
	Vector3Dfloat();
	Vector3Dfloat(float nuevox, float nuevoy, float nuevoz);
};