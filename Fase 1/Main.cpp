#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include "recursos/sha256.h"
#include "json/json.h"


#define color SetConsoleTextAttribute
using namespace std;

struct Usuario{
    string nick;
    string password;
    string edad;
    string moneda;
};

struct Articulo{
    string id;
    string categoria;
    string precio;
    string nombre;
    string src;
};

struct Movimiento{
    string mov_x;
    string mov_y;
};
///////////////////////////////////////////////////////////////////// EMPIEZA LISTA ////////////////////////////////////////////////////////////////////////

class Lista{
    private:
        class Nodo{
            public: 
                Nodo *siguiente;
                Articulo articulo;
                Lista *lista;
                string categoria;
        };
        Nodo *raiz;
        Nodo *ultimo;
    public:
        Lista();
        ~Lista();
        void insertarNodo(Articulo articulo);
        void insertarNodoC(string categoria , Lista lista);
        bool vacia();
        void imprimir(); 
};

Lista::Lista(){
    raiz = NULL;
    cabeza = NULL;
    cola = NULL;
    ultimo = NULL;

}

Lista::~Lista()     //sirve para destruir la lista circular con todos sus nodos
{ 
    if (raiz != NULL) {
        Nodo *reco = raiz->siguiente;
        Nodo *bor;
        while (reco != raiz)
        {
            bor = reco;
            reco = reco->siguiente;
            delete bor;
        }
        delete raiz;
    }
    if (cabeza != NULL) {
        NodoC *reco = cabeza->siguiente;
        NodoC *bor;
        while (reco != cabeza)
        {
            bor = reco;
            reco = reco->siguiente;
            delete bor;
        }
        delete cabeza;
    }
}

void Lista::insertarNodo(Articulo articulo) {
    Nodo *nuevo = new Nodo();
    nuevo->articulo = articulo;
    if (raiz == NULL) 
    {
        ultimo = nuevo;
        raiz = nuevo;

    }
    else 
    {
        ultimo->siguiente = nuevo;
        nuevo->siguiente = NULL;
        ultimo = nuevo;
    }
}

void Lista::insertarNodoC(string categoria, Lista list) {
    Nodo *nuevo = new Nodo();
    nuevo -> categoria = categoria;
    nuevo -> lista = list;
    if (cola == NULL) 
    {
        cola = nuevo;
        cabeza = nuevo;

    }
    else 
    {
        cola->siguiente = nuevo;
        nuevo->siguiente = NULL;
        cola = nuevo;
    }
}

bool Lista::vacia()
{
    if (raiz == NULL)
        return true;
    else
        return false;
}
/*
void Lista::imprimir()    /// esto  quiere revisar
{
    if (!vacia()) {
        Nodo *reco = raiz;
        do {
            cout<<reco->dato.nick<<endl;
            cout<<reco->dato.moneda<<endl;
            reco = reco->siguiente;
        } while (reco != raiz);
        
    }
    else{
        cout<<"No existen elementos en la lista"<<endl;
        getch();
    }
}*/
//////////////////////////////////////////////////////////////////////// EMPIEZA LISTA CIRUCLAR ////////////////////////////////////////////////////////////////////////////
class ListaCircular{
    private:
        class Nodo{
            public: 
                Usuario dato;
                Nodo *siguiente;
                Nodo *anterior;
        };
        Nodo *raiz;
    public:
        ListaCircular();
        ~ListaCircular();
        void insertarNodo(Usuario x);
        bool vacia();
        void imprimir();
    
};

ListaCircular::ListaCircular(){
    raiz = NULL;
}

ListaCircular::~ListaCircular()     //sirve para destruir la lista circular con todos sus nodos
{ 
    if (raiz != NULL) {
        Nodo *reco = raiz->siguiente;
        Nodo *bor;
        while (reco != raiz)
        {
            bor = reco;
            reco = reco->siguiente;
            delete bor;
        }
        delete raiz;
    }
}

void ListaCircular::insertarNodo(Usuario x) 
{
    Nodo *nuevo = new Nodo();
    nuevo->dato = x;
    if (raiz == NULL) 
    {
        nuevo->siguiente = nuevo;
        nuevo->anterior = nuevo;
        raiz = nuevo;
    }
    else 
    {
        Nodo *ultimo = raiz->anterior;
        nuevo->siguiente = raiz;
        nuevo->anterior = ultimo;
        raiz->anterior = nuevo;
        ultimo->siguiente = nuevo;
    }
}

bool ListaCircular::vacia()
{
    if (raiz == NULL)
        return true;
    else
        return false;
}

void ListaCircular::imprimir()
{
    if (!vacia()) {
        Nodo *reco = raiz;
        do {
            cout<<reco->dato.nick<<endl;
            cout<<reco->dato.moneda<<endl;
            reco = reco->siguiente;
        } while (reco != raiz);
        
    }
    else{
        cout<<"No existen elementos en la lista"<<endl;
        getch();
    }
}
//////////////////////////////////////////////////////////////////////// EMPIEZA COLA //////////////////////////////////////////////////////////////////////////

