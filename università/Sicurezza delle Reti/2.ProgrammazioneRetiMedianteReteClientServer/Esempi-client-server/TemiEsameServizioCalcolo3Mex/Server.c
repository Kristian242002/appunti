#include "network.h"

int main(void) {
    socketif_t socket;
    connection_t connection;
    int num1, num2, response;
    char op;

    socket = createTCPServer(35000);

    if (socket < 0) {
        printf("[SERVER] Errore di creazione del socket: %i\n", socket);
    } else {
        printf("[SERVER] Sono in attesa di richieste di connessione da qualche client\n");
        connection = acceptConnection(socket);
        printf("[SERVER] Connessione instaurata\n");

        while (1) {
            TCPReceive(connection, &num1, sizeof(num1));
            TCPReceive(connection, &num2, sizeof(num2));
            TCPReceive(connection, &op, sizeof(op));

            if (op == 'e') {
                printf("[SERVER] Il client ha richiesto la chiusura\n");
                break;
            }

            printf("[SERVER] Ricevuto: %d %c %d\n", num1, op, num2);

            if (op == '+')
                response = num1 + num2;
            else if (op == '-')
                response = num1 - num2;
            else if (op == '*')
                response = num1 * num2;
            else if (op == '/')
                response = num1 / num2;

            printf("[SERVER] Invio la risposta al client\n");
            TCPSend(connection, &response, sizeof(response));
        }

        closeConnection(connection);
    }
}
