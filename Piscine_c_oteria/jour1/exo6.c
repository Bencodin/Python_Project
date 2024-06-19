#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
int main(int argc, char *argv[])
{
    char nom[100] = {0};
 
    write(1,&nom,sizeof(nom));
    scanf("%s", nom);
    write(1,&nom,sizeof(nom));
 
    return 0;
}
