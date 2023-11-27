#include "SistemaDeMensajes.h"

// Completar...

SistemaDeMensajes::SistemaDeMensajes(): _conns(), _proxys() {};

// Pre: 0 <= id < 4
void SistemaDeMensajes::registrarJugador(int id, string ip) {
        desregistrarJugador(id);
        _conns[id] = new ConexionJugador(ip);
}

// Pre: 0 <= id < 4
bool SistemaDeMensajes::registrado(int id) const {
    return _conns[id] != nullptr;
}

// Pre: registrado(id)
void SistemaDeMensajes::enviarMensaje(int id, string mensaje) {
    _conns[id]->enviarMensaje(mensaje);
}

// Pre: registrado(id)
string SistemaDeMensajes::ipJugador(int id) const {
    return _conns[id]->ip();
}

SistemaDeMensajes::~SistemaDeMensajes() {
    for (int id = 0; id < 4; ++id) {
        delete _conns[id];
    }
    for (int i = 0; i < _proxys.size(); ++i) {
        delete _proxys[i];
    }
}

void SistemaDeMensajes::desregistrarJugador(int id) {
    if (registrado(id)) {
        delete _conns[id];
        _conns[id] = nullptr;
    }
}

SistemaDeMensajes::Proxy* SistemaDeMensajes::obtenerProxy(int id) {
    Proxy* p = new Proxy(&_conns[id]);
    _proxys.push_back(p);
    return p;
}

SistemaDeMensajes::Proxy::Proxy(ConexionJugador** conn): _conn(conn) { }

void SistemaDeMensajes::Proxy::enviarMensaje(string msg) {
    (*_conn)->enviarMensaje(msg);
}

/*
SistemaDeMensajes::SistemaDeMensajes(): _conns(), _proxys() {};

// Pre: 0 <= id < 4
void SistemaDeMensajes::registrarJugador(int id, string ip) {
        desregistrarJugador(id);
        _conns[id] = new ConexionJugador(ip);
}

// Pre: 0 <= id < 4
bool SistemaDeMensajes::registrado(int id) const {
    return _conns[id] != nullptr;
}

// Pre: registrado(id)
void SistemaDeMensajes::enviarMensaje(int id, string mensaje) {
    _conns[id]->enviarMensaje(mensaje);
}

// Pre: registrado(id)
string SistemaDeMensajes::ipJugador(int id) const {
    return _conns[id]->ip();
}

SistemaDeMensajes::~SistemaDeMensajes() {
    for (int id = 0; id < 4; ++id) {
        delete _conns[id];
    }
    for (int i = 0; i < _proxys.size(); ++i) {
        delete _proxys[i];
    }
}

void SistemaDeMensajes::desregistrarJugador(int id) {
    if (registrado(id)) {
        delete _conns[id];
        _conns[id] = nullptr;
    }
}

Proxy* SistemaDeMensajes::obtenerProxy(int id) {
    Proxy* p = new Proxy(&_conns[id]);
    _proxys.push_back(p);
    return p;
}

*/