/**
 * Created by checchio on 10/14/19.
 */
class Vache extends Animal{
    private int nbTaches;
    private static double vachePrixKiloRegime = 0.2;
    private static final Regime vacheRegime = new Regime("herbe", vachePrixKiloRegime);

    public int getNbTaches(){return nbTaches;}

    public Vache(String nom, int poids, int nbTaches){
        super(nom,poids, vacheRegime);
        this.nbTaches = nbTaches;
    }
    public Vache(String nom){
        this(nom, 120, 11);
    }

    @Override
    public double getCoutNourriture(){
        return 0.1 * getPoids() * vachePrixKiloRegime;
    }

    @Override
    public void crier(){
        super.crier();
        System.out.println("cette vache de " + getPoids() + "kg avec ses belles " + nbTaches + " taches !");
    }

    @Override
    public String toString(){
        return super.toString() + " qui est une vache avec " + nbTaches + " taches";
    }
}
