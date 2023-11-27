#include <vector>
#include "algobot.h"

using namespace std;

// Ejercicio 1
vector<int> quitar_repetidos(vector<int> s) {
    vector<int> temp;
    int cant = 0;
    if(s.size() >= 1) {
        temp.push_back(s[0]);
        for (int i = 1; i < s.size(); ++i) {
            for (int j = 0; j < temp.size(); ++j) {
                if (s[i] == temp[j]) {
                    cant++;
                }
            }
            if(cant == 0) {
                temp.push_back(s[i]);
            }
            cant = 0;
        }
    }
    return temp;
}

// Ejercicio 2
vector<int> quitar_repetidos_v2(vector<int> s) {
    set<int> temp;
    for (int i = 0; i < s.size(); ++i) {
        temp.insert(s[i]);
    }
    vector<int> res;
    for (int k : temp)
        res.push_back(k);
    return res;
}

// Ejercicio 3
int cantApariciones(vector<int> s, int a) {
    int cant = 0;
    for (int i = 0; i < s.size(); ++i) {
        if(s[i] == a)
            cant++;
    }
    return cant;
}

bool mismos_elementos(vector<int> a, vector<int> b) {
    bool mismos = true;
    for (int i = 0; i < a.size(); ++i) {
        mismos = mismos && cantApariciones(b, a[i]) > 0;
    }
    for (int i = 0; i < b.size(); ++i) {
        mismos = mismos && cantApariciones(a, b[i]) > 0;
    }
    return mismos;
}

// Ejercicio 4
bool mismos_elementos_v2(vector<int> a, vector<int> b) {
    set<int> tempA;
    set<int> tempB;
    for (int i = 0; i < a.size(); ++i) {
        tempA.insert(a[i]);
    }
    for (int i = 0; i < b.size(); ++i) {
        tempB.insert(b[i]);
    }
    return(tempA == tempB);
}

// Ejercicio 5
map<int, int> contar_apariciones(vector<int> s) {
    map<int, int> m;
    for (int i = 0; i < s.size(); ++i) {
        m[s[i]] = cantApariciones(s, s[i]);
    }
    return m;
}

// Ejercicio 6
vector<int> filtrar_repetidos(vector<int> s) {
    vector<int> temp;
    for (int i = 0; i < s.size(); ++i) {
        if(cantApariciones(s, s[i]) == 1)
            temp.push_back(s[i]);
    }
    return temp;
}

// Ejercicio 7
set<int> interseccion(set<int> a, set<int> b) {
    set<int> temp;
    for (int k : a)
        if(b.count(k) == 1)
            temp.insert(k);
    return temp;
}

// Ejercicio 8
map<int, set<int>> agrupar_por_unidades(vector<int> s) {
    map<int, set<int>> m;
    set<int> temp = {};
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < s.size(); ++j) {
            if(s[j] % 10 == i)
                temp.insert(s[j]);
        }
        if(!temp.empty()) {
            m[i] = temp;
            temp = {};
        }
    }
    return m;
}

// Ejercicio 9
vector<char> traducir(vector<pair<char, char>> tr, vector<char> str) {
    vector<char> s;
    int cant = 0;
    for (int i = 0; i < str.size(); ++i) {
        cant = 0;
        for (int j = 0; j < tr.size(); ++j) {
            if(str[i] == tr[j].first) {
                s.push_back(tr[j].second);
                cant++;
            }
        }
        if(cant == 0) {
            s.push_back(str[i]);
            cant = 0;
        }
    }
    return s;
}

// Ejercicio 10
// QUEDAN CORREGIR CASOS DONDE LOS GRUPOS SON DE UN INTEGRANTE

bool IgualesLU(LU a, LU b) {
    return a.numero() == b.numero() && a.anio() == b.anio();
}

bool IgualesGrupo(vector<LU> a, vector<LU> b) {
    return IgualesLU(a[0], b[0]) && !IgualesLU(a[1], b[1]) ||
        !IgualesLU(a[0], b[0]) && IgualesLU(a[1], b[1]) ;
}


bool integrantes_repetidos(vector<Mail> s) {
    bool hayRep = false;
    vector<vector<LU>> lib;
    vector<LU> temp;

    for (int i = 0; i < s.size(); ++i) {
        for (LU k : s[i].libretas()) {
            temp.push_back(k);
        }
        lib.push_back(temp);
        temp = {};
    }

    for (int i = 0; i < lib.size(); ++i) {
        for (int j = i + 1; j < lib.size(); ++j) {
            if(IgualesGrupo(lib[i], lib[j]))
                hayRep = true;
        }
    }
    return hayRep;
}

// Ejercicio 11
map<set<LU>, Mail> entregas_finales(vector<Mail> s) {
  return map<set<LU>, Mail>();
}
