import java.awt.geom.Line2D.Double;
import gui.*;
import java.awt.Color;
import java.awt.Polygon;
import java.util.Random;
import java.awt.Point;
import java.lang.Math;
import java.util.LinkedList;

public class Boids implements GraphicalElement{
	private static final int nbBoids = 100;
	Double[] boids = new Double[nbBoids];
	Double[] boidsCopy = new Double[nbBoids] ;
	Double[] boidsInit = new Double[nbBoids];
	
	private Random rand = new Random();
	private static final int distNeighbour = 500;
	private static final int ratioRule1 = 100;
	private static final int limDistRule2 = 5;
	private static final int ratioRule3 = 8;
	private static final double deadAngle = 70; //degrees

	private void deepCopyBoids(Double[] boidsToCopy, Double[] boidsCopied){
		for(int i=0; i< nbBoids; i++)
			boidsCopied[i] = new Double(boidsToCopy[i].getP1(), boidsToCopy[i].getP2());
	}

	public Boids(int guiW, int guiH){		
		int xCenter = guiW/2;
		int yCenter = guiH/2;
		int distToCenter = Math.min(50, Math.min( guiW - xCenter, guiH - yCenter));
		int maxSpeed = 3;
		
		int globalMovementX = 1; // 1 for right, -1 for left
		int globalMovementY = 1; // -1 for up
		
		for(int i=0; i < nbBoids; i++){
			//on focalise les boids au milieu
			int xP1 = xCenter + rand.nextInt(distToCenter*2) - distToCenter;
			int yP1 = yCenter + rand.nextInt(distToCenter*2) - distToCenter;

			int xP2 = xP1 + rand.nextInt(maxSpeed) - maxSpeed/2 + globalMovementX;
			int yP2 = yP1 + rand.nextInt(maxSpeed) - maxSpeed/2 + globalMovementY;

			boids[i] = new Double(xP1, yP1, xP2, yP2);
		}
		
		deepCopyBoids(boids, boidsInit);
		deepCopyBoids(boids, boidsCopy);
	}

	public void stepMove(){
		for(int i=0; i<nbBoids; i++){
			Double copyBoid = boidsCopy[i];
			Double boid = boids[i];

			LinkedList<Double> neighbours = findNeighbours(copyBoid);
			if(neighbours.size() == 0) break;
			
			Double v1 = rule1(copyBoid, neighbours);
			addVector(boid,v1);
			Double v2 = rule2(copyBoid, neighbours);
			addVector(boid,v2);
			Double v3 = rule3(copyBoid, neighbours);
			addVector(boid,v3);

			stepMoveBoid(boid);
		}

		for(int i=0; i<nbBoids; i++)
			boidsCopy[i].setLine(boids[i]);
	}

	private Double rule1(Double boid, LinkedList<Double> neib){
		int finalX = 0;
		int finalY = 0;
		for(Double b: neib){
			finalX += b.getX1();
			finalY += b.getY1();
		}

		int dx = (int) ((finalX/neib.size() - boid.getX1()) / ratioRule1 );
		int dy = (int) ((finalY/neib.size() - boid.getY1()) / ratioRule1) ;

		return new Double(0,0,dx,dy);
	}

	private Double rule2(Double boid, LinkedList<Double> neib){
		int x = (int)boid.getX1();
		int y = (int)boid.getY1();

		Double v = new Double();
		for(Double b: neib){
			int dx = (int) b.getX1() - x;
			int dy = (int) b.getY1() - y;
			if(Math.abs(dx) < limDistRule2 && Math.abs(dy) < limDistRule2)
				addVector(v, new Double(0,0,-dx, -dy));
		}

		return v;
	}

	private Double rule3(Double boid, LinkedList<Double> neib){
		Double v = new Double();
		
		for(Double b: neib)
			addVector(v, b);

		v.setLine(0,0, v.getX2() / neib.size(), v.getY2() / neib.size()); //averaging
		
		int dx = getDx(boid);
		int dy = getDy(boid);
		addVector(v, new Double(0,0,-dx, -dy));
		v.setLine(0,0, v.getX2() / ratioRule3, v.getY2() / ratioRule3); //normalizing
		
		return v;
	}	

	private LinkedList<Double> findNeighbours(Double b){
		//brute force one
		LinkedList<Double> neighbours = new LinkedList<Double>();

		Polygon backTriangle = getDeadAnglePolygon(b);

		for(Double boid: boids)
			if( !b.equals(boid) && !backTriangle.contains(boid.getP1()) && isNeighbour(b,boid))
				neighbours.add(boid);
		return neighbours;
	}

	private Polygon getDeadAnglePolygon(Double b){
		int dx = getDx(b);
		int dy = getDy(b);
		int xP1 = (int) b.getX1();
		int yP1 = (int) b.getY1();

		double insideAngleVector = dx == 0 ? 90 : Math.atan(dy/dx);
		double outsideAngleVector = 90 - insideAngleVector; //inside means in the side which touches the horizontal diameter
		double semiDeadAngle = deadAngle / 2;
		double angleInside = insideAngleVector - semiDeadAngle;
		double angleOutside = outsideAngleVector - semiDeadAngle;

		int dxInside = (int) Math.floor(distNeighbour *  Math.cos(angleInside));
		int dyInside = (int) Math.floor(distNeighbour *  Math.sin(angleInside));

		int xP2 = xP1 + dxInside;
		int yP2 = yP1 + dyInside;

		int dyOutside = (int) Math.floor(distNeighbour *  Math.cos(angleOutside));
		int dxOutside = (int) Math.floor(distNeighbour *  Math.sin(angleOutside));

		int xP3 = xP1 + dxOutside;
		int yP3 = yP1 + dyOutside;

		return new Polygon(new int[] {xP1, xP2, xP3}, new int[] {yP1, yP2, yP3}, 3);

	}

	private boolean isNeighbour(Double b1, Double b2){ //TODO: add gestion champ vision
		return b1.getP1().distance(b2.getP2()) < distNeighbour;
	}
	
	/** vectorial additon of v2 on v1 */
	private void addVector(Double v1, Double v2){
		int dx = getDx(v2);
		int dy = getDy(v2);
		v1.setLine(v1.getX1(), v1.getY1(), v1.getX2() + dx, v1.getY2() + dy);
	}

	/** move boid according to current velocity, which he keeps to the next step */
	private void stepMoveBoid(Double boid){
		int dx = getDx(boid);
		int dy = getDy(boid);
		int x2 = (int)boid.getX2();
		int y2 = (int)boid.getY2();
		boid.setLine(x2, y2, x2 + dx, y2 + dy);
	}

	private int getDx(Double v){ return (int) (v.getX2() - v.getX1());}
	private int getDy(Double v){ return (int) (v.getY2() - v.getY1());}

	public void reInit(){
		deepCopyBoids(boidsInit, boids);
		deepCopyBoids(boidsInit, boidsCopy);
	}
	
	@Override
	public void paint(java.awt.Graphics2D g2d){
		for(Double boid : boids)
		{
			Point p = new Point((int)boid.getX1(), (int)boid.getY1());
			gui.Rectangle graphicalR = new gui.Rectangle((int)p.getX(), (int)p.getY(),
														 Color.WHITE, Color.GREEN, 3);
			graphicalR.paint(g2d);
		}			
	}
	
}
