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

void alloca_array(int ** const array, int dim) {
    *array = malloc(dim*sizeof(int));
}

void dealloca_array(int ** const array) {
    free(*array);
}

int annulla_connessioni()
{
    return annulla_tutte_le_connessioni();
}

int annulla_connessione(const int socket)
{
    return annulla_connessione_socket(socket);
}

void set_manda_indietro(int ** const array, int * const dim, const int socket_fd) {
    *dim = 1;
    alloca_array(array, *dim);
    (*array)[0] = socket_fd;
}

void set_manda_notifica(int ** const array, int * const dim, const int socket_richiedente, const char * const nome_gruppo) {
    PGresult * accettante;
    *dim = 2;
    accettante = select_socket_amministratore(nome_gruppo);
    if (accettante == NULL || PQntuples(accettante) == 0) {
        set_manda_indietro(array, dim, socket_richiedente);
    }
    else {
        alloca_array(array, *dim);
        (*array)[0] = atoi(PQgetvalue(accettante, 0, 2));
        (*array)[1] = socket_richiedente;
    }
    PQclear(accettante);
}

void set_accetta_notifica(int ** const array, int * const dim, const int socket_accettante, const char * const nome_richiedente) {
    PGresult * richiedente;
    *dim = 2;
    richiedente = check_se_utente_connesso(nome_richiedente);
    if (richiedente == NULL || PQntuples(richiedente) == 0) {
        set_manda_indietro(array, dim, socket_accettante);
    }
    else {
        alloca_array(array, *dim);
        (*array)[0] = atoi(PQgetvalue(richiedente, 0, 2));
        (*array)[1] = socket_accettante;
    }
    PQclear(richiedente);

}

void set_manda_messaggio(int ** const array, int * const dim, const int socket_fd, const char * const nome_utente, const char * const nome_gruppo) {
    PGresult * socket_gruppo;
    int num_risultati;
    socket_gruppo = select_socket_gruppo(nome_gruppo, nome_utente);
    if (socket_gruppo == NULL) {
        set_manda_indietro(array, dim, socket_fd);
    }
    else {
        num_risultati = PQntuples(socket_gruppo);
        *dim = num_risultati + 1;
        alloca_array(array, *dim);
        for (int i = 0; i < num_risultati; i++) {
            (*array)[i] = atoi(PQgetvalue(socket_gruppo, i, 2));
        }
        printf("la dimensione dell'array in set manda messaggio è %d con socket_fd %d\n", *dim, socket_fd);
        (*array)[*dim -1] = socket_fd;
    }
    PQclear(socket_gruppo);
}

