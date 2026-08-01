#include "network.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    connection_t connection;
    char filename[100];
    int c;
    FILE *fptr;

    printf("[CLIENT] Creo una connessione logica col server\n");
    connection = createTCPConnection("localhost", 40000);
    if (connection < 0) {
        printf("[CLIENT] Errore nella connessione al server: %i\n", connection);
        return -1;
    }

    printf("Nome del file da richiedere al server:\n");
    scanf("%s", filename);

    // Invio il nome del file richiesto
    TCPSend(connection, filename, sizeof(filename));

    // Apro il file locale in scrittura, stesso nome
    fptr = fopen(filename, "wb");
    if (fptr == NULL) {
        printf("[CLIENT] Errore apertura file locale %s\n", filename);
        closeConnection(connection);
        return -1;
    }

    // Ricevo un byte alla volta finché non arriva il segnale di fine (-1)
    TCPReceive(connection, &c, sizeof(c));
    while (c != -1) {
        fputc(c, fptr);
        TCPReceive(connection, &c, sizeof(c));
    }

    printf("[CLIENT] File %s ricevuto e salvato\n", filename);
    fclose(fptr);
    closeConnection(connection);
    return 0;
}
