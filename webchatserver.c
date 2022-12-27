#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define DIMBUFF 256
#define PORTA "10000"
// tiene traccia di tutti gli utenti online e accetta le richieste di messaggio di quelli attivi presso le loro chat reindirizzandole
//presso gli utenti giusti
int main() {
	// definizione variabili
	int socket_ascolta;
	int socket_client;
	struct sockaddr_un indirizzo;
	struct addrinfo hints;
	struct addrinfo *indirizzo_bind;
	struct sockaddr_storage indirizzo_client;
	socklen_t indirizzo_client_len = sizeof(indirizzo_client);

	pid_t child_pid;
	char buffer[DIMBUFF] = {0};

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(0, PORTA, &hints, &indirizzo_bind);

	// creazione socket
	socket_ascolta = socket(indirizzo_bind->ai_family, indirizzo_bind->ai_socktype, indirizzo_bind->ai_protocol);
	if (socket_ascolta < 0) { 
			perror("Errore nella creazione della server socket");
			exit(-1);
	}
	else {
		printf("Server: socket server creata\n");
	}

	//bind
	if (bind(socket_ascolta, indirizzo_bind->ai_addr, indirizzo_bind->ai_addrlen) != 0) { 
			perror("Errore nel bind della server socket");
			exit(-1);
	}
	else {
		printf("Server: bind riuscito\n");
	}

	// listen
	if (listen(socket_ascolta, 10) < 0){
			perror("Errore nel listen presso il server");
			exit(-1);
	}
	else {
		printf("Server: in ascolto\n");
	}

	// accept
	while(1) {
		socket_client = accept(socket_ascolta, (struct sockaddr *) &indirizzo_client, &indirizzo_client_len);
		if (socket_client < 0) { 
			perror("Errore nella creazione della client socket");
			exit(-1);
		}
		else {
			printf("Server: connessione accettata\n");
		}
		printf("socket_connessione = %d\n", socket_client);
		// recv
		printf("Si procede con la fork\n");
	
		child_pid = fork();
		// processo figlio
		if (child_pid == 0) {
				int byte_letti;
				byte_letti = recv(socket_client, buffer, DIMBUFF, 0);
				printf("%d caratteri letti dal server\n", byte_letti);
				buffer[byte_letti] = '\0';	
				printf("Server: il messaggio ricevuto: %s\n", buffer);

				char *inizio;
				char *fine;
				int dimensione;
				char cmd[DIMBUFF];
				char nome[DIMBUFF];
				char password[DIMBUFF];

				inizio = strstr(buffer, "cmd=");
				inizio += strlen("cmd=");
				fine = strstr(inizio, "\r\n");
				if (inizio && fine) {
					dimensione = fine-inizio;
					printf("dimensione %d\n", dimensione);
					strncpy(cmd, inizio, dimensione);
					cmd[dimensione]='\0';
					printf("il comando letto e' %s\n", cmd);
				}
				else {
					printf("Errore: inizio e' NULL\n");
				}
				
				inizio = strstr(buffer, "nome=");
				inizio += strlen("nome=");
				fine = strstr(inizio, "\r\n");
				if (inizio && fine) {
					dimensione = fine-inizio;
					printf("dimensione %d\n", dimensione);
					strncpy(nome, inizio, dimensione);
					nome[dimensione]='\0';
					printf("il nome letto e' %s\n", nome);
				}
				else {
					printf("Errore: inizio e' NULL\n");
				}

				inizio = strstr(buffer, "password=");
				inizio += strlen("password=");
				fine = strstr(inizio, "\r\n");
				if (inizio && fine) {
					dimensione = fine-inizio;
					printf("dimensione %d\n", dimensione);
					strncpy(password, inizio, dimensione);
					password[dimensione]='\0';
					printf("la password letta e' %s\n", password);
				}
				else {
					printf("Errore: inizio e' NULL\n");
				}

				if(strcmp(nome, "pippo") == 0 && strcmp(password, "paolo") == 0) {
					printf("Login OK\n");
					send(socket_client, "1", 1, 0);
				}
				else {
					printf("Login fallito\n");
					send(socket_client, "0", 1, 0);
				}


				printf("Server: chiusa socket client\n");
				close(socket_client);
			close(child_pid);
		}
		// processo padre
		else {
			printf("entrato nel processo padre prima della wait\n");
			wait(NULL);
			printf("Superata wait del padre\n");
			if (!close(socket_ascolta)) {
				perror("Errore in chiusura della socket presso il server");
				exit(-1);
			}
			else {
				printf("Server: socket chiusa con successo\n");
			}
		}
		printf("superato if ed else nella while dell'accept");
	}
	
	unlink("./demo_socket");
	printf("Server: socket unlinkata\n");
	printf("Server: sessione terminata\n");
	return 1;
}
