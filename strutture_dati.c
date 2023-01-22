#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "strutture_dati.h"

richiesta_accesso *inizializza_richiesta_accesso(const int richiedente_id)
{
    richiesta_accesso *accesso = malloc (sizeof(richiesta_accesso*));

    if (accesso != NULL)
    {
        accesso->richiedente_id = richiedente_id;
        accesso->next = NULL;
    }

    return accesso;
}

void dealloca_richiesta_accesso(richiesta_accesso *Richiesta_accesso)
{
    free (Richiesta_accesso);
}

utente *inizializza_utente(const char * const nome)
{
    utente *elemento = NULL;
    
    if (strlen(nome) > NOME_UTENTE_LEN)
        return elemento;
    
    elemento = malloc (sizeof(utente*));

    if (elemento != NULL)
    {
        strcpy (elemento->nome,nome);
        elemento->gruppi_aggiunti = malloc (10*sizeof(int*));
        if (elemento->gruppi_aggiunti == NULL)
        {
            free (elemento);
            return NULL;
        }
        elemento->socket_fd = 0;
    }
    
    return elemento;
}

void dealloca_utente(utente *Utente)
{
    free (Utente->gruppi_aggiunti);
    free (Utente);
}

gruppo *inizializza_gruppo(const char * const nome, const int amministratore)
{
    gruppo *elemento = NULL;

    if (strlen(nome) > NOME_GRUPPO_LEN)
        return elemento;

    elemento = malloc (sizeof(gruppo*));

    if (elemento != NULL)
    {
        strcpy (elemento->nome,nome);
        elemento->amministratore_id = amministratore;
        elemento->membri = malloc (DIM_INIZIALE_UTENTI*sizeof(int*));
        elemento->notifiche = malloc (sizeof(richiesta_accesso*));
        elemento->chat = malloc (sizeof(messaggio*));
        if (elemento->membri == NULL || elemento->notifiche == NULL || elemento->chat == NULL)
        {
            free (elemento->membri);
            free (elemento->notifiche);
            free (elemento->chat);
            free (elemento);
            return NULL;
        }
    }

    return elemento;
}

void dealloca_gruppo(gruppo * Gruppo)
{
    free (Gruppo->membri);
    free (Gruppo->notifiche);
    free (Gruppo->chat);
    free (Gruppo);
}

messaggio *inizializza_messaggio(const char * const contenuto, int mittente_id, int orario)
{
    messaggio *elemento = NULL;
    if (strlen(contenuto)>MESSAGGIO_LEN)
        return NULL;

    elemento = malloc (sizeof(messaggio*));

    if (elemento != NULL)
    {
        strcpy (elemento->contenuto,contenuto);
        elemento->mittente_id = mittente_id;
        elemento->orario = orario;
    }
    
    return elemento;
}

void dealloca_messaggio(messaggio * Messaggio)
{
    free (Messaggio);
}

gruppi *inizializza_gruppi(int * dimensione)
{
    gruppi *Gruppi = malloc ((*dimensione)*sizeof(gruppi*));
    return Gruppi;
}

void *dealloca_gruppi(gruppi * Gruppi)
{
    free (Gruppi);
}

utenti *inizializza_utenti(int * dimensione)
{
    utenti *Utenti = malloc ((*dimensione)*sizeof(gruppi*));
    return Utenti;
}

void *dealloca_utenti(utenti * Utenti)
{
    free (Utenti);
}