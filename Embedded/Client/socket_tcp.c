#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>

#define		RECV_BUFF		512
#define 	EMB_PORT		4000

int main(int argc, char * argv[]) {
	int 				sock_srv;
	int					sock_client;
	int					sock_len;
	int					recv_len;
	int					b_continue;
	struct sockaddr_in 	server;
	struct sockaddr_in 	client;
	char				recv_buff[RECV_BUFF];
	
	// Création du socket
	sock_srv = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if(sock_srv == -1)
	{
		perror("Erreur socket()");
		exit(errno);
	}
	
	server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(EMB_PORT);
	
	// Bind du socket sur l'adresse:port
	if( bind(sock_srv, (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("Erreur bind()");
		exit(errno);
	}
	
	// Attente de connexions entrantes
    listen(sock_srv, 3);
	
	// Acceptation de la connexion entrante (un seul superviseur est autorisé à se connecter)
    sock_len = sizeof(client);
    sock_client = accept(sock_srv, (struct sockaddr *)&client, (socklen_t*)&sock_len);
    if (sock_client < 0)
    {
        perror("Erreur accept()");
    }
	
	printf("Client connecte\n");
	
	// On laisse le programme continuer tant que le message exit n'a pas été reçu
	b_continue = 1;
	while (b_continue) {
		// Réception des paquets envoyés par le client
		sock_len = sizeof(client);
		recv_len = recvfrom(sock_client, (void *)recv_buff , sizeof(recv_buff), 0, (struct sockaddr *)&client, (socklen_t*)&sock_len);
		if (recv_len < 0) {
			printf("Erreur recv()");
		}
		if (recv_len == 0) {
			printf("Client deconnecte\n");
			b_continue = 0;
		}
		// On positionne un \0 en fin de chaine de caractère reçue
		recv_buff[recv_len] = 0;
		//memset(recv_buff + recv_len, 0, sizeof(recv_buff) - recv_len);
		printf("Paquet reçu : %s\n", recv_buff);
		if (strcmp(recv_buff, "exit") == 0) {
			printf("Ordre recu : fin du programme\n");
			b_continue = 0;
		}
		if (strcmp(recv_buff, "takeoff") == 0) {
			printf("Ordre reçu : decollage\n");
		}
		if (strcmp(recv_buff, "land") == 0) {
			printf("Ordre reçu : atterrissage\n");
		}
	}
	
	close(sock_srv);
	
	return 0;
}