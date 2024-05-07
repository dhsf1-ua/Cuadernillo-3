#ifndef _TVECTORCALENDARIO_H_
#define _TVECTORCALENDARIO_H_

#include <iostream>
#include "tcalendario.h"

using namespace std;

class TVectorCalendario{
    private:
        TCalendario *c;
        int tamano;
        TCalendario error;

    public:
        TVectorCalendario();
        TVectorCalendario(int);
        TVectorCalendario(const TVectorCalendario &);
        ~TVectorCalendario();
        TVectorCalendario &operator=(const TVectorCalendario &);
        bool operator==(const TVectorCalendario &);
        bool operator!=(const TVectorCalendario &);
        //parte izq
        TCalendario &operator[](int);
        //parte derecha
        TCalendario operator[](int) const;
        int Tamano();
        //cantidad de posiciones ocupadas (no vacías)
        int Ocupadas();
        //devuelve true si existe el calendario en el vector
        bool ExisteCal(const TCalendario &);
        //Mostrar por pantalla mensajes de TCalendario en el vector, de fecha igual o posterior a la pasada
        void MostrarMensajes(int,int,int);
        bool Redimensionar(int);

        friend ostream &operator<<(ostream &os, const TVectorCalendario &);


};

#endif