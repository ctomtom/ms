import jade.util.leap.Serializable;

public class Produit implements Serializable {
   private double prix;
   private double prixReserve;
   private String designation;
   public int val=0;
   public Produit(double prix,String designation,int val,double prixReserve) {
	   this.prix=prix;
	   this.designation=designation;
	   this.prixReserve = prixReserve;
	   this.val=val;
   }
   
public Produit() {
	// TODO Auto-generated constructor stub
}

public double getPrixReserve() {
	return prixReserve;
}

public void setPrixReserve(double prixMaxAgent) {
	this.prixReserve = prixMaxAgent;
}

public double getPrix() {
	return prix;
}
public void setPrix(double prix) {
	this.prix = prix;
}
public String getDesignation() {
	return designation;
}
public void setDesignation(String designation) {
	this.designation = designation;
}

@Override
public String toString() {
	return "Produit [prix=" + prix + ", prixReserve=" + prixReserve + ", designation=" + designation + ", val=" + val
			+ "]";
}
   
}

