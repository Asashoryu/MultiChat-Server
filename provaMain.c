#include <stdio.h>
#include <string.h>

#include "gestore_pacchetti.h"

int main ()
{
    char pac[200];
    strcpy (pac, "cmd=100\r\nnome=Alex\r\npassword=pass");
    printf ("%s\n",pac);
    char *cmd = parse_comando (pac);
    printf ("%s\n",cmd);

    printf("provo a stampare /");
    return 0;
}