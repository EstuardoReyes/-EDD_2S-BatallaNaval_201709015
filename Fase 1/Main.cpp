#include <iostream>
#include <windows.h>
#include <conio.h>
#include "nlohmann/json.hpp"
#include <fstream>


#define color SetConsoleTextAttribute

using namespace std;
using json = nlohmann::json;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 

void limpiar(){
    for(int i = 1 ; i<200;i++){
        cout<<" "<<endl;
    }
}

void carga(){
    ifstream dict_json1_read("db_juego.json");
    json dict_json1 = json::parse(dict_json1_read);

    cout<<dict_json1;
    getch();

}

void menu(){
    int numero=0;
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
    cin>>numero;
    switch(numero) {
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