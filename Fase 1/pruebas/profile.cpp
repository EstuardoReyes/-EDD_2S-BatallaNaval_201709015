#include <iostream>
#include <fstream>
#include <graphviz/gvc.h>


using namespace std;


bool saveImageGV(string file_path){
    GVC_t *gvc;
    Agraph_t *g;
    FILE *fp;
    gvc = gvContext();
    fp = fopen((file_path+".dot").c_str(), "r");
    g = agread(fp, 0);
    gvLayout(gvc, g, "dot");
    gvRender(gvc, g, "png", fopen((file_path+".png").c_str(), "w"));
    gvFreeLayout(gvc, g);
    agclose(g);
    return (gvFreeContext(gvc));
}


int main(){
    bool hola;
    hola = saveImageGV("prueba");
    return 0;
}
