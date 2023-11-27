#ifndef _LISTA_ALUMNOS_H_
#define _LISTA_ALUMNOS_H_

#include <string>
#include <ostream>

using namespace std;

typedef unsigned long Nat;
 
class Lista {
    public:

        // Constructor por defecto de la clase Lista.
        Lista();

        // Constructor por copia de la clase Lista.
        Lista(const Lista& l);

        // Destructor de la clase Lista.
        ~Lista();

        // Operador asignacion
        Lista& operator=(const Lista& aCopiar);

        // Agrega un elemento al principio de la Lista.
        void agregarAdelante(const int& elem);

        // Agrega un elemento al final de la Lista.
        void agregarAtras(const int& elem);

        // Elimina el i-ésimo elemento de la Lista.
        void eliminar(Nat i);

        // Devuelve la cantidad de elementos que contiene la Lista.
        int longitud() const;

        // Devuelve el elemento en la i-ésima posición de la Lista.
        const int& iesimo(Nat i) const;

        // Devuelve el elemento en la i-ésima posición de la Lista.
        int& iesimo(Nat i);

        // Muestra la lista en un ostream. Formato de salida: [a_0, a_1, a_2, ...]
        void mostrar(ostream& o);

        //Utiliza el método mostrar(os) para sobrecargar el operador <<
        friend ostream& operator<<(ostream& os, Lista& l) {
        l.mostrar(os);
        return os;
    }

    private:
        struct Nodo {
            Nodo* prev;
            Nodo* prox;
            int valor;
            Nodo(int x): valor(x), prev(nullptr), prox(nullptr) {}
        };
        Nodo* _primero;
        Nodo* _ultimo;
        int _size;
};

#endif
