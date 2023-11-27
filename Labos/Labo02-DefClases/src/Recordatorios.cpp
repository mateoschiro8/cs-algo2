#include <iostream>
#include <list>

using namespace std;

using uint = unsigned int;

// Pre: 0 <= mes < 12
uint dias_en_mes(uint mes) {
    uint dias[] = {
        // ene, feb, mar, abr, may, jun
        31, 28, 31, 30, 31, 30,
        // jul, ago, sep, oct, nov, dic
        31, 31, 30, 31, 30, 31
    };
    return dias[mes - 1];
}

// Ejercicio 7, 8, 9 y 10

// Clase Fecha
class Fecha {
  public:
    Fecha(int mes, int dia);
    int mes();
    int dia();

    #if EJ >= 9 // Para ejercicio 9
    bool operator==(Fecha o);
    #endif

    void incrementar_dia();

  private:
    int mes_;
    int dia_;
};

Fecha::Fecha(int mes, int dia): mes_(mes), dia_(dia) {}

int Fecha::mes() {
    return mes_;
}

int Fecha::dia() {
    return dia_;
}

ostream& operator<<(ostream& os, Fecha f) {
    os << f.dia() << "/" << f.mes();
    return os;
}

bool Fecha::operator==(Fecha f) {
    return dia_ == f.dia() && mes_ == f.mes();
}

#if EJ >= 9
/*
bool Fecha::operator==(Fecha o) {
    bool igual_dia = this->dia() == o.dia() && this->mes() == o.mes();
    return igual_dia;
}
*/
#endif

void Fecha::incrementar_dia() {
    if(dia_ + 1 > dias_en_mes(mes_)) {
        dia_ = 1;
        mes_++;
        if (mes_ == 13)
            mes_ = 1;
    } else
        dia_++;
}

// Ejercicio 11, 12

class Horario {
    public:
        Horario(uint hora, uint min);
        uint hora();
        uint min();

        bool operator<(Horario h);

    private:
        uint hora_;
        uint min_;
};

Horario::Horario(uint hora, uint min): hora_(hora), min_(min) {}

uint Horario::hora() {
    return hora_;
}

uint Horario::min() {
    return min_;
}

ostream& operator<<(ostream& os, Horario h) {
    os << h.hora() << ":" << h.min();
    return os;
}

bool Horario::operator<(Horario h) {
    return hora_ < h.hora() || (hora_ = h.hora() && min_ < h.min());
}

// Ejercicio 13

class Recordatorio {
    public:
        Recordatorio(Fecha f, Horario h, string m);
        string mensaje();
        Fecha fecha();
        Horario horario();

    private:
        string m_;
        Fecha f_;
        Horario h_;
};

Recordatorio::Recordatorio(Fecha fecha, Horario horario, string mensaje):
        m_(mensaje), f_(fecha), h_(horario){}

string Recordatorio::mensaje() {
    return m_;
}

Fecha Recordatorio::fecha() {
    return f_;
}

Horario Recordatorio::horario() {
    return h_;
}

ostream& operator<<(ostream& os, Recordatorio r) {
    os << r.mensaje() << " @ " << r.fecha() << " " << r.horario();
    return os;
}

// Ejercicio 14

class Agenda {
    public:
        Agenda(Fecha fecha_inicial);
        void agregar_recordatorio(Recordatorio rec);
        void incrementar_dia();
        list<Recordatorio> recordatorios_de_hoy();
        Fecha hoy();

    private:
        Fecha f_;
        list<Recordatorio> r_;
};

Agenda::Agenda(Fecha fecha_inicial): f_(fecha_inicial) {}

void Agenda::agregar_recordatorio(Recordatorio r) {
    r_.push_back(r);
}

void Agenda::incrementar_dia() {
    f_.incrementar_dia();
}

Fecha Agenda::hoy() {
    return f_;
}

bool compRecordatorios(Recordatorio &r1, Recordatorio &r2) {
    return r1.horario() < r2.horario();
}

list<Recordatorio> Agenda::recordatorios_de_hoy() {
    list<Recordatorio> temp;
    for(Recordatorio k : r_) {
        if(k.fecha() == hoy())
            temp.push_back(k);
    }
    temp.sort(compRecordatorios);
    return temp;
}

ostream& operator<<(ostream& os, Agenda a) {
    os << a.hoy() << endl;
    os << "=====" << endl;
    for(Recordatorio k : a.recordatorios_de_hoy())
        os << k << endl;
    return os;
}