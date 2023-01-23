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

int aggiungi_richiesta_accesso (gruppi *Gruppi, const int richiedente_id, const int gruppo_id)
{
    Gruppi->array_gruppi[gruppo_id]->notifiche = aggiungi_richiesta_accesso_alla_lista (Gruppi->array_gruppi[gruppo_id]->notifiche, richiedente_id);
    return 1;
}

richiesta_accesso *aggiungi_richiesta_accesso_alla_lista (richiesta_accesso *notifica, const int richiedente_id)
{
    richiesta_accesso *elemento = NULL;
    elemento = inizializza_richiesta_accesso (richiedente_id);
    if (elemento != NULL)
    {
        elemento->next = notifica;
        return elemento;
    }
    return notifica;
}

int rimuovi_richiesta_accesso (gruppi *Gruppi, const int gruppo_id, const int richiedente_id)
{
    Gruppi->array_gruppi[gruppo_id]->notifiche = rimuovi_richiesta_accesso_dalla_lista (Gruppi->array_gruppi[gruppo_id]->notifiche, richiedente_id);
    if (Gruppi->array_gruppi[gruppo_id] == NULL)
        return 0;
    else
        return 1;
}

richiesta_accesso *rimuovi_richiesta_accesso_dalla_lista (richiesta_accesso *notifica, const int richiedente_id)
{
    richiesta_accesso *tmp;

    if (notifica == NULL)
        return NULL;

    if (notifica->richiedente_id == richiedente_id)
    {
        tmp = notifica->next;
        free (notifica);
        return tmp;
    }

    notifica->next = rimuovi_richiesta_accesso_dalla_lista (notifica->next, richiedente_id);
    return notifica;
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

int trova_min_id_gruppo (gruppi *Gruppi)
{
    int i;
    for (i=0;i<Gruppi->dim;i++)
    {
        if (Gruppi->array_gruppi[i] == NULL)
        {
            return i;
        }
    }
    return -1;
}

int trova_min_id_utente (utenti *Utenti)
{
    int i;
    for (i=0;i<Utenti->dim;i++)
    {
        if (Utenti->array_utenti[i] == NULL)
        {
            return i;
        }
    }
    return -1;
}

int aggiungi_gruppo (gruppi *Gruppi, const char * const nome_gruppo, int amministratore_id)
{
    int i = trova_min_id_gruppo (Gruppi);

    if (i != -1)
    {
        Gruppi->array_gruppi[i] = inizializza_gruppo (nome_gruppo,amministratore_id);
        return 1;
    }
    else
    {
        return 0;
    }
}

int aggiungi_utente (utenti *Utenti, const char * const nome)
{
    int i = trova_min_id_utente (Utenti);

    if (i != -1)
    {
        Utenti->array_utenti[i] = inizializza_utente (nome);
        return 1;
    }
    else
    {
        return 0;
    }
    
}

messaggio *inizializza_messaggio(const char * const contenuto, int mittente_id, long long int orario)
{
    messaggio *elemento = NULL;
    if (strlen(contenuto)>MESSAGGIO_LEN)
        return NULL;

    elemento = malloc (sizeof(messaggio*));

    if (elemento != NULL)
    {
        strcpy (elemento->contenuto,contenuto);
        elemento->mittente_id = mittente_id;
        elemento->minutaggio = orario;
        elemento->next = NULL;
    }
    
    return elemento;
}

void dealloca_messaggio(messaggio * Messaggio)
{
    free (Messaggio);
}

int aggiungi_messaggio(gruppi *Gruppi, const int gruppo_id, const int mittente_id, long long int minutaggio, const char * const contenuto)
{
    int i;
    if (strlen (contenuto) > MESSAGGIO_LEN)
        return 0;

    for (i=0;i<Gruppi->dim;i++)
    {
        if (i == gruppo_id)
        {
            Gruppi->array_gruppi[i]->chat = aggiungi_messaggio_in_lista (Gruppi->array_gruppi[i]->chat, contenuto, mittente_id, minutaggio);
            return 1;
        }
    }

    return 0;
}

messaggio *aggiungi_messaggio_in_lista(messaggio *chat, const char * const contenuto, int mittente_id, long long minutaggio)
{
    messaggio *elemento = NULL;

    if (chat == NULL)
        return NULL;

    if (chat->minutaggio <= minutaggio)
    {
        elemento = inizializza_messaggio (contenuto, mittente_id, minutaggio);
        return elemento;
    }

    chat->next = aggiungi_messaggio_in_lista (chat->next, contenuto, mittente_id, minutaggio);
    return chat;
}

gruppi *inizializza_gruppi(int * numero_di_gruppi)
{
    int i;
    gruppi *Gruppi = malloc (sizeof(gruppi*));
    if (Gruppi != NULL)
    {
        Gruppi->dim = (*numero_di_gruppi)*2;
        Gruppi->array_gruppi = malloc ((*numero_di_gruppi)*sizeof(gruppo*));
        for (i=0;i<Gruppi->dim;i++)
        {
            Gruppi->array_gruppi[i] = NULL;
        }
    }
    return Gruppi;
}

void *dealloca_gruppi(gruppi * Gruppi)
{
    int i;
    for (i=0;i<Gruppi->dim;i++)
    {
        dealloca_gruppo (Gruppi->array_gruppi[i]);
    }
    free (Gruppi->array_gruppi);
    free (Gruppi);
}

utenti *inizializza_utenti(int * numero_di_utenti)
{
    int i;
    utenti *Utenti = malloc (sizeof(utenti*));
    if (Utenti != NULL)
    {
        Utenti->dim = (*numero_di_utenti)*2;
        Utenti->array_utenti = malloc ((*numero_di_utenti)*sizeof(utente*));
        for (i=0;i<Utenti->dim;i++)
        {
            Utenti->array_utenti[i] = NULL;
        }
    }
}

void *dealloca_utenti(utenti * Utenti)
{
    int i;
    for (i=0;i<Utenti->dim;i++)
    {
        dealloca_utente (Utenti->array_utenti[i]);
    }
    free (Utenti->array_utenti);
    free (Utenti);
}