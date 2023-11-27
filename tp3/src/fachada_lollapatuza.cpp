#include "fachada_lollapatuza.h"

FachadaLollapatuza::FachadaLollapatuza(const set<Persona> &personas, const map<IdPuesto, aed2_Puesto> &infoPuestos) {

    map<IdPuesto, Puesto> nuevosPuestos = {};                      // Nuevo diccionario de puestos
    aed2_Puesto pst;                                               // Puestos de la fachada que serán adaptados a nuestra clase
    map<IdPuesto, aed2_Puesto>::const_iterator It;                 // Iterador para los puestos
    Menu menu;
    Stock stock;
    Promociones promociones;
    IdPuesto ID;

    for (It = infoPuestos.begin(); It != infoPuestos.end(); ++It) {   // Itero sobre todos los puestos
        ID = It->first;
        pst = It->second;
        menu = pst.menu;
        stock = pst.stock;
        promociones = pst.promociones;
        Puesto p = Puesto(personas, stock, promociones, menu);      // Utilizo el constructor de los nuevos puestos
//        nuevosPuestos.at(ID) = p;
        nuevosPuestos[ID] = p;
    }
    _lolla = new Lollapatuza(personas, nuevosPuestos);

}

FachadaLollapatuza::~FachadaLollapatuza() {
    delete _lolla;
}

void FachadaLollapatuza::registrarCompra(Persona persona, Producto producto, Nat cant, IdPuesto idPuesto) {
    _lolla->iVenderL(persona, producto, cant, idPuesto);
}

void FachadaLollapatuza::hackear(Persona persona, Producto producto) {
    _lolla->iHackear(persona, producto);
}

Nat FachadaLollapatuza::gastoTotal(Persona persona) const {
    return _lolla->iGastoPersona(persona);
}

Persona FachadaLollapatuza::mayorGastador() const {
    return _lolla->iPersonaMaxGasto();
}

IdPuesto FachadaLollapatuza::menorStock(Producto producto) const {
    return _lolla->iPuestoMenorStock(producto);
}

const set<Persona> &FachadaLollapatuza::personas() const {
    return _lolla->iPersonas();
}

Nat FachadaLollapatuza::stockEnPuesto(IdPuesto idPuesto, const Producto &producto) const {
    return _lolla->iPuestos().at(idPuesto).iStock(producto);
}

Nat FachadaLollapatuza::descuentoEnPuesto(IdPuesto idPuesto, const Producto &producto, Nat cantidad) const {
    return _lolla->iPuestos()[idPuesto].iDescuento(producto, cantidad);
}

Nat FachadaLollapatuza::gastoEnPuesto(IdPuesto idPuesto, Persona persona) const {
    return _lolla->iPuestos()[idPuesto].iGasto(persona);
}

list<Nat> FachadaLollapatuza::ventasSinDescEnPuesto(IdPuesto idPuesto, Persona persona, Producto producto) const {
    return _lolla->iPuestos()[idPuesto].ventasSinDesc(persona, producto);
}

list<Nat> FachadaLollapatuza::ventasConDescEnPuesto(IdPuesto idPuesto, Persona persona, Producto producto) const {
    return _lolla->iPuestos()[idPuesto].ventasConDesc(persona, producto);
}


set<IdPuesto> FachadaLollapatuza::idsDePuestos() const {
    set<IdPuesto> IDS = {};
    map<IdPuesto,Puesto> puestos = _lolla->iPuestos();
    map<IdPuesto,Puesto>::const_iterator It;
    for(It  = puestos.begin(); It != puestos.end(); It++) {
        IDS.insert(It->first);
    }
    return IDS;
}