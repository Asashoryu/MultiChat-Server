//gcc -o wbc webchatserver.c controller.c gestore_pacchetti.c database.c -I/usr/include/postgresql -L/usr/lib/postgresql/15/lib -lpq
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>

#include "controller.h"

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

	fd_set socket_aperte;
	FD_ZERO(&socket_aperte);
	FD_SET(socket_ascolta, &socket_aperte);
	int max_socket = socket_ascolta;

	// accept
	while(1) {

		fd_set socket_leggibili;
		socket_leggibili = socket_aperte;
		if (select(max_socket + 1, &socket_leggibili, 0, 0, 0) < 0) {
			fprintf(stderr, "select() fallita. (%d)\n", errno);
			return 1;
		}

		int i;
		for (int i = 1; i <= max_socket; ++i) {
			if (FD_ISSET(i, &socket_leggibili)) {

				if (i == socket_ascolta) {

					struct sockaddr_storage indirizzo_client;
					socklen_t indirizzo_client_len = sizeof(indirizzo_client);
					int socket_client = accept(socket_ascolta, (struct sockaddr*) &indirizzo_client, &indirizzo_client_len);
					if (socket_client < 0) {
						fprintf(stderr, "accept() fallita. (%d)/n", errno);
						return 1;
					}

					FD_SET(socket_client, &socket_aperte);
					if (socket_client > max_socket) {
						max_socket = socket_client;
					}

					char indirizzo_buffer[100];
					getnameinfo((struct sockaddr*) &indirizzo_client, indirizzo_client_len, indirizzo_buffer, sizeof(indirizzo_buffer), 0, 0, NI_NUMERICHOST);
					printf("Server: accettata una nuova connessione da %s\n", indirizzo_buffer);
				}
				else {
					char buffer_read[DIMBUFF];
					int byte_ricevuti = recv(i, buffer_read, DIMBUFF, 0);

					printf("%d caratteri letti dal server\n", byte_ricevuti);
					buffer_read[byte_ricevuti] = '\0';
					printf("Server: il messaggio ricevuto: %s\n", buffer_read);

					if (byte_ricevuti < 1) {
						FD_CLR(i, &socket_aperte);
						close(i);
						printf("Server: una connessione e stata chiusa\n");
						continue;
					}

					char * pacchetto_da_spedire;
					int * array;
					int dim;
					processa(buffer_read, &pacchetto_da_spedire, &array, &dim, i);
					printf("\nEcco il pacchetto che sarebbe spedito di dimensione %ld:\n%s", strlen(pacchetto_da_spedire), pacchetto_da_spedire);
					send(i, pacchetto_da_spedire, strlen(pacchetto_da_spedire), 0);
					dealloca_pacchetto(pacchetto_da_spedire);
					
					// int j;
					// for (j = 1; j <= max_socket; ++j) {
					// 	if (FD_ISSET(j, &socket_aperte)) {
					// 		if (j == socket_ascolta || j == i) {
					// 			continue;
					// 		}
					// 		else {
					// 			send(j, buffer_read, byte_ricevuti, 0);
					// 		}
					// 	}
					// }
				}
			}
		}

		/*socket_client = accept(socket_ascolta, (struct sockaddr *) &indirizzo_client, &indirizzo_client_len);
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
		*/
	}

	close(socket_ascolta);
	printf("Server: socket chiuse\n");
	printf("Server: sessione terminata\n");
	return 1;
}
