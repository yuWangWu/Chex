#include "Baldosa.h"

Vector2Dint Baldosa::findbArriba(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero) {
	Vector2Dint resultado{};
	resultado.col = actual.identificador.col;

	if (actual.identificador.row < (tablero[actual.identificador.col].size() - 1))
		// Caso positivo
		resultado.row = actual.identificador.row + 1;
	else
		// Caso negativo
		resultado.existe = false;

	return resultado;
}

Vector2Dint Baldosa::findbAbajo(Baldosa actual) {
	Vector2Dint resultado{};
	resultado.col = actual.identificador.col;

	if (actual.identificador.row > 0)
		// Caso positivo
		resultado.row = actual.identificador.row - 1;
	else
		// Caso negativo
		resultado.existe = false;

	return resultado;
}

Vector2Dint Baldosa::findbIzqArriba(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero) {
	Vector2Dint resultado{};
	
	if ((actual.identificador.col < 1) ||
		((actual.identificador.col < 6) && (actual.identificador.row == (tablero[actual.identificador.col].size() - 1)))) {
		// Caso negativo
		resultado.existe = false;
	}
	else {
		// Caso positivo
		resultado.col = actual.identificador.col - 1;
		resultado.row = (actual.identificador.col < 6) ? actual.identificador.row : actual.identificador.row + 1;
	}

	return resultado;
}

Vector2Dint Baldosa::findbIzqAbajo(Baldosa actual) {
	Vector2Dint resultado{};

	if ((actual.identificador.col < 1) ||
		((actual.identificador.col < 6) && (actual.identificador.row < 1))) {
		// Caso negativo
		resultado.existe = false;
	}
	else {
		// Caso positivo
		resultado.col = actual.identificador.col - 1;
		resultado.row = (actual.identificador.col < 6) ? actual.identificador.row - 1 : actual.identificador.row;
	}

	return resultado;
}

Vector2Dint Baldosa::findbDerArriba(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero) {
	Vector2Dint resultado{};

	if ((actual.identificador.col > 9) ||
		((actual.identificador.col > 4) && (actual.identificador.row == (tablero[actual.identificador.col].size() - 1)))) {
		// Caso negativo
		resultado.existe = false;
	}
	else {
		// Caso positivo
		resultado.col = actual.identificador.col + 1;
		resultado.row = (actual.identificador.col < 5) ? actual.identificador.row + 1 : actual.identificador.row;
	}

	return resultado;
}

Vector2Dint Baldosa::findbDerAbajo(Baldosa actual) {
	Vector2Dint resultado{};

	if ((actual.identificador.col > 9) ||
		((actual.identificador.col > 4) && (actual.identificador.row < 1))) {
		// Caso negativo 
		resultado.existe = false;
	}
	else {
		// Caso positivo
		resultado.col = actual.identificador.col + 1;
		resultado.row = (actual.identificador.col < 5) ? actual.identificador.row : actual.identificador.row - 1;
	}

	return resultado;
}

Vector2Dint Baldosa::findbEsqIzquierda(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero) {
	Vector2Dint resultado{};

	if ((actual.identificador.col < 2) ||
		((actual.identificador.col < 6) && (actual.identificador.row < 1)) ||
		((actual.identificador.col < 6) && (actual.identificador.row == (tablero[actual.identificador.col].size() - 1)))) {
		// Caso negativo
		resultado.existe = false;
	}
	else {
		// Caso positivo
		resultado.col = actual.identificador.col - 2;
		resultado.row = (actual.identificador.col < 6) ? actual.identificador.row - 1 :
			(actual.identificador.col > 6) ? actual.identificador.row + 1 : actual.identificador.row;
	}

	return resultado;
}

Vector2Dint Baldosa::findbEsqDerecha(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero) {
	Vector2Dint resultado{};

	if ((actual.identificador.col > 8) ||
		((actual.identificador.col > 4) && (actual.identificador.row < 1)) ||
		((actual.identificador.col > 4) && (actual.identificador.row == (tablero[actual.identificador.col].size() - 1)))) {
		// Caso negativo
		resultado.existe = false;
	}
	else {
		// Caso positivo
		resultado.col = actual.identificador.col + 2;
		resultado.row = (actual.identificador.col > 4) ? actual.identificador.row - 1 :
			(actual.identificador.col < 4) ? actual.identificador.row + 1 : actual.identificador.row;
	}

	return resultado;
}

