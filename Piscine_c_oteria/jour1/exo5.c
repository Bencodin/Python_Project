#include <unistd.h>
#include <stdio.h>

int o_charpos(char *str, char carac)
{
	
	for(int i = 0; str[i] != '\0';i++)
		if(str[i] == carac)
			return i;
	return -1;
}

int main (void)
{
char *str ="abcdefghifj";
char c ='b';
int pos = o_charpos(str, c);

printf("caractere %c à la position %d, \ndans la chaine %s", c, pos, str); /* juste printf pour tester le pos qui nous renvoie bien la position dans le str */ 
}
