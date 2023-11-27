#ifndef STRING_MAP_H_
#define STRING_MAP_H_

#include <string>

using namespace std;

template<typename T>
class string_map {
public:

    string_map();        // Constructor. Construye un diccionario vacio

    string_map(const string_map<T>& aCopiar);          // Constructor. Construye un diccionario por copia

    string_map& operator=(const string_map& d);     // Operador asignación

    ~string_map();              // Destructor

    void insert(const pair<string, T> &nuevo);               // Inserta un par clave - valor en el diccionario

    int count(const string &key) const;               // Devuelve cantidad de apariciones de la clave (0 o 1)

    const T& at(const string& key) const;             // Dada una clave, devuelve su significado (no modificable)
    T& atMod(const string& key);                   // Dada una clave, devuelve su significado (modificable)

    void erase(const string& key);              // Dada una clave, la borra del diccionario junto a su significado

    int size() const;                    // Devuelve cantidad de claves definidas

    bool empty() const;               // Devuelve true si no hay ningún elemento en el diccionario

    T &operator[](const string &key);            // Operador [], acceso o definición de pares clave - valor

private:
    struct Nodo {
        vector<Nodo*> siguientes;
        T* definicion;
        Nodo(): siguientes(256, nullptr), definicion(nullptr) {}
    };
    Nodo* _raiz;
    int _size;
    vector<string> _claves;

    void borrarNodo(Nodo* borrar);
};

#include "string_map.hpp"

#endif // STRING_MAP_H_
