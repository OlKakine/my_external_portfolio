public class Vector {
	protected Rational[] tab;

	public Vector(int size){
		if(size < 0) throw new IllegalArgumentException("Vector size can't be negative");
		this.tab = new Rational[size];
		for(int i=0; i<size; i++)
			this.tab[i] = new Rational();	
	}
	public Vector(Vector v){
		this.tab = new Rational[v.tab.length];
		for(int i=0; i<v.tab.length; i++)
			this.tab[i] = v.tab[i];
	}

	@Override
	public String toString(){
		String s = "(";
		for(Rational r: this.tab)
			s = s + (String) r.toString() + ", ";
		if(this.tab.length != 0)
			s = s.substring(0, s.length()-2);
		s = s+ ")";
		return s;
	}

	public void set(int i, Rational r){
		if(i>= this.tab.length) throw new IllegalArgumentException("Indice out of vector bound");
		tab[i] = new Rational(r);
	}

	public Rational get(int i){
		if(i>= this.tab.length) throw new IllegalArgumentException("Indice out of vector bound");
		return new Rational(tab[i]);
	}

	public void mult(Rational factor){
		for(Rational r: this.tab)
			r.mult(factor);
	}

	public void add(Vector v){
		if(this.tab.length != v.tab.length) throw new IllegalArgumentException("Can't add Vectors of different sizes.");
		for(int i=0; i<this.tab.length; i++)
			this.tab[i].add(v.tab[i]);
	}

	
}
