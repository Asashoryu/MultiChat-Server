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

PGresult *select_gruppi_utente(const char * const nome_utente) {
    PGconn *miaconn   = NULL;
    PGresult *gruppi_db = NULL;
    char comandoSQL[2000];
    char errore[1000];

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"select * from gruppo where nome = '%s' ORDER BY nome", nome_utente);
        gruppi_db = PQexec(miaconn, comandoSQL);
        strcpy(errore, PQresultErrorMessage(gruppi_db));
        if(strlen(errore) > 0)
        {
            printf("%s\n",errore);
            printf("DB: errore nel comando select, gruppi non trovati\n");
            PQclear(gruppi_db);
            gruppi_db = NULL;
        }
    }
    else
    {
        printf("DB: Database non trovato, gruppi non caricati\n");
    }

    disconnetti_db(miaconn);
    return gruppi_db;
}

PGresult *select_messaggi_gruppo_utente(const char * const nome_gruppo) {
    PGconn *miaconn   = NULL;
    PGresult *messaggi_db = NULL;
    char comandoSQL[2000];
    char errore[1000];

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"select * from messaggio where nome_gruppo = '%s' ORDER BY minutaggio", nome_gruppo);
        messaggi_db = PQexec(miaconn, comandoSQL);
        strcpy(errore, PQresultErrorMessage(messaggi_db));
        if(strlen(errore) > 0)
        {
            printf("%s\n",errore);
            printf("DB: errore nel comando select, messaggi non trovati\n");
            PQclear(messaggi_db);
            messaggi_db = NULL;
        }
    }
    else
    {
        printf("DB: Database non trovato, messaggi non caricati\n");
    }

    disconnetti_db(miaconn);
    return messaggi_db;
}

PGresult *select_notifiche_gruppo_utente(const char * const nome_gruppo) {
    PGconn *miaconn   = NULL;
    PGresult *notifiche_db = NULL;
    char comandoSQL[2000];
    char errore[1000];

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"select * from notifica where nome_gruppo = '%s'", nome_gruppo);
        notifiche_db = PQexec(miaconn, comandoSQL);
        strcpy(errore, PQresultErrorMessage(notifiche_db));
        if(strlen(errore) > 0)
        {
            printf("%s\n",errore);
            printf("DB: errore nel comando select, notifiche non trovate\n");
            PQclear(notifiche_db);
            notifiche_db = NULL;
        }
    }
    else
    {
        printf("DB: Database non trovato, notifiche non caricate\n");
    }

    disconnetti_db(miaconn);
    return notifiche_db;
}

int insert_gruppo_db(const char * const nome, const char * const amministratore) {
    PGconn *miaconn;
    PGresult *exe;
    char comandoSQL[2000];
    char errore[1000];
    int flag = 0;

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"Insert into gruppo(nome, amministratore_id) values ('%s', '%s')", nome, amministratore);
        exe = PQexec(miaconn, comandoSQL);
        strcpy(errore, PQresultErrorMessage(exe));
        if(strlen(errore) > 0)
        {
            printf("%s\n",errore);
            printf("DB: errore nel comando insert, gruppo non inserito\n");
        }
        else
        {
            printf("DB: gruppo inserito con successo\n");
            flag = 1;
        }
        PQclear(exe);
    }
    else
    {
        printf("DB: database non trovato, gruppo non inserito\n");
    }

    disconnetti_db(miaconn);
    return flag;
}
PGresult *select_utenti_connessi() {

    PGconn *miaconn   = NULL;
        PGresult *utente_registrato_db = NULL;
        char comandoSQL[2000];
        char errore[1000];

        miaconn = connetti_db(CONNSTRINGA);

        if(miaconn != NULL)
        {
            sprintf(comandoSQL,"select * from utente WHERE connessione IS NOT NULL");
            utente_registrato_db = PQexec(miaconn, comandoSQL);
            strcpy(errore, PQresultErrorMessage(utente_registrato_db));
            if(strlen(errore) > 0)
            {
                printf("%s\n",errore);
                printf("DB: errore nel comando select, utenti non trovati\n");
                PQclear(utente_registrato_db);
                utente_registrato_db = NULL;
            }
        }
        else
        {
            printf("DB: Database non trovato, utenti non caricati\n");
        }

        disconnetti_db(miaconn);
        return utente_registrato_db;
}

PGresult *select_gruppi_senza_utente(const char * const nome_utente, const char * const nome_gruppo) {
    PGconn *miaconn   = NULL;
    PGresult *gruppi_db = NULL;
    char comandoSQL[2000];
    char errore[1000];

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"select * from gruppo, membership where nome = '%s' AND nome_utente <> '%s'", nome_gruppo, nome_utente);
        gruppi_db = PQexec(miaconn, comandoSQL);
        strcpy(errore, PQresultErrorMessage(gruppi_db));
        if(strlen(errore) > 0)
        {
            printf("%s\n",errore);
            printf("DB: errore nel comando select, gruppi non trovati\n");
            PQclear(gruppi_db);
            gruppi_db = NULL;
        }
    }
    else
    {
        printf("DB: Database non trovato, gruppi non caricati\n");
    }

    disconnetti_db(miaconn);
    return gruppi_db;
}


