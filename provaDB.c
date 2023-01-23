// gcc -o provaDB provaDB.c database.c -I/usr/include/postgresql -L/usr/lib/postgresql/15/lib -lpq
#include <stdio.h>
#include <string.h>
#include <libpq-fe.h>
#include "database.h"

#define UTENTE_ID 1
#define NOME "giacomo"
#define PASSWORD "giacomino12"

int main() {
    int id = UTENTE_ID;
    char nome[100];
    char password[100];
    strcpy(nome, NOME);
    strcpy(password, PASSWORD);

    //insert_utente_db(id, nome, password);
}