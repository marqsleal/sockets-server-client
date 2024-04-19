# Simple TCP Server

Este é um programa simples de servidor TCP escrito em C que aceita conexões de clientes, lê mensagens enviadas pelos clientes e envia uma resposta HTTP básica.
O cliente utilizado para acessar o servidor é o mesmo postado no projeto anterior (link: https://github.com/marqsleal/sockets-client/).

## Requisitos

Este projeto requer um ambiente de desenvolvimento Linux C padrão, incluindo uma Makefile utilizando CLANG e as bibliotecas de sistema padrão.

## Como Usar

1. Compile o programa a partir da Makefile utilizando o comando:
    ```
    make
    ```

2. Execute o programa o programa do servidor:
    ```
    ./tcps
    ```

3. Abra seu navegador padrão e acesse a porta 18000:
    ```
    http://localhost:18000
    ```

## Exemplo de Uso

```
$ ./tcps
...

GET / HTTP/1.1
Host: localhost:18000
Connection: keep-alive
sec-ch-ua: "Not A(Brand";v="99", "Opera GX";v="107", "Chromium";v="121"
sec-ch-ua-mobile: ?0
sec-ch-ua-platform: "Windows"
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/121.0.0.0 Safari/537.36 OPR/107.0.0.0 (Edition std-1)
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
Sec-Fetch-Site: none
Sec-Fetch-Mode: navigate
Sec-Fetch-User: ?1
Sec-Fetch-Dest: document
Accept-Encoding: gzip, deflate, br
Accept-Language: pt-BR,pt;q=0.9,en-US;q=0.8,en;q=0.7

...
```

## Contribuindo

Contribuições são bem-vindas! Sinta-se à vontade para abrir problemas (issues) ou enviar solicitações de pull (pull requests) para melhorar este projeto.

## Autor

Este projeto foi desenvolvido para fins de estudo por Gabriel F. Leal.