void processa_login(const char * const pacchetto, char * const pacchetto_da_spedire, int ** const array_socket, int * const dim, const int socket_fd) {
    PGresult *utente_registrato;

    char * nome;
    char * password;

    format_add_inizio_pacchetto(pacchetto_da_spedire);

    alloca_login(&nome, &password);
    parse_login(pacchetto, nome, password);
    printf(" 1");
    utente_registrato = check_se_utente_registrato(nome, password);
    printf(" 2 %s ", nome);
    //errore DB
    if (utente_registrato == NULL) {
        format_login_risposta(LOGINERR, pacchetto_da_spedire);
        set_manda_indietro(array_socket, dim, socket_fd);
    }
    else {
        printf(" 3");
        // se non registrato 
        if (PQntuples(utente_registrato) == 0) {
            format_login_risposta(LOGINNONTROVATO, pacchetto_da_spedire);
            set_manda_indietro(array_socket, dim, socket_fd);
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
            set_manda_indietro(array_socket, dim, socket_fd);
            format_add_inizio_body(pacchetto_da_spedire);
            printf(" 6");

            update_stato_connessione_utente(nome, socket_fd);

            gruppi_utente = select_gruppi_utente(nome);
            printf(" 7");
            num_gruppi_utente = PQntuples(gruppi_utente);
            printf(" 8");

            format_add_inizio_gruppi(pacchetto_da_spedire);
            printf(" 9");
            // aggiungi i gruppi
            for (int i = 0; i < num_gruppi_utente; i++) {
                format_add_inizio_gruppo(pacchetto_da_spedire);

                strcpy(nome_gruppo, PQgetvalue(gruppi_utente, i, 1));
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
                    format_add_inizio_messaggio(pacchetto_da_spedire);
                    format_add_mittente_messaggio(pacchetto_da_spedire, PQgetvalue(messaggi_gruppi_utente, j, 1));
                    format_add_contenuto_messaggio(pacchetto_da_spedire, PQgetvalue(messaggi_gruppi_utente, j, 3));
                    format_add_minutaggio_messaggio(pacchetto_da_spedire, PQgetvalue(messaggi_gruppi_utente, j, 4));
                    format_add_fine_messaggio(pacchetto_da_spedire);
                }
                printf(" 15");

                PQclear(messaggi_gruppi_utente);

                format_add_fine_messaggi(pacchetto_da_spedire);
                printf(" 16");

                format_add_inizio_notifiche(pacchetto_da_spedire);
                // aggiunti le notifiche se amministratore
                if (strcmp(nome, PQgetvalue(gruppi_utente, i, 0)) == 0) {
                    notifiche_gruppi_utente = select_notifiche_gruppo_utente(nome_gruppo);
                    printf(" 17");
                    num_notifiche_gruppo = PQntuples(notifiche_gruppi_utente);

                    printf(" 18");
                    for (int k = 0; k < num_notifiche_gruppo; k++) {
                        format_add_inizio_notifica(pacchetto_da_spedire);
                        format_add_notificante(pacchetto_da_spedire, PQgetvalue(notifiche_gruppi_utente, k, 0));
                        format_add_gruppo_notificato(pacchetto_da_spedire, nome_gruppo);
                        format_add_fine_notifica(pacchetto_da_spedire);
                    }

                    PQclear(notifiche_gruppi_utente);
                    printf(" 19");
                }

                format_add_fine_notifiche(pacchetto_da_spedire);

                format_add_fine_gruppo(pacchetto_da_spedire);
            }
            PQclear(gruppi_utente);

            format_add_fine_gruppi(pacchetto_da_spedire);
            format_add_fine_body(pacchetto_da_spedire);
        }
    }

    format_add_fine_pacchetto(pacchetto_da_spedire);

    PQclear(utente_registrato); 
    dealloca_login(&nome, &password);
}

void processa_signin(const char * const pacchetto, char * const pacchetto_da_spedire, int ** const array_socket, int * const dim, const int socket_fd) {
    PGresult *utente_registrato;
    int inserito = 0;

    char * nome;
    char * password;

    format_add_inizio_pacchetto(pacchetto_da_spedire);

    alloca_signin(&nome, &password);
    parse_signin(pacchetto, nome, password);

    //printf("Debug: signin %s\n", nome);
    utente_registrato = check_se_utente_registrato(nome, password);
    //errore DB
    if (utente_registrato == NULL) {
        format_signin_risposta(SIGNINERR, pacchetto_da_spedire);
        set_manda_indietro(array_socket, dim, socket_fd);
    }
    else {
        // se utente guà registrato 
        if (PQntuples(utente_registrato) == 1) {
            format_signin_risposta(SIGNGIAREGISTRATO, pacchetto_da_spedire);
            set_manda_indietro(array_socket, dim, socket_fd);
        }
        // se non ancora registrato
        else {
            inserito = insert_utente_db(nome, password);
            //errore DB
            if (inserito  == 0) {
                format_signin_risposta(SIGNINERR, pacchetto_da_spedire);
                set_manda_indietro(array_socket, dim, socket_fd);
            }
            else {
                update_stato_connessione_utente(nome, socket_fd);
                format_signin_risposta(SIGNINOK, pacchetto_da_spedire);
                set_manda_indietro(array_socket, dim, socket_fd);
                format_add_inizio_body(pacchetto_da_spedire);
                format_add_fine_body(pacchetto_da_spedire);
            }
        }
    }

    format_add_fine_pacchetto(pacchetto_da_spedire);

    PQclear(utente_registrato);

    dealloca_signin(&nome, &password);
}

