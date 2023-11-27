#include "../src/fachada_lollapatuza.h"
#include "gtest-1.8.1/gtest.h"
#include <set>

using namespace std;

class LollaGrupoTest : public testing::Test {
protected:
    Menu menu;
    set<Persona> personas, personas89, personas49;
    set<IdPuesto> idsPuestos;
    Stock stock2, stock6, stock7;
    Promociones descuentos2, descuentos6, descuentos7;
    Puesto puesto2, puesto6, puesto7;
    map<IdPuesto, Puesto> puestos;

    void SetUp() {
        menu = {{3, 500}, {4, 1000}, {5, 2500}, {7, 2000}};
        personas = {2, 4, 8, 9};
        idsPuestos = {2, 6, 7};
        stock2 = {{3, 10}, {4, 5}, {5, 30}, {7, 10}};
        stock6 = {{3, 5}, {4, 15}, {5, 25}, {7, 5}};
        stock7 = {{3, 20}, {4, 20}, {5, 20}, {7, 20}};
        descuentos2 = {{7, {{3, 20}, {6, 25}}}};
        descuentos6 = {{4, {{4, 15}}}};
        descuentos7 = {{3, {{5, 30}}}, {7, {{2, 10}}}};
        puesto2 = Puesto(personas, stock2, descuentos2, menu);
        puesto6 = Puesto(personas,stock6, descuentos6, menu);
        puesto7 = Puesto(personas,stock7, descuentos7, menu);
        puestos = {{2, puesto2}, {6, puesto6}, {7, puesto7}};
    }
};

TEST_F(LollaGrupoTest, CrearLolla) {
    Lollapatuza l(personas, puestos);

    for (const Persona& p : personas) {
        EXPECT_EQ(l.iGastoPersona(p), 0);
    }

    EXPECT_EQ(personas.count(l.iPersonaMaxGasto()), 1);
    EXPECT_EQ(l.iPersonaMaxGasto(), 2);

    EXPECT_EQ(l.iPuestoMenorStock(3), 6);
    EXPECT_EQ(l.iPuestoMenorStock(4), 2);
    EXPECT_EQ(l.iPuestoMenorStock(5), 7);
    EXPECT_EQ(l.iPuestoMenorStock(7), 6);
}

TEST_F(LollaGrupoTest, CompraSinDescCambiaMenorStock) {
    Lollapatuza l(personas, puestos);

    for (const Persona& p : personas) {
        EXPECT_EQ(l.iGastoPersona(p), 0);
    }

    EXPECT_EQ(personas.count(l.iPersonaMaxGasto()), 1);
    EXPECT_EQ(l.iPersonaMaxGasto(), 2);

    EXPECT_EQ(l.iPuestoMenorStock(3), 6);
    EXPECT_EQ(l.iPuestoMenorStock(4), 2);
    EXPECT_EQ(l.iPuestoMenorStock(5), 7);
    EXPECT_EQ(l.iPuestoMenorStock(7), 6);


    // Compra 4 cocas 2 veces en puesto 2, y cambia puesto menor stock de la Coca de 6 a 2

    Producto Coca = 3;
    Persona Juan = 4;
    IdPuesto IdMostaza = 2;
    Nat cant = 4;
    list<Nat> ventasSDescMostaza = {cant, cant};
    list<Nat> ventasCDescMostaza = {};

    Puesto Mostaza = l.iPuestos()[IdMostaza];
    EXPECT_EQ(Mostaza.iStock(Coca), 10);

    l.iVenderL(Juan, Coca, cant, IdMostaza);
    l.iVenderL(Juan, Coca, cant, IdMostaza);

    Mostaza = l.iPuestos()[IdMostaza];
    Nat gastoJuan = 2 * (cant * Mostaza.precios()[Coca] * (100 - Mostaza.iDescuento(Coca, cant))/100);

    EXPECT_EQ(l.iPuestoMenorStock(3), IdMostaza);
    EXPECT_EQ(l.iGastoPersona(Juan), gastoJuan);
    EXPECT_EQ(l.iPersonaMaxGasto(), Juan);
    EXPECT_EQ(Mostaza.ventasSinDesc(Juan, Coca), ventasSDescMostaza);
    EXPECT_EQ(Mostaza.ventasConDesc(Juan, Coca), ventasCDescMostaza);
}

TEST_F(LollaGrupoTest, CompraConDescNoCambiaMenorStock) {
    Lollapatuza l(personas, puestos);

    for (const Persona& p : personas) {
        EXPECT_EQ(l.iGastoPersona(p), 0);
    }

    EXPECT_EQ(personas.count(l.iPersonaMaxGasto()), 1);
    EXPECT_EQ(l.iPersonaMaxGasto(), 2);

    EXPECT_EQ(l.iPuestoMenorStock(3), 6);
    EXPECT_EQ(l.iPuestoMenorStock(4), 2);
    EXPECT_EQ(l.iPuestoMenorStock(5), 7);
    EXPECT_EQ(l.iPuestoMenorStock(7), 6);

    Producto PapasFritas = 4;
    Persona Juan = 4;
    IdPuesto IdMcDonalds = 6;
    Nat cant = 4;
    list<Nat> ventasSDescMcDonalds = {};
    list<Nat> ventasCDescMcDonalds = {cant, cant};

    l.iVenderL(Juan, PapasFritas, cant, IdMcDonalds);
    l.iVenderL(Juan, PapasFritas, cant, IdMcDonalds);

    Puesto McDonalds = l.iPuestos()[IdMcDonalds];
    Nat gastoJuan = 2 * (cant * McDonalds.precios()[PapasFritas] * (100 - McDonalds.iDescuento(PapasFritas, cant))/100);

    EXPECT_EQ(l.iPuestoMenorStock(4), 2);
    EXPECT_EQ(l.iGastoPersona(Juan), gastoJuan);
    EXPECT_EQ(l.iPersonaMaxGasto(), Juan);
    EXPECT_EQ(McDonalds.ventasSinDesc(Juan, PapasFritas), ventasSDescMcDonalds);
    EXPECT_EQ(McDonalds.ventasConDesc(Juan, PapasFritas), ventasCDescMcDonalds);

}

