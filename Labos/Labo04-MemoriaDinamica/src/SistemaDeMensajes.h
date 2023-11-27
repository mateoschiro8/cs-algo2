#ifndef SISTEMADEMENSAJES_H
#define SISTEMADEMENSAJES_H

#include "ConexionJugador.h"
#include <string>
#include <vector>

#if EJ == 4 || EJ == 5
#include "Proxy.h"
#elif EJ == 6
#include "Proxy2.h"
#endif

using namespace std;

class SistemaDeMensajes {
  public:
    SistemaDeMensajes();
    class Proxy;
    void registrarJugador(int id, string ip);
    bool registrado(int id) const;
    void enviarMensaje(int id, string mensaje);
    string ipJugador(int id) const;
    void desregistrarJugador(int ip);
    Proxy* obtenerProxy(int id);

    ~SistemaDeMensajes();

    class Proxy {
    public:
        Proxy(ConexionJugador** conn);
        void enviarMensaje(string msg);

    private:
        ConexionJugador** _conn;
        Proxy(const Proxy&);
    };

  private:
    ConexionJugador* _conns[4];
    vector<Proxy*> _proxys;
};

#endif

/*
class SistemaDeMensajes {
  public:
    SistemaDeMensajes();
    // Pre: 0 <= id < 4
    void registrarJugador(int id, string ip);
    // Pre: 0 <= id < 4
    bool registrado(int id) const;

    // Pre: registrado(id)
    void enviarMensaje(int id, string mensaje);

    // Pre: registrado(id)
    string ipJugador(int id) const;

    void desregistrarJugador(int ip);

    Proxy* obtenerProxy(int id);

    ~SistemaDeMensajes();

  private:
    ConexionJugador* _conns[4];
    vector<Proxy*> _proxys;
};

 */