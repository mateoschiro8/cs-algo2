#include <iostream>

using namespace std;

using uint = unsigned int;

// Ejercicio 1

class Rectangulo {
    public:
        Rectangulo(uint alto, uint ancho);
        uint alto();
        uint ancho();
        float area();

    private:
        int alto_;
        int ancho_;
};

Rectangulo::Rectangulo(uint alto, uint ancho) : alto_(alto), ancho_(ancho) {};

uint Rectangulo::alto() {
    // Completar
    return alto_;
}

uint Rectangulo::ancho() {
    // Completar
    return ancho_;
}

float Rectangulo::area() {
    return alto_ * ancho_;
}


// Ejercicio 2

float PI = 3.14;

class Elipse {
    public:
        Elipse(uint a, uint b);
        uint r_a();
        uint r_b();
        float area();

    private:
        int ra_;
        int rb_;
};

Elipse::Elipse(uint a, uint b): ra_(a), rb_(b) { }

uint Elipse::r_a() {
    return ra_;
}

uint Elipse::r_b() {
    return rb_;
}

float Elipse::area() {
    return ra_ * rb_ * PI;
}


// Ejercicio 3

class Cuadrado {
    public:
        Cuadrado(uint lado);
        uint lado();
        float area();

    private:
        Rectangulo r_;
};

Cuadrado::Cuadrado(uint lado): r_(lado, lado) {}

uint Cuadrado::lado() {
    return r_.alto();
}

float Cuadrado::area() {
    return r_.area();
}

// Ejercicio 4

// Clase Circulo

class Circulo {
    public:
        Circulo(uint radio);
        uint radio();
        float area();

    private:
        Elipse e_;
};

Circulo::Circulo(uint radio): e_(radio, radio) {}

uint Circulo::radio() {
    return e_.r_a();
}

float Circulo::area() {
    return e_.area();
}


// Ejercicio 5

ostream& operator<<(ostream& os, Rectangulo r) {
    os << "Rect(" << r.alto() << ", " << r.ancho() << ")";
    return os;
}

ostream& operator<<(ostream& os, Elipse e) {
    os << "Elipse(" << e.r_a() << ", " << e.r_b() << ")";
    return os;
}

// Ejercicio 6

ostream& operator<<(ostream& os, Cuadrado c) {
    os << "Cuad(" << c.lado() << ")";
    return os;
}

ostream& operator<<(ostream& os, Circulo c) {
    os << "Circ(" << c.radio() << ")";
    return os;
}

