#include "Lollapatuza.h"

Lollapatuza::Lollapatuza(const set<Persona>& personas, const map<IdPuesto, Puesto>& infoPuestos):
    _personas(personas), _puestos(infoPuestos) {

    // Creamos los iteradores para las personas, los puestos, y el diccionario de precios
    set<Persona>::const_iterator It1;
    // set<Persona>::const_iterator It2;
    map<IdPuesto, Puesto>::const_iterator It3 = infoPuestos.begin();
    Menu::const_iterator It4;

    // Creamos el conjunto de personas con gasto 0
    set<Persona> PersonasGasto0 = {};

    // Nos guardamos el diccionario de precios
    Menu precios = It3->second.precios();

    // Creamos la tupla para agregar en hackeables
    tuple<IdPuesto, Puesto*, Nat, map<IdPuesto, Nat>, ColaPrior> temp;

    // Iteramos sobre todas las personas. Las insertamos en PersonasGasto0, les definimos gasto 0, y le agregamos
    // una tupla "vacia" en hackeables, por cada item.
    for (It1 = personas.begin(); It1 != personas.end(); ++It1) {                               // O(A) *
        PersonasGasto0.insert(*It1);                                                                  // O(log(A))
        // It2 = PersonasGasto0.find(*It1);
        //  _iteradorAPersona[*It1] = It2;
        _gastos[*It1] = 0;                                                                               // O(log(A))

        for(It4 = precios.begin(); It4 != precios.end(); ++It4) {                              // O(I) *
            temp = {0, nullptr, 0, {}, {}};
            _hackeables[*It1][It4->first] = temp;                                                 // O(log(A) + log(I))
        }
    }

    // Agregamos todas las personas al conjunto de personas con gasto 0
    _personasPorGasto[0] = PersonasGasto0;
}                                                                                          // O(A*I*(log(A) + log(I)))

void Lollapatuza::iVenderL(Persona persona, Producto producto, Nat cant, IdPuesto idPuesto) {

    // Obtenemos el puesto, y registramos la compra en el mismo
    Puesto puesto = _puestos[idPuesto];                                                                   // O(log(P))
    _puestos[idPuesto].iVenderP(persona, producto, cant);                   // O(log(P) + log(I) + log(cant) + log(A))

    // Obtenemos el precio, el descuento y calculamos el gasto de la venta
    Nat descuentoI = puesto.iDescuento(producto, cant);                                       // O(log(I) + log(cant))
    Nat precioI = puesto.precios()[producto];                                                             // O(log(I))
    Nat gastoVenta = precioI * cant * (100 - descuentoI)/100;

    // Obtenemos el gasto viejo de la persona, calculamos el gasto nuevo y lo actualizamos
    Nat viejoGasto = _gastos[persona];                                                                    // O(log(A))
    Nat nuevoGasto = viejoGasto + gastoVenta;
    _gastos[persona] = nuevoGasto;                                                                        // O(log(A))

    // Usamos el gasto viejo para obtener el conjunto donde estaba, y la borramos. Si el conjunto queda vacío,
    // lo eliminamos, y si no, lo actualizamos. Luego, nos fijamos si el conjunto donde debe ir ahora ya existe.
    // Si es asi, simplemente lo agregamos. Si no, lo definimos con la persona

    // set<Persona>::const_iterator It1 = _iteradorAPersona[persona];
    // conjGastoViejo.erase(It1);
    set<Persona> conjGastoViejo = _personasPorGasto[viejoGasto];                                          // O(log(A))
    conjGastoViejo.erase(persona);                                                                     // O(log(A))
    if (conjGastoViejo.empty()) {
        _personasPorGasto.erase(viejoGasto);                                                           // O(log(A))
    } else {
        _personasPorGasto[viejoGasto] = conjGastoViejo;                                                   // O(log(A))
    }
    if(_personasPorGasto.count(nuevoGasto)) {                                                          // O(log(A))
        _personasPorGasto[nuevoGasto].insert(persona);                                                 // O(log(A))
    } else {
        _personasPorGasto[nuevoGasto] = {persona};                                                        // O(log(A))
    }
    // It1 = _personasPorGasto[nuevoGasto].find(persona);
    // _iteradorAPersona[persona] = It1;

    // Nos fijamos si la venta podría ser hackeada (si tuvo descuento 0). Si es así, obtenemos la tupla correspondiente
    // en _hackeables, y vemos que datos debemos actualizar.
    if (descuentoI == 0) {
        tuple<IdPuesto, Puesto*, Nat, map<IdPuesto, Nat>, ColaPrior> tuplaHack;
        tuplaHack = _hackeables[persona][producto];                                              // O(log(A) + log(I))
        IdPuesto idMenorHack = get<0>(tuplaHack);
        Puesto* puestoHack = get<1>(tuplaHack);
        Nat cantVentasHackeables = get<2>(tuplaHack);
        map<IdPuesto, Nat> ventasHackeables = get<3>(tuplaHack);
        ColaPrior IDsHack = get<4>(tuplaHack);

        // Si el puesto ya tiene ventas hackeables, le sumamos una. Si no, lo definimos con una venta, y lo
        // encolamos en el heap de los IDs hackeables.
        if(ventasHackeables.count(idPuesto)) {                                                        // O(log(P))
            ventasHackeables[idPuesto]++;                                                                // O(log(P))
            if(idPuesto == idMenorHack)
                cantVentasHackeables++;
        } else {
            ventasHackeables[idPuesto] = 1;                                                              // O(log(P))
            IDsHack.encolar(idPuesto);                                                             // O(log(P))
        }

        // Luego, nos fijamos si el ID que tenemos guardado como menor es 0. Si es así, significa que no hay ningún
        // puesto guardado como hackeable. Si no, nos fijamos si el ID del puesto es menor al que tenemos guardado
        // como el menor, y en caso de ser así, actualizamos la información del anterior, guardamos el nuevo
        // y actualizamos la referencia.
        if (idMenorHack == 0) {
            idMenorHack = idPuesto;
            puestoHack = &_puestos[idPuesto];                                                            // O(log(P))
            cantVentasHackeables = 1;
        } else if(idPuesto < idMenorHack) {
            ventasHackeables[idMenorHack] = cantVentasHackeables;                                        // O(log(P))
            puestoHack = &_puestos[idPuesto];                                                            // O(log(P))
            idMenorHack = idPuesto;
            cantVentasHackeables = ventasHackeables[idPuesto];                                           // O(log(P))
        }

        // Y actualizamos la tupla en hackeables
        _hackeables[persona][producto] = {idMenorHack, puestoHack, cantVentasHackeables, ventasHackeables, IDsHack};
                                                                                                // O(log(A) + log(I))
 // cOpia todo, cambiar a referencia
    }
}                                                                         // O(log(P) + log(I) + log(A) + log(cant))

