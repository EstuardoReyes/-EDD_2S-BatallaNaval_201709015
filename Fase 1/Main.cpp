#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <string.h>
#include "recursos/sha256.h"
#include "recursos/JSON.hpp"
#include "clases/lista_circular.h"

#define color SetConsoleTextAttribute

using namespace std;
using JSON = dnc::JSON;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 

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
    Lista lista;
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

int main() {
    menu();
    return 0;

}