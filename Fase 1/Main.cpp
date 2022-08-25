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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
        void ordenarArticulos();
        void imprimir(); 
};


void Lista::ordenar(){
    cout<<"Usuarios ordenados por edad ascendentes"<<endl;
    Nodo *actual, *siguiente, *reco;
    actual = raiz;
    reco = raiz;
    Usuario t;
    int r;
   
    //ordenamiento burbuja ascendente
    while(actual->siguiente != NULL)
     {
          siguiente = actual->siguiente;
          
          while(siguiente!=NULL)
          {
               if(stoi(actual->us.edad) > stoi(siguiente->us.edad))
               {
                    t = siguiente->us;
                    siguiente->us = actual->us;
                    actual->us = t;          
               }
               siguiente = siguiente->siguiente;                    
          }    
          actual = actual->siguiente;
          siguiente = actual->siguiente;
           
     }
     while(reco != NULL){
        cout<<"edad:"<<reco->us.edad<<"   usuario: "<<reco->us.nick<<endl;    
        reco = reco->siguiente;
     }cout<<endl;
    //ordenamiento burbuja descendente
     cout<<"Usuarios ordenados por edad descendentes"<<endl;

     actual = raiz;
    
      while(actual->siguiente != NULL)
     {
          siguiente = actual->siguiente;
          
          while(siguiente!=NULL)
          {
               if(stoi(actual->us.edad) < stoi(siguiente->us.edad))
               {
                    t = siguiente->us;
                    siguiente->us = actual->us;
                    actual->us = t;          
               }
               siguiente = siguiente->siguiente;                    
          }    
          actual = actual->siguiente;
          siguiente = actual->siguiente;
           
     }
     reco = raiz;
     while(reco != NULL){
        cout<<"edad:"<<reco->us.edad<<"   usuario: "<<reco->us.nick<<endl;    
        reco = reco->siguiente;  
     }
}

void Lista::ordenarArticulos(){
    Lista *listaSimple = new Lista();
    if (!vacia()) {
        Nodo *reco = raiz;
        do {
            Nodo *aux = reco->lista->raiz;
            
            while(aux != NULL ){//AQUI VA A RECOGER TODOS LOS ELEMENTOS DE LA LISTA DE ARTICULOS Y LO COLOCARA EN UNA SIMPLE
                listaSimple->insertarNodo(aux->articulo);
                aux = aux->siguiente;
            }
            reco = reco->siguiente;
        } while (reco->siguiente != NULL);
    }
    else{
        cout<<"No existen elementos en la lista"<<endl;
       
    }
   //ahora teniendo todos los elementos en la lista los vamos a aordenar
 cout<<"Articulos ordenados por precio ascendentes"<<endl;
    Nodo *actual, *siguiente, *reco;
    actual = listaSimple->raiz;
    reco = listaSimple->raiz;
    Articulo t;
    int r;
   
    //ordenamiento burbuja ascendente
    while(actual->siguiente != NULL)
     {
          siguiente = actual->siguiente;
          
          while(siguiente!=NULL)
          {
               if(stoi(actual->articulo.precio) > stoi(siguiente->articulo.precio))
               {
                    t = siguiente->articulo;
                    siguiente->articulo = actual->articulo;
                    actual->articulo = t;          
               }
               siguiente = siguiente->siguiente;                    
          }    
          actual = actual->siguiente;
          siguiente = actual->siguiente;
           
     }
     while(reco != NULL){
        cout<<"Preio:   Q"<<reco->articulo.precio<<"   Articulo: "<<reco->articulo.nombre<<endl;    
        reco = reco->siguiente;
     }cout<<endl;
    //ordenamiento burbuja descendente
     cout<<"Articulos ordenados por precio descendentes"<<endl;

     actual = listaSimple->raiz;
    
      while(actual->siguiente != NULL)
     {
          siguiente = actual->siguiente;
          
          while(siguiente!=NULL)
          {
               if(stoi(actual->articulo.precio) < stoi(siguiente->articulo.precio))
               {
                    t = siguiente->articulo;
                    siguiente->articulo = actual->articulo;
                    actual->articulo = t;          
               }
               siguiente = siguiente->siguiente;                    
          }    
          actual = actual->siguiente;
          siguiente = actual->siguiente;
           
     }
     reco = listaSimple->raiz;
     while(reco != NULL){
        cout<<"Precio:  Q"<<reco->articulo.precio<<"   Articulo: "<<reco->articulo.nombre<<endl;    
        reco = reco->siguiente;  
     }
 



}

