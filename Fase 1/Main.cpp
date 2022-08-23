#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <string.h>
#include "recursos/sha256.h"
#include <jsoncpp/json/json.h>


#define color SetConsoleTextAttribute
using namespace std;
using namespace Json;

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
    string ancho;
    string alto;
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
       
    public:
        Lista();
        ~Lista();
        void insertarNodo(Articulo articulo);
        void insertar(Articulo articulo);
        bool vacia();
        void imprimir(); 
};

Lista::Lista(){
    raiz = NULL;
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
}

void Lista::insertarNodo(Articulo articulo) {
    Nodo *nuevo = new Nodo();
    nuevo->articulo = articulo;
    if (raiz == NULL){
        raiz = nuevo;
        nuevo->articulo = articulo;
        nuevo->siguiente = NULL;
    }
    else{
        Nodo *reco = raiz;
       
        while (reco->siguiente != NULL){
            reco = reco->siguiente;
        }
        reco->siguiente = nuevo;
        nuevo->siguiente = NULL;
        nuevo->articulo = articulo;
    }
   
   
}
/*sirve para insertar las cabezas pricipañes en la lista principañ de objetos*/
void Lista::insertar(Articulo articulo) {
    Nodo *nuevo = new Nodo();
    Nodo *reco;
    if (raiz == NULL){
        raiz = nuevo;
        raiz->categoria=articulo.categoria;
        Lista *lis = new Lista();
        nuevo->lista = lis;
        nuevo->siguiente = NULL;
        nuevo->lista->insertarNodo(articulo);
    }
    else{
        bool encontrado = false;
        reco = raiz; while (reco != NULL){
        if (reco->categoria == articulo.categoria){
            encontrado = true;
        }
        reco = reco->siguiente;
        } 
        if (encontrado == true){
            Lista *lisaux = new Lista();
            reco = raiz;
            while (reco != NULL){
            if (reco->categoria == articulo.categoria){
            lisaux = reco->lista;     
            }
            reco = reco->siguiente;
        } 
        lisaux->insertarNodo(articulo);
        }
        else{
            Lista *lis = new Lista();
            Nodo *reco = raiz;
            while (reco->siguiente != NULL){
                reco = reco->siguiente;
            }
            reco->siguiente = nuevo;
            nuevo->lista = lis;
            nuevo->categoria = articulo.categoria;
            lis->insertarNodo(articulo);
        }
    }
}

bool Lista::vacia()
{
    if (raiz == NULL)
        return true;
    else
        return false;
}

void Lista::imprimir()    /// esto  quiere revisar
{
    if (!vacia()) {
        Nodo *reco = raiz;
        do {
            cout<<endl;
            cout<<"Categoria: "<<reco->categoria<<endl;
            Nodo *aux = reco->lista->raiz;
            while(aux != NULL ){
                cout<<aux->articulo.id<<" "<<aux->articulo.categoria<<" "<<aux->articulo.nombre<<" "<<aux->articulo.precio<<" "<<aux->articulo.src<<endl;
                aux = aux->siguiente;
            }
            reco = reco->siguiente;
        } while (reco->siguiente != NULL);
    }
    else{
        cout<<"No existen elementos en la lista"<<endl;
       
    }
}
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
            cout<<reco->dato.password<<endl;
            cout<<reco->dato.edad<<endl;
            cout<<reco->dato.moneda<<endl;
            reco = reco->siguiente;
        } while (reco != raiz);
        
    }
    else{
        cout<<"No existen elementos en la lista"<<endl;
        string t;
        cin>>t;
    }
}
//////////////////////////////////////////////////////////////////////// EMPIEZA COLA //////////////////////////////////////////////////////////////////////////

