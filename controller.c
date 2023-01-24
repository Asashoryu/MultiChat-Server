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

void processa_login(const char * const pacchetto, char * const pacchetto_da_spedire, int ** array_socket, int * dim) {
    PGresult *utente_registrato;

    char * nome;
    char * password;
    alloca_login(&nome, &password);
    parse_login(pacchetto, nome, password);
    printf(" 1");
    utente_registrato = check_se_utente_registrato(nome, password);
    printf(" 2");
    //errore DB
    if (utente_registrato == NULL) {
        format_login_risposta(LOGINERR, pacchetto_da_spedire);
    }
    else {
        printf(" 3");
        // se non registrato 
        if (PQntuples(utente_registrato) == 0) {
            format_login_risposta(LOGINNONTROVATO, pacchetto_da_spedire);
        }
        // se registrato
        else {
            printf(" 4");
            // aggiungo i gruppi dell'utente
            PGresult * gruppi_utente;
            PGresult * messaggi_gruppi_utente;
            PGresult * notifiche_gruppi_utente;

            char nome_gruppo[100];
            char nome_notificante[100];

            int num_gruppi_utente;
            int num_messaggi_gruppo;
            int num_notifiche_gruppo;
            printf(" 5");
            format_login_risposta(LOGINOK, pacchetto_da_spedire);
            printf(" 6");
            gruppi_utente = select_gruppi_utente(nome);
            printf(" 7");
            num_gruppi_utente = PQntuples(gruppi_utente);
            printf(" 8");

            format_add_inizio_gruppi(pacchetto_da_spedire);
            printf(" 9");
            // aggiungi i gruppi
            for (int i = 0; i < num_gruppi_utente; i++) {
                strcpy(nome_gruppo, PQgetvalue(gruppi_utente, i, 0));
                printf(" 10");

                format_add_nome_gruppo(pacchetto_da_spedire, nome_gruppo);
                printf(" 11");

                messaggi_gruppi_utente = select_messaggi_gruppo_utente(nome_gruppo);
                printf(" 12");
                num_messaggi_gruppo = PQntuples(messaggi_gruppi_utente);
                printf(" 13");

                format_add_inizio_messaggi(pacchetto_da_spedire);
                printf(" 14");
                // aggiungi i messaggi
                for (int j = 0; j < num_messaggi_gruppo; j++) {
                    format_add_mittente_messaggio(pacchetto_da_spedire, PQgetvalue(messaggi_gruppi_utente, j, 1));
                    format_add_contenuto_messaggio(pacchetto_da_spedire, PQgetvalue(messaggi_gruppi_utente, j, 3));
                    format_add_minutaggio_messaggio(pacchetto_da_spedire, PQgetvalue(messaggi_gruppi_utente, j, 4));
                }
                printf(" 15");

                PQclear(messaggi_gruppi_utente);

                format_add_fine_messaggi(pacchetto_da_spedire);
                printf(" 16");

                notifiche_gruppi_utente = select_notifiche_gruppo_utente(nome_gruppo);
                printf(" 17");
                num_notifiche_gruppo = PQntuples(notifiche_gruppi_utente);

                format_add_inizio_notifiche(pacchetto_da_spedire);
                printf(" 18");
                // aggiunti le notifiche
                for (int k = 0; k < num_messaggi_gruppo; k++) {
                    format_add_notificante(pacchetto_da_spedire, PQgetvalue(notifiche_gruppi_utente, k, 0));
                    format_add_gruppo_notificato(pacchetto_da_spedire, nome_gruppo);
                }

                PQclear(notifiche_gruppi_utente);
                printf(" 19");

                format_add_fine_notifiche(pacchetto_da_spedire);

            }
            PQclear(gruppi_utente);

            format_add_fine_gruppi(pacchetto_da_spedire);
        }
    }

    PQclear(utente_registrato); 
    dealloca_login(&nome, &password);
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
            if (PQntuples(utente_registrato) == 1) {
                format_signin_risposta(SIGNGIAREGISTRATO, pacchetto_da_spedire);
            }
            // se non ancora registrato
            else {
                format_signin_risposta(SIGNINOK, pacchetto_da_spedire);
            }
        }
    }

    PQclear(utente_registrato);
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
        // gruppo già esistente
        if (PQntuples(gruppo_registrato) == 1) {
            format_crea_gruppo_risposta(CREAGRUPGIAREGISTRATO, pacchetto_da_spedire);
        }
        else {
            inserito = insert_gruppo_db(nome_gruppo, nome_utente);
            // errore DB
            if (inserito == 0) {
                format_crea_gruppo_risposta(CREAGRUPERR, pacchetto_da_spedire);
            }
            // se non ancora registrato
            else {
                format_crea_gruppo_risposta(CREAGRUPOK, pacchetto_da_spedire);
            }
        }
    }

    PQclear(gruppo_registrato);
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

    PQclear(utenti_connessi);
}

