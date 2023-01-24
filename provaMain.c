#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gestore_pacchetti.h"
#include <stdio.h>
#include <string.h>
#include <libpq-fe.h>
#include "database.h"

//gcc -o prova provaMain.c database.c -I/usr/include/postgresql -L/usr/lib/postgresql/15/lib -lpq

int main ()
{
    int flag;
    char nome[200];
    char amministratore[200];
    char password[200];
    char user[200];
    int num,i;
    PGresult *risultato;
    // strcpy (nome,"G1");
    //strcpy (amministratore,"Alex");
    // strcpy (password,"pass");
    // flag = insert_utente_db (amministratore,password);
    strcpy (user,"Patroccio");
    // flag = insert_utente_db (user,"Pietroclo");
    //scanf ("%s",nome);
    // flag = insert_gruppo_db (nome,amministratore);
    //flag = insert_membership_db (user,nome);
    // printf ("%d\n",flag);
    // strcpy (nome,"G20");
    // flag = insert_gruppo_db (nome,amministratore);
    // flag = insert_membership_db (user,nome);
    risultato = select_gruppi_senza_utente (user);
    num = PQntuples (risultato);
    for (i=0;i<num;i++)
    {
        printf ("%s\n",PQgetvalue(risultato,i,0));
    }
    return 0;
}