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

PGresult *select_gruppi_db() {
    PGconn *miaconn   = NULL;
    PGresult *gruppi_db = NULL;
    char comandoSQL[2000];
    char errore[1000];

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"select * from gruppo ORDER BY gruppo_id");
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

PGresult *select_utenti_db() {
    PGconn *miaconn   = NULL;
    PGresult *utenti_db = NULL;
    char comandoSQL[2000];
    char errore[1000];

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"select * from utente ORDER BY utente_id");
        utenti_db = PQexec(miaconn, comandoSQL);
        strcpy(errore, PQresultErrorMessage(utenti_db));
        if(strlen(errore) > 0)
        {
            printf("%s\n",errore);
            printf("DB: errore nel comando select, gruppi non trovati\n");
            PQclear(utenti_db);
            utenti_db = NULL;
        }
    }
    else
    {
        printf("DB: Database non trovato, gruppi non caricati\n");
    }

    disconnetti_db(miaconn);
    return utenti_db;
}

PGresult *select_membership_db() {
    PGconn *miaconn   = NULL;
    PGresult *member_db = NULL;
    char comandoSQL[2000];
    char errore[1000];

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"select * from membership ORDER BY utente_id");
        member_db = PQexec(miaconn, comandoSQL);
        strcpy(errore, PQresultErrorMessage(member_db));
        if(strlen(errore) > 0)
        {
            printf("%s\n",errore);
            printf("DB: errore nel comando select, membri dei gruppi non trovati\n");
            PQclear(member_db);
            member_db = NULL;
        }
    }
    else
    {
        printf("DB: Database non trovato, membri dei gruppi non caricati\n");
    }

    disconnetti_db(miaconn);
    return member_db;
}

PGresult *select_messaggi_db() {
    PGconn *miaconn   = NULL;
    PGresult *messaggi_db = NULL;
    char comandoSQL[2000];
    char errore[1000];

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"select * from messaggio ORDER BY gruppo_id, minutaggio");
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

PGresult *select_notifiche_db() {
    PGconn *miaconn   = NULL;
    PGresult *notifiche_db = NULL;
    char comandoSQL[2000];
    char errore[1000];

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"select * from notifica ORDER BY gruppo_id");
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

int insert_gruppo_db(const int gruppo_id, const char * const nome, const int amministratore_id) {
    PGconn *miaconn;
    PGresult *exe;
    char comandoSQL[2000];
    char errore[1000];
    int flag = 0;

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"Insert into gruppo(gruppo_id, nome, amministratore_id) values (%d, '%s', %d)", gruppo_id, nome, amministratore_id);
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

int insert_utente_db(const int utente_id, const char * const nome, const char * const password) {
    PGconn *miaconn;
    PGresult *exe;
    char comandoSQL[2000];
    char errore[1000];
    int flag = 0;

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"Insert into utente(utente_id, nome, password) values (%d, '%s', '%s')", utente_id, nome, password);
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

int insert_membership_db(const int utente_id, const int gruppo_id) {
    PGconn *miaconn;
    PGresult *exe;
    char comandoSQL[2000];
    char errore[1000];
    int flag = 0;

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"Insert into membership(utente_id, gruppo_id) values (%d, %d)", utente_id, gruppo_id);
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

int insert_messaggio_db(const int mittente_id, const int gruppo_id, char * contenuto, const long long int minutaggio) {
    PGconn *miaconn;
    PGresult *exe;
    char comandoSQL[2000];
    char errore[1000];
    int flag = 0;

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"Insert into messaggio(mittente_id, gruppo_id, contenuto, minutaggio) values (%d, %d, %d, %lld)", mittente_id, gruppo_id, contenuto, minutaggio);
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

int insert_notifica_db(const int utente_notificante_id, const int gruppo_id) {
    PGconn *miaconn;
    PGresult *exe;
    char comandoSQL[2000];
    char errore[1000];
    int flag = 0;

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"Insert into notifica(utente_notificante_id, gruppo_id,) values (%d, %d)", utente_notificante_id, gruppo_id);
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

int delete_membership_db(const int utente_id, const int gruppo_id) {
    PGconn *miaconn;
    PGresult *exe;
    char comandoSQL[2000];
    char errore[1000];
    int flag = 0;

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"delete from membership where utente_id = %d AND gruppo_id = %d", utente_id, gruppo_id);
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

int delete_notifica_db(const int utente_notificante_id, const int gruppo_id) {
    PGconn *miaconn;
    PGresult *exe;
    char comandoSQL[2000];
    char errore[1000];
    int flag = 0;

    miaconn = connetti_db(CONNSTRINGA);

    if(miaconn != NULL)
    {
        sprintf(comandoSQL,"delete from notifica where utente_notificante_id = %d AND gruppo_id = %d", utente_notificante_id, gruppo_id);
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

int check_se_registrato(const char* const nome, const char* const password) {
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