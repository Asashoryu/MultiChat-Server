#ifndef GESTORE_PACCHETTI_H
#define GESTORE_PACCHETTI_H

// i comandi seguono questa logica:
// prima cifra=(codice comando); 
// seconda cifra=(mittente: 0 se client, 1 se server);
// terza cifra=(flag accessorio: 0 no flag, 1 se il comando è stato ricevuto, 2 errore generico)

// comandi (client)
#define LOGIN 100
#define SIGNIN 200
#define CREAGRUP 300
#define SENDMESS 400
#define ACCETTAUT 500
// comandi OK (server)
#define LOGINOK 111
#define SIGNINOK 211
#define CREAGRUPOK 311
#define SENDMESSOK 411
#define ACCETTAUTOK 511
// comandi ERROR (server)
#define LOGINERR 112
#define SIGNINERR 212
#define CREAGRUPERR 312
#define SENDMESSERR 412
#define ACCETTAUTERR 512

// restituisce il tipo di comando ricevuto dal pacchetto
char *parse_comando(const char * const pacchetto);
void parse_login(const char * const pacchetto, char * nome, char * password);
void parse_signin(const char * const pacchetto, char * nome, char * password);
void parse_crea_gruppo(const char * const pacchetto, char * nome_gruppo, int utente_id);
void parse_messaggio(const char * const pacchetto, int gruppo_id, int utente_id, char * messaggio);

char *format_response(const int codice_comando);

#endif