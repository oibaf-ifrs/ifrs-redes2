#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h>

// LISTA DIRETORIOS
void listDir(char *dir)
{
	DIR *dp;
	struct dirent *ep;
	dp = opendir (dir);
	if (dp != NULL)
	{
		while (ep = readdir (dp))
		puts (ep->d_name);
		(void) closedir (dp);
	}
	else
	perror ("Couldn't open the directory!\n");
}

// PROGRAMA PRINCIPAL
int main (int argc, char* argv[])
{
	if (argc<2)
	{
		printf("ERROR: you must supply a directory!\n");
		exit (1);
	}
	else {
		listDir(argv[1]);
		exit (0);
	}
}
