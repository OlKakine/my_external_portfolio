class Regime{
	private String nom;
	private double prix;

	public String getNom(){return nom;}
	public double getPrix(){return prix;}

	public Regime(String nom, double prix){
		this.nom = nom;
		this.prix = prix;
	}

	@Override
	public String toString(){
		return "Regime: " + nom + " coutant " + prix + " au kilo.";
	}
}
