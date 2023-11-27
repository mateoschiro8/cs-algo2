
#ifndef TP_LOLLA_LOLLAPATUZA_H
#define TP_LOLLA_LOLLAPATUZA_H

#include "tipos.h"
#include "Puesto.h"
#include "ColaPrior.h"

class Lollapatuza {
public:
    Lollapatuza(const set<Persona>& personas, const map<IdPuesto, Puesto>& infoPuestos);

    void iVenderL(Persona persona, Producto producto, Nat cant, IdPuesto idPuesto);
    void iHackear(Persona persona, Producto producto);

    Nat& iGastoPersona(Persona persona);
    Persona iPersonaMaxGasto() const;
    IdPuesto iPuestoMenorStock(Producto producto) const;

    const set<Persona>& iPersonas() const;
    map<IdPuesto, Puesto> iPuestos() const;

private:

    map<Persona, Nat> _gastos;
    map<IdPuesto, Puesto> _puestos;
    set<Persona> _personas;
    map<Persona, map<Producto,tuple<IdPuesto, Puesto*, Nat, map<IdPuesto, Nat>, ColaPrior>>> _hackeables;
    map<Nat, set<Persona>> _personasPorGasto;

//    map<Persona, set<Persona>::const_iterator> _iteradorAPersona;

    /*
       Durante la implementación, nos dimos cuenta que el diccionario iteradorAPersona que habiamos planteado en
    la estructura original no era tan util como pensabamos, y traia algunos problemas. Al usar la funcion set.erase()
    para borrar un elemento de un conjunto, tenemos dos opciones: borrar según el valor o usando un iterador,
    según la posición.
        Si borramos según el valor usando el iterador, deberiamos desreferenciarlo. Es decir, usamos la
    persona para obtener el iterador del diccionario, y después desreferenciarlo para obtener la persona.
    Es un paso extra innecesario.
        Y borrar segun posiciones nos trajo problemas, porque interpretaba el valor del iterador (el int que representa
    a la persona) como la posición, y daba cualquier resultado menos el esperado.
        Buscando en internet sobre este problema, vimos que:
    # Según https://learn.microsoft.com/es-es/cpp/standard-library/set-class?view=msvc-170,
       * Un conjunto de la biblioteca estándar de C++ es un contenedor asociativo de tamaño variable
    que admite la recuperación eficaz de valores de elemento según un valor de clave asociado. [...]
       * Los contenedores asociativos están optimizados para las operaciones de búsqueda,
    inserción y eliminación. Las funciones miembro que admiten estas operaciones explícitamente las realizan
    de forma eficiente en un tiempo que es proporcional en promedio al logaritmo del número de elementos del contenedor.
    # Según https://cplusplus.com/reference/set/set/, los conjuntos están implementados sobre ABBs, y la función
     erase(), si es según el valor, toma tiempo logarítmico en la cantidad de elementos.
        Por lo tanto, vimos que no necesitabamos los iteradores, porque buscar la persona a borrar en el momento, en
    tiempo logarítmico, se mantenía dentro de las complejidades que necesitamos.
        De cualquier manera, quedan comentadas las partes que no funcionaron, para ver si quizás no lo estabamos
    haciendo de forma correcta.

        Otra modificación realizada es que _hackeables devuelve ahora también una referencia al puesto que será
    hackeado. Teníamos el problema que, al solo guardarnos el ID, necesitabamos buscarlo al hackear, y eso hacía
    que aparezca una complejidad log(P) que no debía estar. Ahora, al guardarnos la referencia, no hace falta buscarlo,
    simplemente la "seguimos" y hacemos las operaciones que hay que hacer. Al momento de cambiar el puesto, ya que deja
    de ser hackeable, ahí actualizamos este puntero, y ahí aparece la complejidad log(P) que no molesta.

        Agregamos también en el puesto la función iHackear( ), que se encarga de devolver 1 al stock del item,
    modificar el gasto de la persona y modificar las compras de la persona en ese puesto. Esta función apareció porque,
    en caso de no tenerla, debiamos meternos en la parte privada de los puestos desde el Lollapatuza, y eso es una
    mala práctica, ya que rompe el encapsulamiento.

        En los puestos, modificamos ventasSinDesc y ventasConDesc, porque antes solo devolvían una lista de ventas
    <producto, cantidad>. El problema es que al hackear, agarrábamos la primer compra, que no necesariamente era
    la compra que queríamos hackear (podría ser de otro producto). Ahora es un
    dicc(persona, dicc(producto, lista<cant>)), donde cada cant es una compra distinta, y podemos asegurarnos que
    la compra que modificamos es del producto que queremos.
                                                                                                                    */
};

#endif //TP_LOLLA_LOLLAPATUZA_H
