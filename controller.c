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
        pacchetto_da_spedire = processa_singin(pacchetto, array_socket, dim);
    }
    if (comando == CREAGRUP) {
        pacchetto_da_spedire = processa_crea_gruppo(pacchetto, array_socket, dim);
    }
    if (comando == SENDMESS) {
        pacchetto_da_spedire = processa_messaggio(pacchetto, array_socket, dim);
    }
    if (comando == ACCETTAUT) {
        pacchetto_da_spedire = processa_accetta_notifica(pacchetto, array_socket, dim);
    }
}

char *processa_login(const char * const pacchetto, int ** array_socket, int * dim) {
    char * nome;
    char * password;
    parse_login(pacchetto, nome, password);
    check_se_utente_registrato(nome, password);
}

char *processa_signin(const char * const pacchetto, int ** array_socket, int * dim) {
    char * nome;
    char * password;
    parse_signin(pacchetto, nome, password);
}

char *processa_crea_gruppo(const char * const pacchetto, int ** array_socket, int * dim) {
    char * nome_gruppo;
    char * nome_utente;
    parse_crea_gruppo(pacchetto, nome_gruppo, nome_utente);
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
