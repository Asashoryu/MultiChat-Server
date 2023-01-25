#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "gestore_pacchetti.h"

#define LN_STR 1000

int parse_comando(const char * const pacchetto)
{
    char *inizio = NULL;
    char *fine = NULL;
    int dim = 0;
    char comando[200];
    char *cmd = malloc(200*sizeof(char));
    int cmd_valore = 0;

    strcpy (comando, pacchetto);
    inizio = strstr (comando,"cmd=");
    inizio += strlen ("cmd=");
    fine = strstr (inizio,"\r\n");
    if (inizio && fine)
    {
        dim = fine-inizio;
        strncpy (cmd,inizio,dim);
        cmd[dim] = '\0';
        cmd_valore = atoi(cmd);
        return cmd_valore;
    }
    return 0;
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
        nome[dim] = '\0';
     }

     inizio = strstr (comando,"password=");
     inizio += strlen ("password=");
     fine = strstr (inizio,"\r\n");
     if (inizio && fine)
     {
        dim = fine-inizio;
        strncpy (password,inizio,dim);
        password[dim] = '\0';
     }
}

void parse_signin(const char * const pacchetto, char * nome, char * password)
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
        nome[dim] = '\0';
     }

     inizio = strstr (comando,"password=");
     inizio += strlen ("password=");
     fine = strstr (inizio,"\r\n");
     if (inizio && fine)
     {
        dim = fine-inizio;
        strncpy (password,inizio,dim);
        password[dim] = '\0';
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
        nome_gruppo[dim] = '\0';
    }

    inizio = strstr (comando,"utente=");
    inizio += strlen ("utente=");
    fine = strstr (inizio,"\r\n");
    if (inizio && fine)
    {
        dim = fine-inizio;
        strncpy (nome_utente,inizio,dim);
        nome_utente[dim] = '\0';
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
        nome_gruppo[dim] = '\0';
    }

    inizio = strstr (comando,"utente=");
    inizio += strlen ("utente=");
    fine = strstr (inizio,"\r\n");
    if (inizio && fine)
    {
        dim = fine-inizio;
        strncpy (nome_utente,inizio,dim);
        nome_utente[dim] = '\0';
    }

    inizio = strstr (comando,"messaggio=");
    inizio += strlen ("messaggio=");
    fine = strstr (inizio,"\r\n");
    if (inizio && fine)
    {
        dim = fine-inizio;
        strncpy (messaggio,inizio,dim);
        messaggio[dim] = '\0';
    }

    inizio = strstr (comando,"minutaggio=");
    inizio += strlen ("minutaggio=");
    fine = strstr (inizio,"\r\n");
    if (inizio && fine)
    {
        dim = fine-inizio;
        strncpy (minutaggio,inizio,dim);
        minutaggio[dim] = '\0';
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
        nome_gruppo[dim] = '\0';
    }

    inizio = strstr (comando,"utente=");
    inizio += strlen ("utente=");
    fine = strstr (inizio,"\r\n");
    if (inizio && fine)
    {
        dim = fine-inizio;
        strncpy (nome_utente,inizio,dim);
        nome_utente[dim] = '\0';
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
        nome_gruppo[dim] = '\0';
    }

    inizio = strstr (comando,"utente=");
    inizio += strlen ("utente=");
    fine = strstr (inizio,"\r\n");
    if (inizio && fine)
    {
        dim = fine-inizio;
        strncpy (nome_utente,inizio,dim);
        nome_utente[dim] = '\0';
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
        nome_gruppo[dim] = '\0';
    }

    inizio = strstr (comando,"utente=");
    inizio += strlen ("utente=");
    fine = strstr (inizio,"\r\n");
    if (inizio && fine)
    {
        dim = fine-inizio;
        strncpy (nome_utente,inizio,dim);
        nome_utente[dim] = '\0';
    }

    strcpy (comando,pacchetto);
    inizio = strstr (comando,"richiedente=");
    inizio += strlen ("richiedente=");
    fine = strstr (inizio,"\r\n");
    if (inizio && fine)
    {
        dim = fine-inizio;
        strncpy (nome_richiedente,inizio,dim);
        nome_richiedente[dim] = '\0';
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

void alloca_signin(char **nome, char **password)
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

void dealloca_login(char **nome, char **password)
{
    free(*nome);
    free(*password);
    *nome = NULL;
    *password = NULL;
}

void dealloca_signin(char **nome, char **password)
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

void dealloca_messaggio(char **nome_gruppo, char **nome_utente, char **messaggio, char **minutaggio)
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
        format_add_inizio_intestazione(pacchetto_da_spedire);
        sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "cmd=%d\r\nmessaggio=Utente loggato con successo\r\n", LOGINOK);
        format_add_fine_intestazione(pacchetto_da_spedire);
    }
    else if (comando == LOGINERR) {
        format_add_inizio_intestazione(pacchetto_da_spedire);
        sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "cmd=%d\r\nmessaggio=Errore nel login: non è stato possibile accedere al Database\r\n", LOGINERR);
        format_add_fine_intestazione(pacchetto_da_spedire);
    }
    else if (comando == LOGINNONTROVATO) {
        format_add_inizio_intestazione(pacchetto_da_spedire);
        sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "cmd=%d\r\nmessaggio=Utente non trovato\r\n", LOGINNONTROVATO);
        format_add_fine_intestazione(pacchetto_da_spedire);
    }
}

