#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

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

void parse_messaggio(const char * const pacchetto, char * nome_gruppo, char * nome_utente, char * messaggio)
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
}

void parse_accetta_notifica(const char * const pacchetto, char * nome_gruppo, char * nome_utente)
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

char *alloca_comando()
{
    return malloc (LN_STR*sizeof(char*));
}

void alloca_nome_e_password(char **nome, char **password)
{
    *nome = malloc (LN_STR*sizeof(char));
    *password = malloc (LN_STR*sizeof(char));
}

void alloca_gruppo_e_nome(char **gruppo, char **nome)
{
    *gruppo = malloc (LN_STR*sizeof(char));
    *nome = malloc (LN_STR*sizeof(char));
}

void alloca_messaggio(char *messaggio)
{
    messaggio = malloc (200*sizeof(char*));
}

void dealloca_comando(char **cmd)
{
    free(*cmd);
    *cmd = NULL;
}

void dealloca_nome_password(char **nome, char **password)
{
    free(*nome);
    free(*password);
    *nome = NULL;
    *password = NULL;
}

// void dealloca_gruppo_e_nome(char *gruppo, char *nome)
// {
//     free(gruppo);
//     free(nome);
// }

// void dealloca_messaggio(char *messaggio)
// {
//     free(messaggio);
// }