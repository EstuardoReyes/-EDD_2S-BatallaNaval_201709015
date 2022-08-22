#include <iostream>
#include <fstream>
#include <string>
#include <jsoncpp/json/json.h>

using namespace std;
using namespace Json;

int main()
{
  fstream ofile("json.json");
  string strjson;
  if (!ofile.is_open()) {
    return 0;
  }
 
  string strline;
  while (getline(ofile, strline)) {
   strjson += strline;
  }
  
  ofile.close();
  
  Json::Reader reader;  //  Reader 
  Json::Value root;    //  The value of value can be any object
  
  if (reader.parse(strjson, root)) {
  
    int size = root.size();   //  Number of root nodes
  
    for (int j = 0; j < size; j++) {
      
      cout << root[j]["name"].asString() << endl;
 
      const Json::Value arrayObj = root[j]["lines"];
 
      for (int i = 0; i < arrayObj.size(); i++) {
 
        if (arrayObj[i].isMember("line")) {
          cout << arrayObj[i]["line"].asString() << endl;
        }
        if (arrayObj[i].isMember("cpp")) {
          cout << arrayObj[i]["cpp"].asString() << endl;
        }
        if (arrayObj[i].isMember("java")) {
          cout << arrayObj[i]["java"].asString() << endl;
        }
    
        int m = 0;
      }
    }
  }
 return 0;
}