Vector2Dint Baldosa::findbEsqIzqArriba(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero) {
	Vector2Dint resultado{};

	// linea problematica
	actual.identificador = findbIzqArriba(actual, tablero);
	if (actual.identificador.existe == false) {
		resultado.existe = false;
		return resultado;
	}
	resultado = findbArriba(actual, tablero); 
	// si no existe el metodo ya aplica false
	
	return resultado;
}

Vector2Dint Baldosa::findbEsqIzqAbajo(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero) {
	Vector2Dint resultado{};

	actual.identificador = findbIzqAbajo(actual);
	if (actual.identificador.existe == false) {
		resultado.existe = false;
		return resultado;
	}
	resultado = findbAbajo(actual);
	// si no existe el metodo ya aplica false

	return resultado;
}

Vector2Dint Baldosa::findbEsqDerArriba(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero) {
	Vector2Dint resultado{};

	actual.identificador = findbDerArriba(actual, tablero);
	if (actual.identificador.existe == false) {
		resultado.existe = false;
		return resultado;
	}
	resultado = findbArriba(actual, tablero);
	// si no existe el metodo ya aplica false

	return resultado;
}

Vector2Dint Baldosa::findbEsqDerAbajo(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero) {
	Vector2Dint resultado{};

	actual.identificador = findbDerAbajo(actual);
	if (actual.identificador.existe == false) {
		resultado.existe = false;
		return resultado;
	}
	resultado = findbAbajo(actual);
	// si no existe el metodo ya aplica false

	return resultado;
}

Vector2Dint Baldosa::findbCaballoDerArriba(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero) {
	Vector2Dint resultado{};

	actual.identificador = findbEsqDerecha(actual, tablero);
	if (actual.identificador.existe == false) {
		resultado.existe = false;
		return resultado;
	}
	resultado = findbDerArriba(actual, tablero);
	// si no existe, el metodo ya aplica false

	return resultado;
}

Vector2Dint Baldosa::findbCaballoDerAbajo(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero) {
	Vector2Dint resultado{};

	actual.identificador = findbEsqDerecha(actual, tablero);
	if (actual.identificador.existe == false) {
		resultado.existe = false;
		return resultado;
	}
	resultado = findbDerAbajo(actual);
	// si no existe, el metodo ya palica false

	return resultado;
}

Vector2Dint Baldosa::findbCaballoIzqArriba(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero) {
	Vector2Dint resultado{};

	actual.identificador = findbEsqIzquierda(actual, tablero);
	if (actual.identificador.existe == false) {
		resultado.existe = false;
		return resultado;
	}
	resultado = findbIzqArriba(actual, tablero);
	// si no existe, el metodo ya aplica false

	return resultado;
}

Vector2Dint Baldosa::findbCaballoIzqAbajo(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero) {
	Vector2Dint resultado{};

	actual.identificador = findbEsqIzquierda(actual, tablero);
	if (actual.identificador.existe == false) {
		resultado.existe = false;
		return resultado;
	}
	resultado = findbIzqAbajo(actual);
	// si no existe, el metodo ya aplica false

	return resultado;
}

Vector2Dint Baldosa::findbCaballoEsqIzqArrArriba(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero) {
	Vector2Dint resultado{};

	actual.identificador = findbEsqIzqArriba(actual, tablero);
	if (actual.identificador.existe == false) {
		resultado.existe = false;
		return resultado;
	}
	resultado = findbArriba(actual, tablero);
	// si no existe, el metodo ya aplica false

	return resultado;
}

Vector2Dint Baldosa::findbCaballoEsqIzqArrAbajo(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero) {
	Vector2Dint resultado{};

	actual.identificador = findbEsqIzqArriba(actual, tablero);
	if (actual.identificador.existe == false) {
		resultado.existe = false;
		return resultado;
	}
	resultado = findbIzqArriba(actual, tablero);
	// si no existe, el metodo ya aplica false

	return resultado;
}

Vector2Dint Baldosa::findbCaballoEsqDerArrArriba(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero) {
	Vector2Dint resultado{};

	actual.identificador = findbEsqDerArriba(actual, tablero);
	if (actual.identificador.existe == false) {
		resultado.existe = false;
		return resultado;
	}
	resultado = findbArriba(actual, tablero);
	// si no existe el metodo ya aplica flase

	return resultado;
}

