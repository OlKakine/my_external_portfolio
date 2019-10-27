abstract class Animal {
	private String nom;
	private int poids;
	private Regime regime;

	public String getNom(){return nom;}
	public int getPoids(){return poids;}

	public Regime getRegime(){return regime;}

	public Animal(String nom, int poids, Regime regime){
		this.nom = nom;
		this.poids = poids;
		this.regime = regime;		
	}

	public abstract double getCoutNourriture();

	public void crier(){System.out.print(nom + " crie...");}

	@Override
	public String toString(){
		return nom + " un animal de " + poids + "kg";
	}
}
