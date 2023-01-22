#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <libpq-fe.h>

#include "strutture_dati.h"
#include "database.h"

int avvia_dati(gruppi *Gruppi, utenti *Utenti) {
    PGresult *gruppi_db;
    PGresult *utenti_db;
    PGresult *membership_db;
    PGresult *messaggi_db;
    PGresult *notifiche_db;

    dealloca_gruppi(Gruppi);
    dealloca_utenti(Utenti);

    gruppi_db = select_gruppi_db();
    utenti_db = select_utenti_db();
    membership_db = select_membership_db();
    messaggi_db = select_messaggi_db();
    notifiche_db = select_notifiche_db();

    int flag = 0;

    if (gruppi_db == NULL || utenti_db == NULL || membership_db == NULL || messaggi_db == NULL || notifiche_db == NULL) {
        return 0;
    }

    avvia_gruppi(Gruppi, gruppi_db);
    avvia_utenti(Utenti, utenti_db);
    avvia_membership(Gruppi, Utenti, membership_db);
    avvia_messaggi(Gruppi, messaggi_db);
    avvia_notifica(Gruppi, gruppi_db);    
}

int avvia_gruppi(gruppi *Gruppi, PGresult *gruppi_db) {
    
    int num_tuple;
    int max_gruppo_id;

    int gruppo_id;

    gruppo * gruppo_pt;

    if (Gruppi = NULL || gruppi_db == NULL) {
        return 0;
    }

    num_tuple = PQntuples(gruppi_db);
    max_gruppo_id = atoi(PQgetvalue(gruppi_db, num_tuple - 1, 1));

    inizializza_gruppi(max_gruppo_id);

    for (int i = 0; i < num_tuple; i++) {
        gruppo_pt = inizializza_gruppo(PQgetvalue(gruppi_db, i, 2), atoi(PQgetvalue(gruppi_db, i, 3)));
        Gruppi->array_gruppi[atoi(PQgetvalue(gruppi_db, i, 1))] = gruppo_pt;
    }
}

int avvia_utenti(utenti *Utenti, PGresult *utenti_db) {
    int num_tuple;
    int max_utente_id;

    int utente_id;

    utente * gruppo_pt;

    if (Utenti = NULL || utenti_db == NULL) {
        return 0;
    }

    num_tuple = PQntuples(utenti_db);
    max_utente_id = atoi(PQgetvalue(utenti_db, num_tuple - 1, 1));

    inizializza_gruppi(max_utente_id);

    for (int i = 0; i < num_tuple; i++) {
        gruppo_pt = inizializza_gruppo(PQgetvalue(utenti_db, i, 2), atoi(PQgetvalue(utenti_db, i, 3)));
        Utenti->array_utenti[atoi(PQgetvalue(utenti_db, i, 1))] = gruppo_pt;
    }
}

int avvia_membership(gruppi *Gruppi, utenti *Utenti, PGresult *membership_db) {

}

int avvia_messaggi(gruppi *Gruppi, PGresult *messaggi_db) {

}

int avvia_notifica(gruppi *Gruppi, PGresult *gruppi_db) {

}