class Cola {
private:
    class Nodo {
    public:
        movimiento mov;
        Nodo *sig;
        string ancho;
        string alto;
    };
    Nodo *raiz;
    Nodo *ultimo:
    public:
        Cola();
        ~Cola();
        void encolar(Movimiento mov);
        bool vacia();
        void imprimir();
        void descolar();
};

Cola::Cola(){
    raiz = NULL;
    ultimo = NULL;
}

Cola::~Cola(){
    if (raiz != NULL) {
        Nodo *reco = raiz->sig;
        Nodo *bor;
        while (reco != raiz)
        {
            bor = reco;
            reco = reco->sig;
            delete bor;
        }
        delete raiz;
    }
}

void Cola::encolar(Movimiento mov) {
    Nodo *nuevo = new Nodo();
    nuevo->mov = mov;
    if (raiz == NULL) {
        raiz = nuevo;
        ultimo = nuevo;
    }
    else{
        ultimo->sig = nuevo;
        nuevo->sig = NULL;
        ultimo = nuevo;
    }
}

bool Cola::vacia(){
    if (raiz == NULL)
        return true;
    else
        return false;
}

void Cola::imprimir(){
    if (!vacia()) {
        Nodo *reco = raiz;
        do {
         //   cout<<reco->info  <<"-";     modificar
            reco = reco->sig;
        } while (reco != NULL);
    }
}

void Cola::descolar(){
    raiz = raiz->sig;    
}

/////////////////////////////////////////////////////////////////////////// EMPIEZA PILA /////////////////////////////////////////////////////////////////

class Pila{
private:
    class Nodo {
        public:
            Nodo *abajo;
       
    };
    Nodo *cima;
    public:
    Pila();
    ~Pila();
    void push();
    bool vacia();
    void imprimir();
    void pop();
};

Pila::Pila(){
    cima = NULL;
   
}

Pila::~Pila(){
    if (cima != NULL) {
        Nodo *reco = cima->abajo;
        Nodo *bor;
        while (reco != NULL)
        {
            bor = reco;
            reco = reco->abajo;
            delete bor;
        }
        delete cima;
    }
}

void Pila::push() {
    Nodo *nuevo = new Nodo();
    nuevo->mov = mov;
    if (raiz == NULL) {
        raiz = nuevo;
        ultimo = nuevo;
    }
    else{
        ultimo->sig = nuevo;
        nuevo->sig = NULL;
        ultimo = nuevo;
    }
}

bool Pila::vacia(){
    if (raiz == NULL)
        return true;
    else
        return false;
}

void Pila::imprimir(){
    if (!vacia()) {
        Nodo *reco = raiz;
        do {
         //   cout<<reco->info  <<"-";     modificar
            reco = reco->sig;
        } while (reco != NULL);
    }
}

void Pila::descolar(){

    cima = cima->abajo;    
}


////////////////////////////////////////////////////////////////////////// FUNCIONES /////////////////////////////////////////////////////////////////////
void carga();

void limpiar();

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 

void menu();

int main() {
    menu();
    return 0;

}

void limpiar(){
    for(int i = 1 ; i<200;i++){
        cout<<" "<<endl;
    }
}

void carga(){
    /*
    string msg;
    cout << "Escribe el mensaje:\n";
	cin >> ws;
	getline(cin, msg);
	string nuevo = SHA256::cifrar(msg);   //Sirve para encriptar la contraseña ahora solo falta decencriptar
	cout << "\nHash resultante: " << nuevo;
	cout << "\n";*/
    //usuario user("tato","tato961122",25,300);
    ListaCircular *lc = new ListaCircular();
    Usuario us,no;
    us.edad = "25";
    us.moneda = "200";
    us.nick = "tato961122";
    us.password = "4234f" ;
    no.edad = "24";
    no.moneda = "240";
    no.nick = "fdfdf";
    no.password = "fsf";
    lc->insertarNodo(no);
    lc->insertarNodo(us);
    lc->imprimir();
    getch();
    


}

void menu(){
    int opcion=0;
    color(hConsole, 10);
    cout<<"          MENU              "<<endl;
    cout<<"****************************"<<endl;
    cout<<"*  1. Carga Masiva         *"<<endl;
    cout<<"*  2. Registrar Usuario    *"<<endl;
    cout<<"*  3. Login                *"<<endl;
    cout<<"*  4. Reportes             *"<<endl;
    cout<<"*  5. Salir del juego      *"<<endl;
    cout<<"****************************"<<endl;
    cout<<"  Ingrese una opcion: ";
    cin>>opcion;
    switch(opcion) {
        case 1:
            carga();
            limpiar();
            menu();
        break;
        case 2:
            cout<<"opcion2"<<endl;
        break;
        case 3:
            cout<<"opcion2"<<endl;
        break;
        case 4:
            cout<<"opcion2"<<endl;
        break;
        case 5:
            color(hConsole,9);
            cout<<"  Adios"<<endl;
            getch();
        break;
        default:
        color(hConsole,14);
        cout<<"Por favor ingrese una opcion valida"<<endl;
        getch();
        limpiar();
        menu();
      
        

}

}
