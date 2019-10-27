public class TestZoo{
	public static void main(String[] args){
		Zoo ensimag = new Zoo("Ensimag");

		Canard catherine = new Canard("Catherine");
		System.out.println(catherine.getCoutNourriture());

		Animal julie = new Vache("Julie");

		ensimag.ajouteAnimal(catherine);
		ensimag.ajouteAnimal(julie);
		// ensimag.ajouteAnimal(new Animal("Sahar"));
		// ensimag.ajouteAnimal(new Animal("Benoit"));
		// ensimag.ajouteAnimal(new Animal("Nicolas"));
		// ensimag.ajouteAnimal(new Animal("Sebastien"));
		// ensimag.ajouteAnimal(new Animal("Sylvain"));

		ensimag.crier();
		System.out.println(ensimag);
		System.out.println(ensimag.getCoutGlobalNourriture());
	}
}
