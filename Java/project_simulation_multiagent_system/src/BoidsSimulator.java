import gui.*;
import java.awt.Color;
import java.util.Random;

public class BoidsSimulator implements Simulable {
	//can rpz boids with rect thx to Double.getRect
	Boids boids;

	private static final int guiW = 500;
	private static final int guiH = 500;

	public BoidsSimulator(){
		boids = new Boids(guiW, guiH);		
	}

	public Boids getBoidsGraphicalElement(){
		return boids;
	}

	@Override
	public void next(){
		boids.stepMove();
	}

	@Override
	public void restart(){
		boids.reInit();
	}

	
	
	// private Random rand = new Random();
	// private static int guiW = 50;
	// private static int guiH = 50;
	// private static int nbCases = BoidsSimulator.guiH * BoidsSimulator.guiW;
	// private static int size = 10;

	// private Color[] colors = {Color.WHITE, Color.BLUE};
	// //case vaut 1 si alive a l'init
	// private boolean[][] initCases = new boolean[BoidsSimulator.guiH][BoidsSimulator.guiW];

	// private boolean isIterEven = true;
	// private boolean[][] evenCases = new boolean[BoidsSimulator.guiH][BoidsSimulator.guiW];
	// private boolean[][] unevenCases = new boolean[BoidsSimulator.guiH][BoidsSimulator.guiW];
	
	// private ColorableSquare[][] cases =
	// 	new ColorableSquare[BoidsSimulator.guiH][BoidsSimulator.guiW];
	
	// public BoidsSimulator(){
		
		
	// 	int dead;
	// 	for(int i=0; i<50; i++){
	// 		for(int j=0; j<50; j++){
	// 			//if(i<20 ||  i>30 || j>30 || j<20) dead = 1; //on focalise les cases vivantes au milieu
	// 			//else dead = rand.nextInt(7);
	// 			dead = rand.nextInt(7);
				
	// 			switch(dead){
	// 			case 0: //not dead -> alive
	// 				initCases[i][j] = true;
	// 				evenCases[i][j] = true;
	// 				unevenCases[i][j] = true;
	// 				cases[i][j] = new ColorableSquare(10*i, 10*j, Color.BLACK,
	// 													colors[1], BoidsSimulator.size);
	// 				break;
	// 			default:
	// 				cases[i][j] = new ColorableSquare(10*i, 10*j, Color.BLACK,
	// 													colors[0], BoidsSimulator.size);
	// 			}
	// 		}
	// 	}
	// }

	// public ColorableSquare getRect(int i){
	// 	return this.cases[(int) (i/50)][i%50];
	// }

	// public int getNbCases(){
	// 	return BoidsSimulator.nbCases;
	// }

	// private void computeCaseAndChangeColor(int i, int j){ //can be optimized
	// 	boolean[][] currentCases = isIterEven ? evenCases : unevenCases;
	// 	boolean[][] nextCases = isIterEven ? unevenCases : evenCases;

	// 	int nbAliveNeighbour = 0;
	// 	for (int x=-1; x<2; x++){
	// 		int neighbourI = i + x - 50;
	// 		while(neighbourI < 0) neighbourI += 50; //kind of modulo
	// 		for(int y = -1; y<2; y++){				
	// 			int neighbourJ = j + y - 50;
	// 			while(neighbourJ < 0 ) neighbourJ += 50;
	// 			nbAliveNeighbour += currentCases[neighbourI][neighbourJ] ? 1 : 0;
	// 		}
	// 	}			

	// 	if(currentCases[i][j] == false){//si case morte
	// 		if(nbAliveNeighbour == 3){
	// 			nextCases[i][j] = true;//elle devient vivante
	// 			cases[i][j].changeColor(colors[1]);
	// 		}
	// 		else
	// 			nextCases[i][j] = false;
	// 	}
	// 	else if(nbAliveNeighbour != 3 && nbAliveNeighbour != 4){
	// 		nextCases[i][j] = false;
	// 		cases[i][j].changeColor(colors[0]);
	// 	}
	// 	else
	// 		nextCases[i][j] = true;
	// }
	
	// public void next(){ //can optimize by knowing the limits of alive cases
	// 	for(int i=0; i<BoidsSimulator.guiH; i++)
	// 		for(int j=0; j<BoidsSimulator.guiW; j++)
	// 			computeCaseAndChangeColor(i,j);

	// 	isIterEven = !isIterEven;
	// }

	// @Override public void restart(){
	// 	boolean[][] currentCases = isIterEven ? evenCases : unevenCases;
	// 	boolean[][] nextCases = isIterEven ? unevenCases : evenCases;
		
	// 	for(int i=0; i<50; i++){
	// 		for(int j=0; j<50; j++){
	// 			if(initCases[i][j] != currentCases[i][j])
	// 				cases[i][j].changeColor(colors[initCases[i][j] ? 1 : 0]); //cannot convert
				
	// 			currentCases[i][j] = initCases[i][j];
	// 			nextCases[i][j] = initCases[i][j];
	// 		}
	// 	}
	// 	isIterEven = true;
	// }
}
