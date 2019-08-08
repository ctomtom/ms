package application;
import java.util.ArrayList;

public class Solution {
private int fitness;
private ArrayList<Integer> bits;
public Solution(int fitness, ArrayList<Integer> bits) {
	super();
	this.fitness = fitness;
	this.bits = bits;
}
public Solution() {
	// TODO Auto-generated constructor stub
}
public int getFitness() {
	return fitness;
}
public void setFitness(int fitness) {
	this.fitness = fitness;
}
public ArrayList<Integer> getBits() {
	return bits;
}
public void setBits(ArrayList<Integer> bits) {
	this.bits = bits;
}

public void afficher() {
	for(int i=0;i<this.bits.size();i++)
	{System.out.println(bits.get(i));}
}


public static boolean contain(ArrayList<Integer> liste, int j)
{for(int i=0;i<liste.size();i++)
  {
	if(liste.get(i)==j) {return true;}
    
  }
	return false;
}
//fonction qui calcule le fitness de la solution
	
public void fitness(int m[][]) {
		int b;int s=0;
		ArrayList<Integer> clauses=new ArrayList<Integer>();
		//parcourir les bits
		for(int i=0;i<this.getBits().size();i++)
		 {if(this.getBits().get(i)==0) {b=-(i+1);}
			else {b=i+1;}
		  //en parcourant toutes les clauses
		  //verifier l'existence du littéral dans la clause et incrementer fitness de la solution
		  //s'il y existe 
		  //et sauvegarder les clauses satisfaites
				for(int j=0;j<m.length;j++)
				  {if(contain(clauses,j)==false)
				    {
					  if(m[j][0]==b||m[j][1]==b||m[j][2]==b) 
					  {
					  clauses.add(j);s=s+1;
					  this.setFitness(s);}
				     }
		          }
	      }
	
	}


}