TEST_F(LollaGrupoTest, HackearCompraCambiaMaxGastador) {
    Lollapatuza l(personas, puestos);

    for (const Persona& p : personas) {
        EXPECT_EQ(l.iGastoPersona(p), 0);
    }

    EXPECT_EQ(personas.count(l.iPersonaMaxGasto()), 1);
    EXPECT_EQ(l.iPersonaMaxGasto(), 2);

    EXPECT_EQ(l.iPuestoMenorStock(3), 6);
    EXPECT_EQ(l.iPuestoMenorStock(4), 2);
    EXPECT_EQ(l.iPuestoMenorStock(5), 7);
    EXPECT_EQ(l.iPuestoMenorStock(7), 6);

    // Compra 4 cocas 2 veces en puesto 2, y cambia puesto menor stock de la Coca de 6 a 2

    Producto Coca = 3;
    Producto Pancho = 5;
    Persona Juan = 4;
    Persona Rosa = 9;
    Nat cant1 = 3;
    Nat cant2 = 1;
    IdPuesto IdMostaza = 2;
    Puesto Mostaza = l.iPuestos()[IdMostaza];
    list<Nat> ventasSDescJuan = {cant1,cant1};
    list<Nat> ventasCDescJuan = {};
    list<Nat> ventasSDescRosa = {cant2};
    list<Nat> ventasCDescRosa = {};
    Nat gastoJuan = (cant1 * Mostaza.precios()[Coca] * (100 - Mostaza.iDescuento(Coca, cant1))/100) +
                    (cant1 * Mostaza.precios()[Coca] * (100 - Mostaza.iDescuento(Coca, cant1))/100);
    Nat gastoRosa = (cant2 * Mostaza.precios()[Pancho] * (100 - Mostaza.iDescuento(Pancho, cant2))/100);

    l.iVenderL(Juan, Coca, cant1, IdMostaza);
    l.iVenderL(Juan, Coca, cant1, IdMostaza);
    l.iVenderL(Rosa, Pancho, cant2, IdMostaza);

    Mostaza = l.iPuestos()[IdMostaza];

    EXPECT_EQ(l.iGastoPersona(Juan), gastoJuan);
    EXPECT_EQ(l.iGastoPersona(Rosa), gastoRosa);
    EXPECT_EQ(l.iPersonaMaxGasto(), Juan);
    EXPECT_EQ(Mostaza.ventasSinDesc(Juan, Coca), ventasSDescJuan);
    EXPECT_EQ(Mostaza.ventasConDesc(Juan, Coca), ventasCDescJuan);
    EXPECT_EQ(Mostaza.ventasSinDesc(Rosa, Pancho), ventasSDescRosa);
    EXPECT_EQ(Mostaza.ventasConDesc(Rosa, Pancho), ventasCDescRosa);
    EXPECT_EQ(Mostaza.iStock(Coca), 4);
    EXPECT_EQ(Mostaza.iStock(Pancho), 29);

    l.iHackear(Juan, Coca);
    l.iHackear(Juan, Coca);

    Mostaza = l.iPuestos()[IdMostaza];
    EXPECT_EQ(Mostaza.iStock(Coca), 6);
    EXPECT_EQ(l.iPersonaMaxGasto(), Rosa);

    gastoJuan -= 2 * Mostaza.precios()[Coca];
    ventasSDescJuan = {cant1 - 2, cant1};

    EXPECT_EQ(Mostaza.ventasSinDesc(Juan, Coca), ventasSDescJuan);
    EXPECT_EQ(Mostaza.ventasConDesc(Juan, Coca), ventasCDescJuan);
    EXPECT_EQ(Mostaza.ventasSinDesc(Rosa, Pancho), ventasSDescRosa);
    EXPECT_EQ(Mostaza.ventasConDesc(Rosa, Pancho), ventasCDescRosa);
    EXPECT_EQ(l.iGastoPersona(Juan), gastoJuan);
    EXPECT_EQ(l.iGastoPersona(Rosa), gastoRosa);

    l.iHackear(Rosa, Pancho);
    Mostaza = l.iPuestos()[IdMostaza];

    EXPECT_EQ(Mostaza.iStock(Pancho), 30);
    EXPECT_EQ(l.iPersonaMaxGasto(), Juan);

    gastoRosa -= Mostaza.precios()[Pancho];
    ventasSDescRosa = {};

    EXPECT_EQ(l.iGastoPersona(Juan), gastoJuan);
    EXPECT_EQ(l.iGastoPersona(Rosa), gastoRosa);

    EXPECT_EQ(Mostaza.ventasSinDesc(Juan, Coca), ventasSDescJuan);
    EXPECT_EQ(Mostaza.ventasConDesc(Juan, Coca), ventasCDescJuan);
    EXPECT_EQ(Mostaza.ventasSinDesc(Rosa, Pancho), ventasSDescRosa);
    EXPECT_EQ(Mostaza.ventasConDesc(Rosa, Pancho), ventasCDescRosa);
}

   // Tests Lolla

class LollaTest : public testing::Test {
protected:
    Menu menu;
    set<Persona> personas, personas89, personas49;
    set<IdPuesto> idsPuestos;
    Stock stock2, stock6, stock7;
    Promociones descuentos2, descuentos6, descuentos7;
    aed2_Puesto puesto2, puesto6, puesto7;
    map<IdPuesto, aed2_Puesto> puestos;

    void SetUp() {
        menu = {{3, 500}, {4, 1000}, {5, 2500}, {7, 2000}};
        personas = {2, 4, 8, 9};
        personas89 = {8, 9};
        personas49 = {4, 9};
        idsPuestos = {2, 6, 7};
        stock2 = {{3, 10}, {4, 5}, {5, 30}, {7, 10}};
        stock6 = {{3, 5}, {4, 15}, {5, 25}, {7, 5}};
        stock7 = {{3, 20}, {4, 20}, {5, 20}, {7, 20}};
        descuentos2 = {{7, {{3, 20}, {6, 25}}}};
        descuentos6 = {{4, {{4, 15}}}};
        descuentos7 = {{3, {{5, 30}}}, {7, {{2, 10}}}};
        puesto2 = {stock2, descuentos2, menu};
        puesto6 = {stock6, descuentos6, menu};
        puesto7 = {stock7, descuentos7, menu};
        puestos = {{2, puesto2}, {6, puesto6}, {7, puesto7}};
    }
};

TEST_F(LollaTest, arrancar_lolla) {
    FachadaLollapatuza l(personas, puestos);

    for (const Persona& p : personas) {
        EXPECT_EQ(l.gastoTotal(p), 0);
    }
    EXPECT_EQ(personas.count(l.mayorGastador()), 1);
    EXPECT_EQ(l.menorStock(3), 6);
    EXPECT_EQ(l.menorStock(4), 2);
    EXPECT_EQ(l.menorStock(5), 7);
    EXPECT_EQ(l.menorStock(7), 6);
    EXPECT_EQ(l.personas(), personas);
    for (const pair<const Producto, Nat>& s : stock2) {
        EXPECT_EQ(l.stockEnPuesto(2, s.first), s.second);
    }
    for (const pair<const Producto, Nat>& s : stock6) {
        EXPECT_EQ(l.stockEnPuesto(6, s.first), s.second);
    }
    for (const pair<const Producto, Nat>& s : stock7) {
        EXPECT_EQ(l.stockEnPuesto(7, s.first), s.second);
    }
    for (const IdPuesto& id : idsPuestos) {
        for (const Persona& p : personas) {
            EXPECT_EQ(l.gastoEnPuesto(id, p), 0);
        }
    }
    EXPECT_EQ(l.descuentoEnPuesto(2, 3, 9), 0);
    EXPECT_EQ(l.descuentoEnPuesto(2, 4, 8), 0);
    EXPECT_EQ(l.descuentoEnPuesto(2, 5, 3), 0);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 2), 0);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 3), 20);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 4), 20);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 5), 20);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 6), 25);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 7), 25);
    EXPECT_EQ(l.descuentoEnPuesto(6, 3, 2), 0);
    EXPECT_EQ(l.descuentoEnPuesto(6, 4, 3), 0);
    EXPECT_EQ(l.descuentoEnPuesto(6, 4, 4), 15);
    EXPECT_EQ(l.descuentoEnPuesto(6, 4, 5), 15);
    EXPECT_EQ(l.descuentoEnPuesto(6, 5, 1), 0);
    EXPECT_EQ(l.descuentoEnPuesto(6, 7, 8), 0);
    EXPECT_EQ(l.descuentoEnPuesto(7, 3, 4), 0);
    EXPECT_EQ(l.descuentoEnPuesto(7, 3, 5), 30);
    EXPECT_EQ(l.descuentoEnPuesto(7, 3, 6), 30);
    EXPECT_EQ(l.descuentoEnPuesto(7, 4, 9), 0);
    EXPECT_EQ(l.descuentoEnPuesto(7, 5, 1), 0);
    EXPECT_EQ(l.descuentoEnPuesto(7, 7, 1), 0);
    EXPECT_EQ(l.descuentoEnPuesto(7, 7, 2), 10);
    EXPECT_EQ(l.descuentoEnPuesto(7, 7, 3), 10);
    EXPECT_EQ(l.idsDePuestos(), idsPuestos);
}

