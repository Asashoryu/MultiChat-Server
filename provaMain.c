#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gestore_pacchetti.h"

int main ()
{
    char pac[200];
    char *cmd = NULL;
    char *nome = NULL;
    char *password = NULL;
    strcpy (pac, "cmd=100\r\nnome=Alex\r\npassword=pass\r\n\r\n");
    // printf ("%s\n",pac);
    cmd = alloca_comando();
    cmd = parse_comando (pac);
    alloca_nome_e_password (&nome,&password);
    // nome = malloc (200*sizeof(char));
    // password = malloc (200*sizeof(char));
    parse_login (pac,nome,password);
    printf ("comando = %s\n",cmd);
    dealloca_comando(&cmd);
    dealloca_nome_password(&nome,&password);
    if (nome == NULL && password == NULL)
    {
        printf ("Ok\n");
    }
    return 0;
}