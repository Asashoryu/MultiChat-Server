#include <libpq-fe.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "database.h"

PGconn* connetti_db(const char* const connstring)
{
    PGconn *conn = PQconnectdb(connstring);

    if (PQstatus(conn) == CONNECTION_BAD)
    {
        fprintf(stderr, "DB: connessione fallita: %s\n", PQerrorMessage(conn));
        disconnetti_db(conn);
        return NULL;
    }
    else if (PQstatus(conn) == CONNECTION_OK)
    {
        // puts("DB: connesso");
        return conn;
    }
}

void disconnetti_db(PGconn* conn)
{
    //puts("DB: disconnesso");
    PQfinish(conn);
}

int inserisci_utente_db(const int utente_id, const char * const nome, const char * const password) 
{
    PGconn *miaconn;
    PGresult *exe;
    char comandoSQL[2000];
    char errore[1000];
    int flag = 0;

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"Insert into utente values (%d, '%s', '%s')", utente_id, nome, password);
        exe = PQexec(miaconn, comandoSQL);
        strcpy(errore, PQresultErrorMessage(exe));
        if(strlen(errore) > 0)
        {
            printf("%s\n",errore);
            printf("DB: errore nel comando insert, utente non inserito\n");
        }
        else
        {
            printf("DB: utente inserito con successo\n");
            flag = 1;
        }
        PQclear(exe);
    }
    else
    {
        printf("DB: database non trovato, utente non inserito\n");
    }

    disconnetti_db(miaconn);
    return flag;
}