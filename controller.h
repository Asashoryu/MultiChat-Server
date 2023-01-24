#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "database.h"

#define PACCHETT0_LEN 10000

void processa(const char * const pacchetto, char * pacchetto_da_spedire, int ** array_socket, int * dim);

#endif