void Lollapatuza::iHackear(Persona persona, Producto producto) {

    // Obtenemos la tupla con los datos del puesto a hackear
    tuple<IdPuesto, Puesto*, Nat, map<IdPuesto, Nat>, ColaPrior> tuplaHack;
    tuplaHack = _hackeables[persona][producto];                                                  // O(log(A) + log(I))
    IdPuesto idMenorHack = get<0>(tuplaHack);
    Puesto* puestoHack = get<1>(tuplaHack);
    Nat cantVentasHackeables = get<2>(tuplaHack);
    map<IdPuesto, Nat> ventasHackeables = get<3>(tuplaHack);
    ColaPrior IDsHack = get<4>(tuplaHack);

    // Obtenemos la cantidad de items comprados en la venta a hackear y el item. Sacamos la venta de la lista de ventas,
    // y disminuimos en 1 la cantidad de items comprados. Si la cantidad de items queda mayor a cero (la venta sigue
    // "existiendo"), la volvemos a agregar con un item menos. Si no, no hacemos nada.
    Nat cantItemsComprados = puestoHack->ventasSinDesc(persona, producto).front();                        // O(log(A))
    cantItemsComprados -= 1;

    // Ahora, aplicamos la misma lógica utilizada en la función iVenderL, para ver en qué conjunto de gasto corresponde
    // ubicar a la persona.
    Nat precioI = puestoHack->precios()[producto];
    Nat viejoGasto = _gastos[persona];                                                                    // O(log(A))
    Nat nuevoGasto = viejoGasto - precioI;
    _gastos[persona] = nuevoGasto;                                                                        // O(log(A))

    // Llamamos a Hackear dentro del puesto, que devuelve uno de stock, disminuye el gasto de la persona y
    // modifica sus ventas
    puestoHack->iHackearP(persona, producto);                                                    // O(log(I) + log(A))

    // set<Persona>::const_iterator It1 = _iteradorAPersona[persona];
    // conjGastoViejo.erase(It1);
    set<Persona> conjGastoViejo = _personasPorGasto[viejoGasto];                                          // O(log(A))
    conjGastoViejo.erase(persona);                                                                     // O(log(A))
    if (conjGastoViejo.empty()) {
        _personasPorGasto.erase(viejoGasto);                                                           // O(log(A))
    } else {
        _personasPorGasto[viejoGasto] = conjGastoViejo;                                                   // O(log(A))
    }
    if(_personasPorGasto.count(nuevoGasto)) {                                                          // O(log(A))
        _personasPorGasto[nuevoGasto].insert(persona);                                                 // O(log(A))
    } else {
        _personasPorGasto[nuevoGasto] = {persona};                                                        // O(log(A))
    }
    // It1 = _personasPorGasto[nuevoGasto].find(persona);
    // _iteradorAPersona[persona] = It1;

    // Luego, actualizamos la información de hackeables. Si la venta sigue siendo hackeable, no hacemos nada.
    // Pero si deja de ser hackeable, disminuimos la cantidad de ventas hackeables. Si deja de haber ventas hackeables
    // para ese puesto, nos fijamos si existe otro. Si lo hay, lo ponemos, y sino, volvemos a poner la tupla "vacía".
    if(cantItemsComprados == 0) {
        cantVentasHackeables -= 1;
        if (cantVentasHackeables == 0) {
            ventasHackeables.erase(idMenorHack);                                                       // O(log(P))
            if(IDsHack.tam() == 0) {
                idMenorHack = 0;
                puestoHack = nullptr;
            } else {
                idMenorHack = IDsHack.proximo();
                IDsHack.desencolar();                                                                     // O(log(P))
                puestoHack = &_puestos[idMenorHack];                                                      // O(log(P))
            }
        }
        _hackeables[persona][producto] = {idMenorHack, puestoHack, cantVentasHackeables, ventasHackeables, IDsHack};
                                                                                                 // O(log(A) + log(I))
    }
}                                                                  // O(log(A) + log(I)) / O(log(A) + log(I) + log(P))