void processa_crea_gruppo(const char * const pacchetto, char * const pacchetto_da_spedire, int ** const array_socket, int * const dim, const int socket_fd) {
    PGresult *gruppo_registrato = 0;
    int inserito = 0;
    int inserita_membership = 0;

    char * nome_gruppo;
    char * nome_utente;

    format_add_inizio_pacchetto(pacchetto_da_spedire);

    alloca_crea_gruppo(&nome_gruppo, &nome_utente);

    parse_crea_gruppo(pacchetto, nome_gruppo, nome_utente);

    gruppo_registrato = check_se_gruppo_registrato(nome_gruppo);
    //errore DB
    if (gruppo_registrato == NULL) {
        format_crea_gruppo_risposta(CREAGRUPERR, pacchetto_da_spedire);
        set_manda_indietro(array_socket, dim, socket_fd);
    }
    else {
        // gruppo già esistente
        if (PQntuples(gruppo_registrato) == 1) {
            format_crea_gruppo_risposta(CREAGRUPGIAREGISTRATO, pacchetto_da_spedire);
            set_manda_indietro(array_socket, dim, socket_fd);
        }
        else {
            inserito = insert_gruppo_db(nome_gruppo, nome_utente);
            inserita_membership = insert_membership_db(nome_utente, nome_gruppo);
            // errore DB
            if (inserito == 0) {
                format_crea_gruppo_risposta(CREAGRUPERR, pacchetto_da_spedire);
                set_manda_indietro(array_socket, dim, socket_fd);
            }
            // se non ancora registrato
            else {
                format_crea_gruppo_risposta(CREAGRUPOK, pacchetto_da_spedire);
                set_manda_indietro(array_socket, dim, socket_fd);
                format_add_inizio_body(pacchetto_da_spedire);
                format_add_inizio_gruppi(pacchetto_da_spedire);
                format_add_inizio_gruppo(pacchetto_da_spedire);

                format_add_nome_gruppo(pacchetto_da_spedire, nome_gruppo);
                
                format_add_fine_gruppo(pacchetto_da_spedire);
                format_add_fine_gruppi(pacchetto_da_spedire);

                format_add_fine_body(pacchetto_da_spedire);
            }
        }
    }

    format_add_fine_pacchetto(pacchetto_da_spedire);


    PQclear(gruppo_registrato);
    dealloca_crea_gruppo(&nome_gruppo, &nome_utente);
}

void processa_messaggio(const char * const pacchetto, char * const pacchetto_da_spedire, int ** const array_socket, int * const dim, const int socket_fd) {
    int inserito = 0;

    char * nome_gruppo;
    char * nome_utente;
    char * contenuto;
    char * minutaggio;

    format_add_inizio_pacchetto(pacchetto_da_spedire);

    alloca_messaggio(&nome_gruppo, &nome_utente, &contenuto, &minutaggio);
    parse_messaggio(pacchetto, nome_gruppo, nome_utente, contenuto, minutaggio);
    inserito = insert_messaggio_db(nome_utente, nome_gruppo, contenuto, minutaggio);
    if (inserito == 0) {
        format_messaggio_risposta(SENDMESSERR, pacchetto_da_spedire);
        set_manda_indietro(array_socket, dim, socket_fd);
    }
    else {
        format_messaggio_risposta(SENDMESSOK, pacchetto_da_spedire);
        set_manda_messaggio(array_socket, dim, socket_fd, nome_utente, nome_gruppo);
        format_add_inizio_body(pacchetto_da_spedire);
        format_add_inizio_gruppi(pacchetto_da_spedire);
        format_add_inizio_gruppo(pacchetto_da_spedire);

        format_add_nome_gruppo(pacchetto_da_spedire, nome_gruppo);

        format_add_inizio_messaggi(pacchetto_da_spedire);
        format_add_inizio_messaggio(pacchetto_da_spedire);

        format_add_mittente_messaggio(pacchetto_da_spedire, nome_utente);
        format_add_contenuto_messaggio(pacchetto_da_spedire, contenuto);

        format_add_minutaggio_messaggio(pacchetto_da_spedire, minutaggio);


        format_add_fine_messaggio(pacchetto_da_spedire);

        format_add_fine_messaggi(pacchetto_da_spedire);


        format_add_fine_gruppo(pacchetto_da_spedire);


        format_add_fine_gruppi(pacchetto_da_spedire);

        format_add_fine_body(pacchetto_da_spedire);

    }
    format_add_fine_pacchetto(pacchetto_da_spedire);

    dealloca_messaggio(&nome_gruppo, &nome_utente, &contenuto, &minutaggio);
}

