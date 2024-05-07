#ifndef _TCALENDARIO_H_
#define _TCALENDARIO_H_

#include <iostream>

using namespace std;

class TCalendario {
    private:

        int dia;
        int mes;
        int anyo;
        char* mensaje;

    public:

        //TCalendario();
        TCalendario(int dia = 1, int mes = 1, int anyo = 1900, const char* mens = NULL);
        TCalendario(const TCalendario &cal);
        ~TCalendario();
        TCalendario & operator=(const TCalendario &cal);

        // Sobrecarga del operador: SUMA de fecha + un número de dias;
        TCalendario operator+(int dias);
        // Sobrecarga del operador: RESTA de fecha - un número de dias;
        TCalendario operator-(int dias);
        // Modifica la fecha incrementándola en un dia (con postincremento);
        TCalendario operator++(int);
        // Modifica la fecha incrementándola en un dia (con preincremento);
        TCalendario & operator++();
        // Modifica la fecha decrementándola en un dia (con postdecremento);
        TCalendario operator--(int);
        // Modifica la fecha decrementándola en un día (con predecremento);
        TCalendario & operator--();
        // Modifica la fecha
        bool ModFecha (int d, int m, int a);
        // Modifica el mensaje
        bool ModMensaje(const char * mens);
        // Sobrecarga del operador igualdad;
        bool operator ==(const TCalendario &cal);
        // Sobrecarga del operador desigualdad;
        bool operator !=(const TCalendario &cal);
        // Sobrecarga del operador >; (ver ACLARACIÓN sobre ORDENACIÓN)
        bool operator>(const TCalendario &cal);
        // Sobrecarga del operador <; (ver ACLARACIÓN sobre ORDENACIÓN)
        bool operator<(const TCalendario &cal);
        //TCalendario vacío
        bool EsVacio();
        // Devuelve el día del calendario;
        int Dia() const;
        // Devuelve el mes del calendario;
        int Mes() const;
        // Devuelve el año del calendario;
        int Anyo() const;
        // Devuelve el mensaje del calendario;
        char *Mensaje() const;

        friend ostream & operator<<(ostream &os, const TCalendario &cal);
};

#endif
