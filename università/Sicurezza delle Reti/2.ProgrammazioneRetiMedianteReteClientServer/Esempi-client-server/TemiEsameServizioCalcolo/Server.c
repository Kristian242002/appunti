#include "network.h"

typedef struct {
    int num1;
    int num2;
    char op;
} request_t;

int main(void) {
    socketif_t sockfd;
    request_t request;
    int response;
    char host[MAXADDRESSLEN];
    int port;

    sockfd = createUDPInterface(35000);

    if (sockfd < 0) {
        printf("[SERVER] Errore di creazione del socket: %i\n", sockfd);
    } else {
        printf("[SERVER] In attesa di richieste UDP sulla porta 35000...\n");

        while (1) {
            UDPReceive(sockfd, &request, sizeof(request), host, &port);

            if (request.op == 'e') {
                printf("[SERVER] Il client %s:%d ha richiesto la chiusura\n", host, port);
                break;
            }

            printf("[SERVER] Ricevuto da %s:%d -> %d %c %d\n", host, port, request.num1, request.op, request.num2);

            if (request.op == '+')
                response = request.num1 + request.num2;
            else if (request.op == '-')
                response = request.num1 - request.num2;
            else if (request.op == '*')
                response = request.num1 * request.num2;
            else if (request.op == '/')
                response = request.num1 / request.num2;

            printf("[SERVER] Invio la risposta al client\n");
            UDPSend(sockfd, &response, sizeof(response), host, port);
        }

        closeConnection(sockfd);
    }
}
