
template<class T>
ColaPrior<T>::ColaPrior(): _cola({}) { }

template<class T>
int ColaPrior<T>::tam() const {
	return _cola.size();
}

template<class T>
int ColaPrior<T>::padre(int i) {
    return ((i - 1)/2);
}

template<class T>
void ColaPrior<T>::encolar(const T& elem) {
    _cola.push_back(elem);
    int i = tam() - 1;

    while(i > 0 && _cola[i] > _cola[padre(i)]) {
        swap(_cola[padre(i)], _cola[i]);
        i = padre(i);
    }

}

template<class T>
const T& ColaPrior<T>::proximo() const {
	return _cola[0];
}

template<class T>
void ColaPrior<T>::heapify(vector<T> &elem, int i) {
    int izq = 2*i + 1;
    int der = 2*i + 2;
    int max = i;
    if(izq < elem.size() && elem[izq] > elem[max])
        max = izq;
    if(der < elem.size() && elem[der] > elem[max])
        max = der;
    if(max != i) {
        swap(elem[i], elem[max]);
        heapify(elem, max);
    }
}

template<class T>
void ColaPrior<T>::desencolar() {
	int i = tam() - 1;
    _cola[0] = _cola[i];
    _cola.pop_back();
    heapify(_cola, 0);
}

template<class T>
ColaPrior<T>::ColaPrior(const vector<T>& elems) {
	for(int i = 0; i < elems.size(); i++)
        _cola.push_back(elems[i]);
    for(int i = 0; i < elems.size(); i++)
        heapify(_cola, elems.size() - i - 1);
}

