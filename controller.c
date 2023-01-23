#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <libpq-fe.h>

#include "gestore_pacchetti.h"
#include "database.h"

char *processa(const char * const pacchetto, int ** array_socket, int * dim) {
    char * pacchetto_da_spedire;
    int comando;

    comando = parse_comando(pacchetto);

    if (comando == LOGIN) {
        pacchetto_da_spedire = processa_login(pacchetto, array_socket, dim);
    }
    if (comando == SIGNIN) {
        pacchetto_da_spedire = processa_signin(pacchetto, array_socket, dim);
    }
    if (comando == CREAGRUP) {
        pacchetto_da_spedire = processa_crea_gruppo(pacchetto, array_socket, dim);
    }
    if (comando == SENDMESS) {
        pacchetto_da_spedire = processa_messaggio(pacchetto, array_socket, dim);
    }
    if (comando == ACCETTAUT) {
        pacchetto_da_spedire = processa_acc(pacchetto, array_socket, dim);
    }
}

char *processa_login(const char * const pacchetto, int ** array_socket, int * dim) {
    PGresult *utente_registrato;
    char * pacchetto_da_spedire;

    char * nome;
    char * password;
    parse_login(pacchetto, nome, password);
    utente_registrato = check_se_utente_registrato(nome, password);
    //errore DB
    if (utente_registrato == NULL) {
        pacchetto_da_spedire = format_login_risposta(LOGINERR);
    }
    else {
        // se registrato
        if (PQntuples(utente_registrato == 1)) {
            pacchetto_da_spedire = format_login_risposta(LOGINOK);
        }
        // se non registrato 
        else {
            pacchetto_da_spedire = format_login_risposta(LOGINNONTROVATO);
        }
    }

    return pacchetto_da_spedire;
}

char *processa_signin(const char * const pacchetto, int ** array_socket, int * dim) {
    PGresult *utente_registrato;
    int inserito = 0;
    char * pacchetto_da_spedire;

    char * nome;
    char * password;
    parse_login(pacchetto, nome, password);
    utente_registrato = check_se_utente_registrato(nome, password);
    //errore DB
    if (utente_registrato == NULL) {
        pacchetto_da_spedire = format_signin_risposta(SIGNINERR);
    }
    else {
        inserito = insert_utente_db(nome, password);
        //errore DB
        if (inserito  == 0) {
            pacchetto_da_spedire = format_signin_risposta(SIGNINERR);
        }
        else {
            // se utente guà registrato
            if (PQntuples(utente_registrato == 1)) {
                pacchetto_da_spedire = format_signin_risposta(SIGNGIAREGISTRATO);
            }
            // se non ancora registrato
            else {
                pacchetto_da_spedire = format_signin_risposta(SIGNINOK);
            }
        }
    }


    return pacchetto_da_spedire;
}

char *processa_crea_gruppo(const char * const pacchetto, int ** array_socket, int * dim) {
    PGresult *gruppo_registrato = 0;
    int inserito = 0;
    char * pacchetto_da_spedire;

    char * nome_gruppo;
    char * nome_utente;

    parse_crea_gruppo(pacchetto, nome_gruppo, nome_utente);

    gruppo_registrato = check_se_gruppo_registrato(nome_gruppo);
    //errore DB
    if (gruppo_registrato == NULL) {
        format_crea_gruppo_risposta(CREAGRUPERR);
    }
    else {
        inserito = insert_gruppo_db(nome_gruppo, nome_utente);
        // errore DB
        if (inserito == 0) {
            format_crea_gruppo_risposta(CREAGRUPERR);
        }
        else {
            // gruppo già esistente
            if (PQntuples(gruppo_registrato == 1)) {
                pacchetto_da_spedire = format_crea_gruppo_risposta(CREAGRUPGIAREGISTRATO);
            }
            // se non ancora registrato
            else {
                pacchetto_da_spedire = format_crea_gruppo_risposta(CREAGRUPOK);
            }
        }
    }
}

char *processa_messaggio(const char * const pacchetto, int ** array_socket, int * dim) {
    char * nome_gruppo;
    char * nome_utente;
    char * contenuto;
    parse_messaggio(pacchetto, nome_gruppo, nome_utente, contenuto);
}

char *processa_accetta_notifica(const char * const pacchetto, int ** array_socket, int * dim) {
    char * nome_gruppo;
    char * nome_utente;
    parse_accetta_notifica(pacchetto, nome_utente, nome_gruppo);
}
