#include "Baldosa.h"
#include <iostream>

Coordenadas Baldosa::getIzquierda(Baldosa actual) {
	Coordenadas resultado{};
	resultado.col = actual.coordenadas.col - 2;

	if (actual.coordenadas.col > 6)
		resultado.row = actual.coordenadas.row + 1;
	else if (actual.coordenadas.col == 6)
		resultado.row = actual.coordenadas.row;
	else if (actual.coordenadas.col < 6)
		resultado.row = actual.coordenadas.row - 1;

	// Cuando hay error, TEMPORAL
	if ((resultado.col < 0) || (resultado.row < 0) || (resultado.row > (5 - resultado.col)))
		resultado.existe = false,
        std::cout << "No tiene baldosa a su izquierda!" << std::endl;

	return resultado;
}

Coordenadas Baldosa::getDerecha(Baldosa actual) {
	Coordenadas resultado{};
	resultado.col = actual.coordenadas.col + 2;

	if (actual.coordenadas.col < 4)
		resultado.row = actual.coordenadas.row + 1;
	else if (actual.coordenadas.col == 4)
		resultado.row = actual.coordenadas.row;
	else if (actual.coordenadas.col > 4)
		resultado.row = actual.coordenadas.row - 1;

	// Cuando hay error, TEMPORAL
	if ((resultado.col > 10) || (resultado.row < 0) || (resultado.row > (15 - resultado.col)))
		resultado.existe = false,
        std::cout << "No tiene baldosa a su derecha!" << std::endl;

	return resultado;
}

Coordenadas Baldosa::getArriba(Baldosa actual) {
	Coordenadas resultado{};
	resultado.col = actual.coordenadas.col;

	if (((actual.coordenadas.col < 6) || (actual.coordenadas.row < (5 + actual.coordenadas.col))) ||
		((actual.coordenadas.col > 4) || (actual.coordenadas.row < (15 - actual.coordenadas.col))))
		resultado.row = actual.coordenadas.row + 1;
	// Cuando hay error, TEMPORAL
	else
        resultado.existe = false,
		std::cout << "No tiene baldosa encima!" << std::endl;

	return resultado;
}

Coordenadas Baldosa::getAbajo(Baldosa actual) {
	Coordenadas resultado{};
	resultado.col = actual.coordenadas.col;

	if (actual.coordenadas.row > 0)
		resultado.row = actual.coordenadas.row - 1;
	// Cuando hay error, TEMPORAL
	else
        resultado.existe = false,
		std::cout << "No tiene baldosa abajo!" << std::endl;

	return resultado;
}

Coordenadas Baldosa::getIzqArriba(Baldosa actual) {
	Coordenadas resultado{};
	resultado.col = actual.coordenadas.col - 1;

	if ((actual.coordenadas.col > 0) ||
		((actual.coordenadas.col < 6) && (actual.coordenadas.row < (5 + actual.coordenadas.col))))
		resultado.row = actual.coordenadas.row;
	// Cuando hay error, TEMPORAL
	else
        resultado.existe = false,
		std::cout << "No tiene baldosa arriba a la izquierda!" << std::endl;

	return resultado;
}

Coordenadas Baldosa::getIzqAbajo(Baldosa actual) {
	Coordenadas resultado{};
	resultado.col = actual.coordenadas.col - 1;

	if ((actual.coordenadas.col > 0) ||
		((actual.coordenadas.col < 6) && (actual.coordenadas.row > 0)))
		resultado.row = actual.coordenadas.row - 1;
	// Cuando hay error, TEMPORAL
	else
        resultado.existe = false,
		std::cout << "No tiene baldosa abajo a la izquierda!" << std::endl;

	return resultado;
}

Coordenadas Baldosa::getDerArriba(Baldosa actual) {
	Coordenadas resultado{};
	resultado.col = actual.coordenadas.col + 1;

	if ((actual.coordenadas.col < 10) ||
		((actual.coordenadas.col > 4) && (actual.coordenadas.row < (15 - actual.coordenadas.col))))
		resultado.row = actual.coordenadas.row;
	// Cuando hay error, TEMPORAL
	else
        resultado.existe = false,
		std::cout << "No tiene baldosa arriba a la derecha!" << std::endl;

	return resultado;
}

Coordenadas Baldosa::getDerAbajo(Baldosa actual) {
	Coordenadas resultado{};
	resultado.col = actual.coordenadas.col + 1;

	if ((actual.coordenadas.col < 10) ||
		((actual.coordenadas.col > 4) && (actual.coordenadas.row > 0)))
		resultado.row = actual.coordenadas.row - 1;
	// Cuando hay error, TEMPORAL
	else
        resultado.existe = false,
		std::cout << "No tiene baldosa abajo a la derecha!" << std::endl;

	return resultado;
}