Vector2Dint Baldosa::findbCaballoEsqDerArrAbajo(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero) {
	Vector2Dint resultado{};

	actual.identificador = findbEsqDerArriba(actual, tablero);
	if (actual.identificador.existe == false) {
		resultado.existe = false;
		return resultado;
	}
	resultado = findbDerArriba(actual, tablero);
	// si no existe el metodo ya aplica false;

	return resultado;
}

Vector2Dint Baldosa::findbCaballoEsqIzqAbjArriba(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero) {
	Vector2Dint resultado{};

	actual.identificador = findbEsqIzqAbajo(actual, tablero);
	if (actual.identificador.existe == false) {
		resultado.existe = false;
		return resultado;
	}
	resultado = findbIzqAbajo(actual);
	// si no existe el metodo ya aplica false

	return resultado;
}

Vector2Dint Baldosa::findbCaballoEsqIzqAbjAbajo(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero) {
	Vector2Dint resultado{};

	actual.identificador = findbEsqIzqAbajo(actual, tablero);
	if (actual.identificador.existe == false) {
		resultado.existe = false;
		return resultado;
	}
	resultado = findbAbajo(actual);
	// si no existe el metodo ya aplica false

	return resultado;
}

Vector2Dint Baldosa::findbCaballoEsqDerAbjArriba(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero) {
	Vector2Dint resultado{};

	actual.identificador = findbEsqDerAbajo(actual, tablero);
	if (actual.identificador.existe == false) {
		resultado.existe = false;
		return resultado;
	}
	resultado = findbDerAbajo(actual);
	// si no existe el metodo ya aplica false

	return resultado;
}

Vector2Dint Baldosa::findbCaballoEsqDerAbjAbajo(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero) {
	Vector2Dint resultado{};

	actual.identificador = findbEsqDerAbajo(actual, tablero);
	if (actual.identificador.existe == false) {
		resultado.existe = false;
		return resultado;
	}
	resultado = findbAbajo(actual);
	// si no existe el metodo ya aplica false

	return resultado;
}

void Baldosa::findPosicionesTodas(Baldosa actual, const std::vector<std::vector<Baldosa>>& tablero) {
	bArriba = findbArriba(actual, tablero);
	bAbajo = findbAbajo(actual);
	bIzqArriba = findbIzqArriba(actual, tablero);
	bIzqAbajo = findbIzqAbajo(actual);
	bDerArriba = findbDerArriba(actual, tablero);
	bDerAbajo = findbDerAbajo(actual);

	bEsqIzquierda = findbEsqIzquierda(actual, tablero);
	bEsqDerecha = findbEsqDerecha(actual, tablero);
	bEsqIzqArriba = findbEsqIzqArriba(actual, tablero);
	bEsqIzqAbajo = findbEsqIzqAbajo(actual, tablero);
	bEsqDerArriba = findbEsqDerArriba(actual, tablero);
	bEsqDerAbajo = findbEsqDerAbajo(actual, tablero);
	
	bCaballoDerArriba = findbCaballoDerArriba(actual, tablero);
	bCaballoDerAbajo = findbCaballoDerAbajo(actual, tablero);
	bCaballoIzqArriba = findbCaballoIzqArriba(actual, tablero);
	bCaballoIzqAbajo = findbCaballoIzqAbajo(actual, tablero);
	bCaballoEsqIzqArrArriba = findbCaballoEsqIzqArrArriba(actual, tablero);
	bCaballoEsqIzqArrAbajo = findbCaballoEsqIzqArrAbajo(actual, tablero);
	bCaballoEsqDerArrArriba = findbCaballoEsqDerArrArriba(actual, tablero);
	bCaballoEsqDerArrAbajo = findbCaballoEsqDerArrAbajo(actual, tablero);
	bCaballoEsqIzqAbjArriba = findbCaballoEsqIzqAbjArriba(actual, tablero);
	bCaballoEsqIzqAbjAbajo = findbCaballoEsqIzqAbjAbajo(actual, tablero);
	bCaballoEsqDerAbjArriba = findbCaballoEsqDerAbjArriba(actual, tablero);
	bCaballoEsqDerAbjAbajo = findbCaballoEsqDerAbjAbajo(actual, tablero);
}
