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
    char line[50];
    char host[MAXADDRESSLEN];
    int port;

    sockfd = createUDPInterface(36000); 

    while (1) {
        printf("[CLIENT] Inserisci 'num1 op num2' (op = + - * /) oppure 'esci' per terminare:\n");
        scanf(" %[^\n]", line);

        if (strcmp(line, "esci") == 0) {
            request.op = 'e';
            UDPSend(sockfd, &request, sizeof(request), "localhost", 35000);
            printf("[CLIENT] Chiudo\n");
            break;
        }

        sscanf(line, "%d %c %d", &request.num1, &request.op, &request.num2);
        UDPSend(sockfd, &request, sizeof(request), "localhost", 35000);
        UDPReceive(sockfd, &response, sizeof(response), host, &port);
        printf("[CLIENT] Risultato: %d\n", response);
    }

    closeConnection(sockfd);
}
