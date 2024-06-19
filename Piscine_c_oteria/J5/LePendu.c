#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

char CRead();
int CompareChar(char c1,char c2);
int CompareChaine(char chaine1[],char chaine2[]);
void  TrouveMot(FILE *fichier,char chaine[]);
void InitiaChaine(char chaine2[],char c,int j);
int LettreUtilise(char c,char chaine[]);
void MotAct(char chaine[],char chaine2[]);
int PosChar(char c,char chaine[]);
void PlacerCar(char,char[]);



int main() {
  printf("\nBienvenue au Pendu !\n");
  printf("----------------------------------\n");
  printf("Le Principe est de deviné le mot lettre par lettre.\nBonne chance !\n\n");
  FILE* fichier = NULL;
  srand(time(NULL));
  int life = 10;
  char motSecret[15]={0},motActuel[15]={0},lettreProposer[11];
  char c;


      life = 10;
      TrouveMot(fichier,motSecret);
		if (strlen(motSecret) > 0) {
	    	InitiaChaine(lettreProposer,'0',11);
	    	InitiaChaine(motActuel,'*',strlen(motSecret));
	    	printf("Le mot secret : %s,Tentatives : %d\nLe jeu commence !\n",motActuel,life );

	    	do {
	        	printf("Donnez une lettre : \n");
	        	c = CRead();
	        	if ( !(c < 'A') || (c > 'Z')) {
	        	if (!LettreUtilise(c,motActuel) && !LettreUtilise(c,lettreProposer))
	       		{
	            	if (LettreUtilise(c,motSecret)) {
	              	printf("la lettre existe !\n");
	              	int i = 0;
	                	do {
	                		if (CompareChar(c,motSecret[i])) motActuel[i] = motSecret[i];
	                    	i++;
	                	} while(motSecret[i] != '\0');
	                	printf("%s\n",motActuel);
	              	} else
	              	{
	               		life--;
	               		printf("Nope !\nLe mot secret : %s\nTentative(s) restante(s) : %d\n",motActuel,life);
	               		PlacerCar(c,lettreProposer);
	              }
	          } else printf("Déjà proposé !\n");
	        } else printf("Ce n'est pas une lettre !\nLe mot secret : %s\nTentative(s) restante(s) : %d\n",motActuel,life);

	        }while ((!CompareChaine(motActuel,motSecret)) && (life != 0));

	        if (life == 0) {
	        	printf("_____________\n");
	        	printf(" | /       |\n");
	        	printf(" |/        O\n");
	        	printf(" |        -|-\n");
	        	printf(" |         /\\\n");
	        	printf(" |\n");
	        	printf("_|____________\n");
	        	printf("Trop tard tu es mort !\n");
	        	printf("Le mot à trouver étais : %s\n",motSecret);
	        }
	        else printf("Vous avez Gagné ! Bravo\n");

	        }
        else printf("Le Dictionnaire est introuvable !\n");



  return 0;
}

char CRead()
{
  char car = 0;
  car = getchar();
  car = toupper(car);
  while (getchar() != '\n');
  return car;
}

int CompareChar(char c1,char c2)
{
    if (c1 == c2) return 1;else return 0;
}

int CompareChaine(char chaine1[],char chaine2[]) // retourne 1 si Kifkif , 0 Sinon
{
  size_t i;
  int sortie = 1;
    for (i = 0; i < ((strlen(chaine1)>strlen(chaine2))?strlen(chaine1):strlen(chaine2)) ;i++) if (chaine1[i] != chaine2[i]) sortie = 0;
    return sortie;
}

void  TrouveMot(FILE *fichier,char chaine[])
{
    int i = 0,MAX,MIN = 1;
    char c;
    fichier = fopen("Dictionnaire.txt","r");
    if (fichier != NULL)
    {
      while ((c = fgetc(fichier)) != EOF)
      {
          if (c == '\n') {
            i++;
          }
      }
      MAX = i;
      rewind(fichier);
      int line = (rand() % (MAX - MIN + 1)) + MIN; //Generateur de nombre aléatoire
      if (line == 1) rewind(fichier);
      else
      {
      while (line - 2 >= 0)
      {
          c = fgetc(fichier);
          if (c == '\n')
          line--;
      }
      }
      fgets(chaine,15,fichier);
      chaine[strlen(chaine)-1] = '\0';
      fclose(fichier);
    } else printf("Erreur d'ouverture du fichier\n");
}

void MotAct(char chaine[],char chaine2[])
{
    size_t i = 0;
    while (i < strlen(chaine))
    {
        chaine2[i] = '*';
        i++;
    }
    chaine2[strlen(chaine)] = '\0';
}

void InitiaChaine(char chaine[],char c,int j)
{
    int i = 0;
    while (i < j)
    {
        chaine[i] = c;
        i++;
    }
    chaine[j] = '\0';
}

int LettreUtilise(char c,char chaine[])
{
    int i;
    for (i = 0; (c != chaine[i]) && (chaine[i] != '\0') ;i++);
    if (chaine[i] != '\0') return 1; else return 0;
}

void PlacerCar(char c,char chaine[])
{
  int i;
    for (i=0; chaine[i] != '0' ;i++);
    chaine[i] = c;
}

int PosChar(char c,char chaine[])
{
  size_t i;
    for (i=0;(chaine[i] != '\0') && (chaine[i] != c);i++);
    if (i <= strlen(chaine)) return i;
    else return -1;
}
