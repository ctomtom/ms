#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
typedef struct element
{ char entite[12];
  char type[12];
  char nature[12];
  int ligne; int colonne; int size;
  char v[12];
  struct element *svt;
}listelm;

listelm* liste=NULL;

listelm* recherche(char val[12])
{listelm* parc;
parc=liste; 
while(parc!=NULL)
{if(strcmp(parc->entite,val)==0){return parc;}else{parc=parc->svt;}}
return parc;
}

void inserer(char entite[12],char nature[12],char type[12],int l,int s,char v[12])
{
listelm *parc,*nouveau;

if(liste==NULL){liste=malloc(sizeof(listelm));strcpy(liste->entite,entite);strcpy(liste->type,type);strcpy(liste->nature,nature);
  liste->ligne=l;liste->size=s;strcpy(liste->v,v);liste->svt=NULL;}
  else
  {nouveau=malloc(sizeof(listelm));strcpy(nouveau->entite,entite);strcpy(nouveau->type,type);strcpy(nouveau->nature,nature);
  nouveau->ligne=l;nouveau->size=s;strcpy(nouveau->v,v); parc=liste;
   while(parc->svt!=NULL){parc=parc->svt;} parc->svt=nouveau;nouveau->svt=NULL;}

}

void afficher()
{listelm *parc;FILE* f=NULL; 
parc=liste;
printf("%-12s%-12s%-12s%-12s\n","entite","type","nature","taille");
f=fopen("tablesymb.txt","w+");
fprintf(f,"%-12s%-12s%-12s%-12s\n","entite","type","nature","taille");
while(parc!=NULL){printf("%-12s%-12s%-12s%-12d\n", parc->entite, parc->type, parc->nature,parc->size);
fprintf(f,"%-12s%-12s%-12s%-12d\n", parc->entite, parc->type, parc->nature,parc->size);
parc=parc->svt;}
fclose(f);
}


