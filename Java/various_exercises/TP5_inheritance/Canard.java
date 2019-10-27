class Canard extends Animal {
	private String couleurPlume;
	private static final double poidsGraines = 1;

	private static final Regime canardRegime = new Regime("graine", 0.8);

	public String getCouleurPlume(){return couleurPlume;}

	public Canard(String nom, int poids, String couleurPlume){
		super(nom,poids,canardRegime);
		this.couleurPlume = couleurPlume;
	}
	public Canard(String nom){
		this(nom, 4, "noir tuxien cancane");
	}

	@Override
	public double getCoutNourriture(){
		return poidsGraines * getRegime().getPrix();
	}

	@Override
	public void crier(){
		super.crier();
		System.out.println("ce canard de " + getPoids() + "kg aux belles plumes " + couleurPlume + " !");
	}

	@Override
	public String toString(){
		return super.toString() + " qui est un canard avec des plumes " + couleurPlume;
	}
	
}
