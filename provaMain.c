#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gestore_pacchetti.h"

int main ()
{
    char pac[200];
    strcpy (pac, "cmd=100\r\nnome=Alex\r\nutente=pass\r\n\r\n");
    // printf ("%s\n",pac);
    char *nome = alloca_nome();
    char *password = alloca_password();
    parse_login (pac,nome,password);
    printf ("l'utente %s nel gruppo %s\n",nome,password);
    dealloca_nome_password (nome,password);
    return 0;
}