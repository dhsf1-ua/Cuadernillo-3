#include <string.h>
#include "../include/tvectorcalendario.h"

TVectorCalendario::TVectorCalendario(){
    c = NULL;
    tamano = 0;
    error = TCalendario(); //?
}

TVectorCalendario::TVectorCalendario(int tam){
    error = TCalendario();
    if (tam>0){
        tamano = tam;
        c = new TCalendario[tam];
    }
    else{
        c = NULL;
        tamano = 0;
    }
}

TVectorCalendario::TVectorCalendario(const TVectorCalendario &vcal){
    error = TCalendario();
    if (vcal.tamano>0){
        tamano = vcal.tamano;
        c = new TCalendario[vcal.tamano];
        for(int i=0; i<vcal.tamano; i++){
            c[i] = vcal.c[i];
        }
    }
    else{
        c = NULL;
        tamano = 0;
    }
}

TVectorCalendario::~TVectorCalendario(){
    delete[] c;
    c = NULL;
    tamano = 0;
}

TVectorCalendario &TVectorCalendario::operator=(const TVectorCalendario &vcal){
    if(this != &vcal){
        delete[] c;
        tamano = vcal.tamano;
        if(tamano>0){
            c = new TCalendario[tamano];
            for(int i=0; i<vcal.tamano; i++){
                c[i] = vcal.c[i];
            }
        }
        else
            c = NULL;
    }
    return *this;
}

bool TVectorCalendario::operator==(const TVectorCalendario &vcal){
    if (tamano == vcal.tamano){
        for(int i = 0; i<tamano; i++){
            if(c[i] != vcal.c[i]){
                return false;
            }
        }
        return true;
    }
    else
        return false;
}

bool TVectorCalendario::operator!=(const TVectorCalendario &vcal){
    return !(*this == vcal);
}

//parte izq
TCalendario &TVectorCalendario::operator[](int pos){
    if(pos>=1 && pos<=tamano){
        return c[pos-1];
    }
    else   
        return this->error;
}

TCalendario TVectorCalendario::operator[](int pos) const{
    if(pos>=1 && pos<=tamano){
        return c[pos-1];
    }
    else   
        return this->error;
}

int TVectorCalendario::Tamano(){ //es correcto?
    return tamano;
}

int TVectorCalendario::Ocupadas(){
    int contador = 0;
    for(int i=0; i<tamano; i++){
        if(!c[i].EsVacio()){
            contador++;
        }
    }
    return contador;
}

bool TVectorCalendario::ExisteCal(const TCalendario &cal){
    for(int i=0; i<tamano; i++){
        if(c[i] == cal){
            return true;
        }
    }
    return false;
}

void TVectorCalendario::MostrarMensajes(int dia, int mes, int anyo){
    bool impreso = false;
    TCalendario auxCal(dia,mes,anyo,NULL);
    cout<<"[";
    if(!auxCal.EsVacio()){
        for(int i = 0; i<tamano; i++){
            if(c[i]==auxCal || c[i]>auxCal){
                if(!impreso){
                    impreso = true;
                    cout<<c[i];
                }  
                else{
                    cout<<", "<<c[i];
                }
            }
        }
    }
    cout<<"]";
}

bool TVectorCalendario::Redimensionar(int tam){ //duda
    if(tam<=0){
        return false;
    }
    if(tam == tamano){
        return false;
    }

    TCalendario *newVec = new TCalendario[tam];
    if(tam > 0 && tam > tamano){
        for(int i=0; i<tamano; i++){
            newVec[i] = c[i];
        }
        for(int j = tamano; j<tam; j++){
            newVec[j] = TCalendario();
        }
    }
    if(tam > 0 && tam < tamano){
        for(int i=0; i<tam; i++){
            newVec[i] = c[i];
        }
    }

    delete[] c;
    c = newVec;
    tamano = tam;
    return true;
}

ostream &operator<<(ostream &os, const TVectorCalendario &vcal){
    bool first = true;
    os<<"[";
    for(int i=0; i<vcal.tamano;i++){
        if(first){
            os << "(" << i+1 << ") " << vcal.c[i];
            first = false;
        }
        else
            os << ", (" << i+1 << ") " << vcal.c[i];
    }
    os<<"]";
    return os;
}
