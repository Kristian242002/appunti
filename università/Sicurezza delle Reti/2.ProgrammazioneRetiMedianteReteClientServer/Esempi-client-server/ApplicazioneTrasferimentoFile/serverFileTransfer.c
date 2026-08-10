#include "network.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    socketif_t socket;
    connection_t connection;
    char filename[100];
    int c;
    FILE *fptr;

    socket = createTCPServer(40000);
    if (socket < 0) {
        printf("[SERVER] Errore di creazione del socket: %i\n", socket);
        return -1;
    }

    printf("[SERVER] Sono in attesa di richieste di connessione da qualche client\n");
    connection = acceptConnection(socket);
    printf("[SERVER] Connessione instaurata\n");

    // Ricevo il nome del file richiesto dal client
    TCPReceive(connection, filename, sizeof(filename));
    printf("[SERVER] Il client ha richiesto il file: %s\n", filename);

    fptr = fopen(filename, "rb");
    if (fptr == NULL) {
        printf("[SERVER] Errore apertura file %s\n", filename);
        c = -1;
        TCPSend(connection, &c, sizeof(c)); // segnalo subito la fine (errore)
        closeConnection(connection);
        return -1;
    }

    // Leggo e invio un byte alla volta
    c = fgetc(fptr);
    while (c != EOF) {
        TCPSend(connection, &c, sizeof(c));
        c = fgetc(fptr);
    }

    // Segnale di fine trasmissione
    c = -1;
    TCPSend(connection, &c, sizeof(c));

    printf("[SERVER] Trasferimento completato\n");
    fclose(fptr);
    closeConnection(connection);
    return 0;
}
