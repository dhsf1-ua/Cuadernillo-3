#include <string.h>
#include "../include/tcalendario.h"

//función para saber si un año es bisiesto
bool isBisiesto(int a){
    if(a%100==0 && a%400==0){
        return true;
    }
    else if(a%4==0 && a%100==0){
        return false;
    }
    else if(a%4==0){
        return true;
    }
    else
        return false;
}

//funcion para saber dias en un mes
int diasMes(int mes, int anyo) {
    static const int diasEnMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int dias = diasEnMes[mes-1];
    
    if(isBisiesto(anyo) && mes == 2){
        dias++;
    }

    return dias;
}

//funcion para saber si una fecha tiene un formato correcto
bool checkDate(int dia, int mes, int anyo){
    if(anyo<1900 || dia <=0 || mes <=0 || dia > 31 || mes > 12){
        return true;
    }
    if((mes == 4 || mes == 6 || mes == 9 || mes == 11) && (dia > 30)){
        return true;
    }
    if((mes == 2)){
        if(dia>29){
            return true;
        }
        else if((dia == 29) && !isBisiesto(anyo)){
            return true;
        } 
    }
    return false;
}

TCalendario::TCalendario(int dia, int mes, int anyo, const char* mens){
    bool incoDate = checkDate(dia,mes,anyo);

    if(!incoDate){
        this->dia = dia;
        this->mes = mes;
        this->anyo = anyo;
        if (mens != NULL) {
            mensaje = new char[strlen(mens) + 1];
            strcpy(mensaje, mens);
        } else {
            mensaje = NULL;
        }
    }
    else{
        this->dia = 1;
        this->mes = 1;
        this->anyo = 1900;
        mensaje = NULL;
    }
}

TCalendario::~TCalendario(){
    if(mensaje!=NULL){ 
        delete[] mensaje;
        mensaje = NULL;
    }
    dia = 1;
    mes = 1;
    anyo = 1900;
    mensaje = NULL;
}

TCalendario::TCalendario(const TCalendario &cal) {
    dia = cal.dia;
    mes = cal.mes;
    anyo = cal.anyo;

    if (cal.mensaje != NULL) {
        mensaje = new char[strlen(cal.mensaje) + 1];
        strcpy(mensaje, cal.mensaje);
    } else {
        mensaje = NULL;
    }
}

TCalendario &TCalendario::operator=(const TCalendario &cal){
    if (this != &cal) {
        delete[] mensaje;

        dia = cal.dia;
        mes = cal.mes;
        anyo = cal.anyo;

        if (cal.mensaje != NULL) {
            mensaje = new char[strlen(cal.mensaje) + 1];
            strcpy(mensaje, cal.mensaje);
        } else {
            mensaje = NULL;
        }
    }
    return *this;
}

TCalendario TCalendario::operator+(int dias){ 
    TCalendario copia = *this;
    
    if(dias>=0){
        copia.dia += dias;
        while(copia.dia > diasMes(copia.mes, copia.anyo)){
            copia.dia -= (diasMes(copia.mes,copia.anyo));
            copia.mes++;
            if(copia.mes>12){
                copia.mes = 1;
                copia.anyo++;
            }
        }
    }
    
    return copia;
}

TCalendario TCalendario::operator-(int dias){
    TCalendario copia = *this;

    if(dias>=0){
        copia.dia -= dias;
        while(copia.dia <= 0 ){
            copia.dia += diasMes(copia.mes-1,copia.anyo);
            copia.mes--;
            if(copia.mes<=0){
                copia.mes = 12;
                copia.anyo--;
                copia.dia += 31;
            }
        }
        if(copia.anyo < 1900){ 
            return TCalendario(); 
        }
    }
    
    return copia;
}

//postincremento
TCalendario TCalendario::operator++(int){ 
    TCalendario copia(*this);
    *this = *this + 1;
    return copia;
}

//preincremento
TCalendario &TCalendario::operator++(){
    *this = *this + 1;
    return *this;
}

//postdecremento
TCalendario TCalendario::operator--(int){ 
    TCalendario copia(*this);
    *this = *this - 1;
    return copia;
}

//predecremento
TCalendario &TCalendario::operator--(){
    *this = *this - 1;
    return *this;
}

bool TCalendario::operator==(const TCalendario &cal){
    return(dia == cal.dia && mes == cal.mes && anyo == cal.anyo &&
     ((mensaje != NULL && cal.mensaje !=NULL && strcmp(mensaje, cal.mensaje) == 0) || (mensaje == NULL && cal.mensaje == NULL)));
}

bool TCalendario::operator!=(const TCalendario &cal){
    return !(*this == cal);
}

bool TCalendario::operator>(const TCalendario &cal){
    if(anyo > cal.anyo){
        return true;
    }
    else if(anyo==cal.anyo){
        if(mes > cal.mes){
            return true;
        }
        else if(mes == cal.mes){
            if(dia > cal.dia){
                return true;
            }
            else if(dia == cal.dia){
                if (*this == cal){
                    return false;
                }
                if(mensaje == NULL && cal.mensaje != NULL){
                    return false;
                }
                if(mensaje != NULL && cal.mensaje == NULL){
                    return true;
                }
                if(strcmp(mensaje,cal.mensaje) > 0){
                    return true;
                }
            }
        }
    }
    return false;
}

bool TCalendario::operator<(const TCalendario &cal){ 
    if(*this == cal){
        return false;
    }
    if (*this > cal){
        return false;
    }
    return true;
}

bool TCalendario::EsVacio(){
    return (*this == TCalendario());
}

bool TCalendario::ModFecha(int d,int m,int a){
    bool incoDate = checkDate(d,m,a);

    if(incoDate){
        return false;
    }
    else{
        dia = d;
        mes = m;
        anyo = a;
        return true;
    }
}

bool TCalendario::ModMensaje(const char *mens){
    delete[] mensaje;

    if (mens == NULL) {
        mensaje = NULL;
    } else {
        mensaje = new char[strlen(mens) + 1];
        strcpy(mensaje, mens);
    }

    return true;
}

int TCalendario::Dia() const{
    return this->dia;
}

int TCalendario::Mes() const{
    return this->mes;
}

int TCalendario::Anyo() const{
    return this->anyo;
}

char *TCalendario::Mensaje() const{ 
    return mensaje;
}

ostream & operator<<(ostream &os, const TCalendario &cal){
    if(cal.Dia() < 10) 
        os << "0" ;
    os << cal.Dia() << "/";

    if(cal.Mes() < 10)
        os << "0";
    os<< cal.Mes() << "/" << cal.Anyo() << " ";

    if(cal.Mensaje() == NULL)
        os << "\"\"";
    else
        os << "\"" << cal.Mensaje() << "\"";
    return os;
}