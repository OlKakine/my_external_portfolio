import gui.GUISimulator;
import java.awt.Color;

public class TestConwaySimulator {
	public static void main(String[] args){
		GUISimulator gui = new GUISimulator(500,500, Color.BLACK);
		ConwaySimulator conwaySimulator = new ConwaySimulator();
		gui.setSimulable(conwaySimulator);

		for(int i = 0; i<conwaySimulator.getNbCases(); i++){
			gui.addGraphicalElement(conwaySimulator.getRect(i));
		}
		
	}
}
