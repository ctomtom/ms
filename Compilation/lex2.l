%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "synt2.tab.h"
extern YYSTYPE yylval;
int l=1,c=0;
%}
s [\n]
idf ([A-Z]([a-zA-Z]|[0-9])*)
entierp [1-9]([0-9])*|0
entiern [\-]?{entierp}
reel   [\-]?[0-9]+"."[0-9]+
taille [1-9]([0-9])*
com2 "//"([^/]|[^/]"/"[^/]|\n)*"//"
%%
{com2}       {int i;for(i=0;i<=yyleng;i++){if(yytext[i]=='\n'){l+=1;c=0;}else c+=1;}}
{taille}    {if(atoi(yytext)>32767){printf("Ligne %d, colonne %d: %s Erreur lexical: La valeur d'un entier doit etre entre -32768 et 32767!\n",l,c,yytext);}
               else {c+=yyleng;yylval.entier=atoi(yytext);return taille;}}
"-"         {c+=yyleng;return moins;}
{reel}      {c+=yyleng;yylval.reel=atof(yytext);return reel;}
{entierp}   {if(atoi(yytext)>32767||atoi(yytext)<-32768){printf("Ligne %d, colonne %d: %s Erreur lexical: La valeur d'un entier doit etre entre -32768 et 32767!\n",l,c,yytext);}
               else {c+=yyleng;yylval.entier=atoi(yytext);return entierp;}}
{entiern}   {if(atoi(yytext)>32767||atoi(yytext)<-32768){printf("Ligne %d, colonne %d: %s Erreur lexical: La valeur d'un entier doit etre entre -32768 et 32767!\n",l,c,yytext);}
               else {c+=yyleng;yylval.entier=atoi(yytext);return entiern;}}
"real"      {c+=yyleng;yylval.str=strdup(yytext);return real;}
{idf}       {if(yyleng>12){printf("Ligne %d, colonne %d: %s Erreur lexical: La taille d'un identificateur ne doit pas dépasser 12 caractères!\n",l,c,yytext);} 
	                        else{yylval.str=strdup(yytext); c+=yyleng;return idf;}}
"const"     {c+=yyleng;yylval.str=strdup(yytext); return mc_const;}
{s}         {l+=1;c=0;}
"integer"   {c+=yyleng;yylval.str=strdup(yytext);return mc_int;}
"while"     {c+=yyleng;yylval.str=strdup(yytext); return mc_while;}
"programme" {c+=yyleng;yylval.str=strdup(yytext); return programme;}
"if"        {c+=yyleng;yylval.str=strdup(yytext);return mc_if;}
"execute"   {c+=yyleng;yylval.str=strdup(yytext); return execute;}
"calcul"    {c+=yyleng;yylval.str=strdup(yytext); return calcul;}
"tab"       {c+=yyleng;yylval.str=strdup(yytext); return tab;}
"boucle"    {c+=yyleng;yylval.str=strdup(yytext); return boucle;}
"["         {c+=yyleng;return cg;}
"]"         {c+=yyleng;return cd;}
"=="        {c+=yyleng;return eg;}
":="        {c+=yyleng;return aff;}
";"         {c+=yyleng;return pvg;}
"+"         {c+=yyleng;return plus;}
"*"         {c+=yyleng;return mult;}
"/"         {c+=yyleng;return '/';}
"<"         {c+=yyleng;return inf;}
">"         {c+=yyleng;return sup;}
"<="        {c+=yyleng;return infeg;}
">="        {c+=yyleng;return supeg;}
"("         {c+=yyleng;return pg;}
")"         {c+=yyleng;return pd;}
","         {c+=yyleng;return vg;}
"}"         {c+=yyleng;return ad;}
"{"         {c+=yyleng;return ag;}
"#"         {c+=yyleng;return hashtag;}
"!="        {c+=yyleng;return diff;}
"::"        {c+=yyleng;return dec;}
"||"        {c+=yyleng;return sep;}
[ \t]        {c+=1;}
.           {printf("Ligne %d,colonne %d : %s Erreur lexical: Entite inconnue!\n",l,c,yytext);c+=yyleng;}
%%
int yywrap(){return 1;}
