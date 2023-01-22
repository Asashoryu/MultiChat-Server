#ifndef STRUTTURE_DATI_H
#define STRUTTURE_DATI_H

#define NOME_GRUPPO_LEN 100

#define NOME_UTENTE_LEN 100

#define MESSAGGIO_LEN 1024
#define DATA_LEN 30

#define DIM_INIZIALE_UTENTI 10
#define DIM_INIZIALE_GRUPPI 10

typedef struct messaggio {
    char contenuto[MESSAGGIO_LEN];
    int mittente_id;
    char orario[DATA_LEN];
} messaggio;

typedef struct richiesta_accesso {
    int richiedente_id;
    struct richiesta_accesso *next;
} richiesta_accesso;

typedef struct utente
{
    char nome[NOME_UTENTE_LEN];
    int *gruppi_aggiunti;
    int socket_fd;
} utente;

typedef struct gruppo
{
    char nome[NOME_GRUPPO_LEN];
    messaggio *chat;
    int *membri;
    int amministratore_id;
    richiesta_accesso *notifiche;
} gruppo;

typedef gruppo * gruppi;
typedef utente * utenti;

// ritorna una nuova richiesta di accesso
richiesta_accesso *inizializza_richiesta_accesso(const int richiedente_id);
void dealloca_richiesta_accesso(richiesta_accesso *Richiesta_accesso);
// ritorna una nuovo utente
utente *inizializza_utente(const char * const nome);
void dealloca_utente(utente *Utente);
// ritorna un nuovo gruppo
gruppo *inizializza_gruppo(const char * const nome, const int amministratore);
void dealloca_gruppo(gruppo * Gruppo);
// ritorna un nuovo array di gruppi
gruppi *inizializza_gruppi(int * dimensione);
void *dealloca_gruppi(gruppi * Gruppi);
// ritorna un nuovo array di utenti
utenti *inizializza_utenti(int * dimensione);
void *dealloca_utenti(utenti * Utenti);
// ritorna 1=(dati avviati con successo), o 0=false



#endif