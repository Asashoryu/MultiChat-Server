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