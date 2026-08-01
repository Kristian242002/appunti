#include "network.h"

int main(void) {
    int request, response;
    socketif_t socket;
    connection_t connection;
    
    socket = createTCPServer(35000); // istanza interfaccia soccketr
    if (socket < 0){
        printf("[SERVER] Errore di creazione del socket: %i\n", socket);
    }
    else
    {
        printf("[SERVER] Sono in attesa di richieste di connessione da qualche client\n");    
        connection = acceptConnection(socket); // accettazione three way handshake
        printf("[SERVER] Connessione instaurata\n");
        TCPReceive(connection, &request, sizeof(request));// ricevo
        printf("[SERVER] Ho ricevuto la seguente richiesta dal client: %d\n", request);
        response = request + 1;
        printf("[SERVER] Invio la risposta al client\n");
        TCPSend(connection, &response, sizeof(response));//invio
        closeConnection(connection);// chiudo
    }
}

