public class TestBalls {
	public static void main(String[] args) {
		Balls b = new Balls();
		System.out.println(b);
		b.translate(1,2);
		System.out.println(b);
		b.reInit();
		System.out.println(b);
	}
}
