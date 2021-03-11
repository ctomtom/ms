%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tabsymb.h"
#include "quadruplet.h"
#include "optimisation.h"
#include "codeobjet.h"
extern int l,c; 
extern FILE* yyin;
extern char* yytext;
char sauv[12],sauv2[12],bibboucle[6],bibcalcul[6],bibtab[3],temp[12],val[12], cond[12], s[12],nbq[12],nomprog[30],tai[12];char T[2]="T";
int i=1,ins,exec,wh,err; 
listequad*pt=NULL;listelm* entite=NULL; pilelm* quad,*p=NULL,*p2=NULL;
%}
%union{
int entier;
char* str;
double reel;
}

%token moins <str>idf real mc_int boucle calcul tab <entier> entierp <entier> entiern <entier> taille <reel> reel 
%token aff pvg pd pg mult '/' dec plus inf eg begin end vg cg cd diff infeg sup supeg hashtag ad ag sep
%token mc_const mc_while mc_if programme execute  

%%
S: bibs programme idf ag declaration instructions ad {strcpy(nomprog,$3);printf("Syntaxe correcte.\n");YYACCEPT;}
bibs : hashtag bib bibs  | hashtag bib
; 
bib : boucle {strcpy(bibboucle,$1);}
      | 
      calcul {strcpy(bibcalcul,$1);}
      | 
      tab {strcpy(bibtab,$1);}
;
type: mc_int {strcpy(sauv,$1);}
      | 
      real {strcpy(sauv,$1);}
;
declaration : type dec listevariable declaration | type dec listevariable
;
listevariable: var_simple | constante | tableau 
;
tableau : idf cg taille cd sep tableau {if(strlen(bibtab)==0){printf("Ligne %d colonne %d: La bibliotheque TAB doit etre declaree!\n",l,c);err++;}
                                        else {entite=recherche($1);
                                               if(entite==NULL){inserer($1,"tableau",sauv,l,$3,"");sprintf(tai,"%d",$3);
                                                                ajouterquadruplet("Bounds","1",tai,"");
                                                                ajouterquadruplet("ADEC",$1,"","");}
                                                else {if(entite->ligne==l){err++;printf("ligne %d,colonne %d : Double declaration de l'entite %s dans la meme ligne\n",l,c,$1);}
                                                      else {err++;printf("ligne %d,colonne %d: Double declaration de l'entite %s dans une nouvelle ligne\n",l,c,$1);}
                                                       }}} 
          |           
          idf cg taille cd pvg {if(strlen(bibtab)==0){printf("Ligne %d colonne %d: La bibliotheque TAB doit etre declaree!\n",l,c);err++;}
                                  else {entite=recherche($1);
                                        if(entite==NULL){inserer($1,"tableau",sauv,l,$3,"");sprintf(tai,"%d",$3);
                                                                ajouterquadruplet("Bounds","1",tai,"");
                                                                ajouterquadruplet("ADEC",$1,"","");}
                                         else {if(entite->ligne==l)
                                               {err++;printf("ligne %d,colonne %d : Double declaration de l'entite %s dans la meme ligne\n",l,c,$1);}
                                              else {err++;printf("ligne %d,colonne %d: Double declaration de l'entite %s dans une nouvelle ligne\n",l,c,$1);}
                                                }}} 
;
constante : mc_const listconst
;
listconst : idf aff valeur sep 
                 {entite=recherche($1);
                   if(entite==NULL){
                   	              if(strcmp(sauv,sauv2)!=0){err++;printf("Ligne %d colonne %d : Type de la constante %s et initialisation incompatibles!\n",l,c,$1);}
                   	              else {inserer($1,"constante",sauv,l,1,val);}
                   	               }
                    else {if(strcmp(entite->type,sauv)!=0){
                                                           printf("ligne %d,colonne %d :Entite %s deja declaree avec un autre type!\n",l,c,$1);err++;}
                           else {if(entite->ligne==l){
                                  printf("ligne %d,colonne %d : Double declaration de l'entite %s dans la meme ligne!\n",l,c,$1);err++;}
                                  else {printf("ligne %d,colonne %d: Double declaration de l'entite %s dans une nouvelle ligne!\n",l,c,$1);err++;}
                                 } 
                          }
                      } listconst
            | 
            idf aff valeur pvg 
                  {entite=recherche($1);
                   if(entite==NULL){
                   	              if(strcmp(sauv,sauv2)!=0){printf("Ligne %d colonne %d : Type de la constante %s et initialisation incompatibles!\n",l,c,$1);err++;}
                   	              else {
                   	              	inserer($1,"constante",sauv,l,1,val);}
                   	               }
                    else {if(strcmp(entite->type,sauv)!=0){
                                                           printf("ligne %d,colonne %d :Entite %s deja declaree avec un autre type!\n",l,c,$1);err++;}
                           else {if(entite->ligne==l){
                                  printf("ligne %d,colonne %d : Double declaration de l'entite %s dans la meme ligne!\n",l,c,$1);err++;}
                                  else {printf("ligne %d,colonne %d: Double declaration de l'entite %s dans une nouvelle ligne!\n",l,c,$1);err++;}
                                 } 
                          }
                      }
