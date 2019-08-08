package application;
import java.io.BufferedReader;

import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Random;
import java.util.Stack;

public class App {  int  col,ligne,m[][];

public App() {};
public int getLigne() {
	return ligne;
}


public void setLigne(int ligne) {
	this.ligne = ligne;
}


	public int getCol() {
	return col;
}


public void setCol(int col) {
	this.col = col;
}



	public  void remplir (String filename) {
		m=new int[ligne][col];
		String clauses[][]=new String[ligne][col];
		
	    int i=0,j;
	
		BufferedReader br = null;
		FileReader fr = null;
        String line;
        String[] p;
		try {
			fr = new FileReader(filename);
			br = new BufferedReader(fr);
			line=br.readLine();
			while ((line =br.readLine()) != null&&i<ligne) 
			   {if(!line.contains("c")&&!line.contains("p"))
				  {
				   line=line.substring(0, line.length()-2);
					p=line.split(" ");
				     for(j=0;j<=col-1;j++) {				
				    	                {clauses[i]=p;}
					                   }	
				     i++;
			       }
			   }

		     } catch (IOException e) {

			e.printStackTrace();

		      } finally {

     			try {

				   if (br != null)
					br.close();

				   if (fr != null)
					fr.close();

			        } catch (IOException ex) {

				                ex.printStackTrace();

			                               }
		                }
		for(i=0;i<ligne;i++)
		{for(j=0;j<col;j++)
		   {
			try{m[i][j]=Integer.parseInt(clauses[i][j]);}
		     catch(NumberFormatException ex){ex.printStackTrace();}
				
				}
		}
		
	}
	
	
	 public ArrayList<Noeud> bfs(int plg,int t){
		 long starttime;
	        ArrayList<Noeud> open = new ArrayList<Noeud>() ;
	        ArrayList<Noeud> solution = new ArrayList<Noeud>() ;
	        Noeud racine=new Noeud(0,0);
	        Noeud courant = racine ; 
	        Random rand = new Random();
	        int prof=0;
	        int value=0 ;       
	        int numclssat = 0 ; 
	        open.add(courant); 
	          
	        starttime=System.currentTimeMillis();
	        while(!open.isEmpty() && numclssat <ligne &&System.currentTimeMillis()-starttime<t){
	        	
	        	System.out.println("Open : "+courant.getValue()+"\n");
	            courant = open.get(0);
	            System.out.println("La valeur du noeud courant est "+courant.getValue()+"\n");
	              open.remove(0);         	 
	                 
	              numclssat= courant.sat(m, courant.getChaine(), col);           
	             System.out.print("Solution:\n ");
	            for(int k=0;k<courant.getChaine().size();k++){	            	
	                         System.out.print(courant.getChaine().get(k).getValue()+" ");
	                         	                     }	            
	            System.out.print(courant.getValue());            
	         
	            System.out.println(" Le nombre de clauses satisfaites: " + numclssat+"\n");
	            
	         
	                    value = 0;prof=prof+1;
	              while(value==0||(new Noeud(-value,prof).containnoeud(courant.chaine))==true||courant.getValue()==value||
                  		(new Noeud(	value,prof).containnoeud(courant.chaine))==true||courant.getValue()==-value) 
	              {value = rand.nextInt(plg + 1 + plg) - plg;}		
	                    Noeud n = new Noeud(value,prof);
	                    n.AjouterListe(courant);
	                    Noeud n2 = new Noeud(-value,prof);
	                    n2.AjouterListe(courant);
	                  
	                    { open.add(n); }
	               
	                    { open.add(n2);}
	                    solution=courant.getChaine();solution.add(courant);
	                          
	             
	              }
	     
	       return solution;
	        }         	                    
	      