char *processa_cerca_gruppo(const char * const pacchetto, char * const pacchetto_da_spedire, int ** array_socket, int * dim) {
    PGresult *gruppi_trovati;
    char * nome_utente;
    char * nome_gruppo;

    parse_cerca_gruppo(pacchetto_da_spedire, nome_utente, nome_gruppo);

    gruppi_trovati = select_gruppi_senza_utente(nome_utente, nome_gruppo);
    if (gruppi_trovati == NULL) {
        format_cerca_gruppo(SEARCHGRUPERR, pacchetto_da_spedire);
    }
    else {
        format_cerca_gruppo(SEARCHGRUPOK, pacchetto_da_spedire);
        format_add_inizio_gruppi(pacchetto_da_spedire);
        for (int i = 0; i < PQntuples(gruppi_trovati); i++) {
            format_add_nome_gruppo(pacchetto_da_spedire, PQgetvalue(gruppi_trovati, i, 0));
        }
        format_add_fine_gruppi(pacchetto_da_spedire);
    }

    PQclear(gruppi_trovati);
}

char * processa_manda_notifica(const char * const pacchetto, char * const pacchetto_da_spedire, int ** array_socket, int * dim) {
    int inserito;

    char * nome_utente;
    char * nome_gruppo;
    parse_manda_notifica(pacchetto_da_spedire, nome_utente, nome_gruppo);
    
    inserito = insert_notifica_db(nome_utente, nome_gruppo);
    if (inserito == 0) {
        format_manda_notifica(SENDNOTIFICAERR, pacchetto_da_spedire);
    }
    else {
        format_manda_notifica(SENDNOTIFICA, pacchetto_da_spedire);
        format_add_inizio_notifiche(pacchetto_da_spedire);
        format_add_gruppo_notificato(pacchetto_da_spedire, nome_gruppo);
        format_add_fine_notifiche(pacchetto_da_spedire);
    }
}

char *processa_accetta_notifica(const char * const pacchetto, char * const pacchetto_da_spedire, int ** array_socket, int * dim) {
    PGresult *messaggi_gruppo;
    int rimossa = 0;
    int inserito = 0;

    char * nome_gruppo;
    char * nome_utente;
    char * nome_richiedente;

    parse_accetta_notifica(pacchetto, nome_utente, nome_gruppo, nome_richiedente);

    inserito = insert_membership_db(nome_richiedente, nome_gruppo);
    
    if (inserito == 0) {
        format_accetta_notifica(ACCETTAUTERR, pacchetto_da_spedire);
    }
    else {
        rimossa = delete_notifica_db(nome_richiedente, nome_gruppo);
        if (rimossa == 0) {
            format_accetta_notifica(ACCETTAUTERR, pacchetto_da_spedire);
        }
        else {
            messaggi_gruppo = select_messaggi_gruppo_utente(nome_gruppo);
            format_accetta_notifica(ACCETTAUTOK, pacchetto_da_spedire);

            format_add_inizio_gruppi(pacchetto_da_spedire);

            format_add_nome_gruppo(pacchetto_da_spedire, nome_gruppo);
            format_add_inizio_messaggi(pacchetto_da_spedire);

            // aggiungi i messaggi
            for (int j = 0; j < PQntuples(messaggi_gruppo); j++) {
                format_add_mittente_messaggio(pacchetto_da_spedire, PQgetvalue(messaggi_gruppo, j, 1));
                format_add_contenuto_messaggio(pacchetto_da_spedire, PQgetvalue(messaggi_gruppo, j, 3));
                format_add_minutaggio_messaggio(pacchetto_da_spedire, PQgetvalue(messaggi_gruppo, j, 4));
            }

            format_add_fine_messaggi(pacchetto_da_spedire);

            format_add_fine_gruppi(pacchetto_da_spedire);

            PQclear(messaggi_gruppo);
        }
    }
}

char *processa_pacchetto_non_riconosciuto(const char * const pacchetto, char * const pacchetto_da_spedire, int ** array_socket, int * dim) {
    format_pacchetto_non_riconosciuto(PACCHETTONONCOMPRESO, pacchetto_da_spedire);
}

void processa(const char * const pacchetto, char *  pacchetto_da_spedire, int ** array_socket, int * dim) {
    int comando;

    comando = parse_comando(pacchetto);
    pacchetto_da_spedire = alloca_pacchetto();

    if (comando == LOGIN) {
        printf("Debug: entrato in login");
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
    else if (comando == SEARCHGRUP) {
        processa_cerca_gruppo(pacchetto, pacchetto_da_spedire, array_socket, dim);
    }
    else if (comando == SENDNOTIFICA) {
        processa_manda_notifica(pacchetto, pacchetto_da_spedire, array_socket, dim);
    }
    else if (comando == ACCETTAUT) {
        processa_accetta_notifica(pacchetto, pacchetto_da_spedire, array_socket, dim);
    }
    else {
        processa_pacchetto_non_riconosciuto(pacchetto, pacchetto_da_spedire, array_socket, dim);
    }

}
