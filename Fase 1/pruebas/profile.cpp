#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>


using namespace std;

int main(){
    ifstream ifs("profile.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj);
    cout<<"Last name: "<<obj["lastname"].asString()<<endl;
    cout<<"Firts name: "<<obj["firstname"].asString()<<endl;
    return 0;
}
