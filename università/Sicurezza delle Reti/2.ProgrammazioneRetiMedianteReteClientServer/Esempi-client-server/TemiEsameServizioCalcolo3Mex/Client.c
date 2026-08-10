#include "network.h"

int main(void) {
    connection_t connection;
    int num1, num2, response;
    char line[50], op;

    printf("[CLIENT] Creo una connessione logica col server\n");
    connection = createTCPConnection("localhost", 35000);

    if (connection < 0) {
        printf("[CLIENT] Errore nella connessione al server: %i\n", connection);
    } else {
        while (1) {
            printf("[CLIENT] Inserisci 'num1 op num2' (op = + - * /) oppure 'esci' per terminare:\n");
            scanf(" %[^\n]", line);

            if (strcmp(line, "esci") == 0) {
                num1 = 0;
                num2 = 0;
                op = 'e';
                TCPSend(connection, &num1, sizeof(num1));
                TCPSend(connection, &num2, sizeof(num2));
                TCPSend(connection, &op, sizeof(op));
                printf("[CLIENT] Chiudo la connessione\n");
                break;
            }

            sscanf(line, "%d %c %d", &num1, &op, &num2);

            TCPSend(connection, &num1, sizeof(num1));
            TCPSend(connection, &num2, sizeof(num2));
            TCPSend(connection, &op, sizeof(op));

            TCPReceive(connection, &response, sizeof(response));
            printf("[CLIENT] Risultato: %d\n", response);
        }

        closeConnection(connection);
    }
}
