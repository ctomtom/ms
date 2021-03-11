#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include<malloc.h>


void codeinutile(){
listequad* parc=NULL,*parc2=NULL,*supp=NULL;
 parc=listeq;supp=listeq;
 while(parc!=NULL)
   {if(strcmp(parc->op,":=")==0||strcmp(parc->op,"+")==0||strcmp(parc->op,"-")==0||strcmp(parc->op,"/")==0||strcmp(parc->op,"*")==0)
 	     {parc2=parc->svt;
 	      while(parc2!=NULL&&strcmp(parc2->op1,parc->res)!=0&&strcmp(parc2->op2,parc->res)!=0&&strcmp(parc2->res,parc->res)!=0&&atoi(parc2->op1)!=parc->num)
          {parc2=parc2->svt;}
        if(parc2==NULL){strcpy(parc->op,"");strcpy(parc->op1,"");strcpy(parc->op2,"");strcpy(parc->res,"");}
        }
        parc=parc->svt;
    }

}

void simpalgebrique(){
listequad* parc=NULL;
parc=listeq;
while(parc!=NULL){
  if(strcmp(parc->op,"*")==0)
  	{if(strcmp(parc->op1,"2")==0){strcpy(parc->op1,parc->op2);strcpy(parc->op,"+");}
     if(strcmp(parc->op2,"2")==0){strcpy(parc->op2,parc->op1);strcpy(parc->op,"+");}
     if(strcmp(parc->op1,"1")==0){strcpy(parc->op1,parc->op2);strcpy(parc->op2,"");strcpy(parc->op,":=");}
     if(strcmp(parc->op2,"1")==0){strcpy(parc->op2,"");strcpy(parc->op,":=");}
     if(strcmp(parc->op1,"0")==0){strcpy(parc->op2,"");strcpy(parc->op,":=");}
     if(strcmp(parc->op2,"0")==0){strcpy(parc->op2,"");strcpy(parc->op1,"0");strcpy(parc->op,":=");}
    }
  if(strcmp(parc->op,"/")==0)
    {if(strcmp(parc->op2,"1")==0){strcpy(parc->op2,"");strcpy(parc->op,":=");}
     if(strcmp(parc->op1,parc->op2)==0){strcpy(parc->op1,"1");strcpy(parc->op2,"");strcpy(parc->op,":=");}
    }
  if(strcmp(parc->op,"+")==0)
    {if(strcmp(parc->op1,"0")==0){strcpy(parc->op1,parc->op2);strcpy(parc->op2,"");strcpy(parc->op,":=");}
     if(strcmp(parc->op2,"0")==0){strcpy(parc->op2,"");strcpy(parc->op,":=");}
    }
  if(strcmp(parc->op,"-")==0)
    {if(strcmp(parc->op1,parc->op2)==0){strcpy(parc->op2,"");strcpy(parc->op1,"0");strcpy(parc->op,":=");}
     if(strcmp(parc->op2,"0")==0){strcpy(parc->op2,"");strcpy(parc->op,":=");}

    }
parc=parc->svt;}
free(parc);
}

void propcopie(){
listequad* parc=NULL;listequad* parc2=NULL;int nbr=0;
parc=listeq;
while(parc!=NULL){
            parc2=parc->svt;
            while(parc2!=NULL&&nbr==0){if(strcmp(parc->op,":=")==0)
                                        {if(strcmp(parc2->res,parc->res)==0){nbr++;}
                                         else{if(strcmp(parc2->op1,parc->res)==0){strcpy(parc2->op1,parc->op1);}
                                               if(strcmp(parc2->op2,parc->res)==0){strcpy(parc2->op2,parc->op1);}
                                              }}
                                parc2=parc2->svt;
                               }
                  parc=parc->svt;
	              }
free(parc2);free(parc);
}

void expredondante(){
listequad* parc=NULL,*parc2=NULL;int nbr;
parc=listeq;
while(parc!=NULL){
          nbr=0;
          parc2=parc->svt;
         while(parc2!=NULL&&nbr==0)
          {if(strcmp(parc2->res,parc->op1)==0||strcmp(parc2->res,parc->op2)==0){nbr++;}
          else
            {if(strcmp(parc2->op1,parc->op1)==0&&strcmp(parc2->op2,parc->op2)==0)
              {if(strcmp(parc->op,parc2->op)==0)
                {if(nbr==0){strcpy(parc2->op,":=");strcpy(parc2->op1,parc->res);strcpy(parc2->op2,"");}
                  }
                   }
                  parc2=parc2->svt;}
                 }
     parc=parc->svt;}
free(parc);free(parc2);}

void opti(){
listequad *parcq=NULL; FILE* m=NULL;
parcq=listeq;
if(parcq!=NULL) {printf("%-12s%-12s%-12s%-12s%-12s\n","Numero","Operation","Operande1","Operande2","Resultat");}
m=fopen("quadopti.txt","w+");
fprintf(m, "%-12s%-12s%-12s%-12s%-12s\n","Numero","Operation","Operande1","Operande2","Resultat");
while(parcq!=NULL){
if(strcmp(parcq->op,"")!=0){
printf("%-12d%-12s%-12s%-12s%-12s\n",parcq->num,parcq->op,parcq->op1,parcq->op2,parcq->res);
fprintf(m,"%-12d%-12s%-12s%-12s%-12s\n",parcq->num,parcq->op,parcq->op1,parcq->op2,parcq->res);
}
parcq=parcq->svt;}
fclose(m);}

