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

// Definicion variables del usuario
Vector3Dfloat ojo(0.0f, 0.0f, 100.0f);
Vector3Dfloat direccion(0.0f, 0.0f, 0.0f);
Vector3Dfloat arriba(0.0f, 1.0f, 0.0f);

Camara camara(ojo, direccion, arriba);
Tablero tablero;

// Definicion de los Callbacks
void OnDraw(void);
void OnKeyboardDown(unsigned char key, int x, int y);
void OnTimer(int value);

// Codigo
int main(int argc, char* argv[]) {
	// Inicializacion y creacion de la ventana.
	glutInit(&argc, argv);
	glutInitWindowSize(1920, 1080);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Chex - Ajedrez Hexagonal");

	// Inicializacion de luces y perspectiva.
	// Primero se hace la version en 2D y luego 
	// se pasa a 3D.
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(100.0, 1920 / 1080.0f, 0.1, 150);

	// Registro de Callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(0.017, OnTimer, 0); // ~60 FPS
	glutKeyboardFunc(OnKeyboardDown);

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
	camara.inicia();
	tablero.dibujar();

	// Codigo del usuario termina

	glutSwapBuffers();
}

void OnKeyboardDown(unsigned char key, int x_t, int y_t) {
	// Codigo del usuario comienza


	// Codigo del usuario termina

	glutPostRedisplay();
}

void OnTimer(int value) {
	// Codigo del usuario comienza


	// Codigo del usuario termina

	glutTimerFunc(0.017, OnTimer, 0);
	glutPostRedisplay();
}
