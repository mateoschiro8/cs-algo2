#include "Lista.h"

Lista::Lista(): _primero(nullptr), _ultimo(nullptr), _size(0) { }

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista() {
    Nodo* actual = _primero;
    Nodo* siguiente;
    while(actual != nullptr) {
        siguiente = actual->prox;
        delete actual;
        actual = siguiente;
    }
    _primero = nullptr;
}

Lista& Lista::operator=(const Lista& aCopiar) {
    // Destruye todos los nodos
    Nodo* actual = _primero;
    Nodo* siguiente;
    while(actual != nullptr) {
        siguiente = actual->prox;
        delete actual;
        actual = siguiente;
    }
    _primero = nullptr;
    _ultimo = nullptr; 
    _size = 0;

    // Copia todos los nodos
    actual = aCopiar._primero;
    while(actual != nullptr) {
        agregarAtras(actual->valor);
        actual = actual->prox;
    }
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    Nodo* nuevo = new Nodo(elem);
    if(_primero != nullptr) {
        _primero->prev = nuevo;
        nuevo->prox = _primero;
    } else {
        _ultimo = nuevo;
    }
    _primero = nuevo;
    _size++;
}

void Lista::agregarAtras(const int& elem) {
    Nodo* nuevo = new Nodo(elem);
    if(_primero != nullptr) {
        _ultimo->prox = nuevo;
        nuevo->prev = _ultimo;
    } else {
        _primero = nuevo;
    }
    _ultimo = nuevo;
    _size++;
}

void Lista::eliminar(Nat i) {
    Nodo* actual = _primero;
    Nodo* previo;
    for (int j = 0; j < i; ++j) {
        previo = actual;
        actual = actual->prox;
    }
    if(i != 0) {
        if(i == _size - 1) {
            previo->prox = nullptr;
            _ultimo = previo;
        } else {
            previo->prox = actual->prox;
            previo = actual;
            actual = actual->prox;
            actual->prev = previo->prev;
            actual = previo;
        }
    } else {
        if(actual->prox == nullptr) {
            _primero = nullptr;
            _ultimo = nullptr;
        }
        else {
            _primero = actual->prox;
            _primero->prev = nullptr;
        }
    }
    delete actual;
    _size--;
}

int Lista::longitud() const {
    return _size;
}

const int& Lista::iesimo(Nat i) const {
    Nodo* actual = _primero;
    for (int j = 0; j < i; ++j) {
        actual = actual->prox;
    }
    return actual->valor;
}

int& Lista::iesimo(Nat i) {
    Nodo* actual = _primero;
    for (int j = 0; j < i; ++j) {
        actual = actual->prox;
    }
    return actual->valor;
}

void Lista::mostrar(ostream& o) {
    Nodo* actual = _primero;
    o << "[";
    while(actual != nullptr) {
        if(actual->prox != nullptr) {
            o << actual->valor << ", ";
        } else {
            o << actual->valor;
        }
        actual = actual->prox;
    }
    o << "]" << endl;
}
