#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "database.h"

#define PACCHETT0_LEN 100000

void processa(const char * const pacchetto, char ** pacchetto_da_spedire, int ** const array_socket, int * dim, const int socket_fd);
char *alloca_pacchetto();
void dealloca_pacchetto(char * pacchetto);
char *alloca_array(int ** const array, int dim);
void dealloca_array(int ** const array);

#endif