template <typename T>
string_map<T>::string_map(): _raiz(nullptr), _size(0), _claves({}) { }

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; }
// Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    vector<string> claves;
    T valor;

    for(int i = 0; i < _claves.size(); i++)    // Borro todos los que ya estén
        erase(_claves[i]);

    for(int j = 0; j < d._claves.size(); j++) {   // Agrego todos los nuevos
        valor = d.at(d._claves[j]);
        insert(make_pair(d._claves[j],valor));
    }
}

template <typename T>
string_map<T>::~string_map(){
    if(_raiz != nullptr) {
        for (int i = 0; i < 256; ++i) {
            borrarNodo(_raiz->siguientes[i]);
        }
        if (_raiz->definicion != nullptr) {
            delete _raiz->definicion;
        }
        delete _raiz;
    }
}

template <typename T>
void string_map<T>::borrarNodo(Nodo* borrar) {
    if(borrar != nullptr) {
        for (int i = 0; i < 256; ++i) {
            borrarNodo(borrar->siguientes[i]);
        }
        if (borrar->definicion != nullptr) {
            delete borrar->definicion;
        }
        delete borrar;
    }
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    if(count(clave) == 0)
        insert(make_pair(clave, 1));
    return atMod(clave);
}

template <typename T>
void string_map<T>::insert(const pair<string, T> &nuevo) {
    Nodo* actual = _raiz;
    T* def = new T(nuevo.second);

    if(count(nuevo.first) == 0)
        _claves.push_back(nuevo.first);

    if (actual == nullptr) {
        actual = new Nodo();
        _raiz = actual;
        for (int i = 0; i < nuevo.first.size(); ++i) {
            int index = int(nuevo.first[i]);
            actual->siguientes[index] = new Nodo();
            actual = actual->siguientes[index];
        }
        actual->definicion = def;
    } else {
        for (int i = 0; i < nuevo.first.size(); ++i) {
            int index = int(nuevo.first[i]);
            if(actual->siguientes[index] == nullptr) {
                actual->siguientes[index] = new Nodo();
            }
            actual = actual->siguientes[index];
        }
        if(actual->definicion != nullptr)
            delete actual->definicion;
        actual->definicion = def;
    }
    _size++;
}

template <typename T>
int string_map<T>::count(const string& clave) const{
    Nodo* actual = _raiz;
    bool esta = false;
    if(actual != nullptr) {
        esta = true;
        for (int i = 0; i < clave.size() && esta; ++i) {
            if(actual->siguientes[int(clave[i])] != nullptr) {
                actual = actual->siguientes[int(clave[i])];
            } else {
                esta = false;
            }
        }
    }
    if (esta && actual->definicion != nullptr)
        return 1;
    else
        return 0;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo* actual = _raiz;
    for (int i = 0; i < clave.size(); ++i) {
        actual = actual->siguientes[int(clave[i])];
    }
    return *(actual->definicion);
}

template <typename T>
T& string_map<T>::atMod(const string& clave) {
    Nodo* actual = _raiz;
    for (int i = 0; i < clave.size(); ++i) {
        actual = actual->siguientes[int(clave[i])];
    }
    return *(actual->definicion);
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    Nodo* actual = _raiz;
    Nodo* ultDejable = _raiz;
    Nodo* previo = _raiz;
    int indexUltDejable = 0;
    int cantSiguientes = 0;
    for(int i = 0; i < clave.size(); i++) {          // Voy hasta el significado
        actual = actual->siguientes[int(clave[i])];
        for (int j = 0; j < 256; ++j) {    // Me fijo cuantos tiene adelante
            if(actual->siguientes[j] != nullptr)
                cantSiguientes++;
        }
        if(cantSiguientes > 1 || cantSiguientes == 1 && actual->definicion != nullptr) {
            ultDejable = actual;
            indexUltDejable = i;
        }
    }
    if(cantSiguientes > 0) {   // Si tiene alguien más adelante
        delete actual->definicion;
        actual->definicion = nullptr;
    } else { // Si es el ultimo, vuelvo al ultimo lugar donde puedo borrar y borro para abajo
        actual = ultDejable;
        ultDejable->siguientes[int(clave[indexUltDejable])] = nullptr;
        for(int k = indexUltDejable; k < clave.size(); k++) {
            previo = actual;
            actual = actual->siguientes[int(clave[indexUltDejable])];
            delete previo->definicion;
            delete previo;
        }
        delete actual->definicion;
        delete actual;
    }
    _size--;
    for(int i = 0; i < _claves.size(); i++) {
        if(_claves[i] == clave) {
            swap(_claves[i], _claves[_claves.size() - 1]);
            _claves.pop_back();
        }
    }
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    Nodo* actual = _raiz;
    bool hayAlgo = false;
    if(actual != nullptr) {
        for (int i = 0; i < 256 && !hayAlgo; ++i) {
            if(actual->siguientes[i] != nullptr)
                hayAlgo = true;
        }
    }
    return !hayAlgo;
}