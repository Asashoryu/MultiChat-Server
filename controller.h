#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "database.h"

#define PACCHETT0_LEN 100000

void processa(const char * const pacchetto, char ** pacchetto_da_spedire, int ** array_socket, int * dim, int socket_fd);
char *alloca_pacchetto();
void dealloca_pacchetto(char * pacchetto);

#endif