;
var_simple: idf sep var_simple 	
                   {entite=recherche($1);
                   if(entite==NULL){inserer($1,"simple",sauv,l,1,"");}
                    else {
                      if(strcmp(entite->type,sauv)!=0)
                           {printf("ligne %d,colonne %d :Entite %s deja declaree avec un autre type \n",l,c,$1);err++;}
                           else {if((entite->ligne)==l)
                                 {printf("ligne %d,colonne %d : Double declaration de l'entite %s dans la meme ligne\n",l,c,$1);err++;}
                                  else {printf("ligne %d,colonne %d: Double declaration de l'entite %s dans une nouvelle ligne\n",l,c,$1);err++;}
                                       } }}
            | 
            idf pvg 
                  {entite=recherche($1);
                   if(entite==NULL){inserer($1,"simple",sauv,l,1,"");}
                       else
                           {if(strcmp(entite->type,sauv)!=0)
                              {printf("ligne %d,colonne %d :Entite %s deja declaree avec un autre type \n",l,c,$1);err++;}
                              else {if((entite->ligne)==l)
                                     {printf("ligne %d,colonne %d : Double declaration de l'entite %s dans la meme ligne\n",l,c,$1);err++;}
                                    else 
                                    {printf("ligne %d,colonne %d: Double declaration de l'entite %s dans une nouvelle ligne\n",l,c,$1);err++;}
                                      }}}
;
instructions :  instruction | instruction instructions 
;
instruction : affectation | boucle_while | condition
;
affectation: idf aff expression pvg {if(recherche($1)==NULL)
                                     {printf("Ligne %d colonne %d: Variable non declaree %s \n",l,c,$1);err++;}                                    
                                      else {//if(strcmp(recherche($1)->type,sauv2)!=0)
                                             //{printf("Ligne %d colonne %d: Variable fortement typee %s\n",l,c,$1);}
                                             //else{} 
                                                //p2=NULL;
                                                if(strcmp(recherche($1)->nature,"constante")==0){err++;printf("Ligne %d colonne %d: Entite %s Erreur modification d'une constante!\n",l,c,$1);}                                   
                                                else{p2=desempiler(quad);
                                                    if(strcmp(recherche($1)->type,p2->typep)!=0)
                                                      {printf("Ligne %d colonne %d: Variable fortement typee %s \n",l,c, $1);err++;}
                                                     else {ajouterquadruplet(":=",p2->ent,"",$1);}
                                                //free(p2);
                                                     }
                                            }
                                            }
             | 
             idf cg taille cd aff expression pvg 
                              {if(recherche($1)==NULL)
                                {printf("Ligne %d colonne %d: Tableau non declaree %s \n",l,c,$1);err++;}
                                  else {/*if(strcmp(recherche($1)->type,sauv2)!=0)
                                        {printf("Ligne %d colonne %d: Variable fortement typee %s \n",l,c,$1);}
                                        else {*/
                                             if(strcmp(recherche($1)->nature,"tableau")!=0){err++;printf("Ligne %d colonne %d: Affectation a un tableau or %s n'est pas un tableau!\n",l,c,$1);}
                                              else{ entite=recherche($1);
                                                if($3>(entite->size))
                                                 {printf("Ligne %d colonne %d: Depassement de capacite du tableau!\n",l,c);err++;}
                                                  else{//p2=NULL;                                   
                                                     p2=desempiler(quad);
                                                     if(strcmp(recherche($1)->type,p2->typep)!=0)
                                                        {printf("Ligne %d colonne %d: Variable fortement typee %s \n",l,c, $1);err++;}
                                                        else {char ch[100];char ch1[100];sprintf(ch,"[%d]",$3);strcpy(ch1,$1);strcat(ch1,ch);
                                                              ajouterquadruplet(":=",p2->ent,"",ch1);}
                                                              } } 
                                                                  }}