char *processa_cerca_gruppo(const char * const pacchetto, char * const pacchetto_da_spedire, int ** const array_socket, int * const dim, const int socket_fd) {
    PGresult *gruppi_trovati;
    char * nome_utente;
    char * nome_gruppo;

    format_add_inizio_pacchetto(pacchetto_da_spedire);
    
    alloca_cerca_gruppo(&nome_gruppo, &nome_utente);
    parse_cerca_gruppo(pacchetto, nome_gruppo, nome_utente);

    gruppi_trovati = select_gruppi_senza_utente(nome_utente,nome_gruppo);
    if (gruppi_trovati == NULL) {
        format_cerca_gruppo(SEARCHGRUPERR, pacchetto_da_spedire);
        set_manda_indietro(array_socket, dim, socket_fd);
    }
    else {
        format_cerca_gruppo(SEARCHGRUPOK, pacchetto_da_spedire);
        set_manda_indietro(array_socket, dim, socket_fd);
        format_add_inizio_body(pacchetto_da_spedire);
        format_add_inizio_gruppi(pacchetto_da_spedire);
        for (int i = 0; i < PQntuples(gruppi_trovati); i++) {
            format_add_inizio_gruppo(pacchetto_da_spedire);
            format_add_nome_gruppo(pacchetto_da_spedire, PQgetvalue(gruppi_trovati, i, 0));
            format_add_fine_gruppo(pacchetto_da_spedire);
        }
        format_add_fine_gruppi(pacchetto_da_spedire);
        format_add_fine_body(pacchetto_da_spedire);
    }

    format_add_fine_pacchetto(pacchetto_da_spedire);

    PQclear(gruppi_trovati);
    dealloca_cerca_gruppo(&nome_gruppo, &nome_utente);
}

char * processa_manda_notifica(const char * const pacchetto, char * const pacchetto_da_spedire, int ** const array_socket, int * const dim, const int socket_fd) {
    int inserito;

    char * nome_utente;
    char * nome_gruppo;

    format_add_inizio_pacchetto(pacchetto_da_spedire);

    alloca_manda_notifica(&nome_gruppo, &nome_utente);

    parse_manda_notifica(pacchetto, nome_gruppo, nome_utente);
    
    inserito = insert_notifica_db(nome_utente, nome_gruppo);
    if (inserito == 0) {
        format_manda_notifica(SENDNOTIFICAERR, pacchetto_da_spedire);
        set_manda_indietro(array_socket, dim, socket_fd);
    }
    else {
        format_manda_notifica(SENDNOTIFICAOK, pacchetto_da_spedire);
        set_manda_notifica(array_socket, dim, socket_fd, nome_gruppo);

        format_add_inizio_body(pacchetto_da_spedire);
        format_add_inizio_gruppi(pacchetto_da_spedire);
        format_add_inizio_gruppo(pacchetto_da_spedire);
            format_add_nome_gruppo(pacchetto_da_spedire, nome_gruppo);
        format_add_inizio_notifiche(pacchetto_da_spedire);

        format_add_inizio_notifica(pacchetto_da_spedire);

        format_add_notificante(pacchetto_da_spedire, nome_utente);
        format_add_gruppo_notificato(pacchetto_da_spedire, nome_gruppo);

        format_add_fine_notifica(pacchetto_da_spedire);

        format_add_fine_notifiche(pacchetto_da_spedire);
        format_add_fine_gruppo(pacchetto_da_spedire);
        format_add_fine_gruppi(pacchetto_da_spedire);
        format_add_fine_body(pacchetto_da_spedire);
    }

    format_add_fine_pacchetto(pacchetto_da_spedire);

    dealloca_manda_notifica(&nome_gruppo, &nome_utente);
}