TEST_F(LollaTest, vender_sin_descuento) {
    FachadaLollapatuza l(personas, puestos);
    l.registrarCompra(4, 5, 7, 6);

    EXPECT_EQ(l.gastoTotal(2), 0);
    EXPECT_EQ(l.gastoTotal(4), 17500);
    EXPECT_EQ(l.gastoTotal(8), 0);
    EXPECT_EQ(l.gastoTotal(9), 0);
    EXPECT_EQ(l.mayorGastador(), 4);
    EXPECT_EQ(l.menorStock(3), 6);
    EXPECT_EQ(l.menorStock(4), 2);
    EXPECT_EQ(l.menorStock(5), 6);
    EXPECT_EQ(l.menorStock(7), 6);
    EXPECT_EQ(l.personas(), personas);
    for (const pair<const Producto, Nat>& s : stock2) {
        EXPECT_EQ(l.stockEnPuesto(2, s.first), s.second);
    }
    EXPECT_EQ(l.stockEnPuesto(6, 3), 5);
    EXPECT_EQ(l.stockEnPuesto(6, 4), 15);
    EXPECT_EQ(l.stockEnPuesto(6, 5), 18);
    EXPECT_EQ(l.stockEnPuesto(6, 7), 5);
    for (const pair<const Producto, Nat>& s : stock7) {
        EXPECT_EQ(l.stockEnPuesto(7, s.first), s.second);
    }
    for (const Persona& p : personas) {
        EXPECT_EQ(l.gastoEnPuesto(2, p), 0);
    }
    EXPECT_EQ(l.gastoEnPuesto(6, 2), 0);
    EXPECT_EQ(l.gastoEnPuesto(6, 4), 17500);
    EXPECT_EQ(l.gastoEnPuesto(6, 8), 0);
    EXPECT_EQ(l.gastoEnPuesto(6, 9), 0);
    for (const Persona& p : personas) {
        EXPECT_EQ(l.gastoEnPuesto(7, p), 0);
    }
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 2), 0);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 3), 20);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 4), 20);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 5), 20);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 6), 25);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 7), 25);
    EXPECT_EQ(l.descuentoEnPuesto(6, 4, 3), 0);
    EXPECT_EQ(l.descuentoEnPuesto(6, 4, 4), 15);
    EXPECT_EQ(l.descuentoEnPuesto(6, 4, 5), 15);
    EXPECT_EQ(l.descuentoEnPuesto(7, 3, 4), 0);
    EXPECT_EQ(l.descuentoEnPuesto(7, 3, 5), 30);
    EXPECT_EQ(l.descuentoEnPuesto(7, 3, 6), 30);
    EXPECT_EQ(l.descuentoEnPuesto(7, 7, 1), 0);
    EXPECT_EQ(l.descuentoEnPuesto(7, 7, 2), 10);
    EXPECT_EQ(l.descuentoEnPuesto(7, 7, 3), 10);
    EXPECT_EQ(l.idsDePuestos(), idsPuestos);
}

TEST_F(LollaTest, vender_dos_veces_mismo_producto_persona_y_puesto) {
    FachadaLollapatuza l(personas, puestos);
    l.registrarCompra(8, 3, 4, 2);
    l.registrarCompra(8, 3, 2, 2);

    EXPECT_EQ(l.gastoTotal(2), 0);
    EXPECT_EQ(l.gastoTotal(4), 0);
    EXPECT_EQ(l.gastoTotal(8), 3000);
    EXPECT_EQ(l.gastoTotal(9), 0);
    EXPECT_EQ(l.mayorGastador(), 8);
    EXPECT_EQ(l.menorStock(3), 2);
    EXPECT_EQ(l.menorStock(4), 2);
    EXPECT_EQ(l.menorStock(5), 7);
    EXPECT_EQ(l.menorStock(7), 6);
    EXPECT_EQ(l.personas(), personas);
    EXPECT_EQ(l.stockEnPuesto(2, 3), 4);
    EXPECT_EQ(l.stockEnPuesto(2, 4), 5);
    EXPECT_EQ(l.stockEnPuesto(2, 5), 30);
    EXPECT_EQ(l.stockEnPuesto(2, 7), 10);
    for (const pair<const Producto, Nat>& s : stock6) {
        EXPECT_EQ(l.stockEnPuesto(6, s.first), s.second);
    }
    for (const pair<const Producto, Nat>& s : stock7) {
        EXPECT_EQ(l.stockEnPuesto(7, s.first), s.second);
    }
    EXPECT_EQ(l.gastoEnPuesto(2, 2), 0);
    EXPECT_EQ(l.gastoEnPuesto(2, 4), 0);
    EXPECT_EQ(l.gastoEnPuesto(2, 8), 3000);
    EXPECT_EQ(l.gastoEnPuesto(2, 9), 0);
    for (const Persona& p : personas) {
        EXPECT_EQ(l.gastoEnPuesto(6, p), 0);
    }
    for (const Persona& p : personas) {
        EXPECT_EQ(l.gastoEnPuesto(7, p), 0);
    }
    EXPECT_EQ(l.idsDePuestos(), idsPuestos);
}

TEST_F(LollaTest, vender_dos_veces_distinto_producto) {
    FachadaLollapatuza l(personas, puestos);
    l.registrarCompra(9, 3, 1, 6);
    l.registrarCompra(9, 7, 2, 6);

    EXPECT_EQ(l.gastoTotal(2), 0);
    EXPECT_EQ(l.gastoTotal(4), 0);
    EXPECT_EQ(l.gastoTotal(8), 0);
    EXPECT_EQ(l.gastoTotal(9), 4500);
    EXPECT_EQ(l.mayorGastador(), 9);
    EXPECT_EQ(l.menorStock(3), 6);
    EXPECT_EQ(l.menorStock(4), 2);
    EXPECT_EQ(l.menorStock(5), 7);
    EXPECT_EQ(l.menorStock(7), 6);
    EXPECT_EQ(l.personas(), personas);
    for (const pair<const Producto, Nat>& s : stock2) {
        EXPECT_EQ(l.stockEnPuesto(2, s.first), s.second);
    }
    EXPECT_EQ(l.stockEnPuesto(6, 3), 4);
    EXPECT_EQ(l.stockEnPuesto(6, 4), 15);
    EXPECT_EQ(l.stockEnPuesto(6, 5), 25);
    EXPECT_EQ(l.stockEnPuesto(6, 7), 3);
    for (const pair<const Producto, Nat>& s : stock7) {
        EXPECT_EQ(l.stockEnPuesto(7, s.first), s.second);
    }
    for (const Persona& p : personas) {
        EXPECT_EQ(l.gastoEnPuesto(2, p), 0);
    }
    EXPECT_EQ(l.gastoEnPuesto(6, 2), 0);
    EXPECT_EQ(l.gastoEnPuesto(6, 4), 0);
    EXPECT_EQ(l.gastoEnPuesto(6, 8), 0);
    EXPECT_EQ(l.gastoEnPuesto(6, 9), 4500);
    for (const Persona& p : personas) {
        EXPECT_EQ(l.gastoEnPuesto(7, p), 0);
    }
    EXPECT_EQ(l.idsDePuestos(), idsPuestos);
}

