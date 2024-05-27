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

Vector3Ddouble::Vector3Ddouble() {
	x = 0;
	y = 0;
	z = 0;
}

Vector3Ddouble::Vector3Ddouble(double nuevox, double nuevoy, double nuevoz) {
	x = nuevox;
	y = nuevoy;
	z = nuevoz;
}

Vector3Ddouble Vector3Ddouble::operator+(Vector3Ddouble otroVector) {
	return Vector3Ddouble(x + otroVector.x, y + otroVector.y, z + otroVector.z);
}

Vector3Ddouble Vector3Ddouble::operator-(Vector3Ddouble otroVector) {
	return Vector3Ddouble(x - otroVector.x, y - otroVector.y, z - otroVector.z);
}

Vector3Ddouble Vector3Ddouble::operator*(double valor) {
	return Vector3Ddouble(x * valor, y * valor, z * valor);
}

Vector3Ddouble Vector3Ddouble::operator/(double valor) {
	return Vector3Ddouble(x / valor, y / valor, z / valor);
}

double Vector3Ddouble::modulo() {
	return (sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
}

Vector3Ddouble Vector3Ddouble::unitario() {
	return (*this / modulo());
}

Vector3Ddouble Vector3Ddouble::crossProduct(Vector3Ddouble otroVector) {
	return Vector3Ddouble(y * otroVector.z - z * otroVector.y,
		z * otroVector.x - x * otroVector.z,
		x * otroVector.y - y * otroVector.x);
}


Vector4Dfloat::Vector4Dfloat(double nuevox, double nuevoy, double nuevoz, double nuevow) {
	x = nuevox;
	y = nuevoy;
	z = nuevoz;
	w = nuevow;
}