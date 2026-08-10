#include "network.h"

#define MAX_TARGHE 100

typedef struct {
    char targa[10];
    int passaggi;
} record_t;

int main(void) {
    socketif_t sock;
    record_t archivio[MAX_TARGHE];
    int numTarghe = 0;

    char targa[10];
    int response, i, trovata;
    char clientHost[MAXADDRESSLEN];
    int clientPort;

    sock = createUDPInterface(35000);

    if (sock < 0) {
        printf("[SERVER] Errore di creazione del socket: %i\n", sock);
    } else {
        printf("[SERVER] In attesa di passaggi al casello...\n");

        while (1) {
            UDPReceive(sock, targa, sizeof(targa), clientHost, &clientPort);
            printf("[SERVER] Passaggio rilevato per la targa: %s\n", targa);

            trovata = 0;
            for (i = 0; i < numTarghe; i++) {
                if (strcmp(archivio[i].targa, targa) == 0) {
                    archivio[i].passaggi++;
                    response = archivio[i].passaggi;
                    trovata = 1;
                    break;
                }
            }

            if (!trovata) {
                strcpy(archivio[numTarghe].targa, targa);
                archivio[numTarghe].passaggi = 1;
                response = 1;
                numTarghe++;
            }

            printf("[SERVER] Numero di passaggi per %s: %d\n", targa, response);
            UDPSend(sock, &response, sizeof(response), clientHost, clientPort);
        }
    }
}