void format_signin_risposta(const int comando, char * const pacchetto_da_spedire) {
    if (comando == SIGNINOK) {
        format_add_inizio_intestazione(pacchetto_da_spedire);
        sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "cmd=%d\r\nmessaggio=Utente registrato con successo\r\n", LOGINOK);
        format_add_fine_intestazione(pacchetto_da_spedire);
    }
    else if (comando == SIGNINERR) {
        format_add_inizio_intestazione(pacchetto_da_spedire);
        sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "cmd=%d\r\nmessaggio=Errore nel sign in: non è stato possibile accedere al Database\r\n", LOGINERR);
        format_add_fine_intestazione(pacchetto_da_spedire);
    }
    else if (comando == SIGNGIAREGISTRATO) {
        format_add_inizio_intestazione(pacchetto_da_spedire);
        sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "cmd=%d\r\nmessaggio=Utente già registrato\r\n", SIGNGIAREGISTRATO);
        format_add_fine_intestazione(pacchetto_da_spedire);
    }
}

void format_crea_gruppo_risposta(const int comando, char * const pacchetto_da_spedire) {
    if (comando == CREAGRUPOK) {
        format_add_inizio_intestazione(pacchetto_da_spedire);
        sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "cmd=%d\r\nmessaggio=Gruppo creato con successo\r\n", LOGINOK);
        format_add_fine_intestazione(pacchetto_da_spedire);
    }
    else if (comando == CREAGRUPERR) {
        format_add_inizio_intestazione(pacchetto_da_spedire);
        sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "cmd=%d\r\nmessaggio=Errore nella creazione del gruppo: non è stato possibile accedere al Database\r\n", LOGINERR);
        format_add_fine_intestazione(pacchetto_da_spedire);
    }
    else if (comando == CREAGRUPGIAREGISTRATO) {
        format_add_inizio_intestazione(pacchetto_da_spedire);
        sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "cmd=%d\r\nmessaggio=Il gruppo esiste già\r\n", SIGNGIAREGISTRATO);
        format_add_fine_intestazione(pacchetto_da_spedire);
    }
}

void format_messaggio_risposta(const int comando, char * const pacchetto_da_spedire) {
    if (comando == SENDMESSOK) {
        format_add_inizio_intestazione(pacchetto_da_spedire);
        sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "cmd=%d\r\nmessaggio=Messaggio ricevuto\r\n", SENDMESSOK);
        format_add_fine_intestazione(pacchetto_da_spedire);
    }
    else if (comando == SENDMESSERR) {
        format_add_inizio_intestazione(pacchetto_da_spedire);
        sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "cmd=%d\r\nmessaggio=Errore nel send del messaggio: non è stato possibile accedere al Database\r\n", SENDMESSERR);
        format_add_fine_intestazione(pacchetto_da_spedire);
    }
}

void format_cerca_gruppo(const int comando, char * const pacchetto_da_spedire) {
    if (comando == SEARCHGRUPOK) {
        format_add_inizio_intestazione(pacchetto_da_spedire);
        sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "cmd=%d\r\nmessaggio=Ricerca gruppi completata\r\n", SEARCHGRUPOK);
        format_add_fine_intestazione(pacchetto_da_spedire);
    }
    else if (comando == SEARCHGRUPERR) {
        format_add_inizio_intestazione(pacchetto_da_spedire);
        sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "cmd=%d\r\nmessaggio=Errore nella ricerca dei gruppi: non è stato possibile accedere al Database\r\n", SEARCHGRUPERR);
        format_add_fine_intestazione(pacchetto_da_spedire);
    }
}

void format_manda_notifica(const int comando, char * const pacchetto_da_spedire) {
    if (comando == SENDNOTIFICAOK) {
        format_add_inizio_intestazione(pacchetto_da_spedire);
        sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "cmd=%d\r\nmessaggio=Notifica mandata con successo\r\n", SENDNOTIFICAOK);
        format_add_fine_intestazione(pacchetto_da_spedire);
    }
    else if (comando == SEARCHGRUPERR) {
        format_add_inizio_intestazione(pacchetto_da_spedire);
        sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "cmd=%d\r\nmessaggio=Errore nell'invio della notifica: non è stato possibile accedere al Database\r\n", SEARCHGRUPERR);
        format_add_fine_intestazione(pacchetto_da_spedire);
    }
}

