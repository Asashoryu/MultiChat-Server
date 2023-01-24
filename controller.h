#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "database.h"

#define PACCHETT0_LEN 10000

char *processa(const char * const pacchetto, int ** array_socket, int * dim);

#endif