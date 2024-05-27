#include <iostream>

#include "Raton.h"
#include "freeglut.h"

Vector3Ddouble Raton::MouseHandler(int boton, int estado, int x, int y) {
	system("CLS");

	bool down = (estado == GLUT_DOWN);

	int button;
	if (boton == GLUT_LEFT_BUTTON) {
		button = RI_MOUSE_LEFT_BUTTON_DOWN;
		// Desarrollo
		// Quitar luego
		std::cout << "Pulsado Izquierda en: ";
	}
	if (boton == GLUT_RIGHT_BUTTON) {
		button = RI_MOUSE_RIGHT_BUTTON_DOWN;
		// Desarrollo
		// Quitar luego
		std::cout << "Pulsado Derecha en: ";
	}

	int specialKey = glutGetModifiers();
	bool ctrlKey = (specialKey & GLUT_ACTIVE_CTRL) ? true : false;
	bool sKey = specialKey & GLUT_ACTIVE_SHIFT;

	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);


		// Desarrollo
		// Quitar luego
		std::cout << "Posicion ventana: " << winX << ", " << winY << std::endl;
		std::cout << "Posicion OpenGL: " << posX << ", " << posY << ", " << posZ << std::endl;


	return Vector3Ddouble{ posX, posY, posZ };
}