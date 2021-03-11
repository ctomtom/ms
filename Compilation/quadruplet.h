#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include<malloc.h>

typedef struct quadruplet {
char op[12];
char op1[12];
char op2[12];
char res[12];
int  num;
struct quadruplet *svt;
}listequad;

typedef struct pelm
{ char ent[12];
  char typep[12];
  struct pelm *svt;
}pilelm;

typedef struct numquad
{int n;
struct numquad* svt;
}nq;

listequad* listeq=NULL;
int cpt=1;
nq* inst=NULL,*etwhile=NULL;listequad* brfin=NULL,*brwhile=NULL,*brcond=NULL,*qc=NULL;

void ajouterquadruplet(char op[12],char op1[12],char op2[12],char res[12]){
listequad *parcq=NULL;

qc=malloc(sizeof(listequad));strcpy(qc->op,op);strcpy(qc->op1,op1);strcpy(qc->op2,op2);strcpy(qc->res,res);
qc->num=cpt;cpt=cpt+1;
if(listeq==NULL){listeq=qc;listeq->svt=NULL;//qc=nouveau;
}
else{parcq=listeq;
while(parcq->svt!=NULL){parcq=parcq->svt;} parcq->svt=qc;qc->svt=NULL;}
}

void maj_quad(listequad* q,int col, char val [12]){
  if(col==0){strcpy(q->op,val);}
  else  {if(col==1){strcpy(q->op1,val);}
          else{ if(col==2){strcpy(q->op2,val);}
               else {if(col==3){strcpy(q->res,val);}}}
      }
}

void afficherquadrupletpremiere()
{listequad *parcq=NULL; FILE* m=NULL;
parcq=listeq;
if(parcq!=NULL) {printf("%-12s%-12s%-12s%-12s%-12s\n","Numero","Operation","Operande1","Operande2","Resultat");}
m=fopen("quad.txt","w+");
fprintf(m,"%-12s%-12s%-12s%-12s%-12s\n","Numero","Operation","Operande1","Operande2","Resultat");
while(parcq!=NULL){

printf("%-12d%-12s%-12s%-12s%-12s\n",parcq->num,parcq->op,parcq->op1,parcq->op2,parcq->res);
fprintf(m,"%-12d%-12s%-12s%-12s%-12s\n",parcq->num,parcq->op,parcq->op1,parcq->op2,parcq->res);

parcq=parcq->svt;}
fclose(m);
}
void afficherquadruplet()
{listequad *parcq=NULL;
parcq=listeq;
if(parcq!=NULL) {printf("%-12s%-12s%-12s%-12s%-12s\n","Numero","Operation","Operande1","Operande2","Resultat");}
while(parcq!=NULL){
printf("%-12d%-12s%-12s%-12s%-12s\n",parcq->num,parcq->op,parcq->op1,parcq->op2,parcq->res);
parcq=parcq->svt;}

}

pilelm* empiler(pilelm* p,char entite[12],char nature[12])
{
if(p==NULL) {p=malloc(sizeof(pilelm));strcpy(p->ent,entite);strcpy(p->typep,nature);p->svt=NULL;}
else
{pilelm*P=NULL;P=malloc(sizeof(pilelm));strcpy(P->ent,entite);strcpy(P->typep,nature);P->svt=p;p=P;}
return p;
}

pilelm* desempiler(pilelm* p){
 pilelm* q=NULL;
  if(p!=NULL){q=p;p=p->svt;}
  return q;
}

nq* empilernq(nq* q,int n){
   if(q==NULL){q=malloc(sizeof(nq));q->n=n;q->svt=NULL;}
   else{
    nq* t=NULL;
    t=malloc(sizeof(nq));t->n=n;t->svt=q;q=t;
      }
   return q;
}
int depilernq(nq* q){
  int n=0;
if(q!=NULL)
{
  n=q->n;
  q=q->svt;
   }
 return n;
}

listequad* empilerbr(listequad* br,listequad* q){
listequad* t=NULL;
  t=malloc(sizeof(listequad));

  t->svt=br;t=q;br=t;
return br;
}

listequad* depilerbr(listequad* p){
listequad* q=NULL;
if(p!=NULL)
  {
    q=p;p=p->svt;
  }
return q;
}
