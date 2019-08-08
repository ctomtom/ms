import java.io.IOException;
import java.util.Scanner;

import jade.core.AID;
import jade.core.Agent;
import jade.core.behaviours.CyclicBehaviour;
import jade.core.behaviours.OneShotBehaviour;
import jade.core.behaviours.SequentialBehaviour;
import jade.core.behaviours.TickerBehaviour;
import jade.lang.acl.ACLMessage;
import jade.lang.acl.UnreadableException;
import java.awt.TextArea;

public class Acheteur extends Agent {
	public  static int val;
	double Mise;
	 double PrixMax;
	 Produit E;
	 V1 Vendeur;
	 int cont;
	 TextArea text;
	 Scanner in = new Scanner(System.in);
  
  public Acheteur(double prixMax,double mise ) {
		 this.Mise=mise;
		 this.PrixMax=prixMax;
  }
  public Acheteur( ) {
	
}
	
	public double getMise() {
		return Mise;
	}

	public void setMise(double mise) {
		Mise = mise;
	}

	public double getPrixMax() {
		return PrixMax;
	}

	public void setPrixMax(double prixMax) {
		PrixMax = prixMax;
	}

	
	public void setProuit(Produit E) {
		this.E=E;
		
	}
	
   protected void setup() {

	   //doActivate();
	    Object[]args=getArguments();
	   if(args!=null) {
		  
		   PrixMax=(double) args[0];
		 
		   Mise=(double) args[1];
		   
		   text=(TextArea) args[2];
		   
		   
	    }
	   
	   addBehaviour(new CyclicBehaviour(this){
		   public void action() {
			   ACLMessage m;
			  
			   double PrixNew;

			   m=blockingReceive();
			
			   if(m!=null){				 
				   
				   try {
					  Object []o=(Object[])m.getContentObject();
					  E=(Produit)o[0];
					  cont=(int)o[1];
					  if(cont==2) {
						//delete all agents
						  System.out.println(getLocalName()+"is deleted");
						  doDelete();
					  }
					  else
					 
					  if(cont==0) {
					  
					  PrixNew=E.getPrix()+Mise;
					  	
					
					  ACLMessage reply =m.createReply();
					  reply.setPerformative(ACLMessage.INFORM);
					 
					  try {
						   if(E.getPrix()>PrixMax ||PrixNew>PrixMax) {
							   System.out.println("Je suis "+getLocalName()+",j'ai reçu le produit "+E.getDesignation()+" avec le prix "+E.getPrix());
								  text.appendText("\nJe suis "+getLocalName()+",j'ai reçu le produit "+E.getDesignation()+" avec le prix "+E.getPrix());
								  
						    	   o[0]=E;
						    	   o[1]=-1;
						    	   reply.setContentObject(o);
							       reply.setLanguage("JavaSerialization");
								   System.out.println(getLocalName()+" veut quitter car son prix seuil a été dépassé.");
								   send (reply);
						   }
						   else if(PrixNew<=PrixMax){
					    	  System.out.println("je suis "+getLocalName()+" j'ai reçu le produit "+E.getDesignation()+" avec le prix "+E.getPrix()+" et je propose le nouveau prix= "+PrixNew);
							  text.appendText("\nje suis "+getLocalName()+" j'ai reçu le produit "+E.getDesignation()+" avec le prix "+E.getPrix()+" et je propose le nouveau prix= "+PrixNew);
									
					    	   E.setPrix(PrixNew);
					    	   o[0]=E;
					    	   o[1]=0;
					    	 
					    	   reply.setContentObject(o);
						       reply.setLanguage("JavaSerialization");
					           send(reply);}    
					       
					  }catch(IOException e2) { 
						  e2.printStackTrace(); 
						  } 
					  }else  if(cont==1){
						  
						  text.appendText("\n****"+getLocalName()+" a quitté l'enchère car son prix seuil a été dépassé****");
						  System.out.println(getLocalName()+" a quitté l'enchère car son prix seuil a été dépassé");doDelete();  }
					  
					  } catch(UnreadableException e) {
							   System.out.println(getLocalName()+"catched exception"+e.getMessage());
						  }
				         
					     }block();
				        
			
			   } 

	   });
	
	   
}


}
