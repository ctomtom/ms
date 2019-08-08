package application;
import java.util.ArrayList;
import java.util.Stack;
public class Noeud {
    private int depth;
    private int value; 
    Noeud pere;
    ArrayList<Noeud>chaine=new ArrayList<Noeud>() ;
   
    //constructeur 

    public ArrayList<Noeud> getChaine() {
		return chaine;
	}

	   public void AjouterListe(Noeud n){
	       int i;
	      if(!n.getChaine().isEmpty()){
	          for(i=0;i<n.getChaine().size();i++)
	          { chaine.add(n.getChaine().get(i));}
	      }
	      chaine.add(n);
	   }
	      

	public Noeud(int value , int deapth) {
      
        this.pere = null ;
        this.value = value;
        this.depth=deapth;        
    }
    
    
    public Noeud() {
		// TODO Auto-generated constructor stub
	}

	public int getDepth() {
        return depth;
    }

    public int getValue() {
        return value;
    }

    public void setDepth(int depth) {
        this.depth = depth;
    }

    
    public void setValue(int value) {
        this.value = value;
    }
  
      public  boolean contain(ArrayList<Integer> liste, int j)
      {for(int i=0;i<liste.size();i++)
        {
      	if(liste.get(i)==j) {return true;}
          
        }
      	return false;
      }
      
      public boolean containnoeud(ArrayList<Noeud> l)
      {
    	  for(int i=0;i<l.size();i++)
    	  {if(l.get(i).getValue()==this.getValue()) {return true;}}
    	  return false;
      }
    
      public int sat(int m[][],ArrayList<Noeud> n,int col) {
  		int s=0;
  		ArrayList<Integer> clauses=new ArrayList<Integer>();
  		ArrayList<Integer> sol=new ArrayList<Integer>();
  		int k;
  		  //en parcourant toutes les clauses
  		  //verifier l'existence du littéral dans la clause et incrementer fitness de la solution
  		  //s'il y existe 
  		  //et sauvegarder les clauses satisfaites
  		//parcourir les noeud
  				for(int i=0;i<n.size();i++)
  				  {//parcourir les clauses
  					for(int j=0;j<m.length;j++)
  				     {if(contain(clauses,j)==false)
  				       {k=0;
  					    while(k<col&&m[j][k]!=n.get(i).getValue())
  					     {k++;}
  					  
  				        if(k<col&&!contain(sol,-n.get(i).getValue())){clauses.add(j);s=s+1;sol.add(n.get(i).getValue());}
  				       }
  		             }
  	               }
  				return s;
  				}

      
  	}
