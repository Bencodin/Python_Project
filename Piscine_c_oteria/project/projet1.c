#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
 
#define true 0
#define false 1
 
 
struct personne
{
    char prenom[4096];
    char nom[4096];
    char localite[4096];
    char tel[4096];
 
};
typedef struct personne perso;
 
void saisir(perso *tab,int n,char nomfich[]);
void lister(perso *tab,int n);
void rechercher(perso *tab,int n,char num1[100]);
void rechercher1(perso *tab,int n,char local[200]);
void supprimer(perso *tab,int n,char num1[100],char nomfich[]);
 
int main()
{
    printf("BIENVENUE DANS LE PROGRAMME DE GESTION D'ANNUAIRE TELEPHONIQUE\n");
    int choix,n;
    int new_choice;
    char num1[100],name[200];
    char local[200];
    perso *tab= NULL;
    printf("donner le nombre de personne a ajouter\n");
    scanf("%d",&n);
    tab=(perso *)malloc(n* sizeof(perso));
    
do
{   printf("********ANNUAIRE_OTERIA********\n");
    printf("1--> Ajouter des personnes\n");
    printf("2--> lister les personnes\n");
    printf("3--> rechercher une personne\n");
    printf("4--> rechercher une personne connaissant sa localite*\n");
    printf("5--> Supprimer une persone\n");
    printf("6--> quitter\n");
    printf("********ANNUAIRE_OTERIA********\n");
    printf("faite votre Oteri_choix\n");
    
    scanf("%d",&choix);
    
    switch(choix)
    {
        case 1:
	       printf("donner le nom du nouveau fichier  \n");
               scanf("%s",name);
               printf("le nom du fichier est :\t%s\n",name);
               printf("Saisir les informations sur les personnes\n");
               saisir(tab,n,name);
               break;
        case 2: 
	       printf("Liste des personnes:\n");
               lister(tab,n);
               break;
        case 3:
	       printf("recherche d 'une personne\n");
               printf("entrer le numero de telephone\n");
               scanf("%s",num1);
               rechercher(tab,n,num1);
                break;
        case 4:
	       	printf("recherche d 'une personne connaissant sa localite\n");
                printf("entrer la localite\n");
                scanf("%s",local);
                rechercher1(tab,n,local);
                break;
        case 5: 
		printf("suppression d 'une personne\n");
                printf("entrer le numero de telephone\n");
                scanf("%s",num1);
                supprimer(tab,n,num1,name);
                break;
     
        default:
		if (choix <= 6  )  
		{
		break;
		}
		else
		{
		   printf("entre un nombre entre 1 et 7\n");
	   	   // scanf("%d",&choix);
		  

		}
    }
}
while(choix!=6);
printf("vous êtes deconnecté :(\n");
free(tab);
return 0;
}
 
void saisir(perso *tab,int n,char nomfich[])
{   FILE *f;
    int i;

    //char * positionEntree = NULL; //change
    
    f=fopen(nomfich,"a+");
    for(i=0;i<n;i++)
    {
        printf("entrer les informations de la personne %d\n",i+1);
        printf("donner son nom\n");
        scanf("%s",tab[i].nom);
        printf("entrer son prenom\n");
        scanf("%s",tab[i].prenom);
        printf("entrer sa localite\n");
        scanf("%s",tab[i].localite);
        printf("entrer le numero de telephone\n");
        scanf("%s",tab[i].tel);
    }
        for(i=0;i<n;i++)
        {
        fprintf(f, "nom:%s\nprenom:%s\nlocalite:%s\ntelephone:%s\n", tab[i].nom,tab[i].prenom,tab[i].localite,tab[i].tel);
        fclose(f);
    }
}
 
void lister(perso *tab,int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        printf("Personne %d\n",i+1);
        printf("Nom:%s\n",tab[i].nom);
        printf("Prenom:%s\n",tab[i].prenom);
        printf("Localite:%s\n",tab[i].localite);
        printf("Tel:%s\n",tab[i].tel);
    }
}
void rechercher(perso *tab,int n,char num1[10])
{
 int i,trouve,p;
 char trouveprenom[20],trouvenumero[10],trouvenom[20];
 trouve=false;
 i=0;
 while((i<n)&&(trouve==false))
 {
     p=strcmp(num1,tab[i].tel);
     if(p==0)
     {
        strcpy(trouveprenom,tab[i].prenom);
        strcpy(trouvenom,tab[i].nom);
        strcpy(trouvenumero,tab[i].tel);
        trouve=true;
     }
     else
     i++;
 }
 if(trouve==true)
     {
        printf("Nom:%s\n",tab[i].nom);
        printf("Prenom:%s\n",tab[i].prenom);
        printf("Localite:%s\n",tab[i].localite);
        printf("Telephone:%s\n",tab[i].tel);
 
     }
 else
 printf("ce nom n existe pas dans l'annuaire\n");
 }
void rechercher1(perso *tab,int n,char local[20])
{
 int i,trouve,p;
 char trouveprenom[20],trouvenom[20],trouvetel[20];
 trouve=false;
 i=0;
 while((i<n)&&(trouve==false))
 {
     p=strcmp(local,tab[i].localite);
     if(p==0)
     {
        strcpy(trouveprenom,tab[i].prenom);
        strcpy(trouvenom,tab[i].nom);
        strcpy(trouvetel,tab[i].tel);
        trouve=true;
     }
     else
     i++;
 }
 if(trouve==true)
 {
        printf("Nom:%s\n",trouvenom);
        printf("Prenom:%s\n",trouveprenom);
        printf("Telephone:%s\n",trouvetel);
 }
 else
 printf("ce numero n existe pas dans l'annuaire\n");
 }
 
 
 /**********fonction_supprimer**********/


void supprimer(perso *tab,int n,char num1[10],char nomfich[])
{
    int i;
  FILE *fichier, *sortie;
  char enleve[32];
  do
    {
     fichier = fopen("annuaire.txt", "r");
     if (!fichier)
         printf("ERREUR: Impossible d'ouvrir le fichier: \n");
    }
  while (!fichier);
  do
    {
 
     sortie = fopen("suppression.txt", "w");
     if (!sortie)
         printf("ERREUR: Impossible d'ouvrir fichier: \n");
    }
  while (!sortie);
  /* Saisie de l'enregistrement à supprimer */
  printf("Enregistrement à supprimer : ");
  scanf("%s",enleve);
  i=0;
  while (!feof(fichier))
    {
 
     fscanf(fichier, "%s\n", tab[i].nom);
 
     if (strcmp(tab[i].nom, enleve) != 0)
     {
          fprintf(sortie, "%s\n", tab[i].nom);
          fprintf(sortie, "%s\n", tab[i].prenom);
          fprintf(sortie, "%s\n", tab[i].localite);
          fprintf(sortie, "%s\n", tab[i].tel);
     }
     i++;
    }
  /* Fermeture des fichiers */
  fclose(sortie);
  fclose(fichier);
//  key=getch();
 
}

