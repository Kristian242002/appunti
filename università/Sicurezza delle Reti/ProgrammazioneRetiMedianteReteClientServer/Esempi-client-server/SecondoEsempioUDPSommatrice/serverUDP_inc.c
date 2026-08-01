#include "network.h"
int main(void) {
    int request;
    int somma = 0;
    socketif_t socket;
    char hostAddress[MAXADDRESSLEN];
    int port;

    socket = createUDPInterface(35000);
    printf("[SERVER] Sono in attesa di richieste da qualche client\n");

    do {
        UDPReceive(socket, &request, sizeof(request), hostAddress, &port);
        printf("[SERVER] Ricevuto: %d\n", request);
        somma += request;
    } while (request != 0);

    printf("[SERVER] Invio somma finale: %d\n", somma);
    UDPSend(socket, &somma, sizeof(somma), hostAddress, port);
}
