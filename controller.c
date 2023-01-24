#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <libpq-fe.h>

#include "gestore_pacchetti.h"
#include "database.h"
#include "controller.h"

char *alloca_pacchetto() {
    return malloc(PACCHETT0_LEN*sizeof(char));
}

void dealloca_pacchetto(char * pacchetto) {
    free(pacchetto);
}

void processa(const char * const pacchetto, const * pacchetto_da_spedire, int ** array_socket, int * dim) {
    int comando;

    comando = parse_comando(pacchetto);
    pacchetto_da_spedire = alloca_pacchetto;

    if (comando == LOGIN) {
        processa_login(pacchetto, pacchetto_da_spedire, array_socket, dim);
    }
    else if (comando == SIGNIN) {
        processa_signin(pacchetto, pacchetto_da_spedire, array_socket, dim);
    }
    else if (comando == CREAGRUP) {
        processa_crea_gruppo(pacchetto, pacchetto_da_spedire, array_socket, dim);
    }
    else if (comando == SENDMESS) {
        processa_messaggio(pacchetto, pacchetto_da_spedire, array_socket, dim);
    }
    else if (comando == ACCETTAUT) {
        processa_acc(pacchetto, pacchetto_da_spedire, array_socket, dim);
    }
    else {
        processa_pacchetto_non_riconosciuto(pacchetto, pacchetto_da_spedire, array_socket, dim);
    }
}

void processa_login(const char * const pacchetto, char * const pacchetto_da_spedire, int ** array_socket, int * dim) {
    PGresult *utente_registrato;

    char * nome;
    char * password;
    parse_login(pacchetto, nome, password);

    utente_registrato = check_se_utente_registrato(nome, password);
    //errore DB
    if (utente_registrato == NULL) {
        format_login_risposta(LOGINERR, pacchetto_da_spedire);
    }
    else {
        // se non registrato 
        if (PQntuples(utente_registrato == 0)) {
            format_login_risposta(LOGINNONTROVATO, pacchetto_da_spedire);
        }
        // se registrato
        else {
            // aggiungo i gruppi dell'utente
            PGresult * gruppi_utente;
            PGresult * messaggi_gruppi_utente;
            PGresult * notifiche_gruppi_utente;

            char nome_gruppo[100];

            char nome_mittente_messaggio[100];
            char contenuto_messaggio[1000];
            char minutaggio_messaggio[20];
            
            char nome_notificante[100];

            int num_gruppi_utente;
            int num_messaggi_gruppo;
            int num_notifiche_gruppo;

            format_login_risposta(LOGINOK, pacchetto_da_spedire);

            gruppi_utente = select_gruppi_utente(nome);
            num_gruppi_utente = PQntuples(gruppi_utente);

            format_add_inizio_gruppi(pacchetto_da_spedire);
            // aggiungi i gruppi
            for (int i = 0; i < num_gruppi_utente; i++) {
                strcpy(nome_gruppo, PQgetvalue(gruppi_utente, i, 0));

                format_add_nome_gruppo(pacchetto_da_spedire);

                messaggi_gruppi_utente = select_messaggi_gruppo_utente(nome_gruppo);
                num_messaggi_gruppo = PQntuples(messaggi_gruppi_utente);

                format_add_inizio_messaggi(pacchetto_da_spedire);
                // aggiungi i messaggi
                for (int j = 0; j < num_messaggi_gruppo; j++) {
                    strcpy(nome_mittente_messaggio, PQgetvalue(messaggi_gruppi_utente, j, 1));
                    strcpy(contenuto_messaggio, PQgetvalue(contenuto_messaggio, j, 3));
                    strcpy(minutaggio_messaggio, PQgetvalue(contenuto_messaggio, j, 4));

                    format_add_mittente_messaggio(pacchetto_da_spedire, nome_mittente_messaggio);
                    format_add_contenuto_messaggio(pacchetto_da_spedire, contenuto_messaggio);
                    format_add_minutaggio_messaggio(pacchetto_da_spedire, minutaggio_messaggio);
                }

                PQclear(messaggi_gruppi_utente);

                format_add_fine_messaggi(pacchetto_da_spedire);

                notifiche_gruppi_utente = select_notifiche_gruppo_utente(nome_gruppo);
                num_notifiche_gruppo = PQntuples(notifiche_gruppi_utente);

                format_add_inizio_notifiche(pacchetto_da_spedire);
                // aggiunti le notifiche
                for (int k = 0; k < num_messaggi_gruppo; k++) {
                    strcpy(nome_notificante, PQgetvalue(notifiche_gruppi_utente, k, 0));

                    format_add_notificante(pacchetto_da_spedire, nome_notificante);
                }

                PQclear(notifiche_gruppi_utente);

                format_add_fine_notifiche(pacchetto_da_spedire);

            }
            PQclear(gruppi_utente);

            format_add_fine_gruppi(pacchetto_da_spedire);
        }
    }

    PQclear(utente_registrato); 

    return pacchetto_da_spedire;
}