	 public  ArrayList<Noeud> dfs(int plg,int t){
		 long starttime=System.currentTimeMillis();
	       Stack<Noeud> open = new Stack<Noeud>() ;
	      
	        Noeud racine=new Noeud(0,0);
	        ArrayList<Noeud> solution = new ArrayList<Noeud>() ;
	        Noeud courant = racine; 
	        Random rand = new Random();
	        int value;       
	        int profmax = plg;
	        int prof =0;
	        int numclssat = 0 ; 
	        open.push(courant); 
	        courant.setDepth(prof);
	        
	        while(!open.isEmpty() && numclssat< m.length&&System.currentTimeMillis()-starttime<t){
	            courant = open.pop();   	            
	              numclssat=courant.sat(m, courant.getChaine(), col); 
	              System.out.println("La valeur du noeud courant est "+courant.getValue()+"\n"
	              		+ " le nombre de clauses satisfaites est "+numclssat+"\n");
	              
	             System.out.println("Solution: \n");
	            
	             for(int i=0;i<courant.getChaine().size();i++)
	             { System.out.print(courant.getChaine().get(i).getValue()+" ");}
	             System.out.print(courant.getValue());
	             System.out.println();
	              
	              if(courant.getDepth() < profmax &&  numclssat< m.length ){
	                    prof=courant.getDepth()+1 ; 
	                    value=0;
	                    while(value==0||(new Noeud(-value,prof).containnoeud(courant.chaine))==true||courant.getValue()==value||
	                    		(new Noeud(	value,prof).containnoeud(courant.chaine))==true||courant.getValue()==-value)
	                    {value = rand.nextInt(plg + 1 + plg) - plg;}	
	                    
	                    Noeud n = new Noeud(value,prof);	  
	                    n.AjouterListe(courant);
	                   
	                    Noeud n2 = new Noeud(-value,prof);	
	                    n2.AjouterListe(courant);
	              
	                         open.push(n2); 
	                  
	                         open.push(n);                           
	                  
	                     solution=courant.getChaine();solution.add(courant);	                 
	                   	              }	          
	              }  
	        return solution;
	    }
	 
	public static Comparator<Solution> fit = new Comparator<Solution>() {
     
        public int compare(Solution o1, Solution o2) {
            return o1.getFitness() - o2.getFitness();
        }};
        
	
	
	//fonction qui retourne 1 si la solution satisfait toutes les clauses, 0 sinon
	public  int evaluer(Solution sol) {
		if(sol.getFitness()==ligne) {return 1;}
		else {return 0;}
	}
	
	public int evaluerpart(Particle p ) {
		if(p.getFitness()==ligne) {return 1;}
		else {return 0;}
	}
	
	//fonction qui initialise une population de solution
	public static ArrayList<Solution> population(int popsize,int plg)
	{Solution solution;
	ArrayList<Solution> population=new ArrayList<Solution>();
	int r; Random rand=new Random();
	
		for(int i=0;i<popsize;i++)
		 {//construire une solution
			solution = new Solution();
			ArrayList<Integer> bits=new ArrayList<Integer>();
		  for(int j=0;j<plg;j++)
		  {	  
		  r=rand.nextInt(2);
		   bits.add(r);
		  }
		  solution.setBits(bits);
		  population.add(solution);
		}
		return population;
	}
	
	//fonction qui initialise un groupe de particules(solutions)
	public static ArrayList <Particle> swarm(int swarmsize,int plg)
	{
		Particle particle;
		ArrayList<Particle> swarm=new ArrayList<Particle>();
		int r; Random rand=new Random();ArrayList<Integer> bits;
		 //remplir swarm
	    for(int i=0;i<swarmsize;i++)
		  {//construire une solution
				particle = new Particle();
				bits=new ArrayList<Integer>();
			 //init la position de la particule 
				for(int j=0;j<plg;j++)
			   {	  
			    r=rand.nextInt(2);bits.add(r);			    		  
			   }
				particle.setPosition(bits);	
				
				//init la vitesse de la particule				  
			    r=rand.nextInt(plg);
			    particle.setVelocity(r);		  
			   
			 
			  swarm.add(particle);
			}
			return swarm;
	}
	
