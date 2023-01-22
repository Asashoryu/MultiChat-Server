#ifndef DATABASE_H
#define DATABASE_H

#include <libpq-fe.h>

#define CONNSTRINGA "user=postgres password=1234 dbname=multichat"

PGconn* connetti_db(const char* const connstring);
void disconnetti_db(PGconn* conn);

PGresult *select_gruppi_db();
PGresult *select_utenti_db();
PGresult *select_membership_db();
PGresult *select_messaggi_db();
PGresult *select_notifiche_db();

int insert_gruppo_db(const int gruppo_id, const char * const nome, const int amministratore_id);
int insert_utente_db(const int utente_id, const char * const nome, const char * const password);
int insert_membership_db(const int utente_id, const int gruppo_id);
int insert_messaggio_db(const int mittente_id, const int gruppo_id, char * contenuto, const long long int minutaggio);
int insert_notifica_db(const int utente_notificante_id, const int gruppo_id);

int delete_membership_db(const int utente_id, const int gruppo_id);
int delete_notifica_db(const int utente_notificante_id, const int gruppo_id);

int check_se_registrato(const char* const nome, const char* const password);

void stampa_result_query(PGresult *result_query);

#endif