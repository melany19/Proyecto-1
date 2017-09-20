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
#include "list.h"

using namespace std;

void *task1(void *);

static int connFd;

int main()
{
    int port = 8088, verificar;
    socklen_t len; //store size of the address
    //bool loop = false;
    struct sockaddr_in svrAdd, clntAdd;

    pthread_t threadA[3];

    //crea el socket
    verificar = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(verificar < 0)
    {
        cerr << "Cannot open socket" << endl;
        return 0;
    }


    svrAdd.sin_family = AF_INET;
    svrAdd.sin_addr.s_addr = INADDR_ANY;
    svrAdd.sin_port = htons(port);

    //bind socket
    if(bind(verificar, (sockaddr*)&svrAdd, sizeof(svrAdd)) < 0)
    {
        cerr << "Cannot bind" << endl;
        return 0;
    }

    listen(verificar, 5);

    len = sizeof(clntAdd);

    int noThread = 0;

    while (noThread < 3)
    {
        socklen_t len = sizeof(clntAdd);

        cout << "Listening" << endl;

        //this is where client connects. svr will hang in this mode until client conn
        connFd = accept(verificar, (struct sockaddr *)&clntAdd, &len);

        if (connFd < 0)
        {
            cerr << "Cannot accept connection" << endl;
            return 0;
        }
        else
        {
            cout << "Connection successful" << endl;
        }

        pthread_create(&threadA[noThread], NULL, task1, NULL);

        noThread++;
    }

    for(int i = 0; i < 3; i++)
    {
        pthread_join(threadA[i], NULL);
    }


}

void *task1 (void *dummyPt)
{
    cout << "Thread No: " << pthread_self() << endl;
    char test[300];
    bzero(test, 301);
    bool loop = false;
    while(!loop)
    {
        bzero(test, 301);


        read(connFd, test, 300);

        string tester (test);
        cout << tester << endl;


        if(tester == "exit")
            break;
    }
    cout << "\nClosing thread and conn" << endl;
    close(connFd);
}
