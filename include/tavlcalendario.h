#ifndef _TAVLCalendario_H_
#define _TAVLCalendario_H_

#include <iostream>
#include <queue>
#include "tcalendario.h"
#include "tvectorcalendario.h"

using namespace std;
class TNodoAVL;

class TAVLCalendario{
    private:
        TNodoAVL *raiz;
        void InordenAux(TVectorCalendario &, int &) const;
        void PreordenAux(TVectorCalendario &, int &);
        void PostordenAux(TVectorCalendario &, int &);
        TNodoAVL* MaximoNodoIzq(TNodoAVL *&);
        TNodoAVL* MinimoNodoDe(TNodoAVL *&);
        
    public: 

        // Constructor por defecto
        TAVLCalendario ();

        // Constructor de copia
        TAVLCalendario (const TAVLCalendario &);

        // Destructor
        ~TAVLCalendario ();

        // Sobrecarga del operador asignación
        TAVLCalendario & operator=(const TAVLCalendario &);
        
        // Sobrecarga del operador igualdad
        bool operator==(const TAVLCalendario &);

        bool operator!=(const TAVLCalendario &);

        // Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
        bool EsVacio() const;

        // Inserta el elemento en el árbol
        bool Insertar(const TCalendario &);

        // Borra el elemento en el árbol (criterio: sustituir por el mayor de la izq)
        bool Borrar(const TCalendario &);
        //bool BorrarAux(TNodoAVL *&, const TCalendario &);
        
        // Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
        bool Buscar(const TCalendario &) const;

        // Devuelve el elemento de la raíz del árbol
        TCalendario Raiz() const;

        // Devuelve la altura del árbol (la altura de un árbol vacío es 0)
        int Altura();
        
        // Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
        int Nodos() const;

        // Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
        int NodosHoja();

        // Devuelve el recorrido en INORDEN sobre un vector
        TVectorCalendario Inorden() const;

        // Devuelve el recorrido en PREORDEN sobre un vector
        TVectorCalendario Preorden();

        // Devuelve el recorrido en POSTORDEN sobre un vector
        TVectorCalendario Postorden();
        
        // Devuelve el recorrido en NIVELES sobre un vector
        TVectorCalendario Niveles() const;

        // Sobrecarga del operador salida
        friend ostream & operator<<(ostream &, const TAVLCalendario &);

    friend class TNodoAVL;
};

class TNodoAVL {
    private:
        TCalendario item;
        TAVLCalendario iz, de;
        int fe;
    public: 
        TNodoAVL();
        TNodoAVL(const TNodoAVL &);
        ~TNodoAVL();
        TNodoAVL & operator=(const TNodoAVL &);
    friend class TAVLCalendario;
};

#endif