int insert_utente_db(const char * const nome, const char * const password) {
    PGconn *miaconn;
    PGresult *exe;
    char comandoSQL[2000];
    char errore[1000];
    int flag = 0;

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"Insert into utente(nome, password) values ('%s', '%s')", nome, password);
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

int insert_membership_db(const char * const nome_utente, const char * const nome_gruppo) {
    PGconn *miaconn;
    PGresult *exe;
    char comandoSQL[2000];
    char errore[1000];
    int flag = 0;

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"Insert into membership(nome_utente, nome_gruppo) values ('%s', '%s')", nome_utente, nome_gruppo);
        exe = PQexec(miaconn, comandoSQL);
        strcpy(errore, PQresultErrorMessage(exe));
        if(strlen(errore) > 0)
        {
            printf("%s\n",errore);
            printf("DB: errore nel comando insert, membership non inserita\n");
        }
        else
        {
            printf("DB: membership inserita con successo\n");
            flag = 1;
        }
        PQclear(exe);
    }
    else
    {
        printf("DB: database non trovato, membership non inserita\n");
    }

    disconnetti_db(miaconn);
    return flag;
}

int insert_messaggio_db(const char * const nome_utente, const char * const nome_gruppo, const char * const  contenuto, const char * const minutaggio) {
    PGconn *miaconn;
    PGresult *exe;
    char comandoSQL[2000];
    char errore[1000];
    int flag = 0;

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"Insert into messaggio(nome_utente, nome_gruppo, contenuto, minutaggio) values ('%s', '%s', '%s', %s)", nome_utente, nome_gruppo, contenuto, minutaggio);
        exe = PQexec(miaconn, comandoSQL);
        strcpy(errore, PQresultErrorMessage(exe));
        if(strlen(errore) > 0)
        {
            printf("%s\n",errore);
            printf("DB: errore nel comando insert, messaggio non inserito\n");
        }
        else
        {
            printf("DB: messaggio inserito con successo\n");
            flag = 1;
        }
        PQclear(exe);
    }
    else
    {
        printf("DB: database non trovato, messaggio non inserito\n");
    }

    disconnetti_db(miaconn);
    return flag;
}

int insert_notifica_db(const char * const nome_utente, const char * const nome_gruppo) {
    PGconn *miaconn;
    PGresult *exe;
    char comandoSQL[2000];
    char errore[1000];
    int flag = 0;

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"Insert into notifica(nome_utente, nome_gruppo) values ('%s', '%s')", nome_utente, nome_gruppo);
        exe = PQexec(miaconn, comandoSQL);
        strcpy(errore, PQresultErrorMessage(exe));
        if(strlen(errore) > 0)
        {
            printf("%s\n",errore);
            printf("DB: errore nel comando insert, notifica non inserita\n");
        }
        else
        {
            printf("DB: notifica inserita con successo\n");
            flag = 1;
        }
        PQclear(exe);
    }
    else
    {
        printf("DB: database non trovato, notifica non inserita\n");
    }

    disconnetti_db(miaconn);
    return flag;
}

int delete_membership_db(const char * const nome_utente, const char * const nome_gruppo) {
    PGconn *miaconn;
    PGresult *exe;
    char comandoSQL[2000];
    char errore[1000];
    int flag = 0;

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"delete from membership where nome_utente = '%s' AND nome_gruppo = '%s'", nome_utente, nome_gruppo);
        exe = PQexec(miaconn, comandoSQL);
        strcpy(errore, PQresultErrorMessage(exe));
        if(strlen(errore) > 0)
        {
            printf("%s\n",errore);
            printf("DB: errore nel comando delete, membership non cancellata\n");
        }
        else
        {
            printf("DB: membership cancellata con successo\n");
            flag = 1;
        }
        PQclear(exe);
    }
    else
    {
        printf("DB: database non trovato, membership non cancellata\n");
    }

    disconnetti_db(miaconn);
    return flag;
}

int delete_notifica_db(const char * const nome_utente, const char * const nome_gruppo) {
    PGconn *miaconn;
    PGresult *exe;
    char comandoSQL[2000];
    char errore[1000];
    int flag = 0;

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"delete from notifica where nome_utente = '%s' AND nome_gruppo = '%s'", nome_utente, nome_gruppo);
        exe = PQexec(miaconn, comandoSQL);
        strcpy(errore, PQresultErrorMessage(exe));
        if(strlen(errore) > 0)
        {
            printf("%s\n",errore);
            printf("DB: errore nel comando delete, notifica non cancellata\n");
        }
        else
        {
            printf("DB: notifica cancellata con successo\n");
            flag = 1;
        }
        PQclear(exe);
    }
    else
    {
        printf("DB: database non trovato, notifica non cancellata\n");
    }

    disconnetti_db(miaconn);
    return flag;
}

