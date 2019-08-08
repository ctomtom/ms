import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

import jade.core.AID;
import jade.core.Agent;
import jade.core.behaviours.CyclicBehaviour;

import jade.lang.acl.ACLMessage;
import jade.lang.acl.UnreadableException;
import java.awt.TextArea;
public class V1 extends Agent {

 //
	static int x=1;
   Produit E=new Produit();
   ACLMessage m;
   static long start; long time;
   
   static double max=0;
    static int nbrAcheteur ,n;
    
    Object []o=new Object[2];
    int cont;
    AID LastAidMax;
    TextArea text;
     
  //les getters et les setters  
   public int getNbrAcheteur() {
	return nbrAcheteur;
}
  public  void setNbrAcheteur(int nbrAcheteur) {
	this.nbrAcheteur = nbrAcheteur;
}
  
  //liste des AID des acheteurs
  ArrayList<AID> BuyersAgents=new ArrayList<AID>(); 
  ArrayList<AID> ListAgentQuitter=new ArrayList<AID>(); 
  ArrayList<AID> ListAgentQuitterCopie=new ArrayList<AID>(); 
   AID agentID;
   //liste des acheteurs 
   ArrayList<Acheteur>ListeAcheteurs;
  
   public V1() {  
   }
   
   protected void setup() { 
    
	   Object[]args=getArguments();
	   if(args!=null) {
		   E.setPrix(Double.valueOf((String)(args[0])).doubleValue());
		 
		   E.setPrixReserve(Double.valueOf((String)(args[1])).doubleValue());
		   
		   
		    time=(long) args[5];
		    text=(TextArea)args[3];
		   nbrAcheteur=(int)args[2];
		    E.setDesignation((String) args[4]);
		   o[0]=E;
		   o[1]=0;
		   
		// envoi du prix init aux acheteurs
		   m=new ACLMessage(ACLMessage.INFORM);
		
		   for(int i=1; i<=nbrAcheteur; i++) {
			  BuyersAgents.add(new AID("Acheteur"+(i),AID.ISLOCALNAME));
			 
			  m.addReceiver(BuyersAgents.get(i-1));
			  
			  System.out.println("agent ="+BuyersAgents.get(i-1).getLocalName());
			  
	         }
		   try {
				 m.setContentObject(o);
				 m.setLanguage("JavaSerialization");
				   //  System.out.println("Message=="+m.getContent());
				      send(m);
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		   
	   }
	   
	   start=System.currentTimeMillis();
	    
	   addBehaviour(new CyclicBehaviour(this){
		   public void action() {
			   ACLMessage m2 = null;	  	
				
		//recevoir l'object E
	
			   System.out.println("start="+(long)start);
			   
		
			   n=BuyersAgents.size();
		  
		 while(n!=0){
		   m2=blockingReceive(); 
		    n--;
		    while(m2==null) {
		    	try {
					wait();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
		    }
		   try {
			   //recuperer le produit depuis l'acheteur
			  o=(Object[]) m2.getContentObject();
			  
			  E=(Produit)o[0];
			
			  cont=(int)o[1];
			  System.out.println(cont);
			  if(cont==0) {
			 
			  if(E.getPrix()>max) {max=E.getPrix(); LastAidMax=m2.getSender();			 
							
			  }
			 
			  }
			  else  if(cont==-1){
				 					
				  agentID=m2.getSender();
				  ListAgentQuitter.add(agentID);			  
			  }
			  
		   }
	      catch(UnreadableException e) {
				    System.err.println(getLocalName()+"catched exception"+e.getMessage());
		  }  
		 
		   }block();
		 
		 text.appendText("\n--------Je suis "+getLocalName()+" j'annonce le plus grand prix reçu ="+max+"---------");
		   System.out.println("max final= "+max);
		     //tester si il y'a des agents qui veulent quitter 	     
		    
		     int i=0;
		     ACLMessage mAgentDelete=new ACLMessage(ACLMessage.INFORM);
				
		     while((ListAgentQuitter.isEmpty()==false) && (i<ListAgentQuitter.size()) ){
		    	 o[1]=1;
		    	 o[0]=null;
		    	 mAgentDelete.addReceiver(ListAgentQuitter.get(i));
		    	 try {
		    		 mAgentDelete.setContentObject(o);
		    		 mAgentDelete.setLanguage("JavaSerialization");
					send(mAgentDelete);
					
				     
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
		    	
		    	int j=0;
		    	while (!BuyersAgents.isEmpty() && j<BuyersAgents.size()) {
		    		AID A=BuyersAgents.get(j);
		    		if((!ListAgentQuitter.isEmpty())&&(!BuyersAgents.isEmpty())&& A.equals(ListAgentQuitter.get((i))) )
		    		{
		    			 m.removeReceiver(ListAgentQuitter.get(i));
				    	 ListAgentQuitterCopie.add(ListAgentQuitter.get(i));
				    	 ListAgentQuitter.remove(i);
				    	BuyersAgents.remove(A);
				    
		    		}
		    		j++;
		    		 
		    	}
		    	
		    	 i++;
		     }
		
		     long duree=System.currentTimeMillis()-start;
		     System.out.println("duree="+duree);
		     if(BuyersAgents.size()==1) {
		    	   o[0]=null;
	               o[1]=-1;
	               try {
	               	  
	               		m.setContentObject(o);
	               		m.setLanguage("JavaSerialization");
	               		send(m);
	               	} catch (IOException e1) {
	               		// TODO Auto-generated catch block
	               		e1.printStackTrace();
	               	}  
	               
		    	 
		     }else 
		     if((!BuyersAgents.isEmpty()) &&(duree<time)) {
		   
              E.setPrix(max);   
              o[0]=E;
              o[1]=0;
       	    try {
      
       		m.setContentObject(o);
       		m.setLanguage("JavaSerialization");
       		send(m);
       	} catch (IOException e1) {
       		// TODO Auto-generated catch block
       		e1.printStackTrace();
       	}  
		     }
		
		     //si tous les acheteurs s'arretent
		     else { 
		    	 
		    	 //arreter l'enchere
		    	 //si le dernier prix reçu par le vendeur > prix de reserve, le produit sera vendu 
		    	  int j=0;
		    	  AID A = null;

		    	   if(duree>=time) {
		    		   //supprimer les achteurs 
		    		   System.out.println("Le temps de l'enchère  est terminé.");
		    		   text.appendText("\n----------------Le temps de l'enchère  est terminé.-------------------");
		    		   o[0]=null;
		               o[1]=2;
		               try {
		               	   
		               		m.setContentObject(o);
		               		m.setLanguage("JavaSerialization");
		               		send(m);
		               	} catch (IOException e1) {
		               		// TODO Auto-generated catch block
		               		e1.printStackTrace();
		               	}  
		               
		    	   }    	   
		    	   
		    	   
		    	
		    	   if(max>=E.getPrixReserve()) {
		    		   text.appendText("\n---------------Le gagnant est : "+LastAidMax.getLocalName()+" avec un prix de "+max+"-----------");
			    	   System.out.println("le gagnant est "+LastAidMax.getLocalName()+" avec un prix de "+max);}
	    		   else {
	    			   text.appendText("\n-----------------Pas de gagnant pour cette enchère!---------------");
	    			     System.out.println("Pas de gagnant pour cette enchère!");} 
		    	 
		    	   doDelete();
		    	
		    	 
		     }	   
	 
		   }
	    
	   });
	  
   }
}