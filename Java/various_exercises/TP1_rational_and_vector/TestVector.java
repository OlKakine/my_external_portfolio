public class TestVector {
	public static void main(String[] args){
		System.out.println("Test1: vect contains its own rationals");		
		Rational frac1 = new Rational(2,3);
		Rational frac2 = new Rational(3,2);		
		Vector v = new Vector(2);
		v.set(0, frac1);
		System.out.println(v);		
		frac1.mult(frac2);
		System.out.println(v);

		System.out.println("Test2: same");
		v.set(0, new Rational(1,2));
		v.set(1, new Rational(1,2));
		System.out.println(v);
		Rational a = v.get(0);
		a.mult(new Rational(1,3));
		System.out.println(v);

		System.out.println("Test mult *3");
		v.mult(new Rational(3));
		System.out.println(v);		

		System.out.println("Test add v + v");		
		v.add(v);
		System.out.println(v);

		System.out.println("Test extensible vect");
		ExtensibleVector v1 = new ExtensibleVector(v);
		System.out.println(v1);
		v1.add(new Rational(2,3));
		System.out.println(v1);
		System.out.println(v);
	}
}
