#include "Puesto.h"

Puesto::Puesto(const set<Persona>& personas, Stock& stock, Promociones& promociones, Menu& menu):
                                                                                  _stock(stock), _precios(menu)  {

    // Iteramos todas las personas, y les agregamos gasto 0 y listas de ventas vacias
    set<Persona>::const_iterator it1;
    for (it1 = personas.begin(); it1 != personas.end(); ++it1) {                                 // O(A) *
        _ventasConDesc[*it1] = {};                                                                         // O(log(A))
        _ventasSinDesc[*it1] = {};                                                                         // O(log(A))
        _gasto[*it1] = 0;                                                                                  // O(log(A))
    }

    /* Correcciones sobre la marcha: por la manera en la que funciona nuestro algoritmo de encontrar los descuentos
    (creando el descuento y despues retrocediendolo), es necesario que en descuentos, todos los items tengan definida
     para la cantidad 1, el descuento 0. Asi que hacemos eso acá manualmente.    */

    map<Producto, Nat>::iterator it2;
    _descuentos = promociones;
    for (it2 = stock.begin(); it2 != stock.end() ; ++it2) {                                     // O(I) *
        _descuentos[it2->first][1] = 0;                                                                    // log(I)
    }
}                                                                                            // O(A*log(A) + I*log(I))

void Puesto::iVenderP(Persona persona, Producto producto, Nat cant) {

    // Obtenemos el precio del item y el descuento
    Nat precioI = _precios[producto];                                                                     // O(log(I))
    Nat descuentoI = iDescuento(producto, cant);                                              // O(log(I) + log(cant))

    // Modificamos el stock del item y el gasto de la persona
    _stock[producto] -= cant;                                                                             // O(log(I))
    _gasto[persona] += precioI * cant * (100 - descuentoI)/100;                                           // O(log(A))

    // Nos fijamos si hubo descuento o no, y agregamos la venta a la lista de ventas correspondiente
    if(descuentoI == 0) {
        list<Nat>& l = _ventasSinDesc[persona][producto];                                          // O(log(A))
        l.push_back(cant);
    } else {
        list<Nat>& l = _ventasConDesc[persona][producto];                                          // O(log(A))
        l.push_back(cant);
    }
}                                                                                    // O(log(I) + log(cant) + log(A))

void Puesto::iHackearP(Persona persona, Producto producto) {

    // Aumentamos el stock del producto en 1, y disminuimos el gassto de la persona según el precio del item
    _stock[producto] += 1;                                                                                // O(log(I))
    _gasto[persona] -= _precios[producto];                                                                // O(log(I))

    // Sacamos la 1er venta de ese producto de esa persona y le disminuimos uno a la cantidad, y en caso de que siga
    // habiendo items, la volvemos a agregar con la cantidad disminuida
    Nat cant = _ventasSinDesc[persona][producto].front();                                        // O(log(I) + log(A))
    _ventasSinDesc[persona][producto].pop_front();                                               // O(log(I) + log(A))
    cant--;
    if(cant > 0)
        _ventasSinDesc[persona][producto].push_front(cant);                                   // O(log(I) + log(A))
}                                                                                                // O(log(I) + log(A))

Nat Puesto::iGasto(Persona persona) const {
    return _gasto.at(persona);                                                                        // O(log(A))
}

Nat Puesto::iStock(Producto producto) const {
    return _stock.at(producto);                                                                        // O(log(I))
}

Nat Puesto::iDescuento(Producto producto, Nat cant) const {
    Nat desc = 0;

    // Obtenemos los descuentos para ese item
    map<Nat, Nat> d = _descuentos.at(producto);                                                        // O(log(I))

    if (d.count(cant)) {
        // Si esta definido el descuento para esa cantidad, lo devolvemos
        desc = d[cant];                                                                                // O(log(cant))
    } else {
        // Si no, definimos esa cantidad con descuento 0, vamos a la cantidad menor con descuento definido, y
        // devolvemos esa. En este caso, no es necesario borrar la recién creada, ya que no estamos actualizando
        // en realidad los descuentos, sino que nos guardamos una copia de ellos.
        map<Nat, Nat>::iterator it;
        d[cant] = 0;                                                                                   // O(log(cant))
        it = d.find(cant);                                                                          // O(log(cant))
        it--;
        desc = it->second;
    }
    return desc;                                                                              // O(log(I) + log(cant))
}

list<Nat> Puesto::ventasSinDesc(Persona persona, Producto producto) const {
    if(_ventasSinDesc.count(persona)) {
        if(_ventasSinDesc.at(persona).count(producto))
            return _ventasSinDesc.at(persona).at(producto);
    }
    return {};
}

list<Nat> Puesto::ventasConDesc(Persona persona, Producto producto) const {
    if (_ventasConDesc.count(persona)) {
        if (_ventasConDesc.at(persona).count(producto))
            return _ventasConDesc.at(persona).at(producto);
    }
    return {};
}

Menu Puesto::precios() const {
    return _precios;
}
