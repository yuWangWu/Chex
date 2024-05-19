#include "VectoresUtiles.h"
#include <cmath>

Vector2Dfloat::Vector2Dfloat() {
	x = 0;
	y = 0;
}

Vector2Dfloat::Vector2Dfloat(double nuevox, double nuevoy) {
	x = nuevox;
	y = nuevoy;
}

Vector3Dfloat::Vector3Dfloat() {
	x = 0;
	y = 0;
	z = 0;
}

Vector3Dfloat::Vector3Dfloat(double nuevox, double nuevoy, double nuevoz) {
	x = nuevox;
	y = nuevoy;
	z = nuevoz;
}

Vector3Dfloat Vector3Dfloat::operator+(Vector3Dfloat otroVector) {
	return Vector3Dfloat(x + otroVector.x, y + otroVector.y, z + otroVector.z);
}

Vector3Dfloat Vector3Dfloat::operator-(Vector3Dfloat otroVector) {
	return Vector3Dfloat(x - otroVector.x, y - otroVector.y, z - otroVector.z);
}

Vector3Dfloat Vector3Dfloat::operator*(double valor) {
	return Vector3Dfloat(x * valor, y * valor, z * valor);
}

Vector3Dfloat Vector3Dfloat::operator/(double valor) {
	return Vector3Dfloat(x / valor, y / valor, z / valor);
}

double Vector3Dfloat::modulo() {
	return (sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
}

Vector3Dfloat Vector3Dfloat::unitario() {
	return (*this / modulo());
}

Vector3Dfloat Vector3Dfloat::crossProduct(Vector3Dfloat otroVector) {
	return Vector3Dfloat(y * otroVector.z - z * otroVector.y,
		z * otroVector.x - x * otroVector.z,
		x * otroVector.y - y * otroVector.x);
}


Vector4Dfloat::Vector4Dfloat(double nuevox, double nuevoy, double nuevoz, double nuevow) {
	x = nuevox;
	y = nuevoy;
	z = nuevoz;
	w = nuevow;
}