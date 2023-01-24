#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "gestore_pacchetti.h"

#define LN_STR 1000

char *parse_comando(char *pacchetto)
{
    char *inizio = NULL;
    char *fine = NULL;
    int dim = 0;
    char comando[200];
    char *cmd = malloc(200*sizeof(char));

    strcpy (comando, pacchetto);
    inizio = strstr (comando,"cmd=");
    inizio += strlen ("cmd=");
    fine = strstr (inizio,"\r\n");
    if (inizio && fine)
    {
        dim = fine-inizio;
        strncpy (cmd,inizio,dim);
        cmd[dim] = '\0';
        return cmd;
    }
    return NULL;
}

void parse_login(const char * const pacchetto, char * nome, char * password)
{
    char *inizio = NULL;
    char *fine = NULL;
    int dim = 0;
    char comando[200];

     strcpy (comando,pacchetto);
     inizio = strstr (comando,"nome=");
     inizio += strlen ("nome=");
     fine = strstr (inizio,"\r\n");
     if (inizio && fine)
     {
        dim = fine-inizio;
        strncpy (nome,inizio,dim);
     }

     inizio = strstr (comando,"password=");
     inizio += strlen ("password=");
     fine = strstr (inizio,"\r\n");
     if (inizio && fine)
     {
        dim = fine-inizio;
        strncpy (password,inizio,dim);
     }
}

void parse_crea_gruppo(const char * const pacchetto, char * nome_gruppo, char * nome_utente)
{
    char *inizio;
    char *fine;
    int dim;
    char comando[200];

    strcpy (comando,pacchetto);
    inizio = strstr (comando,"gruppo=");
    inizio += strlen ("gruppo=");
    fine = strstr (inizio,"\r\n");
    if (inizio && fine)
    {
        dim = fine-inizio;
        strncpy (nome_gruppo,inizio,dim);
    }

    inizio = strstr (comando,"utente=");
    inizio += strlen ("utente=");
    fine = strstr (inizio,"\r\n");
    if (inizio && fine)
    {
        dim = fine-inizio;
        strncpy (nome_utente,inizio,dim);
    }
}

void parse_messaggio(const char * const pacchetto, char * nome_gruppo, char * nome_utente, char * messaggio, char *minutaggio)
{
    char *inizio;
    char *fine;
    int dim;
    char comando[200];

    strcpy (comando,pacchetto);
    inizio = strstr (comando,"gruppo=");
    inizio += strlen ("gruppo=");
    fine = strstr (inizio,"\r\n");
    if (inizio && fine)
    {
        dim = fine-inizio;
        strncpy (nome_gruppo,inizio,dim);
    }

    inizio = strstr (comando,"utente=");
    inizio += strlen ("utente=");
    fine = strstr (inizio,"\r\n");
    if (inizio && fine)
    {
        dim = fine-inizio;
        strncpy (nome_utente,inizio,dim);
    }

    inizio = strstr (comando,"messaggio=");
    inizio += strlen ("messaggio=");
    fine = strstr (inizio,"\r\n");
    if (inizio && fine)
    {
        dim = fine-inizio;
        strncpy (messaggio,inizio,dim);
    }

    inizio = strstr (comando,"minutaggio=");
    inizio += strlen ("minutaggio=");
    fine = strstr (inizio,"\r\n");
    if (inizio && fine)
    {
        dim = fine-inizio;
        strncpy (minutaggio,inizio,dim);
    }
}

void parse_cerca_gruppo(const char * const pacchetto, char * nome_gruppo, char * nome_utente)
{
    char *inizio;
    char *fine;
    int dim;
    char comando[200];

    strcpy (comando,pacchetto);
    inizio = strstr (comando,"gruppo=");
    inizio += strlen ("gruppo=");
    fine = strstr (inizio,"\r\n");
    if (inizio && fine)
    {
        dim = fine-inizio;
        strncpy (nome_gruppo,inizio,dim);
    }

    inizio = strstr (comando,"utente=");
    inizio += strlen ("utente=");
    fine = strstr (inizio,"\r\n");
    if (inizio && fine)
    {
        dim = fine-inizio;
        strncpy (nome_utente,inizio,dim);
    }
}

void parse_manda_notifica(const char * const pacchetto, char * nome_gruppo, char * nome_utente)
{
    char *inizio;
    char *fine;
    int dim;
    char comando[200];

    strcpy (comando,pacchetto);
    inizio = strstr (comando,"gruppo=");
    inizio += strlen ("gruppo=");
    fine = strstr (inizio,"\r\n");
    if (inizio && fine)
    {
        dim = fine-inizio;
        strncpy (nome_gruppo,inizio,dim);
    }

    inizio = strstr (comando,"utente=");
    inizio += strlen ("utente=");
    fine = strstr (inizio,"\r\n");
    if (inizio && fine)
    {
        dim = fine-inizio;
        strncpy (nome_utente,inizio,dim);
    }
}

void parse_accetta_notifica(const char * const pacchetto, char * nome_gruppo, char * nome_utente, char * nome_richiedente)
{
    char *inizio;
    char *fine;
    int dim;
    char comando[200];

    strcpy (comando,pacchetto);
    inizio = strstr (comando,"gruppo=");
    inizio += strlen ("gruppo=");
    fine = strstr (inizio,"\r\n");
    if (inizio && fine)
    {
        dim = fine-inizio;
        strncpy (nome_gruppo,inizio,dim);
    }

    inizio = strstr (comando,"utente=");
    inizio += strlen ("utente=");
    fine = strstr (inizio,"\r\n");
    if (inizio && fine)
    {
        dim = fine-inizio;
        strncpy (nome_utente,inizio,dim);
    }

    strcpy (comando,pacchetto);
    inizio = strstr (comando,"richiedente=");
    inizio += strlen ("richiedente=");
    fine = strstr (inizio,"\r\n");
    if (inizio && fine)
    {
        dim = fine-inizio;
        strncpy (nome_richiedente,inizio,dim);
    }
}

