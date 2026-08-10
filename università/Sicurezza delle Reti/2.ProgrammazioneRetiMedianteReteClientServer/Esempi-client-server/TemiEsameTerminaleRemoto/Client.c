#include "network.h"

int main(void) {
    connection_t connection;
    char command[256];
    char output[4096];

    printf("[CLIENT] Creo una connessione logica col server\n");
    connection = createTCPConnection("localhost", 35000);

    if (connection < 0) {
        printf("[CLIENT] Errore nella connessione al server: %i\n", connection);
    } else {
        while (1) {
            printf("shell> ");
            fgets(command, sizeof(command), stdin);
            command[strcspn(command, "\n")] = '\0'; // rimuove il newline finale

            TCPSend(connection, command, sizeof(command));

            if (strcmp(command, "esci") == 0) {
                printf("[CLIENT] Chiudo la connessione\n");
                break;
            }

            TCPReceive(connection, output, sizeof(output));
            printf("%s\n", output);
        }

        closeConnection(connection);
    }
}
