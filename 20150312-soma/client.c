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
	int num1, num2, tam;

	printf("Somador remoto!\nInforme o primeiro número:");
	scanf("%d",&num1);
	send(fd, &num1, sizeof(num1), 0);

	printf("Informe o segundo número:");
	scanf("%d",&num2);
	send(fd, &num2, sizeof(num1), 0);

	tam = recv(fd, &num1, sizeof(num1), 0);

	printf("Soma: %d\n",num1);
}

