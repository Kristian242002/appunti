#include "network.h"

int main(void) {
    socketif_t sock;
    char targa[10];
    int response;
    char serverHost[MAXADDRESSLEN];
    int serverPort;

    sock = createUDPInterface(AUTO);

    if (sock < 0) {
        printf("[CLIENT] Errore di creazione del socket: %i\n", sock);
    } else {
        printf("[CLIENT] Inserisci la targa:\n");
        scanf("%s", targa);

        UDPSend(sock, targa, sizeof(targa), "localhost", 35000);
        UDPReceive(sock, &response, sizeof(response), serverHost, &serverPort);

        printf("[CLIENT] Numero di passaggi registrati per %s: %d\n", targa, response);

        closeConnection(sock);
    }
}
