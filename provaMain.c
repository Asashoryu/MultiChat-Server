#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gestore_pacchetti.h"
#include <stdio.h>
#include <string.h>
#include <libpq-fe.h>
#include "database.h"

//gcc -o prova provaMain.c database.c -I/usr/include/postgresql -L/usr/lib/postgresql/15/lib -lpq

//gcc -o prova 

int main ()
{
    int flag;
    char pk[200];
    char *nome;
    char amministratore[200];
    char *password;
    char user[200];
    char gruppo[200];
    char mess[200];
    int num,i;
    PGresult *risultato;

    // strcpy(pk,"cmd=100\r\nnome=Pino\r\npassword=pass\r\n\r\n");
    // alloca_signin (&nome,&password);
    // parse_signin (pk,nome,password);
    // printf ("%s %s\n",nome,password);
    // dealloca_signin(&nome,&password);

    strcpy (gruppo,"Gruppo1");
    strcpy (user,"Pino");
    strcpy (mess,"Welaaaaa");

    flag = insert_notifica_db (user,gruppo);
    if (flag == 1)
        printf ("OK\n");
    // risultato = select_gruppi_senza_utente (user);
    // num = PQntuples (risultato);
    // for (i=0;i<num;i++)
    // {
    //     printf ("%s\n",PQgetvalue(risultato,i,0));
    // }
    return 0;
}