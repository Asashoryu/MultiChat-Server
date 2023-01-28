#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gestore_pacchetti.h"
#include <stdio.h>
#include <string.h>
//#include <libpq-fe.h>
//#include "database.h"

//gcc -o prova provaMain.c database.c -I/usr/include/postgresql -L/usr/lib/postgresql/15/lib -lpq

//gcc -o prova 

int main ()
{
    // int flag;
    // int socket;
    // void *ns = NULL;
    char pk[200];
    // char *nokme;
    // char amministratore[200];
    // char password[200];
    // char user[200];
    // char gruppo[200];
    // char mess[200];
    // int num,i;
    // PGresult *risultato;

    char *gruppo;
    char *utente;
    char *richiedente;

    strcpy(pk,"cmd=800\r\ngruppo=Pino\r\nutente=pass\r\nrichiedente=ciao\r\n\r\n");
    alloca_annulla_notifica (&gruppo,&utente,&richiedente);
    parse_annulla_notifica (pk,gruppo,utente,richiedente);
    printf ("%s %s %s\n",gruppo,utente,richiedente);
    dealloca_annulla_notifica (&gruppo,&utente,&richiedente);

    // strcpy (gruppo,"Mondo");
    // strcpy (user,"Trincalex");
    // strcpy (mess,"Welaaaaa");
    // strcpy (password,"pass15");
    // socket = 10;

    // flag = annulla_connessione_utente (user);
    // if (flag == 1)
    //     printf ("OK\n");
    // risultato = select_socket_gruppo (gruppo,user);
    // num = PQntuples (risultato);
    // for (i=0;i<num;i++)
    // {
    //     printf ("%s\n",PQgetvalue(risultato,i,2));
    // }
    return 0;
}