#include <iostream>
#include "rmlib.h"

int main() {

    char * valores[4]= {"192.168.0.30", "8080", "192.168.0.106", "8083"};
    rm_init(valores);


    int xd = 23;
    void* ptr = &xd;
    rm_new("melany", ptr, 8);


    return 0;


}