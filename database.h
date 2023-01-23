#ifndef DATABASE_H
#define DATABASE_H

#include <libpq-fe.h>

#define CONNSTRINGA "user=postgres password=1234 dbname=multichat"

PGconn* connetti_db(const char* const connstring);
void disconnetti_db(PGconn* conn);

PGresult *select_gruppi_utente(const char * const nome_utente);
PGresult *select_messaggi_gruppi_utente(const char * const nome_gruppo);
PGresult *select_notifiche_gruppi_utente(const char * const nome_gruppo);

int insert_gruppo_db(const char * const nome, const char * const amministratore);
int insert_utente_db(const char * const nome, const char * const password);
int insert_membership_db(const char * const nome_utente, const char * const nome_gruppo);
int insert_messaggio_db(const char * const nome_utente, const char * const nome_gruppo, const char * const  contenuto, const long long int minutaggio);
int insert_notifica_db(const char * const nome_utente, const char * const nome_gruppo);

int delete_membership_db(const char * const nome_utente, const char * const nome_gruppo);
int delete_notifica_db(const char * const nome_utente, const char * const nome_gruppo);

PGresult *check_se_utente_registrato(const char* const nome, const char* const password);
PGresult *check_se_gruppo_registrato(const char* const nome);
PGresult *check_se_utente_amministratore(const char* const nome_utente, const char* const nome_gruppo);

int update_stato_connessione_utente(const char * const nome, const int socket);

void stampa_result_query(PGresult *result_query);

#endif