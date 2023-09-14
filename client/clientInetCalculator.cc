#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <unistd.h>

#define PORT 3000
#define IP_SERVER "127.0.0.1"

using namespace std;

struct operation {
        int value1;
        int value2;
        int oper;
        int result;
};
struct operation op;

int main() {
        int s0, s1;
        struct sockaddr_in server;
        int rval;

        s0=socket(AF_INET, SOCK_STREAM, 0);
        if (s0<0)
        {
                perror("opening stream socket");
                exit(1);
        }

        s1=socket(AF_INET, SOCK_STREAM, 0);
        if (s1<0)
        {
                perror("opening stream socket");
                exit(1);
        }

        //Server Connection
        bzero(&server, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons (PORT);
        server.sin_addr.s_addr = inet_addr(IP_SERVER); 
        if (connect(s0, (struct sockaddr *) &server, sizeof(server)) < 0 ) {
                perror("connectando stream socket 0");
                exit(0);
        }

        if (connect(s1, (struct sockaddr *) &server, sizeof(server)) < 0 ) {
                perror("connectando stream socket 1");
                exit(0);
        }

        cout << "Digite o Primeiro Valor "<< endl;
        cin >> op.value1;
        cout << "Digite o Segundo Valor "<< endl;
        cin >> op.value2;
        cout << "Digite 1 para somar "<< endl;
        cout << "Digite 2 para subtrair "<< endl;
        cout << "Digite 3 para multiplicar "<< endl;
        cout << "Digite 4 para dividir "<< endl;
        cin >> op.oper;
        cout << "Solicitando servico ao servidor "<< endl;
        rval = send(s0, &op, sizeof(struct operation), 0);
        cout << "Recebido resultado do servidor "<< endl;
        rval = recv(s1, &op, sizeof(struct operation), 0);

        switch (op.oper) {
                case 1:
                        cout << op.value1 << "  +  " << op.value2 << " = " << op.result << endl;
                break;

                case 2:
                        cout << op.value1 << "  -  " << op.value2 << " = " << op.result << endl;
                break;

                case 3:
                        cout << op.value1 << "  *  " << op.value2 << " = " << op.result << endl;
                break;

                case 4:
                        cout << op.value1 << "  /  " << op.value2 << " = " << op.result << endl;
                break;
        }
        close (s0);
        close (s1);
}