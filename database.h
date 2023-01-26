#ifndef DATABASE_H
#define DATABASE_H

#include <libpq-fe.h>

#define CONNSTRINGA "user=postgres password=1234 dbname=multichat"

PGconn* connetti_db(const char* const connstring);
void disconnetti_db(PGconn* conn);

//restituisce tutti i gruppi a cui appartiene l'utente
PGresult *select_gruppi_utente(const char * const nome_utente);
PGresult *select_messaggi_gruppo_utente(const char * const nome_gruppo);
PGresult *select_notifiche_gruppo_utente(const char * const nome_gruppo);
PGresult *select_utenti_connessi();
PGresult *select_gruppi_senza_utente(const char * const nome_utente);
PGresult *select_socket_gruppo (const char * const nome_gruppo, const char * const nome_utente);
PGresult *select_utente (const char * const nome_utente);

int insert_gruppo_db(const char * const nome, const char * const amministratore);
int insert_utente_db(const char * const nome, const char * const password);
int insert_membership_db(const char * const nome_utente, const char * const nome_gruppo);
int insert_messaggio_db(const char * const nome_utente, const char * const nome_gruppo, const char * const  contenuto, const char * const minutaggio);
int insert_notifica_db(const char * const nome_utente, const char * const nome_gruppo);

int delete_membership_db(const char * const nome_utente, const char * const nome_gruppo);
int delete_notifica_db(const char * const nome_utente, const char * const nome_gruppo);

PGresult *check_se_utente_registrato(const char* const nome, const char* const password);
PGresult *check_se_gruppo_registrato(const char* const nome);
PGresult *check_se_utente_amministratore(const char* const nome_utente, const char* const nome_gruppo);
PGresult *check_se_utente_connesso(const char * const nome_utente);

int update_stato_connessione_utente(const char * const nome, const int socket);

void stampa_result_query(PGresult *result_query);

#endif