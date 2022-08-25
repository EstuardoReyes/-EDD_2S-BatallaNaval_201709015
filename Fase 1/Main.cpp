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
                Usuario us;
        };
        Nodo *raiz;
       
    public:
        Lista();
        ~Lista();
        void insertarNodo(Articulo articulo);
        void insertar(Articulo articulo);
        bool vacia();
        void insertarUsuario(Usuario us);
        void ordenar();
        void imprimir(); 
};

void Lista::ordenar(){
    cout<<"Usuarios ordenados por edad ascendentes"<<endl;
    
}

void Lista::insertarUsuario(Usuario us){
    Nodo *nuevo = new Nodo();
    nuevo->us = us;
    if (raiz == NULL){
        raiz = nuevo;
        nuevo->us = us;
    }
    else{
        Nodo *reco = raiz;
       
        while (reco->siguiente != NULL){
            reco = reco->siguiente;
        }
        reco->siguiente = nuevo;
        nuevo->siguiente = NULL;
        nuevo->us = us;
    }
}

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
        int numero = 1;
        cout<<"#     ID           CATEGORIA                         NOMBRE                              PRECIO"<<endl;
        do {
            Nodo *aux = reco->lista->raiz;
            
            while(aux != NULL ){
                int i=13;
                int nu=5;
                
                  int cat = 34;
                    int nom = 36;

                cout<<numero<<":";
               
                if(numero <10){
                for(int e = 0; e<4;e++){
                    cout<<" ";
                }}
                else{
                    for(int e = 0; e<3;e++){
                    cout<<" ";
                }}


                cout<<aux->articulo.id;
                i = i - aux->articulo.id.length();
                for(int e = 0; e<i;e++){
                    cout<<" ";
                }
                cout<<aux->articulo.categoria;
                cat = cat - aux->articulo.categoria.length();
                for(int e = 0; e<cat;e++){
                    cout<<" ";
                }
                cout<<aux->articulo.nombre;
                nom = nom - aux->articulo.nombre.length();
                for(int e = 0; e<nom;e++){
                    cout<<" ";
                }
                cout<<"Q."<<aux->articulo.precio<<endl;
                
                
                
                numero = numero + 1;
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
        bool buscar(string nombre);
        void eliminar(Usuario usuario);
        Usuario obtener(string nick, string pass);
        Usuario getRaiz();
        void ordenar();

        
    
};

void ListaCircular::ordenar(){
   
    Nodo *reco = raiz;
    Lista *listaSimple = new Lista();
    do{
        listaSimple->insertarUsuario(reco->dato);
        reco = reco->siguiente;
    }while(reco != raiz);
    listaSimple->ordenar();


  
  }

string ListaCircular::getRaiz(){
    string lista = "";
    Nodo *reco;
    reco = raiz;
    int i = 1;
    do{
        lista = "n"<<i<<"[label="<<reco->dato.nick<<"];"
        i = i + 1;
        reco = reco->siguiente;
        }while(reco != raiz);
   

    return lista;
}

void ListaCircular::eliminar(Usuario usuario){
    Nodo *reco;
    reco = raiz;
        do{
        if (reco->dato.nick == usuario.nick){
        reco->anterior->siguiente = reco->siguiente;
        reco->siguiente->anterior = reco->anterior;
        delete reco;
        break;}
        reco = reco->siguiente;
        }while(reco != raiz);
    
}


Usuario ListaCircular::obtener(string nick, string pass){
    Nodo *reco;
    Usuario regreso;
    reco = raiz;
    bool bandera=false;
     do{
        if (reco->dato.nick == nick){
            if (reco->dato.password == SHA256::cifrar(pass)){
                cout<<"pasao"<<endl;
                return reco->dato;
              
            }
            else{
                bandera = true;
                cout<<"contraseña incorrecta"<<endl;
           }
        }
        reco = reco->siguiente;
        }while (reco != raiz);
        if (bandera == false){
        cout<<"Usuario no registrado"<<endl;
        }
        regreso.nick = "no";
        return regreso;


}

bool ListaCircular::buscar(string nombre){
    if(raiz == NULL){
        return false;
    }
    else{
        Nodo *reco = raiz;
        do{
            if (reco->dato.nick == nombre){
                return true;
            }
            reco = reco->siguiente;
        }while (reco != raiz);
        return false;
    }
}

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
        Movimiento getRaiz();
};

