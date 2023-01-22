#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "strutture_dati.h"
#include "database.h"

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