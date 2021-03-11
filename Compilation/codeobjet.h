#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include<malloc.h>
extern char nomprog[30];
void codeobjet(){
	listequad* q=NULL;listelm* p=NULL;
	q=listeq;p=liste;FILE* code_objet=NULL; 
  code_objet=fopen("code_objet.asm","w+");
	printf("TITLE %s.asm\n",nomprog);
  fprintf(code_objet,"TITLE %s.asm\n",nomprog);
	printf("\nPILE SEGMENT STACK\n");
  fprintf(code_objet,"\nPILE SEGMENT STACK\n");
	printf("     dw 100 dup(?)\n");
  fprintf(code_objet,"     dw 100 dup(?)\n");
	printf("base_pile EQU  this word \n");
  fprintf(code_objet,"base_pile EQU  this word \n");
	printf("PILE ENDS\n");
  fprintf(code_objet,"PILE ENDS\n");
	printf("\nASSUME SS:PILE\n");
  fprintf(code_objet,"\nASSUME SS:PILE\n");
	printf("MOV AX,PILE\n");
  fprintf(code_objet,"MOV AX,PILE\n");
	printf("MOV SS, AX\n");
  fprintf(code_objet,"MOV SS, AX\n");
	printf("MOV SP, base_pile\n");
  fprintf(code_objet,"MOV SP, base_pile\n");
  printf("\nDATA SEGMENT\n");
  fprintf(code_objet,"\nDATA SEGMENT\n");
    while(p!=NULL){
    	if(strcmp(p->nature,"simple")==0)
    	{if(strcmp(p->type,"integer")==0){printf("%s DW ?\n",p->entite);fprintf(code_objet,"%s DW ?\n",p->entite);}
    	 if(strcmp(p->type,"real")==0){printf("%s DQ ?\n",p->entite);fprintf(code_objet,"%s DQ ?\n",p->entite);}
        }
        if(strcmp(p->nature,"tableau")==0)
        {if(strcmp(p->type,"integer")==0){printf("%s DW %d dup (?)\n",p->entite,p->size);fprintf(code_objet,"%s DW %d dup (?)\n",p->entite,p->size);}
    	   if(strcmp(p->type,"real")==0){printf("%s DQ %d dup (?)\n",p->entite,p->size);fprintf(code_objet,"%s DQ %d dup (?)\n",p->entite,p->size);}
        }
        if(strcmp(p->nature,"constante")==0)
        {printf("%s EQU %s\n",p->entite,p->v);fprintf(code_objet,"%s EQU %s\n",p->entite,p->v);
        }
        p=p->svt;
                  }
    printf("DATA ENDS\n");
    fprintf(code_objet,"DATA ENDS\n");
    printf("\nCODE SEGMENT\n");
    fprintf(code_objet,"\nCODE SEGMENT\n");
    printf("MAIN:\n");
    fprintf(code_objet,"MAIN:\n");    
	while(q!=NULL)
	{if(strcmp(q->op,"+")==0){if(q->op1[strlen(q->op1)-1]==']'){if(q->op2[strlen(q->op2)-1]==']')
                                                                 {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);                                                                
                                                                  printf("ADD AX,%s\n",q->op2);
                                                                  printf("MOV %s,AX\n",q->res);
                                                                  printf("PUSH AX\n");
                                                                  fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                  fprintf(code_objet,"ADD AX,%s\n",q->op2);
                                                                  fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                  fprintf(code_objet,"PUSH AX\n");}                                                                  
                                                                  else{if(recherche(q->op2)!=NULL)
            	                                                        {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                         printf("ADD AX,%s\n",q->op2);
                                                                         printf("MOV %s,AX\n",q->res);
                                                                         printf("PUSH AX\n");

                                                                         fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                         fprintf(code_objet,"ADD AX,%s\n",q->op2);
                                                                         fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                         fprintf(code_objet,"PUSH AX\n");}
                                                                         else {if(q->op2[0]=='T')
                                                                                {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                                 printf("POP BX\n");
                                                                                 printf("ADD AX,BX\n");
                                                                                 printf("MOV %s,AX\n",q->res);
                                                                                 printf("PUSH AX\n");

                                                                                 fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                                 fprintf(code_objet,"POP BX\n");
                                                                                 fprintf(code_objet,"ADD AX,BX\n");
                                                                                 fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                                 fprintf(code_objet,"PUSH AX\n");}
                                                                                else{printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                                     printf("ADD AX,%s\n",q->op2);
                                                                                     printf("MOV %s,AX\n",q->res);
                                                                                     printf("PUSH AX\n");

                                                                                     fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                                     fprintf(code_objet,"ADD AX,%s\n",q->op2);
                                                                                     fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                                     fprintf(code_objet,"PUSH AX\n");
                                                                                   }                          
                                                                                }
                                                                        }
                                                                }
                              else {if(recherche(q->op1)!=NULL){if(q->op2[strlen(q->op2)-1]==']')
                                                                 {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                  printf("ADD AX,%s\n",q->op2);
                                                                  printf("MOV %s,AX\n",q->res);
                                                                  printf("PUSH AX\n");

                                                                  fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                  fprintf(code_objet,"ADD AX,%s\n",q->op2);
                                                                  fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                  fprintf(code_objet,"PUSH AX\n"); }

                                                                 else{if(recherche(q->op2)!=NULL)
            	                                                         {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                        printf("ADD AX,%s\n",q->op2);
                                                                        printf("MOV %s,AX\n",q->res);
                                                                        printf("PUSH AX\n");
                                                                       
                                                                        fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                        fprintf(code_objet,"ADD AX,%s\n",q->op2);
                                                                        fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                        fprintf(code_objet,"PUSH AX\n");
                                                                       }
                                                                       else {if(q->op2[0]=='T')
                                                                             {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                              printf("POP BX\n");
                                                                              printf("ADD AX,BX\n");
                                                                              printf("MOV %s,AX\n",q->res);
                                                                              printf("PUSH AX\n");

                                                                              fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                              fprintf(code_objet,"POP BX\n");
                                                                              fprintf(code_objet,"ADD AX,BX\n");
                                                                              fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                              fprintf(code_objet,"PUSH AX\n");
                                                                            }
                                                                             else{printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                                  printf("ADD AX,%s\n",q->op2);
                                                                                  printf("MOV %s,AX\n",q->res);
                                                                                  printf("PUSH AX\n");

                                                                                  fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                                  fprintf(code_objet,"ADD AX,%s\n",q->op2);
                                                                                  fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                                  fprintf(code_objet,"PUSH AX\n");
                                                                                }
                                                                             }
                                                                       }
                                                                }
                                     else{if(q->op1[0]=='T'){if(q->op2[strlen(q->op2)-1]==']')
                                                              {printf("ETIQ%d: POP AX\n",q->num);                        
                                                               printf("ADD AX,%s\n",q->op2);
                                                               printf("MOV %s,AX\n",q->res);
                                                               printf("PUSH AX\n");

                                                               fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);                        
                                                               fprintf(code_objet,"ADD AX,%s\n",q->op2);
                                                               fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                               fprintf(code_objet,"PUSH AX\n");
                                                             }
                                                              else{if(recherche(q->op2)!=NULL)
            	                                                    {printf("ETIQ%d: POP AX\n",q->num);
                                                                     printf("ADD AX,%s\n",q->op2);
                                                                     printf("MOV %s,AX\n",q->res);
                                                                     printf("PUSH AX\n");

                                                                   fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                     fprintf(code_objet,"ADD AX,%s\n",q->op2);
                                                                     fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                     fprintf(code_objet,"PUSH AX\n");}

                                                                    else {if(q->op2[0]=='T')
                                                                           {printf("ETIQ%d: POP BX\n",q->num);
                                                                            printf("POP AX\n");
                                                                            printf("ADD AX,BX\n");
                                                                            printf("MOV %s,AX\n",q->res);
                                                                            printf("PUSH AX\n");

                                                                            fprintf(code_objet,"ETIQ%d: POP BX\n",q->num);
                                                                            fprintf(code_objet,"POP AX\n");
                                                                            fprintf(code_objet,"ADD AX,BX\n");
                                                                            fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                            fprintf(code_objet,"PUSH AX\n");
                                                                          }
                                                                           else{printf("ETIQ%d: POP AX\n",q->num);
                                  	                                            printf("ADD AX,%s\n",q->op2);
                                                                                printf("MOV %s,AX\n",q->res);
                                                                                printf("PUSH AX\n");

                                                                                fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                                fprintf(code_objet,"ADD AX,%s\n",q->op2);
                                                                                fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                                fprintf(code_objet,"PUSH AX\n");
                                                                              }                                                              
                                                                           }
                                                                  }
                 	                                        }
                 	                       else {if(q->op2[strlen(q->op2)-1]==']')
                 	  	                          {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                   printf("ADD AX,%s\n",q->op2);
                                                   printf("MOV %s,AX\n",q->res);
                                                   printf("PUSH AX\n");

                                                   fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                   fprintf(code_objet,"ADD AX,%s\n",q->op2);
                                                   fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                   fprintf(code_objet,"PUSH AX\n");
                                                 }
                 	  	                         else{if(recherche(q->op2)!=NULL)
            	                                         {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                        printf("ADD AX,%s\n",q->op2);
                                                        printf("MOV %s,AX\n",q->res);
                                                        printf("PUSH AX\n");

                                                        fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                        fprintf(code_objet,"ADD AX,%s\n",q->op2);
                                                        fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                        fprintf(code_objet,"PUSH AX\n");
                                                       }
                                                      else {if(q->op2[0]=='T')
                                                             {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                              printf("POP BX\n");
                                                              printf("ADD AX,BX\n");
                                                              printf("MOV %s,AX\n",q->res);
                                                              printf("PUSH AX\n");

                                                              fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                              fprintf(code_objet,"POP BX\n");
                                                              fprintf(code_objet,"ADD AX,BX\n");
                                                              fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                              fprintf(code_objet,"PUSH AX\n");
                                                            }
                                                             else{printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                  	                              printf("ADD AX,%s\n",q->op2);
                                                                  printf("MOV %s,AX\n",q->res);
                                                                  printf("PUSH AX\n");

                                                                  fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                  fprintf(code_objet,"ADD AX,%s\n",q->op2);
                                                                  fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                  fprintf(code_objet,"PUSH AX\n");
                                                                }                          
                                                            }
                                                        }
                 	                            }
                                         }
                }
            }
     
     if(strcmp(q->op,"-")==0){if(q->op1[strlen(q->op1)-1]==']'){if(q->op2[strlen(q->op2)-1]==']')
                                                                 {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                  printf("SUB AX,%s\n",q->op2);
                                                                  printf("MOV %s,AX\n",q->res);
                                                                  printf("PUSH AX\n");

                                                                  fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                  fprintf(code_objet,"SUB AX,%s\n",q->op2);
                                                                  fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                  fprintf(code_objet,"PUSH AX\n");
                                                                 }                                                                  
                                                                  else{if(recherche(q->op2)!=NULL)
            	                                                        {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                         printf("SUB AX,%s\n",q->op2);
                                                                         printf("MOV %s,AX\n",q->res);
                                                                         printf("PUSH AX\n");

                                                                         fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                         fprintf(code_objet,"SUB AX,%s\n",q->op2);
                                                                         fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                         fprintf(code_objet,"PUSH AX\n");
                                                                       }
                                                                         else {if(q->op2[0]=='T')
                                                                                {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                                 printf("POP BX\n");
                                                                                 printf("SUB AX,BX\n");
                                                                                 printf("MOV %s,AX\n",q->res);
                                                                                 printf("PUSH AX\n");

                                                                                 fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                                 fprintf(code_objet,"POP BX\n");
                                                                                 fprintf(code_objet,"SUB AX,BX\n");
                                                                                 fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                                 fprintf(code_objet,"PUSH AX\n");
                                                                               }
                                                                                else{printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                                     printf("SUB AX,%s\n",q->op2);
                                                                                     printf("MOV %s,AX\n",q->res);
                                                                                     printf("PUSH AX\n");

                                                                                     fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                                     fprintf(code_objet,"SUB AX,%s\n",q->op2);
                                                                                     fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                                     fprintf(code_objet,"PUSH AX\n");
                                                                                   }                          
                                                                                }
                                                                        }
                                                                }
                              else {if(recherche(q->op1)!=NULL){if(q->op2[strlen(q->op2)-1]==']')
                                                                 {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                  printf("SUB AX,%s\n",q->op2);
                                                                  printf("MOV %s,AX\n",q->res);
                                                                  printf("PUSH AX\n");

                                                                  fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                  fprintf(code_objet,"SUB AX,%s\n",q->op2);
                                                                  fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                  fprintf(code_objet,"PUSH AX\n");
                                                                }
                                                                 else{if(recherche(q->op2)!=NULL)
            	                                                         {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                        printf("SUB AX,%s\n",q->op2);
                                                                        printf("MOV %s,AX\n",q->res);
                                                                        printf("PUSH AX\n");

                                                                       fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                       fprintf(code_objet,"SUB AX,%s\n",q->op2);
                                                                       fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                       fprintf(code_objet,"PUSH AX\n");
                                                                     }
                                                                       else {if(q->op2[0]=='T')
                                                                             {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                              printf("POP BX\n");
                                                                              printf("SUB AX,BX\n");
                                                                              printf("MOV %s,AX\n",q->res);
                                                                              printf("PUSH AX\n");

                                                                              fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                              fprintf(code_objet,"POP BX\n");
                                                                              fprintf(code_objet,"SUB AX,BX\n");
                                                                              fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                              fprintf(code_objet,"PUSH AX\n");
                                                                            }
                                                                             else{printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                                  printf("SUB AX,%s\n",q->op2);
                                                                                  printf("MOV %s,AX\n",q->res);
                                                                                  printf("PUSH AX\n");

                                                                                  fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                                  fprintf(code_objet,"SUB AX,%s\n",q->op2);
                                                                                  fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                                  fprintf(code_objet,"PUSH AX\n");
                                                                                }
                                                                             }
                                                                       }
                                                                }
                                     else{if(q->op1[0]=='T'){if(q->op2[strlen(q->op2)-1]==']')
                                                              {printf("ETIQ%d: POP AX\n",q->num);                        
                                                               printf("SUB AX,%s\n",q->op2);
                                                               printf("MOV %s,AX\n",q->res);
                                                               printf("PUSH AX\n");

                                                               fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);                        
                                                               fprintf(code_objet,"SUB AX,%s\n",q->op2);
                                                               fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                               fprintf(code_objet,"PUSH AX\n");
                                                             }
                                                              else{if(recherche(q->op2)!=NULL)
            	                                                      {printf("ETIQ%d: POP AX\n",q->num);
                                                                     printf("SUB AX,%s\n",q->op2);
                                                                     printf("SUB %s,AX\n",q->res);
                                                                     printf("PUSH AX\n");

                                                                     fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                     fprintf(code_objet,"SUB AX,%s\n",q->op2);
                                                                     fprintf(code_objet,"SUB %s,AX\n",q->res);
                                                                     fprintf(code_objet,"PUSH AX\n");
                                                                   }
                                                                    else {if(q->op2[0]=='T')
                                                                           {printf("ETIQ%d: POP BX\n",q->num);
                                                                            printf("POP AX\n");
                                                                            printf("SUB AX,BX\n");
                                                                            printf("MOV %s,AX\n",q->res);
                                                                            printf("PUSH AX\n");

                                                                            fprintf(code_objet,"ETIQ%d: POP BX\n",q->num);
                                                                            fprintf(code_objet,"POP AX\n");
                                                                            fprintf(code_objet,"SUB AX,BX\n");
                                                                            fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                            fprintf(code_objet,"PUSH AX\n");
                                                                          }
                                                                           else{printf("ETIQ%d: POP AX\n",q->num);
                                  	                                            printf("SUB AX,%s\n",q->op2);
                                                                                printf("MOV %s,AX\n",q->res);
                                                                                printf("PUSH AX\n");

                                                                                fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                                fprintf(code_objet,"SUB AX,%s\n",q->op2);
                                                                                fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                                fprintf(code_objet,"PUSH AX\n");
                                                                              }                                                              
                                                                           }
                                                                  }
                 	                                        }
                 	                       else {if(q->op2[strlen(q->op2)-1]==']')
                 	  	                           { printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                   printf("SUB AX,%s\n",q->op2);
                                                   printf("MOV %s,AX\n",q->res);
                                                   printf("PUSH AX\n");

                                                   fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                   fprintf(code_objet,"SUB AX,%s\n",q->op2);
                                                   fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                   fprintf(code_objet,"PUSH AX\n");
                                                 }
                 	  	                         else{if(recherche(q->op2)!=NULL)
            	                                        {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                        printf("SUB AX,%s\n",q->op2);
                                                        printf("MOV %s,AX\n",q->res);
                                                        printf("PUSH AX\n");

                                                        fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                        fprintf(code_objet,"SUB AX,%s\n",q->op2);
                                                        fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                        fprintf(code_objet,"PUSH AX\n");
                                                      }
                                                      else {if(q->op2[0]=='T')
                                                             {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                              printf("POP BX\n");
                                                              printf("SUB AX,BX\n");
                                                              printf("MOV %s,AX\n",q->res);
                                                              printf("PUSH AX\n");

                                                              fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                              fprintf(code_objet,"POP BX\n");
                                                              fprintf(code_objet,"SUB AX,BX\n");
                                                              fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                              fprintf(code_objet,"PUSH AX\n");
                                                            }
                                                             else{printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                  	                              printf("SUB AX,%s\n",q->op2);
                                                                  printf("MOV %s,AX\n",q->res);
                                                                  printf("PUSH AX\n");

                                                                  fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                  fprintf(code_objet,"SUB AX,%s\n",q->op2);
                                                                  fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                  fprintf(code_objet,"PUSH AX\n");
                                                                }                          
                                                            }
                                                        }
                 	                            }
                                         }
                }
            }
     if(strcmp(q->op,"*")==0){if(q->op1[strlen(q->op1)-1]==']'){if(q->op2[strlen(q->op2)-1]==']')
                                                                 {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                  printf("MULT AX,%s\n",q->op2);
                                                                  printf("MOV %s,AX\n",q->res);
                                                                  printf("PUSH AX\n");

                                                                  fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                  fprintf(code_objet,"MULT AX,%s\n",q->op2);
                                                                  fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                  fprintf(code_objet,"PUSH AX\n");
                                                                }                                                                  
                                                                  else{if(recherche(q->op2)!=NULL)
            	                                                          {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                         printf("MULT AX,%s\n",q->op2);
                                                                         printf("MOV %s,AX\n",q->res);
                                                                         printf("PUSH AX\n");

                                                                         fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                         fprintf(code_objet,"MULT AX,%s\n",q->op2);
                                                                         fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                         fprintf(code_objet,"PUSH AX\n");
                                                                       }
                                                                         else {if(q->op2[0]=='T')
                                                                                {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                                 printf("POP BX\n");
                                                                                 printf("MULT AX,BX\n");
                                                                                 printf("MOV %s,AX\n",q->res);
                                                                                 printf("PUSH AX\n");

                                                                                 fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                                 fprintf(code_objet,"POP BX\n");
                                                                                 fprintf(code_objet,"MULT AX,BX\n");
                                                                                 fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                                 fprintf(code_objet,"PUSH AX\n");
                                                                               }
                                                                                else{printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                                     printf("MULT AX,%s\n",q->op2);
                                                                                     printf("MOV %s,AX\n",q->res);
                                                                                     printf("PUSH AX\n");

                                                                                     fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                                     fprintf(code_objet,"MULT AX,%s\n",q->op2);
                                                                                     fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                                     fprintf(code_objet,"PUSH AX\n");
                                                                                   }                          
                                                                                }
                                                                        }
                                                                }
                              else {if(recherche(q->op1)!=NULL){if(q->op2[strlen(q->op2)-1]==']')
                                                                 {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                  printf("MULT AX,%s\n",q->op2);
                                                                  printf("MOV %s,AX\n",q->res);
                                                                  printf("PUSH AX\n");

                                                                  fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                  fprintf(code_objet,"MULT AX,%s\n",q->op2);
                                                                  fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                  fprintf(code_objet,"PUSH AX\n");
                                                                 }
                                                                 else{if(recherche(q->op2)!=NULL)
            	                                                        {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                       printf("MULT AX,%s\n",q->op2);
                                                                       printf("MOV %s,AX\n",q->res);
                                                                       printf("PUSH AX\n");

                                                                       fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                       fprintf(code_objet,"MULT AX,%s\n",q->op2);
                                                                       fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                       fprintf(code_objet,"PUSH AX\n");
                                                                        }
                                                                       else {if(q->op2[0]=='T')
                                                                             {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                              printf("POP BX\n");
                                                                              printf("MULT AX,BX\n");
                                                                              printf("MOV %s,AX\n",q->res);
                                                                              printf("PUSH AX\n");

                                                                              fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                              fprintf(code_objet,"POP BX\n");
                                                                              fprintf(code_objet,"MULT AX,BX\n");
                                                                              fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                              fprintf(code_objet,"PUSH AX\n");
                                                                            }
                                                                             else{printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                                  printf("MULT AX,%s\n",q->op2);
                                                                                  printf("MOV %s,AX\n",q->res);
                                                                                  printf("PUSH AX\n");

                                                                                  fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                                  fprintf(code_objet,"MULT AX,%s\n",q->op2);
                                                                                  fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                                  fprintf(code_objet,"PUSH AX\n");
                                                                                }
                                                                             }
                                                                       }
                                                                }
                                     else{if(q->op1[0]=='T'){if(q->op2[strlen(q->op2)-1]==']')
                                                              {printf("ETIQ%d: POP AX\n",q->num);                        
                                                               printf("MULT AX,%s\n",q->op2);
                                                               printf("MOV %s,AX\n",q->res);
                                                               printf("PUSH AX\n");

                                                               fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);                        
                                                               fprintf(code_objet,"MULT AX,%s\n",q->op2);
                                                               fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                               fprintf(code_objet,"PUSH AX\n");
                                                             }
                                                              else{if(recherche(q->op2)!=NULL)
            	                                                      {printf("ETIQ%d: POP AX\n",q->num);
                                                                     printf("MULT AX,%s\n",q->op2);
                                                                     printf("MOV %s,AX\n",q->res);
                                                                     printf("PUSH AX\n");

                                                                     fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                     fprintf(code_objet,"MULT AX,%s\n",q->op2);
                                                                     fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                     fprintf(code_objet,"PUSH AX\n");
                                                                   }
                                                                    else {if(q->op2[0]=='T')
                                                                           {printf("ETIQ%d: POP BX\n",q->num);
                                                                            printf("POP AX\n");
                                                                            printf("MULT AX,BX\n");
                                                                            printf("MOV %s,AX\n",q->res);
                                                                            printf("PUSH AX\n");

                                                                            fprintf(code_objet,"ETIQ%d: POP BX\n",q->num);
                                                                            fprintf(code_objet,"POP AX\n");
                                                                            fprintf(code_objet,"MULT AX,BX\n");
                                                                            fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                            fprintf(code_objet,"PUSH AX\n");
                                                                          }
                                                                           else{printf("ETIQ%d: POP AX\n",q->num);
                                  	                                            printf("MULT AX,%s\n",q->op2);
                                                                                printf("MOV %s,AX\n",q->res);
                                                                                printf("PUSH AX\n");

                                                                                fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                                fprintf(code_objet,"MULT AX,%s\n",q->op2);
                                                                                fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                                fprintf(code_objet,"PUSH AX\n");
                                                                              }                                                              
                                                                           }
                                                                  }
                 	                                        }
                 	                       else {if(q->op2[strlen(q->op2)-1]==']')
                 	  	                           {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                   printf("MULT AX,%s\n",q->op2);
                                                   printf("MOV %s,AX\n",q->res);
                                                   printf("PUSH AX\n");

                                                   fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                   fprintf(code_objet,"MULT AX,%s\n",q->op2);
                                                   fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                   fprintf(code_objet,"PUSH AX\n");
                                                 }
                 	  	                         else{if(recherche(q->op2)!=NULL)
            	                                         {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                        printf("MULT AX,%s\n",q->op2);
                                                        printf("MOV %s,AX\n",q->res);
                                                        printf("PUSH AX\n");

                                                        fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                        fprintf(code_objet,"MULT AX,%s\n",q->op2);
                                                        fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                        fprintf(code_objet,"PUSH AX\n");
                                                      }
                                                      else {if(q->op2[0]=='T')
                                                             {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                              printf("POP BX\n");
                                                              printf("MULT AX,BX\n");
                                                              printf("MOV %s,AX\n",q->res);
                                                              printf("PUSH AX\n");

                                                              fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                              fprintf(code_objet,"POP BX\n");
                                                              fprintf(code_objet,"MULT AX,BX\n");
                                                              fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                              fprintf(code_objet,"PUSH AX\n");
                                                            }
                                                             else{printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                  	                              printf("MULT AX,%s\n",q->op2);
                                                                  printf("MOV %s,AX\n",q->res);
                                                                  printf("PUSH AX\n");

                                                                  fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                  fprintf(code_objet,"MULT AX,%s\n",q->op2);
                                                                  fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                  fprintf(code_objet,"PUSH AX\n");
                                                                }                          
                                                            }
                                                        }
                 	                            }
                                         }
                }
            }
     if(strcmp(q->op,"/")==0){if(q->op1[strlen(q->op1)-1]==']'){if(q->op2[strlen(q->op2)-1]==']')
                                                                 {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                  printf("DIV AX,%s\n",q->op2);
                                                                  printf("MOV %s,AX\n",q->res);
                                                                  printf("PUSH AX\n");

                                                                  fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                  fprintf(code_objet,"DIV AX,%s\n",q->op2);
                                                                  fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                  fprintf(code_objet,"PUSH AX\n");
                                                                }                                                                  
                                                                  else{if(recherche(q->op2)!=NULL)
            	                                                          {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                         printf("DIV AX,%s\n",q->op2);
                                                                         printf("MOV %s,AX\n",q->res);
                                                                         printf("PUSH AX\n");

                                                                         fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                         fprintf(code_objet,"DIV AX,%s\n",q->op2);
                                                                         fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                         fprintf(code_objet,"PUSH AX\n");
                                                                       }
                                                                         else {if(q->op2[0]=='T')
                                                                                {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                                 printf("POP BX\n");
                                                                                 printf("DIV AX,BX\n");
                                                                                 printf("MOV %s,AX\n",q->res);
                                                                                 printf("PUSH AX\n");

                                                                                 fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                                 fprintf(code_objet,"POP BX\n");
                                                                                 fprintf(code_objet,"DIV AX,BX\n");
                                                                                 fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                                 fprintf(code_objet,"PUSH AX\n");
                                                                               }
                                                                                else{printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                                     printf("DIV AX,%s\n",q->op2);
                                                                                     printf("MOV %s,AX\n",q->res);
                                                                                     printf("PUSH AX\n");

                                                                                     fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                                     fprintf(code_objet,"DIV AX,%s\n",q->op2);
                                                                                     fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                                     fprintf(code_objet,"PUSH AX\n");
                                                                                   }                          
                                                                                }
                                                                        }
                                                                }
                              else {if(recherche(q->op1)!=NULL){if(q->op2[strlen(q->op2)-1]==']')
                                                                 {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                  printf("DIV AX,%s\n",q->op2);
                                                                  printf("MOV %s,AX\n",q->res);
                                                                  printf("PUSH AX\n");

                                                                  fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                  fprintf(code_objet,"DIV AX,%s\n",q->op2);
                                                                  fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                  fprintf(code_objet,"PUSH AX\n");
                                                                }
                                                                 else{if(recherche(q->op2)!=NULL)
            	                                                         {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                        printf("DIV AX,%s\n",q->op2);
                                                                        printf("MOV %s,AX\n",q->res);
                                                                        printf("PUSH AX\n");

                                                                        fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                        fprintf(code_objet,"DIV AX,%s\n",q->op2);
                                                                        fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                        fprintf(code_objet,"PUSH AX\n");
                                                                      }
                                                                       else {if(q->op2[0]=='T')
                                                                             {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                              printf("POP BX\n");
                                                                              printf("DIV AX,BX\n");
                                                                              printf("MOV %s,AX\n",q->res);
                                                                              printf("PUSH AX\n");

                                                                              fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                              fprintf(code_objet,"POP BX\n");
                                                                              fprintf(code_objet,"DIV AX,BX\n");
                                                                              fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                              fprintf(code_objet,"PUSH AX\n");
                                                                            }
                                                                             else{printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                                  printf("DIV AX,%s\n",q->op2);
                                                                                  printf("MOV %s,AX\n",q->res);
                                                                                  printf("PUSH AX\n");

                                                                                  fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                                  fprintf(code_objet,"DIV AX,%s\n",q->op2);
                                                                                  fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                                  fprintf(code_objet,"PUSH AX\n");
                                                                                }
                                                                             }
                                                                       }
                                                                }
                                     else{if(q->op1[0]=='T'){if(q->op2[strlen(q->op2)-1]==']')
                                                              {printf("ETIQ%d: POP AX\n",q->num);                        
                                                               printf("DIV AX,%s\n",q->op2);
                                                               printf("MOV %s,AX\n",q->res);
                                                               printf("PUSH AX\n");

                                                               fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);                        
                                                               fprintf(code_objet,"DIV AX,%s\n",q->op2);
                                                               fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                               fprintf(code_objet,"PUSH AX\n");
                                                             }
                                                              else{if(recherche(q->op2)!=NULL)
            	                                                      {printf("ETIQ%d: POP AX\n",q->num);
                                                                     printf("DIV AX,%s\n",q->op2);
                                                                     printf("MOV %s,AX\n",q->res);
                                                                     printf("PUSH AX\n");

                                                                     fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                     fprintf(code_objet,"DIV AX,%s\n",q->op2);
                                                                     fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                     fprintf(code_objet,"PUSH AX\n");
                                                                    }
                                                                    else {if(q->op2[0]=='T')
                                                                           {printf("ETIQ%d: POP BX\n",q->num);
                                                                            printf("POP AX\n");
                                                                            printf("DIV AX,BX\n");
                                                                            printf("MOV %s,AX\n",q->res);
                                                                            printf("PUSH AX\n");

                                                                            fprintf(code_objet,"ETIQ%d: POP BX\n",q->num);
                                                                            fprintf(code_objet,"POP AX\n");
                                                                            fprintf(code_objet,"DIV AX,BX\n");
                                                                            fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                            fprintf(code_objet,"PUSH AX\n");
                                                                          }
                                                                           else{printf("ETIQ%d: POP AX\n",q->num);
                                  	                                            printf("DIV AX,%s\n",q->op2);
                                                                                printf("MOV %s,AX\n",q->res);
                                                                                printf("PUSH AX\n");

                                                                                fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                                fprintf(code_objet,"DIV AX,%s\n",q->op2);
                                                                                fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                                fprintf(code_objet,"PUSH AX\n");
                                                                              }                                                              
                                                                           }
                                                                  }
                 	                                        }
                 	                       else {if(q->op2[strlen(q->op2)-1]==']')
                 	  	                           {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                   printf("DIV AX,%s\n",q->op2);
                                                   printf("MOV %s,AX\n",q->res);
                                                   printf("PUSH AX\n");

                                                   fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                   fprintf(code_objet,"DIV AX,%s\n",q->op2);
                                                   fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                   fprintf(code_objet,"PUSH AX\n");
                                                 }
                 	  	                         else{if(recherche(q->op2)!=NULL)
            	                                        {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                        printf("DIV AX,%s\n",q->op2);
                                                        printf("MOV %s,AX\n",q->res);
                                                        printf("PUSH AX\n");

                                                        fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                        fprintf(code_objet,"DIV AX,%s\n",q->op2);
                                                        fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                        fprintf(code_objet,"PUSH AX\n");
                                                      }
                                                      else {if(q->op2[0]=='T')
                                                             {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                              printf("POP BX\n");
                                                              printf("DIV AX,BX\n");
                                                              printf("MOV %s,AX\n",q->res);
                                                              printf("PUSH AX\n");

                                                              fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                              fprintf(code_objet,"POP BX\n");
                                                              fprintf(code_objet,"DIV AX,BX\n");
                                                              fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                              fprintf(code_objet,"PUSH AX\n");
                                                            }
                                                             else{printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                  	                              printf("DIV AX,%s\n",q->op2);
                                                                  printf("MOV %s,AX\n",q->res);
                                                                  printf("PUSH AX\n");

                                                                  fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                                                  fprintf(code_objet,"DIV AX,%s\n",q->op2);
                                                                  fprintf(code_objet,"MOV %s,AX\n",q->res);
                                                                  fprintf(code_objet,"PUSH AX\n");
                                                                }                          
                                                            }
                                                        }
                 	                            }
                                         }
                }
            }
     if(strcmp(q->op,":=")==0){if(q->op1[strlen(q->op1)-1]==']')
                                {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                 printf("MOV %s,AX\n",q->res);
                                 fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                 fprintf(code_objet,"MOV %s,AX\n",q->res);
                                 }
                                else {if(recherche(q->op1)!=NULL)
     	                                 {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                        printf("MOV %s,AX\n",q->res);
                                        fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op1);
                                        fprintf(code_objet,"MOV %s,AX\n",q->res);
                                       }             
                                      else{if(q->op1[0]=='T')
                                            {printf("ETIQ%d: POP AX\n",q->num);
                                             printf("MOV %s,AX\n",q->res);
                                             fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                             fprintf(code_objet,"MOV %s,AX\n",q->res);
                                             }
                                           else {printf("ETIQ%d: MOV %s,%s\n",q->num,q->res,q->op1);fprintf(code_objet,"ETIQ%d: MOV %s,%s\n",q->num,q->res,q->op1);}
                                           }
                                     }
                                }

     if(strcmp(q->op,"BR")!=0){if(strcmp(q->op,"BNE")==0){if(q->op2[strlen(q->op2)-1]==']'){if(q->res[strlen(q->res)-1]==']')
                                                                                             {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                              printf("CMP AX,%s\n",q->res);
                                                                                              printf("JNE ETIQ%s\n",q->op1);

                                                                                              fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                              fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                              fprintf(code_objet,"JNE ETIQ%s\n",q->op1);
                                                                                              }
                                                                                             else{if(recherche(q->res)!=NULL)
                                                             	                                     {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                    printf("CMP AX,%s\n",q->res);
                                                                                                    printf("JNE ETIQ%s\n",q->op1);

                                                                                                    fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                    fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                    fprintf(code_objet,"JNE ETIQ%s\n",q->op1);
                                                                                                   }
                                                                                                  else{if(q->res[0]=='T')
                                                                                                       {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                        printf("POP BX\n");	
                                                                                                        printf("CMP AX,BX\n");
                                                                                                        printf("JNE ETIQ%s\n",q->op1);

                                                                                                        fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                        fprintf(code_objet,"POP BX\n"); 
                                                                                                        fprintf(code_objet,"CMP AX,BX\n");
                                                                                                        fprintf(code_objet,"JNE ETIQ%s\n",q->op1);
                                                                                                        }
                                                                                                      else{printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                           printf("CMP AX,%s\n",q->res);
                                                                                                           printf("JNE ETIQ%s\n",q->op1);

                                                                                                           fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                           fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                           fprintf(code_objet,"JNE ETIQ%s\n",q->op1);
                                                                                                           }
                                                                                                      }
                                                                                                 }
                                                                                            }
                                                            else{if(recherche(q->op2)!=NULL){if(q->res[strlen(q->res)-1]==']')
                                                                                              {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                               printf("CMP AX,%s\n",q->res);
                                                                                               printf("JNE ETIQ%s\n",q->op1);

                                                                                               fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                               fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                               fprintf(code_objet,"JNE ETIQ%s\n",q->op1);
                                                                                               }
                                                                                              else{if(recherche(q->res)!=NULL)
                                                             	                                      {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                     printf("CMP AX,%s\n",q->res);
                                                                                                     printf("JNE ETIQ%s\n",q->op1);

                                                                                                     fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                     fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                     fprintf(code_objet,"JNE ETIQ%s\n",q->op1);
                                                                                                     }
                                                                                                 else{if(q->res[0]=='T')
                                                                                                       {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                        printf("POP BX\n");	
                                                                                                        printf("CMP AX,BX\n");
                                                                                                        printf("JNE ETIQ%s\n",q->op1);

                                                                                                        fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                        fprintf(code_objet,"POP BX\n"); 
                                                                                                        fprintf(code_objet,"CMP AX,BX\n");
                                                                                                        fprintf(code_objet,"JNE ETIQ%s\n",q->op1);
                                                                                                      }
                                                                                                      else{printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                           printf("CMP AX,%s\n",q->res);
                                                                                                           printf("JNE ETIQ%s\n",q->op1);

                                                                                                           fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                           fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                           fprintf(code_objet,"JNE ETIQ%s\n",q->op1);
                                                                                                           }
                                                                                                      }
                                                                                                 }
                                                                                            }                                                     	  

                                                            	  else{if(q->op2[0]=='T'){if(q->res[strlen(q->res)-1]==']')
                                                                                              {printf("ETIQ%d: POP AX\n",q->num);
                                                                                               printf("CMP AX,%s\n",q->res);
                                                                                               printf("JNE ETIQ%s\n",q->op1);

                                                                                               fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                                               fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                               fprintf(code_objet,"JNE ETIQ%s\n",q->op1);
                                                                                               }
                                                                                              else{if(recherche(q->res)!=NULL)
                                                             	                                      {printf("ETIQ%d: POP AX\n",q->num);
                                                                                                     printf("CMP AX,%s\n",q->res);
                                                                                                     printf("JNE ETIQ%s\n",q->op1);

                                                                                                     fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                                                     fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                     fprintf(code_objet,"JNE ETIQ%s\n",q->op1);
                                                                                                     }
                                                                                                   else{if(q->res[0]=='T')
                                                                                                         {printf("ETIQ%d: POP BX\n",q->num);
                                                                                                          printf("POP AX\n");	
                                                                                                          printf("CMP AX,BX\n");
                                                                                                          printf("JNE ETIQ%s\n",q->op1);

                                                                                                          fprintf(code_objet,"ETIQ%d: POP BX\n",q->num);
                                                                                                          fprintf(code_objet,"POP AX\n"); 
                                                                                                          fprintf(code_objet,"CMP AX,BX\n");
                                                                                                          fprintf(code_objet,"JNE ETIQ%s\n",q->op1);
                                                                                                          }
                                                                                                        else{printf("ETIQ%d: POP AX\n",q->num);
                                                                                                             printf("CMP AX,%s\n",q->res);
                                                                                                             printf("JNE ETIQ%s\n",q->op1);

                                                                                                             fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                                                             fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                             fprintf(code_objet,"JNE ETIQ%s\n",q->op1);
                                                                                                             }
                                                                                                        }
                                                                                                   }
                                                                                           }
                                                                         else{if(q->res[strlen(q->res)-1]==']')
                                                                                              {printf("ETIQ%d: MOV AX,%s\n",q->num,q->res);
                                                                                               printf("CMP %s,AX\n",q->op2);
                                                                                               printf("JNE ETIQ%s\n",q->op1);

                                                                                               fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->res);
                                                                                               fprintf(code_objet,"CMP %s,AX\n",q->op2);
                                                                                               fprintf(code_objet,"JNE ETIQ%s\n",q->op1);
                                                                                               }
                                                                                              else{if(recherche(q->res)!=NULL)
                                                             	                                      {printf("ETIQ%d: MOV AX,%s\n",q->num,q->res);
                                                                                                     printf("CMP %s,AX\n",q->op2);
                                                                                                     printf("JNE ETIQ%s\n",q->op1);

                                                                                                     fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->res);
                                                                                                     fprintf(code_objet,"CMP %s,AX\n",q->op2);
                                                                                                     fprintf(code_objet,"JNE ETIQ%s\n",q->op1);
                                                                                                     }
                                                                                                    else{if(q->res[0]=='T')
                                                                                                          {printf("ETIQ%d: POP AX\n",q->num);                                                                                                          	
                                                                                                           printf("CMP %s,AX\n",q->op2);
                                                                                                           printf("JNE ETIQ%s\n",q->op1);

                                                                                                           fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);                                                                                                            
                                                                                                           fprintf(code_objet,"CMP %s,AX\n",q->op2);
                                                                                                           fprintf(code_objet,"JNE ETIQ%s\n",q->op1);
                                                                                                           }
                                                                                                           else{printf("ETIQ%d: CMP %s,%s\n",q->num,q->op2,q->res);
                                                                                                                printf("JNE ETIQ%s\n",q->op1);

                                                                                                                fprintf(code_objet,"ETIQ%d: CMP %s,%s\n",q->num,q->op2,q->res);
                                                                                                                fprintf(code_objet,"JNE ETIQ%s\n",q->op1);
                                                                                                                }
                                                                                                         }
                                                                                                   }
                                                                              }
                                                            	      }
                                                                }
                                                         }

                                if(strcmp(q->op,"BE")==0){if(q->op2[strlen(q->op2)-1]==']'){if(q->res[strlen(q->res)-1]==']')
                                                                                             {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                              printf("CMP AX,%s\n",q->res);
                                                                                              printf("JE ETIQ%s\n",q->op1);

                                                                                              fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                              fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                              fprintf(code_objet,"JE ETIQ%s\n",q->op1);
                                                                                            }
                                                                                             else{if(recherche(q->res)!=NULL)
                                                             	                                     {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                    printf("CMP AX,%s\n",q->res);
                                                                                                    printf("JE ETIQ%s\n",q->op1);

                                                                                                    fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                    fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                    fprintf(code_objet,"JE ETIQ%s\n",q->op1);
                                                                                                   }
                                                                                                 else{if(q->res[0]=='T')
                                                                                                       {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                        printf("POP BX\n");	
                                                                                                        printf("CMP AX,BX\n");
                                                                                                        printf("JE ETIQ%s\n",q->op1);

                                                                                                        fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                        fprintf(code_objet,"POP BX\n"); 
                                                                                                        fprintf(code_objet,"CMP AX,BX\n");
                                                                                                        fprintf(code_objet,"JE ETIQ%s\n",q->op1);
                                                                                                      }
                                                                                                      else{printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                           printf("CMP AX,%s\n",q->res);
                                                                                                           printf("JE ETIQ%s\n",q->op1);

                                                                                                           fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                           fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                           fprintf(code_objet,"JE ETIQ%s\n",q->op1);
                                                                                                           }
                                                                                                      }
                                                                                                 }
                                                                                            }
                                                            else{if(recherche(q->op2)!=NULL){if(q->res[strlen(q->res)-1]==']')
                                                                                              {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                               printf("CMP AX,%s\n",q->res);
                                                                                               printf("JE ETIQ%s\n",q->op1);

                                                                                               fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                               fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                               fprintf(code_objet,"JE ETIQ%s\n",q->op1);
                                                                                             }
                                                                                              else{if(recherche(q->res)!=NULL)
                                                             	                                      {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                     printf("CMP AX,%s\n",q->res);
                                                                                                     printf("JE ETIQ%s\n",q->op1);

                                                                                                     fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                     fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                     fprintf(code_objet,"JE ETIQ%s\n",q->op1);
                                                                                                   }
                                                                                                   else{if(q->res[0]=='T')
                                                                                                         {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                          printf("POP BX\n");	
                                                                                                          printf("CMP AX,BX\n");
                                                                                                          printf("JE ETIQ%s\n",q->op1);

                                                                                                          fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                          fprintf(code_objet,"POP BX\n"); 
                                                                                                          fprintf(code_objet,"CMP AX,BX\n");
                                                                                                          fprintf(code_objet,"JE ETIQ%s\n",q->op1);
                                                                                                        }
                                                                                                        else{printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                             printf("CMP AX,%s\n",q->res);
                                                                                                             printf("JE ETIQ%s\n",q->op1);

                                                                                                             fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                             fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                             fprintf(code_objet,"JE ETIQ%s\n",q->op1);
                                                                                                            }
                                                                                                      }
                                                                                                 }
                                                                                            }                                                     	  

                                                            	  else{if(q->op2[0]=='T'){if(q->res[strlen(q->res)-1]==']')
                                                                                              {printf("ETIQ%d: POP AX\n",q->num);
                                                                                               printf("CMP AX,%s\n",q->res);
                                                                                               printf("JE ETIQ%s\n",q->op1);

                                                                                               fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                                               fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                               fprintf(code_objet,"JE ETIQ%s\n",q->op1);
                                                                                             }
                                                                                              else{if(recherche(q->res)!=NULL)
                                                             	                                      {printf("ETIQ%d: POP AX\n",q->num);
                                                                                                     printf("CMP AX,%s\n",q->res);
                                                                                                     printf("JE ETIQ%s\n",q->op1);

                                                                                                     fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                                                     fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                     fprintf(code_objet,"JE ETIQ%s\n",q->op1);
                                                                                                   }
                                                                                                   else{if(q->res[0]=='T')
                                                                                                         {printf("ETIQ%d: POP BX\n",q->num);
                                                                                                          printf("POP AX\n");	
                                                                                                          printf("CMP AX,BX\n");
                                                                                                          printf("JE ETIQ%s\n",q->op1);

                                                                                                          fprintf(code_objet,"ETIQ%d: POP BX\n",q->num);
                                                                                                          fprintf(code_objet,"POP AX\n"); 
                                                                                                          fprintf(code_objet,"CMP AX,BX\n");
                                                                                                          fprintf(code_objet,"JE ETIQ%s\n",q->op1);
                                                                                                        }
                                                                                                        else{printf("ETIQ%d: POP AX\n",q->num);
                                                                                                             printf("CMP AX,%s\n",q->res);
                                                                                                             printf("JE ETIQ%s\n",q->op1);

                                                                                                             fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                                                             fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                             fprintf(code_objet,"JE ETIQ%s\n",q->op1);
                                                                                                             }
                                                                                                        }
                                                                                                   }
                                                                                           }
                                                                         else{if(q->res[strlen(q->res)-1]==']')
                                                                                              {printf("ETIQ%d: MOV AX,%s",q->num,q->res);
                                                                                               printf("CMP %s,AX\n",q->op2);
                                                                                               printf("JE ETIQ%s\n",q->op1);

                                                                                               fprintf(code_objet,"ETIQ%d: MOV AX,%s",q->num,q->res);
                                                                                               fprintf(code_objet,"CMP %s,AX\n",q->op2);
                                                                                               fprintf(code_objet,"JE ETIQ%s\n",q->op1);
                                                                                               }
                                                                                              else{if(recherche(q->res)!=NULL)
                                                             	                                      {printf("ETIQ%d: MOV AX,%s",q->num,q->res);
                                                                                                     printf("CMP %s,AX\n",q->op2);
                                                                                                     printf("JE ETIQ%s\n",q->op1);

                                                                                                     fprintf(code_objet,"ETIQ%d: MOV AX,%s",q->num,q->res);
                                                                                                     fprintf(code_objet,"CMP %s,AX\n",q->op2);
                                                                                                     fprintf(code_objet,"JE ETIQ%s\n",q->op1);
                                                                                                     }
                                                                                                    else{if(q->res[0]=='T')
                                                                                                          {printf("ETIQ%d: POP AX\n",q->num);                                                                                                          	
                                                                                                           printf("CMP %s,AX\n",q->op2);
                                                                                                           printf("JE ETIQ%s\n",q->op1);

                                                                                                           fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);                                                                                                            
                                                                                                           fprintf(code_objet,"CMP %s,AX\n",q->op2);
                                                                                                           fprintf(code_objet,"JE ETIQ%s\n",q->op1);
                                                                                                           }
                                                                                                          else{printf("ETIQ%d: CMP %s,%s\n",q->num,q->op2,q->res);
                                                                                                               printf("JE ETIQ%s\n",q->op1);

                                                                                                               fprintf(code_objet,"ETIQ%d: CMP %s,%s\n",q->num,q->op2,q->res);
                                                                                                               fprintf(code_objet,"JE ETIQ%s\n",q->op1);
                                                                                                               }
                                                                                                         }
                                                                                                   }
                                                                              }
                                                            	      }
                                                                }
                                                         }
                                if(strcmp(q->op,"BGE")==0){if(q->op2[strlen(q->op2)-1]==']'){if(q->res[strlen(q->res)-1]==']')
                                                                                             {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                              printf("CMP AX,%s\n",q->res);
                                                                                              printf("JGE ETIQ%s\n",q->op1);

                                                                                              fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                              fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                              fprintf(code_objet,"JGE ETIQ%s\n",q->op1);
                                                                                            }
                                                                                             else{if(recherche(q->res)!=NULL)
                                                             	                                     {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                    printf("CMP AX,%s\n",q->res);
                                                                                                    printf("JGE ETIQ%s\n",q->op1);

                                                                                                    fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                    fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                    fprintf(code_objet,"JGE ETIQ%s\n",q->op1);
                                                                                                   }
                                                                                                 else{if(q->res[0]=='T')
                                                                                                       {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                        printf("POP BX\n");	
                                                                                                        printf("CMP AX,BX\n");
                                                                                                        printf("JGE ETIQ%s\n",q->op1);

                                                                                                        fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                        fprintf(code_objet,"POP BX\n"); 
                                                                                                        fprintf(code_objet,"CMP AX,BX\n");
                                                                                                        fprintf(code_objet,"JGE ETIQ%s\n",q->op1);
                                                                                                        }
                                                                                                      else{printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                           printf("CMP AX,%s\n",q->res);
                                                                                                           printf("JGE ETIQ%s\n",q->op1);

                                                                                                           fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                           fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                           fprintf(code_objet,"JGE ETIQ%s\n",q->op1);
                                                                                                           }
                                                                                                      }
                                                                                                 }
                                                                                            }
                                                            else{if(recherche(q->op2)!=NULL){if(q->res[strlen(q->res)-1]==']')
                                                                                              {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                               printf("CMP AX,%s\n",q->res);
                                                                                               printf("JGE ETIQ%s\n",q->op1);

                                                                                               fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                               fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                               fprintf(code_objet,"JGE ETIQ%s\n",q->op1);
                                                                                             }
                                                                                              else{if(recherche(q->res)!=NULL)
                                                             	                                      {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                     printf("CMP AX,%s\n",q->res);
                                                                                                     printf("JGE ETIQ%s\n",q->op1);

                                                                                                     fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                     fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                     fprintf(code_objet,"JGE ETIQ%s\n",q->op1);
                                                                                                   }
                                                                                                 else{if(q->res[0]=='T')
                                                                                                       {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                        printf("POP BX\n");	
                                                                                                        printf("CMP AX,BX\n");
                                                                                                        printf("JGE ETIQ%s\n",q->op1);

                                                                                                        fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                        fprintf(code_objet,"POP BX\n"); 
                                                                                                        fprintf(code_objet,"CMP AX,BX\n");
                                                                                                        fprintf(code_objet,"JGE ETIQ%s\n",q->op1);
                                                                                                      }
                                                                                                      else{printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                           printf("CMP AX,%s\n",q->res);
                                                                                                           printf("JGE ETIQ%s\n",q->op1);

                                                                                                           fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                           fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                           fprintf(code_objet,"JGE ETIQ%s\n",q->op1);
                                                                                                           }
                                                                                                      }
                                                                                                 }
                                                                                            }                                                     	  

                                                            	  else{if(q->op2[0]=='T'){if(q->res[strlen(q->res)-1]==']')
                                                                                              {printf("ETIQ%d: POP AX\n",q->num);
                                                                                               printf("CMP AX,%s\n",q->res);
                                                                                               printf("JGE ETIQ%s\n",q->op1);

                                                                                               fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                                               fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                               fprintf(code_objet,"JGE ETIQ%s\n",q->op1);
                                                                                               }
                                                                                              else{if(recherche(q->res)!=NULL)
                                                             	                                      {printf("ETIQ%d: POP AX\n",q->num);
                                                                                                     printf("CMP AX,%s\n",q->res);
                                                                                                     printf("JGE ETIQ%s\n",q->op1);

                                                                                                     fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                                                     fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                     fprintf(code_objet,"JGE ETIQ%s\n",q->op1);
                                                                                                     }
                                                                                                   else{if(q->res[0]=='T')
                                                                                                         {printf("ETIQ%d: POP BX\n",q->num);
                                                                                                          printf("POP AX\n");	
                                                                                                          printf("CMP AX,BX\n");
                                                                                                          printf("JGE ETIQ%s\n",q->op1);

                                                                                                          fprintf(code_objet,"ETIQ%d: POP BX\n",q->num);
                                                                                                          fprintf(code_objet,"POP AX\n"); 
                                                                                                          fprintf(code_objet,"CMP AX,BX\n");
                                                                                                          fprintf(code_objet,"JGE ETIQ%s\n",q->op1);
                                                                                                          }
                                                                                                        else{printf("ETIQ%d: POP AX\n",q->num);
                                                                                                             printf("CMP AX,%s\n",q->res);
                                                                                                             printf("JGE ETIQ%s\n",q->op1);

                                                                                                             fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                                                             fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                             fprintf(code_objet,"JGE ETIQ%s\n",q->op1);
                                                                                                             }
                                                                                                        }
                                                                                                   }
                                                                                           }
                                                                         else{if(q->res[strlen(q->res)-1]==']')
                                                                                              {printf("ETIQ%d: MOV AX,%s\n",q->num,q->res);
                                                                                               printf("CMP %s,AX\n",q->op2);
                                                                                               printf("JGE ETIQ%s\n",q->op1);

                                                                                               fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->res);
                                                                                               fprintf(code_objet,"CMP %s,AX\n",q->op2);
                                                                                               fprintf(code_objet,"JGE ETIQ%s\n",q->op1);
                                                                                               }
                                                                                              else{if(recherche(q->res)!=NULL)
                                                             	                                      {printf("ETIQ%d: MOV AX,%s\n",q->num,q->res);
                                                                                                     printf("CMP %s,AX\n",q->op2);
                                                                                                     printf("JGE ETIQ%s\n",q->op1);

                                                                                                     fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->res);
                                                                                                     fprintf(code_objet,"CMP %s,AX\n",q->op2);
                                                                                                     fprintf(code_objet,"JGE ETIQ%s\n",q->op1);
                                                                                                     }
                                                                                                    else{if(q->res[0]=='T')
                                                                                                          {printf("ETIQ%d: POP AX\n",q->num);                                                                                                          	
                                                                                                           printf("CMP %s,AX\n",q->op2);
                                                                                                           printf("JGE ETIQ%s\n",q->op1);

                                                                                                           fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);                                                                                                            
                                                                                                           fprintf(code_objet,"CMP %s,AX\n",q->op2);
                                                                                                           fprintf(code_objet,"JGE ETIQ%s\n",q->op1);
                                                                                                          }
                                                                                                           else{printf("ETIQ%d: CMP %s,%s\n",q->num,q->op2,q->res);
                                                                                                                printf("JGE ETIQ%s\n",q->op1);

                                                                                                                fprintf(code_objet,"ETIQ%d: CMP %s,%s\n",q->num,q->op2,q->res);
                                                                                                                fprintf(code_objet,"JGE ETIQ%s\n",q->op1);
                                                                                                               }
                                                                                                         }
                                                                                                   }
                                                                              }
                                                            	      }
                                                                }
                                                         }                         

                                if(strcmp(q->op,"BG")==0){if(q->op2[strlen(q->op2)-1]=']'){if(q->res[strlen(q->res)-1]==']')
                                                                                             {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                              printf("CMP AX,%s\n",q->res);
                                                                                              printf("JG ETIQ%s\n",q->op1);

                                                                                              fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                              fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                              fprintf(code_objet,"JG ETIQ%s\n",q->op1);
                                                                                             }
                                                                                             else{if(recherche(q->res)!=NULL)
                                                             	                                     {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                    printf("CMP AX,%s\n",q->res);
                                                                                                    printf("JG ETIQ%s\n",q->op1);

                                                                                                    fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                    fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                    fprintf(code_objet,"JG ETIQ%s\n",q->op1);
                                                                                                  }
                                                                                                 else{if(q->res[0]=='T')
                                                                                                       {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                        printf("POP BX\n");	
                                                                                                        printf("CMP AX,BX\n");
                                                                                                        printf("JG ETIQ%s\n",q->op1);

                                                                                                        fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                        fprintf(code_objet,"POP BX\n"); 
                                                                                                        fprintf(code_objet,"CMP AX,BX\n");
                                                                                                        fprintf(code_objet,"JG ETIQ%s\n",q->op1);
                                                                                                      }
                                                                                                      else{printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                           printf("CMP AX,%s\n",q->res);
                                                                                                           printf("JG ETIQ%s\n",q->op1);

                                                                                                           fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                           fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                           fprintf(code_objet,"JG ETIQ%s\n",q->op1);
                                                                                                           }
                                                                                                      }
                                                                                                 }
                                                                                            }
                                                            else{if(recherche(q->op2)!=NULL){if(q->res[strlen(q->res)-1]==']')
                                                                                              {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                               printf("CMP AX,%s\n",q->res);
                                                                                               printf("JG ETIQ%s\n",q->op1);

                                                                                               fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                               fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                               fprintf(code_objet,"JG ETIQ%s\n",q->op1);
                                                                                               }
                                                                                              else{if(recherche(q->res)!=NULL)
                                                             	                                      {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                     printf("CMP AX,%s\n",q->res);
                                                                                                     printf("JG ETIQ%s\n",q->op1);

                                                                                                     fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                     fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                     fprintf(code_objet,"JG ETIQ%s\n",q->op1);
                                                                                                   }
                                                                                                 else{if(q->res[0]=='T')
                                                                                                       {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                        printf("POP BX\n");	
                                                                                                        printf("CMP AX,BX\n");
                                                                                                        printf("JG ETIQ%s\n",q->op1);

                                                                                                        fprintf(code_objet,"ETIQ%d: MOV AX, %s \n",q->num,q->op2);
                                                                                                        fprintf(code_objet,"POP BX\n"); 
                                                                                                        fprintf(code_objet,"CMP AX,BX\n");
                                                                                                        fprintf(code_objet,"JG ETIQ%s \n",q->op1);
                                                                                                        }
                                                                                                      else{printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                           printf("CMP AX,%s\n",q->res);
                                                                                                           printf("JG ETIQ%s\n",q->op1);

                                                                                                           fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                           fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                           fprintf(code_objet,"JG ETIQ%s\n",q->op1);
                                                                                                           }
                                                                                                      }
                                                                                                 }
                                                                                            }                                                     	  

                                                            	  else{if(q->op2[0]=='T'){if(q->res[strlen(q->res)-1]==']')
                                                                                              {printf("ETIQ%d: POP AX\n",q->num);
                                                                                               printf("CMP AX,%s\n",q->res);
                                                                                               printf("JG ETIQ%s\n",q->op1);

                                                                                               fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                                               fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                               fprintf(code_objet,"JG ETIQ%s\n",q->op1);
                                                                                             }
                                                                                              else{if(recherche(q->res)!=NULL)
                                                             	                                      {printf("ETIQ%d: POP AX\n",q->num);
                                                                                                     printf("CMP AX,%s\n",q->res);
                                                                                                     printf("JG ETIQ%s\n",q->op1);

                                                                                                     fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                                                     fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                     fprintf(code_objet,"JG ETIQ%s\n",q->op1);
                                                                                                    }
                                                                                                   else{if(q->res[0]=='T')
                                                                                                         {printf("ETIQ%d: POP BX\n",q->num);
                                                                                                          printf("POP AX\n");	
                                                                                                          printf("CMP AX,BX\n");
                                                                                                          printf("JG ETIQ%s\n",q->op1);

                                                                                                          fprintf(code_objet,"ETIQ%d: POP BX\n",q->num);
                                                                                                          fprintf(code_objet,"POP AX\n"); 
                                                                                                          fprintf(code_objet,"CMP AX,BX\n");
                                                                                                          fprintf(code_objet,"JG ETIQ%s\n",q->op1);
                                                                                                        }
                                                                                                        else{printf("ETIQ%d: POP AX\n",q->num);
                                                                                                             printf("CMP AX,%s\n",q->res);
                                                                                                             printf("JG ETIQ%s\n",q->op1);

                                                                                                             fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                                                             fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                             fprintf(code_objet,"JG ETIQ%s\n",q->op1);
                                                                                                             }
                                                                                                        }
                                                                                                   }
                                                                                           }
                                                                         else{if(q->res[strlen(q->res)-1]==']')
                                                                                              {printf("ETIQ%d: MOV AX,%s \n",q->num,q->res);
                                                                                               printf("CMP %s,AX\n",q->op2);
                                                                                               printf("JG ETIQ%s\n",q->op1);

                                                                                               fprintf(code_objet,"ETIQ%d: MOV AX,%s \n",q->num,q->res);
                                                                                               fprintf(code_objet,"CMP %s,AX\n",q->op2);
                                                                                               fprintf(code_objet,"JG ETIQ%s\n",q->op1);
                                                                                             }
                                                                                              else{if(recherche(q->res)!=NULL)
                                                             	                                      {printf("ETIQ%d: MOV AX,%s \n",q->num,q->res);
                                                                                                     printf("CMP %s,AX\n",q->op2);
                                                                                                     printf("JG ETIQ%s\n",q->op1);

                                                                                                     fprintf(code_objet,"ETIQ%d: MOV AX,%s \n",q->num,q->res);
                                                                                                     fprintf(code_objet,"CMP %s,AX\n",q->op2);
                                                                                                     fprintf(code_objet,"JG ETIQ%s\n",q->op1);
                                                                                                     }
                                                                                                    else{if(q->res[0]=='T')
                                                                                                         {printf("ETIQ%d: POP AX\n",q->num);                                                                                                          	
                                                                                                          printf("CMP %s ,AX\n",q->op2);
                                                                                                          printf("JG ETIQ%s\n",q->op1);

                                                                                                          fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);                                                                                                           
                                                                                                          fprintf(code_objet,"CMP %s ,AX\n",q->op2);
                                                                                                          fprintf(code_objet,"JG ETIQ%s\n",q->op1);
                                                                                                        }
                                                                                                          else{printf("ETIQ%d: CMP %s,%s\n",q->num,q->op2,q->res);
                                                                                                               printf("JG ETIQ%s\n",q->op1);

                                                                                                               fprintf(code_objet,"ETIQ%d: CMP %s,%s\n",q->num,q->op2,q->res);
                                                                                                               fprintf(code_objet,"JG ETIQ%s\n",q->op1);
                                                                                                               }
                                                                                                         }
                                                                                                   }
                                                                              }
                                                            	      }
                                                                }
                                                         }
                                if(strcmp(q->op,"BLE")==0){if(q->op2[strlen(q->op2)-1]==']'){if(q->res[strlen(q->res)-1]==']')
                                                                                              {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                               printf("CMP AX,%s\n",q->res);
                                                                                               printf("JLE ETIQ%s\n",q->op1);

                                                                                               fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                               fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                               fprintf(code_objet,"JLE ETIQ%s\n",q->op1);
                                                                                               }
                                                                                             else{if(recherche(q->res)!=NULL)
                                                             	                                     {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                    printf("CMP AX,%s\n",q->res);
                                                                                                    printf("JLE ETIQ%s\n",q->op1);

                                                                                                    fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                    fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                    fprintf(code_objet,"JLE ETIQ%s\n",q->op1);
                                                                                                   }
                                                                                                 else{if(q->res[0]=='T')
                                                                                                       {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                        printf("POP BX\n");	
                                                                                                        printf("CMP AX,BX\n");
                                                                                                        printf("JLE ETIQ%s\n",q->op1);

                                                                                                        fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                        fprintf(code_objet,"POP BX\n"); 
                                                                                                        fprintf(code_objet,"CMP AX,BX\n");
                                                                                                        fprintf(code_objet,"JLE ETIQ%s\n",q->op1);
                                                                                                         }
                                                                                                      else{printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                           printf("CMP AX,%s\n",q->res);
                                                                                                           printf("JLE ETIQ%s\n",q->op1);

                                                                                                           fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                           fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                           fprintf(code_objet,"JLE ETIQ%s\n",q->op1);
                                                                                                           }
                                                                                                      }
                                                                                                 }
                                                                                            }
                                                            else{if(recherche(q->op2)!=NULL){if(q->res[strlen(q->res)-1]==']')
                                                                                              {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                               printf("CMP AX,%s\n",q->res);
                                                                                               printf("JLE ETIQ%s\n",q->op1);

                                                                                               fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                               fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                               fprintf(code_objet,"JLE ETIQ%s\n",q->op1);
                                                                                               }
                                                                                              else{if(recherche(q->res)!=NULL)
                                                             	                                      {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                     printf("CMP AX,%s\n",q->res);
                                                                                                     printf("JLE ETIQ%s\n",q->op1);

                                                                                                     fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                     fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                     fprintf(code_objet,"JLE ETIQ%s\n",q->op1);
                                                                                                     }
                                                                                                 else{if(q->res[0]=='T')
                                                                                                       {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                        printf("POP BX\n");	
                                                                                                        printf("CMP AX,BX\n");
                                                                                                        printf("JLE ETIQ%s\n",q->op1);

                                                                                                        fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                        fprintf(code_objet,"POP BX\n"); 
                                                                                                        fprintf(code_objet,"CMP AX,BX\n");
                                                                                                        fprintf(code_objet,"JLE ETIQ%s\n",q->op1);
                                                                                                      }
                                                                                                      else{printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                           printf("CMP AX,%s\n",q->res);
                                                                                                           printf("JLE ETIQ%s\n",q->op1);

                                                                                                           fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                           fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                           fprintf(code_objet,"JLE ETIQ%s\n",q->op1);
                                                                                                           }
                                                                                                      }
                                                                                                 }
                                                                                            }                                                     	  

                                                            	  else{if(q->op2[0]=='T'){if(q->res[strlen(q->res)-1]==']')
                                                                                              {printf("ETIQ%d: POP AX\n",q->num);
                                                                                               printf("CMP AX,%s\n",q->res);
                                                                                               printf("JLE ETIQ%s\n",q->op1);

                                                                                               fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                                               fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                               fprintf(code_objet,"JLE ETIQ%s\n",q->op1);
                                                                                             }
                                                                                              else{if(recherche(q->res)!=NULL)
                                                             	                                      {printf("ETIQ%d: POP AX\n",q->num);
                                                                                                     printf("CMP AX,%s\n",q->res);
                                                                                                     printf("JLE ETIQ%s\n",q->op1);

                                                                                                     fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                                                     fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                     fprintf(code_objet,"JLE ETIQ%s\n",q->op1);
                                                                                                     }
                                                                                                   else{if(q->res[0]=='T')
                                                                                                         {printf("ETIQ%d: POP BX\n",q->num);
                                                                                                          printf("POP AX\n");	
                                                                                                          printf("CMP AX,BX\n");
                                                                                                          printf("JLE ETIQ%s\n",q->op1);

                                                                                                          fprintf(code_objet,"ETIQ%d: POP BX\n",q->num);
                                                                                                          fprintf(code_objet,"POP AX\n"); 
                                                                                                          fprintf(code_objet,"CMP AX,BX\n");
                                                                                                          fprintf(code_objet,"JLE ETIQ%s\n",q->op1);
                                                                                                         }
                                                                                                        else{printf("ETIQ%d: POP AX\n",q->num);
                                                                                                             printf("CMP AX,%s\n",q->res);
                                                                                                             printf("JLE ETIQ%s\n",q->op1);

                                                                                                             fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                                                             fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                             fprintf(code_objet,"JLE ETIQ%s\n",q->op1);
                                                                                                             }
                                                                                                        }
                                                                                                   }
                                                                                           }
                                                                         else{if(q->res[strlen(q->res)-1]==']')
                                                                                              {printf("ETIQ%d: MOV AX,%s\n",q->num,q->res);
                                                                                               printf("CMP %s,AX\n",q->op2);
                                                                                               printf("JLE ETIQ%s\n",q->op1);

                                                                                               fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->res);
                                                                                               fprintf(code_objet,"CMP %s,AX\n",q->op2);
                                                                                               fprintf(code_objet,"JLE ETIQ%s\n",q->op1);
                                                                                               }
                                                                                              else{if(recherche(q->res)!=NULL)
                                                             	                                      {printf("ETIQ%d: MOV AX,%s\n",q->num,q->res);
                                                                                                     printf("CMP %s,AX\n",q->op2);
                                                                                                     printf("JLE ETIQ%s\n",q->op1);

                                                                                                     fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->res);
                                                                                                     fprintf(code_objet,"CMP %s,AX\n",q->op2);
                                                                                                     fprintf(code_objet,"JLE ETIQ%s\n",q->op1);
                                                                                                     }
                                                                                                    else{if(q->res[0]=='T')
                                                                                                         {printf("ETIQ%d: POP AX\n",q->num);                                                                                                          	
                                                                                                          printf("CMP %s,AX\n",q->op2);
                                                                                                          printf("JLE ETIQ%s\n",q->op1);

                                                                                                          fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);                                                                                                           
                                                                                                          fprintf(code_objet,"CMP %s,AX\n",q->op2);
                                                                                                          fprintf(code_objet,"JLE ETIQ%s\n",q->op1);
                                                                                                        }
                                                                                                          else{printf("ETIQ%d: CMP %s,%s\n",q->num,q->op2,q->res);
                                                                                                               printf("JLE ETIQ%s\n",q->op1);

                                                                                                               fprintf(code_objet,"ETIQ%d: CMP %s,%s\n",q->num,q->op2,q->res);
                                                                                                               fprintf(code_objet,"JLE ETIQ%s\n",q->op1);
                                                                                                               }
                                                                                                         }
                                                                                                   }
                                                                              }
                                                            	      }
                                                                }
                                                         }
                                if(strcmp(q->op,"BL")==0){if(q->op2[strlen(q->op2)-1]==']'){if(q->res[strlen(q->res)-1]==']')
                                                                                             {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                              printf("CMP AX,%s\n",q->res);
                                                                                              printf("JL ETIQ%s\n",q->op1);

                                                                                              fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                              fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                              fprintf(code_objet,"JL ETIQ%s\n",q->op1);
                                                                                              }
                                                                                             else{if(recherche(q->res)!=NULL)
                                                             	                                     {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                    printf("CMP AX,%s\n",q->res);
                                                                                                    printf("JL ETIQ%s\n",q->op1);

                                                                                                    fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                    fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                    fprintf(code_objet,"JL ETIQ%s\n",q->op1);
                                                                                                    }
                                                                                                 else{if(q->res[0]=='T')
                                                                                                       {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                        printf("POP BX\n");	
                                                                                                        printf("CMP AX,BX\n");
                                                                                                        printf("JL ETIQ%s\n",q->op1);

                                                                                                        fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                        fprintf(code_objet,"POP BX\n"); 
                                                                                                        fprintf(code_objet,"CMP AX,BX\n");
                                                                                                        fprintf(code_objet,"JL ETIQ%s\n",q->op1);
                                                                                                      }
                                                                                                      else{printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                           printf("CMP AX,%s\n",q->res);
                                                                                                           printf("JL ETIQ%s\n",q->op1);

                                                                                                           fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                           fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                           fprintf(code_objet,"JL ETIQ%s\n",q->op1);
                                                                                                           }
                                                                                                      }
                                                                                                 }
                                                                                            }
                                                            else{if(recherche(q->op2)!=NULL){if(q->res[strlen(q->res)-1]==']')
                                                                                              {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                               printf("CMP AX,%s\n",q->res);
                                                                                               printf("JL ETIQ%s\n",q->op1);

                                                                                               fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                               fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                               fprintf(code_objet,"JL ETIQ%s\n",q->op1);
                                                                                             }
                                                                                              else{if(recherche(q->res)!=NULL)
                                                             	                                      {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                     printf("CMP AX,%s\n",q->res);
                                                                                                     printf("JL ETIQ%s\n",q->op1);

                                                                                                     fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                     fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                     fprintf(code_objet,"JL ETIQ%s\n",q->op1);
                                                                                                     }
                                                                                                 else{if(q->res[0]=='T')
                                                                                                       {printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                        printf("POP BX\n");	
                                                                                                        printf("CMP AX,BX\n");
                                                                                                        printf("JL ETIQ%s\n",q->op1);

                                                                                                        fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                        fprintf(code_objet,"POP BX\n"); 
                                                                                                        fprintf(code_objet,"CMP AX,BX\n");
                                                                                                        fprintf(code_objet,"JL ETIQ%s\n",q->op1);
                                                                                                        }
                                                                                                      else{printf("ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                           printf("CMP AX,%s\n",q->res);
                                                                                                           printf("JL ETIQ%s\n",q->op1);

                                                                                                           fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->op2);
                                                                                                           fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                           fprintf(code_objet,"JL ETIQ%s\n",q->op1);
                                                                                                           }
                                                                                                      }
                                                                                                 }
                                                                                            }                                                     	  

                                                            	  else{if(q->op2[0]=='T'){if(q->res[strlen(q->res)-1]==']')
                                                                                              {printf("ETIQ%d: POP AX\n",q->num);
                                                                                               printf("CMP AX,%s\n",q->res);
                                                                                               printf("JL ETIQ%s\n",q->op1);

                                                                                               fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                                               fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                               fprintf(code_objet,"JL ETIQ%s\n",q->op1);
                                                                                               }
                                                                                              else{if(recherche(q->res)!=NULL)
                                                             	                                      {printf("ETIQ%d: POP AX\n",q->num);
                                                                                                     printf("CMP AX,%s\n",q->res);
                                                                                                     printf("JL ETIQ%s\n",q->op1);

                                                                                                     fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                                                     fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                     fprintf(code_objet,"JL ETIQ%s\n",q->op1);
                                                                                                    }
                                                                                                   else{if(q->res[0]=='T')
                                                                                                         {printf("ETIQ%d: POP BX\n",q->num);
                                                                                                          printf("POP AX\n");	
                                                                                                          printf("CMP AX,BX\n");
                                                                                                          printf("JL ETIQ%s\n",q->op1);

                                                                                                          fprintf(code_objet,"ETIQ%d: POP BX\n",q->num);
                                                                                                          fprintf(code_objet,"POP AX\n"); 
                                                                                                          fprintf(code_objet,"CMP AX,BX\n");
                                                                                                          fprintf(code_objet,"JL ETIQ%s\n",q->op1);
                                                                                                         }
                                                                                                        else{printf("ETIQ%d: POP AX\n",q->num);
                                                                                                             printf("CMP AX,%s\n",q->res);
                                                                                                             printf("JL ETIQ%s\n",q->op1);

                                                                                                             fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);
                                                                                                             fprintf(code_objet,"CMP AX,%s\n",q->res);
                                                                                                             fprintf(code_objet,"JL ETIQ%s\n",q->op1);
                                                                                                             }
                                                                                                        }
                                                                                                   }
                                                                                           }
                                                                         else{if(q->res[strlen(q->res)-1]==']')
                                                                                              {printf("ETIQ%d: MOV AX,%s\n",q->num,q->res);
                                                                                               printf("CMP %s,AX\n",q->op2);
                                                                                               printf("JL ETIQ%s\n",q->op1);

                                                                                               fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->res);
                                                                                               fprintf(code_objet,"CMP %s,AX\n",q->op2);
                                                                                               fprintf(code_objet,"JL ETIQ%s\n",q->op1);
                                                                                             }
                                                                                              else{if(recherche(q->res)!=NULL)
                                                             	                                      {printf("ETIQ%d: MOV AX,%s\n",q->num,q->res);
                                                                                                     printf("CMP %s,AX\n",q->op2);
                                                                                                     printf("JL ETIQ%s\n",q->op1);

                                                                                                     fprintf(code_objet,"ETIQ%d: MOV AX,%s\n",q->num,q->res);
                                                                                                     fprintf(code_objet,"CMP %s,AX\n",q->op2);
                                                                                                     fprintf(code_objet,"JL ETIQ%s\n",q->op1);
                                                                                                   }
                                                                                                    else{if(q->res[0]=='T')
                                                                                                          {printf("ETIQ%d: POP AX\n",q->num);                                                                                                          	
                                                                                                           printf("CMP %s,AX\n",q->op2);
                                                                                                           printf("JL ETIQ%s\n",q->op1);

                                                                                                           fprintf(code_objet,"ETIQ%d: POP AX\n",q->num);                                                                                                            
                                                                                                           fprintf(code_objet,"CMP %s,AX\n",q->op2);
                                                                                                           fprintf(code_objet,"JL ETIQ%s\n",q->op1);
                                                                                                           }
                                                                                                           else{printf("ETIQ%d: CMP %s,%s\n",q->num,q->op2,q->res);
                                                                                                                printf("JL ETIQ%s\n",q->op1);

                                                                                                                fprintf(code_objet,"ETIQ%d: CMP %s,%s\n",q->num,q->op2,q->res);
                                                                                                                fprintf(code_objet,"JL ETIQ%s\n",q->op1);
                                                                                                               }
                                                                                                         }
                                                                                                   }
                                                                              }
                                                            	      }
                                                                }
                                                         }
                                                         
                                }
                                                          
                               
 if(strcmp(q->op,"BR")==0){printf("ETIQ%d: JMP ETIQ%s\n",q->num,q->op1);fprintf(code_objet,"ETIQ%d: JMP ETIQ%s\n",q->num,q->op1);} 
	q=q->svt;}
	printf("CODE ENDS\n");
	printf("END MAIN\n");
  fprintf(code_objet,"CODE ENDS\n");
  fprintf(code_objet,"END MAIN\n");
  fclose(code_objet);
}