TEST_F(LollaTest, vender_dos_veces_distinta_persona) {
    FachadaLollapatuza l(personas, puestos);
    l.registrarCompra(2, 5, 3, 7);
    l.registrarCompra(4, 5, 6, 7);

    EXPECT_EQ(l.gastoTotal(2), 7500);
    EXPECT_EQ(l.gastoTotal(4), 15000);
    EXPECT_EQ(l.gastoTotal(8), 0);
    EXPECT_EQ(l.gastoTotal(9), 0);
    EXPECT_EQ(l.mayorGastador(), 4);
    EXPECT_EQ(l.menorStock(3), 6);
    EXPECT_EQ(l.menorStock(4), 2);
    EXPECT_EQ(l.menorStock(5), 7);
    EXPECT_EQ(l.menorStock(7), 6);
    EXPECT_EQ(l.personas(), personas);
    for (const pair<const Producto, Nat>& s : stock2) {
        EXPECT_EQ(l.stockEnPuesto(2, s.first), s.second);
    }
    for (const pair<const Producto, Nat>& s : stock6) {
        EXPECT_EQ(l.stockEnPuesto(6, s.first), s.second);
    }
    EXPECT_EQ(l.stockEnPuesto(7, 3), 20);
    EXPECT_EQ(l.stockEnPuesto(7, 4), 20);
    EXPECT_EQ(l.stockEnPuesto(7, 5), 11);
    EXPECT_EQ(l.stockEnPuesto(7, 7), 20);
    for (const Persona& p : personas) {
        EXPECT_EQ(l.gastoEnPuesto(2, p), 0);
    }
    for (const Persona& p : personas) {
        EXPECT_EQ(l.gastoEnPuesto(6, p), 0);
    }
    EXPECT_EQ(l.gastoEnPuesto(7, 2), 7500);
    EXPECT_EQ(l.gastoEnPuesto(7, 4), 15000);
    EXPECT_EQ(l.gastoEnPuesto(7, 8), 0);
    EXPECT_EQ(l.gastoEnPuesto(7, 9), 0);
    EXPECT_EQ(l.idsDePuestos(), idsPuestos);
}

TEST_F(LollaTest, vender_dos_veces_distinto_puesto) {
    FachadaLollapatuza l(personas, puestos);
    l.registrarCompra(8, 4, 3, 2);
    l.registrarCompra(8, 4, 6, 7);

    EXPECT_EQ(l.gastoTotal(2), 0);
    EXPECT_EQ(l.gastoTotal(4), 0);
    EXPECT_EQ(l.gastoTotal(8), 9000);
    EXPECT_EQ(l.gastoTotal(9), 0);
    EXPECT_EQ(l.mayorGastador(), 8);
    EXPECT_EQ(l.menorStock(3), 6);
    EXPECT_EQ(l.menorStock(4), 2);
    EXPECT_EQ(l.menorStock(5), 7);
    EXPECT_EQ(l.menorStock(7), 6);
    EXPECT_EQ(l.personas(), personas);
    EXPECT_EQ(l.stockEnPuesto(2, 3), 10);
    EXPECT_EQ(l.stockEnPuesto(2, 4), 2);
    EXPECT_EQ(l.stockEnPuesto(2, 5), 30);
    EXPECT_EQ(l.stockEnPuesto(2, 7), 10);
    for (const pair<const Producto, Nat>& s : stock6) {
        EXPECT_EQ(l.stockEnPuesto(6, s.first), s.second);
    }
    EXPECT_EQ(l.stockEnPuesto(7, 3), 20);
    EXPECT_EQ(l.stockEnPuesto(7, 4), 14);
    EXPECT_EQ(l.stockEnPuesto(7, 5), 20);
    EXPECT_EQ(l.stockEnPuesto(7, 7), 20);
    EXPECT_EQ(l.gastoEnPuesto(2, 2), 0);
    EXPECT_EQ(l.gastoEnPuesto(2, 4), 0);
    EXPECT_EQ(l.gastoEnPuesto(2, 8), 3000);
    EXPECT_EQ(l.gastoEnPuesto(2, 9), 0);
    for (const Persona& p : personas) {
        EXPECT_EQ(l.gastoEnPuesto(6, p), 0);
    }
    EXPECT_EQ(l.gastoEnPuesto(7, 2), 0);
    EXPECT_EQ(l.gastoEnPuesto(7, 4), 0);
    EXPECT_EQ(l.gastoEnPuesto(7, 8), 6000);
    EXPECT_EQ(l.gastoEnPuesto(7, 9), 0);
    EXPECT_EQ(l.idsDePuestos(), idsPuestos);
}

TEST_F(LollaTest, vender_dos_veces_distinta_persona_mismo_gasto) {
    FachadaLollapatuza l(personas, puestos);
    l.registrarCompra(8, 5, 2, 2);
    l.registrarCompra(9, 4, 5, 7);

    EXPECT_EQ(l.gastoTotal(2), 0);
    EXPECT_EQ(l.gastoTotal(4), 0);
    EXPECT_EQ(l.gastoTotal(8), 5000);
    EXPECT_EQ(l.gastoTotal(9), 5000);
    EXPECT_EQ(personas89.count(l.mayorGastador()), 1);
    EXPECT_EQ(l.menorStock(3), 6);
    EXPECT_EQ(l.menorStock(4), 2);
    EXPECT_EQ(l.menorStock(5), 7);
    EXPECT_EQ(l.menorStock(7), 6);
    EXPECT_EQ(l.personas(), personas);
    EXPECT_EQ(l.stockEnPuesto(2, 3), 10);
    EXPECT_EQ(l.stockEnPuesto(2, 4), 5);
    EXPECT_EQ(l.stockEnPuesto(2, 5), 28);
    EXPECT_EQ(l.stockEnPuesto(2, 7), 10);
    for (const pair<const Producto, Nat>& s : stock6) {
        EXPECT_EQ(l.stockEnPuesto(6, s.first), s.second);
    }
    EXPECT_EQ(l.stockEnPuesto(7, 3), 20);
    EXPECT_EQ(l.stockEnPuesto(7, 4), 15);
    EXPECT_EQ(l.stockEnPuesto(7, 5), 20);
    EXPECT_EQ(l.stockEnPuesto(7, 7), 20);
    EXPECT_EQ(l.gastoEnPuesto(2, 2), 0);
    EXPECT_EQ(l.gastoEnPuesto(2, 4), 0);
    EXPECT_EQ(l.gastoEnPuesto(2, 8), 5000);
    EXPECT_EQ(l.gastoEnPuesto(2, 9), 0);
    for (const Persona& p : personas) {
        EXPECT_EQ(l.gastoEnPuesto(6, p), 0);
    }
    EXPECT_EQ(l.gastoEnPuesto(7, 2), 0);
    EXPECT_EQ(l.gastoEnPuesto(7, 4), 0);
    EXPECT_EQ(l.gastoEnPuesto(7, 8), 0);
    EXPECT_EQ(l.gastoEnPuesto(7, 9), 5000);
    EXPECT_EQ(l.idsDePuestos(), idsPuestos);
}

