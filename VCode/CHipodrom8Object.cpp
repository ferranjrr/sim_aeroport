#include "CHipodrom8Object.h"

using namespace std;

CHipodrom8Object::CHipodrom8Object(CSimulatorObject* simulator, string nom) {
	m_nom = nom;
}

void CHipodrom8Object::showStatistics() {

}

bool CHipodrom8Object::AcceptEntity() { // Se necesita que nos pasen el objeto por parámetro
	return true; // S'ha de comprovar si no està ple?
}
