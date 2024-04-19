#include "common.h"

void err_n_die(const char *fmt, ...)
{
    int errno_save;
    va_list     ap;

    // qualquer chamada de livraria ou sistema pode setar um erro, então, precisamos salvar isso agora
    errno_save = errno;

    // imprimir fmt+args pra standard out
    va_start(ap, fmt);
    vfprintf(stdout, fmt, ap);
    fprintf(stdout, "\n");
    fflush(stdout);

    // imprimir mensagem de erro se errno foi setado
    if(errno_save != 0)
    {
        fprintf(stdout, "(errno = %d) : %s\n", errno_save, strerror(errno_save));
        fprintf(stdout, "\n");
        fflush(stdout);
    }
    va_end(ap);

    // essa é a parte do 'e morre'. Termina o programa com um erro.
    exit(1);
}

char *bin2hex(const unsigned char *input, size_t len)
{
    char *result;
    char *hexits = "0123456789ABCDEF";

    if (input == NULL || len <=0)
        return NULL;
    
    //(2 hexits+space)/chr + NULL
    int resultlength = (len*3)+1;
    result = malloc(resultlength);
    bzero(result, resultlength);

    for (int i = 0; i < len ; i++)
    {
        result[i*3]     = hexits[input[i] >> 4];
        result[(i*3)+1] = hexits[input[i] & 0x0F];
        result[(i*3)+2] = ' '; // por motivo de leitura
    }

    return result;
}