TEST_F(LollaTest, vender_causa_mismo_stock) {
    FachadaLollapatuza l(personas, puestos);
    l.registrarCompra(8, 5, 10, 2);

    EXPECT_EQ(l.gastoTotal(2), 0);
    EXPECT_EQ(l.gastoTotal(4), 0);
    EXPECT_EQ(l.gastoTotal(8), 25000);
    EXPECT_EQ(l.gastoTotal(9), 0);
    EXPECT_EQ(l.mayorGastador(), 8);
    EXPECT_EQ(l.menorStock(3), 6);
    EXPECT_EQ(l.menorStock(4), 2);
    EXPECT_EQ(l.menorStock(5), 2);
    EXPECT_EQ(l.menorStock(7), 6);
    EXPECT_EQ(l.personas(), personas);
    EXPECT_EQ(l.stockEnPuesto(2, 3), 10);
    EXPECT_EQ(l.stockEnPuesto(2, 4), 5);
    EXPECT_EQ(l.stockEnPuesto(2, 5), 20);
    EXPECT_EQ(l.stockEnPuesto(2, 7), 10);
    for (const pair<const Producto, Nat>& s : stock6) {
        EXPECT_EQ(l.stockEnPuesto(6, s.first), s.second);
    }
    for (const pair<const Producto, Nat>& s : stock7) {
        EXPECT_EQ(l.stockEnPuesto(7, s.first), s.second);
    }
    EXPECT_EQ(l.gastoEnPuesto(2, 2), 0);
    EXPECT_EQ(l.gastoEnPuesto(2, 4), 0);
    EXPECT_EQ(l.gastoEnPuesto(2, 8), 25000);
    EXPECT_EQ(l.gastoEnPuesto(2, 9), 0);
    for (const Persona& p : personas) {
        EXPECT_EQ(l.gastoEnPuesto(6, p), 0);
    }
    for (const Persona& p : personas) {
        EXPECT_EQ(l.gastoEnPuesto(7, p), 0);
    }
    EXPECT_EQ(l.idsDePuestos(), idsPuestos);
}

TEST_F(LollaTest, vender_con_descuento) {
    FachadaLollapatuza l(personas, puestos);
    l.registrarCompra(9, 4, 5, 6);

    EXPECT_EQ(l.gastoTotal(2), 0);
    EXPECT_EQ(l.gastoTotal(4), 0);
    EXPECT_EQ(l.gastoTotal(8), 0);
    EXPECT_EQ(l.gastoTotal(9), 4250);
    EXPECT_EQ(l.mayorGastador(), 9);
    EXPECT_EQ(l.menorStock(3), 6);
    EXPECT_EQ(l.menorStock(4), 2);
    EXPECT_EQ(l.menorStock(5), 7);
    EXPECT_EQ(l.menorStock(7), 6);
    EXPECT_EQ(l.personas(), personas);
    for (const pair<const Producto, Nat>& s : stock2) {
        EXPECT_EQ(l.stockEnPuesto(2, s.first), s.second);
    }
    EXPECT_EQ(l.stockEnPuesto(6, 3), 5);
    EXPECT_EQ(l.stockEnPuesto(6, 4), 10);
    EXPECT_EQ(l.stockEnPuesto(6, 5), 25);
    EXPECT_EQ(l.stockEnPuesto(6, 7), 5);
    for (const pair<const Producto, Nat>& s : stock7) {
        EXPECT_EQ(l.stockEnPuesto(7, s.first), s.second);
    }
    for (const Persona& p : personas) {
        EXPECT_EQ(l.gastoEnPuesto(2, p), 0);
    }
    EXPECT_EQ(l.gastoEnPuesto(6, 2), 0);
    EXPECT_EQ(l.gastoEnPuesto(6, 4), 0);
    EXPECT_EQ(l.gastoEnPuesto(6, 8), 0);
    EXPECT_EQ(l.gastoEnPuesto(6, 9), 4250);
    for (const Persona& p : personas) {
        EXPECT_EQ(l.gastoEnPuesto(7, p), 0);
    }
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 2), 0);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 3), 20);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 4), 20);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 5), 20);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 6), 25);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 7), 25);
    EXPECT_EQ(l.descuentoEnPuesto(6, 4, 3), 0);
    EXPECT_EQ(l.descuentoEnPuesto(6, 4, 4), 15);
    EXPECT_EQ(l.descuentoEnPuesto(6, 4, 5), 15);
    EXPECT_EQ(l.descuentoEnPuesto(7, 3, 4), 0);
    EXPECT_EQ(l.descuentoEnPuesto(7, 3, 5), 30);
    EXPECT_EQ(l.descuentoEnPuesto(7, 3, 6), 30);
    EXPECT_EQ(l.descuentoEnPuesto(7, 7, 1), 0);
    EXPECT_EQ(l.descuentoEnPuesto(7, 7, 2), 10);
    EXPECT_EQ(l.descuentoEnPuesto(7, 7, 3), 10);
    EXPECT_EQ(l.idsDePuestos(), idsPuestos);
}

TEST_F(LollaTest, vender_con_distintos_descuentos) {
    FachadaLollapatuza l(personas, puestos);
    l.registrarCompra(2, 7, 7, 2);
    l.registrarCompra(2, 7, 3, 2);

    EXPECT_EQ(l.gastoTotal(2), 15300);
    EXPECT_EQ(l.gastoTotal(4), 0);
    EXPECT_EQ(l.gastoTotal(8), 0);
    EXPECT_EQ(l.gastoTotal(9), 0);
    EXPECT_EQ(l.mayorGastador(), 2);
    EXPECT_EQ(l.menorStock(3), 6);
    EXPECT_EQ(l.menorStock(4), 2);
    EXPECT_EQ(l.menorStock(5), 7);
    EXPECT_EQ(l.menorStock(7), 2);
    EXPECT_EQ(l.personas(), personas);
    EXPECT_EQ(l.stockEnPuesto(2, 3), 10);
    EXPECT_EQ(l.stockEnPuesto(2, 4), 5);
    EXPECT_EQ(l.stockEnPuesto(2, 5), 30);
    EXPECT_EQ(l.stockEnPuesto(2, 7), 0);
    for (const pair<const Producto, Nat>& s : stock6) {
        EXPECT_EQ(l.stockEnPuesto(6, s.first), s.second);
    }
    for (const pair<const Producto, Nat>& s : stock7) {
        EXPECT_EQ(l.stockEnPuesto(7, s.first), s.second);
    }
    EXPECT_EQ(l.gastoEnPuesto(2, 2), 15300);
    EXPECT_EQ(l.gastoEnPuesto(2, 4), 0);
    EXPECT_EQ(l.gastoEnPuesto(2, 8), 0);
    EXPECT_EQ(l.gastoEnPuesto(2, 9), 0);
    for (const Persona& p : personas) {
        EXPECT_EQ(l.gastoEnPuesto(6, p), 0);
    }
    for (const Persona& p : personas) {
        EXPECT_EQ(l.gastoEnPuesto(7, p), 0);
    }
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 2), 0);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 3), 20);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 4), 20);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 5), 20);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 6), 25);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 7), 25);
    EXPECT_EQ(l.descuentoEnPuesto(6, 4, 3), 0);
    EXPECT_EQ(l.descuentoEnPuesto(6, 4, 4), 15);
    EXPECT_EQ(l.descuentoEnPuesto(6, 4, 5), 15);
    EXPECT_EQ(l.descuentoEnPuesto(7, 3, 4), 0);
    EXPECT_EQ(l.descuentoEnPuesto(7, 3, 5), 30);
    EXPECT_EQ(l.descuentoEnPuesto(7, 3, 6), 30);
    EXPECT_EQ(l.descuentoEnPuesto(7, 7, 1), 0);
    EXPECT_EQ(l.descuentoEnPuesto(7, 7, 2), 10);
    EXPECT_EQ(l.descuentoEnPuesto(7, 7, 3), 10);
    EXPECT_EQ(l.idsDePuestos(), idsPuestos);
}

