#include "common.h"
#include <strings.h>

int main (int argc, char **argv)
{
    // Vars
    int                     listenfd, connfd, n;
    struct sockaddr_in      servaddr;
    uint8_t                 buff[MAXLINE+1];
    uint8_t                 recvline[MAXLINE+1];

    // Criar novo socket
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_n_die("socket error.");

    // Endereço
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family         = AF_INET;
    servaddr.sin_addr.s_addr    = htonl(INADDR_ANY);
    servaddr.sin_port           = htons(SERVER_PORT);
    
    // Bind
    if ((bind(listenfd, (SA *) &servaddr, sizeof(servaddr))) < 0)
        err_n_die("bind error.");
    
    // Listen
    if ((listen(listenfd, 10)) < 0)
        err_n_die("listen error.");

    // Conection Dispatcher
    for ( ; ; )
    {
        struct sockaddr_in addr;
        socklen_t addr_len;
        char client_addres[MAXLINE-1];

        // Bloqueio de aceitações até a conexão imininente chegar
        // Retrona um "file descriptor" para a conexão
        printf("Waiting for the connection on port %d\n", SERVER_PORT);
        fflush(stdout);
        connfd = accept(listenfd, (SA *) &addr, &addr_len); /* Socket do cliente */

        inet_ntop(AF_INET, &addr, client_addres, MAXLINE);
        printf("Client connection: %s\n", client_addres);

        // Zera o buffer se terminada
        memset(recvline, 0, MAXLINE);

        // Agora le a mensagem do client
        while ( (n = read(connfd, recvline, MAXLINE-1) ) > 0)
        {
            fprintf(stdout, "\n%s\n\n%s", bin2hex(recvline, n), recvline);

            // Detectar final da mensagem (forma enxuta)
            if (recvline[n-1] == '\n')
            {
                break;
            }
            memset(recvline, 0, MAXLINE);
        }
        if (n < 0)
            err_n_die("read error.");
        
        // Enviando resposta HTTP
        snprintf((char*) buff, sizeof(buff), "HTTP/1.0 200 OK\r\n\r\nHello");

        write(connfd, (char*) buff, strlen((char *) buff));
        close(connfd);
    }    
}