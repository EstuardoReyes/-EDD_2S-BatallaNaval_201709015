#include <iostream>
#include <fstream>
#include <string>
#include <System.JSON.hpp>
 
using namespace std;

int main()
{

  unique_ptr<TStringStream> jsonStream(new TStringStream);
  jsonStream->LoadFromFile("addressBook.json");

  TJSONObject* jsonFile = (TJSONObject*)TJSONObject::ParseJSONValue(jsonStream->DataString);

  TJSONArray* contactArray = (TJSONArray*)TJSONObject::ParseJSONValue(jsonFile->GetValue("addressBook.json"));

  

}