#ifndef DATABASE_H
#define DATABASE_H

#include <libpq-fe.h>

#define CONNSTRINGA "user=postgres password=1234 dbname=multichat"

PGconn* connetti_db(const char* const connstring);
void disconnetti_db(PGconn* conn);
int inserisci_utente_db(const char* const nome, const char* const password, const char const modo);
int check_se_registrato(const char* const nome, const char* const password, const char const modo);
int stampa_result_query(const char * const comandoSQL);
grafo_citta *carica_grafo_db();
int inserisci_notifica_db(const int partenza_id, const int arrivo_id);
int cancella_notifiche_db();
int cancella_notifica_db(const int id_partenza, const int id_arrivo);

#endif