void format_accetta_notifica(const int comando, char * const pacchetto_da_spedire) {
    if (comando == ACCETTAUTOK) {
        format_add_inizio_intestazione(pacchetto_da_spedire);
        sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "cmd=%d\r\nmessaggio=Notifica accettata con successo\r\n", ACCETTAUTOK);
        format_add_fine_intestazione(pacchetto_da_spedire);
    }
    else if (comando == ACCETTAUTERR) {
        format_add_inizio_intestazione(pacchetto_da_spedire);
        sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "cmd=%d\r\nmessaggio=Errore nell'accettazione della notifica: non è stato possibile accedere al Database\r\n", ACCETTAUTERR);
        format_add_fine_intestazione(pacchetto_da_spedire);
    }
}

void format_pacchetto_non_riconosciuto(const int comando, char * const pacchetto_da_spedire) {
    if (comando == PACCHETTONONCOMPRESO) {
        format_add_inizio_intestazione(pacchetto_da_spedire);
        sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "cmd=%d\r\nmessaggio=Pacchetto non compreso, provare a ripetere l'azione\r\n", PACCHETTONONCOMPRESO);
        format_add_fine_intestazione(pacchetto_da_spedire);
    }
}

void format_add_inizio_gruppi(char * pacchetto_da_spedire) {
    sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "<gruppi>\r\n");
}

void format_add_fine_gruppi(char * pacchetto_da_spedire) {
    sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "</gruppi>\r\n");
}

void format_add_inizio_gruppo(char * pacchetto_da_spedire) {
    sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "<gruppo>\r\n");
}
void format_add_fine_gruppo(char * pacchetto_da_spedire) {
    sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "</gruppo>\r\n");
}

void format_add_inizio_messaggi(char * pacchetto_da_spedire) {
    sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "<messaggi>\r\n");
}

void format_add_fine_messaggi(char * pacchetto_da_spedire) {
    sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "</messaggi>\r\n");
}

void format_add_inizio_messaggio(char * pacchetto_da_spedire) {
    sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "<messaggio>\r\n");
}

void format_add_fine_messaggio(char * pacchetto_da_spedire) {
    sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "</messaggio>\r\n");
}

void format_add_inizio_notifiche(char * pacchetto_da_spedire) {
    sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "<notifiche>\r\n");
}

void format_add_fine_notifiche(char * pacchetto_da_spedire) {
    sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "</notifiche>\r\n");
}

void format_add_inizio_notifica(char * pacchetto_da_spedire) {
    sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "<notifica>\r\n");
}

void format_add_fine_notifica(char * pacchetto_da_spedire) {
    sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "</notifica>\r\n");
}

void format_add_inizio_pacchetto(char* pacchetto_da_spedire) {
    sprintf(pacchetto_da_spedire, "\r\n<pacchetto>\r\n");
}

void format_add_fine_pacchetto(char* pacchetto_da_spedire) {
    sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "</pacchetto>\r\n");
}

void format_add_inizio_intestazione(char* pacchetto_da_spedire) {
    sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "<head>\r\n");
}

void format_add_fine_intestazione(char* pacchetto_da_spedire) {
    sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "</head>\r\n");
}

void format_add_nome_gruppo(char * pacchetto_da_spedire, const char * const nome_gruppo) {
    sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "nome_gruppo=%s\r\n", nome_gruppo);
}

void format_add_mittente_messaggio(char * pacchetto_da_spedire, const char * const nome_mittente_messaggio) {
    sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "mittente=%s\r\n", nome_mittente_messaggio);
}

void format_add_contenuto_messaggio(char * pacchetto_da_spedire, const char * const contenuto_messaggio) {
    sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "contenuto=%s\r\n", contenuto_messaggio);
}

void format_add_minutaggio_messaggio(char * pacchetto_da_spedire, const char * const minutaggio_messaggio) {
    sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "minutaggio=%s\r\n", minutaggio_messaggio);
}

void format_add_notificante(char * pacchetto_da_spedire, const char * const nome_notificante) {
    sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "notificante=%s\r\n", nome_notificante);
}

void format_add_gruppo_notificato(char * pacchetto_da_spedire, const char * const gruppo_notificato) {
    sprintf(pacchetto_da_spedire + strlen(pacchetto_da_spedire), "gruppo_notificato=%s\r\n", gruppo_notificato);
}
