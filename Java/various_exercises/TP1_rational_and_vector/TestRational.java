public class TestRational {
	public static void main(String[] args){
		Rational frac1 = new Rational(3,2);
		System.out.println(frac1);
		Rational frac2 = new Rational(1,3);
		System.out.println(frac2);
		
		frac1.mult(frac2);
		System.out.println(frac1);
		
		Rational frac3 = Rational.mult(frac1, frac2);
		System.out.println(frac3);
	}
}

