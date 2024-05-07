#include "../include/tavlcalendario.h"

//====TNodoAVL====

TNodoAVL::TNodoAVL() : item(), iz(), de(), fe(0) {}


// Constructor de copia
TNodoAVL::TNodoAVL(const TNodoAVL &nodo) : item(nodo.item), iz(nodo.iz), de(nodo.de), fe(nodo.fe) {}

// Destructor
TNodoAVL::~TNodoAVL() {}

// Sobrecarga del operador asignación
TNodoAVL &TNodoAVL::operator=(const TNodoAVL &nodo) {
    if (this != &nodo) {
        item = nodo.item;
        iz = nodo.iz;
        de = nodo.de;
    }
    return *this;
}

//====TAVLCalendario====

// Constructor por defecto
TAVLCalendario::TAVLCalendario() {
    raiz = NULL;
}

// Constructor de copia
TAVLCalendario::TAVLCalendario(const TAVLCalendario &abb) {
    if (abb.raiz != NULL) {
        raiz = new TNodoAVL(*abb.raiz);
    } else {
        raiz = NULL;
    }
}

// Destructor
TAVLCalendario::~TAVLCalendario() {
    if (!EsVacio()) {
        raiz->iz.~TAVLCalendario();
        raiz->de.~TAVLCalendario();
        delete raiz;
        raiz = NULL;
    }
}

// Sobrecarga del operador de asignación
TAVLCalendario & TAVLCalendario::operator=(const TAVLCalendario &avl) {
   delete raiz;
   if(!avl.EsVacio())
        raiz = new TNodoAVL(*avl.raiz);
    return *this;
}

bool TAVLCalendario::EsVacio() const{
    return raiz==NULL;
}

bool TAVLCalendario::operator==(const TAVLCalendario &abb){
    TVectorCalendario inorden1 = Inorden();
    TVectorCalendario inorden2 = abb.Inorden();
    return inorden1 == inorden2;
}

bool TAVLCalendario::Insertar(const TCalendario &cal){
    if(raiz == NULL){
        raiz = new TNodoAVL();
        raiz->item = cal;
        return true;
    }
    else if(raiz->item == cal){
        return false;
    }
    else if(raiz->item < cal){
        return raiz->de.Insertar(cal);
    }
    else{
        return raiz->iz.Insertar(cal);
    }
}

bool TAVLCalendario::Borrar(const TCalendario &cal){
    if(raiz == NULL){
        return false;
    }
    else if(raiz->item < cal){
        return raiz->de.Borrar(cal);
    }
    else if(raiz->item > cal){
        return raiz->iz.Borrar(cal);
    }
    else{
        //Caso 1: hoja
        if(raiz->iz.raiz == NULL && raiz->de.raiz == NULL){
            raiz->~TNodoAVL();
            raiz = NULL;
        }
        else if(raiz->iz.raiz == NULL){ //Caso 2: hijos en derecha
            TNodoAVL *min = MinimoNodoDe(raiz->de.raiz);
            raiz->item = min->item;
            raiz->de.Borrar(min->item);
        }
        else{ //Caso 3: tanto hijos iz como hijos iz y derecha
            TNodoAVL *max = MaximoNodoIzq(raiz->iz.raiz);
            raiz->item = max->item;
            raiz->iz.Borrar(max->item);
        }
        return true;
    }
}

TNodoAVL* TAVLCalendario::MaximoNodoIzq(TNodoAVL *&nodo) {
    if (nodo->de.raiz == NULL) {
        return nodo;
    } else {
        return MaximoNodoIzq(nodo->de.raiz);
    }
}

TNodoAVL* TAVLCalendario::MinimoNodoDe(TNodoAVL *&nodo) {
    if (nodo->iz.raiz == NULL) {
        return nodo;
    } else {
        return MinimoNodoDe(nodo->iz.raiz);
    }
}

bool TAVLCalendario::Buscar(const TCalendario &cal) const{
    if(raiz == NULL){
        return false;
    }
    else if (raiz->item == cal){
        return true;
    }
    else if (raiz->item > cal){
        return raiz->iz.Buscar(cal);
    }
    else
        return raiz->de.Buscar(cal);
}

