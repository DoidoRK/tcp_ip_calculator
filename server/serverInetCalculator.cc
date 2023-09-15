#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

#define PORT 3000
using namespace std;

struct operation {
        int value1;
        int value2;
        int oper;
        int result;
};

struct operation op;
int main()
{       
        int sock, length;
        struct sockaddr_in server;
        int rval, i, s0, s1;
        char c;

        /* Create socket. */            

        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {  
                perror("opening stream socket");
                exit(1);
        }   

        bzero(&server, sizeof(server));                       
        server.sin_family = AF_INET; 
        server.sin_addr.s_addr = INADDR_ANY; 
        server.sin_port = htons(PORT);
        length = sizeof(server);
        if (bind(sock, (struct sockaddr *)&server, length) < 0){
                perror("binding stream socket");
                exit(0);
        }

        /*Waits for connections */
        listen(sock,5);
        while (1) {
                cout << "Servidor aguardando!! "<< endl;
                s0 = accept(sock,(struct sockaddr *)0,(socklen_t *)0);
                rval = recv(s0, &op, sizeof(struct operation), 0);  
                s1 = accept(sock,(struct sockaddr *)0,(socklen_t *)0);
                cout << "Pedido recebido!! "<< endl;
                switch (op.oper) {
                        case 1:
                                op.result = op.value1 + op.value2;
                        break;
                        case 2:
                                op.result = op.value1 - op.value2;
                        break;
                        case 3:
                                op.result = op.value1 * op.value2;
                        break;
                        case 4: 
                                op.result = op.value1 / op.value2;
                        break;
                }
                rval = send(s1, &op, sizeof(struct operation), 0);  
                cout << "Resultado enviado!! "<< endl;
        }
        close (s0);
        close (s1);
}