#include "network.h"

float calcolaSomma(float val1, float val2)  {
   return (val1 + val2);
}

int contaPrimi(int a, int b)  {
    int i, j, flag;
    int count = 0;
    
    // Traverse each number in the interval
    for (i = a; i <= b; i++) {
        // Skip 0 and 1 as they are
        // neither prime nor composite
        if (i == 1 || i == 0)
            continue;
        
        // flag variable to tell
        // if i is prime or not
        flag = 1;
        
        for (j = 2; j <= i / 2; ++j) {
            if (i % j == 0) {
                flag = 0;
                break;
            }
        }
        
        // flag = 1 means i is prime
        if (flag == 1)
            count++;
    }
    
    return count;
}

int main(){
    socketif_t sockfd;
    FILE* connfd;
    int res, i;
    long length=0;
    char request[MTU], url[MTU], method[10], c;
    
    sockfd = createTCPServer(8000);
    if (sockfd < 0){
        printf("[SERVER] Errore: %i\n", sockfd);
        return -1;
    }
    
    while(true) {
        connfd = acceptConnectionFD(sockfd);
        
        fgets(request, sizeof(request), connfd);
        strcpy(method,strtok(request, " "));
        strcpy(url,strtok(NULL, " "));
        while(request[0]!='\r') {
            fgets(request, sizeof(request), connfd);
            if(strstr(request, "Content-Length:")!=NULL)  {
                length = atol(request+15);
            }
        }
        
        if(strcmp(method, "POST")==0)  {
            for(i=0; i<length; i++)  {
                c = fgetc(connfd);
            }
        }
        
        if(strstr(url, "calcola-somma")!=NULL)  {
            printf("Chiamata a funzione sommatrice\n");
            
            char *function, *op1, *op2;
            float somma, val1, val2;
   
            // skeleton: decodifica (de-serializzazione) dei parametri
            function = strtok(url, "?&");
            op1 = strtok(NULL, "?&");
            op2 = strtok(NULL, "?&");
            strtok(op1,"=");
            val1 = atof(strtok(NULL,"="));
            strtok(op2,"=");
            val2 = atof(strtok(NULL,"="));
            
            // chiamata alla business logic
            somma = calcolaSomma(val1, val2);
            
            // skeleton: codifica (serializzazione) del risultato
            fprintf(connfd,"HTTP/1.1 200 OK\r\n\r\n{\r\n    \"somma\":%f\r\n}\r\n", somma);
        }
        else if(strstr(url, "numeri-primi")!=NULL)  {
            printf("Chiamata a funzione numeri-primi\n");
            
            char *function, *pmin, *pmax;
            int numPrimi, valMin, valMax;
            
            // skeleton: decodifica (de-serializzazione) dei parametri
            function = strtok(url, "?&");
            pmin = strtok(NULL, "?&");
            pmax = strtok(NULL, "?&");
            strtok(pmin,"=");
            valMin = atoi(strtok(NULL,"="));
            strtok(pmax,"=");
            valMax = atoi(strtok(NULL,"="));
            
            // chiamata alla business logic
            numPrimi = contaPrimi(valMin, valMax);
            
            // skeleton: codifica (serializzazione) del risultato
            fprintf(connfd,"HTTP/1.1 200 OK\r\n\r\n{\r\n    \"numeriPrimi\":%d\r\n}\r\n", numPrimi);
        }
        else {
            fprintf(connfd,"HTTP/1.1 200 OK\r\n\r\n{\r\n    Funzione non riconosciuta!\r\n}\r\n");
        }
        
        fclose(connfd);
                
        printf("\n\n[SERVER] sessione HTTP completata\n\n");
    }
    
    closeConnection(sockfd);
    return 0;
}