	public Solution algogenetique(int plg) {
	    int r, ind,iter;
	    int maxiter=10;double rc=0.1, mr=0.3; int popsize=50;
	    int optimale=0;
	   
		ArrayList <Solution>population=new ArrayList<Solution>();
		Random rand = new Random();
		
		//construire une population de solution
		population=population(popsize,plg);
		
		//evaluation de la population
		int i=0;
		while( i<population.size()&&optimale==0)
		{population.get(i).fitness(m);
		 optimale=evaluer(population.get(i));
		 i++;
		}
		 /*System.out.println("La population initiale: \n");
		 for(int m=0;m<population.size();m++)
		 {
			 System.out.println("L'individu:");
		 population.get(m).afficher();}*/
		 
		 
		//Croisement et mutation
		 iter=1; int bit_individu3;
		Solution individu1=new Solution();
		Solution individu2=new Solution();
		ArrayList <Integer>intermediaire=new ArrayList<Integer>();
		ArrayList <Integer>intermediaire2=new ArrayList<Integer>();
		while(iter<=maxiter&&optimale==0)
		{  //croisement
			
		   for(int j=1;j<=popsize*rc;j++)
		    {r=rand.nextInt(2);
			 individu1=population.get(r);
			 r=rand.nextInt(2);
			 individu2=population.get(r);
			 r=rand.nextInt(plg);
		 
			/* 
			 System.out.println("le premier indiv: \n");
			 individu1.afficher();
			 System.out.println("Le deuxieme individu: \n");
			 individu2.afficher();*/		
			 			 
			 for(int k=0;k<=r;k++)
			 {
				 intermediaire.add(k, individu1.getBits().get(k));
			 }
			 for(int k=r+1;k<plg;k++) 
			 {
				 intermediaire.add(k, individu2.getBits().get(k));
			 }
			 			 
			 population.add(new Solution(0,intermediaire));
			 
			 for(int k=0;k<=r;k++)
			 {
				 intermediaire2.add(k, individu2.getBits().get(k));
			 }
			 for(int k=r+1;k<plg;k++) 
			 {
				 intermediaire2.add(k, individu1.getBits().get(k));
			 }
			
			 population.add(new Solution(0,intermediaire2));
		    }
		   //mutation
		 
		   for(int j=1;j<=popsize*mr;j++)
		    {r=rand.nextInt(population.size()-1);
			 bit_individu3=rand.nextInt(plg);
		     if(population.get(r).getBits().get(bit_individu3)==0) 
		      {population.get(r).getBits().set(bit_individu3,1);}
		     else {population.get(r).getBits().set(bit_individu3,0);}
		    }
		    
		   //evaluation de la nouvelle population		    
		    
		   for(i=0;i<population.size();i++)
		   {population.get(i).fitness(m);			   
		   }
		   
		   //selection en éliminant les moins bonnes
		   Collections.sort(population, fit);            	
           Collections.reverse(population);
           
		  /*for(i=0;i<population.size();i++)
		   {System.out.println(population.get(i).getFitness());}	*/   
	           
		   //suppression des moins bons
		  ind=population.size()-1;
		  while (!population.isEmpty()&&ind!=popsize-1)
		  {

			  population.remove(ind);ind=ind-1;

		  }
		   optimale=evaluer(population.get(0));
		   iter++;
		
		   //System.out.println("La meilleure solution pour mr="+mr+ " a le fitness: "+population.get(0).getFitness()+"\n");
		}
		/*System.out.println("les plus bonnes:");
		for(i=0;i<population.size();i++)
		   {System.out.println(population.get(i).getFitness());}*/
		
		System.out.print("La meilleure fitness obtenue est:"+population.get(0).getFitness()+"\n");
		/*for(int x=0;x<population.get(0).getBits().size();x++)
		{System.out.print(population.get(0).getBits().get(x)+" ");}
		System.out.println();*/
		return population.get(0);
	}
	
	public Particle algopso(int plg) {
		ArrayList<Integer> gbest; int maxiter=70;int swarmsize=70; double c1=0.4,c2=2,w=0.2,r2=0.6,r1=0.6;
		
		//Random rand=new Random();		
		ArrayList <Particle>swarm=new ArrayList<Particle>();
		int optimale=0;
	    ArrayList<Integer> xi;
	    
		//intialiser swarm 
		swarm=swarm(swarmsize,plg);
		
		//pbesti=xi		
		for(int i=0;i<swarmsize;i++)
	     {xi=swarm.get(i).getPosition();
		  swarm.get(i).setPbest(xi);
		  }
		
		//evaluer
		int i=0;
		while( i<swarm.size())
		{swarm.get(i).fitness(m);
		if(evaluerpart(swarm.get(i))==1) {optimale=1;};
		 i++;
		}		
		
		//gbest
	     int j=0; 
		for(i=1;i<swarmsize;i++)
		{
			if(swarm.get(i).getFitness()>swarm.get(j).getFitness()) {j=i;}
		}
		gbest=swarm.get(j).getPbest();		
		
		int iter=1;Particle p;
		while(iter<=maxiter&&optimale==0)
		{
		  
			for(i=0;i<swarmsize;i++)
			{   //updating v & pos
				p=swarm.get(i);
				p.updatevelocity(w, c1, c2, r1, r2, gbest);
				p.updateposition();					
				p.fitness(m);
				swarm.set(i, p);				
			}			
			//màj gbest
			
			for(i=0;i<swarmsize;i++)
			{
				if(swarm.get(i).getFitness()>swarm.get(j).getFitness()) {j=i;}
			}
			gbest=swarm.get(j).getPbest();
			optimale=evaluerpart(swarm.get(j));
			iter++;
		}
		System.out.println("The best fitness is: "+swarm.get(j).getFitness());
		return swarm.get(j);
	}


}
