#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h>
#include "codes.h"

void listDir(char *dir);
void handle_list(int fd);
void handle_put(int fd);
void handle_get(int fd);
void handle_help(int fd);
void handle_quit(int fd);

// MAIN PROGRAM START
int main (int argc, char* argv[])
{
	if (argc<2)
	{
		perror("You must supply a directory!\n");
		exit (1);
	}
	else {
		listDir(argv[1]);
		//exit (0);
	}
	int domain, type, protocol;
	int socketfd;
	int novo_socketfd;

	struct sockaddr_in end_local;
	struct sockaddr_in end_remoto;
	int tam_end_local;
	int tam_end_remoto;
	bzero(&end_remoto, sizeof(end_remoto));
	bzero(&tam_end_remoto, sizeof(tam_end_remoto));

	int resultado_do_fork;
	
	domain = AF_INET;
	type = SOCK_STREAM;
	protocol = 0;

	/********************* Abre o socket ***************8*/
	socketfd = socket(domain,type,protocol);
	if(socketfd == -1)
	{	perror("Erro no socket\n");
		exit(1);

	}


	/***************** Associa o socket a uma porta local ***/
	end_local.sin_family = AF_INET;
	end_local.sin_port = htons(30000);
	end_local.sin_addr.s_addr = INADDR_ANY;
	tam_end_local = sizeof(end_local);
	if(bind(socketfd, (struct sockaddr *)&end_local, tam_end_local) == -1)
	{	perror("Erro no bind\n");
		exit(1);
	
	}


	/************ Espera por um pedido de conexao **********/
	listen(socketfd, 50);



	/*********** Aceita as conexao *************/
	while(1)
	{
		novo_socketfd = accept(socketfd, (struct sockaddr *) &end_remoto, &tam_end_remoto);
		resultado_do_fork = fork();
		if(resultado_do_fork == 0) //filho
		{
			close(socketfd);
			funcao_do_servidor(novo_socketfd);
			exit(0);
		}
		else
			close(novo_socketfd);
	}

}

// COMMAND AND CONTROL
funcao_do_servidor(int fd)
{
	char prompt[MAX_STR_SIZE];
	sprintf(prompt, "Hello! Server says:\n%d-LIST\n%d-PUT\n%d-GET\n%d-HELP\n%d-QUIT\n\n",REQUEST_CODE_LIST,REQUEST_CODE_PUT,REQUEST_CODE_GET,REQUEST_CODE_HELP,REQUEST_CODE_QUIT);
	char parameter[MAX_STR_SIZE];
	int option=0;
	int tam=0;
	int responseCode = RESPONSE_CODE_NOT_IMPLEMENTED;

	while (option-REQUEST_CODE_QUIT)
	{
		send(fd, prompt, MAX_STR_SIZE, 0);
		recv(fd, &option, sizeof(option), 0);
		switch(option)
		{
			case REQUEST_CODE_LIST:
				handle_list(fd);
				//break;
			case REQUEST_CODE_PUT:
				handle_put(fd);
				//break;
			case REQUEST_CODE_GET:
				handle_get(fd);
				//break;
			case REQUEST_CODE_HELP:
				send(fd, &responseCode, sizeof(responseCode), 0);
				handle_help(fd);
				break;
			default:
				handle_quit(fd);
				break;
		}
	}
	//tam = recv(fd, &num1, sizeof(num1), 0);
	//tam = recv(fd, &num2, sizeof(num2), 0);
	//printf("Recebi: %i e %i\nBytes: %i\n",num1, num2,tam);
	//tam = num1 + num2;
	//send(fd, &tam, sizeof(tam), 0);

}

// FUNÇÕES AUXILIARES
void listDir(char *dir)
{
	char tmpFileName[255];
	DIR *dp;
	struct dirent *ep;
	struct stat buf;
	dp = opendir (dir);
	if (dp != NULL)
	{
		while (ep = readdir (dp))
		{
			sprintf(tmpFileName,"%s/%s",dir,ep->d_name);
			stat(tmpFileName, &buf);
			//lista somente arquivos comuns (nao dir, nao block dev, ...)
			if (S_ISREG(buf.st_mode)) {
				puts (ep->d_name);
			}
		}
		closedir(dp);
	}
	else
		perror ("Couldn't open the directory!\n");
}

// FUNÇÕES PARA MANIPULAR COMANDOS
void handle_list(int fd)
{
	int responseCode = RESPONSE_CODE_NOT_IMPLEMENTED;
	send(fd, &responseCode, sizeof(responseCode), 0);
}

void handle_put(int fd)
{
	int responseCode = RESPONSE_CODE_NOT_IMPLEMENTED;
	send(fd, &responseCode, sizeof(responseCode), 0);
}

void handle_get(int fd)
{
	int responseCode = RESPONSE_CODE_NOT_IMPLEMENTED;
	send(fd, &responseCode, sizeof(responseCode), 0);
}

void handle_help(int fd)
{
	int responseCode = RESPONSE_CODE_NOT_IMPLEMENTED;
	send(fd, &responseCode, sizeof(responseCode), 0);
}

void handle_quit(int fd)
{
	int responseCode = RESPONSE_CODE_OK;
	send(fd, &responseCode, sizeof(responseCode), 0);
}