;
expression : t plus expression {if(strlen(bibcalcul)==0){printf("Ligne %d colonne %d: La bibliotheque CALCUL doit etre declaree!\n",l,c);err++;}
                                 else {
                                 //p=NULL;p2=NULL;
                                 p=quad;p2=quad->svt;
                                 p=desempiler(p);p2=desempiler(p2);quad=quad->svt;quad=quad->svt;
                                 if(strcmp(p->typep,p2->typep)!=0){printf("Ligne %d colonne %d: Types incompatibles!\n",l,c);err++;}
                                 else {sprintf(temp,"T%d",i);i++;
                                 quad=empiler(quad,temp,p->typep);
                                 ajouterquadruplet("+",p2->ent,p->ent,temp);}
                                 //free(p);free(p2);
                               }
                                 }
             |
             t moins expression {if(strlen(bibcalcul)==0){printf("Ligne %d colonne %d: La bibliotheque CALCUL doit etre declaree!\n",l,c);err++;}
                                 else{
                                 //p=NULL;p2=NULL;
                                 p=quad;p2=quad->svt;
                                 p=desempiler(p);p2=desempiler(p2);quad=quad->svt;quad=quad->svt;
                                 if(strcmp(p->typep,p2->typep)!=0){printf("Ligne %d colonne %d: Types incompatibles!\n",l,c);err++;}
                                 else {sprintf(temp,"T%d",i);i++;
                                 quad=empiler(quad,temp,p->typep);
                                 ajouterquadruplet("-",p2->ent,p->ent,temp);}
                                 //free(p);free(p2);
                               }
                               }
             |
             t 
;
t : valeurx mult t {if(strlen(bibcalcul)==0){printf("Ligne %d colonne %d: La bibliotheque CALCUL doit etre declaree!\n",l,c);err++;}
                     else{ //p=NULL;p2=NULL;
                            p=quad;p2=quad->svt;
                            p=desempiler(p);p2=desempiler(p2);quad=quad->svt;quad=quad->svt;
                            if(strcmp(p->typep,p2->typep)!=0){printf("Ligne %d colonne %d: Types incompatibles!\n",l,c);err++;}
                            else {sprintf(temp,"T%d",i);i++;
                                 quad=empiler(quad,temp,p->typep);
                                 ajouterquadruplet("*",p2->ent,p->ent,temp);}
                                 //free(p);free(p2);
                               }
                               }
    |
    valeurx '/' t {if(strlen(bibcalcul)==0){printf("Ligne %d colonne %d: La bibliotheque CALCUL doit etre declaree!\n",l,c);err++;}
                     else{
                            //p=NULL;p2=NULL;
                            p=quad;p2=quad->svt;
                            p=desempiler(p);p2=desempiler(p2);quad=quad->svt;quad=quad->svt;
                            if(strcmp(p->typep,p2->typep)!=0){printf("Ligne %d colonne %d: Types incompatibles!\n",l,c);err++;}
                            else {sprintf(temp,"T%d",i);i++;
                                 quad=empiler(quad,temp,p->typep);
                                 ajouterquadruplet("/",p2->ent,p->ent,temp);}
                                //free(p);free(p2);
                               }
                               }
    |
    valeurx
;
valeurx : valeur 
         |
         valeurid
; 
valeur : entierp {strcpy(sauv2,"integer");sprintf(val,"%d",$1);quad=empiler(quad,val,sauv2);}
         |
         taille {strcpy(sauv2,"integer");sprintf(val,"%d",$1);quad=empiler(quad,val,sauv2);}
         |
         entiern {strcpy(sauv2,"integer");sprintf(val,"%d",$1);quad=empiler(quad,val,sauv2);}
         |
         reel {strcpy(sauv2,"real");sprintf(val,"%f",$1);quad=empiler(quad,val,sauv2);}
         
;
valeurid: idf {if(recherche($1)==NULL)
               {printf("Ligne %d colonne %d: %s Variable non declaree\n",l,c,$1);err++;}
                          else {//strcpy(sauv2,entite->type);
                               quad=empiler(quad,$1,recherche($1)->type);
                              }
                          }
         | 
         idf cg taille cd {if(recherche($1)==NULL)
                            {printf("Ligne %d colonne %d: %s Tableau non declaree\n",l,c,$1);err++;}
                            else {if(strcmp(recherche($1)->nature,"tableau")!=0){printf("Ligne %d colonne %d: %s n'est pas un tableau!\n",l,c,$1);err++;}
                            	   else{entite=recherche($1);strcpy(sauv2,entite->type);
                                        if($3>(recherche($1)->size))
                                         {printf("Ligne %d colonne %d: Depassement de capacite du tableau %s\n",l,c,$1);err++;}
                                          else{char ch[100];char ch1[100];sprintf(ch,"[%d]",$3);strcpy(ch1,$1);strcat(ch1,ch);
                                               quad=empiler(quad,ch1,recherche($1)->type);
                                              }
                                       }
                                  }
                          }
