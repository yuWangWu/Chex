#pragma once
#include "VectoresUtiles.h"
#include "Esfera.h"

class Raton {
public:
	static Vector2Dfloat posicionVentana;
	// Posicion mundo se refiere a la 
	// posicion en el plano zfar.
	static Vector3Dfloat posicionMundo;

public:
	// Misc 
	//static void handlerRaton(int boton, int estado, int x, int y, Linea& linea);
	//static void MouseButton(int x, int y, int button, bool down, bool sKey, bool ctrlKey, Linea& linea);

	static void MouseHandler(int boton, int estado, int x, int y, Esfera& esfera);
	static void MouseButton(int x, int y, int button, bool down, bool sKey, bool ctrlKey, Esfera& esfera);
};