char *processa_accetta_notifica(const char * const pacchetto, char * const pacchetto_da_spedire, int ** const array_socket, int * const dim, const int socket_fd) {
    PGresult *messaggi_gruppo;
    int rimossa = 0;
    int inserito = 0;

    char * nome_gruppo;
    char * nome_utente;
    char * nome_richiedente;

    format_add_inizio_pacchetto(pacchetto_da_spedire);

    alloca_accetta_notifica(&nome_gruppo, &nome_utente, &nome_richiedente);

    parse_accetta_notifica(pacchetto, nome_gruppo, nome_utente, nome_richiedente);

    printf ("%s %s %s",nome_gruppo,nome_utente,nome_richiedente);

    inserito = insert_membership_db(nome_richiedente, nome_gruppo);
    
    if (inserito == 0) {
        format_accetta_notifica(ACCETTAUTERR, pacchetto_da_spedire);
        set_manda_indietro(array_socket, dim, socket_fd);
    }
    else {
        rimossa = delete_notifica_db(nome_richiedente, nome_gruppo);
        if (rimossa == 0) {
            format_accetta_notifica(ACCETTAUTERR, pacchetto_da_spedire);
            set_manda_indietro(array_socket, dim, socket_fd);
        }
        else {
            messaggi_gruppo = select_messaggi_gruppo_utente(nome_gruppo);
            format_accetta_notifica(ACCETTAUTOK, pacchetto_da_spedire);
            set_accetta_notifica(array_socket, dim, socket_fd, nome_richiedente);

            format_add_inizio_body(pacchetto_da_spedire);

            format_add_inizio_gruppi(pacchetto_da_spedire);

            format_add_inizio_gruppo(pacchetto_da_spedire);

            format_add_nome_gruppo(pacchetto_da_spedire, nome_gruppo);
            format_add_inizio_messaggi(pacchetto_da_spedire);

            // aggiungi i messaggi
            for (int j = 0; j < PQntuples(messaggi_gruppo); j++) {
                format_add_inizio_messaggio(pacchetto_da_spedire);
                format_add_mittente_messaggio(pacchetto_da_spedire, PQgetvalue(messaggi_gruppo, j, 1));
                format_add_contenuto_messaggio(pacchetto_da_spedire, PQgetvalue(messaggi_gruppo, j, 3));
                format_add_minutaggio_messaggio(pacchetto_da_spedire, PQgetvalue(messaggi_gruppo, j, 4));
                format_add_fine_messaggio(pacchetto_da_spedire);
            }

            format_add_fine_messaggi(pacchetto_da_spedire);
            format_add_fine_gruppo(pacchetto_da_spedire);

            format_add_fine_gruppi(pacchetto_da_spedire);

            format_add_fine_body(pacchetto_da_spedire);

            PQclear(messaggi_gruppo);
        }
    }

    format_add_fine_pacchetto(pacchetto_da_spedire);

    dealloca_accetta_notifica(&nome_gruppo, &nome_utente, &nome_richiedente);
}

