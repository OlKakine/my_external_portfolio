import gui.*;
import java.awt.Point;
import java.awt.Color;
import java.util.Random;

public class BallsSimulator implements Simulable {
	private int nbOvals = 10;
	private Oval[] ovals  = new Oval[this.nbOvals];
	private Oval[] initOvals  = new Oval[this.nbOvals];
	private int[] dxs  = new int[this.nbOvals];
	private int[] initDxs = new int[this.nbOvals];
	private int[] dys  = new int[this.nbOvals];
	private int[] initDys = new int[this.nbOvals];
	

	private Random rand = new Random();
	private static int guiW = 850;
	private static int guiH = 500;
	private Color color = Color.WHITE;
	private int size = 5;
	
	public BallsSimulator(){	
		for(int i=0; i<nbOvals; i++){
			int randX = rand.nextInt(BallsSimulator.guiW-1)+1;
			int randY = rand.nextInt(BallsSimulator.guiH-1)+1;
			this.ovals[i] = new Oval(randX, randY , this.color,
									 this.color,this.size);
			this.initOvals[i] = new Oval(randX, randY, this.color,
										 this.color, this.size);

			int dx = 0;
			int dy = 0;
			while(dx*dy == 0){ // we want balls to move
				dx = rand.nextInt(3) - 1;
				dy = rand.nextInt(3) - 1;
			}
			
			this.dxs[i] = dx;
			this.initDxs[i] = dx;
		    this.dys[i] = dy;
			this.initDys[i] = dy;
		}
		
	}

	public Oval getOval(int i){
		return this.ovals[i];
	}

	public int getNbOvals(){
		return this.nbOvals;
	}
	
	@Override
	public void next(){
		for(int i=0; i<this.nbOvals; i++){
			ovals[i].translate(this.dxs[i],this.dys[i]);

			//we make balls to bounce
			int x = ovals[i].getX();
			int y = ovals[i].getY();
			if(x==0 || x==BallsSimulator.guiW)
				this.dxs[i] = 0 - this.dxs[i];
			if(y==0 || y==BallsSimulator.guiH)
				this.dys[i] = 0 - this.dys[i];
		}			
	}

	@Override public void restart(){
		for(int i=0; i<nbOvals; i++){
			this.ovals[i].translate(this.initOvals[i].getX() - this.ovals[i].getX(),
									this.initOvals[i].getY() - this.ovals[i].getY());
			this.dxs[i] = this.initDxs[i];
			this.dys[i] = this.initDys[i];
		}
	}
}


// public class BallsSimulator implements Simulable {
// 	private Balls balls; //useless only need ovals
// 	private Oval[] ovals;

// 	public BallsSimulator(){
// 		this.balls = new Balls();
// 		this.ovals = new Oval[balls.size()];
// 		for(int i=0; i<balls.size(); i++){
// 			Point p = this.balls.getBall(i);
// 			this.ovals[i] = new Oval((int)p.getX(), (int)p.getY(), Color.WHITE, Color.WHITE, 5);
// 		}
// 	}

// 	private void updateOvals(){
// 		for (int i = 0 ; i<this.ovals.length; i++){
// 			this.ovals[i].translate((int)this.balls.getBall(i).getX() - this.ovals[i].getX(),
// 									(int)this.balls.getBall(i).getY() - this.ovals[i].getY());
// 		} 
// 	}

// 	public Oval getOval(int i){
// 		return this.ovals[i];
// 	}
	
// 	@Override
// 	public void next(){
// 		this.balls.translate(1,2);
// 		updateOvals();
		
// 	}

// 	@Override public void restart(){
// 		this.balls.reInit();
// 		updateOvals();
// 	}
// }
