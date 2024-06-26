#pragma once

// Includes del sistema
#include <iostream>

// Includes del usuario
#include "freeglut.h"
#include "VectoresUtiles.h"

class Raton {
private:
	static Vector2Dfloat posicionVentana;
	// Posicion mundo se refiere a la 
	// posicion en el plano zfar.
	static Vector3Ddouble posicionMundo;

public:
	// Misc 
	//static void handlerRaton(int boton, int estado, int x, int y, Linea& linea);
	//static void MouseButton(int x, int y, int button, bool down, bool sKey, bool ctrlKey, Linea& linea);

	static Vector3Ddouble MouseHandler(int boton, int estado, int x, int y);
	//static Vector3Dfloat MouseButton(int x, int y, int button, bool down, bool sKey, bool ctrlKey, Esfera& esfera);
};

