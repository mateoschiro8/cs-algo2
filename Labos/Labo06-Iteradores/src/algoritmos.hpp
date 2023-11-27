#ifndef ALGO2_LABO_CLASE5_ALGORITMOS_H
#define ALGO2_LABO_CLASE5_ALGORITMOS_H

#include <utility>
#include <iterator>
#include <vector>

// Completar con las funciones del enunciado

/* Original
template <class Contenedor>
typename Contenedor::value_type minimo(const Contenedor& c) {
    typename Contenedor::value_type min = *c.begin();
    typename Contenedor::const_iterator it;
    for(it = c.begin(); it != c.end(); it++) {
        if(*it < min) {
            min = *it;
        }
    }
    return min;
} */

// Modificado
template <class Contenedor>
typename Contenedor::value_type minimo(const Contenedor& c) {
    typename Contenedor::const_iterator min = c.begin();
    typename Contenedor::const_iterator it;
    for(it = c.begin(); it != c.end(); it++) {
        if(*it < *min) {
            min = it;
        }
    }
    return *min;
}

template<class Contenedor>
typename Contenedor::value_type promedio(const Contenedor& c) {
    typename Contenedor::value_type total = 0;
    int cant = 0;
    typename Contenedor::const_iterator it;
    for(it = c.begin(); it != c.end(); it++) {
        total = total + *it;
        cant++;
    }
    return total/cant;
}

/* Original
template<class Iterator>
typename Iterator::value_type minimoIter(const Iterator& desde, const Iterator& hasta) {
    auto min = *desde;
    for(auto i = desde; i != hasta; i++) {
        if(*i < min) {
            min = *i;
        }
    }
    return min;
}
*/

// Modificado
template<class Iterator>
typename Iterator::value_type minimoIter(const Iterator& desde, const Iterator& hasta) {
    Iterator min = desde;
    Iterator it;
    for(it = desde; it != hasta; it++) {
        if(*it < *min) {
            min = it;
        }
    }
    return *min;
}

template<class Iterator>
typename Iterator::value_type promedioIter(const Iterator& desde, const Iterator& hasta) {
    typename Iterator::value_type total = 0;
    int cant = 0;
    for(Iterator it = desde; it != hasta; it++) {
        total = total + *it;
        cant++;
    }
    return total/cant;
}

template<class Contenedor>
void filtrar(Contenedor &c, const typename Contenedor::value_type& elem) {
    typename Contenedor::const_iterator it;
    for(it = c.begin(); it != c.end(); it++) {
        if(*it == elem) {
            c.erase(it);
            it = c.begin();
        }
    }
}

template<class Contenedor>
bool ordenado(Contenedor &c) {
    typename Contenedor::const_iterator it;
    typename Contenedor::const_iterator prox;
    bool orden = true;
    for(it = c.begin(); it != c.end(); it++) {
        prox = it;
        prox++;
        if(prox != c.end() && *it > *prox) {
            orden = false;
        }
    }
    return orden;
}

template<class Contenedor>
std::pair<Contenedor, Contenedor> split(const Contenedor & c, const typename Contenedor::value_type& elem) {
    typename Contenedor::const_iterator it;
    Contenedor p1;
    Contenedor p2;
    for (it = c.begin(); it != c.end(); ++it) {
        if(*it < elem) {
            p1.insert(p1.end(), *it);
        } else {
            p2.insert(p2.end(), *it);
        }
    }
    return make_pair(p1, p2);
}

template <class Contenedor>
void merge(const Contenedor& c1, const Contenedor & c2, Contenedor & res) {
    typename Contenedor::const_iterator it1 = c1.begin();
    typename Contenedor::const_iterator it2 = c2.begin();
    while(it1 != c1.end() && it2 != c2.end()) {
        if(*it1 < *it2) {
            res.insert(res.end(),*it1);
            it1++;
        } else {
            res.insert(res.end(),*it2);
            it2++;
        }
    }
    while(it1 != c1.end()) {
        res.insert(res.end(),*it1);
        it1++;
    }
    while(it2 != c2.end()) {
        res.insert(res.end(),*it2);
        it2++;
    }
}

#endif //ALGO2_LABO_CLASE5_ALGORITMOS_H
