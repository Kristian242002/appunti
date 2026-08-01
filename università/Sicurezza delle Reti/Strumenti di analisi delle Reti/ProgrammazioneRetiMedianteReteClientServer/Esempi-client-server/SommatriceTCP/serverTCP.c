#include "network.h"
int main(void) {
    socketif_t socket;
    connection_t connection;
    int request, somma = 0;

    socket = createTCPServer(35000);

    if (socket < 0) {
        printf("[SERVER] Errore di creazione del socket: %i\n", socket);
    }else {
        printf("[SERVER] Sono in attesa di richieste di connessione da qualche client\n");
        connection = acceptConnection(socket);
        printf("[SERVER] Connessione instaurata\n");

        do {
            TCPReceive(connection, &request, sizeof(request));
            printf("[SERVER] Ricevuto: %d\n", request);
            somma += request;
        } while (request != 0);

        printf("[SERVER] Invio la somma finale: %d\n", somma);
        TCPSend(connection, &somma, sizeof(somma));

        closeConnection(connection);
    }
}