// FUNCIONES EN RATON, MOUSE TRACKING
// UNA NOCHE ENTERA DE TRABAJO QUE NO HA SERVIDO PARA NADA
//void Raton::handlerRaton(int boton, int estado, int x, int y, Linea& linea) {
//	system("CLS");
//
//	bool down = (estado == GLUT_DOWN);
//
//	int button;
//	if (boton == GLUT_LEFT_BUTTON) {
//		button = RI_MOUSE_LEFT_BUTTON_DOWN;
//		std::cout << "Pulsado Izquierda en: ";
//	}
//	if (boton == GLUT_RIGHT_BUTTON) {
//		button = RI_MOUSE_RIGHT_BUTTON_DOWN;
//		std::cout << "Pulsado Derecha en: ";
//	}
//
//	int specialKey = glutGetModifiers();
//	bool ctrlKey = (specialKey & GLUT_ACTIVE_CTRL) ? true : false;
//	bool sKey = specialKey & GLUT_ACTIVE_SHIFT;
//
//	MouseButton(x, y, boton, down, sKey, ctrlKey, linea);
//}
//
//void Raton::MouseButton(int x, int y, int button, bool down, bool sKey, bool ctrlKey, Linea& linea) {
//	float hFar = 2 * tan(Perspectiva::fov / (360 / 3.141592)) * Perspectiva::zfar;
//	float wFar = hFar * (Perspectiva::ancho / Perspectiva::alto);
//	
//	posicionVentana.x = (2.0f * x) / Perspectiva::ancho - 1.0f;
//	posicionVentana.y = 1.0f - (2.0f * y) / Perspectiva::alto;
//
//	std::cout << posicionVentana.x << ", " << posicionVentana.y << std::endl;
//
//	posicionVentana.x = posicionVentana.x * wFar / 2;
//	posicionVentana.y = posicionVentana.y * hFar / 2;
//
//	std::cout << posicionVentana.x << ", " << posicionVentana.y << std::endl;
//
//	Vector3Dfloat normal = (Camara::direccion - Camara::ojo).unitario();
//	Vector3Dfloat lado = (Camara::arriba.crossProduct(normal));
//	Vector3Dfloat arriba = normal.crossProduct(lado);
//
//	Vector3Dfloat offset = normal * 50;
//	//offset = { offset.x, offset.y, 0 };
//
//	posicionMundo = Vector3Dfloat(lado.x * posicionVentana.x + arriba.x * posicionVentana.y,
//		lado.y * posicionVentana.x + arriba.y * posicionVentana.y,
//		lado.z * posicionVentana.x + arriba.z * posicionVentana.y);
//	posicionMundo = posicionMundo + offset;
//	posicionMundo = { -posicionMundo.x, posicionMundo.y, posicionMundo.z };
//
//	std::cout << "Posicion mundo: " << posicionMundo.x << ", " << posicionMundo.y << ", " << posicionMundo.z << std::endl;
//
//	//linea.origen = { posicionMundo.x, posicionMundo.y, 99 };
//	linea.final = posicionMundo;
//}


// FUNCION QUE SE HA USADO PARA PROBAR GLUNPROJECT
// DISCLAIMER: FUNCION REFERENCIADO DEL TABLERO DE EJEMPLO
// QUE SE HA SUBIDO A MOODLE. 
// COGE LAS COORDENADAS DEL RATON.
// ESTE CODIGO ES PROPIEDAD DE PABLO SAN SEGUNDO
//Vector3Dfloat Raton::MouseButton(int x, int y, int button, bool down, bool sKey, bool ctrlKey, Esfera& esfera) {
//	GLint viewport[4];
//	GLdouble modelview[16];
//	GLdouble projection[16];
//	GLfloat winX, winY, winZ;
//	GLdouble posX, posY, posZ;
//
//	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
//	glGetDoublev(GL_PROJECTION_MATRIX, projection);
//	glGetIntegerv(GL_VIEWPORT, viewport);
//
//	winX = (float)x;
//	winY = (float)viewport[3] - (float)y;
//	glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
//	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
//
//	esfera.posicion = { posX, posY, posZ };
//
//	std::cout << "Posicion ventana: " << winX << ", " << winY << std::endl;
//	std::cout << "Posicion OpenGL: " << posX << ", " << posY << ", " << posZ << std::endl;
//
//	return Vector3Dfloat{ posX, posY, posZ };
//}