char *processa_annulla_notifica(const char * const pacchetto, char * const pacchetto_da_spedire, int ** const array_socket, int * const dim, const int socket_fd) {

    char * nome_gruppo;
    char * nome_utente;
    char * nome_richiedente;
    int rimosso;

    format_add_inizio_pacchetto (pacchetto_da_spedire);

    alloca_annulla_notifica (&nome_gruppo,&nome_utente,&nome_richiedente);
    parse_annulla_notifica (pacchetto,nome_gruppo,nome_utente,nome_richiedente);

    printf ("%s %s %s",nome_gruppo,nome_utente,nome_richiedente);

    rimosso = delete_notifica_db (nome_richiedente,nome_gruppo);

    if (rimosso == 0) {
        format_annulla_notifica (RIFIUTANOTERR,pacchetto_da_spedire);
        set_manda_indietro (array_socket,dim,socket_fd);
    }
    else {
        format_annulla_notifica (RIFIUTANOTOK,pacchetto_da_spedire);
        set_manda_indietro (array_socket,dim,socket_fd);

        format_add_inizio_body(pacchetto_da_spedire);
        format_add_inizio_gruppi(pacchetto_da_spedire);
        format_add_inizio_gruppo(pacchetto_da_spedire);

        format_add_nome_gruppo(pacchetto_da_spedire, nome_gruppo);

        format_add_fine_gruppo(pacchetto_da_spedire);
        format_add_fine_gruppi(pacchetto_da_spedire);
        format_add_fine_body(pacchetto_da_spedire);

    }

    format_add_fine_pacchetto(pacchetto_da_spedire);

    dealloca_annulla_notifica(&nome_gruppo,&nome_utente,&nome_richiedente);
}

char *processa_pacchetto_non_riconosciuto(const char * const pacchetto, char * const pacchetto_da_spedire, int ** const array_socket, int * const dim, const int socket_fd) {
    format_add_inizio_pacchetto(pacchetto_da_spedire);
    format_pacchetto_non_riconosciuto(PACCHETTONONCOMPRESO, pacchetto_da_spedire);
    set_manda_indietro(array_socket, dim, socket_fd);
    format_add_fine_pacchetto(pacchetto_da_spedire);
}

void processa(const char * const pacchetto, char **  pacchetto_da_spedire, int ** const array_socket, int * const dim, const int * const socket_fd) {
    int comando;

    comando = parse_comando(pacchetto);
    *pacchetto_da_spedire = alloca_pacchetto();

    if (comando == LOGIN) {
        processa_login(pacchetto, *pacchetto_da_spedire, array_socket, dim, *socket_fd);
    }
    else if (comando == SIGNIN) {
        processa_signin(pacchetto, *pacchetto_da_spedire, array_socket, dim, *socket_fd);
    }
    else if (comando == CREAGRUP) {
        processa_crea_gruppo(pacchetto, *pacchetto_da_spedire, array_socket, dim, *socket_fd);
    }
    else if (comando == SENDMESS) {
        processa_messaggio(pacchetto, *pacchetto_da_spedire, array_socket, dim, *socket_fd);
    }
    else if (comando == SEARCHGRUP) {
        processa_cerca_gruppo(pacchetto, *pacchetto_da_spedire, array_socket, dim, *socket_fd);
    }
    else if (comando == SENDNOTIFICA) {
        processa_manda_notifica(pacchetto, *pacchetto_da_spedire, array_socket, dim, *socket_fd);
    }
    else if (comando == ACCETTAUT) {
        processa_accetta_notifica(pacchetto, *pacchetto_da_spedire, array_socket, dim, *socket_fd);
    }
    else if (comando == RIFIUTANOT) {
        processa_annulla_notifica(pacchetto, *pacchetto_da_spedire, array_socket, dim, *socket_fd);
    }
    else {
        processa_pacchetto_non_riconosciuto(pacchetto, *pacchetto_da_spedire, array_socket, dim, *socket_fd);
    }

}