void Lista::insertarUsuario(Usuario us){
    Nodo *nuevo = new Nodo();
    nuevo->us = us;
    if (raiz == NULL){
        raiz = nuevo;
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
        cout<<"#     ID                                      CATEGORIA                                       NOMBRE                              PRECIO"<<endl;
        do {
            Nodo *aux = reco->lista->raiz;
            
            while(aux != NULL ){
                int i=40;
                int nu=5;
                
                  int cat = 48;
                    int nom = 36;

                cout<<numero<<":";
               
                if(numero <10){
                for(int e = 0; e<4;e++){
                    cout<<" ";
                }}
                if(numero>9 and numero <100){
                    for(int e = 0; e<3;e++){
                    cout<<" ";
                }}
                if(numero>99){
                     for(int e = 0; e<2;e++){
                    cout<<" ";
                }
                }
                


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
        void ordenar();

        
    
};

void ListaCircular::ordenar(){
   string t;
    Nodo *reco = raiz;
    Lista *listaSimple = new Lista();
    do{
        listaSimple->insertarUsuario(reco->dato);
        reco = reco->siguiente;
    }while(reco != raiz);
    listaSimple->ordenar();
    cin>>t;


  
  }

void ListaCircular::eliminar(Usuario usuario){
    Nodo *reco;
    reco = raiz;
        if (usuario.nick == raiz->dato.nick){

            reco->anterior->siguiente = reco->siguiente;
            reco->siguiente->anterior = reco->anterior;
            raiz = reco->siguiente;
            delete reco;
        }
        else{
        do{
        if (reco->dato.nick == usuario.nick){
        reco->anterior->siguiente = reco->siguiente;
        reco->siguiente->anterior = reco->anterior;
        delete reco;
        break;}
        reco = reco->siguiente;
        }while(reco != raiz);
    
}}

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
            Movimiento dato;
       
    };
    Nodo *cima;
    public:
    Pila();
    ~Pila();
    void push(Movimiento mov);
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

void Pila::push(Movimiento mov) {
   
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
            cout<<"x: "<<reco->dato.mov_x<<" y: "<<reco->dato.mov_y<<endl;
            reco = reco->abajo;
        } while (reco != NULL);
    }
}

void Pila::pop(){
    cima = cima->abajo;    
}


////////////////////////////////////////////////////////////////////////// FUNCIONES /////////////////////////////////////////////////////////////////////

class ListaPilas{
    private:
        class Nodo{
            public: 
                Nodo *siguiente;
                Pila *pila;
              
        };
        Nodo *raiz;
       
    public:
        ListaPilas();
        ~ListaPilas();
        bool vacia();
        void imprimir(); 
        void insertarPila(Pila *pila);
};

void ListaPilas::insertarPila(Pila *pil){
    Nodo *nuevo = new Nodo();
    nuevo->pila = pil;
    if (raiz == NULL){
        raiz = nuevo;

    }
    else{
        Nodo *reco = raiz;
        while (reco->siguiente != NULL){
            reco = reco->siguiente;
        }
        reco->siguiente = nuevo;
        nuevo->siguiente = NULL;
    }
}




ListaPilas::ListaPilas(){
    raiz = NULL;
}

ListaPilas::~ListaPilas()     //sirve para destruir la lista circular con todos sus nodos
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

bool ListaPilas::vacia()
{
    if (raiz == NULL)
        return true;
    else
        return false;
}

void ListaPilas::imprimir()    /// esto  quiere revisar
{
   
}











//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
ListaPilas *l_pila = new ListaPilas();



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
    fstream ofile("f1_masiva.json");
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
        a.moneda = to[j]["monedas"].asString();
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
    cout<<"Usuario: "<<pa.nick<<"   Tokens: "<<pa.moneda<<endl;
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
                l_usuarios->eliminar(pa); //revision
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
        case 5:{ //realizar movimientos
            Pila *pila = new Pila();
            int opc=0;
            bool bandera = true;
            int numeroPartidas = 5 + rand() % (11 - 5) ; //selecciona un numero aleatorio de jugadas para determinar el ganador
            while(numeroPartidas != 0){
                limpiar();
                 cout<<"Seleccionee una opcion"<<endl;
                cout<<"  1. Ingresar jugada:       "<<endl;
                cout<<"  2. Detroceder jugada  "<<endl;
                cout<<"  3. Abandonar       "<<endl;
                cin>>opc;
                switch (opc)
                {
                case 1:{
                    string x1,y1;
                    Movimiento mov;
                    cout<<"Ingrese X: ";
                    cin>>ws;
                    getline(cin,x1);
                    cout<<"Ingrese Y: ";
                    cin>>ws;
                    getline(cin,y1);
                    mov.mov_x = x1;
                    mov.mov_y = y1;
                    pila->push(mov);
                    numeroPartidas = numeroPartidas -1;}
                break;
                case 2:{
                    pila->pop();
                    numeroPartidas = numeroPartidas + 1;}
                    break;
                case 3:{
                    cout<<"partida perdida"<<endl;
                    bandera = false;
                    l_pila->insertarPila(pila);
                    numeroPartidas = 0;
                break;
                }
                }
            }
            if(bandera == true){
                cout<<"Felicidades ganas 100 tokens"<<endl;
                l_pila->insertarPila(pila);
                int monto = stoi(pa.moneda) + 100;
                pa.moneda = to_string(monto);
            }
            //revisar
            







            
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
   
    string t;
    cout<<"Lista de Usuarios:"<<endl;
    l_usuarios->ordenar();
    cout<<endl<<"Lista de Articulos "<<endl;
    l_articulos->ordenarArticulos();
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