Movimiento Cola::getRaiz(){
    return raiz->mov;
}

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
        cout<<"    Ancho: "<<raiz->mov.ancho<<endl;
        cout<<"    Alto: "<<raiz->mov.alto<<endl;
        cout<<"    Movimientos:"<<endl;
        do {
            cout<<"              x:"<<reco->mov.mov_x<<" y:"<<reco->mov.mov_y<<endl;
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

void editar();

void registrar();
//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 

void menu();

void login();

void reporte();
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
    bool verificar = true;
    while(verificar == true){
    cout<<"Ingrese nombre de usuario: ";
    cin>>ws;
    getline(cin,nombre);
    verificar = l_usuarios->buscar(nombre);
    if(verificar == true){
        cout<<"Nombre de usuario ya en uso ingrese uno nuevo: "<<endl;
        cin>>t;
        limpiar();
    }
    }
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

void login(){
    Usuario pa;
    string nombre,pass,t;
        do{
        limpiar();
        cout<<"Ingrese nombre de usuario: ";
        cin>>ws;
        getline(cin,nombre);
        cout<<"Ingrese su contraseña: ";
        cin>>ws;
        getline(cin,pass);
        pa = l_usuarios->obtener(nombre,pass);
        }while(pa.nick == "no");

    limpiar();


    int opcion=0;
    //color(hConsole, 10);
    bool salir = false;
    while(salir == false){
    cout<<"Usuario: "<<pa.nick<<endl;
    cout<<endl;
    cout<<"              Login              "<<endl;
    cout<<"********************************"<<endl;
    cout<<"*  1. Editar informacion       *"<<endl;
    cout<<"*  2. Eliminar cuenta          *"<<endl;
    cout<<"*  3. Ver tutorial             *"<<endl;
    cout<<"*  4. Ver articulos de tienda  *"<<endl;
    cout<<"*  5. Reaizar movimientos      *"<<endl;
    cout<<"*  6. Regresar a menu          *"<<endl;
    cout<<"********************************"<<endl;
    cout<<"  Ingrese una opcion: ";
    cin>>opcion;
    switch(opcion) {
        case 1:{
            cout<<"Seleccione la informacion que desea editar"<<endl;
            cout<<"  1. Nick:       "<<endl;
            cout<<"  2. Contraseña  "<<endl;
            cout<<"  3. edad:       "<<endl;
            cin>>opcion;
            switch(opcion){
                case 1:
                 do{
                    cout<<"Ingrese nombre de usuario: ";
                    cin>>ws;
                    getline(cin,nombre);
                    pa = l_usuarios->obtener(nombre,pass);
                 }while(pa.nick != "no");
                pa.nick = nombre;
                cout<<"cambio efectuado correctamente"<<endl;
                cin>>t;
                break;
                case 2:
                    cout<<"Ingrese su nueva contraseña: ";
                    cin>>ws;
                    getline(cin,pass);
                    pa.password= SHA256::cifrar(pass);
                    cout<<"cambio efectuado correctamente"<<endl;
                    cin>>t;
                break;
                case 3:
                    string edad;
                    cout<<"Ingrese su nueva edad: ";
                    cin>>ws;
                    getline(cin,edad);
                    pa.edad = edad;
                    cout<<"cambio efectuado correctamente"<<endl;
                break;
            }
            limpiar();}
        break;
        case 2://aqui es para eliminar el usuario
            {char pregunta;
            limpiar();
            cout<<"Esta seguro de eliminar su usuario? (s/n)"<<endl;
            cin>>pregunta;
            if (pregunta == 's'){
                l_usuarios->eliminar(pa);
                salir = true;
                menu();
            }}
        break;
        case 3:{
            limpiar();
            Movimiento aux;
            aux = c_tutorial->getRaiz();
            cout<<"Tutorial:"<<endl<<endl<<endl;
            cout<<"   Tablero:"<<endl;
            c_tutorial->imprimir();
            cin>>t;}
        break;
        case 4:{
            l_articulos->imprimir();
            cout<<" Ingrese el articulo que desea comprar: ";
            cin>>t;}
        break;
        case 5:{
            limpiar();
           cin>>t;
        }
        break;
        case 6:
          {
            salir = true;
            limpiar();
            menu();}
        break;
        default:
        cout<<"Por favor ingrese una opcion valida: ";
        string t;
        cin>>t;   
          
    }
    }
}

void reporte(){
    ////////imagen de listaa circular
    string lista;
    lista = "digraph g{ 
	ranksep=0.5;node[shape=box, fontname="Arial"];";
    string list = l_usuarios.get();


    cout<<"Lista de Usuarios:"<<endl;
    l_usuarios.ordenar();
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
            registrar();
            limpiar();
            menu();
        break;
        case 3:
            login();
            limpiar();
            menu();
        break;
        case 4:
            reporte();
            limpiar();
            menu();
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
