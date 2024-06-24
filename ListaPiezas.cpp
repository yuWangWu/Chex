#include "ListaPiezas.h"

//bool ListaPiezas::agregar(Pieza* _pieza) {
//	// Check que no haya otra pieza en la posicion
//	for (Pieza* p : lista)
//		if (_pieza->getPosTablero() == p->getPosTablero())
//			return false;
//
//	lista.push_back(_pieza);
//}
//
//void ListaPiezas::inicializarBlanco() {
//	this->agregar(new Peon({ true, 1, 0 }, true));
//	this->agregar(new Peon({ true, 2, 1 }, true));
//	this->agregar(new Peon({ true, 3, 2 }, true));
//	this->agregar(new Peon({ true, 4, 3 }, true));
//	this->agregar(new Peon({ true, 5, 4 }, true));
//	this->agregar(new Peon({ true, 6, 3 }, true));
//	this->agregar(new Peon({ true, 7, 2 }, true));
//	this->agregar(new Peon({ true, 8, 1 }, true));
//	this->agregar(new Peon({ true, 9, 0 }, true));
//
//	this->agregar(new Torre({ true, 2, 0 }, true));
//	this->agregar(new Torre({ true, 8, 0 }, true));
//
//	this->agregar(new Alfil({ true, 5, 0 }, true));
//	this->agregar(new Alfil({ true, 5, 1 }, true));
//	this->agregar(new Alfil({ true, 5, 2 }, true));
//
//	this->agregar(new Caballo({ true, 3, 0 }, true, true));
//	this->agregar(new Caballo({ true, 7, 0 }, true, true));
//
//	this->agregar(new Rey({ true, 4, 0 }, true));
//	this->agregar(new Reina({ true, 6, 0 }, true));
//}
//
//void ListaPiezas::inicializarNegro() {
//	for (int numero : {1, 2, 3, 4, 5, 6, 7, 8, 9})
//		this->agregar(new Peon(Vector2Dint{ true, numero, 6 }, false));
//	
//	this->agregar(new Torre({ true, 2, 7 }, false));
//	this->agregar(new Torre({ true, 8, 7 }, false));
//
//	this->agregar(new Alfil({ true, 5, 10 }, false));
//	this->agregar(new Alfil({ true, 5, 9 }, false));
//	this->agregar(new Alfil({ true, 5, 8 }, false));
//
//	this->agregar(new Caballo({ true, 3, 8 }, false, false));
//	this->agregar(new Caballo({ true, 7, 8 }, false, false));
//	
//	this->agregar(new Rey({ true, 4, 9 }, false));
//	this->agregar(new Reina({ true, 6, 9 }, false));
//}
//
//void ListaPiezas::asignarPosMundo(Tablero& _tablero) {
//	for (auto p : lista) {
//		p->setPosMundoAnterior(p->getPosMundo());
//		p->setPosMundo(_tablero[p->getPosTablero().col][p->getPosTablero().row].hexagono.getCentro());
//		p->setSincronia(false);
//	}
//}