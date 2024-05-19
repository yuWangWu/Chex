#include "Esfera.h"
#include "freeglut.h"

Esfera::Esfera(float nradio, float nslices, float nrings, Vector3Dfloat nposicion) {
	radio = nradio;
	slices = nslices;
	rings = nrings;
	posicion = nposicion;
}

void Esfera::dibuja() {
	glColor3ub(255, 0, 0);
	glTranslated(posicion.x, posicion.y, posicion.z);
	glutSolidSphere(radio, 20, 20);
	glTranslated(-posicion.x, -posicion.y, -posicion.z);
}

Linea::Linea(Vector3Dfloat norigen, Vector3Dfloat nfinal) {
	origen = norigen;
	final = nfinal;
}

void Linea::dibuja() {
	glBegin(GL_LINES);
	glColor3ub(255, 0, 0);
	glVertex3f(origen.x, origen.y, origen.z);
	glVertex3f(final.x, final.y, final.z);
	glEnd();
}