TCalendario TAVLCalendario::Raiz() const{
    if(!EsVacio())
        return raiz->item;
    else
        return TCalendario();
}

int TAVLCalendario::Altura(){
     if(raiz == NULL){
        return 0;
    }
    else{
        int derecha = raiz->de.Altura();;
        int izq = raiz->iz.Altura();
        return 1 + max(derecha,izq);
    }
}

int TAVLCalendario::Nodos() const{
    if(raiz == NULL){
        return 0;
    }
    else{
        int derecha = raiz->de.Nodos();
        int izq = raiz->iz.Nodos();
        return 1 + derecha + izq;
    }
}

int TAVLCalendario::NodosHoja(){
    if(raiz == NULL){
        return 0;
    }
    else if(raiz->de.raiz == NULL && raiz->iz.raiz == NULL){
        return 1;
    }
    else{
        int derecha = raiz->de.NodosHoja();
        int izq = raiz->iz.NodosHoja();
        return derecha + izq;
    }
}

TVectorCalendario TAVLCalendario::Inorden() const{
    if(EsVacio()){
        return TVectorCalendario();
    }
    else{
    int pos = 1;
    TVectorCalendario v = TVectorCalendario(Nodos());
    InordenAux(v, pos);
    return v;
    }
}

void TAVLCalendario::InordenAux(TVectorCalendario &v, int &pos) const{
    if(!EsVacio()){
        raiz->iz.InordenAux(v,pos);
        v[pos] = Raiz();
        pos++;
        raiz->de.InordenAux(v,pos);
    }
}

TVectorCalendario TAVLCalendario::Preorden(){
    int pos = 1;
    TVectorCalendario v = TVectorCalendario(Nodos());
    PreordenAux(v,pos);
    return v;
}

void TAVLCalendario::PreordenAux(TVectorCalendario &v, int &pos){
    if(!EsVacio()){
        v[pos] = Raiz();
        pos++;
        raiz->iz.PreordenAux(v,pos);
        raiz->de.PreordenAux(v,pos);
    }
}

TVectorCalendario TAVLCalendario::Postorden(){
    int pos = 1;
    TVectorCalendario v = TVectorCalendario(Nodos());
    PostordenAux(v,pos);
    return v;
}

void TAVLCalendario::PostordenAux(TVectorCalendario &v, int &pos){
    if(!EsVacio()){
        raiz->iz.PostordenAux(v,pos);
        raiz->de.PostordenAux(v,pos);
        v[pos] = Raiz();
        pos++;
    }
}

TAVLCalendario TAVLCalendario::operator+(const TAVLCalendario &abb) const{
    TAVLCalendario copia = TAVLCalendario(*this);
    TVectorCalendario inorden = abb.Inorden();

    for(int i = 1; i<=inorden.Tamano(); i++){
        copia.Insertar(inorden[i]);
    }

    return copia;
}

TAVLCalendario TAVLCalendario::operator-(const TAVLCalendario &abb) const{
    TAVLCalendario copia = TAVLCalendario(*this);
    TAVLCalendario resultante = TAVLCalendario();
    TVectorCalendario inorden = copia.Inorden();
    
    for(int i=1; i<=inorden.Tamano();i++){
        if(!abb.Buscar(inorden[i])){
            resultante.Insertar(inorden[i]);
        }
    }
    return resultante;
}

TVectorCalendario TAVLCalendario::Niveles() const{
    
    if (raiz == NULL) {
        return TVectorCalendario();
    }

    queue<TAVLCalendario> q;
    TVectorCalendario v(Nodos());

    TAVLCalendario abb = *this;
    q.push(abb);

    int i = 1;
    while (!q.empty()) {
        abb = q.front();
        q.pop();
        v[i++] = abb.raiz->item;

        if (!abb.raiz->iz.EsVacio()){
            q.push(abb.raiz->iz);
        }
        if (!abb.raiz->de.EsVacio()){
            q.push(abb.raiz->de);
        }
    }
    return v;
}

ostream & operator<<(ostream & os, const TAVLCalendario & abb) {
    TVectorCalendario v = abb.Niveles();
    os<<v;
    return os;
}