void processa_signin(const char * const pacchetto, char * const pacchetto_da_spedire, int ** array_socket, int * dim) {
    PGresult *utente_registrato;
    int inserito = 0;

    char * nome;
    char * password;
    parse_login(pacchetto, nome, password);
    utente_registrato = check_se_utente_registrato(nome, password);
    //errore DB
    if (utente_registrato == NULL) {
        format_signin_risposta(SIGNINERR, pacchetto_da_spedire);
    }
    else {
        inserito = insert_utente_db(nome, password);
        //errore DB
        if (inserito  == 0) {
            format_signin_risposta(SIGNINERR, pacchetto_da_spedire);
        }
        else {
            // se utente guà registrato
            if (PQntuples(utente_registrato == 1)) {
                format_signin_risposta(SIGNGIAREGISTRATO, pacchetto_da_spedire);
            }
            // se non ancora registrato
            else {
                format_signin_risposta(SIGNINOK, pacchetto_da_spedire);
            }
        }
    }
}

void processa_crea_gruppo(const char * const pacchetto, char * const pacchetto_da_spedire, int ** array_socket, int * dim) {
    PGresult *gruppo_registrato = 0;
    int inserito = 0;

    char * nome_gruppo;
    char * nome_utente;

    parse_crea_gruppo(pacchetto, nome_gruppo, nome_utente);

    gruppo_registrato = check_se_gruppo_registrato(nome_gruppo);
    //errore DB
    if (gruppo_registrato == NULL) {
        format_crea_gruppo_risposta(CREAGRUPERR, pacchetto_da_spedire);
    }
    else {
        inserito = insert_gruppo_db(nome_gruppo, nome_utente);
        // errore DB
        if (inserito == 0) {
            format_crea_gruppo_risposta(CREAGRUPERR, pacchetto_da_spedire);
        }
        else {
            // gruppo già esistente
            if (PQntuples(gruppo_registrato == 1)) {
                format_crea_gruppo_risposta(CREAGRUPGIAREGISTRATO, pacchetto_da_spedire);
            }
            // se non ancora registrato
            else {
                format_crea_gruppo_risposta(CREAGRUPOK, pacchetto_da_spedire);
            }
        }
    }
}

void processa_messaggio(const char * const pacchetto, char * const pacchetto_da_spedire, int ** array_socket, int * dim) {
    PGresult * utenti_connessi;
    int inserito = 0;

    char * nome_gruppo;
    char * nome_utente;
    char * contenuto;
    char * minutaggio;

    parse_messaggio(pacchetto, nome_gruppo, nome_utente, contenuto, minutaggio);
    inserito = insert_messaggio_db(nome_utente, nome_gruppo, contenuto, minutaggio);
    if (inserito == 0) {
        format_messaggio_risposta(SENDMESSERR, pacchetto_da_spedire);
    }
    else {
        format_messaggio_risposta(SENDMESSOK, pacchetto_da_spedire);
        format_add_nome_gruppo(pacchetto_da_spedire, nome_gruppo);
        format_add_inizio_messaggi(pacchetto_da_spedire);
        format_add_mittente_messaggio(pacchetto_da_spedire, nome_utente);
        format_add_contenuto_messaggio(pacchetto_da_spedire, contenuto);
        format_add_minutaggio_messaggio(pacchetto_da_spedire, minutaggio);
        format_add_fine_messaggi(pacchetto_da_spedire);
    }
}

char *processa_accetta_notifica(const char * const pacchetto, char * const pacchetto_da_spedire, int ** array_socket, int * dim) {
    char * nome_gruppo;
    char * nome_utente;
    parse_accetta_notifica(pacchetto, nome_utente, nome_gruppo);
    
}

char *processa_pacchetto_non_riconosciuto(const char * const pacchetto, char * const pacchetto_da_spedire, int ** array_socket, int * dim) {
    format_pacchetto_non_riconosciuto(PACCHETTONONCOMPRESO, pacchetto_da_spedire);
}
