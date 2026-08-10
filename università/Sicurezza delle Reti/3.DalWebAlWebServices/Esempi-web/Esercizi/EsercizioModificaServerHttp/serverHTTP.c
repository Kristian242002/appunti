#include "network.h"

int main(){
    socketif_t sockfd;
    FILE* connfd;
    FILE* filefd;
    int i;
    long length=0, fileLength;
    char request[MTU], method[10], path[100], c;
    char header[256];
    char filename[100];
    char *buffer;
    
    sockfd = createTCPServer(8000);
    if (sockfd < 0){
        printf("[SERVER] Errore: %i\n", sockfd);
        return -1;
    }
    
    while(true) {
        connfd = acceptConnectionFD(sockfd);
        
        fgets(request, sizeof(request), connfd);
        printf("%s", request);
        
        strcpy(method, strtok(request, " "));
        strcpy(path, strtok(NULL, " "));   // <-- estraggo il path richiesto dal browser
        
        while(request[0]!='\r') {
            fgets(request, sizeof(request), connfd);
            printf("%s", request);
            if(strstr(request, "Content-Length:")!=NULL)  {
                length = atol(request+15);
            }
        }
        
        if(strcmp(method, "POST")==0)  {
            for(i=0; i<length; i++)  {
                c = fgetc(connfd);
                printf("%c", c);
            }
        }
        
        if(strcmp(path, "/")==0)
            strcpy(filename, "prova.html");   // pagina di default
        else
            strcpy(filename, path+1);   // tolgo lo slash iniziale

        filefd = fopen(filename, "rb");
        
        if(filefd == NULL) {
            char *notFound = "HTTP/1.1 404 Not Found\r\n\r\n<html><body>File non trovato</body></html>\r\n";
            fputs(notFound, connfd);
        }
        else {
            fseek(filefd, 0, SEEK_END);
            fileLength = ftell(filefd);
            rewind(filefd);
            
            buffer = malloc(fileLength);
            fread(buffer, 1, fileLength, filefd);
            fclose(filefd);
            
            sprintf(header, "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\n\r\n", fileLength);
            fputs(header, connfd);
            fwrite(buffer, 1, fileLength, connfd);
            
            free(buffer);
        }
        
        fclose(connfd);
        printf("\n\n[SERVER] sessione HTTP completata\n\n");
    }
    
    return 0;
}