PGresult *check_se_utente_registrato(const char* const nome, const char* const password) {
    PGconn *miaconn   = NULL;
    PGresult *utente_registrato_db = NULL;
    char comandoSQL[2000];
    char errore[1000];

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"select * from utente WHERE nome = '%s' AND password = '%s'", nome, password);
        utente_registrato_db = PQexec(miaconn, comandoSQL);
        strcpy(errore, PQresultErrorMessage(utente_registrato_db));
        if(strlen(errore) > 0)
        {
            printf("%s\n",errore);
            printf("DB: errore nel comando select, utente non trovato\n");
            PQclear(utente_registrato_db);
            utente_registrato_db = NULL;
        }
    }
    else
    {
        printf("DB: Database non trovato, utente non caricato\n");
    }

    disconnetti_db(miaconn);
    return utente_registrato_db;
}

PGresult *check_se_gruppo_registrato(const char* const nome) {
    PGconn *miaconn   = NULL;
    PGresult *utente_registrato_db = NULL;
    char comandoSQL[2000];
    char errore[1000];

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"select * from utente WHERE nome = '%s'", nome);
        utente_registrato_db = PQexec(miaconn, comandoSQL);
        strcpy(errore, PQresultErrorMessage(utente_registrato_db));
        if(strlen(errore) > 0)
        {
            printf("%s\n",errore);
            printf("DB: errore nel comando select, gruppo non trovato\n");
            PQclear(utente_registrato_db);
            utente_registrato_db = NULL;
        }
    }
    else
    {
        printf("DB: Database non trovato, gruppo non caricato\n");
    }

    disconnetti_db(miaconn);
    return utente_registrato_db;
}

PGresult *check_se_utente_amministratore(const char* const nome_utente, const char* const nome_gruppo) {
    PGconn *miaconn   = NULL;
    PGresult *utente_registrato_db = NULL;
    char comandoSQL[2000];
    char errore[1000];

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"select * from gruppo WHERE nome = '%s' AND amministratore = '%s'", nome_gruppo, nome_utente);
        utente_registrato_db = PQexec(miaconn, comandoSQL);
        strcpy(errore, PQresultErrorMessage(utente_registrato_db));
        if(strlen(errore) > 0)
        {
            printf("%s\n",errore);
            printf("DB: errore nel comando select, gruppi non trovati\n");
            PQclear(utente_registrato_db);
            utente_registrato_db = NULL;
        }
    }
    else
    {
        printf("DB: Database non trovato, gruppi non caricati\n");
    }

    disconnetti_db(miaconn);
    return utente_registrato_db;
}

PGresult *check_se_utente_connesso(const char * const nome_utente) {
    PGconn *miaconn   = NULL;
    PGresult *utente_registrato_db = NULL;
    char comandoSQL[2000];
    char errore[1000];

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"select * from utente WHERE nome = '%s'", nome_utente);
        utente_registrato_db = PQexec(miaconn, comandoSQL);
        strcpy(errore, PQresultErrorMessage(utente_registrato_db));
        if(strlen(errore) > 0)
        {
            printf("%s\n",errore);
            printf("DB: errore nel comando select, utente non trovato\n");
            PQclear(utente_registrato_db);
            utente_registrato_db = NULL;
        }
    }
    else
    {
        printf("DB: Database non trovato, utente non caricato\n");
    }

    disconnetti_db(miaconn);
    return utente_registrato_db;
}

int update_stato_connessione_utente(const char * const nome, const int socket) {
    PGconn *miaconn;
    PGresult *exe;
    char comandoSQL[2000];
    char errore[1000];
    int flag = 0;

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"Update utente set connessione = %d where nome = '%s'", socket, nome);
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


void stampa_result_query(PGresult *result_query) {
    char errore[1000];
    int num_tuple = 0;
    int num_field = 0;

    strcpy(errore, PQresultErrorMessage(result_query));

    if(strlen(errore) > 0)
    {
        printf("%s\n",errore);
        printf("DB: questa result query ha degli errori\n");
    }
    else
    {
        num_tuple = PQntuples(result_query);
        num_field = PQnfields(result_query);
        printf("numero di tuple: %d\n", num_tuple );
        printf("numero di field: %d\n", num_field );
        for (int i = 0; i < num_tuple; i++)
        {
            for (int j = 0; j < num_field; j++)
            {
                printf("%s ", PQgetvalue(result_query, i, j));
            }
            puts("");
        }
    }
}