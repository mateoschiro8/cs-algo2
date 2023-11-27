#include "gtest-1.8.1/gtest.h"
#include "../src/Libreta.h"
#include "../src/Truco.h"
#include <map>
#include <cmath>

using namespace std;

// Ejercicio 4
TEST(Aritmetica, suma) {
    int calculado = 15 + 7;
    int esperado = 22;
    EXPECT_EQ(calculado, esperado);
}

// Ejercicio 5
TEST(Aritmetica, potencia) {
    float calculado = pow(10,2);
    float esperado = 100;
    EXPECT_EQ(calculado, esperado);
}

// Ejercicios 6..9

TEST(Aritmetica, potencia_general) {
    vector{float} esperado = {25,16,9,4,1,0,1,4,9,16,25};
    vector{float} calculado;
    for (int i = -5; i < 6; ++i) {
        calculado.push_back(pow(i,2)),
    }
    EXPECT_EQ(calculado, esperado);
}

TEST(Diccionario, obtener) {
    map<int,int> m;
    m[2] = 5;
    EXPECT_EQ(m[2], 5);
}

TEST(Diccionario, definir) {
    map<int,int> m;
    EXPECT_EQ(m.count(2), 0);
    m[2] = 5;
    EXPECT_EQ(m.count(2), 1);
}

TEST(Truco, inicio) {
    Truco t;
    EXPECT_EQ(t.puntaje_j1(), 0);
    EXPECT_EQ(t.puntaje_j2(), 0);
}

TEST(Truco, buenas) {
    Truco t;
    EXPECT_EQ(t.buenas(1), false);
    for (int i = 0; i < 15; ++i) {
        t.sumar_punto(1);
    }
    EXPECT_EQ(t.buenas(1), false);
    t.sumar_punto(1);
    EXPECT_EQ(t.buenas(1), true);
    for (int i = 0; i < 2; ++i) {
        t.sumar_punto(1);
    }
    EXPECT_EQ(t.buenas(1), true);
}
