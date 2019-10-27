import java.awt.Point;

public class Balls{
	Point[] balls;

	public Balls(){
		this.balls = new Point[2];
		this.balls[0] = new Point(1,1);
		this.balls[1] = new Point(2,2);
	}

	public void translate(int dx, int dy){
		for(Point p: balls)
			p.translate(dx, dy);
		System.out.println(this);
	}

	public void reInit(){
		this.balls[0] = new Point(1,1);
		this.balls[1] = new Point(2,2);
		// ou this();
	}

	@Override
	public String toString(){
		return this.balls[0].toString() + " " + this.balls[1].toString();
	}

	public Point getBall(int i){
		return balls[i];
	}

	public int size(){
		return balls.length;
	}
	
}
