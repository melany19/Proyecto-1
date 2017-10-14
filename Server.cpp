//
// Created by melany on 20/09/17.
//
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <strings.h>
#include <stdlib.h>
#include <string>
#include <pthread.h>
#include "node.h"
#include "List.h"
#include "Memory.cpp"
#include <pthread.h>


using namespace std;

void *task1(void *);

static int SocketClient;

char* get_key(char paquete[],ssize_t size);
int get_value(char paquete[], ssize_t size);
int get_value_size(char paquete[], ssize_t size);

Memory Memoria = Memory();


int main()
{
    //get_value_size("n&melany&23&8&", 13);
    int tipo, port, portHA, portActivo;
    string ipActivo;

    cout << "Indique el tipo de servidor: " << "\n" << "1 : Activo" << "\n" << "2 : Pasivo" << endl;
    cin >> tipo;

    if (tipo == 1){

        cout << "Indique el puerto del servidor activo: " << endl;
        cin >> port;

    } else if(tipo == 2) {
        cout << "Indique el puerto del servidor pasivo: " << endl;
        cin >> portHA;

        cout << "Indique la ip del servidor activo: " << endl;
        cin >> ipActivo;

        cout << "Indique el puerto del servidor activo: " << endl;
        cin >> portActivo;

        //sincronizarServers(portHA, ipActivo, portActivo);
        port = portHA;
    }else {
        cout << "Servidor incorrecto " << endl;
        return 0;
    }

    int  Socket;
    socklen_t len; //store size of the address
    //bool loop = false;
    struct sockaddr_in ServerAdd, ClientAdd;

    //Hilos
    pthread_t threadA[3];  //Máximo de hilos

    //crea el socket
    Socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //Dominio, flujo, protocolo

    if(Socket < 0)
    {
        cerr << "Error al abrir el socket" << endl;
        return 0;
    }


    ServerAdd.sin_family = AF_INET;  //Dominio
    ServerAdd.sin_addr.s_addr = INADDR_ANY;
    ServerAdd.sin_port = htons(port);  //Puerto a conectar

    //enlazar socket
    if(bind(Socket, (sockaddr*)&ServerAdd, sizeof(ServerAdd)) < 0)
    {
        cerr << "No se pudo conectar" << endl;
        return 0;
    }

    listen(Socket, 5);

    len = sizeof(ClientAdd);

    int noThread = 0;

    while (noThread < 3)
    {
        socklen_t len = sizeof(ClientAdd);

        if (port==portHA){
            cout << "Servidor pasivo escuchando " << endl;
        }else{
            cout << "Servidor activo escuchando " << endl;
        }



        //this is where client connects. svr will hang in this mode until client conn
        SocketClient = accept(Socket, (struct sockaddr *)&ClientAdd, &len);

        if (SocketClient < 0)
        {
            cerr << "No se aceptó la conexión" << endl;
            return 0;
        }
        else
        {
            cout << "Conexión exitosa" << endl;
        }

        pthread_create(&threadA[noThread], NULL, task1, NULL);

        noThread++;
    }

    for(int i = 0; i < 3; i++)
    {
        pthread_join(threadA[i], NULL);
    }


}

void *task1 (void *dummyPt) {
    cout << "Thread No: " << pthread_self() << endl;
    char test[100];
    //bzero(test, 301);
    bool loop = false;
    while (!loop) {
        //bzero(test, 301);


        ssize_t size = read(SocketClient, test, 100);

        string tester(test);
        if (test[0] == 'n'){
            Memoria.RAM.add_end(get_key(test,size),get_value(test,size), get_value_size(test,size));
            Memoria.RAM.print();
            cout << get_key(test,size)<< endl;
            cout << get_value(test,size) << endl;
            cout<< get_value_size(test,size) << endl;

        } else if (test[0]== 'o'){

        }
        cout << tester << endl;


        if (tester == "exit")
            break;
    }
    cout << "\nClosing thread and conn" << endl;
    close(SocketClient);
}


char* get_key(char paquete[], ssize_t size){
    string a(paquete);
    int menor, mayor, auxiliar=0;
    //cout<< size << endl;
    for (int i=0; i< size-1;i++){
        if (paquete[i]=='&'){
            auxiliar+=1;
            if (auxiliar==1){
                menor=i+1;

            }else if(auxiliar==2){
                mayor=i;
                break;
            }

        }

    }

    char* key = (char*)a.substr(menor, mayor-menor).c_str();
    return key;
    cout << key << endl;
}



int get_value(char paquete[], ssize_t size){
    string a(paquete);
    int menor, mayor, auxiliar=0;
    //cout<< size << endl;
    for (int i=0; i< size-1;i++){
        if (paquete[i]=='&'){
            auxiliar+=1;
            if (auxiliar==2){
                menor=i+1;

            }else if(auxiliar==3){
                mayor=i;
                break;
            }

        }

    }

    char* value_aux = (char*)a.substr(menor, mayor-menor).c_str();
    int value = atoi(value_aux);
    return value;
    //cout << value << endl;
}

int get_value_size(char paquete[], ssize_t size){
    string a(paquete);
    int menor, mayor, auxiliar=0;
    //cout<< size << endl;
    for (int i=0; i< size-1;i++){
        if (paquete[i]=='&'){
            auxiliar+=1;
            if (auxiliar==3){
                menor=i+1;

            }else if(auxiliar==4){
                mayor=i;
                break;
            }

        }

    }

    char* value_size_aux = (char*)a.substr(menor, mayor-menor).c_str();
    int value_size = atoi(value_size_aux);
    return value_size;

    //cout << value_size << endl;
}






//void insertarMemoria(String);


