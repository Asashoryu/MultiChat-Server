#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *parse_comando(char *pacchetto)
{
    char *inizio = NULL;
    char *fine = NULL;
    int dim = 0;
    char comando[200];
    char *cmd = NULL;

    strcpy (comando,pacchetto);
    printf ("\n");
    inizio = strstr (comando,"cmd=");
    printf ("\n");
    inizio += strlen ("cmd=");
    fine = strstr (inizio,"\r\n");
    if (inizio && fine)
    {
        dim = fine - inizio;
        strncpy (cmd,inizio,dim);
        cmd[dim] = '\0';
        return cmd;
    }
    return NULL;
}