TEST_F(LollaTest, vender_varias_veces) {
    FachadaLollapatuza l(personas, puestos);
    l.registrarCompra(9, 3, 4, 2); // 2000
    l.registrarCompra(4, 4, 1, 2); // 1000
    l.registrarCompra(8, 5, 1, 2); // 2500
    l.registrarCompra(2, 7, 2, 2); // 4000
    l.registrarCompra(4, 3, 3, 6); // 1500
    l.registrarCompra(8, 4, 5, 6); // 4250 (con descuento)
    l.registrarCompra(2, 5, 3, 6); // 7500
    l.registrarCompra(9, 7, 4, 6); // 8000
    l.registrarCompra(2, 3, 1, 7); // 500
    l.registrarCompra(9, 4, 5, 7); // 5000
    l.registrarCompra(4, 5, 5, 7); // 12500
    l.registrarCompra(8, 7, 3, 7); // 5400 (con descuento)

    EXPECT_EQ(l.gastoTotal(2), 12000);
    EXPECT_EQ(l.gastoTotal(4), 15000);
    EXPECT_EQ(l.gastoTotal(8), 12150);
    EXPECT_EQ(l.gastoTotal(9), 15000);
    EXPECT_EQ(personas49.count(l.mayorGastador()), 1);
    EXPECT_EQ(l.menorStock(3), 6);
    EXPECT_EQ(l.menorStock(4), 2);
    EXPECT_EQ(l.menorStock(5), 7);
    EXPECT_EQ(l.menorStock(7), 6);
    EXPECT_EQ(l.personas(), personas);
    EXPECT_EQ(l.stockEnPuesto(2, 3), 6);
    EXPECT_EQ(l.stockEnPuesto(2, 4), 4);
    EXPECT_EQ(l.stockEnPuesto(2, 5), 29);
    EXPECT_EQ(l.stockEnPuesto(2, 7), 8);
    EXPECT_EQ(l.stockEnPuesto(6, 3), 2);
    EXPECT_EQ(l.stockEnPuesto(6, 4), 10);
    EXPECT_EQ(l.stockEnPuesto(6, 5), 22);
    EXPECT_EQ(l.stockEnPuesto(6, 7), 1);
    EXPECT_EQ(l.stockEnPuesto(7, 3), 19);
    EXPECT_EQ(l.stockEnPuesto(7, 4), 15);
    EXPECT_EQ(l.stockEnPuesto(7, 5), 15);
    EXPECT_EQ(l.stockEnPuesto(7, 7), 17);
    EXPECT_EQ(l.gastoEnPuesto(2, 2), 4000);
    EXPECT_EQ(l.gastoEnPuesto(2, 4), 1000);
    EXPECT_EQ(l.gastoEnPuesto(2, 8), 2500);
    EXPECT_EQ(l.gastoEnPuesto(2, 9), 2000);
    EXPECT_EQ(l.gastoEnPuesto(6, 2), 7500);
    EXPECT_EQ(l.gastoEnPuesto(6, 4), 1500);
    EXPECT_EQ(l.gastoEnPuesto(6, 8), 4250);
    EXPECT_EQ(l.gastoEnPuesto(6, 9), 8000);
    EXPECT_EQ(l.gastoEnPuesto(7, 2), 500);
    EXPECT_EQ(l.gastoEnPuesto(7, 4), 12500);
    EXPECT_EQ(l.gastoEnPuesto(7, 8), 5400);
    EXPECT_EQ(l.gastoEnPuesto(7, 9), 5000);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 2), 0);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 3), 20);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 4), 20);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 5), 20);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 6), 25);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 7), 25);
    EXPECT_EQ(l.descuentoEnPuesto(6, 4, 3), 0);
    EXPECT_EQ(l.descuentoEnPuesto(6, 4, 4), 15);
    EXPECT_EQ(l.descuentoEnPuesto(6, 4, 5), 15);
    EXPECT_EQ(l.descuentoEnPuesto(7, 3, 4), 0);
    EXPECT_EQ(l.descuentoEnPuesto(7, 3, 5), 30);
    EXPECT_EQ(l.descuentoEnPuesto(7, 3, 6), 30);
    EXPECT_EQ(l.descuentoEnPuesto(7, 7, 1), 0);
    EXPECT_EQ(l.descuentoEnPuesto(7, 7, 2), 10);
    EXPECT_EQ(l.descuentoEnPuesto(7, 7, 3), 10);
    EXPECT_EQ(l.idsDePuestos(), idsPuestos);
}

TEST_F(LollaTest, hackear_una_vez) {
    FachadaLollapatuza l(personas, puestos);
    l.registrarCompra(4, 5, 7, 6);
    l.hackear(4, 5);

    EXPECT_EQ(l.gastoTotal(2), 0);
    EXPECT_EQ(l.gastoTotal(4), 15000);
    EXPECT_EQ(l.gastoTotal(8), 0);
    EXPECT_EQ(l.gastoTotal(9), 0);
    EXPECT_EQ(l.mayorGastador(), 4);
    EXPECT_EQ(l.menorStock(3), 6);
    EXPECT_EQ(l.menorStock(4), 2);
    EXPECT_EQ(l.menorStock(5), 6);
    EXPECT_EQ(l.menorStock(7), 6);
    EXPECT_EQ(l.personas(), personas);
    for (const pair<const Producto, Nat>& s : stock2) {
        EXPECT_EQ(l.stockEnPuesto(2, s.first), s.second);
    }
    EXPECT_EQ(l.stockEnPuesto(6, 3), 5);
    EXPECT_EQ(l.stockEnPuesto(6, 4), 15);
    EXPECT_EQ(l.stockEnPuesto(6, 5), 19);
    EXPECT_EQ(l.stockEnPuesto(6, 7), 5);
    for (const pair<const Producto, Nat>& s : stock7) {
        EXPECT_EQ(l.stockEnPuesto(7, s.first), s.second);
    }
    for (const Persona& p : personas) {
        EXPECT_EQ(l.gastoEnPuesto(2, p), 0);
    }
    EXPECT_EQ(l.gastoEnPuesto(6, 2), 0);
    EXPECT_EQ(l.gastoEnPuesto(6, 4), 15000); //
    EXPECT_EQ(l.gastoEnPuesto(6, 8), 0);
    EXPECT_EQ(l.gastoEnPuesto(6, 9), 0);
    for (const Persona& p : personas) {
        EXPECT_EQ(l.gastoEnPuesto(7, p), 0);
    }
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 2), 0);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 3), 20);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 4), 20);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 5), 20);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 6), 25);
    EXPECT_EQ(l.descuentoEnPuesto(2, 7, 7), 25);
    EXPECT_EQ(l.descuentoEnPuesto(6, 4, 3), 0);
    EXPECT_EQ(l.descuentoEnPuesto(6, 4, 4), 15);
    EXPECT_EQ(l.descuentoEnPuesto(6, 4, 5), 15);
    EXPECT_EQ(l.descuentoEnPuesto(7, 3, 4), 0);
    EXPECT_EQ(l.descuentoEnPuesto(7, 3, 5), 30);
    EXPECT_EQ(l.descuentoEnPuesto(7, 3, 6), 30);
    EXPECT_EQ(l.descuentoEnPuesto(7, 7, 1), 0);
    EXPECT_EQ(l.descuentoEnPuesto(7, 7, 2), 10);
    EXPECT_EQ(l.descuentoEnPuesto(7, 7, 3), 10);
    EXPECT_EQ(l.idsDePuestos(), idsPuestos);
}

