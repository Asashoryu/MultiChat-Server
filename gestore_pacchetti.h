#ifndef GESTORE_PACCHETTI_H
#define GESTORE_PACCHETTI_H

// i comandi seguono questa logica:
// prima cifra=(codice comando); 
// seconda cifra=(mittente: 0 se client, 1 se server);
// terza cifra=(flag accessorio: 0 no flag, 1 se il comando è stato ricevuto, 2 errore generico)

#define LN_STR 1000

// comandi (client)
#define LOGIN 100
#define SIGNIN 200
#define CREAGRUP 300
#define SENDMESS 400
#define SEARCHGRUP 500
#define SENDNOTIFICA 600
#define ACCETTAUT 700
// comandi OK (server)
#define LOGINOK 111
#define SIGNINOK 211
#define CREAGRUPOK 311
#define SENDMESSOK 411
#define SEARCHGRUPOK 511
#define SENDNOTIFICAOK  611
#define ACCETTAUTOK 711
// comandi ERROR (server)
#define LOGINERR 112
#define SIGNINERR 212
#define CREAGRUPERR 312
#define SENDMESSERR 412
#define SEARCHGRUPERR 512
#define SENDNOTIFICAERR  612
#define ACCETTAUTERR 712
// 3
#define LOGINNONTROVATO 113
#define SIGNGIAREGISTRATO 213
#define CREAGRUPGIAREGISTRATO 313

// errore cattiva formattazione pacchetto
#define PACCHETTONONCOMPRESO 999

// restituisce il tipo di comando ricevuto dal pacchetto
char *parse_comando(char *pacchetto);
void parse_login(const char * const pacchetto, char * nome, char * password);
void parse_signin(const char * const pacchetto, char * nome, char * password);
void parse_crea_gruppo(const char * const pacchetto, char * nome_gruppo, char * nome_utente);
void parse_messaggio(const char * const pacchetto, char * nome_gruppo, char * nome_utente, char * messaggio, char * minutaggio);
void parse_cerca_gruppo(const char * const pacchetto, char * nome_utente, char * nome_gruppo);
void parse_manda_notifica(const char * const pacchetto, char * nome_utente, char * nome_gruppo);
void parse_accetta_notifica(const char * const pacchetto, char * nome_utente, char * nome_gruppo, char * nome_richiedente);

char *alloca_comando();
void alloca_nome_e_password(char **nome, char **password);
void alloca_gruppo_e_utente(char **gruppo, char **nome);
void alloca_messaggio_e_minutaggio(char **messaggio, char **minutaggio);

void dealloca_comando(char **cmd);
void dealloca_nome_password(char **nome, char **password);
void dealloca_gruppo_e_utente(char **gruppo, char **nome);
void dealloca_messaggio_e_minutaggio(char **messaggio, char **minutaggio);

void format_login_risposta(const int comando, char * const pacchetto_da_spedire);
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
void format_add_inizio_notifiche(char * pacchetto_da_spedire);
void format_add_fine_notifiche(char * pacchetto_da_spedire);

void format_add_nome_gruppo(char * pacchetto_da_spedire, const char * const nome_gruppo);
void format_add_mittente_messaggio(char * pacchetto_da_spedire, const char * const nome_mittente_messaggio);
void format_add_contenuto_messaggio(char * pacchetto_da_spedire, const char * const contenuto_messaggio);
void format_add_minutaggio_messaggio(char * pacchetto_da_spedire, const char * const minutaggio_messaggio);
void format_add_notificante(char * pacchetto_da_spedire, const char * const nome_notificante);
void format_add_gruppo_notificato(char * pacchetto_da_spedire, const char * const gruppo_notificato);

#endif