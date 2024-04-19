#include "common.h"

int main (int argc, char **argv)
{
    // variaveis locais
    int             sockfd, n;
    int             sendbytes;
    struct sockaddr_in servaddr;
    char            sendline[MAXLINE];
    char            recvline[MAXLINE];

    // checador de uso
    if (argc != 2)
        err_n_die("usage: %s <server address>", argv[0]);
    
    // criar novo socket
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_n_die("Error while creating the socket!");
    
    // zerar endereço
    bzero(&servaddr, sizeof(servaddr));
    // AF_INET
    servaddr.sin_family = AF_INET;
    // Port
    servaddr.sin_port = htons(SERVER_PORT);

    // traduzir endereço para binário
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
        err_n_die("inet_pton error for %s ", argv[1]);
    
    // conectar ao servidor
    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
        err_n_die("connect failed!");
    
    // Conectado. Preparando mensagem.
    sprintf(sendline, "GET / HTTP/1.1\r\n\r\n");
    sendbytes = strlen(sendline);
    
    // Enviar socket
    if (write(sockfd, sendline, sendbytes) != sendbytes)
        err_n_die("write error");

    // Receber Resposta
    memset(recvline, 0, MAXLINE);
    // Ler resposta do server
    while ( (n = read(sockfd, recvline, MAXLINE-1)) > 0)
    {
        printf("%s", recvline);
    }
    if (n < 0)
        err_n_die("read error");
    
    // programa terminou com sucesso
    exit(0);
}