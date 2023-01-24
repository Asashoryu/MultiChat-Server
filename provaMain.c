#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gestore_pacchetti.h"

int main ()
{
    char pac1[200];
    char pac2[200];
    char *cmd = NULL;
    char *nome = NULL;
    char *password = NULL;
    char *gruppo_n = NULL;
    char *utente_n = NULL;
    char *messaggio = NULL;
    char *ora = NULL;
    strcpy (pac1, "cmd=100\r\nnome=Alex\r\npassword=pass\r\n\r\n");
    strcpy (pac2,"cmd=200\r\ngruppo=G1\r\nutente=Alex\r\nmessaggio=ciao\r\nminutaggio=min\r\n\r\n");
    cmd = alloca_comando();
    cmd = parse_comando (pac2);
    // alloca_nome_e_password (&nome,&password);
    // parse_login (pac1,nome,password);
    printf ("comando = %s\n",cmd);
    dealloca_comando(&cmd);
    // dealloca_nome_password(&nome,&password);
    alloca_gruppo_e_utente (&gruppo_n,&utente_n);
    alloca_messaggio_e_minutaggio (&messaggio,&ora);
    parse_messaggio (pac2,gruppo_n,utente_n,messaggio,ora);
    printf ("gruppo = %s\nnome = %s\nmessaggio = %s\nora = %s\n",gruppo_n,utente_n,messaggio,ora);
    dealloca_gruppo_e_utente (&gruppo_n,&utente_n);
    dealloca_messaggio_e_minutaggio (&messaggio,&ora);
    if (gruppo_n == NULL && utente_n == NULL && messaggio == NULL && ora == NULL)
    {
        printf ("Ok\n");
    }
    return 0;
}