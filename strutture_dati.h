#ifndef STRUTTURE_DATI_H
#define STRUTTURE_DATI_H

#define NOME_GRUPPO_LEN 100

#define NOME_UTENTE_LEN 100
#define PASSWORD_UTENTE_LEN 100

#define MESSAGGIO_LEN 1024
#define DATA_LEN 30

#define DIM_INIZIALE_UTENTI 100
#define DIM_INIZIALE_GRUPPI 100

typedef struct messaggio {
    char contenuto[MESSAGGIO_LEN];
    int mittente_id;
    long long int minutaggio;
    struct messaggio *next;
} messaggio;

typedef struct richiesta_accesso {
    int richiedente_id;
    struct richiesta_accesso *next;
} richiesta_accesso;

typedef struct utente
{
    int utente_id;
    char nome[NOME_UTENTE_LEN];
    char nome[PASSWORD_UTENTE_LEN];
    int socket_fd;
    int *gruppi_aggiunti;
} utente;

typedef struct gruppo
{
    int gruppo_id;
    char nome[NOME_GRUPPO_LEN];
    int amministratore_id;
    int *membri;
    messaggio *chat;
    richiesta_accesso *notifiche;
} gruppo;

typedef struct gruppi
{
    int dim;
    gruppo **array_gruppi;
} gruppi;

typedef struct utenti
{
    int dim;
    utente **array_utenti;
} utenti;

// ritorna una nuova richiesta di accesso
richiesta_accesso *inizializza_richiesta_accesso(const int richiedente_id);
void dealloca_richiesta_accesso(richiesta_accesso *Richiesta_accesso);
//restituisce 1 se l'inserimento è andato a buon fine, 0 altrimenti
int aggiungi_richiesta_accesso (gruppi *Gruppi, const int richiedente_id, const int gruppo_id);
//restituisce 1 se la rimozione è andata a buon fine, 0 altrimenti
int rimuovi_richiesta_accesso (gruppi *Gruppi, const int gruppo_id, const int richiedente_id);
// ritorna una nuovo utente
utente *inizializza_utente(const char * const nome);
void dealloca_utente(utente *Utente);
// ritorna un nuovo gruppo
gruppo *inizializza_gruppo(const char * const nome, const int amministratore);
void dealloca_gruppo(gruppo * Gruppo);
// ritorna un nuovo messaggio
messaggio *inizializza_messaggio(const char * const contenuto, int mittente_id, long long int orario);
void dealloca_messaggio(messaggio * Messaggio);
// ritorna un nuovo array di gruppi
gruppi *inizializza_gruppi(int * dimensione);
void *dealloca_gruppi(gruppi * Gruppi);
// ritorna un nuovo array di utenti
utenti *inizializza_utenti(int * dimensione);
void *dealloca_utenti(utenti * Utenti);
// ritorna 1=(dati avviati con successo), o 0=false

// ritorna 1=true, o 0=false
int aggiungi_messaggio(gruppi *Gruppi, const int gruppo_id, const int mittente_id, long long int minutaggio, const char * const contenuto);


#endif