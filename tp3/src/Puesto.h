#ifndef TP_LOLLA_PUESTO_H
#define TP_LOLLA_PUESTO_H

#include "tipos.h"

class Puesto {
public:
    Puesto() = default;
    Puesto(const set<Persona>& personas, Stock& stock, Promociones& promociones, Menu& menu);

    void iVenderP(Persona persona, Producto producto, Nat cant);
    void iHackearP(Persona persona, Producto producto);

    Nat iGasto(Persona persona) const;
    Nat iStock(Producto producto) const;
    Nat iDescuento(Producto producto, Nat cant) const;

    // Para facilitar los tests y armado del festival:
    Menu precios() const;
    list<Nat> ventasSinDesc(Persona persona, Producto producto) const;
    list<Nat> ventasConDesc(Persona persona, Producto producto) const;

private:
    Stock _stock;
    map<Persona, Nat> _gasto;
    Menu _precios;
    Promociones _descuentos;
    map<Persona, map<Producto, list<Nat>>> _ventasConDesc;
    map<Persona, map<Producto, list<Nat>>> _ventasSinDesc;

};

#endif //TP_LOLLA_PUESTO_H