TEST_F(LollaTest, hackear_vuelve_menor_stock) {
    FachadaLollapatuza l(personas, puestos);
    l.registrarCompra(4, 5, 7, 6);
    l.hackear(4, 5);
    l.hackear(4, 5);
    l.hackear(4, 5);

    EXPECT_EQ(l.gastoTotal(2), 0);
    EXPECT_EQ(l.gastoTotal(4), 10000);
    EXPECT_EQ(l.gastoTotal(8), 0);
    EXPECT_EQ(l.gastoTotal(9), 0);
    EXPECT_EQ(l.mayorGastador(), 4);
    EXPECT_EQ(l.menorStock(3), 6);
    EXPECT_EQ(l.menorStock(4), 2);
    EXPECT_EQ(l.menorStock(5), 7);
    EXPECT_EQ(l.menorStock(7), 6);
    EXPECT_EQ(l.personas(), personas);
    for (const pair<const Producto, Nat>& s : stock2) {
        EXPECT_EQ(l.stockEnPuesto(2, s.first), s.second);
    }
    EXPECT_EQ(l.stockEnPuesto(6, 3), 5);
    EXPECT_EQ(l.stockEnPuesto(6, 4), 15);
    EXPECT_EQ(l.stockEnPuesto(6, 5), 21);
    EXPECT_EQ(l.stockEnPuesto(6, 7), 5);
    for (const pair<const Producto, Nat>& s : stock7) {
        EXPECT_EQ(l.stockEnPuesto(7, s.first), s.second);
    }
    for (const Persona& p : personas) {
        EXPECT_EQ(l.gastoEnPuesto(2, p), 0);
    }
    EXPECT_EQ(l.gastoEnPuesto(6, 2), 0);
    EXPECT_EQ(l.gastoEnPuesto(6, 4), 10000);
    EXPECT_EQ(l.gastoEnPuesto(6, 8), 0);
    EXPECT_EQ(l.gastoEnPuesto(6, 9), 0);
    for (const Persona& p : personas) {
        EXPECT_EQ(l.gastoEnPuesto(7, p), 0);
    }
    EXPECT_EQ(l.idsDePuestos(), idsPuestos);
}

TEST_F(LollaTest, hackear_altera_puesto_menor_id) {
    FachadaLollapatuza l(personas, puestos);
    l.registrarCompra(8, 4, 3, 2);
    l.registrarCompra(8, 4, 6, 7);
    l.hackear(8, 4);

    EXPECT_EQ(l.gastoTotal(2), 0);
    EXPECT_EQ(l.gastoTotal(4), 0);
    EXPECT_EQ(l.gastoTotal(8), 8000);
    EXPECT_EQ(l.gastoTotal(9), 0);
    EXPECT_EQ(l.mayorGastador(), 8);
    EXPECT_EQ(l.menorStock(3), 6);
    EXPECT_EQ(l.menorStock(4), 2);
    EXPECT_EQ(l.menorStock(5), 7);
    EXPECT_EQ(l.menorStock(7), 6);
    EXPECT_EQ(l.personas(), personas);
    EXPECT_EQ(l.stockEnPuesto(2, 3), 10);
    EXPECT_EQ(l.stockEnPuesto(2, 4), 3);
    EXPECT_EQ(l.stockEnPuesto(2, 5), 30);
    EXPECT_EQ(l.stockEnPuesto(2, 7), 10);
    for (const pair<const Producto, Nat>& s : stock6) {
        EXPECT_EQ(l.stockEnPuesto(6, s.first), s.second);
    }
    EXPECT_EQ(l.stockEnPuesto(7, 3), 20);
    EXPECT_EQ(l.stockEnPuesto(7, 4), 14);
    EXPECT_EQ(l.stockEnPuesto(7, 5), 20);
    EXPECT_EQ(l.stockEnPuesto(7, 7), 20);
    EXPECT_EQ(l.gastoEnPuesto(2, 2), 0);
    EXPECT_EQ(l.gastoEnPuesto(2, 4), 0);
    EXPECT_EQ(l.gastoEnPuesto(2, 8), 2000);
    EXPECT_EQ(l.gastoEnPuesto(2, 9), 0);
    for (const Persona& p : personas) {
        EXPECT_EQ(l.gastoEnPuesto(6, p), 0);
    }
    EXPECT_EQ(l.gastoEnPuesto(7, 2), 0);
    EXPECT_EQ(l.gastoEnPuesto(7, 4), 0);
    EXPECT_EQ(l.gastoEnPuesto(7, 8), 6000);
    EXPECT_EQ(l.gastoEnPuesto(7, 9), 0);
    EXPECT_EQ(l.idsDePuestos(), idsPuestos);
}

// Compra en 2 puestos distintos el mismo producto, ambos hackeables. Luego de hackear, cambia el puesto hackeable.
TEST_F(LollaTest, hackearCambiaPuestoHackeable) {
    FachadaLollapatuza l(personas, puestos);

    Persona Juan = 4;
    Producto Coca = 3;
    IdPuesto Mostaza = 2;
    IdPuesto McDonalds = 6;
    list<Nat> comprasJuanCocaMostazaSinDesc = {1};
    list<Nat> comprasJuanCocaMcDonaldsSinDesc = {2};

    l.registrarCompra(Juan, Coca, 1, Mostaza);
    l.registrarCompra(Juan, Coca, 2, McDonalds);

    EXPECT_EQ(l.ventasSinDescEnPuesto(Mostaza, Juan, Coca), comprasJuanCocaMostazaSinDesc);
    EXPECT_EQ(l.ventasSinDescEnPuesto(McDonalds, Juan, Coca), comprasJuanCocaMcDonaldsSinDesc);

    l.hackear(Juan, Coca);  // Hackea en Mostaza

    comprasJuanCocaMostazaSinDesc = {};

    EXPECT_EQ(l.ventasSinDescEnPuesto(Mostaza, Juan, Coca), comprasJuanCocaMostazaSinDesc);
    EXPECT_EQ(l.ventasSinDescEnPuesto(McDonalds, Juan, Coca), comprasJuanCocaMcDonaldsSinDesc);

    l.hackear(Juan, Coca);  // Hackea en McDonalds

    comprasJuanCocaMcDonaldsSinDesc = {1};

    EXPECT_EQ(l.ventasSinDescEnPuesto(Mostaza, Juan, Coca), comprasJuanCocaMostazaSinDesc);
    EXPECT_EQ(l.ventasSinDescEnPuesto(McDonalds, Juan, Coca), comprasJuanCocaMcDonaldsSinDesc);

    l.hackear(Juan, Coca);  // Hackea en McDonalds

    comprasJuanCocaMcDonaldsSinDesc = {};

    EXPECT_EQ(l.ventasSinDescEnPuesto(Mostaza, Juan, Coca), comprasJuanCocaMostazaSinDesc);
    EXPECT_EQ(l.ventasSinDescEnPuesto(McDonalds, Juan, Coca), comprasJuanCocaMcDonaldsSinDesc);
}

