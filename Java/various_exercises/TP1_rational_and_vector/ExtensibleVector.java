public class ExtensibleVector extends Vector {
	public void add(Rational r){
		Rational[] new_tab = new Rational[this.tab.length+1];
		for(int i=0; i<this.tab.length; i++)
			new_tab[i] = this.tab[i];
		new_tab[this.tab.length] = r;
		this.tab = new_tab;
	}

	public ExtensibleVector(int size){
		super(size);
	}
	public ExtensibleVector(Vector v){
		super(v);
	}

	public int getDimension(){
		return super.tab.length;
	}

	

	
}
