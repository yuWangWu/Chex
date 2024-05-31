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

// Definicion variables del usuario
Vector2Dfloat Raton::posicionVentana(0, 0);
Vector3Ddouble Raton::posicionMundo(0, 0, 0);

Camara camara({ 0.0, -100.0, 100 }, { 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 });
Perspectiva perspectiva(100.0, 1920, 1080, 0.1, 250);

// Desarrollo
// Borrar despues
ListaPiezas piezasBlancas;
ListaPiezas piezasNegras;
// Fin desarrollo

Tablero tablero;

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

	// Inicializacion de luces y perspectiva.
	// Primero se hace la version en 2D y luego 
	// se pasa a 3D.
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

		// Desarrollo 
		// Borrar despues
		piezasNegras.inicializarNegro();
		piezasBlancas.inicializarBlanco();
		piezasNegras.asignarPosMundo(tablero);
		piezasBlancas.asignarPosMundo(tablero);
		// Fin desarrollo

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

		// Desarrollo
		// Borrar despues
		piezasNegras.dibuja();
		piezasBlancas.dibuja();
		// Fin desarrollo

	// Codigo del usuario termina

	// No borrar
	glutSwapBuffers();
}

void OnKeyboardDown(unsigned char key, int x_t, int y_t) {
	// Codigo del usuario comienza


	// Codigo del usuario termina

	// No borrar
	glutPostRedisplay();
}

// DISCLAIMER: FUNCION REFERENCIADO DEL TABLERO DE EJEMPLO
// QUE SE HA SUBIDO A MOODLE. 
// COGE LAS COORDENADAS DEL RATON.
// ESTE CODIGO ES PROPIEDAD DE PABLO SAN SEGUNDO
void OnMouseClick(int b, int state, int x, int y) {
	// Codigo del usuario comienza
	Raton::MouseHandler(b, state, x, y);
	tablero.seleccionRaton(Raton::MouseHandler(b, state, x, y));

	// Codigo del usuario termina

	// No borrar
	glutPostRedisplay();
}

void OnTimer(int value) {
	// Codigo del usuario comienza

	// Desarrollo
	// Borrar despues
	piezasNegras.mueve();
	piezasBlancas.mueve();
	// Fin desarrollo

	// Codigo del usuario termina

	// No borrar
	glutTimerFunc(0.017, OnTimer, 0);
	glutPostRedisplay();
}
