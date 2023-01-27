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
#include <signal.h>

#include "controller.h"

#define DIMBUFF 256
#define PORTA "10000"

int max_socket = 0;

void handle_sigint(int sig)
{
    printf("\nCatturato signal %d\n", sig);
	for (int i = 0; i < max_socket; i++) {
		close(i);
	}
	exit (0);
}

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

	signal(SIGINT, handle_sigint);
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

	setsockopt(socket_ascolta,SOL_SOCKET,SO_REUSEADDR, 0, sizeof(int));

	//bind
	if (bind(socket_ascolta, indirizzo_bind->ai_addr, indirizzo_bind->ai_addrlen) != 0) {
			perror("Errore nel bind della server socket");
			exit(-1);
	}
	else {
		printf("Server: bind riuscito\n");
	}
	freeaddrinfo(indirizzo_bind);

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
	
	max_socket = socket_ascolta;

	// accept
	while(1) {

		fd_set socket_leggibili;
		FD_ZERO(&socket_leggibili);
		struct timeval timeout;
		timeout.tv_sec = 1;
		timeout.tv_usec = 500000;

		memcpy(&socket_leggibili, &socket_aperte, sizeof(socket_aperte));

		if (select(max_socket + 1, &socket_leggibili, 0, 0, &timeout) < 0) {
			fprintf(stderr, "select() fallita. (%d)\n", errno);
			return 1;
		}

		int i;
		for (int i = 0; i <= max_socket; ++i) {
			if (FD_ISSET(i, &socket_leggibili)) {

				printf("Il ciclo e %d\n", i);
				
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

					//setsockopt(socket_client,SOL_SOCKET,SO_REUSEADDR, 0, sizeof(int));

					char indirizzo_buffer[100];
					getnameinfo((struct sockaddr*) &indirizzo_client, indirizzo_client_len, indirizzo_buffer, sizeof(indirizzo_buffer), 0, 0, NI_NUMERICHOST);
					printf("Server: accettata una nuova connessione da %s con socket %d\n", indirizzo_buffer, socket_client);
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
					printf("questa è la socket prima di essere processata: %d\n", i);
					processa(buffer_read, &pacchetto_da_spedire, &array, &dim, &i);

					int pacchetto_da_spedire_len = strlen(pacchetto_da_spedire);

					printf("\nEcco il pacchetto che sarebbe spedito di dimensione %d:\n%s", pacchetto_da_spedire_len, pacchetto_da_spedire);

					printf("%d e la dimensione dell'array di socket da spedire\n", dim);

					for(int a=0; a<dim;a++) printf("elemento %d dell'array %d\n", a, array[a]);

					array[dim-1] = i;

					for(int a=0; a<dim;a++) printf("elemento %d dell'array %d\n", a, array[a]);

					for (int z = 0; z < dim; z++) {
						int begin = 0;
						if(FD_ISSET(array[z], &socket_aperte)) {
							while(begin < pacchetto_da_spedire_len) {
								int sent = send(array[z], pacchetto_da_spedire + begin, pacchetto_da_spedire_len - begin, 0);
								if (sent == -1) {
									printf("Si è verificato un errore nella spedizione del pacchetto %d alla socket %d, con errore %d (%d)\n", z, array[z], sent, errno);
								}
								begin += sent;
								printf("spedito pacchetto %d alla socket %d\n", z, array[z]);
							}
						}
					}

					printf("Finito di spedire i pacchetti\n");

					dealloca_pacchetto(pacchetto_da_spedire);
					dealloca_array(&array);
				}
			}
		}
	}

	close(socket_ascolta);
	printf("Server: socket chiuse\n");
	printf("Server: sessione terminata\n");
	return 1;
}
