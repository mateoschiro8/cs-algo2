//
// Created by mateo on 13/04/23.
//

#ifndef SOLUCION_PERIODO_H
#define SOLUCION_PERIODO_H


class Periodo {
public:
    Periodo(int anios, int meses, int dias);

    int anios() const;
    int meses() const;
    int dias() const;

private:
    int anios_;
    int meses_;
    int dias_;
};


#endif //SOLUCION_PERIODO_H
