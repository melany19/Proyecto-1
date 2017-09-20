//
// Created by melany on 20/09/17.
//

#ifndef REMOTE_MEMORY_RMLIB_H
#define REMOTE_MEMORY_RMLIB_H

#endif //REMOTE_MEMORY_RMLIB_H

#include <string.h>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <strings.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
#include <arpa/inet.h>
using namespace std;

void init (char* argv[])
{
    int Client, port, portHA;
    bool loop = false;
    struct sockaddr_in svrAdd;
    struct hostent *server;
    struct hostent *serverHA;

    //Obtiene los puertos
    port = atoi(argv[1]);  // Convierte un puntero de caracteres en puntero
    portHA = atoi(argv[3]);

    if((port > 65535) || (port < 2000))
    {
        cerr<<"Please enter port number between 2000 - 65535"<<endl;
        exit;
    }

    //crea cliente
    Client = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(Client < 0)
    {
        cerr << "Cannot open socket" << endl;
        exit;
    }

    //Obtiene las ip
    server = gethostbyname(argv[0]);
    serverHA = gethostbyname(argv[2]);

    if(server == NULL)
    {
        cerr << "La IP esta incorrecta" << endl;
        exit;
    }

    if(serverHA == NULL)
    {
        cerr << "La IP esta incorrecta" << endl;
        exit;
    }


    svrAdd.sin_family = AF_INET;
    svrAdd.sin_addr.s_addr = inet_addr(argv[0]);
    svrAdd.sin_port = htons(port);


    int verificar = connect(Client,(struct sockaddr *) &svrAdd, sizeof(svrAdd));
    for (int i=0; i<2; i++){
        if (verificar < 0)
        {
            cerr << "No conectó" << endl;


            if (i==1){
                cerr << "No hay servidores" << endl;
                break;
            }
            svrAdd.sin_addr.s_addr = inet_addr(argv[2]);
            svrAdd.sin_port = htons(portHA);
            int checker = connect(Client,(struct sockaddr *) &svrAdd, sizeof(svrAdd));

        }
        else {
            cerr << "Conectó" << endl;
            break;
        }
    }



    //send stuff to server
    for(;;)
    {
        char s[300];
        //cin.clear();
        //cin.ignore(256, '\n');
        cout << "Enter stuff: ";
        bzero(s, 301);
        cin.getline(s, 300);

        write(Client, s, strlen(s));
    }
}