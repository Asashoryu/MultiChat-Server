#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "strutture_dati.h"
#include "database.h"

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
    utente *elemento = malloc (sizeof(utente*));

    if (elemento != NULL)
    {
        if (strlen(nome) <= NOME_UTENTE_LEN)
            strcpy (elemento->nome,nome);
        elemento->gruppi_aggiunti = NULL;
        elemento->notifiche = NULL;
        elemento->socket_fd = 0;
    }
    
    return elemento;
}