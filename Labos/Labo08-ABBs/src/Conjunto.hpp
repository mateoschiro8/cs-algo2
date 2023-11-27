
template <class T>
Conjunto<T>::Conjunto(): _raiz(nullptr), _size(0) { }

template <class T>
Conjunto<T>::~Conjunto() {
    destruir(_raiz);
    _raiz = nullptr;
}

template <class T>
void Conjunto<T>::destruir(Nodo* actual) {
    if (actual != nullptr) {
        destruir(actual->izq);
        destruir(actual->der);
        delete actual;
    }
}


template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    Nodo* actual = _raiz;
    bool existe = false;
    while(actual != nullptr && !existe) {
        if(clave == actual->valor)
            existe = true;
        else {
            if(actual->valor > clave)
                actual = actual->izq;
            else
                actual = actual->der;
        }
    }
    return existe;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    Nodo* actual = _raiz;
    Nodo* previo = nullptr;
    bool fueIzq = false;
    if(!pertenece(clave)) {
        Nodo* nuevo = new Nodo(clave);
        if(actual == nullptr) {
            _raiz = nuevo;
        } else {
            while(actual != nullptr) {
                if(clave < actual->valor) {
                    previo = actual;
                    actual = actual->izq;
                    fueIzq = true;
                } else {
                    previo = actual;
                    actual = actual->der;
                    fueIzq = false;
                }
            }
            if(fueIzq)
                previo->izq = nuevo;
            else
                previo->der = nuevo;
        }
        _size++;
    }
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    Nodo* actual = _raiz;
    Nodo* previo = nullptr;
    Nodo* predecesor = nullptr;
    T buscado = clave;
    bool fueIzq = false;
    bool borre = false;
    if(pertenece(clave)) {
        if(_raiz != nullptr && buscado == _raiz->valor && _raiz->izq == nullptr && _raiz->der == nullptr) {
            delete _raiz;
            _raiz = nullptr;
            _size--;
        } else {
            while(!borre && actual != nullptr) {
                while(actual->valor != buscado && actual != nullptr) {        //Busco el nodo
                    previo = actual;
                    if (actual->valor > buscado) {
                        actual = actual->izq;
                        fueIzq = true;
                    } else {
                        actual = actual->der;
                        fueIzq = false;
                    }
                }

                if(actual->izq == nullptr && actual->der == nullptr) {          // Me fijo si es una hoja
                    if(fueIzq) {
                        previo->izq = nullptr;
                    } else {
                        previo->der = nullptr;
                    }
                    _size--;
                    delete actual;
                    borre = true;
                } else if(actual->izq == nullptr || actual->der == nullptr) {     // Me fijo si tiene 1 hijo
                    if(previo != nullptr) {
                        if(previo->der == actual) {
                            if(actual->izq == nullptr) {
                                previo->der = actual->der;
                            } else {
                                previo->der = actual->izq;
                            }
                        } else {
                            if(actual->izq == nullptr) {
                                previo->izq = actual->der;
                            } else {
                                previo->izq = actual->izq;
                            }
                        }
                    } else {
                        if(actual->der == nullptr)
                            _raiz = _raiz->izq;
                        else
                            _raiz = _raiz->der;
                    }
                    _size--;
                    delete actual;
                    borre = true;
                } else {                                                    // Me fijo si tiene 2 hijos
                    previo = actual;
                    predecesor = actual->izq;
                    fueIzq = true;
                    while(predecesor->der != nullptr) {
                        fueIzq = false;
                        previo = predecesor;
                        predecesor = predecesor->der;
                    }
                    actual->valor = predecesor->valor;
                    buscado = predecesor->valor;
                    actual = predecesor;
                }
            }
        }
    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    Nodo* actual = _raiz;
    Nodo* sig;
    while(actual != nullptr && actual->valor != clave) {
        if(actual->valor > clave) {
            sig = actual;
            actual = actual->izq;
        } else
            actual = actual->der;
    }
    if(actual->der != nullptr) {
        actual = actual->der;
        while(actual != nullptr) {
            sig = actual;
            actual = actual->izq;
        }
    }
    return sig->valor;
}

template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo* actual = _raiz;
    while(actual->izq != nullptr) {
        actual = actual->izq;
    }
    return actual->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo* actual = _raiz;
    while(actual->der != nullptr) {
        actual = actual->der;
    }
    return actual->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
   return _size;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream& o) const {
    o << "[";
    for(int i = minimo(); i < maximo() - 1; i++) {
        if(pertenece(i))
            o << i << ", ";
    }
    o << maximo() << "]" << endl;
}

template <class T>
typename Conjunto<T>::Nodo* Conjunto<T>::buscarNodo(const T &elem) {
    Nodo* actual = _raiz;
    while(actual != nullptr && actual->valor != elem) {
        if(actual->valor > elem)
            actual = actual->izq;
        else
            actual = actual->der;
    }
    return actual;
}
