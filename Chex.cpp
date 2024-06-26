/***********************************************
	Trabajo de Informatica Industrial
	Curso 2023-2024
	
	Proyecto:	Chex
	Integrantes:	Dario Carnes Blasco
			Yu Wang Wu
   
	Descripcion:	Ajedrez Hexagonal
***********************************************/

// Definiciones librerias del sistema
#include <iostream>
// Definiciones librerias del usuario
#include "freeglut.h"
// Definiciones librerias de objetos
#include "Tablero.h"
#include "VectoresUtiles.h"
#include "Camara.h"
#include "Perspectiva.h"
#include "Raton.h"
#include "Esfera.h"
#include "ListaPiezas.h"
#include "MaqEstados.h"

// Definicion variables del usuario
Perspectiva perspectiva(100.0, 1920, 1080, 0.1, 250);
MaqEstados chex;

// Definicion de los Callbacks
void OnDraw(void);
void OnKeyboardDown(unsigned char key, int x, int y);
void OnMouseClick(int button, int state, int x, int y);
void OnTimer(int value);

// Codigo
int main(int argc, char* argv[]) {
	// Inicializacion y creacion de la ventana.
	glutInit(&argc, argv);
	perspectiva.crearVentana();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Chex - Ajedrez Hexagonal");

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	perspectiva.inicializa();

	// Registro de Callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(0.017, OnTimer, 0); // ~60 FPS
	glutKeyboardFunc(OnKeyboardDown);
	glutMouseFunc(OnMouseClick);

	// Infinite Loop
	glutMainLoop();

	return 0;
}

void OnDraw(void) {
	// Borrar pantalla
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Definir punto de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Codigo del usuario comienza
	chex.dibuja();

	// Codigo del usuario termina

	// No borrar
	glutSwapBuffers();
}

void OnKeyboardDown(unsigned char key, int x_t, int y_t) {
	// Codigo del usuario comienza
	chex.tecla(key);

	// Codigo del usuario termina

	// No borrar
	glutPostRedisplay();
}

void OnMouseClick(int b, int state, int x, int y) {
	// Codigo del usuario comienza
	chex.raton(b, state, x, y);

	// Codigo del usuario termina

	// No borrar
	glutPostRedisplay();
}

void OnTimer(int value) {
	// Codigo del usuario comienza
	chex.timer();

	// Codigo del usuario termina

	// No borrar
	glutTimerFunc(0.017, OnTimer, 0);
	glutPostRedisplay();
}
