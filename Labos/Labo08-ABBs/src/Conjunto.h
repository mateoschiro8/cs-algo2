#ifndef CONJUNTO_H_
#define CONJUNTO_H_

#include <assert.h>
#include <string>
#include <iostream>

using namespace std;

template <class T>
class Conjunto
{
    public:

        Conjunto();  // Constructor. Genera un conjunto vacío.

        ~Conjunto();   // Destructor. Deja limpia la memoria.

        void insertar(const T&);          // Inserta un elemento

        bool pertenece(const T&) const;   // Decide si un elemento pertenece al conjunto.

        void remover(const T&); // Borra un elemento del conjunto (si existe).

        const T& siguiente(const T&);        // Siguiente elemento al recibido por párametro, en orden.

        const T& minimo() const;         // Devuelve el mínimo elemento del conjunto según <.

        const T& maximo() const;             // Devuelve el máximo elemento del conjunto según <.

        unsigned int cardinal() const;         // Cantidad de elementos del conjunto.

        void mostrar(std::ostream&) const;     // Muestra el conjunto.

private:
    struct Nodo
        {
            Nodo(const T& v): valor(v), izq(nullptr), der(nullptr) { }         // El constructor, toma el elemento.
            T valor;                 // El elemento al que representa el nodo.
            Nodo* izq;               // Puntero a la raíz del subárbol izquierdo.
            Nodo* der;               // Puntero a la raíz del subárbol derecho.
        };
    Nodo* _raiz;                 // Puntero a la raíz del árbol.
    int _size;                   // Cantidad de elementos

    Nodo* buscarNodo(const T&);
    void destruir(Nodo* actual);

};

template<class T>
std::ostream& operator<<(std::ostream& os, const Conjunto<T>& c) {
	 c.mostrar(os);
	 return os;
}

#include "Conjunto.hpp"

#endif // CONJUNTO_H_