;
boucle_while: B ag instructions ad {//pt=NULL;//pt=brwhile;
                                    ins=depilernq(etwhile);sprintf(s,"%d",ins);
                                    ajouterquadruplet("BR",s,"","");
                                    sprintf(nbq,"%d",cpt);
                                    pt=depilerbr(brwhile); 
                                    maj_quad(pt,1,nbq);
                                    //free(pt);
                                  }
              
;
condition: A1 mc_if pg comparaison pd {
                                           p=quad;p2=quad->svt;
                                           quad=quad->svt;quad=quad->svt;
                                            p=desempiler(p);p2=desempiler(p2);ins=depilernq(inst);                                            
                                            sprintf(s,"%d",ins);
                                            ajouterquadruplet(cond,s,p2->ent,p->ent);sprintf(nbq,"%d",cpt);
                                            pt=depilerbr(brfin);
                                            maj_quad(pt,1,nbq);
                                          //free(p);free(p2);free(pt);
                                          }
;
B: w pg comparaison pd {//p=NULL;p2=NULL;
                         p=quad;p2=quad->svt;quad=quad->svt;quad=quad->svt;
                         p=desempiler(p);p2=desempiler(p2);ajouterquadruplet(cond,"",p2->ent,p->ent);
                         brwhile=empilerbr(brwhile,qc);
                         //free(p);free(p2);
                       }
;

w: mc_while {if(strlen(bibboucle)==0){printf("Ligne %d colonne %d: La bibliotheque BOUCLE doit etre declaree!\n",l,c);err++;}
               else {etwhile=empilernq(etwhile,cpt);wh=1;}
             }
;
A1 : A instructions {
                     ajouterquadruplet("BR","","","");sprintf(nbq,"%d",cpt);
                     brfin=empilerbr(brfin,qc);
                     pt=depilerbr(brcond);
                     maj_quad(pt,1,nbq);
                     }
                     
;

A: execute {inst=empilernq(inst,cpt+1);ajouterquadruplet("BR","","","");brcond=empilerbr(brcond,qc);exec=1;}
;
comparaison : expression comp expression 
;
comp :      inf {if(wh==1){strcpy(cond,"BGE");wh=0;}
                 else {if(exec==1){strcpy(cond,"BL");exec=0;}}
                 }
            | 
            infeg {if(wh==1){strcpy(cond,"BG");wh=0;}
                   else {if(exec==1){strcpy(cond,"BLE");exec=0;}}
                 }
            | 
            eg {if(wh==1){strcpy(cond,"BNE");wh=0;}
                else {if(exec==1){strcpy(cond,"BE");exec=0;}}
                 }
            | 
            sup {if(wh==1){strcpy(cond,"BLE");wh=0;}
                 else {if(exec==1){strcpy(cond,"BG");exec=0;}}
                 }
            | 
            supeg {if(wh==1){strcpy(cond,"BL");wh=0;}
                   else {if(exec==1){strcpy(cond,"BGE");exec=0;}}
                 }
            | 
            diff {if(wh==1){strcpy(cond,"BE");wh=0;}
                  else {if(exec==1){strcpy(cond,"BNE");exec=0;}}
                 }
;

%%
int yyerror(char* msg)
{printf("Ligne %d colonne %d : Erreur syntaxique %s\n",l,c,yytext);err++;
return 0;}

int main()
{
yyin=fopen("prog.txt","r");
yyparse();
if(err==0)
{printf("*****LA TABLE DES SYMBOLES*****\n");
afficher();
printf("\n*****LES QUADRUPLETS*****\n");
afficherquadrupletpremiere();
printf("\n*****LES QUADRUPLETS OPTIMISES*****\n");
printf("\n*****PROPAGATION DE COPIE*****\n");
propcopie();
afficherquadruplet();
printf("\n*****SIMPLIFICATION ALGEBRIQUE*****\n");
simpalgebrique();
afficherquadruplet();
printf("\n*****EXPRESSIONS REDONDANTES*****\n");
expredondante();
afficherquadruplet();
printf("\n*****ELIMINATION DU CODE INUTILE*****\n");
codeinutile();
opti();
printf("\n*****CODE OBJET*****\n\n");
codeobjet();}
return 1;
}
