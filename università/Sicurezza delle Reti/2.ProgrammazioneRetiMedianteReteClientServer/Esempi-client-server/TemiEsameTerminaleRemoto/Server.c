#include "network.h"

int main(void) {
    socketif_t socket;
    connection_t connection;
    char command[256];
    char output[4096];
    FILE *pipe;
    int len;

    socket = createTCPServer(35000);

    if (socket < 0) {
        printf("[SERVER] Errore di creazione del socket: %i\n", socket);
    } else {
        printf("[SERVER] Sono in attesa di richieste di connessione da qualche client\n");
        connection = acceptConnection(socket);
        printf("[SERVER] Connessione instaurata\n");

        while (1) {
            TCPReceive(connection, command, sizeof(command));

            if (strcmp(command, "esci") == 0) {
                printf("[SERVER] Il client ha richiesto la chiusura\n");
                break;
            }

            printf("[SERVER] Eseguo il comando: %s\n", command);

            memset(output, 0, sizeof(output));
            pipe = popen(command, "r");
            if (pipe != NULL) {
                len = fread(output, 1, sizeof(output) - 1, pipe);
                output[len] = '\0';
                pclose(pipe);
            } else {
                strcpy(output, "Errore nell'esecuzione del comando\n");
            }

            TCPSend(connection, output, sizeof(output));
        }

        closeConnection(connection);
    }
}
