package application;
import java.util.ArrayList;
import java.util.Random;

public class Particle {
	private ArrayList <Integer>position;
	private Integer velocity;
	private ArrayList<Integer> pbest;
	private int fitness;
	
	
	public Particle(ArrayList<Integer> position, Integer velocity, ArrayList<Integer> pbest, int fit) {
		super();
		this.position = position;
		this.velocity = velocity;
		this.pbest = pbest;
		this.fitness = fit;
	}

	public ArrayList<Integer> getPosition() {
		return position;
	}

	public void setPosition(ArrayList<Integer> position) {
		this.position = position;
	}

	public Integer getVelocity() {
		return velocity;
	}

	public void setVelocity(Integer velocity) {
		this.velocity = velocity;
	}

	public ArrayList<Integer> getPbest() {
		return pbest;
	}

	public void setPbest(ArrayList<Integer> pbest) {
		this.pbest = pbest;
	}

	public static boolean contain(ArrayList<Integer> liste, int j)
	{for(int i=0;i<liste.size();i++)
	  {
		if(liste.get(i)==j) {return true;}
	    
	  }
		return false;
	}
	
	public void fitness(int m[][]) {
		int b;int s=0;
		ArrayList<Integer> clauses=new ArrayList<Integer>();
		//parcourir les bits
		for(int i=0;i<this.getPbest().size();i++)
		 {if(this.getPbest().get(i)==0) {b=-(i+1);}
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
public Particle() {}
	public int getFitness() {
		return fitness;
	}

	public void setFitness(int fit) {
		this.fitness = fit;
	}
	
public void updateposition() {
Random rand=new Random();
int r;int b;
	for(int i=1;i<=velocity;i++)
	{r=rand.nextInt(position.size());
	b=position.get(r);
	position.set(r, 1-b);}
}

public void updatevelocity(double w,double c1,double c2,double r1,double r2,ArrayList<Integer> gbest) {
	/*ArrayList<Integer> pos;
	ArrayList<Integer> distance;*/
	Integer v = this.getVelocity();	 
	 
	this.setVelocity((int) Math.round(w*v+c1*r1*distance(pbest,position)+c2*r2*distance(gbest,position)));
}
public int distance(ArrayList<Integer> p1,ArrayList<Integer> p2) {
	int d=0;
	for(int i=0;i<pbest.size();i++)
	{
		if(p1.get(i)!=p2.get(i)) {d=d+1;}
	}
	return d;
}
}