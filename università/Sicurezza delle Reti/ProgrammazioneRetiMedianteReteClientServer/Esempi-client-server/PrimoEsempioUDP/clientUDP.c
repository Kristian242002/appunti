#include "network.h"

int main(void) {
    socketif_t socket;
    char request[]="Ciao sono il client!\n";
    char response[MTU];
    char hostAddress[MAXADDRESSLEN];
    int port;
    
    socket = createUDPInterface(30000); // istanziato l'interfaccia socket
    
    printf("[CLIENT] Spedisco messaggio al server\n");
    printf("[CLIENT] Contenuto: %s\n", request);
    UDPSend(socket, request, strlen(request), "localhost", 100);//invio
     
    UDPReceive(socket, response, MTU, hostAddress, &port);//ricezione
    printf("[CLIENT] Ho ricevuto un messaggio da host/porta %s/%d\n", hostAddress, port);
    printf("[CLIENT] Contenuto: %s\n", response);
}