class Cola {
private:
    class Nodo {
    public:
        Movimiento mov;
        Nodo *sig;
        
    };
    Nodo *raiz;
    Nodo *ultimo;
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
        cout<<"Ancho: "<<raiz->mov.ancho<<endl;
        cout<<"Alto: "<<raiz->mov.alto<<endl;
        do {
            cout<<"x: "<<reco->mov.mov_x<<" y: "<<reco->mov.mov_y<<endl;
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
            Movimiento *dato;
       
    };
    Nodo *cima;
    public:
    Pila();
    ~Pila();
    void push(Movimiento *mov);
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

void Pila::push(Movimiento *mov) {
    Nodo *nuevo = new Nodo();
    nuevo->dato = mov;
    if (cima == NULL) {
        cima = nuevo;
    }
    else{
        nuevo->abajo = cima;
        cima = nuevo;
    }
}

bool Pila::vacia(){
    if (cima == NULL)
        return true;
    else
        return false;
}

void Pila::imprimir(){
    if (!vacia()) {
        Nodo *reco = cima;
        do {
         //   cout<<reco->info  <<"-";     modificar
            reco = reco->abajo;
        } while (reco != NULL);
    }
}

void Pila::pop(){
    cima = cima->abajo;    
}


////////////////////////////////////////////////////////////////////////// FUNCIONES /////////////////////////////////////////////////////////////////////
void carga();

void limpiar();

void registrar();
//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 

void menu();

//variables globales
ListaCircular *l_usuarios = new ListaCircular();
Lista *l_articulos = new Lista(); 
Cola *c_tutorial = new Cola();



int main(int argc, char *argv[]) {
    menu();
    return 0;

}

void limpiar(){
    for(int i = 1 ; i<200;i++){
        cout<<" "<<endl;
    }
}

void carga(){
    
  
    //cout<<"Ingrese nombre del archivo: "<<endl;
    //string msg,t;
    //cin>>ws;
    //getline(cin,msg);
    //msg = msg +".json";
    fstream ofile("db_juego.json");
    string strjson;
    if (!ofile.is_open()) {
        cout<<"Imposible abrir ese archivo"<<endl;
        string t;
        cin>>t;
    }
    string strline;
    while (getline(ofile, strline)) {
        strjson += strline;
    }
    ofile.close();

    Json::Reader reader;  //  Reader 
    Json::Value root; 

    if (reader.parse(strjson, root)) {
  
    Json::Value to = root["usuarios"];
    int size = root["usuarios"].size();
    string t;
   
    for (int j = 0; j < size; j++){
        Usuario a;
        a.nick = to[j]["nick"].asString();
        a.moneda = to[j]["moneda"].asString();
        a.edad = to[j]["edad"].asString();
        a.password = to[j]["password"].asString();
        l_usuarios->insertarNodo(a);
    }
    to = root["articulos"];
    size = root["articulos"].size();
    for (int j = 0; j < size; j++){
        Articulo a;
        a.id = to[j]["id"].asString();
        a.categoria = to[j]["categoria"].asString();
        a.precio= to[j]["precio"].asString();
        a.nombre = to[j]["nombre"].asString();
        a.src = to[j]["src"].asString();
        l_articulos->insertar(a);
        
    } 
    to = root["tutorial"];
    size = root["tutorial"]["movimientos"].size();
    string alto = to["alto"].asString();
    string ancho = to["ancho"].asString();
    to = to["movimientos"];
    for (int j=0; j<size; j++ ){
        Movimiento moviento;
        moviento.alto = alto;
        moviento.ancho = ancho;
        moviento.mov_x = to[j]["x"].asString();
        moviento.mov_y = to[j]["y"].asString();
        c_tutorial->encolar(moviento);
    }  
  }

  
    


}


void registrar(){
    
    
    string nombre,pass,edad,t;
    cout<<"Ingrese nombre de usuario: ";
    cin>>ws;
    getline(cin,nombre);
    cout<<"Ingrese su contraseña: ";
    cin>>ws;
    getline(cin,pass);
    string nuevo = SHA256::cifrar(pass); 
    cout<<"Ingrese su edad: ";
    cin>>ws;
    getline(cin,edad);
    string moneda = "0";
    Usuario us ;
    us.password = nuevo;
    us.moneda = moneda;
    us.nick = nombre;
    us.edad = edad;
    l_usuarios->insertarNodo(us);
    l_usuarios->imprimir();
    cin>>t;


}

void menu(){
    int opcion=0;
    //color(hConsole, 10);
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
            registrar();
            limpiar();
            menu();
        break;
        case 3:
            cout<<"opcion2"<<endl;
        break;
        case 4:
            cout<<"opcion2"<<endl;
        break;
        case 5:
            //color(hConsole,9);
            cout<<"  Adios"<<endl;
            
        break;
        default:
        //color(hConsole,14);
        cout<<"Por favor ingrese una opcion valida"<<endl;
        string t;
        cin>>t;       
        limpiar();
        menu();
      
        

}

}
