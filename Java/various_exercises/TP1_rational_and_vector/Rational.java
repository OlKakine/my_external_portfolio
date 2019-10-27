public class Rational {
	private int num, denom;
	public Rational(int num, int denom ){
		this.num = num;
		setDenom(denom);
	}
	public Rational(int num){
		this(num,1);
	}
	public Rational(){
		this(0,1);
	}
	public Rational(Rational r){
		this(r.num, r.denom);
	}

	private void setDenom(int denom){
		if(denom == 0) throw new IllegalArgumentException("Argument incorrect: denom shouldn't be zero");
		this.denom = denom;

		int fracPgcd = pgcd(this.num, this.denom);
		if( fracPgcd != 1){
			this.num /= fracPgcd;
			this.denom /= fracPgcd;
		}
	}

	@Override
	public String toString(){
		if(this.num == 0) return 0 + "";
		else if(this.denom == 1) return this.num + "";		
		else return this.num + "/" + this.denom;
	}

	public void mult(Rational other){
		this.num *= other.num;
		setDenom(this.denom * other.denom);
	}

	public void add(Rational other){
		this.num = this.num * other.denom + this.denom * other.num;
		setDenom(this.denom * other.denom);
	}

	private int pgcd(int a, int b){
		if(b == 0) return a;
		return pgcd(b, a%b);
	}

	public static Rational mult(Rational a, Rational b){
		Rational newFrac = new Rational(a.num, a.denom);
		a.mult(b);
		return a;
	}
}


