#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
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
        bool buscar(string categoria);
        Lista buscarNodo(string categoria);
};

Lista::Lista(){
    raiz = NULL;
}

bool Lista::buscar(string categoria){
    Nodo *reco = raiz;
    do {
        if (reco->categoria == categoria){
            return true;
        }
        reco = reco->siguiente;
    } while (reco != raiz);
    return false;
    
}

Lista Lista::buscarNodo(string categoria){
    Nodo *reco = raiz;
    Lista gas;
    do {
        if (reco->categoria == categoria){
            gas = *reco->lista;
            return gas;
        }
        reco = reco->siguiente;
    } while (reco != raiz);

    return gas;
    
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
       
        while (reco->siguiente != raiz){
            reco = reco->siguiente;
        }
        reco->siguiente = nuevo;
        nuevo->siguiente = NULL;
        nuevo->articulo = articulo;
    }
   
   
}
/*sirve para insertar las cabezas pricipañes en la lista principañ de objetos*/
void Lista::insertar(Articulo articulo) {
    cout<<"entro"<<endl;
    Nodo *nuevo = new Nodo();
    if (raiz == NULL){
        raiz = nuevo;
        raiz->categoria=articulo.categoria;
        Lista *lis = new Lista();
        raiz->lista = lis;
        raiz->siguiente = NULL;
        raiz->lista->insertarNodo(articulo);
    }
    else{
        
        if (buscar(articulo.categoria) == true){
          
            Lista lisaux = buscarNodo(articulo.categoria);
            lisaux.insertarNodo(articulo);
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
            cout<<reco->categoria<<endl;
            reco = reco->siguiente;
        } while (reco->siguiente != raiz);
        
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
        string ancho;
        string alto;
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

//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 

void menu();

//variables globales
ListaCircular *l_usuarios = new ListaCircular();
Lista *l_articulos = new Lista(); 



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
  
    
    //cout<<root["usuarios"];
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
        cout<<"se ingreso objeto: "<<a.categoria<<endl;
    }
    l_usuarios->imprimir();
  
  }

  
    


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
            cout<<"opcion2"<<endl;
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
