#ifndef COLAPRIOR_H_
#define COLAPRIOR_H_

#include <vector>

using namespace std;

class ColaPrior {
public:
	ColaPrior();

	// Cantidad de elementos en la cola.
	int tam() const;

	// Encola un elemento.
	void encolar(const int& elem);

	// Devuelve el elemento de mayor prioridad.
	// Pre: tam() > 0
	const int& proximo() const;

	// Saca el elemento de mayor prioridad.
	void desencolar();

	// Constructor que hace heapify.
	ColaPrior(const vector<int>& elems);

private:
    vector<int> _cola;

    int padre(int i);
    void heapify(vector<int> &elem, int i);

};

#endif // COLAPRIOR_H_