char *alloca_comando()
{
    return malloc (LN_STR*sizeof(char*));
}

void alloca_login(char **nome, char **password)
{
    *nome = malloc (LN_STR*sizeof(char));
    *password = malloc (LN_STR*sizeof(char));
}

void alloca_sigin(char **nome, char **password)
{
    *nome = malloc (LN_STR*sizeof(char));
    *password = malloc (LN_STR*sizeof(char));
}


void alloca_crea_gruppo(char **nome_gruppo, char **nome_utente)
{
    *nome_gruppo = malloc (LN_STR*sizeof(char));
    *nome_utente = malloc (LN_STR*sizeof(char));
}

void alloca_messaggio(char **nome_gruppo, char **nome_utente, char **messaggio, char **minutaggio)
{
    *nome_gruppo = malloc (LN_STR*sizeof(char));
    *nome_utente = malloc (LN_STR*sizeof(char));
    *messaggio = malloc (LN_STR*sizeof(char));
    *minutaggio = malloc (LN_STR*sizeof(char));
}

void alloca_cerca_gruppo(char **nome_gruppo, char **nome_utente)
{
    *nome_gruppo = malloc (LN_STR*sizeof(char));
    *nome_utente = malloc (LN_STR*sizeof(char));
}

void alloca_manda_notifica(char **nome_gruppo, char **nome_utente)
{
    *nome_gruppo = malloc (LN_STR*sizeof(char));
    *nome_utente = malloc (LN_STR*sizeof(char));
}

void alloca_accetta_notifica(char **nome_gruppo, char **nome_utente, char **nome_rihiedente)
{
    *nome_gruppo = malloc (LN_STR*sizeof(char));
    *nome_utente = malloc (LN_STR*sizeof(char));
    *nome_rihiedente = malloc (LN_STR*sizeof(char));
}

void dealloca_comando(char **cmd)
{
    free(*cmd);
    *cmd = NULL;
}

void dealloca_login(char **nome, char **password)
{
    free(*nome);
    free(*password);
    *nome = NULL;
    *password = NULL;
}

void dealloca_sigin(char **nome, char **password)
{
    free(*nome);
    free(*password);
    *nome = NULL;
    *password = NULL;
}

void dealloca_crea_gruppo (char **nome_gruppo, char **nome_utente)
{
    free(*nome_gruppo);
    free(*nome_utente);
    *nome_gruppo = NULL;
    *nome_utente = NULL;
}

void dealloca_messaggio_e_minutaggio(char **nome_gruppo, char **nome_utente, char **messaggio, char **minutaggio)
{
    free (nome_gruppo);
    free (nome_utente);
    free(*messaggio);
    free(*minutaggio);
    *messaggio = NULL;
    *minutaggio = NULL;
    *nome_gruppo = NULL;
    nome_utente = NULL;
}

void dealloca_cerca_gruppo(char **nome_gruppo, char **nome_utente)
{
    free(*nome_gruppo);
    free(*nome_utente);
    *nome_gruppo = NULL;
    *nome_utente = NULL;
}

void dealloca_manda_notifica(char **nome_gruppo, char **nome_utente)
{
    free(*nome_gruppo);
    free(*nome_utente);
    *nome_gruppo = NULL;
    *nome_utente = NULL;
}

void dealloca_accetta_notifica(char **nome_gruppo, char **nome_utente, char **nome_rihiedente)
{
    free(*nome_gruppo);
    free(*nome_utente);
    free(*nome_rihiedente);
    *nome_gruppo = NULL;
    *nome_utente = NULL;
    *nome_rihiedente = NULL;
}

////// formatting ///////

void format_login_risposta(const int comando, char * const pacchetto_da_spedire) {
    if (comando == LOGINOK) {

    }
}
void format_signin_risposta(const int comando, char * const pacchetto_da_spedire);
void format_crea_gruppo_risposta(const int comando, char * const pacchetto_da_spedire);
void format_messaggio_risposta(const int comando, char * const pacchetto_da_spedire);
void format_cerca_gruppo(const int comando, char * const pacchetto_da_spedire);
void format_manda_notifica(const int comando, char * const pacchetto_da_spedire);
void format_accetta_notifica(const int comando, char * const pacchetto_da_spedire);
void format_pacchetto_non_riconosciuto(const int comando, char * const pacchetto_da_spedire);

void format_add_inizio_gruppi(char * pacchetto_da_spedire);
void format_add_fine_gruppi(char * pacchetto_da_spedire);
void format_add_inizio_messaggi(char * pacchetto_da_spedire);
void format_add_fine_messaggi(char * pacchetto_da_spedire);

void format_add_nome_gruppo(char * pacchetto_da_spedire, const char * const nome_gruppo);
void format_add_mittente_messaggio(char * pacchetto_da_spedire, const char * const nome_mittente_messaggio);
void format_add_contenuto_messaggio(char * pacchetto_da_spedire, const char * const contenuto_messaggio);
void format_add_minutaggio_messaggio(char * pacchetto_da_spedire, const char * const minutaggio_messaggio);
void format_add_notificante(char * pacchetto_da_spedire, const char * const nome_notificante);