Nat& Lollapatuza::iGastoPersona(Persona persona) {
    return _gastos[persona];                                                                              // O(log(A))
}

Persona Lollapatuza::iPersonaMaxGasto() const {

    // Creamos un iterador al ultimo (o mayor) de los conjuntos de personasPorGasto. Luego, creamos un iterador al
    // inicio de ese conjunto, y devolvemos la primer persona. En caso de haber más de una, devuelve la de menor ID.
    map<Nat, set<Persona>>::const_iterator it1 = _personasPorGasto.end();                                   // O(1) #
    it1--;
    set<Persona>::const_iterator it2 = it1->second.begin();                                                   // O(1)
    return *it2;

    // El problema que vemos con tener esta información precalculada en una variable, es que podría darse la situación
    // que, dada una persona que es la de mayor gasto, puede ser hackeada y dejar de ser la de mayor gasto, y
    // habría que recorrer todas las personas para buscar a la nueva, o tenerlas ordenadas en algun tipo de lista.

    // # según https://cplusplus.com/reference/map/map/end/
}                                                                                                              // O(1)

IdPuesto Lollapatuza::iPuestoMenorStock(Producto producto) const {

    // Iteramos sobre todos los puestos. Nos guardamos el primero como el de menor stock, y el stock que posee,
    // y vamos comparando el stock de todos los otros con éste. Si uno tiene menor stock, nos guardamos su ID y
    // el stock, para seguir comparando.
    map<IdPuesto, Puesto>::const_iterator It = _puestos.begin();                                                // O(1)
    Puesto pst = It->second;
    Nat minStockIT = pst.iStock(producto);                                                                 // O(log(I))
    Nat stockIT = 0;
    IdPuesto res = It->first;
    while(It != _puestos.end()) {                                                              // O(P) *
        pst = It->second;
        stockIT = pst.iStock(producto);                                                                    // O(log(I))
        if (stockIT < minStockIT) {
            minStockIT = stockIT;
            res = It->first;
        }
        It++;
    }
    return res;
}                                                                                                        // O(P*log(I))

const set<Persona>& Lollapatuza::iPersonas() const {
    return _personas;
}

map<IdPuesto, Puesto> Lollapatuza::iPuestos() const {
    return _puestos;
}