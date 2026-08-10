#include "network.h"

int main(){
    socketif_t sockfd;
    FILE* connfd;
    int i;
    long length=0;
    char request[MTU], method[10], path[100];
    char filename[200] = "";
    char *p, *start;
    FILE *outfile;
    char c;
    
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
        strcpy(path, strtok(NULL, " "));
        
        while(request[0]!='\r') {
            fgets(request, sizeof(request), connfd);
            printf("%s", request);
            if(strstr(request, "Content-Length:")!=NULL)
                length = atol(request+15);
        }
        
        if(strcmp(method, "POST")==0)  {
            // Leggo riga per riga finché non trovo il filename
            long bytesRead = 0;
            do {
                fgets(request, sizeof(request), connfd);
                bytesRead += strlen(request);
                if(strstr(request, "filename=") != NULL) {
                    start = strstr(request, "filename=\"") + 10;
                    p = strchr(start, '"');
                    strncpy(filename, start, p - start);
                    filename[p - start] = '\0';
                }
            } while(request[0] != '\r' && bytesRead < length);
            
            // Salto la riga vuota che precede il contenuto
            fgets(request, sizeof(request), connfd);
            bytesRead += strlen(request);
            
            // Apro il file su disco e ci scrivo tutto tranne il boundary finale
            outfile = fopen(filename, "wb");
            
            long remaining = length - bytesRead;
            // Il boundary finale + \r\n-- occupa spazio: va scartato
            // approccio semplice: leggo tutto in memoria e taglio il boundary
            char *buffer = malloc(remaining);
            fread(buffer, 1, remaining, connfd);
            
            // Cerco il boundary di chiusura per sapere dove finisce il file vero
            char *boundaryEnd = strstr(buffer, "\r\n------");
            long fileSize = boundaryEnd ? (boundaryEnd - buffer) : remaining;
            
            fwrite(buffer, 1, fileSize, outfile);
            fclose(outfile);
            free(buffer);
            
            printf("[SERVER] File '%s' salvato (%ld byte)\n", filename, fileSize);
        }
        
        char *resp = "HTTP/1.1 200 OK\r\n\r\n<html><body>Upload completato</body></html>\r\n";
        fputs(resp, connfd);
        fclose(connfd);
                
        printf("\n\n[SERVER] sessione HTTP completata\n\n");
    }
    
    return 0;
}