// Compra en un puesto el mismo producto 2 veces, una hackeable y una no
TEST_F(LollaTest, hackearVentaHackeable) {
    FachadaLollapatuza l(personas, puestos);

    Persona Juan = 4;
    Producto Coca = 3;
    IdPuesto BurgerKing = 7;
    list<Nat> comprasJuanCocaBKingSinDesc = {2, 3};
    list<Nat> comprasJuanCocaBkingConDesc = {6};

    l.registrarCompra(Juan, Coca, 6, BurgerKing);      // Compra 6 (no hackeable, tiene descuento)
    l.registrarCompra(Juan, Coca, 2, BurgerKing);      // Compra 2 (hackeable, no tiene descuento)
    l.registrarCompra(Juan, Coca, 3, BurgerKing);      // Compra 3 (hackeable, no tiene descuento)

    EXPECT_EQ(l.ventasSinDescEnPuesto(BurgerKing, Juan, Coca), comprasJuanCocaBKingSinDesc);
    EXPECT_EQ(l.ventasConDescEnPuesto(BurgerKing, Juan, Coca), comprasJuanCocaBkingConDesc);

    l.hackear(Juan, Coca);    // Hackea la 1er venta sin descuento 1 vez

    comprasJuanCocaBKingSinDesc = {1, 3};

    EXPECT_EQ(l.ventasSinDescEnPuesto(BurgerKing, Juan, Coca), comprasJuanCocaBKingSinDesc);
    EXPECT_EQ(l.ventasConDescEnPuesto(BurgerKing, Juan, Coca), comprasJuanCocaBkingConDesc);

    l.hackear(Juan, Coca);    // Hackea la 1er venta sin descuento 1 vez

    comprasJuanCocaBKingSinDesc = {3};

    EXPECT_EQ(l.ventasSinDescEnPuesto(BurgerKing, Juan, Coca), comprasJuanCocaBKingSinDesc);
    EXPECT_EQ(l.ventasConDescEnPuesto(BurgerKing, Juan, Coca), comprasJuanCocaBkingConDesc);

    l.hackear(Juan, Coca);    // Hackea la que fue la 2da (ahora 1era) venta sin descuento 1 vez

    comprasJuanCocaBKingSinDesc = {2};

    EXPECT_EQ(l.ventasSinDescEnPuesto(BurgerKing, Juan, Coca), comprasJuanCocaBKingSinDesc);
    EXPECT_EQ(l.ventasConDescEnPuesto(BurgerKing, Juan, Coca), comprasJuanCocaBkingConDesc);

    l.hackear(Juan, Coca);    // Hackea la que fue la 2da (ahora 1era) venta sin descuento 1 vez

    comprasJuanCocaBKingSinDesc = {1};

    EXPECT_EQ(l.ventasSinDescEnPuesto(BurgerKing, Juan, Coca), comprasJuanCocaBKingSinDesc);
    EXPECT_EQ(l.ventasConDescEnPuesto(BurgerKing, Juan, Coca), comprasJuanCocaBkingConDesc);

    l.hackear(Juan, Coca);    // Hackea la que fue la 2da (ahora 1era) venta sin descuento 1 vez

    comprasJuanCocaBKingSinDesc = {};

    EXPECT_EQ(l.ventasSinDescEnPuesto(BurgerKing, Juan, Coca), comprasJuanCocaBKingSinDesc);
    EXPECT_EQ(l.ventasConDescEnPuesto(BurgerKing, Juan, Coca), comprasJuanCocaBkingConDesc);

}

// Compra en un puesto 2 productos distintos, ambos hackeables
TEST_F(LollaTest, hackearProductosDistintos) {
    FachadaLollapatuza l(personas, puestos);

    Persona Juan = 4;
    Producto Coca = 3;
    Producto Pancho = 5;
    IdPuesto BurgerKing = 7;
    list<Nat> comprasJuanCocaSinDesc = {2,3};
    list<Nat> comprasJuanPanchoSinDesc = {4,1};

    l.registrarCompra(Juan, Coca, 2, BurgerKing);
    l.registrarCompra(Juan, Pancho, 4, BurgerKing);
    l.registrarCompra(Juan, Coca, 3, BurgerKing);
    l.registrarCompra(Juan, Pancho, 1, BurgerKing);

    EXPECT_EQ(l.ventasSinDescEnPuesto(BurgerKing, Juan, Coca), comprasJuanCocaSinDesc);
    EXPECT_EQ(l.ventasSinDescEnPuesto(BurgerKing, Juan, Pancho), comprasJuanPanchoSinDesc);

    l.hackear(Juan, Coca);    // Hackea la 1er venta de Coca 1 vez

    comprasJuanCocaSinDesc = {1, 3};

    EXPECT_EQ(l.ventasSinDescEnPuesto(BurgerKing, Juan, Coca), comprasJuanCocaSinDesc);
    EXPECT_EQ(l.ventasSinDescEnPuesto(BurgerKing, Juan, Pancho), comprasJuanPanchoSinDesc);

    l.hackear(Juan, Pancho);    // Hackea la 1er venta de Pancho 2 veces
    l.hackear(Juan, Pancho);

    comprasJuanPanchoSinDesc = {2, 1};

    EXPECT_EQ(l.ventasSinDescEnPuesto(BurgerKing, Juan, Coca), comprasJuanCocaSinDesc);
    EXPECT_EQ(l.ventasSinDescEnPuesto(BurgerKing, Juan, Pancho), comprasJuanPanchoSinDesc);

    l.hackear(Juan, Coca);    // Hackea la 1er venta de Coca 1 vez. Desaparece la venta, y hackea la 2da
    l.hackear(Juan, Coca);

    comprasJuanCocaSinDesc = {2};

    EXPECT_EQ(l.ventasSinDescEnPuesto(BurgerKing, Juan, Coca), comprasJuanCocaSinDesc);
    EXPECT_EQ(l.ventasSinDescEnPuesto(BurgerKing, Juan, Pancho), comprasJuanPanchoSinDesc);

    l.hackear(Juan, Pancho);    // Hackea la 1er venta de Pancho 2 veces. Desaparece, y hackea la venta restante
    l.hackear(Juan, Pancho);
    l.hackear(Juan, Pancho);

    comprasJuanPanchoSinDesc = {};

    EXPECT_EQ(l.ventasSinDescEnPuesto(BurgerKing, Juan, Coca), comprasJuanCocaSinDesc);
    EXPECT_EQ(l.ventasSinDescEnPuesto(BurgerKing, Juan, Pancho), comprasJuanPanchoSinDesc);

    l.hackear(Juan, Coca);    // Hackea la venta de Coca restante 2 veces
    l.hackear(Juan, Coca);

    comprasJuanCocaSinDesc = {};

    EXPECT_EQ(l.ventasSinDescEnPuesto(BurgerKing, Juan, Coca), comprasJuanCocaSinDesc);
    EXPECT_EQ(l.ventasSinDescEnPuesto(BurgerKing, Juan, Pancho), comprasJuanPanchoSinDesc);
}

 // Tests fachada
