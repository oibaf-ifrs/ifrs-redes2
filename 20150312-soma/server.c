#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

main()
{
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


funcao_do_servidor(int fd)
{
	int num1=0, num2=0;
	int tam=0;

	tam = recv(fd, &num1, sizeof(num1), 0);
	tam = recv(fd, &num2, sizeof(num2), 0);
	printf("Recebi: %i e %i\nBytes: %i\n",num1, num2,tam);
	tam = num1 + num2;
	send(fd, &tam, sizeof(tam), 0);

}

