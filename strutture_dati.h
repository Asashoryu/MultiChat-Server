#ifndef STRUTTURE_DATI_H
#define STRUTTURE_DATI_H

#define NOME_GRUPPO_LEN 100

#define NOME_UTENTE_LEN 100

typedef struct richiesta_accesso {
    int richiedente_id;
    struct richiesta_accesso *next;
} richiesta_accesso;

typedef struct utente
{
    char nome[NOME_UTENTE_LEN];
    int *gruppi_aggiunti;
    int socket_fd;
    richiesta_accesso *notifiche;
} utente;

typedef struct gruppo
{
    char nome[NOME_GRUPPO_LEN];
    int *membri;
    int amministratore_id;
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
int avvia_dati(gruppi * Gruppi, utenti * Utenti);
// ritorna 1=true, o 0=false
int check_se_nome_utente_valido(const char * const nome);
// ritorna 1=true, o 0=false
int check_se_password_utente_valida(const char * const nome);
// ritorna 1=true, o 0=false
int check_se_nome_gruppo_valido(const char * const nome);
// ritorna id_utente se registrato, o 0=false (non registrato)
int check_se_utente_registrato(const char * const nome, const char * const password);
// ritorna 1=true, o 0=false
int check_se_utente_loggato(utenti * Utenti, const int utente_id);
// ritorna id_utente se registrato, o 0=false (non registrato)
int check_se_gruppo_registrato(const char * const nome);
// ritorna id utente, o <=0 se il login non può essere effettuato
int login(utenti * Utenti, const char * const nome, const char * const password);
// ritorna id utente, o <=0 se il signin non può essere effettuato
int signin(utenti * Utenti, const char * const nome, const char * const password);
// ritorna id gruppo, o <=0 se il gruppo non può essere creato
int crea_gruppo(gruppi * Gruppi, const char * const nome, int utente_creatore_id);
// ritorna 1=true, o 0=false 
int crea_notifica(gruppi * Gruppi, utenti * Utenti, const int gruppo_dove_registrarsi_id, const int utente_id);


#endif