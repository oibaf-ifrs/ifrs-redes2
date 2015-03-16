#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "codes.h"

void handle_list(int fd);
void handle_put(int fd);
void handle_get(int fd);
void handle_help(int fd);

// MAIN PROGRAM START
main()
{
	int domain, type, protocol;

	int socketfd;
	int novo_socketfd;

	struct sockaddr_in end_local;
	struct sockaddr_in end_remoto;
	bzero(&end_remoto, sizeof(end_remoto));
        bzero(&end_local, sizeof(end_remoto));
	int tam_end_local;
	int tam_end_remoto;

	int resultado_do_fork;


	domain = AF_INET;
	type = SOCK_STREAM;
	protocol = 0;

	/********************* Abre o socket ***************8*/
	socketfd = socket(domain,type,protocol);
	if(socketfd == -1)
	{	
		perror("Erro no socket\n");
		exit(1);
	}


	/***************** Conecta ao servidor ***/
	end_remoto.sin_family = AF_INET;
	end_remoto.sin_port = htons(30000);
	end_remoto.sin_addr.s_addr = inet_addr("192.168.134.128");
	tam_end_remoto = sizeof(end_remoto);
	if(connect(socketfd, (struct sockaddr *) &end_remoto, tam_end_remoto) == -1)
	{
		perror("Erro no connect\n");
		exit(1);
	}

	funcao_do_cliente(socketfd);
	close(socketfd);
}


funcao_do_cliente(int fd)
{
	char prompt[MAX_STR_SIZE] = "";
	char parameter[MAX_STR_SIZE] = "";
	int requestCode = 0;
	int responseCode = 0;
	int tam;
	while (requestCode-REQUEST_CODE_QUIT)
        {
                recv(fd, prompt, MAX_STR_SIZE, 0);
		printf("%s",prompt);
		scanf("%d",&requestCode);
		send(fd, &requestCode, sizeof(requestCode), 0);
                recv(fd, &responseCode, sizeof(responseCode), 0);
		if(responseCode != RESPONSE_CODE_OK) {
			fprintf(stderr, "SERVER RETURNED ERROR CODE: [%d].\n\n",responseCode);
		}
		else {
			fprintf(stdout, "SERVER RETURNED CODE: [%d].\n\n",responseCode);
	                switch(requestCode)
	                {
				case REQUEST_CODE_LIST:
		                        handle_list(fd);
	                                break;
	                        case REQUEST_CODE_PUT:
	                                handle_put(fd);
                        	        break;
		                case REQUEST_CODE_GET:
	                                handle_get(fd);
	                                break;
        	                case REQUEST_CODE_HELP:
	                                handle_help(fd);
        	                        break;
	                }
		}
        }
	fprintf(stdout,"BYE!\n");
}

// FUNÇÕES PARA MANIPULAR COMANDOS
void handle_list(int fd)
{
}

void handle_put(int fd)
{
}

void handle_get(int fd)
{
}

void handle_help(int fd)
{
}
